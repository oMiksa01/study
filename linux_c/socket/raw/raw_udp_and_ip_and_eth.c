#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define ETHER_TYPE	0x0800
#define MY_PORT 1234
#define TARGET_PORT 7777
#define MY_IP "192.168.16.32"
#define TARGET_IP "192.168.0.1"

#define MAC1s 0xAC
#define MAC2s 0x16
#define MAC3s 0x2D
#define MAC4s 0x4C
#define MAC5s 0xE9
#define MAC6s 0x79

#define MAC1d 0xAC
#define MAC2d 0x16
#define MAC3d 0x2D
#define MAC4d 0x4C
#define MAC5d 0xE9
#define MAC6d 0x79

int main(int argc, char const *argv[]){
    char buff[256];
    char msg[] = "hello!";
    struct ethhdr MACh;
	struct iphdr iph;
	struct udphdr udph;
    struct sockaddr_ll addrS, addrD;
    int sock;

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock < 0){
        perror("socket");
        exit(1);
    }

    udph.source = htons(MY_PORT);
    udph.dest = htons(TARGET_PORT);
    udph.len = htons(sizeof(udph)+sizeof(msg));
    udph.check = htons(0);

    iph.version = 4;//IPv4
    iph.ihl = 5;//5*4=20
    iph.tos = 0;//трафик
    iph.tot_len = htons(sizeof(iph)+sizeof(udph)+sizeof(msg));//len(ipH+udpH+msg)
    iph.id = htons(0);//индификатор пакета
    iph.frag_off = 0;//флаги 0|DF|MF
    iph.ttl = 64;//hit point
    iph.protocol = 17;//udp
    iph.check = htons(0);//csum
    iph.saddr = inet_addr(MY_IP);//IPs
    iph.daddr = inet_addr(TARGET_IP);//IPd

    MACh.h_dest[0] = MAC1d; 
    MACh.h_dest[1] = MAC2d;
    MACh.h_dest[2] = MAC3d;
    MACh.h_dest[3] = MAC4d;
    MACh.h_dest[4] = MAC5d;
    MACh.h_dest[5] = MAC6d;

    MACh.h_source[0] = MAC1s; 
    MACh.h_source[1] = MAC2s;
    MACh.h_source[2] = MAC3s;
    MACh.h_source[3] = MAC4s;
    MACh.h_source[4] = MAC5s;
    MACh.h_source[5] = MAC6s;

    MACh.h_proto = ETHER_TYPE;

    memcpy((void*)buff, (void*)&MACh, sizeof(MACh));
    memcpy((void*)(buff+sizeof(MACh)), (void*)&iph, sizeof(iph));
    memcpy((void*)(buff+sizeof(MACh)+sizeof(iph)), (void*)&udph, sizeof(udph));
    memcpy((void*)(buff+sizeof(MACh)+sizeof(iph)+sizeof(udph)), (void*)&msg, sizeof(msg));

    addrS.sll_family = AF_PACKET;
    addrS.sll_ifindex = if_nametoindex("eth0");
    addrS.sll_halen = 6;
    
    addrS.sll_addr[0] = MAC1s;
    addrS.sll_addr[1] = MAC2s;
    addrS.sll_addr[2] = MAC3s;
    addrS.sll_addr[3] = MAC4s;
    addrS.sll_addr[4] = MAC5s;
    addrS.sll_addr[5] = MAC6s;

    int addrS_len = sizeof(addrS);
    int addrD_len = sizeof(addrD);

    struct udphdr *header;

    sendto(sock, buff, sizeof(buff), 0, (struct sockaddr_ll*)&addrS, addrS_len);

    while(1){
        recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr_ll*)&addrD, &addrD_len);
        
        header = (struct udphdr*)(buff+sizeof(MACh)+sizeof(iph));
        if(ntohs(header->source) == MY_PORT){
            for(int i = sizeof(MACh)+sizeof(iph)+sizeof(udph); buff[i] != '\0'; i++){
                printf("%c", buff[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
