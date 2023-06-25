#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <cmath>
#include "Interpol.h"

typedef double (*RRfunc)(double x);

double _sq(double x) { return (x * x - 6); }
void values(RRfunc f, double a, double b, int n, string Name, std::vector<pair<double, double>> & Vec)
{
    ofstream Cout(Name);
    double step = (b-a)/(n);
    double x = a;
    while (x < b)
    {
        pair <double, double> point;
        point.first = x; 
        point.second = f(x);
        Vec.push_back(point);
        x+= step;
    }
     pair <double, double> point;
        point.first = b; 
        point.second = f(b);
        Vec.push_back(point);
    for (auto i: Vec)
    {
        Cout << i.first << " " << i.second << endl;
    }
}


int main()
{
    NAError err;

    typedef struct
    {
        RRfunc f;
        double a, b;
        std::string name1, name2;
        int k;
    } Test;
    Test tests[3] = {{exp,   -5,   5,   "exp/n_points.txt", "exp/rand_points.txt",    25},
                    {sin,    -10,  10,  "sin/n_points.txt", "sin/rand_points.txt",    25}, 
                    {_sq,    -5,   5,   "sq/n_points.txt",  "sq/rand_points.txt",     25}};
              
   
    for (int i = 0; i < 3; i++)
    {
        vector<pair<double, double>> n_points;
        if (tests[i].a >= tests[i].b)
        {
            err = NA_PARAM;
            cout << "!!Некорректные входные параметры!!" << endl;
            return 1;
        }
        values (tests[i].f, tests[i].a, tests[i].b, n, tests[i].name1, n_points);
        double value;
        double x;
        ofstream Rout;
        Rout.open(tests[i].name2);
        for (int _ = 0; _ < tests[i].k; ++_)
        {
        x = tests[i].a + (double)(rand())/RAND_MAX * (tests[i].b-tests[i].a); 
        value = Interpol (x, n_points, &err);
        Rout << x << " " << value << endl;
        }
        Rout.close();
    }
}
