#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "matrix.hpp"

const double eps = 1e-8;

Matrix::Matrix(std::string name_of_file)
{
    std::ifstream inp(name_of_file);
    if (!inp.is_open())
    {
        throw "!!Не удалось открыть файл!!";
    }

    inp >> _m;
    inp >> _n;
    if (_m <= 0 || _n <= 0)
    {
        throw "Некорректные входные данные";
    }
    a = new double *[_m];
    for (int i = 0; i < _m; ++i)
    {
        a[i] = new double[_n];
        for (int j = 0; j < _n; ++j)
        {
            inp >> a[i][j];
        }
    }
    inp.close();
}

Matrix::Matrix(int m, int n)
{
    if (n <= 0  || m <= 0)
    {
        throw "Некорректные входные данные";
    }
    _n = n;
    _m= m;
    a = new double *[m];
    for (int i = 0; i < m; ++i)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
          a[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < _m; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
}

double Matrix::get_elem(int i, int j) const
{
    if (!(i >= 0 && i < _m) || !(j >= 0 && j < _n))
    {
        throw "Попытка обратиться к элементу, выходящему за пределы матрицы";
    }
    return a[i][j];
}

void Matrix::set_elem(double x,int i, int j)
{
    if (!(i >= 0 && i < _m) || !(j >= 0 && j < _n))
    {
        throw "Попытка обратиться к элементу, выходящему за пределы матрицы";
    }
    a[i][j] = x;
}

void Matrix::print_matrix() const
{
    for (int i = 0; i < _m; ++i)
    {
        for (int j = 0; j < _n; ++j)
        {
            std::cout << a[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void Matrix::gauss()
{
    int m = 0; //(строки)
    int n = 0; //(столбцы)
    while (m < _m && n < _n)
    {
        /* Ищем строку с самым большим элементом */
        double cur_elem = a[m][n];
        for (int i = _m - 1; i > m; --i)
        {
            if (fabs(a[i][n]) > fabs(a[i - 1][n]))
            {
                for (int k = _n - 1; k >= n; --k)
                {
                    cur_elem = a[i][k]; //заменить
                    a[i][k] = a[i - 1][k];
                    a[i - 1][k] = cur_elem;
                }
            }
        }
        /* Если наибольший элемент равен 0, то столбец нулевой и мы не трогаем его, переходим к следующему, если не нулевой,
        то делим на элемент и вычитаем текущую строку из нижних */
        if (fabs(cur_elem - 0) > eps)
        {
            for (int k = n; k < _n; ++k)
            {

                a[m][k] = a[m][k] / cur_elem;
            }
            for (int l = m + 1; l < _m; ++l)
            {
                double x = a[l][n];
                for (int s = 0; s < _n; ++s)
                {
                    a[l][s] -= x * a[m][s];
                }
            }
            ++m;
        }
        ++n;
    }
    std::cout << std::endl;
    for (int i = 0; i < _m; ++i)
    {
        for (int j = 0; j < _n; ++j)
        {
            std::cout << a[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

int Matrix::rank() const
{
    double nul = 0; // счетчик нулевых строк
    for (int i = _m - 1; i >= 0; --i)
    {
        int k = 0;
        for (int j = _n - 1; j >= 0; --j)
        {
            if (fabs(a[i][j] - 0) < eps)
            {
                ++k;
            }
        }
        if (k == _n)
            ++nul;
    }
    return _m - nul;
}
