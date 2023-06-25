#include <stdio.h>
#include <math.h>
#include "calculate_integral.h"

double summ (RRfunc f, double a, double b, int n)
{
    double Integral = 0;
    double delta_n = (b - a) / (double)n;
    for (int i = 0; i < n; i++)
    {
        Integral += (f(a + i * delta_n) + f(a + (i + 1) * delta_n)) * delta_n / 2;
    }
    return Integral;
}

double calculate_integral(RRfunc f, double a, double b, double epsilon, NAError *err)
{
    double Integral_1 = 0;
    double Integral_2 = 0;

    if ((a > b) || epsilon < 0 || !f)
    {
        printf("Некорректные входные параметры!\n");
        *err = NA_PARAM;
        return 0;
    }
    Integral_1 = summ (f, a, b, 1000);
    for (int n = 2000; n < 100000; n = n*2)
    {
        Integral_2 = summ (f, a, b, n);
        if (fabs(Integral_1 - Integral_2) < epsilon)
        {
            *err = NA_OK;
            return Integral_2;
        }
        Integral_1 = Integral_2;
    }
    *err = NA_CONVERGE;
    return Integral_2;
}
