#include <iostream>
#include "Graph.h"
#include <queue>
#include <cassert>
#include <fstream>
#include <chrono>

/*
Mamy n sejfów. Każdy z nich można otworzyć odpowiednim kluczem lub zniszczyć, żeby dostać się do zawartości.
Klucze do tych sejfów znajdują się w tych samych sejfach- w każdym sejfie może być 1 klucz, więcej,
lub może ich nie być w ogóle.

Do każdego sejfu pasuje tylko jeden klucz i wiemy,
w którym sejfie się on znajduje.

Zadaniem jest napisanie programu, który zwróci informację jaka jest najmniejsza liczba sejfów,
które trzeba zniszczyć żeby dostać się do zawartości wszystkich z nich.

Przykładowe wejście do programu może składać się z jeden liczby n oznaczającej liczbę sejfów,
oraz listy n liczb, w której i-ta liczba to indeks sejfu w którym znajduje się klucz do i-tego sejfu.
Przykład:

4
2 1 2 4

Oznacza to, że są 4 sejfy. Klucz do pierwszego sejfu znajduje się w sejfie 2 (2 na pozycji pierwszej),
do drugiego w sejfie 1 (1 na pozycji drugiej), do 3 w sejfie 2 itd.
Dla takiego wejścia, prawidłowa odpowiedź to 2 (trzeba zniszczyć sejfy 1 i 4).
*/

/*
    Idea rozwiązania polega na zwróceniu liczby rozłączych grafów w danych
    Z danych tworzę skierowany graf: sejf -> wierzchołek, klucz -> krawędź
*/

uint findMinSafeNum(Graph& g); // Zwraca najmniejsza liczbe sejfów do zniszczenia

uint test(const uint n, const int* keys); // Wypełnia graf według danych i zwraca najmniejsza liczbe sejfów do zniszczenia

int main() // testy
{
    uint n, correct, nTests, tmp;

    std::ifstream czytaj("testy.txt");
    /*
        testy.txt maja format: 
            liczba testów w pierwszej linii, nastepnie
            [ilosc sejfów] [poprawna odpowiedz] [miejsca wszystkich kluczy]
        -1 w miejscach kluczy oznacza, że do danego sejfu nie ma klucza
    */

    std::cout << "Najmniejsza liczba zniszczonych sejfow:\n";
    const auto start = std::chrono::steady_clock::now();
    czytaj >> nTests; // Liczba testów
    
    for(uint i = 0; i < nTests; ++i)
    {
        czytaj >> n >> correct;

        int* keys = new int[n];
        for(uint j = 0; j < n; ++j) // krawedzie do wczytania
        {
            czytaj >> keys[j];
        }
        tmp = test(n, keys);
        std::cout<< "\tTest " << i << " -> " << tmp << "\n";
        assert(correct == tmp);
        delete[] keys;
    }
    czytaj.close();
    const auto finish = std::chrono::steady_clock::now();

    std::cout<< "\nWszystkie testy zostały zaliczone.\nCzas wykonania: " << 
    std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms\n";
}

uint findMinSafeNum(Graph& g)
{
    assert(g.getVertexNum() > 0);
    uint disjointGraphs = 0, u;

    bool visited[g.getVertexNum()]; // Tablica odwiedzonych wierzchołków

    for(auto i = 0u; i < g.getVertexNum(); ++i) // Na start wszędzie jest 0 -> nieodwiedzony
    {
        visited[i] = 0;
    }

    std::queue<uint> que;

    for(uint v = 0; v < g.getVertexNum(); ++v) // Po każdym wierzchołku
    {
        if(visited[v] == 0)
        {
            que.push(v);
            ++disjointGraphs;
        }

        while(!que.empty()) // Przechodze po każdej możliwej krawędzi
        {
            u = que.front();
            que.pop();
            visited[u] = 1;

            for(auto i: g.allConnections(u))
            {
                if(visited[i] == 0) que.push(i);
            }
        }

    }

    return disjointGraphs;
}

uint test(const uint n, const int* keys)
{
    Graph g(n);
  
    for(auto i = 0u; i < n; ++i)
    {
        if(keys[i] != -1)
        {
            g.addEdge(keys[i], i); 
        }
    }
    // g.show(); // Wyswietla graf
    return findMinSafeNum(g);
}