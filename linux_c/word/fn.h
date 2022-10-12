#ifndef __fn__H
#define __fn__H

#define MISS 0
#define OPEN 1
#define SAVE 2
#define EXIT 3

#define ROW 22
#define COL 78

void move_in_win(WINDOW *, int, int, char);
void read_to_win(WINDOW *, FILE *);
int button_OSE(int, int);
int mouse_click(WINDOW *, char *, int);

#endif