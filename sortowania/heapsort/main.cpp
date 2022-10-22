#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <algorithm>

template<typename Iterator, typename Compare>
void rebuildMaxHeap(Iterator first, Iterator it, Iterator last, Compare com) // Przywraca właściwości kopca
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

void test1(std::mt19937 m, std::uniform_real_distribution<> u)
{
    std::vector<float> v;

    for(int i=0; i< 100; i++)
    {
        v.push_back(u(m));
    }

    heapSort(v.begin(), v.end(), std::less<float>());
    assert(std::is_sorted(v.begin(), v.end(), std::less<float>())); 
}

void test2(std::mt19937 m, std::uniform_real_distribution<> u)
{
    int N = 100000;
    float tab[N];

    for(int i=0; i< N; i++)
    {
        tab[i] = u(m);
    }

    heapSort(tab, tab + (sizeof(tab) / sizeof(*tab)) , std::less<float>());
    assert(std::is_sorted(tab, tab + (sizeof(tab) / sizeof(*tab)), std::less<float>())); 


}

void test3()
{
    char tab[] = {'a', 'a', 'b', 'e', 'h', 'z', 'g', 's', 'p', 'q'};

    heapSort(tab, tab + (sizeof(tab) / sizeof(*tab)) , std::less<float>());
    assert(std::is_sorted(tab, tab + (sizeof(tab) / sizeof(*tab)), std::less<float>())); 
}



int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(-100.0, 100.0);

    test1(gen, distrib);
    test2(gen, distrib);
    test3();

}