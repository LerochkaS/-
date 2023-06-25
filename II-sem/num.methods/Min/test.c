#include <stdio.h>
#include <math.h>
#include "min_value.h"

#define EPS 1e-8

double f1(double x) { return x*x; }
double f2(double x) { return (x*x*x + 10*x*x -5); }
double f3(double x) { return (sin(x)); }
double f4(double x) { return (0*x + 12); }

int main()
{
    NAError err;

    typedef struct
    {
        RRfunc f;
        double a, b;
        NAError err;
        double eps;
        double min;
    } Test;
    Test tests[8] = {{f1,   -10,    5,      NA_OK,         EPS, 0},
                     {NULL, -5,     0,      NA_PARAM,      EPS, 0},
                     {f1,   -5,     12,     NA_PARAM,      -9,  0},
                     {f2,   -5,     40,     NA_OK,         EPS, -5},
                     {f2,   -5,     500,    NA_OK,         EPS, -5},
                     {f3,   -2,     0,      NA_OK,         EPS, -1},
                     {f4,   -1e25,  1e50,   NA_OK,         EPS, 12},
                     {f4,   1e5,    1e6,    NA_OK,         EPS, 12}};

    double value;

    for (int i = 0; i < 7; i++)
    {
        printf("Test № %d\n", i + 1);
        value = min_value(tests[i].f, tests[i].a, tests[i].b, tests[i].eps, &err);
        printf("Возвращенное значение = %lf\n", value);
        printf("Код ошибки: %d  Ожидалось: %d\n", err, tests[i].err);
        printf("Минимальное значение = %lf\n", tests[i].min);
        printf("\n");
    }
    return 0;
}