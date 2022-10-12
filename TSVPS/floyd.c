#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTICES 5
#define MAX_LONG 16

#define LOOP 0
#define INFINITY 99

void filling(int[][VERTICES]);
void print(int [][VERTICES]);
void alg(int[][VERTICES], int[][VERTICES]);

int main(int argc, char const *argv[]) {
  int graf[VERTICES][VERTICES];
  int path[VERTICES][VERTICES];

    filling(graf);
    printf("graf\n");
    print(graf);
    alg(graf, path);
    printf("matrix short path\n");
    print(graf);
    printf("path\n");
    print(path);

  return 0;
}

void filling(int arr[][VERTICES]) {
    srand(time(NULL));
    int temp;
    for(int i = 0; i < VERTICES; i++) {
        for(int j = 0; j < VERTICES; j++) {
            if(i == j)
                arr[i][j] = LOOP;
            else{
                temp = rand() % MAX_LONG;
            if(!temp)
                arr[i][j] = arr[j][i] = INFINITY;
            else arr[i][j] = arr[j][i] = temp;
            }
        }
    }
}

void print(int graf[][VERTICES]) {
  for (int i = 0; i < VERTICES; i++) {
    for (int j = 0; j < VERTICES; j++)
      printf("%5d ", graf[i][j]);
    printf("\n");
  }
  printf("\n");
}

void alg(int graf[][VERTICES], int path[][VERTICES]) {
    for(int i = 0; i < VERTICES; i++)
        for(int j = 0; j < VERTICES; j++) {
            path[i][j] = 0;
            for(int k = 0; k < VERTICES; k++) 
                    if(graf[i][k] + graf[k][j] < graf[i][j]) {
                        graf[i][j] = graf[i][k] + graf[k][j];
                        path[i][j] = k + 1;
                    }
        }
}
