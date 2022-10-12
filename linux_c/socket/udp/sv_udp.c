#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock;
    struct sockaddr_in addr, cl;
    int slen = sizeof(cl);
    char buf[1024];
    int bytes_read;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    inet_aton("192.168.16.32", &addr.sin_addr);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    while(1)
    {
        recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&cl, &slen);
        printf(buf);
        strcat(buf, "and you, Hi\n");
        sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&cl, slen);
    }
    
    return 0;
}