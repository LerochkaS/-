#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 3 // количество булочников
#define M 5 // количество посетителей
#define K 2 // количество мест на прилавке

sem_t mutex;   // семафор для синхронизации доступа к прилавку
sem_t empty;   // семафор для отслеживания свободных мест на прилавке
sem_t full;    // семафор для отслеживания занятых мест на прилавке

int bakery_counter = 0;            // нумерация булочников
int customer_counter = 0;          // нумерация посетителей
int bun_count = 0;                 // подсчет остатка булок

void* baker(void* arg) {
    int bakery_number = 0;
    
    //для каждого булочника даем порядковый номер
    sem_wait(&mutex); //чтобы одновременно потоки не меняли номер текущего булочника
    bakery_number = ++bakery_counter;
    sem_post(&mutex);

    //бесконечно печем булочки
    while (1) {
        sleep(rand() %5 + 1); //время приготовления
        sem_wait(&empty);           // ждем, пока не освободится место на прилавке
        sem_wait(&mutex);           // захватываем семафор mutex для доступа к прилавку

        printf("Булочник %d кладет булку на прилавок\n", bakery_number);
        bun_count++;
        
        printf("Остаток булок на прилавке: %d\n", bun_count);

        sem_post(&mutex);           // освобождаем семафор mutex
        sem_post(&full);            // увеличиваем счетчик занятых мест на прилавке
    }
    return NULL;
}

void* customer(void* arg) {
    int customer_number = 0;
    sem_wait(&mutex);
    customer_number = ++customer_counter;
    sem_post(&mutex);

    while (1) {
        sem_wait(&full);            // ждем, пока на прилавке появится булка
        sem_wait(&mutex);           // захватываем семафор mutex для доступа к прилавку

        // Покупатель берет булку с прилавка
        printf("Покупатель %d берет булку с прилавка\n", customer_number);
        bun_count--;

        // Выводим остаток булок на прилавке
        printf("Остаток булок на прилавке: %d\n", bun_count);

        sem_post(&mutex);           // освобождаем семафор mutex
        sem_post(&empty);           // увеличиваем счетчик свободных мест на прилавке
        sleep(rand() %2 + 1); //едим булку
    }
    return NULL;
}

int main() {
    pthread_t baker_threads[N];
    pthread_t customer_threads[M];

    sem_init(&mutex, 0, 1);         // инициализация семафора mutex со значением 1
    sem_init(&empty, 0, K);         // инициализация семафора empty со значением K
    sem_init(&full, 0, 0);          // инициализация семафора full со значением 0

    int i;
    for (i = 0; i < N; i++) {
        pthread_create(&baker_threads[i], NULL, baker, NULL);            // создание потоков булочников
    }
    for (i = 0; i < M; i++) {
        pthread_create(&customer_threads[i], NULL, customer, NULL);       // создание потоков посетителей
    }

    pthread_exit(NULL);

    return 0;
}

