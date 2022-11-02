#include <iostream>
#include "arraylist.h"

void test1()
{
    ArrayList<int> tab; // domyślny konstruktor
    std:: cout << "****Test1****\nWielkosc Tablicy -> " << tab.size()<< "\nMax Wielkosc -> " << tab.max_size() << "\n";
    for(int i=6; i > 0; i--)
        tab.push_back(i); // push_back

    // Tablica zwiekszyla sie o 4 na max wielkosc
    std:: cout << "Po dodaniu 6 elementow:\nWielkosc Tablicy -> " << tab.size()<< "\nMax Wielkosc -> " << tab.max_size() << "\n";
    tab.display(); // wypisanie
    tab.sort(); // Test sortowania
    tab.display();
    tab.reverse(); // Test odwracania
    tab.display();

    tab.push_front(10); // test push_front
    tab.push_front(99);

    std:: cout << tab;
    std:: cout << "Wielkosc Tablicy -> " << tab.size()<< "\nMax Wielkosc -> " << tab.max_size() << "\n";
    tab.pop_front();
    tab.pop_front();
    tab.pop_front();
    tab.pop_front();
    tab.pop_front();
    tab.display(); // Mozna zauwazyc ze tablica sama sie zmniejszyla
    std:: cout << "Wielkosc Tablicy -> " << tab.size()<< "\nMax Wielkosc -> " << tab.max_size() << "\n";
    tab[1] = 222; // wstawianie poprzez [] dziala
    tab[0] = 111;
    tab[2] = 333;
    std::cout << tab;
}

void test2()
{
    ArrayList<double> a1(20);
    std::cout<<"\n****Test2****\nMax wielkosc poczatkowa->" << a1.max_size() << "\n";
    for(double i = 10.0; i < 21.0; i+= 0.5)
        a1.push_front(i);
    std::cout << a1;
    std::cout<<"Max wielkosc ->" << a1.max_size() << "\n";

    ArrayList<double> a2(a1); // Test copy constructor
    std::cout << a2;
    std::cout<<"Max wielkosc ->" << a2.max_size() << " Wielkosc -> " << a2.size() << "\n";
    std::cout <<"Pierwszy element -> " << a2.front() << " Ostatni element -> " << a2.back() << "\n"; // test front, back

    for(int i = 0; i < 6; i++)
    {
        a2.pop_back();
    }

    // Elementy usuniete z a2, 0 wplywu na a1, rzeczywista kopia
    std::cout << "a2: "<< a2 << "\na1: " << a1 << "\n";

    a1.clear(); // Czyszczenie a1
    if(a1.empty()) std::cout << "A1 puste\n"; // empty

    a2.full() ? std::cout << "A2 pelne\n" : std::cout << "A2 niepelne\n"; // full
    std::cout<<"Max wielkosc ->" << a2.max_size() << " Wielkosc -> " << a2.size() << "\n";
    a2.push_back(2.22);
    a2.push_back(2.22);
    a2.push_back(2.22);
    a2.push_back(2.22);
    a2.full() ? std::cout << "A2 pelne\n" : std::cout << "A2 niepelne\n"; // full
    std::cout<<"Max wielkosc ->" << a2.max_size() << " Wielkosc -> " << a2.size() << "\n";

}

void test3()
{
    ArrayList<char> a1;
    std::cout <<"\n****Test3****\n";
    char znaki[] = {'a', 'b', 'c', 'd', 'e', 'g', 'z', 'a', 'g', 't', 'y', 'e'};

    for(int i = 0; i < 12; i++)
        a1.push_back(znaki[i]);

    a1.display();

    ArrayList<char> a2(std::move(a1)); // test przenoszenia poprzez konstruktor
    std::cout << "a2 -> "<< a2 << "\nWielkosc a2 -> " << a2.size()<< "\na1 -> " << a1 << "\nWielkosc a1 -> " << a1.size() << "\n";

    a1 = std::move(a2); // przenoszenie poprzez operator =
    std::cout << "a2 -> "<< a2 << "\nWielkosc a2 -> " << a2.size()<< "\na1 -> " << a1 << "\nWielkosc a1 -> " << a1.size() << "\n";

    std::cout << a1[2]<<"\n"; // odczyt przez [] dziala
    std::cout << a1.index('c') << "\n"; // odczyt indeksu dziala
    a1.erase(2); // Test erase
    a1.display();

    a1.insert(6,'w'); // test
    a1.display();
}

void testMerge()
{
    ArrayList<float> a1;
    float f = 5.79;
    a1.push_back(f);
    a1.push_back(2.2);
    a1.push_back(5.4);
    a1.push_back(9.5);
    a1.push_back(1.23);
    ArrayList<float> a2(a1);
    a2.sort();
    a2.push_front(-2.2);
    a2.push_back(-1.34);
    std::cout <<"\n****Test Merge****\n" << a1 << "\n" << a2;

    a1.merge(a2);
    a1.display();

}

int main()
{
    test1();
    test2();
    test3();
    testMerge();
}