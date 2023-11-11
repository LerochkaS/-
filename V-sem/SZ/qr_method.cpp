#include "qr_method.h"
#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <stdlib.h>
using namespace std;

int qr_decomposition(int r, int n, double A[], double d1[], double d2[], int var)
{
  double val1 = 0, val2 = 0, k = 0;
  for (int i = 0; i < r - 1; i++)
  {
    val2 = A[(i + 1) * n + i];
    k = val2 * val2;
    val1 = A[i * n + i] - sqrt(fabs(A[i * n + i] * A[i * n + i] + k));
 
    k += val1 * val1;
    k = sqrt(fabs(k));

    if ((var==2)&&(k < 1e-10)) k += 1e-10;
    val1 /= k;
    val2 /= k;
    d1[i] = val1;
    d2[i] = val2;
    for (int j = i; j < r; j++)
    {
      k = val1 * A[i * n + j] + val2 * A[(i + 1) * n + j];
  
      A[i * n + j] -= 2 * val1 * k;
 
      A[(i + 1) * n + j] -= 2 * val2 * k;
    
    }

  }

  for (int i = 0; i < r - 1; i++)
    for (int j = 0; j < min(i + 2, r); j++)
    {
      val2 = d1[i] * A[j * n + i] + d2[i] * A[j * n + i + 1];
      A[j * n + i] -= 2* d1[i] * val2;
      A[j * n + i + 1] -= 2 * d2[i] * val2;
    }
  return 0;
}


int qr_method(int n, double A[], double x[], double d1[], double d2[], double eps, int var)
{
  double val1 = 0, val2 = 0, val = 0, r1, r2, temp = 0;
  int c = 0;
  if ((var == 2)&&(eps < 1e-8))
      eps = 1e-8;
  for (int i = 1; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
        temp = sqrt(A[i * n + i - 1] * A[i * n + i - 1] + A[j * n + i - 1] * A[j * n + i - 1]);
        if ((A[i * n + i - 1] == 0) && (A[j * n + i - 1] == 0)) {
            val1 = 1;
            val2 = 0;
        }
        else {
            val1 = A[i * n + i - 1] / temp;
            val2 = -A[j * n + i - 1] / temp;
        }

        if (abs(val2) < abs(val1)) {
            if (val1 > 0)
                val1 = sqrt(1 - val2 * val2);
            else
                val1 = -sqrt(1 - val2 * val2);
        }
        else if (val2 > 0)
            val2 = sqrt(1 - val1 * val1);
        else
            val2 = -sqrt(1 - val1 * val1);
        A[i * n + i - 1] = temp;
        for (int k = i; k < n; k++)
        {
            val = val1 * A[i * n + k] - val2 * A[j * n + k];
            A[j * n + k] = val2 * A[i * n + k] + val1 * A[j * n + k];
            A[i * n + k] = val;
        }
        A[j * n + i - 1] = 0;

        for (int k = i - 1; k < n; k++)
        {
            val = val1 * A[k * n + i] - val2 * A[k * n + j];
            A[k * n + j] = val2 * A[k * n + i] + val1 * A[k * n + j];
            A[k * n + i] = val;
        }
    }

  val = 0;
  for (int i = 0; i < n; i++)
    for (int j = i - 1; j < n; j++)
      val += A[i * n + j] * A[i * n + j];
  //val = sqrt(val);
  val1 = 0;
  val2 = 0;

  temp = 1000;
  if (var == 2) temp = 5000;

  for (int r = n; r > 2; r--)
  {
    while ((abs(A[(r - 1) * n + r - 2]) * abs(A[(r - 1) * n + r - 2]) > val * eps * eps) && (c<temp))
    {
      val2 = (A[(r - 2) * n + r - 2] + A[(r - 1) * n + r - 1]) * (A[(r - 2) * n + r - 2] + A[(r - 1) * n + r - 1]) - 4 * (A[(r - 2) * n + r - 2] * A[(r - 1) * n + r - 1] - A[(r - 2) * n + r - 1] * A[(r - 1) * n + r - 2]);
      if ((c % 2 == 0) && (val2 > 1e-15))
      {
        val2 = sqrt(val2)/2;
        r1 = A[(r - 2) * n + r - 2] + val2;
        r2 = A[(r - 2) * n + r - 2] - val2;
        //r1 /= 2;
        //r2 /= 2;
        if (abs(r1) > abs(r2))
          val1 = r1;
        else
          val1 = r2;
      }
      else
      {
        val1 = A[(r - 1) * n + r - 1];
      }
      
        /*if (val1 * val1 <= val * eps * eps)
            val1 += 1;*/

      for (int i = 0; i < r; i++)
        A[i * n + i] -= val1;
      qr_decomposition(r, n, A, d1, d2, var);
    
      for (int i = 0; i < r; i++)
        A[i * n + i] += val1;
      c++;
    }
    x[r - 1] = A[(r - 1) * n + r - 1];
  }

  val2 = (A[0] + A[n + 1]) * (A[0] + A[n + 1]) - 4 * (A[0] * A[n + 1] - A[1] * A[n]);
  if (val2 > eps)
  {
    x[0] = (A[0] + A[n + 1] - sqrt(val2)) / 2;
    x[1] = (A[0] + A[n + 1] + sqrt(val2)) / 2;
  }
  else if (val2 < -eps)
  {
    x[0] = (A[0] + A[n + 1]) / 2;
    x[1] = (A[0] + A[n + 1]) / 2;
  }
  else
  {
    x[0] = (A[0] + A[n + 1]) / 2;
    x[1] = (A[0] + A[n + 1]) / 2;
  }
  return 0;
}