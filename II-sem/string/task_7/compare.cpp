#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include "compare.hpp"

const int n = 11;
using namespace std;

void _compare(std::string name_A, std::string name_B, std::string name_C)
{
    std::ifstream fA(name_A);
    if (!fA.is_open())
    {
        throw "!!Не удалось открыть файл A!!";
    }
    std::ifstream fB(name_B);
    if (!fB.is_open())
    {
        throw "!!Не удалось открыть файл B!!";
    }
    ofstream fC(name_C); // файл для записи результатов
    int i = 0;           // для запоминания номера строки в случае удаления
    int j = 0;           // для запоминания строки в случае добавления
    string s1;           //для чтения из файла А
    string s2;           // для чтения из файла В

    deque<string> arr_a;
    for (int _ = 0; _ < n && getline(fA, s1); ++_)
    {
        arr_a.push_back(s1);
    }
    while (getline(fB, s2))
    {
        int num = 0;
        ++j;
        for (int k = 0; k < arr_a.size(); ++k)
        {
            if (s2 == arr_a.at(k))
                break;
            ++num;
        }
        if (num == arr_a.size())
        {
            fC << "В файл добавили строку: " << endl;
            fC << s2 << endl;
            fC << "после строки с номером " << i << endl;
        }
        if (num != 0 && num != arr_a.size())
        {
            for (int k = 0; k < num; ++k)
            {
                if (!arr_a.empty())
                {
                    arr_a.pop_front();
                    if (getline(fA, s1))
                        arr_a.push_back(s1);
                    ++i;
                    fC << "Из файла удалили " << i << " строку" << endl;
                }
            }
        }
        if (!arr_a.empty() && num != arr_a.size())
        {
            ++i;
            arr_a.pop_front();
            if (getline(fA, s1))
                arr_a.push_back(s1);
        }
    }
    for (int k = 0; k < arr_a.size(); ++ k)
    {
        ++i;
        fC << "Из файла удалили строку " << i << endl;
    }
    if (arr_a.size() == 0)
    {
        fC << "изменений не происходило" << endl;
    }
    fA.close();
    fB.close();
    fC.close();
}