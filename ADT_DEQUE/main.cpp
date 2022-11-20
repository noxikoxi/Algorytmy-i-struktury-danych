#include "mydeque.h"

void test_push_back();
void test_push_front();
void test_copy_constructor();
void test_move_constructor();
void test_pop_back();
void test_pop_front();
void test_clear();
void test_opearator();

int main()
{
    test_push_back();
    test_push_front();
    test_copy_constructor();
    test_move_constructor();
    test_pop_front();
    test_pop_back();
    test_clear();
    test_opearator();
}

void test_push_back()
{
    std::cout << "***TEST PUSH_BACK***\n";
    MyDeque<int> que(9);
    int z = 6;
    int x = 7;
    int p = 8;

    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    que.push_back(4);
    que.push_back(5);
    que.push_back(z);
    que.push_back(x);
    que.push_back(std::move(p));

    que.display();

}

void test_push_front()
{
    std::cout << "\n***TEST PUSH_FRONT***\n";
    MyDeque<int> que;
    int z = 6;
    int x = 7;
    int p = 8;

    que.push_front(1);
    que.push_front(2);
    que.push_front(3);
    que.push_front(4);
    que.push_front(5);
    que.push_front(z);
    que.push_front(x);
    que.push_front(std::move(p));

    que.display();
}
void test_copy_constructor()
{
    std::cout << "\n***TEST COPY_CONSTRUCTOR***\n";
    MyDeque<float> que;

    que.push_back(3.5);
    que.push_back(8.9);
    que.push_back(-32.2);
    que.push_back(-6.0);
    
    std::cout <<"Q1 -> ";
    que.display();
    std::cout <<"Q2 -> ";

    MyDeque<float> que1(que);
    que1.display();

    std::cout <<"Po zmianie dla q1:\n";
    que.pop_back();
    std::cout <<"Q1 -> ";
    que.display();
    std::cout <<"Q2 -> ";
    que1.display();
    

}
void test_move_constructor()
{
    std::cout << "\n***TEST MOVE_CONSTRUCTOR***\n";
    MyDeque<float> que;

    que.push_back(3.5);
    que.push_back(8.9);
    que.push_back(-32.2);
    que.push_back(-6.0);
    
    std::cout <<"Q1 -> ";
    que.display();

    MyDeque<float> que1(std::move(que));

    std::cout <<"Q1 po konstruktorze -> ";
    
    //std::cout << que.front();
    
    que.display();
    std::cout <<"\nQ2 -> ";
    que1.display();

}
void test_pop_back()
{
    std::cout << "\n***TEST POP_BACK***\n";
    MyDeque<char> que;

    que.push_back('a');
    que.push_back('b');
    que.push_back('c');
    que.push_back('d');

    que.display();
    std::cout<<"Po uzyciu 2x pop_back -> ";
    que.pop_back();
    que.pop_back();
    que.display();

}
void test_pop_front()
{
    std::cout << "\n***TEST POP_FRONT***\n";
    MyDeque<char> que;

    que.push_back('a');
    que.push_back('b');
    que.push_back('c');
    que.push_back('d');

    que.display();
    std::cout<<"Po uzyciu 2x pop_front -> ";
    que.pop_front();
    que.pop_front();
    que.display();

}
void test_clear()
{
    std::cout << "\n***TEST CLEAR***\n";
    MyDeque<int> que;

    que.push_back(1);
    que.push_back(2);
    que.push_back(3);
    que.push_back(4);

    que.display();

    std::cout << "Front() -> " << que.front() << "\nBack() -> " << que.back() << "\n";
    std::cout << "size() -> " << que.size() << "\n";

    std::cout << "Po uzyciu clear -> ";
    que.clear();
    que.display();
    std::cout << "size() -> " << que.size() << "\n";

}

void test_opearator()
{
    std::cout << "\n***TEST OPERATOR=***\n";
    MyDeque<double> q;
    MyDeque<double> q1;

    q.push_back(1.1);
    q.push_back(2.2);
    q.push_back(3.3);
    q.push_back(4.4);

    std::cout << "Q -> ";
    q.display();

    std::cout << "Po Q1 = Q:\n";

    q1 = q;

    std::cout << "Q -> ";
    q.display();

    std::cout << "Q1 -> ";
    q1.display();

    std::cout << "\nPo Q1 = std::move(Q):\n";

    q1 = std::move(q);

    std::cout << "Q -> ";
    q.display();

    std::cout << "Q1 -> ";
    q1.display();
}