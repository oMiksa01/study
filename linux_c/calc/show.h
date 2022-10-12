#ifndef __show__H
#define __show__H

#define EXIT 0
#define INPUT 1
#define OUTPUT 2

void show();
void print_menu();
short cmd();
void operation(int (*fn)(int, int));

#endif