#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTICES 5
#define MAX_LONG 16

#define BEGIN 0
#define END 2

#define LOOP 0
#define INFINITY 100000


struct element{
    int x, y, t;
}ver[VERTICES * VERTICES];

int filling();
void alg();
int write_GRAF();
void load_GRAF();


int main(int argc, char const *argv[]) {
    //printf("\n%d\n", Write());
    load_GRAF();
    alg();

    return 0;
}

void load_GRAF() {
  FILE *fd = fopen("bellman.txt", "r");
  fread(ver, 1, sizeof(ver), fd);
  fclose(fd);
}

int write_GRAF() {
  FILE *fd = fopen("bellman.txt", "w");
  int index = 0;
  for(int i = 0; i < VERTICES; i++)
    for(int j = 0; j < VERTICES; j++) {
      if(1){
        printf("%d - %d", i, j);
        ver[index].x = i;
        ver[index].y = j;
        scanf("%d", &ver[index].t);
        index++;
      }
    }
    fwrite(ver, sizeof(ver), 1, fd);
    fclose(fd);
    return index - 1;
}

int filling() {
    srand(time(NULL));
    int temp, index = 0;
    for(int i = 0; i < VERTICES; i++) {
        for(int j = 0; j < VERTICES; j++) {
            if(i != j) {
                ver[index].x = i;
                ver[index].y = j;
                temp = rand() % MAX_LONG;
            if(!temp){
                ver[index++].t = INFINITY;
                printf("%3d ", 0);
            }else {
                ver[index++].t = temp;
                printf("%3d ", temp);
                }
            }else printf("%3d ", 0);
        }
        printf("\n");
    }
    return index;
}

void alg() {
    int size = VERTICES * VERTICES;
    int weight[1000];
    int path[VERTICES];

    for(int i = 0; i < VERTICES; i++) 
        weight[i] = INFINITY;
    weight[BEGIN] = LOOP;

    for(int i = 0; i < VERTICES - 1; i++)
        for(int j = 0; j < size; j++)
            if(weight[ver[j].x] + ver[j].t < weight[ver[j].y]) {
                weight[ver[j].y] = weight[ver[j].x] + ver[j].t;
                path[ver[j].y] = ver[j].x;
            }
    
    printf("Short_path");
    for(int i = 0; i < VERTICES; i++)
        if(weight[i] == INFINITY)
            printf("\n%d -> %d = Not", BEGIN, i);
        else printf("\n%d -> %d = %d", BEGIN, i, weight[i]);
    printf("\n");

    int index = path[END];
    int temp;
    printf("Path\n%d", END);
    for(int i = 0; temp != index; i++) {
        printf("<-%d",index);
        temp = index;
        index = path[index];
    }printf("\n");
}

