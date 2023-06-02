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
        Graph(const Graph& other ); // Copy constructor

        ~Graph();

        void addEdge(uint i, uint j) { arr[i][j] = true; }
        void removeEdge(uint i, uint j) { arr[i][j] = false; }
        bool hasEdge(uint i, uint j) { return arr[i][j]; }

        std::set<int> inConnections(uint i) const;
        std::set<int> outConnections(uint i) const;
        std::set<int> allConnections(uint i) const;

        void show() const;
        uint getVertexNum() const {return vertexNum;}

        // BFS
        int* BFS(uint s); // Zwraca najmniejsze odleglosc z wierzchołka S do reszty
};

#endif
