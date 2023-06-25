#include <iostream>
#include <fstream>
#include "def_undef.hpp"

int main()
{
    try
    {
        std::ifstream fA("A.txt");
        if (!fA.is_open())
        {
            throw "!!Не удалось открыть файл A!!";
        }
        std::ofstream fB("B.txt");
        if (!fB.is_open())
        {
            fA.close();
            throw "!!Не удалось открыть файл B!!";
        }

        def_undef(fA, fB);
        std::cout << "Результат записан в файл \"B.txt\"!" << std::endl;
        fA.close();
        fB.close();
    }
    catch (const char *ex)
    {
        std::cerr << "Возникла ошибка: " << ex << '\n';
    }
    return 0;
}
