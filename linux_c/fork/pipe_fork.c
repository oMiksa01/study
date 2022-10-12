#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd[2], refd[2];
    char str[20] = "Hello";

    pipe(fd);
    pipe(refd);

    if(!fork()){
        char buff[20], rebuff[20];
        close(fd[1]);
        close(refd[0]);
        read(fd[0], buff, 20);
        strcpy(rebuff,"And you,");
        strcat(rebuff, buff);
        write(refd[1], rebuff, 20);
    }else{
        close(fd[0]);
        close(refd[1]);
        write(fd[1], str, 20);
        wait(NULL);
        read(refd[0], str, 20);
        printf("%s\n", str);
    }








    return 0;
}
