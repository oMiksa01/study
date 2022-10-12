#include <stdio.h>
#include "show.h"
#include "libcalc.h"

void show(){
    short index;
    short run = INPUT;
    while(run){
        if(run == INPUT){
            print_menu();

            index = cmd();
            if(index) run = OUTPUT;
        }

        if(run == OUTPUT){
            switch(index){
                case 1:  
                    operation(add);
                    run = INPUT;
                    break;
                case 2: 
                    operation(ded);
                    run = INPUT;
                    break;
                case 3: 
                    operation(mult);
                    run = INPUT;
                    break;
                case 4: 
                    operation(div);
                    run = INPUT;
                    break;
                case 5:
                    printf("bye\n"); 
                    run = EXIT; 
                    break;
                default: 
                    printf("wrong choice\n\n"); 
                    break;
            }
        }
    }
}

void print_menu(){
    printf("1)add\n");
    printf("2)ded\n");
    printf("3)mult\n");
    printf("4)div\n");
    printf("5)exit\n");
    printf("?.");
}

short cmd(){
    short cmd;
    scanf("%d", &cmd);
    if((cmd > 0)&&(cmd < 6))
        return cmd;
    else return 0;    
}

void operation(int (*fn)(int, int)){
    int first, second;
    printf("in first number ");
    scanf("%d", &first);
    printf("in second number ");
    scanf("%d", &second);
    printf("result = %d\n\n",fn(first, second));
}
