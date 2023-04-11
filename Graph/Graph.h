#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <queue>

class Graph{
    private:
        const size_t vertexNum;
        bool **arr;
    public:
        Graph(size_t vertexN) : vertexNum(vertexN) 
        { 
            arr = new bool*[vertexNum];
            for(auto i=0u; i < vertexNum; ++i)
            {
                arr[i] = new bool[vertexNum];
            }

            for(auto i=0u; i < vertexNum; ++i)
                for(auto j=0u; j < vertexNum; ++j)
                    arr[i][j] = false;
        }

        ~Graph()
        {
            for(auto i=0u; i < vertexNum; ++i)
            {
                delete arr[i];
            }

            delete arr;
        }

        void addEdge(size_t i, size_t j) {
            arr[i][j] = true;
        }
        void removeEdge(size_t i, size_t j) {
            arr[i][j] = false;
        }
        bool hasEdge(size_t i, size_t j) {
            return arr[i][j];
        }

        std::set<int> inConnections(size_t i) {
            std::set<int> s;
            for(auto j = 0u; j < vertexNum; ++j)
            {
                if(arr[j][i]) s.insert(j);

            }
            return s;
        }
        std::set<int> outConnections(size_t i) {
            std::set<int> s;
            for(auto j = 0u; j < vertexNum; ++j)
            {
                if(arr[i][j]) s.insert(j);

            }
            return s;
        }
        std::set<int> allConnections(size_t i) {
            std::set<int> s;
            for(auto j = 0u; j < vertexNum; ++j)
            {
                if(arr[j][i] || arr[i][j]) s.insert(j);

            }
            return s;
        }

        // BFS
        void BFS() {}


};

#endif
