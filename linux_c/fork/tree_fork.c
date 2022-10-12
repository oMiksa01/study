#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void show(int index){
    printf(" (%d): PID(%d) -- PPID(%d)\n", index, getpid(), getppid());
}

int main(){
    if(!fork()){
        if(!fork()){
            show(3);
        }else{
            show(1);
        }
    }else{
        wait(NULL);
        if(!fork()){
            if(!fork()){
                show(4);
            }else{
                if(!fork()){
                    show(5);
                }else{
                    wait(NULL);
                    show(2);
                }
            }
        }else{
            wait(NULL);
            show(0);
        }
    }
}
