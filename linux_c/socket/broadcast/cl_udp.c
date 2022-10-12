#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sock, bytes_read;
    struct sockaddr_in addr, cl;
    char mesg[1024];

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0){
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = inet_addr("192.168.1.255");
    
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(2);
    }

    bytes_read = recvfrom(sock, mesg, sizeof(mesg), 0, (struct sockaddr *)&cl, sizeof(cl));
    mesg[bytes_read] = '\0';
    printf("%s\n", mesg); 
    
    close(sock);

    return 0;
}