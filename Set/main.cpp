#include "set.h"

/*
    Polecenie "make" kompiluje pliki
*/

void test_insert();
void test_isMemeber();
void test_pop();
void test_mSize();
void test_remove();
void test_union();
void test_intersection();
void test_difference();

// Sprawdza czy tablice sa takie same
template<typename T>
void checkArr(T arr1[], T arr2[], size_t n)
{
    for(size_t i = 0; i < n; ++i)
        assert(arr1[i] == arr2[i]);
}

int main()
{
    std::cout << "TEST_INSERT\n\n";
    test_insert();

    std::cout << "\nTEST_ISMEMBER\n\n";
    test_isMemeber();

    std::cout << "\nTEST_POP\n\n";
    test_pop();

    std::cout << "\nTEST_mSize\n\n";
    test_mSize();

    std::cout << "\nTEST_remove\n\n";
    test_remove();

    std::cout << "\nTEST_union\n\n";
    test_union();

    std::cout << "\nTEST_intersection\n\n";
    test_intersection();

    std::cout << "\nTEST_difference\n\n";
    test_difference();
}

void test_insert()
{
    Set<int> set1;
    Set<double> set2;

    for(int i = 0; i <= 10; ++i) set1.insert(i);
    for(double i = 0; i <= 10; i+= 0.5) set2.insert(i);

    assert(set1.size() == 11);
    set1.insert(0);
    assert(set1.size() == 11);

    int* tab = set1.getTab();
    for(int i = 0; i < 10; ++i)
    {
        assert(tab[i] == i);
    }
    set1.display();
    
    double* tab1 = set2.getTab();
    double d = 0;
    for(int i = 0; i < 10; ++i, d+= 0.5)
    {
        assert(tab1[i] == d);
    }
    set2.display();
}

void test_isMemeber()
{
    Set<int> set1;
    Set<double> set2;

    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.display();
    
    assert(set1.isMember(1) == 1);
    assert(set1.isMember(2) == 1);
    assert(set1.isMember(3) == 1);
    assert(set1.isMember(5) == 0);
    
    set2.insert(1.5);
    set2.insert(2.5);
    set2.insert(3.5);
    set2.display();

    assert(set2.isMember(1.5) == 1);
    assert(set2.isMember(2.5) == 1);
    assert(set2.isMember(3.5) == 1);
    assert(set2.isMember(4.25) == 0);
}

void test_pop()
{
    Set<double> set2;

    for(double i = 0; i <= 10; i+= 0.5) set2.insert(i);

    set2.display();
    set2.pop();
    set2.display();

    assert(set2.size() == 20);
    double* tab = set2.getTab();
    assert(tab[set2.size() - 1] == 9.5);
}

void test_mSize()
{
    Set<int> set;

    std::cout <<"max_rozmiar -> " << set.getMSize() << "\n";
    assert(set.getMSize() == 100);

    for(int i = 0; i < 101; i++) set.insert(i);
    set.display();

    assert(set.size() == 101);
    assert(set.getMSize() == 200);
    std::cout <<"max_rozmiar -> " << set.getMSize() << "\n";

    for(int i = 0; i <= 50; i++) set.pop();
    set.display();
    assert(set.size() == 50);
    std::cout <<"max_rozmiar -> " << set.getMSize() << "\n";
    assert(set.getMSize() == 100);
}

void test_remove()
{
    Set<float> set;

    set.insert(1.23);
    set.insert(2.34);
    set.insert(3.45);
    set.insert(6.77);
    set.insert(1.20);

    set.display();

    assert(set.size() == 5);
    set.remove(1.23);
    assert(set.size() == 4);
    set.display();

    float* tab = set.getTab();
    float tab1[] = {1.20, 2.34, 3.45, 6.77};

    checkArr(tab, tab1, 4);

    set.remove(1.23);
    assert(set.size() == 4);
}

void test_intersection()
{
    Set<double> set1;
    Set<double> set2;

    set1.insert(1.25);
    set1.insert(2.50);
    set1.insert(3.45);
    set1.insert(0.25);

    set2.insert(2.50);
    set2.insert(4.50);
    set2.insert(0.25);
    set2.insert(12.123);

    double arr1[] = {0.25, 2.50};
    set1.intersection(set2).display();
    checkArr(set1.intersection(set2).getTab(), arr1, 2);

    Set<double> set3;
    set3.insert(9.0);
    set3.insert(12.20);
    set3.insert(2.4);

    set3.intersection(set1).display();
    assert(set3.intersection(set1).size() == 0);
}

void test_union()
{
    Set<double> set1;
    Set<double> set2;

    set1.insert(1.25);
    set1.insert(2.50);
    set1.insert(3.45);
    set1.insert(0.25);

    set2.insert(2.50);
    set2.insert(4.50);
    set2.insert(0.25);
    set2.insert(12.123);

    double arr1[] = {0.25, 1.25, 2.50, 3.45, 4.50, 12.123};

    set1._union(set2).display();
    checkArr(set1._union(set2).getTab(), arr1, 6);

}

void test_difference()
{
    Set<int> set1;
    Set<int> set2;
    Set<int> set3;

    set3.insert(7);
    set3.insert(8);


    set1.insert(1);
    set1.insert(2);
    set1.insert(3);
    set1.insert(4);

    set2.insert(3);
    set2.insert(4);
    set2.insert(5);
    set2.insert(6);

    int arr1[] = {1, 2};
    set1.difference(set2).display();
    checkArr(set1.difference(set2).getTab(), arr1, 2);

    assert(set1.difference(set3).size() == 4);
}