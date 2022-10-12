#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "server.h"

int main(int argc, char **argv){
    int fdpub, fdpriv, fd;
    struct message msg;
    int n;
    char line[LINESIZE];
    loop:/* forever */
    if((fdpub = open(PUBLIC, O_RDONLY)) == -1){
        perror(PUBLIC);
        exit(1);
    }
    while (read(fdpub, (char *) &msg,sizeof(msg)) > 0){
        if((fd = open(msg.filename, O_RDONLY)) == -1){
            perror(msg.filename);
            break;
        }
        if((fdpriv = open(msg.privfifo, O_WRONLY)) == -1){
            perror(msg.privfifo);
            break;
        }
        while ((n = read(fd, line, LINESIZE)) > 0)
            write(fdpriv, line, n);
        close(fd);
        close(fdpriv);
    }
    close(fdpub);
    goto loop;
}