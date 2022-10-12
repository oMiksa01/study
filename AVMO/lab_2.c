#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define ACCURACY 10000

#define V 10.2857
#define B_P1 0.8571 
#define B_P2 0.1429
#define A_P1 0.6429
#define A_P2 0.3571

float roat_A[SIZE];
float roat_B[SIZE];

int matrix[2][2] = {{11, 6}, {9, 18}};

void roat_rand();
void game();

int main(int argc, char const *argv[]) {
    roat_rand();
    game();
    
    return 0;
}

void roat_rand() {
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++)
        roat_A[i] = (float)rand() / RAND_MAX;
    for(int i = 0; i < SIZE; i++)
        roat_B[i] = (float)rand() / RAND_MAX;
}

void game() {
    int tactic_A, tactic_B, proc_A = 0, proc_B = 0;
    float prize, sum_prize = 0; 
    printf(" NUM - rand_A - tactic_A - rand_B - tactic_B - prize - sum_prize - mid_prize\n");
    for(int i = 0; i < SIZE; i++) {
        if(roat_A[i] <= A_P1) {
            tactic_A = 0;
            proc_A++;
        }else tactic_A = 1;
        if(roat_B[i] <= B_P1) {
            tactic_B = 0;
            proc_B++;
        }else tactic_B = 1;
        prize = matrix[tactic_A][tactic_B];
        sum_prize += prize;
        printf("%3d -  %.4f - %8d - %.4f - %8d - %5.0f - %9.0f - %9.2f\n", i + 1, roat_A[i], tactic_A + 1,\
         roat_B[i], tactic_B + 1, prize, sum_prize, sum_prize / (i + 1));
    }
    printf("A1 = %d, A2 = %d, B1 = %d, B2 = %d\n", proc_A, SIZE - proc_A, proc_B, SIZE - proc_B);
    float p1 = (float)proc_A / SIZE, p2 = (SIZE - (float)proc_A)/SIZE, q1 = (float)proc_B / SIZE, q2 = (SIZE - (float)proc_B)/SIZE;
    printf("dano:\np -> (%.4f, %.4f)\nq -> (%.4f, %.4f)\n", A_P1, A_P2, B_P1, B_P2);
    printf("result:\np -> (%.4f, %.4f)\nq -> (%.4f, %.4f)\n", p1, p2, q1, q2);
}