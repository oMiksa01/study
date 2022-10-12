#include <curses.h>
#include <string.h>
#include "fn.h"

int main(int argc, char const *argv[]){
    WINDOW *wnd;
    WINDOW *win[2];

    char ch, path[2][256];
    int RUN = 1, focus = 0, y, x;
    int point_row[2] = {0, 0}, last_row[2] = {0, 0};

    if(argc == 3){
        strcpy(path[0], argv[1]);
        strcpy(path[1], argv[2]);
    }else{
        strcpy(path[0], "/");
        strcpy(path[1], ".");
    }

    initscr();
    noecho();
    curs_set(false);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    wnd = newwin(24, 80, 0, 0);
    wbkgd(wnd, COLOR_PAIR(1));

    for(int i = 0; i < 2; i++){
        win[i] = derwin(wnd, ROW, COL, 1, 3 + i*39);
        wbkgd(win[i], COLOR_PAIR(2));
        wrefresh(win[i]);

        keypad(win[i], true);

        show_dir(win[i], path[i], &last_row[i]);
    }

    while(RUN){
        show_focus(win[focus], point_row[focus], last_row[focus]);

        ch = wgetch(win[focus]);
        getyx(win[focus], y, x);

        clear_focus(win[focus]);

        switch (ch){
            case 10:
                strcpy(path[focus], open_dir(win[focus], point_row[focus], path[focus]));
                show_dir(win[focus], path[focus], &last_row[focus]);
                point_row[focus] = 0;
                break;
            case 3:
                if(point_row[focus] == 0)
                    point_row[focus] = last_row[focus];
                else point_row[focus]--;
                break;
            case 2:
                if(point_row[focus] == last_row[focus])
                    point_row[focus] = 0;
                else point_row[focus]++;
                break;
            case 4:
                focus = 0;
                break;
            case 5:
                focus = 1;
                break;
            default:
                break;
        }
    }

    delwin(win[0]);
    delwin(win[1]);
    delwin(wnd);

    endwin();
    return 0;
}
