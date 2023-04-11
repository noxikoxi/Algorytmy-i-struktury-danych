#include <iostream>
#include "Graph.h"

template<class T>
void show(T iterable)
{
    for(auto it = iterable.cbegin(); it != iterable.cend(); ++it)
        std::cout << *it << " ";

    std::cout << "\n";
}

int main()
{
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    show(g.allConnections(1));    


}