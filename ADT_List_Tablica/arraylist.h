// arraylist.h

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <algorithm> // sort


template <typename T>
class ArrayList {
    T* tab;
    size_t msize; // najwieksza mozliwa liczba elementow
    size_t last; // pierwsza wolna pozycja
    constexpr static size_t MIN_SIZE = 4;
    constexpr static size_t EXTEND_VAL = 4;

    void extendArray(); // rozszerza tablice
    void reduceArray(size_t size); // zmniejsza tablice
    void checkSize();

public:
    ArrayList(size_t s=MIN_SIZE) : msize(s), last(0) {
        assert( s >= MIN_SIZE );
        tab = new T[s];
        assert( tab != nullptr );
    } // default constructor
    ArrayList(const ArrayList& other); // copy constructor
    // usage:   ArrayList<int> list2(list1);
    ArrayList(ArrayList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   ArrayList<int> list2(std::move(list1));
    
    ~ArrayList() { delete [] tab; }

    ArrayList& operator=(const ArrayList& other); // copy assignment operator, return *this
    // usage:   list2 = list1; 
    ArrayList& operator=(ArrayList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return last == 0; } // checks if the container has no elements
    bool full() const { return last == msize; } // checks if the container is full
    int size() const { return last; } // liczba elementow na liscie
    int max_size() const { return msize; } // najwieksza mozliwa liczba elementow

    void push_front(const T& item); // dodanie na poczatek
    void push_front(T&& item); // dodanie na poczatek NIEOBOWIAZKOWE
    void push_back(const T& item); // dodanie na koniec
    void push_back(T&& item); // dodanie na koniec NIEOBOWIAZKOWE

    T& front(); // zwraca poczatek, nie usuwa, error dla pustej listy
    T& back(); // zwraca koniec, nie usuwa, error dla pustej listy

    void pop_front(); // usuwa poczatek, error dla pustej listy
    void pop_back(); // usuwa koniec, error dla pustej listy

    void clear(); // czyszczenie listy z elementow
    void display(); // lepiej zdefiniowac operator<<
    void reverse(); // odwracanie kolejnosci
    void sort(); // sortowanie listy

    void merge(ArrayList& other); //  merges two sorted lists into one
    // Operacje z indeksami. NIEOBOWIAZKOWE
    // https://en.cppreference.com/w/cpp/language/operators
    // Array subscript operator

    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]

    void erase(int pos); // usuniecie elementu na pozycji pos
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma)

    void insert(int pos, const T& item); // inserts item before pos
    void insert(int pos, T&& item); // inserts item before pos
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (size_t i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        os << "\n";
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

/*
Zadanie 3.2
Przygotować implementację realizującą ADT LIST na bazie tablicy o zmieniającym się rozmiarze. 
Będzie to klasa ArrayList umieszczona w pliku arraylist.h. Początkowy rozmiar tablicy (min_size)
może wynosić 2 lub 4. Po zapełnieniu tablicy rozmiar może się powiększać o stałą wartość 
lub może się podwajać (wybrać jedną możliwość). 
Po usunięciu pewnej liczby elementów tablica może się zmniejszać, 
aż do osiągnięcia początkowego rozmiaru minimalnego.
*/

// funkcja rozszerza tablice
template<typename T>
void ArrayList<T>::extendArray()
{
    T* p = new T[this->msize + this->EXTEND_VAL]; // alokuje pamiec na wieksza tablice

    std::copy(this->tab, this->tab + this->msize, p); // kopiuje do niej elementy

    this->msize += this->EXTEND_VAL; // zwiekszamy max mozliwa ilosc elementow

    delete[] this->tab; // usuwam stara tablice

    this->tab = p; // ustawiam wskaznik tablicy na p
}

template<typename T>
void ArrayList<T>::checkSize()
{
    if(this->last == this->msize) // Brak miejca na nowy element
        this->extendArray();
}

// funkcja zmniejszajaca tablice
template<typename T>
void ArrayList<T>::reduceArray(size_t size)
{
    T* p = new T[size];

    std::copy(this->tab, this->tab + last, p);
    delete[] this->tab;

    this->tab = p;
    this->msize = size;
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) // copy constructor
{
    this->tab = new T[other.msize]; // alokuje pamiec na nowa tablice

    std::copy(other.tab, other.tab + other.last, this->tab); // kopiowanie tablicy

}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) // copy assignment operator, return *this
{
    if(this != &other) // jezeli są to te same obiekty bez sensu cos robic
    {
        delete[] this->tab;  // usuwam stara tablice
        this->msize = other.msize;
        this->last = other.last;

        tab = new T[msize]; // alokacja pamieci
    
        std::copy(this->tab, this->tab + this->last+1, other.tab);
    }

    return *this;
}

template<typename T>
void  ArrayList<T>::push_front(const T& item) // dodanie na poczatek
{
    this->checkSize(); // Brak miejca na nowy element
       
    std::copy_backward(this->tab, this->tab + this->last+1, this->tab+last+2); // przenoszenie na 2 pozycje
    this->tab[0] = item;
    this->last++;

}

template<typename T>
void  ArrayList<T>::push_back(const T& item) // dodanie na koniec
{
    this->checkSize(); // Brak miejca na nowy element

    this->tab[this->last++] = item;
}

