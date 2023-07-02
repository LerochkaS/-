#pragma once
#include <vector>
#include <cmath>
#include <fstream>
#include "Exception.h"

struct Node
{
    double key_;                // ключ - значение по x
    std::vector<double> value_; // вектор значений по y для одинаковых ключей

    Node *left_;  // Указатель на левое поддерево
    Node *right_; // указатель на правое поддерево
    char len_;    // высота поддерева

    Node(double key, double value, Node *left = nullptr, Node *right = nullptr, char len = 1)
    {
        key_ = round(key * 10) / 10;
        value_.push_back(round(value * 10) / 10);
        left_ = left;
        right_ = right;
        len_ = len;
    }

    Node(double key, std::vector<double> value, Node *left = nullptr, Node *right = nullptr, char len = 1)
    {
        key_ = round(key * 10) / 10;
        value_ = value;
        left_ = left;
        right_ = right;
        len_ = len;
    }

    ~Node() {}
    Node(const Node &other)
    {
        key_ = other.key_;
        value_ = other.value_;
        left_ = other.left_;
        right_ = other.right_;
        len_ = other.len_;
    }

    /* Балансировка (нереальная) */
    Node *RightRotate();
    Node *LeftRotate();
    Node *Balance();

    /* Удаление по ключу первое значение из списка */

    Node *RemoveMin();

    char length(Node *node) const { return (node ? node->len_ : 0); }
    char factor() const { return (length(right_) - length(left_)); }
    void fixlen();
};

class Balance_tree
{
private:
    Node *root_;
    size_t size_;

    Node *FindMin(Node *root);
    Node *FindMax(Node *root);
    Node *Postordettrav(Node *root, Node *(*func)(Node *cur, Node *left, Node *right)) const; // обход дерева

    Node *find(Node *root, double key) const;

    Node *Remove(Node *root, double key, double y);

public:
    Balance_tree()
    {
        root_ = nullptr;
        size_ = 0;
    }
    Balance_tree(double key, double value);
    ~Balance_tree() { clear(root_); }
    Balance_tree(const Balance_tree &other);

    void swap(Balance_tree &other) { std::swap(root_, other.root_); }
    /* Операторы (и так ясно что это операторы, просто с комментарием красивее) */
    Balance_tree operator=(Balance_tree other)
    {
        swap(other);
        return *this;
    }

    double operator[](double key);

    /* Вставить по ключу, возвращает указатель на вставленный узел */
    Node *Insert(Node *root, double key, double value);
    /* Удаление по ключу первое значение из списка */
    size_t Erase(double key, double y);
    /* Напечатать дерево */
     void print(Node *node, int spaces) const;
    /* Есть ли элементв  дереве */
    bool Find(Node *root, double key, double y) const;
    Node *get_root() const { return root_; }
    /* Очистить дерево */
    void clear(Node *node);
    size_t get_size() const { return size_; }
};

class SetR2
{
    friend class Balance_tree;

private:
    double section_;                                  // количество делений (типа дабл потому что если не дабл будет предупреждение)
    double low_;                                      // нижняя граница окрестности
    double up_;                                       // верхняя граница окрестности
    std::vector<std::pair<double, Balance_tree>> set; // вектор пар {область деления, сбалансированное дерево}
    size_t quant_ = 0;                                // количество точек в множестве
    std::pair<double, double> center_;                // центр множества

    SetR2();

public:
    /* EPS - окрестность точки, center - центральная точка, section - количество разбиений оси oY*/
    SetR2(double EPS, std::pair<double, double> center, double section);
    /* Формат файла: eps (окрестность точки), центральная точка, количество разбиений оси oY, далее множество точек из окрестности в виде (x, y)*/
    SetR2(std::ifstream &inp);
    SetR2(const SetR2 &other);
    ~SetR2();

    SetR2 operator=(const SetR2 &other);

    /* Добавление точки в множество */
    bool add(double x, double y);
    /* Удаление точки из множества */
    bool del(double x, double y);
    /* Принадлежит ли точка множеству */
    bool is_here(double x, double y) const;
    /* Получить размер множества */
    size_t get_quant() const { return quant_; }
};

/*---------------------------------------------------AVL-TREE------------------------------------------------------------------*/
Balance_tree::Balance_tree(double key, double value)
{
    try
    {
        root_ = new Node(round(key * 10) / 10, round(value * 10) / 10);
        size_++;
    }
    catch (std::bad_alloc &err)
    {
        throw MyException("Bad_alloc", MEMORY);
    }
}

