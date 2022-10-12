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
#include<linux/if_ether.h>

void print_ip_header(unsigned char* , int);
void print_udp_packet(unsigned char * , int);
void PrintData (unsigned char* , int);

struct sockaddr_in source,dest;
int i, j;
struct ethhdr eth;
eth.

struct UdpHeader{
    u_short src_port;
    u_short targ_port;
    u_short length;
    u_short checksum;
};

void ShowBin(char a)
{
    for (int i = 0; i < 8; i++){
        //Проверяем старший бит)
        if (a & 0x80)
            printf("1");
        else printf("0");
        //Сдвигаем влево на 1 бит
        a = a << 1;
    }
}

int main(int argc, char const *argv[]){
    char msg[1024];
    char msg_sv[] = "hello!\n";
    char msgbuf[256];
    int fdsock, bytes;
    fdsock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if(fdsock < 0){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr_sv, addr;
    
    int my_port = 1234;

    struct UdpHeader header;
    header.src_port = htons(my_port);
    header.targ_port = htons(7777);
    header.length = htons(sizeof(header) + sizeof(msg_sv));
    header.checksum = 0;

    memcpy((void*)msgbuf, (void*)&header, sizeof(header));
    memcpy((void*)(msgbuf+sizeof(header)),(void*)msg_sv, sizeof(msg_sv));

    addr_sv.sin_family = AF_INET;
    addr_sv.sin_port = htons(7777);
    inet_aton("192.168.16.32", &addr_sv.sin_addr);

    int addr_len = sizeof(addr);
    int addr_sv_len = sizeof(addr_sv);
    
    //sendto(fdsock, msgbuf, sizeof(msg_sv) + sizeof(header), 0, (struct sockaddr*)&addr_sv, addr_sv_len);
    
    unsigned short iphdrlen;
    unsigned short *ptr;
    struct iphdr *iph;
    struct udphdr *udph;
    int times = 0;
    while(1){
        
        
        sendto(fdsock, msgbuf, sizeof(msg_sv) + sizeof(header), 0, (struct sockaddr*)&addr_sv, addr_sv_len);
        
        sleep(2);
        
        bytes = recvfrom(fdsock, msg, sizeof(msg), 0, (struct sockaddr*)&addr, &addr_len);
        print_udp_packet(msg, bytes);

        //iph = (struct iphdr*)msg;
        //iphdrlen = iph->ihl*4;
        //udph = (struct udphdr*)(msg+iphdrlen);
        //if(ntohs(udph->source) == 7777){
        //    for(int i = 28; msg[i] != '\0'; i++){
        //        printf("%c", msg[i]);
        //    }
        //}

        //for(int i = 0; i < 30; i++)
        //    printf("%d)%c -- %d\n", i, msg[i], (u_int16_t)msg[i]);
        //ShowBin(msg[20]);
        //printf(" ");
        //ShowBin(msg[21]);
        //printf("\n");
        //printf("\n%d", ntohs((unsigned short)msg[11]));
    }
    return 0;

}

void print_udp_packet(unsigned char *Buffer , int Size)
{
     
    unsigned short iphdrlen;
     
    struct iphdr *iph = (struct iphdr *)Buffer;
    iphdrlen = iph->ihl*4;
     
    struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen);
     
    printf("\n\n***********************UDP Packet*************************\n");
     
    print_ip_header(Buffer,Size);           
     
    printf("\nUDP Header\n");
    printf("   |-Source Port      : %d\n" , ntohs(udph->source));
    printf("   |-Destination Port : %d\n" , ntohs(udph->dest));
    printf("   |-UDP Length       : %d\n" , ntohs(udph->len));
    printf("   |-UDP Checksum     : %d\n" , ntohs(udph->check));
     
    printf("\n");
    printf("IP Header\n");
    PrintData(Buffer , iphdrlen);
         
    printf("UDP Header\n");
    PrintData(Buffer+iphdrlen , sizeof udph);
         
    printf("Data Payload\n");  
    PrintData(Buffer + iphdrlen + sizeof udph ,( Size - sizeof udph - iph->ihl * 4 ));
     
    printf("\n###########################################################");
}

 
void print_ip_header(unsigned char* Buffer, int Size)
{
    unsigned short iphdrlen;        
    struct iphdr *iph = (struct iphdr *)Buffer;
    iphdrlen =iph->ihl*4;
     
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = iph->saddr;
     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;
     
    printf("\n");
    printf("IP Header\n");
    printf("   |-IP Version        : %d\n",(unsigned int)iph->version);
    printf("   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
    printf("   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
    printf("   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
    printf("   |-Identification    : %d\n",ntohs(iph->id));
    printf("   |-TTL      : %d\n",(unsigned int)iph->ttl);
    printf("   |-Protocol : %d\n",(unsigned int)iph->protocol);
    printf("   |-Checksum : %d\n",ntohs(iph->check));
    printf("   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
    printf("   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
}

void PrintData (unsigned char* data , int Size)
{
     
    for(i=0 ; i < Size ; i++)
    {
        if( i!=0 && i%16==0)   //if one line of hex printing is complete...
        {
            printf("         ");
            for(j=i-16 ; j<i ; j++)
            {
                if(data[j]>=32 && data[j]<=128)
                    printf("%c",(unsigned char)data[j]); //if its a number or alphabet
                 
                else printf("."); //otherwise print a dot
            }
            printf("\n");
        } 
         
        if(i%16==0) printf("   ");
            printf(" %02X",(unsigned int)data[i]);
                 
        if( i==Size-1)  //print the last spaces
        {
            for(j=0;j<15-i%16;j++) printf("   "); //extra spaces
             
            printf("         ");
             
            for(j=i-i%16 ; j<=i ; j++)
            {
                if(data[j]>=32 && data[j]<=128) printf("%c",(unsigned char)data[j]);
                else printf(".");
            }
            printf("\n");
        }
    }
}