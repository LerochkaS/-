#include "req.h"

double f(int k, int n, int i, int j)
{
	switch (k)
	{ 
	case 1:
		return n - fmax(i, j) + 1;
	case 2:
		return fmax(i, j);
	case 3:
		return fabs(i - j);
	case 4:
		return 1.0 / (i + j - 1);
	default:
		return -1;
	}
}

int fill_matrix(double matrix[], int n, int k, FILE* input)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
	 	{
			if (k != 0)
			{
				matrix[i * n + j] = f(k, n, i + 1, j + 1);
			}
			else if ((input == nullptr) || (fscanf(input, "%lf", &matrix[i * n + j]) != 1)) { return -1; }
		}
	}
	return 0;
}

void fill_vector(double matrix[], double b[], int n)
{
	for (int i = 0; i < n; i++)
	{
		b[i] = 0;
		for (int j = 0; j <= (n-1)/2; j++)
		{
			b[i] += matrix[i * n + 2*j];
		}
	}
}

void print_matrix(double matrix[], int l, int n, int m)
{
	for (int i = 0; i < fmin(m, l); i++)
	{
		for (int j = 0; j < fmin(m, n); j++)
		{
			printf("%10.3e ", matrix[i * n + j]);
		}
		printf("\n");
	}
}