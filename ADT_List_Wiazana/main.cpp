#include "singlelist.h"

void test1()
{
    SingleList<int> list; // domyslny konstruktor
    std::cout << "*****Test1*****";
    int z = 10;
    int z1 = 233;

    list.push_front(2);
    list.push_front(z1);
    list.push_front(z);
    list.push_front(8);
    list.push_back(6);
    list.pop_front();
    std::cout << "Dlugosc listy-> " << list.size() << "\n";
    list.display();

    list.reverse(); // Odwrocenie listy

    list.display();

    std::cout << list[1] << "\n"; // odczyt list[n]
    std::cout << list[3] << "\n";
    list[3] = 99; // podstawienie list[n]

    list.display();
    std::cout <<"Index 2 to -> " << list.index(2) << "\n";
    std::cout <<"Index 99 to -> " << list.index(99) << "\n";
    std::cout <<"Index 6 to -> " << list.index(6) << "\n";

    list.push_front(2);
    list.push_back(56);
    list.push_back(42);
    list.display();

    std::cout<< "Poczatek listy to -> " << list.front() << "\n";
    std::cout<< "Koniec listy to -> " << list.back() << "\n";
}

void test2()
{
    SingleList<double> list1;
    SingleList<double> listCopy;

    std::cout << "\n*****Test2*****\n";
    for(double i = 10.0; i < 100; i+= 5.75)
        list1.push_front(i);

    
    listCopy = list1;
    SingleList<double> listCopy1(list1);

    std::cout << "Lista i jej kopia przez konstruktor oraz operator=:\n";
    list1.display();
    listCopy1.display();
    listCopy.display();

    std::cout<< "\nPo Zmianie w oryginalnej liscie\n";
    list1.pop_front();
    list1[4] = -999;
    list1.push_back(567);
    list1.erase(6);
    list1.erase(5);
    list1.pop_front();

    list1.display();
    listCopy1.display();
    listCopy.display();
    
    listCopy1.clear(); // Czyszczenie listy
    listCopy1.display();
}

void test3()
{
    SingleList<char> list;
    SingleList<char> moveList1;
    std::cout << "\n*****Test3*****\n";
    char c = 'p';

    list.push_back('z');
    list.push_back('r');
    list.push_back('q');
    list.push_back('y');
    list.push_back('i');
    list.insert(4, c);

    list.display();

    SingleList<char> moveList(std::move(list));
    std::cout << "lista po uzyciu konstrukotra z std::move\n";
    list.display();
    std::cout << "Dlugosc -> " << list.size() << "\n\n";

    moveList1 = std::move(moveList);
    std::cout << "lista po uzyciu operatora= z std::move\n";
    moveList.display();
    std::cout << "Dlugosc -> " << moveList.size() << "\n\n";

    moveList1.display();

}

int main()
{
    test1();
    test2();
    test3();

}