#ifndef LIST_H
#define LIST_H

#include "FOSCore.h"

namespace FOS
{

template <typename T>
class List
{
public:
    List();

    void clear();

    const T &at(int i) const;
    const T &operator[](int i) const;
    T &operator[](int i);

    void reserve(int size);
    void append(const T &t);
    void append(const List<T> &t);
    void prepend(const T &t);
    void insert(int i, const T &t);
    void replace(int i, const T &t);
    void removeAt(int i);
    int removeAll(const T &t);
    bool removeOne(const T &t);
    T takeAt(int i);
    T takeFirst();
    T takeLast();
    void move(int from, int to);
    void swap(int i, int j);
    int indexOf(const T &t, int from = 0) const;
    int lastIndexOf(const T &t, int from = -1) const;
    bool contains(const T &t) const;
    int count(const T &t) const;

private:
    void link();
private:
    T* data;
    size_t length;
    List *next;
};

}

#endif // LIST_H
