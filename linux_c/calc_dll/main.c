#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#define MAX_PLAG 10

#define EXIT 0
#define INPUT 1
#define OUTPUT 2

char *path = "./plag";//путь к плагинам
char *(*name)(int a);//прототип функции из .so
int (*fn)(int a, int b);//прототип функции из .so

struct function{
    char name[8];
    char path[56];
};

void print_plagins(struct function*, int);

int main(int argc, char const *argv[]){
    DIR *dir;
    struct dirent *de;
    struct function fn_form_plag[MAX_PLAG];
    void *ext_library;//указатель на функцию в .so
    int run = INPUT;
    int index;
    int num_plag = 0;//число плагинов
    int counter = 0;
    
    dir = opendir(path);
    if(!dir){
        perror("diropen");
        exit(1);
    }

    while((de = readdir(dir))&&(num_plag <= MAX_PLAG)){
        //пропускаем .. и .
        if( ( strcmp(de->d_name, ".") == 0 ) || ( strcmp(de->d_name, "..") == 0 ) ){
            de = readdir(dir);
        }
        //заполняем новые пути к плагинам
        strcpy(fn_form_plag[num_plag].path, path);
        strcat(fn_form_plag[num_plag].path, "/");
        strcat(fn_form_plag[num_plag].path, de->d_name);
        num_plag++;
    }
    
    while(counter < num_plag){
        ext_library = dlopen(fn_form_plag[counter].path, RTLD_LAZY);
        if(!ext_library){
          fprintf(stderr,"dlopen() error: %s\n", dlerror());
	      exit(1);
        }
        name = dlsym(ext_library, "fn_name");
        strcpy(fn_form_plag[counter].name, (*name)(1));
        dlclose(ext_library);
        counter++;
    }
 
    
    while(run){
        if(run == INPUT){
            print_plagins(fn_form_plag, num_plag);
            scanf("%d", &index);
            index--;
            if(index == num_plag) run = EXIT;
            if((index >= 0)&&(index < num_plag))run = OUTPUT;
        }

        if(run == OUTPUT){
            int first, second;
            printf("in first number ");
            scanf("%d", &first);
            printf("in second number ");
            scanf("%d", &second);
            ext_library = dlopen(fn_form_plag[index].path, RTLD_LAZY);
            if(!ext_library){
                fprintf(stderr,"dlopen() error: %s\n", dlerror());
	            exit(1);
            }
            fn = dlsym(ext_library, fn_form_plag[index].name);
            printf("result = %d\n\n",(*fn)(first, second));
            dlclose(ext_library);
            run = INPUT;
        }
    }
    return 0;
}

void print_plagins(struct function *fn, int num_plag){
    for(int i = 0; i < num_plag; i ++)
        printf("%d)%s\n", i+1, fn[i].name);
    printf("%d)exit\n?.", num_plag+1);
}
