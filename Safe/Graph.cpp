#include "Graph.h"
#include <queue>
#include <iostream>


Graph::Graph(uint vertexN) : vertexNum(vertexN) 
{ 
    arr = new bool*[vertexNum];
    for(auto i=0u; i < vertexNum; ++i)
    {
        arr[i] = new bool[vertexNum](); // Inizjalizuje na 0
    }
}

Graph::Graph(const Graph &other) : vertexNum(other.vertexNum)
{
    arr = new bool*[vertexNum];
    for(auto i=0u; i < vertexNum; ++i)
    {
        arr[i] = new bool[vertexNum]();
    }

    for(auto i=0u; i < vertexNum; ++i)
    {
        for(auto j=0u; j < vertexNum; ++j)
        {
            arr[i][j] = other.arr[i][j];
        }
    }


}

Graph::~Graph()
{
    for(auto i=0u; i < vertexNum; ++i)
    {
        delete[] arr[i];
    }

    delete[] arr;
}

std::set<int> Graph::inConnections(uint i) const
{
    std::set<int> s;
    for(auto j = 0u; j < vertexNum; ++j)
    {
        if(arr[j][i]) s.insert(j);

    }
    return s;
}

std::set<int> Graph::outConnections(uint i) const
{
    std::set<int> s;
    for(auto j = 0u; j < vertexNum; ++j)
    {
        if(arr[i][j]) s.insert(j);
    }
    return s;
}

std::set<int> Graph::allConnections(uint i) const
{
    std::set<int> s;
    for(auto j = 0u; j < vertexNum; ++j)
    {
        if(arr[j][i] || arr[i][j]) s.insert(j);

    }
    return s;
}

void Graph::show() const
{
    std::cout << "Graph {\n";
    for(auto i = 0u; i < vertexNum; ++i)
    {
        std::cout <<"\tVertex " << i << " -> ";
        for(auto j= 0u; j < vertexNum; ++j)
        {
            if(arr[i][j])
            {
                std::cout<< j << " ";
            }

        }
        std::cout << "\n";
    }
    std::cout << "}\n";
}

int* Graph::BFS(uint s)
{
    int* d = new int[vertexNum];
    for(auto i=0u; i < vertexNum; ++i) d[i] = -1;

    std::queue<uint> que;
    que.push(s);
    d[s] = 0;

    while(!que.empty())
    {
        auto u = que.front();
        que.pop();

        for(auto v: outConnections(u))
        {
            if(d[v] == -1)
            {
                d[v] = d[u] + 1;
                que.push(v);
            }
        }
    }

    return d;
}