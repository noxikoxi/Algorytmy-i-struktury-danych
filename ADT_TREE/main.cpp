#include "myTree.h"

int main()
{
    RandomBinaryTree<int> tree;

    for(int i = 1; i < 10; ++i)
    {
        tree.insert(i);
    }
    
    tree.display();
    std::cout << "Suma rekurencyjnie -> " << tree.calc_total() << "\n";
    std::cout << "Suma iteracyjnie -> " << tree.iterCalc_total() << "\n";

    std::cout << "Ilosc lisci rekurencyjnie -> " << tree.calc_leafs() << "\n";
    std::cout << "Ilosc lisci iteracyjnie -> " << tree.iterCalc_leafs() << "\n";

    std::cout << "Min rekurencyjnie -> " << tree.findMin() << "\n";
    std::cout << "Max rekurencyjnie -> " << tree.findMax() << "\n";

    std::cout << "Min iteracyjnie -> " << tree.iterFindMin() << "\n";
    std::cout << "Max iteracyjnie -> " << tree.iterFindMax() << "\n";
}

