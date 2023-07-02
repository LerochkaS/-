#pragma once
#include <iostream>
#include "MyException.h"

template <typename T>
class DList
{
private:
    class Node
    {
    public:
        T value;             //Значение, хранящееся в узле
        Node *prev_, *next_; //Указатели на следующий и предыдущий узлы

        Node(const T &data, Node *Prev = nullptr, Node *Next = nullptr) : value(data), prev_(Prev), next_(Next) {}
        ~Node() {}
        Node(const Node &other) : value(other.value), prev_(other.prev_), next_(other.next_) {}
    };

    Node *begin_, *end_; //Указатели на первый и последний узлы списка
    size_t size;         // Размер списка

public:
    class Iterator
    {
        friend class DList<T>;
    private:
 	DList<T> *ptr_list;
        Node *curr_node;
        int border; // 0 если на внутреннем узле, 1 если до начала, 2 если после конца

	Iterator() : ptr_list(nullptr), curr_node(nullptr), border(1) {}
        Iterator(DList<T> *ptr, Node *curr, int b) : ptr_list(ptr), curr_node(curr), border(b) {}

    public:
        Iterator(const Iterator &other) : ptr_list(other.ptr_list), curr_node(other.curr_node), border(other.border) {}
        ~Iterator() {}

        const T &operator*() const
        {
            if (ptr_list->size == 0)
            {
                throw MyException("Accessing an element outside of the list", RANGE);
            }
            if(curr_node == nullptr)
                throw MyException("Accessing an element outside of the list", RANGE);
            return curr_node->value;
        }

        Iterator &operator++()
        {
            if (ptr_list->size == 0)
                return *this;
            switch (border)
            {
            case 0:
                curr_node = curr_node->next_;
                if (curr_node == nullptr)
                    border = 2;
                break;
            case 1:
                curr_node = ptr_list->begin_;
                border = (curr_node == nullptr) ? 1 : 0;
                break;
            case 2:
                break;
            }
            return *this;
        }

        Iterator &operator--()
        {
            if (ptr_list->size == 0)
                return *this;
            switch (border)
            {
            case 0:
                curr_node = curr_node->prev_;
                if (curr_node == nullptr)
                    border = 1;
                break;
            case 1:
                break;
            case 2:
                curr_node = ptr_list->end_;
                border = (curr_node == nullptr) ? 2 : 0;
                break;
            }
            return *this;
        }

        bool operator!=(const Iterator &other)
        {
            if (ptr_list != other.ptr_list)
                return true;
            if (curr_node != other.curr_node)
                return true;
            if (border != other.border)
                return true;
            return false;
        }

	Iterator& operator=(const Iterator &other)
	{
				border = other.border;
				curr_node = other.curr_node;
				ptr_list = other.ptr_list;
			
		return *this;
	}
    };

    DList() : begin_(nullptr), end_(nullptr), size(0) {}
    DList(const DList<T> &other);
    ~DList();
    /*Получить размер списка*/
    size_t get_size() const { return size; }
    /*Проверка списка на пустоту*/
    bool is_empty() const;
    /*Сортировка по значению*/
    void sort_list();

    /*Добавить узел в конец списка*/
    void push_back(const T &data);
    /*Добавить элемент в начало*/
    void push_front(const T &data);
    /*Добавить узел на текущую позицию, при этом элемент текущей позиции становится предыдущим*/
    void insert(const T &data, Iterator &i);
    /*Удалить первый узел*/
    T pop_front();
    /*Удаляет последний узел */
    T pop_back();
    /*Удалить узел*/
    void del(Iterator &i);
    /*Очистить список от элементов*/
    void clean();

    Iterator begin();
    Iterator end();

    DList<T> &operator=(const DList<T> &other);
    /*Конкатенация*/
    DList<T> operator+(DList<T> &other);
    /*Установить значение по заданному индексу*/
    T &operator[](const Iterator &i);
    /*Вывод списка*/
    template<typename T1>
    friend std::ostream &operator<<(std::ostream &s, const DList<T1> &list);
};

template <typename T>
DList<T>::DList(const DList<T> &other)
{
    size = 0;
    begin_ = end_ = 0;
    Node *temp = other.begin_;
    while (temp)
    {
        push_back(temp->value);
        temp = temp->next_;
    }
}

template <typename T>
bool DList<T>::is_empty() const
{
    if (size == 0)
    {
        return true;
    }
    return false;
}

template <typename T>
DList<T>::~DList<T>()
{
	clean();
}

template <typename T>
void DList<T>::sort_list()
{
    if (size == 0 || size == 1)
        return;
    DList<T>::Iterator cur, nex;
    cur = begin();
    while (cur.curr_node)
    {
        nex = begin();
        while (nex.curr_node)
        {
            if (nex.curr_node->next_)
                if (*nex > nex.curr_node->next_->value)
                {
                    T tmp = nex.curr_node->next_->value;
                    nex.curr_node->next_->value = nex.curr_node->value;
                    nex.curr_node->value = tmp;
                }
            ++nex;
        }
        ++cur;
        if (cur.curr_node)
            nex.curr_node = cur.curr_node->next_;
    }
}

