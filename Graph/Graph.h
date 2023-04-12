#ifndef GRAPH_H
#define GRAPH_H
#include <set>

using uint = unsigned int;

class Graph{
    private:
        const uint vertexNum;
        bool** arr;
    public:
        Graph(uint vertexN);

        ~Graph();

        void addEdge(uint i, uint j) { arr[i][j] = true; }
        void removeEdge(uint i, uint j) { arr[i][j] = false; }
        bool hasEdge(uint i, uint j) { return arr[i][j]; }

        std::set<int> inConnections(uint i);
        std::set<int> outConnections(uint i);
        std::set<int> allConnections(uint i);

        // BFS
        int* BFS(uint s); // Zwraca najmniejsze odleglosc z wierzchołka S do reszty
};

#endif
