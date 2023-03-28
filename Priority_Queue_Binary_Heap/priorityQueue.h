#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <cassert>

template <typename T>
class QueueElem{
    public:
        T value;
        int priority;

        QueueElem() : value(T()), priority(0){};
        QueueElem(T val, int priority) : value(val), priority(priority) {}
        T getVal(){return value;}

        bool operator>(const QueueElem<T> elem){ return priority > elem.priority ? true : false;}
        bool operator<(const QueueElem<T> elem){ return !(*this > elem);}

        
};

template <typename T>
std::ostream& operator<< (std::ostream &os, const QueueElem<T> &q)
{
    return os << "QE(V: " << q.value << ", P: " << q.priority << ")\n";
}

template<typename T>
class priorityQueue
{
    private:
        QueueElem<T>* tab;
        size_t mSize;
        size_t size;

        void resize(double val);
        void heapify(size_t i);

        // do kopca
        size_t right(size_t i) { return i*2 + 1;}
        size_t left(size_t i) { return i*2 + 2;}
        size_t parent(size_t i) { return (i-1)/2;}
        
    public:
        priorityQueue() : mSize(100), size(0) { tab = new QueueElem<T>[mSize];}
        ~priorityQueue(){ delete tab;}

        // dla testow
        size_t getSize(){return size;}
        size_t getMSize(){return mSize;}
        QueueElem<T>* getTab(){return tab;}

        void display(){
            std::cout<<"Kolejka(size: " << size <<  ", mSize: "<< mSize << "):\n\t";
            for(auto i =0u; i < size; ++i) std::cout << tab[i] << "\t";
            std::cout << "\n";
        }

        void insert(T x, int k); // wstawia obiekt x o priorytecie k
        QueueElem<T> max(); // zwraca obiekt o największym priorytecie bez usuwania
        QueueElem<T> extractMax(); // zwraca i usuwa obiekt o najwiekszym priorytecie
};

template<typename T>
void priorityQueue<T>::resize(double val)
{
    mSize *= val;
    QueueElem<T>* temp = new QueueElem<T>[mSize];

    std::copy(tab, tab + size, temp);

    delete tab;
    tab = temp;
}


template<typename T>
QueueElem<T> priorityQueue<T>::max()
{
    assert(size != 0);
    return tab[0];
}

template<typename T>
void priorityQueue<T>::heapify(size_t i)
{
    size_t maxi = i;
    size_t l = left(i);
    size_t r = right(i);

    if(l < size && tab[l] > tab[maxi]) maxi = l;
    if(r < size && tab[r] > tab[maxi]) maxi = r;

    if(maxi != i)
    {
        std::swap(tab[maxi],tab[i]);
        heapify(maxi);
    }

}


template<typename T>
QueueElem<T> priorityQueue<T>::extractMax()
{
    assert(size != 0);

    QueueElem<T> res = tab[0];
    std::swap(tab[0], tab[--size]);
    heapify(0);

    if((size <= (mSize / 4)) && mSize > 100) resize(0.5);

    return res;
}

template<typename T>
void priorityQueue<T>::insert(T x, int k)
{
    if(size >= mSize)
    {
        resize(2);
    }
    size++;
    int index = size-1;
    tab[index] = QueueElem<T>(x, k);
    
    while(index > 0 && tab[parent(index)].priority < k)
    {
       std::swap(tab[index], tab[parent(index)]);
       index = parent(index);
    }
    
}
#endif