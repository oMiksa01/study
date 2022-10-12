#include <stdlib.h>
#include <curses.h>
#include "fn.h"


void move_in_win(WINDOW *win, int y, int x, char step){
    switch ((int)step){   
        case 4:
        //case KEY_LEFT:
            if(x == 0)
                if(y == 0)
                    wmove(win, ROW - 1, COL - 1);
                else wmove(win, y - 1, COL - 1);
            else wmove(win, y, x-1);
            break;
        case 5:
        //case KEY_RIGHT:
            if(x == COL - 1)
                if(y == ROW - 1)
                    wmove(win, 0, 0);
                else wmove(win, y + 1, 0);
            else wmove(win, y, x + 1);
            break;
        case 3:
        //case KEY_UP:
            if(y == 0)
                wmove(win, ROW - 1, x);
            else wmove(win, y - 1, x);
            break;
        case 2:
        //case KEY_DOWN:
            if(y == ROW - 1)
                wmove(win, 0, x);
            else wmove(win, y + 1, x);
            break;
        case 10:
        //case KEY_ENTER:
            if(y == (ROW-1))
                wmove(win, 0, 0);
            else wmove(win, y + 1, 0);
            break;
        default:
            break;
    }
}

void read_to_win(WINDOW * win, FILE *fd){
    if(fd){
        char buff[77];
        int y, x;
    
        wmove(win, 0, 0);
    
        while(fgets(buff, (COL-1), fd) != NULL){
            wprintw(win, "%s", buff);
            
            getyx(win, y, x);
            if(y == (ROW-1)){
                //wclear(win);
                wmove(win, 0, 0);
            }//else wmove(win, y + 1, 0);
        }
        wrefresh(win);
    }
}

int button_OSE(int y, int x){
    if(y == (ROW+1)){
        if((x > 14)&&(x < 19)) return OPEN;
        if((x > 39)&&(x < 44)) return SAVE;
        if((x > 64)&&(x < 69)) return EXIT;
    }
    return MISS;
}

int mouse_click(WINDOW *win, char *path, int target){
    FILE *fd;
    char ch;
    int RUN, y, x;
    getyx(win, y, x);
    
    switch (target){
        case OPEN:
            wclear(win);
            wprintw(win, "in path to file: ");
            
            int i = 0;
            while((ch = wgetch(win)) != 10){
                path[i] = ch;
                i++;
            }
            
            if((fd = fopen(path, "r")) == NULL){
                wclear(win);
                wprintw(win, "fail!\n wrong path: %s", path);
            }else{
                wclear(win);
                read_to_win(win, fd);
                fclose(fd);
            }
            RUN = 1;
            break;
        case SAVE:
            fd = fopen (path, "w");
            if(fd){    
                for(int y = 0; y < ROW - 1; y++){
                    for(int x = 0; x < COL - 1; x++)
                        putc (mvwinch (win, y, x) & A_CHARTEXT, fd);
                    putc('\n', fd);
                }
                fclose(fd);
                wmove(win, 0, 0);
            }else{
                wmove(win, 0, 0);
                wprintw(win, "fail!\nyou didn`t open file!");
            }
            RUN = 1;
            break;
        case EXIT:
            RUN = 0;
            break;
        default:
            RUN = 1;
            break;
    }
    return RUN;
}