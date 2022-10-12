#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMN 4
#define ROW 6

#define good 0
#define bad 1

float equation[COLUMN][ROW];
float temp_equation[COLUMN][ROW];
int col, row, status = bad;

void Write();
void Read();
void Print();
int min_column();
int min_row(int);
void zero_row(int , int);
void devision_column(int, int);
void cp_matrix2temp();
void cp_temp2matrix();
float rectangle(int, int, int, int);
void conclusion();


int main(int argc, char const *argv[]) {
    Read();
    Print();
    while(status) {
        
        col = min_column();
        row = min_row(col);
        cp_matrix2temp();

        for(int i = 0; i < COLUMN; i++)
            if(i != col)
                for(int j = 0; j < ROW; j++)
                    if(j != row)
                        temp_equation[i][j] = rectangle(col, row, i, j);

        devision_column(col, row);
        zero_row(col, row);
        cp_temp2matrix();

        status = good;
        for(int i = 0; i < COLUMN - 1; i++)
            if(equation[i][ROW - 1] < 0)
                status = bad;
        Print();
    }
    //printf("%f - %f - %f - %f\n", equation[0][5],equation[1][5],equation[2][5],equation[3][5]);
    conclusion();
    return 0;
}

void Read() {
  FILE *fd = fopen("curs.txt", "r");
  fread(equation, 1, sizeof(equation), fd);
  fclose(fd);
}

void Write() {
  FILE *fd = fopen("curs.txt", "w");
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

int min_column() {
    int index = 0;
    float temp = equation[0][5];
    for(int i = 1; i < COLUMN - 1; i++)
        if(temp > equation[i][5]) {
            index = i;
            temp = equation[i][5];
        }
    return index;
}

int min_row(int column) {
    int index = 0;
    float temp = fabs(equation[COLUMN - 1][0] / equation[column][0]);
    for(int i = 1; i < ROW - 1; i++)
        if(temp > equation[COLUMN - 1][i] / equation[column][i]) {
            index = i;
            temp = equation[COLUMN - 1][i] / equation[column][i];
        }
    return index;
}

void zero_row(int col, int row) {
    for(int i = 0; i < COLUMN; i++) 
        temp_equation[i][row] = 0;
    temp_equation[col][row] = 1;
}

void devision_column(int col, int row) {
    for(int i = 0; i < ROW; i++) {
        temp_equation[col][i] /= equation[col][row];
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

float rectangle(int i_p, int j_p, int i, int j) {
    return equation[i][j] - (equation[i_p][j] * equation[i][j_p]) / equation[i_p][j_p];
}

void Print() {
    printf("\n    X1         X2        X3        X4       X5          R\n");
    printf("===============================================================\n");
    for(int i = 0; i < COLUMN; i++) {
        for(int j = 0; j < ROW; j++) {
            if(j == ROW - 1)
                printf("| ");
            printf("%9f ", equation[i][j]);
            if(i == COLUMN - 1 && j == ROW - 1)
                printf("<-P");
        }
        printf("\n");
    }
    printf("===============================================================\n");
}

void conclusion() {
    int col;
    for(int i = 0; i < ROW - 1; i++)
        if(equation[0][i] + equation[1][i] + equation[2][i] + equation[3][i] == 1) {
            for(int j = 0; j < COLUMN; j++) {
                if(equation[j][i] == 1)
                    col = j;
            }
            printf("\nresult:\nX%d = %.2f ", i + 1, equation[col][ROW - 1]);            
        }
        printf("\n");
}
