#include<stdio.h> //For standard things
#include<stdlib.h>    //malloc
#include<string.h>    //memset
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MY_PORT 1234
#define PORT 7777
#define IP "192.168.16.32"

struct UdpHeader{
    u_short src_port;
    u_short targ_port;
    u_short length;
    u_short checksum;
};

int main(int argc, char const *argv[]){
    char msg_in[1024];//для приёма
    char msg_out[] = "hello!\n";//сообщение
    char msgbuf[256];//будем отпровлять
    int fdsock;
    
    fdsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fdsock < 0){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr_sv, addr;
    
    //UDP header
    struct UdpHeader header;
    header.src_port = htons(MY_PORT);
    header.targ_port = htons(PORT);
    header.length = htons(sizeof(header) + sizeof(msg_out));
    header.checksum = 0;

    //header+msg
    memcpy((void*)msgbuf, (void*)&header, sizeof(header));
    memcpy((void*)(msgbuf+sizeof(header)),(void*)msg_out, sizeof(msg_out));

    addr_sv.sin_family = AF_INET;
    addr_sv.sin_port = htons(PORT);
    inet_aton(IP, &addr_sv.sin_addr);

    int addr_len = sizeof(addr);
    int addr_sv_len = sizeof(addr_sv);
    
    unsigned short iphdrlen;
    struct iphdr *iph;//ip hearder
    struct udphdr *udph;//udp header

    sendto(fdsock, msgbuf, sizeof(msg_out) + sizeof(header), 0, (struct sockaddr*)&addr_sv, addr_sv_len);
        
    while(1){
        recvfrom(fdsock, msg_in, sizeof(msg_in), 0, (struct sockaddr*)&addr, &addr_len);
        
        //ip len
        iph = (struct iphdr*)msg_in;
        iphdrlen = iph->ihl*4;//5*4

        udph = (struct udphdr*)(msg_in+iphdrlen);
        if(ntohs(udph->source) == PORT){
            for(int i = iphdrlen + 8; msg_in[i] != '\0'; i++){
                printf("%c", msg_in[i]);
            }
            printf("\n");
        }
    }
    return 0;

}
