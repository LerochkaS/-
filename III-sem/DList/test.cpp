#include <iostream>
#include "DList.h"
#include "MyException.h"
using namespace std;

int main()
{
	try
	{
		//==================================Проверка реализации методов на int=========================
		cout << "Проверка реализации методов" << endl;
		DList<int> list1_int;
		cout << "Заполняем лист 1 числами от 10 до 15" << endl;
		for (int k = 10; k <= 15; ++k)
		{
			list1_int.push_back(k);
		}
		cout << list1_int << endl;
		cout << "Удаляем первый элемент листа " << list1_int.pop_front() << endl;
		cout << "Выполняем копирование: лист 2 = лист 1" << endl;
		DList<int> list2_int = list1_int;
		cout << list2_int << endl;
		cout << "заполняем сисок 1 новыми значениями: " << endl;
		list1_int.clean();
		for (int k = -3; k <= 3; ++k)
		{
			list1_int.push_front(k);
		}
		cout << list1_int << endl;
		DList<int> list3_int = list1_int + list2_int;
		cout << "Список 1 + список 2: " << endl;
		cout << list3_int << endl;
		cout << "Будем вставлять в лист 3 рандомные числа в рандомные места: " << endl;
		for (int _ = 0; _ < 3; ++_)
		{
			DList<int>::Iterator i = list3_int.begin();
			int k = rand() % list3_int.get_size();
			for (int j = 1; j < k; ++j)
			{
				++i;
			}
			int val = (rand() % list3_int.get_size());
			list3_int.insert(val, i);
			cout << "Вставляем после элемента " << k << " число " << val << endl;
			cout << list3_int << endl;
		}
		cout << "Будем удалять из листа 3 рандомные числа в рандомных местах: " << endl;
		for (int _ = 0; _ < 3; ++_)
		{
			DList<int>::Iterator i = list3_int.begin();
			int k = rand() % list3_int.get_size();
			for (int j = 1; j != k; ++j)
			{
				++i;
			}
			list3_int.del(i);
			cout << "Удаляем элемент номер " << k << endl;
			cout << list3_int << endl;
		}
		cout << "Сортируем лист 3" << endl;
		list3_int.sort_list();
		cout << list3_int << endl;
		cout << "Выведем только четные номера листа 3" << endl;
		DList<int>::Iterator i = list3_int.begin();
		for (size_t _ = 1; _ <= list3_int.get_size() + 1; ++_)
		{
			if (_ % 2 == 0)
				cout << *i << "\t";
			++i;
		}
		cout << endl;
		cout << "Заменим все нечетные номера на 1" << endl;
		i = list3_int.begin();
		for (size_t _ = 1; _ <= list3_int.get_size() + 1; ++_)
		{
			if (_ % 2 == 1)
				list3_int[i] = 1;
			++i;
			list3_int = list3_int;
		}
		cout << list3_int << endl;
		i = list3_int.begin();
		++i; ++i;
		cout << *i << endl;
		list3_int.del(i); 
		cout << list3_int << endl;
		cout << *i << endl;
	}
	catch (MyException &ex)
	{
		cerr << "Error: " << ex.Message() << '\n';
		cerr << "Code: " << ex.Code() << '\n';
	}
}
