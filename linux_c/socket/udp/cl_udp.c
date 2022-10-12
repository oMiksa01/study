#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

char msg[1024] = "Hello there!\n";

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    inet_aton("192.168.16.32", &addr.sin_addr);
    sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&addr, sizeof(addr));
    
    recvfrom(sock, msg, sizeof(msg), 0, 0, 0);
    printf(msg);
    close(sock);

    return 0;
}