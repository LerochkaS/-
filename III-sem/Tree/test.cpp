#include <iostream>
#include "SetR2.h"

using namespace std;

enum FuncCode
{
    add = 0,
    del = 1,
    is_here = 2,
    get_quant = 3,
};

int main()
{
    /*-------------------------------------------RAND_SET-------------------------------------*/
    cout << "Рандом" << endl;
    SetR2 set(100, {0, 0}, 5);
    for (size_t _ = 0; _ < 10; ++_)
    {
        size_t code = rand() % 4;
        double x = rand() % 100;
        double y = rand() % 100;
        switch (code)
        {
        case add:
            try
            {
                if (set.add(x, y))
                    cout << "Добавлена точка: {" << x << "," << y << "}" << endl;
                [[fallthrough]];
            }
            catch (MyException &ex)
            {
                cerr << "Error: " << ex.Message() << '\n';
                cerr << "Code: " << ex.Code() << '\n';
            }
        case is_here:
            try
            {
                if (set.is_here(x, y))
                    cout << "Точка: {" << x << "," << y << "}"
                         << " присутсвует в множестве" << endl;
                [[fallthrough]];
            }
            catch (MyException &ex)
            {
                cerr << "Error: " << ex.Message() << '\n';
                cerr << "Code: " << ex.Code() << '\n';
            }
        case del:
            try
            {
                if (set.del(x, y))
                    cout << "Удалена точка: {" << x << "," << y << "}" << endl;
                else 
                {
                    cout << "Попытка удалить элемент (" << x << "," << y << ") не принадлежащий множеству" << endl;
                }
                [[fallthrough]];
            }
            catch (MyException &ex)
            {
                cerr << "Error: " << ex.Message() << '\n';
                cerr << "Code: " << ex.Code() << '\n';
            }
        case get_quant:
            cout << "Размер множества равен " << set.get_quant() << endl;
            [[fallthrough]];
        }
    }
    cout<<endl<<endl;
    /*---------------------------------------SET_FROM_FILE--------------------------------------------*/
    cout << "Тесты из файла" << endl;
    std::ifstream inp("inp.txt");
    SetR2 set_from_inp(inp);
    for (size_t _ = 0; _ < 50; ++_)
    {
        size_t code = rand() % 4;
        double x = rand() % 100;
        double y = rand() % 100;
        switch (code)
        {
        case add:
            try
            {
                if (set_from_inp.add(x, y))
                    cout << "Добавлена точка: {" << x << "," << y << "}" << endl;
                [[fallthrough]];
            }
            catch (MyException &ex)
            {
                cerr << "Error: " << ex.Message() << '\n';
                cerr << "Code: " << ex.Code() << '\n';
            }
        case is_here:
            try
            {
                if (set_from_inp.is_here(x, y))
                    cout << "Точка: {" << x << "," << y << "}"
                         << " присутсвует в множестве" << endl;
                [[fallthrough]];
            }
            catch (MyException &ex)
            {
                cerr << "Error: " << ex.Message() << '\n';
                cerr << "Code: " << ex.Code() << '\n';
            }
        case del:
            try
            {
                if (set_from_inp.del(x, y))
                    cout << "Удалена точка: {" << x << "," << y << "}" << endl;
                else 
                {
                    cout << "Попытка удалить элемент (" << x << "," << y << ") не принадлежащий множеству" << endl;
                }
                [[fallthrough]];
            }
            catch (MyException &ex)
            {
                cerr << "Error: " << ex.Message() << '\n';
                cerr << "Code: " << ex.Code() << '\n';
            }
        case get_quant:
            cout << "Размер множества равен " << set_from_inp.get_quant() << endl;
            [[fallthrough]];
        }
    }
}