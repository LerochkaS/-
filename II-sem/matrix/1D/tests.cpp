#include <iostream>
#include <string>
#include <fstream>
#include "../matrix.hpp"

int main()
{
    typedef struct
    {
        std::string name;
        int right_answer;
    } Test;
    Test tests[7] = {{"1D/A1.txt", 3},
                     {"1D/A2.txt", 1},
                     {"1D/A3.txt", 3},
                     {"1D/A4.txt", 3},
                     {"1D/A5.txt", 4},
                     {"1D/A6.txt", 8},
                     {"1D/A7.txt", 6}};
    try
    {
        for (int i = 0; i < 7; ++i)
        {
            Matrix m(tests[i].name);
            std::cout << "Исходная матрица" << std::endl;
            m.print_matrix();
            std::cout << std::endl;
            std::cout << "Ступенчатый вид" << std::endl;
            m.gauss();
            std::cout << std::endl;
            std::cout << "Ранг матрицы равен: " << tests[i].right_answer << "  ";
            std::cout << "Вычисленное значение ранга: " << m.rank() << std::endl;
            std::cout << std::endl;
        }
    }
    catch (const char *ex)
    {
        std::cerr << "Возникла ошибка: " << ex << '\n';
    }
}