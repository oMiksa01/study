#include <stdio.h>
#include <stdlib.h>

#define REB 12
#define VER 7

struct element{
    int a;
    int b;
    int size;
}graf[REB];

struct {
    int a;
    int b;
}bad[REB];
int index_bad = 0;

struct {
    int array[100];
    struct element pair[100];
    int size;
    int variety[VER];
    int index;
    int index_pair;
}try;

struct element vers[VER - 1];

void load_GRAF();
void write_GRAF();
void reb_sort();
void swap(struct element*, struct element*);
void print_connect();
void print_ex_pair();
void alg();

int main(int argc, char const *argv[]) {

    try.index = 0;
    try.index_pair = 0;
    try.size = 0;
    for(int i = 0; i < VER; i++)
        try.variety[i] = i;

    load_GRAF();
    reb_sort();

    //for(int i = 0; i < VER; i++)
        // printf("%d -> (%d,%d)\n", graf[i].size, graf[i].a, graf[i].b);

    alg();

    printf("\nbad_reb\n");
    for(int i = 0; i < index_bad; i++) {
        printf("(%d, %d)\n", bad[i].a, bad[i].b);
    }

    return 0;
}

void reb_sort() {
    int min, index;
    for(int i = 0; i < REB - 1; i++) {
        min = graf[i].size;
        index = i;
        for(int j = i + 1; j < REB; j++)
            if(min > graf[j].size) {
                min = graf[j].size; 
                index = j;
            }
        swap(&graf[i], &graf[index]);      
    }
}

void swap(struct element* a, struct element* b) {
    struct element* temp = malloc(sizeof(struct element));
    *temp = *a;
    *a = *b;
    *b = *temp;
    free(temp);
}

void load_GRAF() {
  FILE *fd = fopen("kraskall.txt", "r");
  fread(graf, 1, sizeof(graf), fd);
  fclose(fd);
}

void write_GRAF() {
  FILE *fd = fopen("kraskall.txt", "w");
  int index = 0;
  for(int i = 0; i < REB; i++) {
    printf("A = ");
    scanf("%d", &graf[i].a);
    printf("B = ");
    scanf("%d", &graf[i].b);
    printf("SIZE = ");
    scanf("%d", &graf[i].size);
  }
  fwrite(graf, sizeof(graf), 1, fd);
  fclose(fd);
}

void alg() {
    printf("\n%d -> |-| -> | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n", 0);
    int A, B, ex_variety, new_variety;
    for(int i = 0; i < REB; i++) {
        A = graf[i].a;
        B = graf[i].b;
        if(try.variety[A - 1] != try.variety[B - 1]) {
            try.array[try.index++] = A;
            try.array[try.index++] = B;
            try.size += graf[i].size;
            try.pair[try.index_pair].a = A;
            try.pair[try.index_pair++].b = B;
            ex_variety = try.variety[B - 1];
            new_variety = try.variety[A - 1];
            for(int j = 0; j < VER; j++)
                if(try.variety[j] == ex_variety)
                    try.variety[j] = new_variety;
            print_ex_pair();
            print_connect();
        }else{
            bad[index_bad].a = A;
            bad[index_bad++].b = B;
        }
    } 
}

void print_ex_pair() {
    for(int i = 0; i < try.index_pair; i++)
        printf("(%d,%d)", try.pair[i].a, try.pair[i].b);
}

void print_connect() {
    printf("->");
    for(int i = 0; i < VER; i++) {
        printf("|");
        for(int j = 0; j < VER; j++) {
            if(i == try.variety[j]) {
                printf(" %d ", j+1);
            }
        }
        printf("|");
    }
    printf("\n");
}
