#ifndef __fn__H
#define __fn__H

#include <sys/stat.h>
#include <dirent.h>
#include <curses.h>
#include <string.h>

#define COL 34
#define ROW 22

void show_dir(WINDOW *, char*, int*);
void show_focus(WINDOW *, int, int);
void clear_focus(WINDOW *);
char* open_dir(WINDOW *, int, char*);

#endif