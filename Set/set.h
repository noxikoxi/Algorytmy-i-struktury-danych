#ifndef SET_H
#define SET_H
#include <iostream>
#include <cassert>

template <typename T>
class Set{
private:
    T* tab;
    size_t mSize;
    size_t current_size;
    void resize(double val); // zmienia rozmiar tablicy

public:

    // Dla testow
    T* getTab(){return tab;}
    size_t getMSize() {return mSize;}

    Set() : mSize(100), current_size(0) { tab = new T[mSize]; } // konstruktor domyslny
    ~Set() { delete tab;}
    
    void insert(T x); // wstawia obiekt do zbioru
    bool isMember(T x); // sprawdza czy obiekt x jest elementem zbioru
    void remove(T x); // usuwa obiekt x ze zbioru
    T pop(); // usuwa i zwraca jeden dowolny element
    size_t size(){return current_size;}; // zwraca rozmiar zbioru

    Set<T> intersection(const Set<T> &s); // zwraca przeciecie zbiorów
    Set<T> difference(const Set<T> &s); // zwraca różnicę zbiorów
    Set<T> _union(const Set<T> &s); // zwraca sume zbiorów

    void display()
    {
        std::cout <<"Set { ";

        for(auto i=0u; i < current_size; ++i) std::cout << tab[i] << " ";

        std::cout << "} o rozmiarze " << current_size;
        std::cout<< "\n";
    }
};

// pomocniczy
template<typename T>
int binary_search(int start, int end, T* arr, T x)
{
    if(start > end) return -1;
    else
    {
        size_t mid = (start + end)/2;
        if(x == arr[mid]) return mid;
        else if(x > arr[mid]) return binary_search(mid+1, end, arr, x);
        else return binary_search(start, mid-1, arr, x);
    }
}

template<typename T>
Set<T> Set<T>::difference(const Set<T> &s)
{
    Set<T> temp;
    size_t i, i1, i2;
    i = i1 = i2 = 0;

    while(i1 != current_size)
    {
        if(i == temp.mSize) temp.resize(2);

        if(i2 == s.current_size) // skonczyly sie elementy, ktore trzeba odjac, przepisuje reszte zbioru 1
        {
            while(i1 != current_size)
            {
                temp.tab[i++] = tab[i1++];
                if(i == temp.mSize) temp.resize(2);
            }
            break;
        }

        while(tab[i1] > s.tab[i2]) ++i2; 

        if(tab[i1] == s.tab[i2]) // elementy w zbiorach takie same, omijam wstawianie
        {
            ++i1;
            ++i2;
        }else{ // sa na pewno różne
            temp.tab[i++] = tab[i1++];
        }
    }
    temp.current_size = i;
    return temp;
}

template<typename T>
Set<T> Set<T>::_union(const Set<T> &s)
{
    Set<T> temp;
    size_t i1, i2, i;
    i1 = i2 = i = 0;
    while(i1 < current_size || i2 < s.current_size)
    {
        if(i == temp.mSize) temp.resize(2);

        if(i1 < current_size && i2 < s.current_size) // jednoczesnie porównuje w 2 zbiorach
        {
            if(tab[i1] == s.tab[i2])
            {
                temp.tab[i] = tab[i1];
                ++i1;
                ++i2;
            }
            else if(tab[i1] < s.tab[i2])
            {
                temp.tab[i] = tab[i1++];
            }
            else{
                temp.tab[i] = s.tab[i2++];
            }
            ++i;
        }else if (i1 < current_size) // w drugim ze zbiorow skonczyly sie juz elementy
        {
            while(i1 != current_size)
            {
                temp.tab[i++] = tab[i1++];
                if(i == temp.mSize) temp.resize(2);
            }
        }else{ // w pierwszym ze zbiorow skonczyly sie juz elementy
            while(i2 != s.current_size)
            {
                temp.tab[i++] = s.tab[i2++];
                if(i == temp.mSize) temp.resize(2);
            }
        }
        
    }
    temp.current_size = i;
    return temp;    
}

template<typename T>
void Set<T>::resize(double val)
{
    mSize *= val;
    T* tab1 = new T[mSize];
    for(auto i = 0u; i < current_size; ++i)
    {
        tab1[i] = std::move(tab[i]);
    }

    delete tab;
    tab = tab1;
}

template<typename T>
Set<T> Set<T>::intersection(const Set<T> &s)
{
    Set<T> temp;
    size_t i, i1, i2;
    i = i1 = i2 = 0;

    while(i1 < current_size && i2 < s.current_size)
    {
        if(i == temp.mSize) temp.resize(2);
        
        if(tab[i1] == s.tab[i2])
        {
            temp.tab[i] = tab[i1];
            ++i1;
            ++i2;
            ++i;
        }else if(tab[i1] < s.tab[i2]){
            ++i1;
        }else{
            ++i2;
        }
    }

    temp.current_size = i;
    return temp;
}

template<typename T>
bool Set<T>::isMember(T x)
{
    if(current_size == 0) return false;

    if(binary_search(0, current_size-1, tab, x) != -1) return true;
    else return false;
}

template<typename T>
void Set<T>::remove(T x)
{
    if(current_size == 0) return;
    int temp = binary_search(0, current_size-1, tab, x);

    if(temp != -1)
    { 
        for(size_t i = temp; i < current_size-1; ++i)
        {
            tab[i] = tab[i+1];
        }

        current_size--;
    }
    

    if(current_size <= (mSize/4) && mSize > 100) // Mozna zmniejszyc tablice
    {
        resize(0.5);
    }
}

template<typename T>
T Set<T>::pop()
{
    assert(current_size > 0);

    if(--current_size <= (mSize/4) && mSize > 100) // Mozna zmniejszyc tablice
    {
        resize(0.5);
    }

    return tab[current_size];
}

template<typename T>
void Set<T>::insert(T x)
{
    if(isMember(x)) return;
    
    if(current_size == 0)
    {
        tab[current_size++] = x;
    }else{
        if(current_size >= mSize) // Przekroczony zakres, zwiekszam tablice
        {
            resize(2);
        }

        for(auto i = current_size-1; i >= 0; --i)
        {
            if(tab[i] > x)
            {
                tab[i+1] = tab[i];

                if(i == 0) // kiedy wstawiam najmniejszy element
                {
                    tab[i] = x;
                    break;
                }
            }else{
                tab[++i] = x;
                break;
            }
        }
        current_size++;
    }
}

#endif