#include <iostream>
#include "journal.h"

journal::journal(size_t begin, size_t end, size_t N)
{
    this->N = N;
    on = begin;
    off = end;
    Set = new pair<size_t, bool> *[off - on];
    for (size_t i = 0; i < (end - begin); i++)
    {
        Set[i] = new pair<size_t, bool>[N];
        for (size_t j = 0; j < N; j++)
        {
            Set[i][j].first = 0;
            Set[i][j].second = false;
        }

    }
}

journal::~journal()
{
    for (int i = 0; i < N; ++i)
    {
        delete[] Set[i];
    }
    delete[] Set;
}

bool journal::free_t(size_t start) const
{
    if (start >= off || start < on)
        throw "В выбранное время ресторан не работает";
    size_t num;
    if(start == (off - 1) || start == (off - 2))
        throw"Невозможно выполнить запись на 3 часа";
    for (size_t i = 0; i < N; i++)
    {
        if(Set[start - on][i].first == 0 && Set[start - on + 1][i].first == 0 && Set[start - on + 2][i].first == 0)
        {
            return true;
        }
    }
    return false;
}

void journal::book(size_t num, size_t start)
{
    if (start < on || start >= off)
        throw "Невозможно выполнить запись на данное время";
    size_t n = free_t(start);
    if (n == -1)
        throw "На данное время нет свободных столиков";
    else
    {
        Set[start - on][n].first = num;
        cout <<"Запись по данному номеру телефона осуществлена"<<endl;
    }
}

size_t journal::near () const
{
    for (size_t i = 0; i < (off - on -  2); i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if(Set[i][j].first == 0 && Set[i + 1][j].first == 0 && Set[i + 2][j].first == 0)
                return i + on;
        }
    }
    return off;
}

bool journal::is_book(size_t num) const
{
    for (size_t i = 0; i < (off - on); i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (Set[i][j].first == num)
                return true;
                
        }
    }
    return false;
}

size_t journal::spend(size_t num)
{
    for (size_t i = 0; i < (off - on); i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (Set[i][j].first == num)
                {
                    Set[i][j].second = true;
                    return j+1;
                }  
        }
    }
}

void journal::bye (size_t start, size_t n)
{
    Set[start][n].first = 0;
    Set[start][n].second= false;
}