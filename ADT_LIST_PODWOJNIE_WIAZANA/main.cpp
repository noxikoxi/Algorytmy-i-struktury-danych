#include "doublelist.h"

void test_push_back();
void test_push_front();
void test_copy_constructor();
void test_move_constructor();
void test_pop_back();
void test_pop_front();
void test_clear();
void test_opearator();
void test_erase();
void test_index();
void test_insert();


int main()
{
   test_push_back();
   test_push_front();
   test_copy_constructor();
   test_move_constructor();
   test_pop_back();
   test_pop_front();
   test_clear();
   test_opearator();
   test_erase();
   test_index();
   test_insert();

}

void test_push_back()
{
    std::cout << "***TEST PUSH_BACK***\n";
    DoubleList<int> list;
    int z = 6;
    int x = 7;
    int p = 8;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(z);
    list.push_back(x);
    list.push_back(std::move(p));

    list.display();

}

void test_push_front()
{
    std::cout << "\n***TEST PUSH_FRONT***\n";
    DoubleList<int> list;
    int z = 6;
    int x = 7;
    int p = 8;

    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);
    list.push_front(z);
    list.push_front(x);
    list.push_front(std::move(p));

    list.display();
}
void test_copy_constructor()
{
    std::cout << "\n***TEST COPY_CONSTRUCTOR***\n";
    DoubleList<float> list;

    list.push_back(3.5);
    list.push_back(8.9);
    list.push_back(-32.2);
    list.push_back(-6.0);
    
    std::cout <<"Lista1 -> ";
    list.display();
    std::cout <<"Lista2 -> ";
    DoubleList<float> list1(list);
    list1.display();
    

}
void test_move_constructor()
{
    std::cout << "\n***TEST MOVE_CONSTRUCTOR***\n";
    DoubleList<float> list;

    list.push_back(3.5);
    list.push_back(8.9);
    list.push_back(-32.2);
    list.push_back(-6.0);
    
    std::cout <<"Lista1 -> ";
    list.display();

    DoubleList<float> list1(std::move(list));

    std::cout <<"Lista1 po konstruktorze -> ";
    list.display();
    std::cout <<"Lista2 -> ";
    list1.display();

}
void test_pop_back()
{
    std::cout << "\n***TEST POP_BACK***\n";
    DoubleList<char> list;

    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');

    list.display();
    std::cout<<"Po uzyciu 2x pop_back -> ";
    list.pop_back();
    list.pop_back();
    list.display();

}
void test_pop_front()
{
    std::cout << "\n***TEST POP_FRONT***\n";
    DoubleList<char> list;

    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');

    list.display();
    std::cout<<"Po uzyciu 2x pop_front -> ";
    list.pop_front();
    list.pop_front();
    list.display();

}
void test_clear()
{
    std::cout << "\n***TEST CLEAR***\n";
    DoubleList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.display();
    std::cout << "Po uzyciu clear -> ";
    list.clear();
    list.display();

}
void test_opearator()
{
    std::cout << "\n***TEST OPERATOR[]***\n";
    DoubleList<double> list;

    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);
    list.push_back(4.4);

    list.display();

    std::cout << "List[0] -> "<< list[0] << "\nList[1] -> " << list[1] << "\nList[3] -> " << list[3] << "\n";

    std::cout << "Po podstawieniu dla List[1] i List[3]:\n";
    list[1] = 99.9;
    list[3] = 12.32;

    list.display();
}
void test_erase()
{
    std::cout << "\n***TEST ERASE***\n";
    DoubleList<double> list;

    list.push_back(3.5);
    list.push_back(8.9);
    list.push_back(-32.2);
    list.push_back(-6.0);
    list.push_front(9.0);
    list.push_front(12.56);

    list.display();
    std::cout<< "Po erase[1]:\n";
    list.erase(1);
    list.display();
    std::cout << "Po erase[4]:\n";
    list.erase(4);
    list.display();

}
void test_index()
{
    std::cout << "\n***TEST INDEX***\n";

    DoubleList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.display();

    std::cout << "Index(1) -> " << list.index(1) << "\n";
    std::cout << "Index(2) -> " << list.index(2) << "\n";
    std::cout << "Index(3) -> " << list.index(3) << "\n";
    std::cout << "Index(4) -> " << list.index(4) << "\n";

}

void test_insert()
{
    std::cout << "\n***TEST INSERT***\n";

    DoubleList<int> list;
    int z = 6;
    int y = 7;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.display();
    list.insert(0, 10);
    list.insert(3, 12);
    list.insert(0, 5);

    list.display();

    list.insert(3, z);
    list.insert(list.size(), std::move(y));
    list.display();

}
