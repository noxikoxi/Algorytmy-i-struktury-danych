// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct SingleNode {
// the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
    int length; // aktualna dlugosc tablicy
public:
    SingleList() : head(nullptr), tail(nullptr), length(0) {}
    ~SingleList(); // tu trzeba wyczyscic wezly

    SingleList(const SingleList& other); // copy constructor
    // usage:   SingleList<int> list2(list1);

    SingleList(SingleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   SingleList<int> list2(std::move(list1));

    SingleList& operator=(const SingleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    SingleList& operator=(SingleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    int size() const { return length;} // O(1)

    void push_front(const T& item); // O(1), L.push_front(item)
    void push_front(T&& item); // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1), L.push_back(item)
    void push_back(T&& item); // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE

    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa

    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)

    void display(); // O(n)
    void reverse(); // O(n)

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
SingleList<T>::~SingleList() {
    // I sposob.
    for (SingleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }

    length = 0;
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <typename T>
void SingleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }

    ++length;
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }

    ++length;
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleList<T>::pop_front() {
    assert(!empty());
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;

    --length;
}

template <typename T>
void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before=head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;

    --length;
}

// Zadanie 4.2
// Wprowadzony zostal atrybut length
template<typename T>
SingleList<T>::SingleList(const SingleList& other) : head(nullptr), tail(nullptr), length(other.length) // copy constructor
{
    if(this != &other && other.length != 0)
    {
        for(SingleNode<T> *node = other.head; node != nullptr;)
        {
            push_back(node->value);
            node = node->next;
        }
    }
}

template<typename T>
void SingleList<T>::clear()
{
    while (!empty()) { pop_front(); }
    length = 0;
}

template<typename T>
SingleList<T>& SingleList<T>::operator=(const SingleList& other) // copy assignment operator, return *this
{
    if(this != &other)
    {
        length = other.length;
        clear();

        for(SingleNode<T> *node = other.head; node != nullptr;)
        {
            push_back(node->value);
            node = node->next;
        }

    }

    return *this;
}

template<typename T>
void SingleList<T>::reverse()
{
    if(length == 0 || length == 1) return;
    else 
    {
        SingleNode<T> *node = head;
        SingleNode<T> *next;

        while(node->next)
        {
            next = node->next;
            node->next = next->next;
            next->next = head;
            head = next;
        }
        tail = node;
    }
}

template<typename T>
SingleList<T>::SingleList(SingleList&& other) // move constructor
{
    if(this != &other)
    {
        length = other.length;
        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }

}

template<typename T>
SingleList<T>& SingleList<T>::operator=(SingleList&& other) // move assignment operator, return *this
{
    if(this != &other)
    {
        for (SingleNode<T> *node; !empty(); ) // usuwanie wezlow
        {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
        }

        length = other.length;
        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }

    return *this;
}

template<typename T>
void SingleList<T>::push_front(T&& item) // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
{
    push_front(item);

    item = T();
}

template<typename T>
void SingleList<T>::push_back(T&& item) // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE
{
    push_back(item);

    item = T();
}

// Operacje z indeksami. NIEOBOWIAZKOWE
template<typename T>
T& SingleList<T>::operator[](int pos) // podstawienie L[pos]=item, odczyt L[pos]
{
    assert(pos >= 0 && pos < length);
    SingleNode<T> *node = head;

    for(auto index = 0; index < pos; ++index)
    {
        node = node->next;
    }

    return node->value;
}

template<typename T>
const T& SingleList<T>::operator[](int pos) const // dostep do obiektu const
{
    assert(pos >= 0 && pos < length);
    SingleNode<T> *node = head;

    for(auto index = 0; index < pos; ++index)
    {
        node = node->next;
    }

    return node->value;
}

template<typename T>
void SingleList<T>::erase(int pos)
{
    assert(pos >= 0 && pos < length);
    SingleNode<T> *node = head;
    SingleNode<T> *before;

    for(int index = 1; index < pos; ++index)
        node = node->next;
    
    before = node;
    node = node->next;
    before->next = node->next;

    delete node;
    --length;
}

template<typename T>
int SingleList<T>::index(const T& item) // jaki index na liscie (-1 gdy nie ma) O(n)
{
    SingleNode<T> *node = head;
    if(item == head->value) return 0;
    auto index = 0;

    while((node = node->next))
    {
        ++index;
        if(node->value == item) return index;
    }

    return -1;
}

template<typename T>
void SingleList<T>::insert(int pos, const T& item) // inserts item before pos,
{
    assert(pos >= 0 && pos < length);
    if(pos == 0) push_front(item);
    else if(pos == size()) push_back(item);
    else
    {
        SingleNode<T> *node = head;
        SingleNode<T> *before;

        for(auto i = 1; i < pos; ++i)
            node = node->next;

        before = node;
        node = node->next;
        before->next = new SingleNode<T>(item);

        (before->next)->next = node;
    }

    ++length;
}

template<typename T>
void SingleList<T>::insert(int pos, T&& item) // inserts item before pos,
{
    assert(pos >= 0 && pos < length);
    if(pos == 0) push_front(item);
    else if (pos == size()) push_back(item);
    else insert(pos, item);

    item = T();
} 
#endif