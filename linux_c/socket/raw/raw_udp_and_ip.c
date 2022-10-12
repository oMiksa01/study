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
    int fdsock, fdRAW;
    
    fdsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fdsock < 0){
        perror("socket");
        exit(1);
    }

    fdRAW = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(fdRAW < 0){
        perror("socket");
        exit(1);
    }

    int val = 1;
    setsockopt(fdRAW,IPPROTO_IP, IP_HDRINCL, &val, sizeof(val));

    struct sockaddr_in addr_sv, addr;
    
    //UDP header
    struct udphdr header;
    struct iphdr ipheader;

    header.source = htons(MY_PORT);
    header.dest = htons(PORT);
    header.len = htons(sizeof(msgbuf)-sizeof(ipheader));
    header.check = htons(0);


    ipheader.version = 4;//IPv4
    ipheader.ihl = 5;//5*4=20
    ipheader.tos = 0;//трафик
    ipheader.tot_len = htons(sizeof(msgbuf));//len(ipH+udpH+msg)
    ipheader.id = htons(0);//индификатор пакета
    ipheader.frag_off = 0;//флаги 0|DF|MF
    ipheader.ttl = 64;//hit point
    ipheader.protocol = 17;//udp
    ipheader.check = htons(0);//csum
    ipheader.saddr = inet_addr(IP);//IPs
    ipheader.daddr = inet_addr(IP);//IPd
    
    //ipH+udpH+msg
    memcpy((void*)msgbuf, (void*)&ipheader, sizeof(ipheader));
    memcpy((void*)(msgbuf+sizeof(ipheader)), (void*)&header, sizeof(header));
    memcpy((void*)(msgbuf+sizeof(ipheader)+sizeof(header)),(void*)&msg_out, sizeof(msg_out));

    addr_sv.sin_family = AF_INET;
    addr_sv.sin_port = htons(PORT);
    inet_aton(IP, &addr_sv.sin_addr);

    int addr_len = sizeof(addr);
    int addr_sv_len = sizeof(addr_sv);
    
    unsigned short iphdrlen;
    struct iphdr *iph;//ip hearder
    struct udphdr *udph;//udp header

    sendto(fdRAW, msgbuf, sizeof(msgbuf), 0, (struct sockaddr*)&addr_sv, addr_sv_len);
        
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



