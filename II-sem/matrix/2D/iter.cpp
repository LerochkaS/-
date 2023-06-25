#include <iostream>
#include <fstream>
#include "../matrix.hpp"

const double eps = 1e-10;

void iter(std::string name_of_file)
{
    Matrix a(name_of_file);      //Матрица коэф
    Matrix column(1, a.get_m()); //вектор-решение
    for (int i = 0; i < a.get_m(); ++i)
    {
        // отдельно проверять на то, чтобы a[i][i] != 0 не нужно, так как для таких матриц метод заведомо не сходится  
        double y = a.get_elem(i, a.get_m()) / a.get_elem(i, i);
        column.set_elem(y, 0, i);
    }
    Matrix x(1, a.get_m()); //вектор-решение полученный в результате приближения

    do //бесконечный цикл, условие выхода прописано в самом цикле
    {
        for (int i = 0; i < a.get_m(); ++i)
        {
            x.set_elem((a.get_elem(i, a.get_m()) / a.get_elem(i, i)), 0, i); // первое приближение выбираем нулевым для облегчения подсчета
            for (int j = 0; j < a.get_m(); ++j)
            {
                if (i != j)
                {
                    double y = a.get_elem(i, j) / a.get_elem(i, i) * column.get_elem(0, j);
                    x.set_elem((x.get_elem(0, i) - y), 0, i);
                }
            }
        }
        bool is_eps = true;
        for (int i = 0; i <= (a.get_m() - 1); ++i)
        {
            if (abs(x.get_elem(0, i) - column.get_elem(0, i)) > eps)
            {
                is_eps = false;
                break;
            }
        }
        for (int i = 0; i < (a.get_n() - 1); ++i)
        {
            column.set_elem(x.get_elem(0, i), 0, i);
        }
        if (is_eps)
            break;

    } while (1);
    for (int i = 0; i < a.get_m(); ++i)
    {
        std::cout << column.get_elem(0, i) << " ";
    }
}