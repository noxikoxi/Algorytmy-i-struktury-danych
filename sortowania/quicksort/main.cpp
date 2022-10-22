#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <array>
#include <algorithm> // dla is_sorted

template<typename Iterator, typename Compare>
Iterator _partition(Iterator first, Iterator last, Compare comp)
{
    auto pivot = last - 1; // element rozdzielajacy
    auto it = first; // iteruje pozycje do ustawienia 

    for(auto j = first; j != pivot; j++)
    {
        if(comp(*j, *pivot))
        {
            std::swap(*it, *j);
            it++;
        }
    }
    std::swap(*it, *pivot);
    return it;
}

template<typename Iterator, typename Compare>
void quicksort(Iterator first, Iterator last, Compare comp)
{   
    if(first < last)
    {
    auto pivot = _partition(first, last, comp);

    quicksort(first, pivot, comp);
    quicksort(pivot + 1, last, comp);
    }
}

void test(std::mt19937 generator, std::uniform_real_distribution<> dis)
{
    std::vector<float> v{}; // std::vector

    for(int i = 0; i < 1000000; i++)
        v.push_back(dis(generator));

    quicksort(v.begin(), v.end(), std::less<float>());
    assert( std::is_sorted(v.begin(), v.end()) );
}

void test1(std::mt19937 generator, std::uniform_real_distribution<> dis)
{
    std::array<float, 100000> arr; // std::array
    

    for(int i = 0; i < 100000; i++)
        arr[i] = dis(generator);

    quicksort(arr.begin(), arr.end(), std::less<float>());
    assert( std::is_sorted(arr.begin(), arr.end()) );
}

void test2()
{
    char tab[] = {'a', 'b', 'd', 'a', 'z', 't', 'e', 'o'}; // zwykla tablica
    
    quicksort(tab, tab + (sizeof(tab) / sizeof(*tab)), std::less<char>());
    assert( std::is_sorted(tab, tab + (sizeof(tab) / sizeof(*tab)) ));   // vector, array
}

int main()
{
    std::random_device rd; // ziarno dla generatora
    std::mt19937 gen(rd()); // generator
    std::uniform_real_distribution<> distrib(-10.0, 10.0);

    test(gen, distrib);
    test1(gen, distrib);
    test2();
    
}