#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 0.001
#define ACC 0.0001

float max(float, float);
struct point next(struct point);
int test(struct point);
float fu(float, float);
float fu_a(float, struct point);

struct point{
    float a;
    float b;
    float res;
};

float a = 0;

int main(int argc, char const *argv[]) {
    struct point X;
    struct point X_next;
    X_next.a = 10;
    X_next.b = 10;
    X_next.res = fu(X_next.a, X_next.b);
    printf("%.3f, %.3f -> %f\n", X_next.a, X_next.b, X_next.res);
    do{
        if(test(X_next)) {
            a = fu_a(a, X_next);
            X_next.a = next(X_next).a;
            X_next.b = next(X_next).b;
            X_next.res = fu(X_next.a, X_next.b);
            printf("*X_next -> %f, %f -> %f\n", X_next.a, X_next.b, X_next.res);
        }else{
            a = 0;
            X.a = X_next.a;
            X.b = X_next.b;
            X.res = X_next.res;

            X_next.a = next(X).a;
            X_next.b = next(X).b;
            X_next.res = fu(X_next.a, X_next.b);
            printf("X_next -> %f, %f -> %f\n", X_next.a, X_next.b, X_next.res);
            printf("X -> %f, %f -> %f\n", X.a, X.b, X.res);
        }
    }while(test(X_next) || test(X) || fabs(X.res - X_next.res) > ACC);
    printf("resolt:\nX_next -> %f, %f -> %f\n", X_next.a, X_next.b, X_next.res);
    printf("X -> %f, %f -> %f\n", X.a, X.b, X.res);
    return 0;
}

float max(float a, float b) {
    if(a < b)
        return b;
    else return a;
}

struct point next(struct point temp) {
    float pr1 = -2 * temp.a + 8;
    float pr2 = -2 * temp.b + 6;
    struct point new;
    //printf("X1(%f) + L(%f) * (f`(X1)(%f) + a(%f) * 5)\n", temp.a, L, pr1, a);
    //printf("X2(%f) + L(%f) * (f`(X2)(%f) + a(%f) * 6)\n", temp.b, L, pr2, a);
    new.a = max(0, temp.a + L * (pr1 + a * 5));
    new.b = max(0, temp.b + L * (pr2 + a * 6));
    return new;
}


int test(struct point temp) {
    if(5 * temp.a + 6 * temp.b - 60 >= 0)
        return 0;
    else return 1;
}

float fu(float a, float b) {
    return -1 * ((a - 4) * (a - 4)) -1*((b - 3) * (b - 3));
}

float fu_a(float a, struct point temp) {
    return a - L * (5 * temp.a + 6 * temp.b - 60);
}