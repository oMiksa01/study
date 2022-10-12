#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "fn.h"

int main(int argc, char ** argv){
    WINDOW *wnd;
    WINDOW *wnd_txt;
    MEVENT event;

    FILE *fd;
    char path[256] = {};
    
    char ch;
    int RUN = 1, y, x;
    
    initscr();

    start_color();
    init_pair(1, COLOR_RED, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
   
    wnd = newwin(24, 80, 0, 0);
    wbkgd(wnd, COLOR_PAIR(1));
    wmove(wnd, 23, 15);
    wprintw(wnd, "OPEN");
    wmove(wnd, 23, 40);
    wprintw(wnd, "SAVE");
    wmove(wnd, 23, 65);
    wprintw(wnd, "EXIT");
    wrefresh(wnd);

    wnd_txt = derwin(wnd, ROW, COL, 1, 1);
    wbkgd(wnd_txt, COLOR_PAIR(2));
    wrefresh(wnd_txt);

    //open file for terminal
    if(argc == 2){
        strcpy(path, argv[1]);
        fd = fopen(path, "r");
        read_to_win(wnd_txt, fd);
        fclose(fd);
    }

    keypad(wnd_txt, true);
    mousemask(BUTTON1_CLICKED, NULL);

    while(RUN){
        getyx(wnd_txt, y, x);
        if((y == (ROW-1))&&(x == (COL-1))) 
            wmove(wnd_txt, 0, 0);

        ch = wgetch(wnd_txt);

        move_in_win(wnd_txt, y, x, ch);
        
        //work with mouse
        getmouse(&event);
        RUN = mouse_click(wnd_txt, path, button_OSE(event.y, event.x));        
    }

    delwin(wnd_txt);
    delwin(wnd);

    endwin();
    exit(EXIT_SUCCESS);
    return 0;
}
