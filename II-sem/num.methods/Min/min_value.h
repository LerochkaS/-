/** Коды ошибок Numerical Algorithms **/  
typedef  enum 
{
    NA_PARAM = 1,     // Недопустимые входные параметры
    NA_OK = 0,        // Все отлично
} NAError;

/* Множество функций R -> R */
typedef double (*RRfunc)(double x);

/** Вычисляет минимальное значение функции на отрезке 
 **
 ** Параметры:
 **     f: заданная функция
 **     epsilon: заданная точность
 **     a, b: границы отрезка
 **     err: адресс для сохранения кода возврата 
 ** 
 **
 ** Возвращаемое значение:
 **     В случае ошибочных переданных значений:  epsilon <= 0, нулевой адрес f,  - функция возращает 0, 
 **     по адресу err записывается NA_PARAN
 **
 **     В случае успеха функция возвращает минимальное значение, по адресу err записывается 
 **     код NA_OK 
 **/
double min_value (RRfunc f, double a, double b, double eps, NAError *err);