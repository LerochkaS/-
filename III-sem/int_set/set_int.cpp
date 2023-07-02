#include <iostream>
#include "set_int.h"

set_int::set_int (int max, int min)
{
	if(max <  min)
		throw "Некорректное значение параметров";
	max_ = max;
	min_ = min;
	set_ = new int [max_ - min_];
}

set_int::set_int(const set_int& other)
{
	min_ = other.min_;
	max_ = other.max_;
	curr = other.curr;
	int size = max_ - min_;
	set_ = new int [size];
	for (int i =0; i< size; ++i)
	{
		set_[i] = other.set_[i];
	}
}
void set_int:: add(int value)
{
	if(curr == max_-min_)
		throw "Очередь переполнена";
	if(value > max_ || value <min_)
		throw"Чсило не входит в границу массива";
	int flag =0;
	for (int i = 0; i< curr; ++i)
	{ 
		if(set_[i] != value)
		{ flag ++;}

		if(flag == curr)
		{ 
			set_[curr] = value;
			curr++;
		}
		else {}
	}
}

void set_int::del()
{
	if(is_empty())
		throw "Очередь пуста";
	curr --;
}
int set_int::max_elem () const
{
	if(is_empty())
		throw"Очередь пуста";
	int max = set_[0];
	for (int i=1; i < curr; ++i)
	{
		if (set_[i] > max) max = set_[i];
	}
	return max;
}

int set_int::min_elem () const
{
	if(is_empty())
		throw"Очередь пуста";
	int min = set_[0];
	for (int i=1; i < curr; ++i)
	{
		if (set_[i] < min) min = set_[i];
	}
	return min;
}
set_int set_int:: operator* (const set_int& other)
{ 
	int *set;
	int size = 0;

	int Max = (max_ < other.max_ ? max_ : other.max_);
	int Min = (min_ > other.min_ ? min_ :other.min_);
	set = new int[Max -Min]; 
	for (int i=0; i<curr; ++i)
	{
		for (int j =0; j< other.curr; j++)
		{
			if (set_[i] == other.set_[j])
			{
				size++;
				set[i] = set_[i];
			}
		}
	}
	set_int  to_return (Max, Min);
	for (int i=0; i<size; ++i)
	{
		to_return.add(set[i]);
	}
	return to_return;
}

bool set_int:: operator== (const set_int& other)
{
	if(curr != other.curr)
		return false;
	for(int i =0; i< curr; ++i)
	{
		int flag = 0;
		for (int j =0; j< curr; j++)
		{
			if(set_[j] != other.set_[j])	
				flag++;
		}
		if(flag == curr)
			return false;
	}
	return true;
}


















