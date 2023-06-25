#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "find_root.h"

#define EPS 1e-8

double f1(double x) { return (x * x - 6); }
double f2(double x) { return (exp(x) - 5); }
double f3(double x) { return (sin(x)); }
double f4(double x) { return (x/(1e-5) - 5); }
double f5(double x) { return (x/(1e4) - 1); }

int main()
{
    NAError err;

    typedef struct
    {
        RRfunc f;
        double a, b;
        NAError err;
        double eps;
        double root;
    } Test;
    Test tests[8] = {{f1,   0,     3,     NA_OK,         EPS, 2.45},
                     {NULL, -5,    0,     NA_PARAM,      EPS, 0},
                     {f1,   9,     1,     NA_PARAM,      EPS, 0},
                     {f2,   0,     10,    NA_OK,         EPS, 1.609},
                     {f2,   100,   200,   NA_EMPTY_ROOT, EPS, 0},
                     {f3,   -0.33, 0.33,  NA_OK,         EPS, 0},
                     {f4,   -100,  100,   NA_OK,         EPS, 0.00005},
                     {f5,   0,     1e6,   NA_OK,         EPS, 1e4}};

    double value;

    for (int i = 0; i < 8; i++)
    {
        printf("Test № %d\n", i + 1);
        value = find_root(tests[i].f, tests[i].a, tests[i].b, EPS, &err);
        printf("Возвращенное значение = %lf\n", value);
        printf("Код ошибки: %d  Ожидалось: %d\n", err, tests[i].err);
        printf("Корень на отрезке = %lf\n", tests[i].root);
        printf("\n");
    }
    return 0;
}
