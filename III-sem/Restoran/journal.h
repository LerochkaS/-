#pragma once 

using namespace std;

class journal
{
    private:
        size_t N; //количество столиков
        size_t on; //время начала поcещения ресторана (учитывая записи)
        size_t off; //время окончания работы ресторана (учитывая записи)
        pair<size_t, bool> **Set;
        journal();
    public:
        journal (size_t begin, size_t end, size_t N);
        ~journal();
        void book (size_t num, size_t start); // сделать запись в журнал по номеру
        bool free_t (size_t start) const; 
        size_t near () const; //возвращает ближайшее время, на которое можно записаться, если такого нет, возвращает off
        bool is_book (size_t num) const; //проверяем, есть ли запись для гостя по номеру телефона
        size_t spend (size_t num); // возвращает номер столика и фиксирует, что гость пришел
        void bye (size_t start, size_t n); //фиксирует уход гостя
};
