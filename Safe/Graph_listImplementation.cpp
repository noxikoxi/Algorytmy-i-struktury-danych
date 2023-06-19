#include "Graph_listImplementation.h"
#include <iostream>
#include <cassert>

void checkRange(uint number, uint max)
{
    assert(number >= 0 && number < max);
}

Graph::Graph(uint vertexNumber) : vertexNum(vertexNumber)
{
    arr = new std::forward_list<uint>[vertexNum];
    inConn = new int[vertexNum];

    for(auto i = 0u; i < vertexNum; ++i)
    {
        inConn[i] = -1;
    }
}

Graph::~Graph()
{
    delete[] arr;
    delete[] inConn;
}

Graph::Graph(const Graph &other) : vertexNum(other.vertexNum)
{
    arr = new std::forward_list<uint>[other.vertexNum];
    inConn = new int[other.vertexNum];

    for(uint i= 0; i< other.vertexNum; ++i)
    {
        arr[i] = other.arr[i];
        inConn[i] = other.inConn[i];
    }
}

bool Graph::hasEdge(uint i, uint j)
{
    checkRange(i, vertexNum);
    checkRange(j, vertexNum);

    for(auto elem = arr[i].begin(); elem != arr[i].end(); ++elem)
    {
        if(*elem == j)
        {
            return true;
        }
    }

    return false;
}

void Graph::addEdge(uint i, uint j)
{
    checkRange(i, vertexNum);
    checkRange(j, vertexNum);
    
    inConn[j] = i;
    for(auto elem = arr[i].begin(); elem != arr[i].end(); ++elem)
    {
        if(*elem == j)
        {
            return;
        }
    }
    arr[i].push_front(j);
}

void Graph::removeEdge(uint i, uint j)
{
    checkRange(i, vertexNum);
    checkRange(j, vertexNum);

    arr[i].remove(j);
}

std::set<int> Graph::inConnections(uint i) const
{
    checkRange(i, vertexNum);

    std::set<int> s;
    if(inConn[i] != -1) s.insert(inConn[i]);
    return s;
}

std::set<int> Graph::outConnections(uint i) const
{
    checkRange(i, vertexNum);
    std::set<int> s;

    for(auto elem = arr[i].begin(); elem != arr[i].end(); ++elem)
    {
        s.insert(*elem);
    }
    return s;
}

std::set<int> Graph::allConnections(uint i) const
{
    checkRange(i, vertexNum);

    std::set<int> s;
    s = outConnections(i);
    if(inConn[i] != -1) s.insert(inConn[i]);
    return s;
}

void Graph::show() const
{
    std::cout << "Graph {\n";
    for(auto i = 0u; i < getVertexNum(); ++i)
    {
        std::cout <<"\tVertex " << i << " -> ";
        for(auto elem = arr[i].begin(); elem != arr[i].end(); ++elem)
        {
            std::cout<< *elem << " ";
  
        }
        std::cout << "\n";
    }
    std::cout << "}\n";
}
