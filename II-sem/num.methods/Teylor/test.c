#include <stdio.h>
#include <math.h>
#include "my_exp.h"

#define EPS 1e-8

int main()
{

    NAError error;

    typedef struct
    {
        double x;
        double eps;
        NAError err;
        double true_value;
    } Test;
    Test tests[8] = {{1, EPS, NA_OK, exp(1)},
                     {1e-3, EPS, NA_OK, exp(1e-3)},
                     {0, EPS, NA_OK, exp(0)},
                     {65, EPS, NA_OK, exp(65)},
                     {-10, EPS, NA_OK, exp(-10)},
                     {1, 0.0, NA_PARAM, 1.0},
                     {-40, EPS, NA_OK, exp(-40)},
                     {10, EPS, NA_OK, exp(10)}};

    double value;

    for (int i = 0; i < 8; i++)
    {
        printf("\n");
        printf("Test № %d\n", i + 1);
        value = my_exp(tests[i].x, tests[i].eps, &error);
        printf("Код ошибки: %d   Ожидалось: %d\n", error, tests[i].err);
        printf("Возвращенное значние = %lf\n", value);
        printf("Истинное значение = %lf\n", tests[i].true_value);
        printf("Погрешность = %lf", fabs(value - tests[i].true_value));
        printf("\n");
    }
    return 0;
}
