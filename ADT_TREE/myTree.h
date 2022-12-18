#ifndef MYTREE_H
#define MYTREE_H

#include <iostream>
#include <stack>
#include <cassert>
#include <queue>
#include <cstdlib>   // std::rand(), RAND_MAX, std::srand()
#include <limits>

// Szablon dla węzła drzewa binarnego i drzewa BST.
template <typename T>
struct BSTNode {
// the default access mode and default inheritance mode are public
    T value;
    BSTNode<T> *left, *right;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() {} // destruktor
};

// Szablon dla przypadkowego drzewa binarnego.
template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;
public:
    RandomBinaryTree() : root(nullptr) {} // konstruktor domyślny

    ~RandomBinaryTree() { clear(); } // trzeba wyczyścić

    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia

    void insert(const T& item) { root = insert(root, item); }

    //void remove(const T& item); // na razie nie usuwamy elementów

    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }

    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }

    void iter_preorder();
    void iter_inorder(); // trudne
    void iter_postorder(); // trudne

    void bfs(); // przejście poziomami (wszerz)
    void clear() { clear(root); root = nullptr; }
    void display() { display(root, 0); }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    void clear(BSTNode<T> *node);

    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const;

    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);

    void display(BSTNode<T> *node, int level);

    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }

    // Zadanie 10.2
    T calc_total(){return calc_total(root);}
    T calc_total(BSTNode<T>* node);
    T iterCalc_total();

    // Zadanie 10.1
    int calc_leafs(){return calc_leafs(root);};
    int calc_leafs(BSTNode<T>* node);
    int iterCalc_leafs();

    // Zadanie 10.3
    T findMin(){return findMin(root);};
    T findMin(BSTNode<T>* node);
    T iterFindMin();

    T findMax(){return findMax(root);};
    T findMax(BSTNode<T>* node);
    T iterFindMax();



};

// Zadanie 10.3
template <typename T>
T RandomBinaryTree<T>::findMin(BSTNode<T>* node)
{
    if(node == nullptr) return std::numeric_limits<T>::max();

    double rootV = (double)node->value;
    double leftV = findMin(node->left);
    double rightV = findMin(node->right);

    if(rootV > leftV) rootV = leftV;
    if(rootV > rightV) rootV = rightV;

    return rootV;
}

// Zadanie 10.3
template <typename T>
T RandomBinaryTree<T>::findMax(BSTNode<T>* node)
{
    if(node == nullptr) return std::numeric_limits<T>::min();

    double rootV = (double)node->value;
    double leftV = findMax(node->left);
    double rightV = findMax(node->right);

    if(rootV < leftV) rootV = leftV;
    if(rootV < rightV) rootV = rightV;

    return rootV;
}

// Zadanie 10.3
template <typename T>
T RandomBinaryTree<T>::iterFindMax()
{
    if(root == nullptr) return T();
    T maxi = root->value;

    std::queue<BSTNode<T>*> q;
    q.push(root);

    while(!q.empty())
    {
        BSTNode<T>* node = q.front();
        if(node->value > maxi) maxi = node->value;
        q.pop();

        if(node->left != nullptr)
        {
            q.push(node->left);
        }

        if(node->right != nullptr)
        {
            q.push(node->right);
        }
    }

    return maxi;
}

// Zadanie 10.3
template <typename T>
T RandomBinaryTree<T>::iterFindMin()
{
    if(root == nullptr) return T();
    T mini = root->value;

    std::queue<BSTNode<T>*> q;
    q.push(root);

    while(!q.empty())
    {
        BSTNode<T>* node = q.front();
        if(node->value < mini) mini = node->value;
        q.pop();

        if(node->left != nullptr)
        {
            q.push(node->left);
        }

        if(node->right != nullptr)
        {
            q.push(node->right);
        }
    }

    return mini;
}


// Zadanie 10.1
template <typename T>
int RandomBinaryTree<T>::calc_leafs(BSTNode<T>* node)
{
    if(node == nullptr) return T();
    else if (node->left == nullptr && node->right == nullptr){
        return 1;
    }else{
        return calc_leafs(node->left) + calc_leafs(node->right);
    }
}

// Zadanie 10.1
template <typename T>
int RandomBinaryTree<T>::iterCalc_leafs()
{
    if(root == nullptr) return T();
    int sum = 0;

    std::queue<BSTNode<T>*> q;
    q.push(root);

    while(!q.empty())
    {
        BSTNode<T>* node = q.front();
        if(node->left == nullptr && node->right == nullptr) sum++;
        q.pop();

        if(node->left != nullptr)
        {
            q.push(node->left);
        }

        if(node->right != nullptr)
        {
            q.push(node->right);
        }
    }

    return sum;
}

// Zadanie 10.2
template <typename T>
T RandomBinaryTree<T>::calc_total(BSTNode<T>* node)
{
    if(node == nullptr) return T();
    else{
        return node->value + calc_total(node->left) + calc_total(node->right);
    }
}

// Zadanie 10.2
template <typename T>
T RandomBinaryTree<T>::iterCalc_total()
{
    if(root == nullptr) return T();
    double sum = 0;

    std::queue<BSTNode<T>*> q;
    q.push(root);

    
    while(!q.empty())
    {
        BSTNode<T>* node = q.front();
        sum += node->value;
        q.pop();

        if(node->left != nullptr)
        {
            q.push(node->left);
        }

        if(node->right != nullptr)
        {
            q.push(node->right);
        }
    }

    return sum;
}

template <typename T>
void RandomBinaryTree<T>::clear(BSTNode<T> *node)
{
    if(node == nullptr) return;

    clear(node->left);
    clear(node->right);

    delete node;
}

// Wyświetlanie obróconego (counterclockwise) drzewa binarnego.
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    std::cout << std::string(3 * level, ' ') << node->value << std::endl;
    display(node->left, level + 1);
}


template <typename T>
BSTNode<T> * RandomBinaryTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (std::rand() % 2) { // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzen
}

template <typename T>
BSTNode<T> * RandomBinaryTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    }
    T* ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr) {
        ptr = search(node->right, item);
    }
    return ptr;
}

template <typename T>
void RandomBinaryTree<T>::bfs() {
    if (root == nullptr) return;
    std::queue<BSTNode<T>*> Q; // wskaźniki do wezłów
    BSTNode<T> *node = root;

    Q.push(node);
    while (!Q.empty()) {
        node = Q.front(); // podglądamy
        Q.pop();        // usuwamy z kolejki
        visit(node); // tu jest właściwe przetworzenie węzła
        if (node->left != nullptr)
            Q.push(node->left);
        if (node->right != nullptr)
            Q.push(node->right);
    }
}

template <typename T>
void RandomBinaryTree<T>::inorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::preorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::postorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

template <typename T>
void RandomBinaryTree<T>::iter_preorder() {
    if (root == nullptr) return;
    std::stack<BSTNode<T>*> S; // wskaźniki do węzłów
    BSTNode<T> *node = root;
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podglądamy
        S.pop();        // usuwamy ze stosu
        visit(node); // tu jest właściwe przetworzenie węzła
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}

#endif