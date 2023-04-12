#include <iostream>
#include "Graph.h"
#include <cassert>
#include <iterator>

template<class T>
void show(const T iterable)
{
    for(auto it = std::begin(iterable); it != std::end(iterable); ++it)
        std::cout << *it << " ";

    std::cout << "\n";
}

template<typename iterator>
void show( iterator beg,  iterator end)
{
    for(auto it = beg; it != end; ++it)
        std::cout << *it << " ";

    std::cout << "\n";

}

template<class T>
void checkVals(T iterable, typename T::value_type* tab, uint n)
{
    assert(n == iterable.size());

    for(auto i = 0u; i < n; ++i)
    {
        assert(iterable.find(tab[i]) != iterable.end());
    }
}

template<class T>
void checkVals(T* tab1, T* tab2, uint n)
{
    for(auto i = 0u; i < n; ++i)
    {
        assert(tab1[i] == tab2[i]);
    }
}

void test_Connections();
void test_bfs();

int main()
{
    test_Connections();
    test_bfs();
}

void test_Connections()
{
    /*
        Polaczenia pomiedzy wierzcholkami:
        0 -> 2, 1
        1 -> 4
        2 -> 3
        3 -> 0, 4
        4 -> 5, 6
        5 ->
        6 -> 5
        7 ->
    */
    Graph g(8);
    g.addEdge(0, 2);
    g.addEdge(0, 1);

    g.addEdge(1, 4);
    
    g.addEdge(2, 3);

    g.addEdge(3, 0);
    g.addEdge(3, 4);
    
    g.addEdge(4, 5);
    g.addEdge(4, 6);

    g.addEdge(6, 5);

    int t[] = {1, 2, 3, 4};
    checkVals(g.outConnections(0), t, 2);
    show(g.outConnections(0));

    t[0] = 4;
    checkVals(g.outConnections(1), t, 1);
    show(g.outConnections(1));

    t[0] = 3;
    checkVals(g.outConnections(2), t, 1);
    show(g.outConnections(2));

    t[0] = 0;
    t[1] = 4;
    checkVals(g.outConnections(3), t, 2);
    show(g.outConnections(3));

    t[0] = 5;
    t[1] = 6;
    checkVals(g.outConnections(4), t, 2);
    show(g.outConnections(4));

    checkVals(g.outConnections(5), t, 0);
    show(g.outConnections(5));

    t[0] = 5;
    checkVals(g.outConnections(6), t, 1);
    show(g.outConnections(6));

    checkVals(g.outConnections(7), t, 0);
    show(g.outConnections(7));

    t[0] = 3;
    checkVals(g.inConnections(0), t, 1);
    t[0] = 0;
    checkVals(g.inConnections(1), t, 1);
    t[0] = 0;
    checkVals(g.inConnections(2), t, 1);
    t[0] = 2;
    checkVals(g.inConnections(3), t, 1);
    t[0] = 3;
    t[1] = 1;
    checkVals(g.inConnections(4), t, 2);
    t[0] = 4;
    t[1] = 6;
    checkVals(g.inConnections(5), t, 2);
    t[0] = 4;
    checkVals(g.inConnections(6), t, 1);

    checkVals(g.inConnections(7), t, 0);

    t[0] = 1;
    t[1] = 2;
    t[3] = 3;
    checkVals(g.allConnections(0),t, 3);

    t[0] = 1;
    t[1] = 3;
    t[2] = 6;
    t[3] = 5;
    checkVals(g.allConnections(4), t, 4);

    checkVals(g.allConnections(7), t, 0);
}

void test_bfs()
{
    std::cout << "TEST BFS\n";
    // ten sam graf co w powyzszym tescie
    Graph g(8);
    g.addEdge(0, 2);
    g.addEdge(0, 1);

    g.addEdge(1, 4);
    
    g.addEdge(2, 3);

    g.addEdge(3, 0);
    g.addEdge(3, 4);
    
    g.addEdge(4, 5);
    g.addEdge(4, 6);

    g.addEdge(6, 5);

    int t[] = {0, 1, 1, 2, 2, 3, 3, -1};
    auto result = g.BFS(0);
    show(result, result + 8);
    checkVals(result, t, 8);
    delete[] result;

    result = g.BFS(4);
    int t1[] = {-1, -1, -1, -1, 0, 1, 1, -1};
    show(result, result + 8);
    checkVals(result, t1, 8);
    delete[] result;

    result = g.BFS(7);
    int t2[] = {-1, -1, -1, -1, -1, -1, -1, 0};
    show(result, result + 8);
    checkVals(result, t2, 8);
    delete[] result;

    result = g.BFS(3);
    int t3[] = {1, 2, 2, 0, 1, 2, 2, -1};
    show(result, result + 8);
    checkVals(result, t3, 8);
    delete[] result;


}