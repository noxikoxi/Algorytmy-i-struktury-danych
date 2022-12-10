#ifndef PQUEUE_H
#define PQUEUE_H

/*
Przygotować prostą implementację realizującą ADT PRIORITY QUEUE na bazie listy powiązanej pojedynczo. 
Lista jest stale uporządkowana, a największy element znajduje się na początku listy. 
Można wykorzystać klasę SingleList lub std::forward_list. 
Wydajność: wstawianie O(n), usuwanie O(1), odczyt największego O(1).
*/

#include <iostream>
#include <forward_list>
#include <cassert>

template <typename T>
class MyPriorityQueue {
    std::forward_list<T> lst; // działa domyślny konstruktor dla std::forward_list
    int len;
public:
    MyPriorityQueue() : len(0) {} // default constructor
    ~MyPriorityQueue(){lst.clear();}

    MyPriorityQueue(const MyPriorityQueue& other) // copy constructor
    {
        if(other.len > 0)
        {
            this->len = other.len;

            for(auto it = other.lst.begin(); it != other.lst.end(); it++)
            {
                this->lst.push_front(*it);
            }
            
            this->lst.reverse();
        }

    }

    MyPriorityQueue(MyPriorityQueue&& other) // move constructor
    {
        if(this != &other)
        {
            this->len = other.len;
            other.len = 0;

            std::swap(this->lst, other.lst);
        }

    }

    MyPriorityQueue& operator=(const MyPriorityQueue& other) // copy assignment operator, return *this
    {
        if(this != &other)
        {
            this->len = other.len;
            this->lst.clear();

            for(auto it = other.lst.begin(); it != other.lst.end(); ++it)
            {
                this->lst.push_front(*it);
            }

            this->lst.reverse();
        }
        return *this;
    }
    
    MyPriorityQueue& operator=(MyPriorityQueue&& other) // move assignment operator, return *this
    {
        if(this != &other)
        {
            this->lst.clear();
            this->len = other.len;
            other.len = 0;

            std::swap(this->lst, other.lst);
        }

        return *this;
    }

    bool empty() const { return lst.empty(); }
    int size() const { return len; } // liczba elementów w kolejce

    void push(const T& item) { // dodanie do kolejki
        if(size() == 0) lst.push_front(item);
        else if(size() == 1)
        { 
            if(item > top()) lst.push_front(item);
            else lst.insert_after(lst.begin(), item);
        }
        else{
            auto old_it = lst.before_begin();
            bool inserted = false;

            for(auto it = lst.begin(); it != lst.end(); ++it)
            {
                if(*it > item)
                {
                    old_it = it;
                    continue;
                } 
                else 
                {
                    lst.insert_after(old_it, item);
                    break;
                }
            } 

            // Przypadek jezeli item jest mniejszy od wszystkich elementow kolejki
            // Wtedy old_it jest o 1 mniejsze od lst.end()
            if(!inserted) lst.insert_after(old_it, item);  
        }

        ++len;      
    }

    void push(T&& item) { // dodanie do kolejki
        if(size() == 0) lst.push_front(std::move(item));
        else if(size() == 1)
        { 
            if(item > top()) lst.push_front(std::move(item));
            else lst.insert_after(lst.begin(), std::move(item));
        }
        else{
            
            auto old_it = lst.before_begin();
            bool inserted = false;

            for(auto it = std::begin(lst); it != std::end(lst); ++it)
            {
                if(*it > item) 
                {
                    old_it = it;
                    continue;
                }
                else
                { 
                    inserted = true;
                    lst.insert_after(old_it, std::move(item));
                    break;
                }
            }

            // Przypadek jezeli item jest mniejszy od wszystkich elementow kolejki
            // Wtedy old_it jest o 1 mniejsze od lst.end()
            if(!inserted) lst.insert_after(old_it, std::move(item));

        }

        ++len;        
    }

    T& top() { return lst.front(); } // zwraca element największy, nie usuwa

    void pop() { // usuwa element największy
        assert(size() > 0);
        lst.pop_front();
        --len;
    }
    void clear() 
    { 
        lst.clear(); 
        this->len = 0;
    } // czyszczenie listy z elementów
    
    void display()
    {
        for(auto it = lst.begin(); it != lst.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }

};

#endif