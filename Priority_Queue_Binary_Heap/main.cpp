#include <iostream>
#include "priorityQueue.h"

// polecenie make kompiluje program

void test_insert();
void test_max();
void test_extractMax();

int main()
{
    std::cout<< "***TEST_INSERT\n";
    test_insert();

    std::cout<< "***TEST_MAX\n";
    test_max();

    std::cout<< "***TEST_EXTRACT_MAX\n";
    test_extractMax();
}

void test_extractMax()
{
    priorityQueue<int> q;

    q.insert(99, 1);
    q.insert(25, 5);
    q.insert(56, 3);
    q.insert(12, 5);
    q.insert(15, 6);

    q.display();
    assert(q.getSize() == 5);
    assert(q.extractMax().value == 15);
    assert(q.getSize() == 4);
    q.display();

}

void test_insert()
{
    priorityQueue<int> q;

    q.insert(4, 1);
    q.insert(3, 2);
    q.insert(2, 3);
    q.insert(1, 4);

    assert(q.getSize() == 4);
    q.display();

    QueueElem<int>* qe = q.getTab();

    for(int i= 0; i < q.getSize(); i++) assert(qe[i].priority == 4-i);

    priorityQueue<int> q1;

    for(int i=0; i < 101; i++) q1.insert(i, i+1);

    q1.insert(1, 1);
    q1.insert(1,2);

    assert(q1.getMSize() == 200);
    assert(q1.getSize() == 103);
}

void test_max()
{
    priorityQueue<int> q;

    q.insert(100, 1);
    q.insert(5, 2);
    q.insert(4, 5);
    q.insert(0, 10);
    q.insert(100, 2);

    q.display();
    assert(q.max().value == 0);
    q.insert(1, 12);
    q.display();
    assert(q.max().value == 1);    
}