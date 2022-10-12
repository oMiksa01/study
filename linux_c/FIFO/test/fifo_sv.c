#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd_fifo; 
    char buf[1024];

    unlink("./fifo0001.1");
    if((mkfifo("./fifo0001.1", O_RDWR)) == -1){
        printf("Невозможно создать fifo\n");
        exit(0);
    }

    if((fd_fifo = open("./fifo0001.1", O_RDONLY))<0){
        perror("fifo open"); 
        exit(0); 
    }

    while(1){
        read(fd_fifo, &buf, sizeof(buf));
        printf("%s\n",buf);
        sleep(2);
    }

    close(fd_fifo);

    return 0;
}