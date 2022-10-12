#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTICES 5
#define MAX_LONG 16

#define BEGIN 4
#define END 1

#define PASS 0
#define POTEN 1

#define LOOP 0
#define INFINITY 99

void Write();
void filling_txt(int[][VERTICES]);
void filling(int[][VERTICES]);
void pring_graf(int [][VERTICES]);
void init(int[], int[]);
void alg(int[][VERTICES], int[], int[]);
void print_size(int[]);
void restor_path(int[][VERTICES], int[], int[]);
void print_path(int[], int);

int main(int argc, char const *argv[]) {
  int graf[VERTICES][VERTICES];
  int size[VERTICES];
  int ver[VERTICES];
  int path[VERTICES];

  filling_txt(graf);
  pring_graf(graf);

  init(ver, size);
  alg(graf, ver, size);
  //print_size(size);
  restor_path(graf, size, path);

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

void pring_graf(int graf[][VERTICES]) {
  printf("Graf\n");
  for (int i = 0; i < VERTICES; i++) {
    for (int j = 0; j < VERTICES; j++)
      printf("%5d ", graf[i][j]);
    printf("\n");
  }
  printf("\n");
}

void init(int ver[], int size[]) {
  for(int i = 0; i < VERTICES; i++) {
    size[i] = INFINITY;
    ver[i] = POTEN;
  }
  size[BEGIN] = LOOP;
}

void alg(int graf[][VERTICES], int ver[], int size[]) {
  int min_index, min_size;
  do {
    min_index = INFINITY;
    min_size = INFINITY;
    for (int i = 0; i < VERTICES; i++) { 
      if ((ver[i] == POTEN) && (size[i] < min_size)) {
        min_size = size[i];
        min_index = i;
      }
    }
    if (min_index != INFINITY) {
      for (int i = 0; i < VERTICES; i++) {
        if (graf[i][min_index] > 0) {
          int temp = min_size + graf[i][min_index];
          if (temp < size[i])
            size[i] = temp;
        }
      }
      ver[min_index] = PASS;
    }
    print_size(size);
  } while (min_index < INFINITY);
}

void print_size(int size[]) {
  static int num, ex_size[VERTICES][VERTICES];
  for(int i = 0; i < VERTICES; i++) {
    ex_size[num][i] = size[i];
  }
  num++;
  if(num == VERTICES){
    for(int i = VERTICES - 2; i >= 0; i--) {
      for(int j = 0; j < VERTICES; j++) {
        if(ex_size[i + 1][j] == ex_size[i][j])
          ex_size[i + 1][j] = -1;
      }
    }

    for(int i = 0; i < VERTICES; i++) {
      for(int j = 0; j < VERTICES; j++) {
        if(ex_size[i][j] == -1)
          printf("%5c",'-');
        else printf("%5d",ex_size[i][j]);
      }
      printf("\n");
    }
  }
}


void restor_path(int graf[][VERTICES], int size[], int path[]) {
  int begin = BEGIN;
  int end = END;
  int weight = size[end];
  int index = 0;
  path[index++] = end;

  while (begin > end) {
    for(int i = 0; i < VERTICES; i++)
      if (graf[i][end] != 0) {
        int temp = weight - graf[i][end];
        if (temp == size[i]) {
          weight = temp;
          end = i;
          path[index++] = i;
        }
      }
  }
  print_path(path, index);
}

void print_path(int path[], int size) {
  printf("path of vertices\n");
  printf("%5d --", BEGIN);
  for (int i = size - 2; i >= 0; i--)
    printf("%d-", path[i]);
  printf("-> %d\n\n", END);
}

void filling_txt(int arr[][VERTICES]) {
  FILE *fd = fopen("dejkstra.txt", "r");
  int qwe[VERTICES][VERTICES];
  fread(arr, 1, sizeof(qwe), fd);
  fclose(fd);
}

void Write() {
  FILE *fd = fopen("gejkstra.txt", "w");
  int num[VERTICES][VERTICES];
  for(int i = 0; i < VERTICES; i++)
    for(int j = 0; j < VERTICES; j++) {
      printf("%d - %d", i, j);
      scanf("%d", &num[i][j]);
    }
    fwrite(num, sizeof(num), 1, fd);
    fclose(fd);
}