#include <stdio.h>
#include <math.h>
#include "my_exp.h"

double my_exp(double x, double eps, NAError *err)
{
    if (eps <= 0.0)
    {
        *err = NA_PARAM;
        return 1;
    }

    double n = 0;
    double h, summ = 1;
    int i = 2;
    h = x;

    while ((fabs(h) > eps) && (n <= 100000))
    {
        if (n == 100000)
        {
            *err = NA_ITER;
            return summ;
        }
        summ += h;
        h *= x / i;
        i++;
        n++;
    }
    *err = NA_OK;
    return summ;
}