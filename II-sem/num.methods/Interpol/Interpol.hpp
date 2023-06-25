#include <iostream>
#include <vector>

const int n = 75;

using namespace std;

/** Коды ошибок Numerical Algorithms **/  
typedef  enum 
{ 
    NA_PARAM = 1,     // Ошибочные входные данные
    NA_OK = 0,        // Все хорошо
} NAError;

/* Множество функций R -> R */
typedef double (*RRfunc)(double x);


/** Составляет массив аргуметнов и значений на них
 ** 
 **/
    void values(RRfunc f, double a, double b, int n, string Name, std::vector<pair<double, double>> & Vec);

/** Вычисляет приближенное значение функции методом кусочно0линейной интерполяции
 **
 ** Параметры:
 **     f: заданная функция 
 **     a, b: заданные границы отрезка
 **     x: точка, в которой приближается значение
 **     err: адресс для сохранения кода возврата 
 ** 

 **
 ** Возвращаемое значение:
 **     В случае ошибочных переданных значений: нулевой адрес f, a>=b  - функиця возращает 1,
 **     по адресу err записывается NA_PARAN
 **
 **     В случчае успеха функция возвращает приближенное значение, по адресу err записывается 
 **     код NA_OK
 **/
double Interpol (double x, double a, double b, std::vector<pair<double, double>> & Vec, NAError *err);
