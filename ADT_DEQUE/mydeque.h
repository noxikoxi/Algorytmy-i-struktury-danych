// mydeque.h

#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyDeque {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyDeque(int s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor

    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other); // copy constructor
    MyDeque(MyDeque&& other); // move constructor NIEOBOWIĄZKOWE

    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this
    MyDeque& operator=(MyDeque&& other); // move assignment operator, return *this NIEOBOWIĄZKOWE

    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }

    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize-1; }

    void push_front(const T& item); // dodanie na początek O(1)
    void push_front(T&& item); // dodanie na początek O(1) NIEOBOWIĄZKOWE
    void push_back(const T& item); // dodanie na koniec O(1)
    void push_back(T&& item); // dodanie na koniec O(1) NIEOBOWIĄZKOWE

    T& front() { assert(tab != nullptr); return tab[head]; } // zwraca poczatek
    T& back() { assert(tab != nullptr); return tab[(tail + msize -1) % msize]; } // zwraca koniec

    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)

    void clear(); // czyszczenie listy z elementow
    void display();

    // Operacje z indeksami. NIEOBOWIĄZKOWE
    // T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    // const T& operator[](int pos) const; // dostęp do obiektu const

    // void erase(int pos);
    // int index(const T& item); // jaki index na liście (-1 gdy nie ma)
    // void insert(int pos, const T& item); // inserts item before pos
    // void insert(int pos, T&& item); // inserts item before pos
};

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());

    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());

    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::display() {
    if(size() != 0)
    {
        for (int i = head; i != tail; i=(i+1) % msize) {
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    } else std::cout <<"pusty\n";
}

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) // copy constructor
{
    if(this != &other)
    {
        tab = new T[other.msize];
        head = tail = 0;
        assert(tab != nullptr); // alokacja pamieci sie nie udala
        
        for(auto i = other.head; i != other.tail; i = (i+1) % other.msize)
        {
            push_back(other.tab[i]);
        }

        msize = other.msize;

    }

}

template <typename T>
MyDeque<T>::MyDeque(MyDeque&& other) // move constructor NIEOBOWIĄZKOWE
{
    if(this != &other)
    {
        // podmiana
        tab = nullptr;
        std::swap(tab, other.tab);
        
        head = other.head;
        tail = other.tail;
        msize = other.msize;

        // czyszczenie
        other.head = other.tail = 0;
        other.msize = 1;
    }

}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) // copy assignment operator, return *this
{
    if(this != &other)
    {
        delete [] tab;
        
        tab = new T[other.msize];
        head = tail = 0;
        assert(tab != nullptr); // alokacja pamieci sie nie udala
 
        for(auto i = other.head; i != other.tail; i = (i+1) % other.msize)
        {
            push_back(other.tab[i]);
        }

        msize = other.msize;

    }

    return *this;
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(MyDeque&& other) // move assignment operator, return *this NIEOBOWIĄZKOWE
{
    if(this != &other)
    {
        // podmiana
        tab = nullptr;
        std::swap(tab, other.tab);
        
        head = other.head;
        tail = other.tail;
        msize = other.msize;

        // czyszczenie
        other.head = other.tail = 0;
        other.msize = 1;
    }

    return *this;
}

template <typename T>
void MyDeque<T>::push_front(T&& item) // dodanie na początek O(1) NIEOBOWIĄZKOWE
{
    assert(!full());

    head = (head + msize -1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(T&& item) // dodanie na koniec O(1) NIEOBOWIĄZKOWE
{
    assert(!full());

    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_front() // usuwa początek kolejki O(1)
{
    assert(!empty());

    tab[head] = T();
    head = (head + msize +1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() // usuwa koniec kolejki O(1)
{
    assert(!empty());

    tab[tail - 1] = T();
    tail = (tail - 1) % msize;
}

template <typename T>
void MyDeque<T>::clear() // czyszczenie listy z elementow
{
    for (int i = head; i != tail; i=(i+1) % msize) {
        tab[i] = T();
    }

    head = tail = 0;

}
#endif

// EOF