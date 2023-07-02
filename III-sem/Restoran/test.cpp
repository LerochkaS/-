#include <iostream>
#include "journal.h"

int main()
{
    try
    {
        journal today(10, 22, 10);
        today.book(89879, 10);
        today.spend(89879);
        /*
        for (size_t i = 0; i < 10; i++)
        {
            today.book(8952 + i, 11); //забронировлаи каждый столик в 11 часов
        }
        today.spend(8952);
        today.book(777, 100);
        */
        for (size_t i = 0; i < 100; i++)
        {
            today.book(555, 12 + i);
        }
    }
    catch (const char *ex)
    {
        std::cerr << "Возникла ошибка: " << ex << std::endl;
    }
}