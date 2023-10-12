#include <cmath>
#include <chrono>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "req.h"
#include "jordan.h"

using namespace std;

int main(int argc, char** argv)
{
	int n, m, k;
	double Ax, norm_Ax_b, norm_b, nev, norm_dx;
	const char* filename;
	chrono::steady_clock::time_point t1, t2;
	FILE* input;

	if (argc < 4) {
		printf("Not enough arguments. It should be 3 or 4.\n");
		return -1;
	}

	if (argc > 5) {
		printf("Too much arguments. It should be 3 or 4.\n");
		return -1;
	}

	n = atoi(argv[1]);
	m = atoi(argv[2]);
	k = atoi(argv[3]);

	if ((n <= 0) || (m <= 0) || (k < 0) || (k > 4)) {
		printf("Wrong input. n and m should be positive integer, k should be either 0, 1, 2, 3 or 4.\n");
		return -1;
	}

	if ((k != 0) && (argc == 5)) {
		printf("Wrong input. If k not a 0, then you should enter only 3 argumants.\n");
		return -1;
	}

	if ((k == 0) && (argc == 4)) {
		printf("Wrong input. If k=0, then you should enter 4 arguments, the last of which is a name of input file.\n");
		return -1;
	}

	input = nullptr;
	if (k == 0) {
		filename = argv[4];
		input = fopen(filename, "rt");
		if (input == NULL) {
			printf("Error opening input file.\n");
			return -1;
		}
	}

	double *matrix = new double[n*n];
	double *b = new double[n];
	double *x = new double[n];

	if (fill_matrix(matrix, n, k, input) == -1)
	{
		printf("Wrong data in file.\n");
		delete[] matrix;
		delete[] b;
		delete[] x;
		return -1;
	}
	fill_vector(matrix, b, n);

	double *matrix2 = new double[n*n];
	double *b2 = new double[n];
	for (int i = 0; i < n * n; i++) { matrix2[i] = matrix[i]; }
	for (int i = 0; i < n ; i++) { b2[i] = b[i];}

	printf("Matrix:\n");
	print_matrix(matrix, n, n, m);

	t1 = chrono::steady_clock::now();
	if (jordan(n, matrix, b, x) == -1) {
		printf("Error: matrix is singular.\n");
		delete [] matrix;
		delete [] matrix2;
		delete [] b;
		delete [] b2;
		return -1;
	}
	t2 = chrono::steady_clock::now();

	printf("\n Solution: \n"); 
	print_matrix(x, n, 1, m);
	printf("\n Time: ");
	cout << chrono::duration_cast<std::chrono::microseconds> (t2 - t1).count() * 1e-6 << std::endl;

	norm_Ax_b = 0;
	norm_b = 0;
	for (int i = 0; i < n; i++) {
		Ax = 0;
		for (int j = 0; j < n; j++)
		{
			Ax += matrix2[n * i + j] * x[j];
		}
		norm_Ax_b += (Ax - b2[i]) * (Ax - b2[i]);
		norm_b += b2[i] * b2[i];
	}
	nev = norm_Ax_b / norm_b;
	printf("Discrepancy: %10.3e\n", nev);

	norm_dx = 0;
	for (int i = 0; i < n; i++) { norm_dx += (x[i] - (i + 1) % 2) * (x[i] - (i + 1) % 2); }
	norm_dx = sqrt(norm_dx);
	printf("Error: %10.3e\n", norm_dx);

	delete [] matrix;
	delete [] matrix2;
	delete [] b;
	delete [] b2;

	return 0;
}