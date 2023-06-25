# include <stdio.h>
# include <stdlib.h>
# include "calculate.h"


double square(double x)
{
    return x*x;
}

double summ(double x)
{
    return x+x; 
}

double plus_one(double x)
{
    return 1+x;
}

int main (){
    FILE *inp;
    FILE *out;
    int n; //количество иксов 
    double *x, *F; //массив иксов и значений функции соответсвенно
    double end; //для проверки на конец
    NAError err;

    inp = fopen ("input.txt", "r");
    if (inp == NULL){
        printf ("НЕ удалось открыть файл!\n");
        return 1;
    }
    if (fscanf (inp, "%d", &n) !=1){
        printf ("Ошибка чтения файла\n");
        fclose (inp);
        return 1;
    }

    x = malloc(sizeof (double)*n);
    if (!x){ //проверяем, создался ли массив
        printf ("Не удалось создать массив\n");
        fclose (inp);
        return 1;
    }   
    for (int i=0; i < n; i ++){ //считываем файл в массив
        if(fscanf(inp, "%lf", &x[i]) != 1){ 
            printf ("Некорректные данные\n");
            fclose (inp);
            free (x);
            return 1;
        }
    }

       if (fscanf (inp, "%lf", &end) != EOF){
        printf ("Не удалось достичь конца файла\n");
        fclose (inp);
        free (x);
        return 0;
    }

    RRfunc Testing_arrs[3] = {square, summ, plus_one}; //массив тестирующих функций

F = malloc(sizeof (double)*n);
    if (!F)
    {
        printf ("Не удалось выделить память под массив значений!\n");
        free (x);
        fclose(inp);
        return 0;
    }


    out = fopen("output.txt", "w");
    if (out == NULL){
        printf("!Не удалось открыть файл \"output.txt\"!\n");
        fclose (inp);
        free (x); 
        return 0;
    }
    for (int j = 0; j < 3; j++){
        calculate (Testing_arrs[j], F, x, n, &err);
        for (int i = 0; i < n; i++)
        {
            fprintf (out, "%lf ", F[i]);
        }
        fprintf(out, "\n");
    }
    
    return 0; 
}