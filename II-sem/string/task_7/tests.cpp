#include <iostream>
#include <string>
#include "compare.hpp"

using namespace std;

int main ()
{
typedef struct
    {
        std::string name_A;
        std::string name_B;
        std::string name_C;
    } Test;
    Test tests[3] = {{"A1.txt", "B1.txt", "C1.txt"},
                     {"A2.txt", "B2.txt", "C2.txt"},
                     {"A3.txt", "B3.txt", "C3.txt"}};

    try
    {
        for (int i = 0; i < 3; ++i)
        {
            _compare (tests[i].name_A, tests[i].name_B, tests[i].name_C);
            cout << "Результат для теста " << i+1 << " записан в файл " << tests[i].name_C << endl;
        }
    }
    catch (const char *ex)
    {
        std::cerr << "Возникла ошибка: " << ex << '\n';
    }           
    return 0;
}