// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *nil;
public:
    DoubleList();
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return nil->next == nil;}
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return nil->next->value; } // zwraca poczatek, nie usuwa
    T& back() const { return nil->prev->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void reverse(); // odwraca liste O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const; // dostep do obiektu const
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
DoubleList<T>::DoubleList() {
    nil = new DoubleNode<T>(); // wartownik
    nil->next = nil;
    nil->prev = nil;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    DoubleNode<T> *node = new DoubleNode<T>(item, nil->next, nil);
    nil->next->prev = node;
    nil->next = node;
}

template <typename T>
void DoubleList<T>::pop_front() {
    assert(!empty());
    DoubleNode<T> *node = nil->next; // zapamiętujemy
    node->next->prev = node->prev; // ogólny schemat usuwania
    node->prev->next = node->next;
    // Przywracanie usuniętego węzła [Knuth]:
    // node->next->prev = node;
    // node->prev->next = node;
    delete node;
}

/*
Zmienić klasę DoubleList przez wprowadzenie wartownika, czyli sztucznego węzła 
łączącego głowę i ogon listy powiązanej podwójnie. W ten sposób powstaje lista cykliczna, 
co upraszcza wstawianie i usuwanie węzłów. 
W klasie DoubleList wystarczy przechowywać tylko łącze do wartownika.
*/

template <typename T>
DoubleList<T>::~DoubleList()
{
    while(!empty())
    {
        pop_front();
    }
}
template <typename T>
int DoubleList<T>::size() const // O(n) bo trzeba policzyc
{
    int size = 0;
    DoubleNode<T> *node = nil->next;
    while(node!= nil)
    {
        size++;
        node = node->next;
    }

    return size;
}

template <typename T>
void DoubleList<T>::push_back(const T& item) // O(1)
{
    if(empty()) // pusta tablica
    {
        DoubleNode<T> *node = new DoubleNode<T>(item, nil, nil);
        nil->next = nil->prev = node;
    }else{
        DoubleNode<T> *node = new DoubleNode<T>(item, nil, nil->prev);
        nil->prev->next = node;
        nil->prev = node;
    }

}

template <typename T>
void DoubleList<T>::clear()
{
    while(!empty()) pop_front();
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) // copy constructor
{
    if(this != &other)
    {
        if(other.size() == 0)
        {
            nil = new DoubleNode<T>(); // wartownik
            nil->next = nil;
            nil->prev = nil;
        }
        else{
            for(DoubleNode<T> *node = other.nil->next; node != other.nil;)
            {
                push_back(node->value);
                node = node->next;
            }
        }
    }

}
template <typename T>
DoubleList<T>::DoubleList(DoubleList&& other)
{
    if(this != &other)
    {
        std::swap(nil, other.nil);
    }

}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other)
{
    if(this != &other)
    {
        clear();

        for(DoubleNode<T> *node = other.front(); node != other.back();)
        {
            push_back(node->value);
            node = node->next;
        }

    }

    return *this;
}

template <typename T>
void DoubleList<T>::display()
{
    DoubleNode<T> *node = nil->next;
        
    while(node != nil)
    {
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout<<"\n";
}

template <typename T>
void DoubleList<T>::display_reversed()
{
    DoubleNode<T> *node = nil->prev;
        
    while(node != nil)
    {
        std::cout << node->value << " ";
        node = node->prev;
    }
    std::cout<<"\n";

}

template <typename T>
void DoubleList<T>::pop_back()
{
    assert(!empty());
    if(nil->next == nil->prev)
    {
        DoubleNode<T> *node = nil->next;
        nil->next = nil->prev = nil;
        delete node;
    }
    else{
        DoubleNode<T> *node = nil->prev;
        nil->prev = node->prev;
        node->prev->next = nil;
        delete node;
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    push_front(item);
}

template <typename T>
void DoubleList<T>::push_back(T&& item) {
    push_back(item);
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& other)
{
    if(this != &other)
    {
        std::swap(nil = other.nil);
    }

    return *this;
}

template <typename T>
T& DoubleList<T>::operator[](int pos) // podstawienie L[pos]=item, odczyt L[pos]
{
    assert(pos >= 0 && pos < size());

    DoubleNode<T> *node = nil->next;

    for(auto i = 0; i < pos; ++i)
    {
        node = node->next;
    }

    return node->value;

}

template <typename T>
const T& DoubleList<T>::operator[](int pos) const // dostep do obiektu const
{
    assert(pos >= 0 && pos < size());

    DoubleNode<T> *node = nil->next;

    for(auto i = 0; i < pos; ++i)
    {
        node = node->next;
    }

    return node->value;

}

template <typename T>
void DoubleList<T>::erase(int pos)
{
    assert(pos >= 0 && pos < size());

    if(pos == 0) pop_front();
    else if (pos == size() - 1) pop_back();
    else
    {
        DoubleNode<T> *node =  nil->next;

        for(auto i = 0; i < pos; ++i)
        {
            node = node->next;
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;   
    } 
}

template <typename T>
int DoubleList<T>::index(const T& item) // jaki index na liscie (-1 gdy nie ma) O(n)
{
    DoubleNode<T> *node =  nil->next;
    int index = 1;

    if(item == node->value) return 0;
    else node = node->next;

    while(node !=  nil)
    {
        if(item == node->value) return index;
        node = node->next;
        index++;
    }

    return -1;
}

template <typename T>
void DoubleList<T>::insert(int pos, const T& item) // inserts item before pos,
{
    assert(pos >= 0 && pos < size() + 1);
    if(pos == 0) push_front(item);
    else if (pos == size()) push_back(item);
    else{
        DoubleNode<T> *node = nil->next;
        DoubleNode<T> *temp;

        for(int i=0 ;i < pos; ++i)
        {
            node = node->next;
        }
        temp = new DoubleNode<T>(item, node, node->prev);
        node->prev->next = temp;
        node->prev = temp;
    }
}

template <typename T>
void DoubleList<T>::insert(int pos, T&& item)// inserts item before pos,
{
    assert(pos >= 0 && pos < size() + 1);
    if(pos == 0) push_front(std::move(item));
    else if (pos == size()) push_back(std::move(item));
    else
    {
        DoubleNode<T> *node = nil->next;
        DoubleNode<T> *temp;

        for(int i=0 ;i < pos; ++i)
        {
            node = node->next;
        }
        temp = new DoubleNode<T>(std::move(item), node, node->prev);
        node->prev->next = temp;
        node->prev = temp;
    }

}

#endif

// EOF