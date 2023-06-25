#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "../matrix.hpp"

int main()
{
    typedef struct
    {
        std::string name;
        std::string answer;
    } Test;
    Test tests[6] = {{"2D/A1.txt", "{2.5, 0.25, 0.2}"}, {"2D/A2.txt", "{0.085, 0.5, -0.25, 0.45}"}, 
                     {"2D/A3.txt", "{1, 2, 3}"}, {"2D/A4.txt", "{1, 2, -1, 3 -1}"}, {"2D/A5.txt", "{3}"}, {"2D/A6.txt", ""}};

    int n = 0;
    try
    {
        for (int i = 0; i < 6; ++i)
        {
            Matrix m(tests[i].name);
            std::cout << "Данная матрица: " << std::endl;
            m.print_matrix();
            std::cout << std::endl;
            std::cout << "Правильный ответ: x= ";
            std::cout << tests[i].answer << std::endl;
            std::cout << std::endl;
            std::cout << "Вычисленный ответ: х= " << "{";
            iter (tests[i].name);
            std::cout << "}" << std::endl;
        }
    }
    catch (const char *ex)
        {
            std::cerr << "Возникла ошибка: "<< ex << std::endl;
        }
}

