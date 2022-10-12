#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    int fd_socket, sock;
    struct sockaddr_in addrs;
    char buf[1024];
    int bytes_read;

    addrs.sin_family = AF_INET;
    addrs.sin_port = htons(7777);
    addrs.sin_addr.s_addr = inet_addr("192.168.1.8");

    if((fd_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("socket");
        exit(1);
    }
    if(bind(fd_socket, (struct sockaddr *)&addrs, sizeof(addrs)) < 0){
        perror("bind");
        exit(2);
    }
    listen(fd_socket, 1);

    struct sockaddr_in cl;

    while(1)
    {
        sock = accept(fd_socket, NULL, NULL);//(struct sockaddr_in *)&cl, sizeof(cl));
        if(sock < 0){
            perror("accept");
            exit(3);
        }
        
        switch(fork())
        {
        case -1:
            perror("fork");
            break;
            
        case 0:
            close(fd_socket);
            while(1){
                bytes_read = recv(sock, buf, 1024, 0);
                if(bytes_read <= 0) break;
                printf("%s(%d)\n", buf, getpid());
                sleep(20);
                //printf("%s\n%s\n%s\n", cl.sin_family, cl.sin_addr.s_addr, cl.sin_port);
                send(sock, buf, bytes_read, 0);
            }
            close(sock);
            _exit(0);
            
        default:
            close(sock);
        }
    }
    close(fd_socket);
    return 0;
}