template <typename T>
void DList<T>::push_back(const T &data)
{
    try
    {
        if (begin_ == nullptr)
        {
            begin_ = new Node(data);
            end_ = begin_;
            begin_->prev_ = nullptr;
            end_->next_ = nullptr;
        }
        else
        {
            Node *current = new Node(data);
            end_->next_ = current;
            current->prev_ = end_;
            end_ = current;
        }
        size++;
    }
    catch (std::bad_alloc &err)
    {
        throw MyException("Bad_alloc", MEMORY);
    }
}

template <typename T>
void DList<T>::push_front(const T &data)
{
    try
    {
        Node *current = new Node(data);
        if (begin_ == nullptr)
        {
            begin_ = end_ = current;
            begin_->prev_ = nullptr;
            end_->next_ = nullptr;
        }
        else
        {
            begin_->prev_ = current;
            current->next_ = begin_;
            begin_ = current;
        }
        size++;
    }
    catch (std::bad_alloc &err)
    {
        throw MyException("Bad_alloc", MEMORY);
    }
}

template <typename T>
void DList<T>::insert(const T &data, Iterator &i)
{
    try
    {
        if (i.border == 2)
            return;
        Node *current = new Node(data);
        switch (i.border)
        {
        case 1:
            push_front(data);
            break;
        case 0:
            current->next_ = i.curr_node->next_;
            current->prev_ = i.curr_node;
            if (i.curr_node != end_)
                i.curr_node->next_->prev_ = current;
            i.curr_node->next_ = current;
            size++;
            break;
        }
    }
    catch (std::bad_alloc &err)
    {
        throw MyException("Bad_alloc", MEMORY);
    }
}

template <typename T>
T DList<T>::pop_front()
{
    if (is_empty())
        throw MyException("Trying to get an element of an empty list", RANGE);
    T term = begin_->value;
    if (size == 1)
    {
        delete begin_;
        begin_ = nullptr;
        end_ = nullptr;
        size--;
    }
    else
    {
        Node *ptr = begin_;
        begin_ = begin_->next_;
        begin_->prev_ = nullptr;
        delete ptr;
        size--;
    }
    return term;
}

template <typename T>
T DList<T>::pop_back()
{
    if (is_empty())
        throw MyException("Trying to get an element of an empty list", RANGE);
    T term = end_->value;
    if (size == 1)
    {
        delete end_;
        begin_ = nullptr;
        end_ = nullptr;
        size--;
    }
    else
    {
        Node *ptr = end_;
        end_ = end_->prev_;
        end_->next_=nullptr;
        delete ptr;
        size--;
    }
    return term;
}

template <typename T>
void DList<T>::del(Iterator &i)
{
    if (i.border == 1 || i.border == 2)
        return;
    size--;
    if (i.curr_node == begin_)
        pop_front();
    else if (i.curr_node == end_)
        pop_back();
    else if (i.border == 0)
    {
	Node *n = i.curr_node->next_;
	int k = (n == nullptr) ? 2 : 0; 
        i.curr_node->prev_->next_ = i.curr_node->next_;
        i.curr_node->next_->prev_ = i.curr_node->prev_;
        delete i.curr_node; 
	i = Iterator(this, n, k);
    }
}

template <class T>
typename DList<T>::Iterator DList<T>::begin()
{
    int b = (begin_ == nullptr) ? 1 : 0;
    return Iterator(this, begin_, b);
}

template <class T>
typename DList<T>::Iterator DList<T>::end()
{
    int b = 2;
    return Iterator(this, nullptr, b);
}

template <typename T>
DList<T> &DList<T>::operator=(const DList<T> &other)
{
    if (this != &other)
    {
        while (begin_)
        {
            end_ = begin_->next_;
            delete begin_;
            begin_ = end_;
            size--;
        }
        Node *temp = other.begin_;
        while (temp != nullptr)
        {
            push_back(temp->value);
            temp = temp->next_;
        }
    }
    return *this;
}

template <typename T>
DList<T> DList<T>::operator+(DList<T> &other)
{
    DList<T> to_return;
    for (Iterator i = begin(); i != end(); ++i)
    {
        to_return.push_back(*i);
    }
    for (Iterator i = other.begin(); i != other.end(); ++i)
    {
        to_return.push_back(*i);
    }
    return to_return;
}

template <typename T>
T &DList<T>::operator[](const Iterator &i)
{
    if (i.border == 1 || i.border == 2)
        throw MyException("Accessing an element outside of the list", RANGE);
    return i.curr_node->value;
}

template <typename T>
std::ostream &operator<<(std::ostream &s, DList<T> &list)
{
    if(list.get_size() == 0)
        s << "List is empty \t";
    else
    {
    for(typename DList<T>::Iterator i = list.begin(); i != list.end(); ++i)
    {
        s << *i << "\t";
    }
    }
	return s;
}

template <typename T>
void DList<T>::clean()
{
    while (begin_)
    {
        end_ = begin_->next_;
        delete begin_;
        begin_ = end_;
    }
    size = 0;
}
