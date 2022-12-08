#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <list>

template <typename T>
class MyQueue{
private:
    std::list<T> *list;

public:
    MyQueue(){
        list = new std::list<T>;
    } // default constructor
    ~MyQueue() { 
        delete list;
    }
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue(MyQueue&& other); // move constructor
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    MyQueue& operator=(MyQueue&& other); // move assignment operator, return *this
    bool empty() const {return list->size() == 0;}
    int size() const {return list->size();}
    void push(const T& item){list->push_back(item);}; // dodanie na koniec
    void push(T&& item){list->push_back(std::move(item));}; // dodanie na koniec
    T& front() { return list->front();} // zwraca początek
    T& back() { return list->back();} // zwraca koniec
    void pop(){ list->pop_front();}; // usuwa początek
    void clear(){ list->clear();}; // czyszczenie listy z elementów
    void display();
};

template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& other) // copy constructor
{
    if(this != &other)
    {
        this->list = new std::list<T>;

        while(!other.list->empty())
        {
            list->push_back(other.list->front());
            other.list->pop_front();
        }
    }
}

template <typename T>
MyQueue<T>::MyQueue(MyQueue&& other) // move constructor
{
    if(this != &other)
    {
        this->list = other.list;
    
        other.list = new std::list<T>;
    }
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other) // copy assignment operator, return *this
{
    if(this != &other)
    {
        this->list->clear();

        for(auto it = other.list->begin(); it != other.list->end(); ++it)
        {
            list->push_back(*it);
        }
    }   
    return *this;
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other) // move assignment operator, return *this
{
    if(this != &other)
    {
        this->list = other.list;
    
        other.list = new std::list<T>;
    }

    return *this;
}

template <typename T>
void MyQueue<T>::display()
{
    if(this->size() == 0) std::cout << "pusta\n";
    else
        {
            for(auto it = list->begin(); it != list->end(); it++)
            {
                std::cout << *it << " ";
            }
            std::cout << "\n";
        }
}

#endif