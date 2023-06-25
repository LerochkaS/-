#include <stdio.h>
#include "calculate_integral.h"
#include <math.h>

// Вычисляет экспоненту
double exp_(double x)
{
    return exp(x);
}

// Возвращает полученное число

double empty_change(double x)
{
    return x;
}

// Вычиляет квадрат числа
double square(double x)
{
    return x * x;
}

// Кубическая парабола 
double cube(double x)
{
    return (5*x*x*x - 12*x*x + 9*x -1);
}

// Что-то интреесное 
double ln_ (double x)
{
    return (-15*log(x) - 7*x - 1);
}

int main()
{
    NAError err;
    double Integral = 0; // Конечное значение интеграла
    double a, b;         //Пределы отрезка
    double epsilon = 1e-4;

    printf("Определите [a;b]\n");
    printf("Введите значение параметра a\n");
    if (scanf("%lf", &a) != 1)
    {
        printf("Некорректные парамтеры a!");
        return 1;
    }
    printf("Введите значение парамтера b\n");
    if (scanf("%lf", &b) != 1)
    {
        printf("Некорректные парамтеры b!");
        return 1;
    }

    if(err == NA_PARAM)
    {
        printf("Некорректные входные параметры!\n");
        return 0;
    }

    RRfunc Testing_Arrs[5] = {exp_, empty_change, square, cube, ln_};

    printf("Для функции exp_: \n");
    Integral = calculate_integral(Testing_Arrs[0], a, b, epsilon, &err);
    if (err == NA_OK)
    {
        printf("Интеграл равен %lf \n", Integral);
    }
    if (err == NA_CONVERGE)
    {
        printf("Не удалось вычислить интеграл с заданной точностью\n");
        printf("Последнее значение равно %lf \n", Integral);
    }
    printf ("\n");

    printf("Для функции x: \n");
    Integral = calculate_integral(Testing_Arrs[1], a, b, epsilon, &err);
    if (err == NA_OK)
    {
        printf("Интеграл равен %lf \n", Integral);
    }
    if (err == NA_CONVERGE)
    {
        printf("Не удалось вычислить интеграл с заданной точностью\n");
        printf("Последнее значение равно %lf \n", Integral);
    }
    printf ("\n");

    printf("Для функции x^2: \n");
    Integral = calculate_integral(Testing_Arrs[2], a, b, epsilon, &err);
    if (err == NA_OK)
    {
        printf("Интеграл равен %lf \n", Integral);
    }
    if (err == NA_CONVERGE)
    {
        printf("Не удалось вычислить интеграл с заданной точностью\n");
        printf("Последнее значение равно %lf \n", Integral);
    }
    printf ("\n");

    printf("Для функции 5*x*x*x - 12*x*x + 9*x -1: \n");
    Integral = calculate_integral(Testing_Arrs[3], a, b, epsilon, &err);
    if (err == NA_OK)
    {
        printf("Интеграл равен %lf \n", Integral);
    }
    if (err == NA_CONVERGE)
    {
        printf("Не удалось вычислить интеграл с заданной точностью\n");
        printf("Последнее значение равно %lf \n", Integral);
    }
    printf ("\n");

    printf("Для функции -15*ln(x) - 7*x - 1: \n");
    Integral = calculate_integral(Testing_Arrs[4], a, b, epsilon, &err);
    if (err == NA_OK)
    {
        printf("Интеграл равен %lf \n", Integral);
    }
    if (err == NA_CONVERGE)
    {
        printf("Не удалось вычислить интеграл с заданной точностью\n");
        printf("Последнее значение равно %lf \n", Integral);
    }
    printf ("\n");

    return 0;
}