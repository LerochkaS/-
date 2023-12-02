#include "qr_method.h"
#include "req.h"
#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;

void norm(double A[], double x[], int n, double* norm1, double* norm2)
{
    double result1 = 0.0, result2 = 0.0;
    for (int i = 0; i < n; i++)
    {
        result1 += A[i * n + i];
        result1 -= x[i];
        result2 -= x[i] * x[i];
        for (int j = 0; j < n; j++) result2 += A[i * n + j] * A[i * n + j];
    }
    result1 = fabs(result1);
    result2 = fabs(result2);
    *norm1 = result1;
    *norm2 = result2;
}

int main(int argc, char *argv[])
{
    int k = 0, n, m, a, j = 0, i = 0;
    double norm1, norm2, eps;
    double *A, *d1, *d2, *x;
    const char *filename;
    FILE* input;
    chrono::steady_clock::time_point t1, t2;

    if ((argc != 5) && (argc != 6))
    {
        cout << "Wrong number of arguments" << endl;
        return (0);
    }
    n = stoi(argv[1]);
    m = stoi(argv[2]);
    eps = stod(argv[3]);
    k = stoi(argv[4]);

    input = nullptr;
    if (k == 0)
    {
        if (argc != 6)
        {
            cout << "No name of file" << endl;
            return 0;
        }
        filename = argv[5];
        input = fopen(filename, "rt");
        if (input == NULL) {
            printf("Error opening input file.\n");
            return -1;
        }
    }
    
    A = (double*)malloc(sizeof(double) * n * n);
    x = (double*)malloc(sizeof(double) * n);
    for (int s = 0; s < n; s++) x[s] = 0;
    d1 = (double*)malloc(sizeof(double) * n);
    d2 = (double*)malloc(sizeof(double) * n);
    
    if (fill_matrix(A, n, k, input) == -1) {
        printf("Wrong data in file.\n");
        free(A);
        free(x);
        free(d1);
        free(d2);
        return -1;
    }
    
    print_matrix(A, n, n, m);
    
    t1 = std::chrono::steady_clock::now();
    a = qr_method(n, A, x, d1, d2, eps, k);
    t2 = std::chrono::steady_clock::now();
    if (a == -1) {
        free(A);
        free(x);
        free(d1);
        free(d2);
        cout << "Matrix doesn't converge" << endl;
        return -1;
    }

    cout << "Eigenvalues:" << endl;
    print_matrix(x, n, 1, m);
    cout << endl;

    if (k == 2) {
        double real_value;
        sort(x, x+n);
        cout << "real values / difference:" << endl;
        for (int i = 0; i < min(m,n); i++) {
            real_value = 4 * sin(3.14159265358 * (i+1) / (2 * n + 2)) * sin(3.14159265358 * (i+1) / (2 * n + 2));
            cout << real_value << " / " << fabs(real_value - x[i]) << endl;
        }
        cout << endl;
    }

    cout << "Time: " << chrono::duration_cast<std::chrono::microseconds> (t2 - t1).count() * 0.6e-6 << endl;
    free(A);
    A = (double*)malloc(sizeof(double) * n * n);
    if (A == NULL)
    {
        cout << "Not enough memory" << endl;
        free(x);
        free(d1);
        free(d2);
        return (0);
     }

    if (k == 0) fill_matrix(A, n, k, input);
    if ((k > 0) && (k < 5))
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) A[i * n + j] = f(n, k, i, j);
    }

    norm(A, x, n, &norm1, &norm2);
    cout << "Norm1: " << norm1 << endl
         << "Norm2: " << norm2 << endl;
    free(A);
    free(x);
    free(d1);
    free(d2);
    return 0;
}