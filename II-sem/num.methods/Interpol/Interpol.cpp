#include <iostream>
#include <vector> 
#include <string>
#include <fstream>
#include "Interpol.h" 

using namespace std;


double Interpol(double x, std::vector<pair<double, double>> & Vec, NAError *err)
{

    double value = 0;
    if (x < Vec[0].first || x > Vec[n].first)
        {
            cout << "К сожалению, заданный x не принадлежит отрезку приближения" << endl;
            *err = NA_PARAM;
            return 1;
        }
    /* Построим линейные функции, приближающие значение заданной на всех отрезках */
    for (int i = 1; i<n; i++)
    {
        if (x <= Vec[i].first)
        {
            if (Vec[i-1].first > Vec[i].first)
            {
                double c =0;
                c = Vec[i-1].first;
                Vec[i-1].first = Vec[i].first;
                Vec[i].first = c;
            }
            value = Vec[i - 1].second + (Vec[i].second - Vec[i - 1].second) * (x - Vec[i - 1].first) / (Vec[i].first - Vec[i - 1].first);
            break;
        }
    }
    *err = NA_OK; 
    return value;
}
