#pragma once

#include <cmath>
#include <cstdio>

double f(int k, int n, int i, int j);
int fill_matrix(double matrix[], int n, int k, FILE* input);
void fill_vector(double matrix[], double b[], int n);
void print_matrix(double matrix[], int l, int n, int m);
 