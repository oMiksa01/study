#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main()
{
    int sock, val = 1;
    struct sockaddr_in addr;
    char buf[1024] = "Hello people";
    
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0){
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("192.168.1.255");

    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));

    while(1)
        sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));

    return 0;
}