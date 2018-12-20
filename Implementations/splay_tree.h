/*
*   Francisco Javier Blázquez Martínez   ~  frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Computense University, Madrid
*
*   Description: Splay trees implementation.
*/

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

template<class T>
class splay_tree
{
  public:
    splay_tree();
    ~splay_tree();
    bool insert(T const& elem);
    bool erase(T const& elem);
    bool search(T const& elem);
    bool empty();

  protected:
    // Node type defined
    struct Node
    {
        T elem;
        Node* right;
        Node* left;
        Node* parent;

        Node(Node* l, T const& e, Node* r, Node* p) : left(l), elem(e), right(r), parent(p) {}
    };

    // Only attribute
    Node* root;

    // Private methods
    void splay(Node* node);                   // Brings node pointed to the root keeping binary tree structure
    void free_up_memory(Node* node);          // Frees up the dinamic memory occupied
    bool insert(Node* node, T const& elem);   // Insert elem in the subtree with node as root (true inserted)
    bool erase(Node* node, T const& elem);    // Erase elem in the subtree with node as root (true if elem was in the tree)
    bool search(Node* node, T const& elem);   // Returns true if elem is present in the subtree with node as root
};

// PUBLIC METHODS IMPLEMENTATION
template<class T>
splay_tree<T>::splay_tree()  { root = nullptr; }

template<class T>
splay_tree<T>::~splay_tree() { free_up_memory(root); }

template<class T>
bool splay_tree<T>::insert(T const& elem) {  return insert(root, elem); }

template<class T>
bool splay_tree<T>::erase(T const& elem) {  return erase(root, elem); }

template<class T>
bool splay_tree<T>::search(T const& elem) {  return search(root, elem); }

template<class T>
bool splay_tree<T>::empty() {  return root==nullptr; }

// PRIVATE METHOD IMPLEMENTATIONS
template<class T>
void splay_tree<T>::splay(Node* node)
{

}

template<class T>
void splay_tree<T>::free_up_memory(Node* node)
{

}

template<class T>
bool splay_tree<T>::insert(Node* node, T const& elem)
{

}

template<class T>
bool splay_tree<T>::erase(Node* node, T const& elem)
{

}

template<class T>
bool splay_tree<T>::search(Node* node, T const& elem)
{

}


#endif //SPLAY_TREE_H
