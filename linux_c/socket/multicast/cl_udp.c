#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int sock, bytes_read, addrlen;
    struct sockaddr_in addr, cl;
    char msg[1024];

    if(sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) < 0){
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("192.168.16.32");
    
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(2);
    }

    struct ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.1");         
    mreq.imr_interface.s_addr = inet_addr("192.168.16.32");
    int mreqlen = sizeof(mreq);

    if(setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, mreqlen) < 0){
        perror("setsockopt mreq");
	    exit(1);
    }

    int cllen = sizeof(cl);
    while(1){
        bytes_read = recvfrom(sock, msg, sizeof(msg), 0, (struct sockaddr *)&cl, &cllen);
        if(bytes_read < 0){
            perror("recvfrom");
	        exit(1);
        }

        printf("ip(%s) meg =>%s\n", inet_ntoa(cl.sin_addr), msg); 
    }
    close(sock);

    return 0;
}