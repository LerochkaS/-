# include "find_root.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define h 1e-10
#define max_iter 100000 
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX((MAX(a, b)), c))


double find_root (RRfunc f, double a, double b, double epsilon, NAError *err)
{
    int n = 0;
    double fa, fb;
    double x_1=0;      
    double x_2=0;      

    if ((a >= b) || (epsilon < 0) || (!f))
    {
        *err = NA_PARAM;
        printf ("Некорректные параметры входа\n");
        return 1;
    }

    fa = f(a);
    fb = f(b);

    if ((fa*fb > 0))
    {
        *err = NA_EMPTY_ROOT;
        printf ("На заданном промежутке корней нет:)\n");
        return 1;
    }

    x_1 = b;
    if (fabs(f(x_1)) < epsilon)
    {
        return x_1;
    }

    while((fabs(x_1 - x_2) > epsilon*MAX3(1, x_1, x_2)) && (n <= max_iter))
    {
        x_2 = x_1;
        x_1 -= f(x_1)/((f(x_1 + h) - f(x_2 - h))/(2*h));
        n++;
    }
   *err = NA_OK;
   if (n == max_iter)
   {
       *err = NA_ITER;
       return x_2;
   }
   return x_2;    
}