double Balance_tree::operator[](double key)
{
    return find(root_, key)->value_[0];
}

Balance_tree::Balance_tree(const Balance_tree &other)
{
    size_ = other.size_;
    root_ = other.Postordettrav(other.root_, [](Node *cur, Node *left, Node *right)
                                {
		try {
			return new Node(cur->key_, cur->value_, left, right, cur->len_);
		}
		catch(const std::bad_alloc &e) {
			throw MyException("Не удалось выделить память", MEMORY);
		} });
}

void Balance_tree::clear(Node *node)
{
    root_ = Postordettrav(node, [](Node *cur, Node *left, Node *right)
                          {
        delete cur;
        return left; });
}

void Node::fixlen()
{
    len_ = (length(left_) > length(right_) ? length(left_) : length(right_)) + 1;
}

/* Реализация балансировок */
Node *Node::RightRotate()
{
    Node *nr = left_;
    left_ = left_->right_;
    nr->right_ = this;
    this->fixlen();
    nr->fixlen();
    return nr;
}

Node *Node::LeftRotate()
{
    Node *nr = right_;
    right_ = right_->left_;
    nr->left_ = this;
    this->fixlen();
    nr->fixlen();
    return nr;
}

Node *Node::Balance()
{
    fixlen();
    if (factor() == 2)
    {
        if (right_->factor() < 0)
            right_ = right_->RightRotate();
        return LeftRotate();
    }
    if (factor() == -2)
    {
        if (left_->factor() > 0)
            left_ = left_->LeftRotate();
        return RightRotate();
    }
    return this;
}

Node *Balance_tree::FindMin(Node *root)
{
    while (root && root->left_)
        root = root->left_;
    return root;
}

Node *Balance_tree::FindMax(Node *root)
{
    while (root && root->right_)
        root = root->right_;
    return root;
}

Node *Balance_tree::Postordettrav(Node *root, Node *(*func)(Node *cur, Node *left, Node *right)) const
{
    if (!root)
        return nullptr;
    Node *left = Postordettrav(root->left_, func);
    Node *right = Postordettrav(root->right_, func);
    return func(root, left, right);
}

Node *Balance_tree::Insert(Node *root, double key, double value)
{
    if (!root)
    {
        try
        {
            Node *nn = new Node(key, value);
            if(size_ == 0)
                root_ = nn;
            ++size_;
            return nn;
        }
        catch (std::bad_alloc &err)
        {
            throw MyException("Bad_alloc", MEMORY);
        }
    }
    if (round(key * 10) / 10.0 < root->key_)
        root->left_ = Insert(root->left_, key, value);
    else if (round(key * 10) / 10.0 > root_->key_)
        root->right_ = Insert(root->right_, key, value);
    else if (round(key * 10) / 10.0 == root->key_)
    {
        root->value_.push_back(value);
    }
    return root->Balance();
}
Node *Node::RemoveMin()
{
    if (left_ == nullptr)
        return right_;
    left_ = left_->RemoveMin();
    return Balance();
}

Node *Balance_tree::Remove(Node *root, double key, double y)
{
    // static Node* parent;
    if (!root)
        return root;
    if (round(key * 10) / 10 < root->key_)
        root->left_ = Remove(root->left_, key, y);
    else if (round(key * 10) / 10 > root->key_)
        root->right_ = Remove(root->right_, key, y);
    else if (round(key * 10) / 10 == root->key_)
    {
        for (size_t i = 0; i < root->value_.size(); ++i)
        {
            if (root->value_[i] == y)
            {
                Node *l = root->left_;
                Node *r = root->right_;
                if (root->value_.size() == 1)
                {
                    delete root;
                }
                else
                {
                    root->value_.erase(root->value_.begin() + i);
                }
                size_--;
                if (!r)
                    return l;
                Node *min = FindMin(r);
                min->right_ = r->RemoveMin();
                min->left_ = l;
                return min->Balance();
            }
        }
    }
    return root->Balance();
}

/*void Balance_tree::print(Node *node, int spaces = 0) const
{
    if (node)
    {

        for (size_t i = 0; i < node->value_.size(); ++i)
        {
            std::cout << "(" << node->key_ << ";" << node->value_[i] << ") ";
        }
        // spaces += 5;
        std::cout << "\n";
        print(node->left_, spaces);
        for (size_t i = 0; i < spaces + 5; ++i)
        {
            std::cout << " ";
        }
        spaces += 5;
        print(node->right_, spaces);
    }
}*/

