#pragma once

class  set_int{
private:
	int min_;
	int max_;
	int *set_; // Массив целых чисел объекта
	int curr=0; // Количесво элементов множества
	set_int();
	public:
	operator= (const set_int 
	set_int (int max, int min);
	~set_int() {delete [] set_;} 
	set_int (const set_int& other);
	void add (int value);
	void del (); //Удаляет последний элемент
        bool is_empty() const {if(curr == 0) {return true;} return false;}
        int amount () const {return curr;} // Возвращает колимчество элементов
        int max_elem () const;
        int min_elem() const;
        int border_left () const {return min_;}
        int border_right () const {return max_;}
        set_int	operator* (const set_int& other);
        bool operator== (const set_int& other);
        	
};