template<typename T>
T& ArrayList<T>::front() // zwraca poczatek, nie usuwa, error dla pustej listy
{
    assert(last >= 0);

    return this->tab[0];
}

template<typename T>
T& ArrayList<T>::back() // zwraca koniec, nie usuwa, error dla pustej listy
{
    assert(last >= 0);

    return this->tab[this->last-1];
}

template<typename T>
void ArrayList<T>::pop_front() // usuwa poczatek, error dla pustej listy
{
    assert(last >= 0);

    std::copy(this->tab+1, this->tab + this->last, this->tab);
    this->last--;

    if(this->msize - this->last > this->EXTEND_VAL) // Jezeli sa wiecej niz 4 wolne mniejsza zmniejszam tab
        this->reduceArray(this->msize - this->EXTEND_VAL);

}

template<typename T>
void ArrayList<T>::pop_back() // usuwa koniec, error dla pustej listy
{
    assert(last >= 0);

    this->tab[--(this->last)] = T();

    if(this->msize - this->last > this->EXTEND_VAL) // Jezeli sa wiecej niz 4 wolne mniejsza zmniejszam tab
        this->reduceArray(this->msize-this->EXTEND_VAL);
}

template<typename T>
void ArrayList<T>::clear() // czyszczenie listy z elementow
{
    for(auto i = 0lu; i < this->last; i++)
        this->tab[i] = T();

    this->last = 0;

    // zmniejszanie tablicy
    delete[] this->tab;
    this->tab = new T[this->MIN_SIZE];
}

template<typename T>
void ArrayList<T>::display() // wyswietla tablice
{
    for(auto i = 0lu; i < this->last; i++)
        std::cout << this->tab[i] << " ";

    std::cout << "\n";
}

template<typename T>
void ArrayList<T>::reverse() // odwracanie kolejnosci
{
    for(auto i = 0lu, j = this->last-1; i < j; i++, j--)
        std::swap(this->tab[i], this->tab[j]);
        
}

template<typename T>
void ArrayList<T>::sort() // sortowanie listy
{
    std::sort(this->tab, this->tab+this->last);
}

template<typename T>
T& ArrayList<T>::operator[](int pos) // podstawienie L[pos]=item
{
    assert(pos >= 0 && (size_t)pos < this->last);
    return this->tab[pos];
}

template<typename T>    
const T& ArrayList<T>::operator[](int pos) const // odczyt L[pos]
{
    if(pos >= 0 && pos < this->last) return T();
    return this->tab[pos];
}

template<typename T>
void ArrayList<T>::erase(int pos) // usuniecie elementu na pozycji pos
{
    assert(pos >= 0 && (size_t)pos < this->last);

    if(pos == 0) this->pop_front();
    else if((size_t)pos == this->last-1) this->pop_back();
    else
    {
        std::copy(this->tab + pos + 1, this->tab + last-1, this->tab + pos);

    }

    if(this->msize - this->last > this->EXTEND_VAL) // Jezeli sa wiecej niz 4 wolne mniejsza zmniejszam tab
        this->reduceArray(this->msize-this->EXTEND_VAL);
}

template<typename T>
int ArrayList<T>::index(const T& item) // jaki index na liscie (-1 gdy nie ma)
{
    for(auto i = 0lu; i < this->last-1; i++)
        if(this->tab[i] == item)
            return i;

    return -1;
}

// Jezeli pos=0, to wstawiamy na poczatek.
// Jezeli pos=size(), to wstawiamy na koniec.
template<typename T>
void ArrayList<T>::insert(int pos, const T& item) // inserts item before pos
{
    assert((size_t)pos < this->msize && pos >= 0);

    this->checkSize(); // Brak miejca na nowy element

    if(pos == 0) this->push_front(item);
    else if ((size_t)pos == this->msize) this->push_back(item);
    else
    {
        this->last++;
        std::copy_backward(this->tab + pos, this->tab + this->last, this-> tab + this->last+1);
        this->tab[pos] = item;
    }

}

//  merges two sorted lists into one
template<typename T>
void ArrayList<T>::merge(ArrayList& other)
{
    this->msize = this->last + other.last;
    T* p = new T[this->msize];

    std::copy(this->tab, this->tab + this->last, p);

    delete[] this->tab;
    this->tab = p;

    for(auto i = 0u; i < other.last; i++)
        this->push_back(other.tab[i]);

    this->last = this->msize;
}

/* ***********************************

    Nieobowiazkowe (dla std::move)

************************************** */
template<typename T>
void ArrayList<T>::insert(int pos, T&& item) // inserts item before pos
{
    this->insert(pos, item);
    item = T();
}

template<typename T>
ArrayList<T>::ArrayList(ArrayList&& other) : msize(other.msize), last(other.last)
{
    assert(this != &other);
    
    this->tab = other.tab;
    other.tab = nullptr;
    other.msize = 0;
    other.last = 0;
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other)
{
    assert(this != &other);

    this->tab = other.tab;
    this->msize = other.msize;
    this->last = other.last;

    other.last = 0;
    other.msize = 0;
    other.tab = nullptr;

    return *this;

}

template<typename T>
void ArrayList<T>::push_front(T&& item)
{
    this->push_front(item);
    item = T();
}

template<typename T>
void ArrayList<T>::push_back(T&& item)
{
    this->push_back(item);
    item = T();
}

// EOF