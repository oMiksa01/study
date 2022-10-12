#include "fn.h"

void show_dir(WINDOW *win, char *path, int *last){
    DIR *dir;
    struct dirent *de;
    int y, x;

    if((dir = opendir(path)) == NULL){
        wprintw(win, "wrong way to dir!");
        wrefresh(win);
    }
    
    wclear(win);

    while(de = readdir(dir)){
        getyx(win, y, x);
        if(y == (ROW - 1)){
            wmove(win, 0, 1);
            wclear(win);
        }
        wprintw(win, " %s\n", de->d_name);
    }
    *last = y;
    wrefresh(win);
    closedir(dir);
}

void show_focus(WINDOW *win, int index, int max){
    for(int i = 0; i <= max; i++)
    {
        wmove(win, i, 0);
        if(i == index)
            wprintw(win, ">");
    }
}

void clear_focus(WINDOW *win){
    for(int i = 0; i < COL; i++)
    {
        wmove(win, i, 0);
        wprintw(win, " ");
    }
    wrefresh(win);
}

char* open_dir(WINDOW *win, int index, char *path){
    struct stat st;
    char path_add[ROW], path_new[256];
    int x;
    for(x = 0; x < ROW - 2; x++){
        path_add[x] = mvwinch(win, index, x+1) & A_CHARTEXT;
        if((int)path_add[x] == 32){
            path_add[x] = '\0';
            break;
        }
    }
	
    (void)strcpy(path_new, path);
    (void)strcat(path_new, "/");
    (void)strcat(path_new, path_add);

    lstat(path_new, &st);
    
    if(S_ISDIR(st.st_mode)){
        /* directory */
        strcpy(path, path_new);
    }
    if(S_ISREG(st.st_mode)){
        /* regular file */
    }
    if(S_ISLNK(st.st_mode)){
        /* symbolic link */
    }
    if(S_ISFIFO(st.st_mode)){
        /* pipe or FIFO */
    }
    if(S_ISCHR(st.st_mode)){
        /* char file */
    }
    if(S_ISBLK(st.st_mode)){
        /* bloсk file */
    } 
    return path;
}