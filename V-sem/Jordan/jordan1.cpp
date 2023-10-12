#include "jordan.h"
#include "req.h"

int jordan(int n, double matrix[], double b[], double x[])
{
	int *indi = new int[n];
	int *indj = new int[n];
	int k1, k2, t;
	double p;
	double max_e;
	for (int i = 0; i < n; i++){ indi[i] = i; indj[i] = i; }
	for (int m = 0; m < n; m++)
	{
		k1 = m;
		k2 = m;
		max_e = matrix[indi[m] * n + indj[m]];
		for (int i = m; i < n; i++)                             
		{
			for (int j = m; j < n; j++)
			{
				if (fabs(matrix[indi[i] * n + indj[j]]) > fabs(max_e))
				{
					k1 = i;
					k2 = j;
					max_e  = matrix[indi[k1] * n + indj[k2]];
				}
			}
		}
		t = indi[k1];
		indi[k1] = indi[m];
		indi[m] = t;
		t = indj[k2];
		indj[k2] = indj[m];
		indj[m] = t;                                            
		if (matrix[indi[m] * n + indj[m]] == 0) { return -1; } 
		p = matrix[indi[m] * n + indj[m]];
		b[indi[m]] /= p;
		for (int j = n - 1; j > m; j--)
		{
			matrix[indi[m] * n + indj[j]] /= p;
		}
		matrix[indi[m] * n + indj[m]] = 1;
		for (int i = 0; i < n; i++)
		{
			if (i != m)
			{
				b[indi[i]] -= matrix[indi[i] * n + indj[m]] * b[indi[m]];
				p = matrix[indi[i] * n + indj[m]];
				for (int j = n-1; j > m; j--)
				{
					matrix[indi[i] * n + indj[j]] -=  p * matrix[indi[m] * n + indj[j]];
				}
				matrix[indi[i] * n + indj[m]] = 0;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		x[indj[i]] = b[indi[i]];
	}
	return 0; 
}