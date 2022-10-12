#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd_fifo;    
    char buffer[1024] = "Hello men\n";

    if((fd_fifo = open("./fifo0001.1", O_WRONLY))<0){
        perror("fd_fifo open"); 
        exit(0); 
    }

    write(fd_fifo, buffer, strlen(buffer));

    close(fd_fifo);

    return 0;
} 