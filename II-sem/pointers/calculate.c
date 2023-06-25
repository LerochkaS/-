#include "calculate.h"

int calculate(RRfunc f, double *F, double *x, int n, NAError *err)
{
    *err = NA_OK;

    for(int i =0; i < n; i++)
    {
        F[i] = (*f)(x[i]);
    }

    return 0;
}