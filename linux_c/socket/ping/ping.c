#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip_icmp.h>

#include <arpa/inet.h>

#define IP "87.240.180.136"
#define PORT 0

struct timeval tv1, tv2, dtv;
struct timezone tz;

void tstart(){
    gettimeofday(&tv1, &tz);
}

long tstop(){
    gettimeofday(&tv2, &tz);
    dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
    if(dtv.tv_sec < 0){
        dtv.tv_sec--;
        dtv.tv_usec+=1000000;
    }
    return dtv.tv_sec*1000 + dtv.tv_usec/1000;
}

struct icmp_msg{
    struct icmphdr hdr;
    char msg[64-sizeof(struct icmphdr)];
};
 
unsigned short csum(void *hdr, int len){
    unsigned short* buff = hdr;
    unsigned sum = 0;
    unsigned short ssum;
    unsigned short count = len >> 1;

    while(count--)
        sum += *buff++;
    if(len & 1)
        sum += *(unsigned char*)buff;
    sum = (unsigned short)sum + (sum >> 16) & 0xFFFF;
    ssum = (unsigned short)sum + (unsigned short)(sum >> 16);

    return (ssum != 0xFFFF) ? ~ssum : ssum;
}

int main(int argc, char const *argv[]){
    struct sockaddr_in send_addr, recv_addr;
    int send_len = sizeof(send_addr);
    int recv_len = sizeof(recv_addr);
    int sock, try = 6, sending = 0, recving = 0;
    long ping_time; 
    struct icmp_msg packet;
    short index = 48;
    char msg[] = "0-try ping";
    
	send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons (PORT);
    send_addr.sin_addr.s_addr  = inet_addr(IP);
 
    printf("Connect to IP: %s PORT: %d\n\n", IP, PORT);
 
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sock < 0){
        perror("fail sock: ");
        exit(1);
    }
    
	while(try--){
        bzero(&packet, sizeof(packet));
        packet.hdr.type = ICMP_ECHO;
        
        msg[0] = (char)index++;
        strcpy(packet.msg, msg);
        
        packet.hdr.checksum = csum(&packet, sizeof(packet));

        if(sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*) &send_addr, send_len) <= 0){
            perror("sendto: ");
        }else{
            sending++;
            tstart();
        }
		
        if(recvfrom(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&recv_addr, &recv_len) <= 0) {
            perror("recvfrom: ");
		}else{
            recving++;
            ping_time = tstop();
        }         
		printf(" %s ping = %dms.\n", inet_ntoa(recv_addr.sin_addr), ping_time);
		
		sleep(1);
    }                
    printf("\nstatus: %d/%d packets, %d loss\n", sending, recving, (sending - recving)); 
    
    return 0;
}