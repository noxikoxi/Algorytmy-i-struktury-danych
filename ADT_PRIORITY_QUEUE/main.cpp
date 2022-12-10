#include "pQueue.h"

void test_push();
void test_copy_constructor();
void test_move_constructor();
void test_pop();
void test_clear();
void test_opearator();

int main()
{
    test_push();
    test_copy_constructor();
    test_move_constructor();
    test_pop();
    test_clear();
    test_opearator();
}

void test_push()
{
    std::cout << "***TEST PUSH***\n";
    MyPriorityQueue<int> q;
    int z = 6;
    int x = 7;
    int p = 8;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(z);
    q.push(x);
    q.push(std::move(p));

    q.display();

    std::cout<< "Przod kolejki -> " << q.top() << "\n";
    std::cout<< "Liczba elementow -> " << q.size() << "\n";

}

void test_copy_constructor()
{
    std::cout << "\n***TEST COPY_CONSTRUCTOR***\n";
    MyPriorityQueue<float> q;

    q.push(3.5);
    q.push(8.9);
    q.push(-32.2);
    q.push(-6.0);
    
    std::cout <<"Kolejka1 -> ";
    q.display();
    std::cout <<"Kolejka2 -> ";
    MyPriorityQueue<float> q1(q);
    q1.display();
    

}

void test_move_constructor()
{
    std::cout << "\n***TEST MOVE_CONSTRUCTOR***\n";
    MyPriorityQueue<float> q;

    q.push(3.5);
    q.push(8.9);
    q.push(-32.2);
    q.push(-6.0);
    
    std::cout <<"Kolejka1 -> ";
    q.display();

    MyPriorityQueue<float> q1(std::move(q));

    std::cout <<"Kolejka1 po konstruktorze -> ";
    q.display();
    std::cout <<"Kolejka1.empty() _> " << q.empty() << "\n";
    std::cout <<"Kolejka2 -> ";
    q1.display();

}

void test_pop()
{
    std::cout << "\n***TEST POP***\n";
    MyPriorityQueue<char> q;

    q.push('a');
    q.push('b');
    q.push('c');
    q.push('d');

    q.display();
    std::cout<<"Po uzyciu 2x pop -> ";
    q.pop();
    q.pop();
    q.display();

}

void test_clear()
{
    std::cout << "\n***TEST CLEAR***\n";
    MyPriorityQueue<int> q;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);


    q.display();
    std::cout << "Czy Kolejka pusta [kolejka.empty()] " << q.empty() << "\n";
    std::cout << "Liczba elementow kolejki: " << q.size() << "\n";
    std::cout << "Po uzyciu clear -> ";
    q.clear();
    q.display();

    std::cout << "Czy Kolejka pusta [kolejka.empty()] " << q.empty() << "\n";
    std::cout << "Liczba elementow kolejki: " << q.size() << "\n";

}

void test_opearator()
{
    std::cout << "\n***TEST OPERATOR=***\n";
    MyPriorityQueue<double> q;
    MyPriorityQueue<double> q1;
    MyPriorityQueue<double> q2;
    q.push(1.1);
    q.push(2.2);
    q.push(3.3);
    q.push(4.4);

    q1.push(-66.4);
    q1.push(32.5);

    q2.push(3.3);
    q2.push(2.98);
    q2.push(123.4);


    std::cout<< "Kolejka1 -> ";
    q.display();
    std::cout<< "Kolejka2 -> ";
    q1.display();
    std::cout<< "Kolejka3 -> ";
    q2.display();

    std::cout<< "\nPo Kolejka1 = Kolejka2:\n\n";
    q = q1;

    std::cout<< "Kolejka1 -> ";
    q.display();
    std::cout<< "Kolejka2 -> ";
    q1.display();

    std::cout<< "Dlugosc Kolejki1 -> " << q.size() << "\n";
    std::cout<< "Dlugosc Kolejki2 -> " << q1.size() << "\n";

    std::cout<< "\nPo Kolejka2 = std::move(Kolejka3):\n\n";
    q1 = std::move(q2);

    std::cout<< "Kolejka2 -> ";
    q1.display();
    std::cout<< "Kolejka3 -> ";
    q2.display();

    std::cout<< "Dlugosc Kolejki2 -> " << q1.size() << "\n";
    std::cout<< "Dlugosc Kolejki3 -> " << q2.size() << "\n";

}