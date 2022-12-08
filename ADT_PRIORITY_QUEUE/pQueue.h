#ifndef PQUEUE_H
#define PQUEUE_H

/*
Przygotować implementację realizującą ADT PRIORITY QUEUE nie korzystającą z kopca z STL, tylko własnych funkcji. 
Wydajność: wstawianie O(log n), usuwanie O(log n), odczyt największego O(1).
*/

#include <iostream>
#include <vector>

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::forward_list
public:
    MyPriorityQueue(int n = 20){lst.reserve(n);} // default constructor
    ~MyPriorityQueue(){lst.clear();}

    MyPriorityQueue(const MyPriorityQueue& other); // copy constructor
    MyPriorityQueue(MyPriorityQueue&& other); // move constructor

    MyPriorityQueue& operator=(const MyPriorityQueue& other); // copy assignment operator, return *this
    MyPriorityQueue& operator=(MyPriorityQueue&& other); // move assignment operator, return *this

    bool empty() const { return lst.empty(); }
    int size() const { return lst.size(); } // liczba elementów w kolejce

    void push(const T& item) { // dodanie do kolejki
        
    }
    void push(T&& item) { // dodanie do kolejki
        
    }

    T& top() { return lst.front(); } // zwraca element największy, nie usuwa

    void pop() { // usuwa element największy
        ;
    }
    void clear() { lst.clear(); } // czyszczenie listy z elementów
    void display();
};

template<typename Iterator, typename Compare>
void rebuildMaxHeap(Iterator first, Iterator it, Iterator last, Compare com) // Przywraca właściwości kopca, it jest rodzicem
{
    auto index = std::distance(first, it); // do obliczenia dzieci
    Iterator extreme = it; // najwiekszy/najmniejszy element
    auto left = first;
    auto right = first;

    std::advance(left, index * 2 + 1); // lewe dziecko
    std::advance(right, index * 2 + 2); // prawe dziecko

    if((left < last) && com(*it, *left)) // porownanie lewego dziecka i rodzica
    {
        extreme = left;
    }

    if((right < last) && com(*extreme ,*right)) // porownanie prawego dziecka i najwiekszego/najmniejszego z poprzedniego porownania
    {
        extreme = right;
    }

    if(extreme != it)
    {
        std::swap(*it, *extreme);
        rebuildMaxHeap(first, extreme, last, com);
    }
}

template<typename Iterator, typename Compare>
void buildHeap(Iterator first, Iterator last, Compare com)
{
    auto size = last - first;
    Iterator it = first;
    std::advance(it, (size/2) - 1);

    for(; it >= first; it--)
    {
        rebuildMaxHeap(first, it, last, com);
    }

}

template<typename Iterator, typename Compare>
void heapSort(Iterator first, Iterator last, Compare com)
{
    buildHeap(first, last, com);
    
    for(auto it = last-1; it > first ;it--)
    {
        std::swap(*it, *first); // zamieniam pozcyja 1 i ostatni element
        // od nowa buduje kopiec bez ostatniego elementu, on jest prawdilowo ustawiony
        rebuildMaxHeap(first, first, it, com); 
    }

}

#endif