#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <forward_list>

using uint = unsigned int;


class Graph{
    private:
        const uint vertexNum;
        std::forward_list<uint> *arr;
        int *inConn; // Lista przechowująca wierzchołek od którego istnieje wchodząca krawędz do i-tego wierzchołka
    public:
        Graph(uint vertexN);
        Graph(const Graph& other ); // Copy constructor

        ~Graph();

        void addEdge(uint i, uint j);
        void removeEdge(uint i, uint j);
        bool hasEdge(uint i, uint j);

        std::set<int> inConnections(uint i) const;
        std::set<int> outConnections(uint i) const;
        std::set<int> allConnections(uint i) const;

        void show() const;
        uint getVertexNum() const {return vertexNum;}
};

#endif
