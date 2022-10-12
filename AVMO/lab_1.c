#include <stdio.h>
#include <stdlib.h>

#define ROW 6
#define COLUMN 5

float equation[COLUMN][ROW];
float temp_equation[COLUMN][ROW];

void Read();
void Write();
void Print();
void swap_row(int, int, int);
int max_column(int);
float rectangle(int, int, int);
void zero_column(int);
void devision_row(int);
void cp_matrix2temp();
void cp_temp2matrix();


int main(int argc, char const *argv[]) {
    int max;
    Read();
    Print();
    for(int position = 0; position < ROW - 1; position++) {
        max = max_column(position);
        swap_row(position, max, position);
        
        cp_matrix2temp();

        for(int i = 0; i < COLUMN; i++)
            if(i != position)
                for(int j = position + 1; j< ROW; j++) {
                    temp_equation[i][j] = rectangle(position, i, j);
                }

        cp_temp2matrix();
        devision_row(position);
        zero_column(position);
        Print();
    } 
    return 0;
}

void Read() {
  FILE *fd = fopen("lab1.txt", "r");
  fread(equation, 1, sizeof(equation), fd);
  fclose(fd);
}

void Write() {
  FILE *fd = fopen("lab1.txt", "w");
  for(int i = 0; i < COLUMN; i++)
    for(int j = 0; j < ROW; j++) {
        if(j == ROW - 1)
            printf("%d equation result = ", i + 1);
        else printf("%d equation X%d = ", i + 1, j + 1);
        scanf("%f", &equation[i][j]);
    }
    fwrite(equation, sizeof(equation), 1, fd);
    fclose(fd);
}

void Print() {
    printf("\n==============================================================\n");
    for(int i = 0; i < COLUMN; i++) {
        for(int j = 0; j < ROW; j++) {
            if(j == ROW - 1)
                printf("| ");
            printf("%9f ", equation[i][j]);
        }
        printf("\n");
    }
    printf("==============================================================\n");
}

void swap_row(int position, int a, int b) {
    float temp;
    for(int i = position; i < ROW; i++) {
        temp = equation[a][i];
        equation[a][i] = equation[b][i];
        equation[b][i] = temp;
    }
}

int max_column(int row) {
    int max = abs(equation[0][row]);
    int index = 0;
    for(int i = 1; i < COLUMN; i++) {
        if(max < abs(equation[i][row])) {
            max = abs(equation[i][row]);
            index = i;
        }
    }
    return index;
}

float rectangle(int position, int i, int j) {
    return equation[i][j] - (equation[position][j] * equation[i][position]) / equation[position][position];
}

void zero_column(int position) {
    for(int i = 0; i < COLUMN; i++) 
        equation[i][position] = 0;
    equation[position][position] = 1;
}

void devision_row(int position) {
    for(int i = position + 1; i < ROW; i++) {
        equation[position][i] /= equation[position][position];
    }
}

void cp_matrix2temp() {
    for(int i = 0; i < COLUMN; i++) 
        for(int j = 0; j < ROW; j++)
            temp_equation[i][j] = equation[i][j];
}

void cp_temp2matrix() {
    for(int i = 0; i < COLUMN; i++) 
        for(int j = 0; j < ROW; j++)
            equation[i][j] = temp_equation[i][j];
}