Node *Balance_tree::find(Node *root, double key) const
{
    if (root)
    {
        if (key < root->key_)
            return find(root->left_, key);
        else if (key > root->key_)
            return find(root->right_, key);
        else if (key == root->key_)
            return root;
    }
    return nullptr;
}

bool Balance_tree::Find(Node *root, double key, double y) const
{
    if (root)
    {
        if (key < root->key_)
            return Find(root->left_, key, y);
        else if (key > root->key_)
            return Find(root->right_, key, y);
        else if (key == root->key_)
        {
            for (size_t i = 0; i < root->value_.size(); ++i)
            {
                if (root->value_[i] == y)
                    return true;
            }
        }
    }
    return false;
}


size_t Balance_tree::Erase(double key, double y)
{
    size_t prev = size_;
    root_ = Remove(root_, key, y);
    return prev - size_;
}
/*------------------------------------------------------------SetR2---------------------------------------------------------------*/

SetR2::SetR2(double EPS, std::pair<double, double> center, double section)
{
    section_ = section;
    low_ = center.second - EPS;
    up_ = center.second + EPS;
    center_ = center;
    for (size_t _ = 0; _ <= section; ++_)
    {
        set.push_back({(low_ + ((up_ - low_) / section_) * _), Balance_tree()});
    }
    add(center_.first, center_.second);
}

SetR2::SetR2(std::ifstream &inp)
{
    if (inp.is_open())
    {
        double EPS;
        inp >> EPS;
        inp >> center_.first;
        inp >> center_.second;
        low_ = center_.second - EPS;
        up_ = center_.second + EPS;
        inp >> section_;
        center_ = center_;
        for (size_t _ = 0; _ <= section_; ++_)
        {
        set.push_back({(low_ + ((up_ - low_) / section_) * _), Balance_tree()});
        }
        add(center_.first, center_.second);
        while (!EOF)
        {
        double x, y;
        inp >> x;
        inp >> y;
        if (y < low_ || y > up_)
            break;
        for (size_t _ = 0; _ < section_; ++_)
        {
            if (y >= set[_].first && y < set[_].first)
                add(x, y);
        }
        }
    }
    else
    {
        throw MyException("Не удалось открыть файл", -1);
    }
}

SetR2::~SetR2()
{
    /*for (size_t _ = 0; _ < section_; ++_)
    {
        std::cout << "В деструкторе i" << std::endl;
        set[_].second.clear(set[_].second.get_root());

    }*/
    set.clear();
}

SetR2::SetR2(const SetR2 &other)
{
    section_ = other.section_;
    low_ = other.low_;
    up_ = other.up_;
    for (size_t _ = 0; _ < section_; ++_)
    {
        set.push_back({other.set[_].first, Balance_tree(other.set[_].second)});
    }
}

SetR2 SetR2::operator=(const SetR2 &other)
{
    if (this != &other)
    {
        for (size_t _ = 0; _ < section_; ++_)
        {
        set[_].second.clear(set[_].second.get_root());
        }
        set.clear();
        section_ = other.section_;
        low_ = other.low_;
        up_ = other.up_;
        for (size_t _ = 0; _ < section_; ++_)
        {
        set.push_back({other.set[_].first, Balance_tree(other.set[_].second)});
        }
    }
    return *this;
}

bool SetR2::add(double x, double y)
{
    if (y < low_ || y > up_)
        return false;
    else
    {
        for (size_t _ = 0; _ <= section_; ++_)
        {
        if (y >= set[_].first && y < set[_ + 1].first)
        {
            set[_].second.Insert(set[_].second.get_root(), x, y);
            quant_++;
            return true;
        }
        }
        return false;
    }
}

bool SetR2::del(double x, double y)
{
    if (y < low_ || y > up_)
        return false;
    else
    {
        for (size_t _ = 0; _ < section_; ++_)
        {
        if (y >= set[_].first && y < set[_ + 1].first)
        {
            if (set[_].second.Erase(x, y) == 1)
            {
                quant_--;
                return true;
            }
            else
            {
                return false;
            }
        }
        }
        return false;
    }
}

bool SetR2::is_here(double x, double y) const
{
    for (size_t _ = 0; _ < section_; ++_)
    {
        if (y >= set[_].first && y < set[_ + 1].first)
        {
        if (set[_].second.Find(set[_].second.get_root(), x, y))
        {
            return true;
        }
        }
    }
    return false;
}

/*void SetR2::print() const
{
    for(size_t i = 0; i < section_; ++i)
    {
        set[i].second.print(set[i].second.get_root());
    }
}*/
