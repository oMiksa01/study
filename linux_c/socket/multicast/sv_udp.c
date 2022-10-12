#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    int sock, val = 1;
    struct sockaddr_in addr;
    char buf[] = "Hello people, this is Multicast";
    int addrlen = sizeof(buf);

    if(sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) < 0){
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("224.0.0.1");
    
    while(1)
        sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, addrlen);
        sleep(2);
    return 0;
}