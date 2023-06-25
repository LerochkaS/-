#include <stdio.h>
#include <math.h>
#include "min_value.h"

#define n 1000
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX((MAX(a, b)), c))

double equal(double a, double b, double eps)
{
    if (fabs(a - b) < MAX3(1, a, b) * eps)
        return 1;
    return 0;
}

double min_value(RRfunc f, double a, double b, double eps, NAError *err)
{
    if ((a >= b) || (eps <= 0) || (!f))
    {
        *err = NA_PARAM;
        printf("!!Некорректные параметры входа!!\n");
        return 0;
    }

    double x[n + 1];
    while (fabs(b - a) > eps)
    {
        for (int i = 0; i <= n; i++)
        {
            x[i] = a + i * (b - a) / n;
        }
        for (int i = 1; i <= n; i++)
        {
            if ((equal(f(x[i - 1]), f(x[i + 1]), eps) == 1) || (f(x[i - 1]) >f(x[i]) 
            && f(x[i + 1]) > f(x[i])))
            {
                a = x[i - 1];
                b = x[i + 1];
            }
        }
    }
    *err = NA_OK;
    return f((a + b) / 2);
}