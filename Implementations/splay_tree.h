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

#include <functional>
#include <stdexcept>

template<typename T = int, typename Comp = std::less<T>>
class splay_tree
{
  public:
    splay_tree()                 { root = nullptr; }
    bool empty()                 { return root == nullptr; }
    bool insert(T const& elem)   { return insert(root, nullptr, elem); }
    bool erase(T const& elem)    { return erase( root, nullptr, elem); }
    bool search(T const& elem)   { return search(root, nullptr, elem); }
    ~splay_tree()                { free_up_memory(root); }

  protected:
    // Node type defined
    struct Node
    {
        T elem;
        Node* right;
        Node* left;
        Node* parent;

        Node(Node* l, T const& e, Node* r, Node* p) : elem(e), right(r), left(l), parent(p) {}
    };

    // Only attribute
    Node* root;

    // Private methods
    void splay(Node* node);                                 // Brings node pointed to the root keeping binary tree structure
    void rotateRight(Node* node);                           // Rotates right from node pointed
    void rotateLeft(Node* node);                            // Rotates left  from node pointed

    void free_up_memory(Node* node);                        // Frees up the dinamic memory occupied
    bool insert(Node* &node, Node* father, T const& elem);  // Insert elem in the subtree with node as root (true inserted)
    bool search(Node* node, Node* father, T const& elem);   // Returns true if elem is present in the subtree with node as root
    bool erase(Node* &node, Node* father, T const& elem);   // Erase elem in the subtree with node as root (true if elem was in the tree)
    Node* lessGreater(Node* node);                          // Returns a pointer to less greater node than node given
};

// PRIVATE METHOD IMPLEMENTATIONS
template<typename T, typename Comp>
void splay_tree<T,Comp>::free_up_memory(Node* node)
{
  if(node != nullptr)
  {
    free_up_memory(node->left);
    free_up_memory(node->right);
    delete node;
  }
}

template<typename T, typename Comp>
void splay_tree<T, Comp>::splay(Node* node)
{

}

template<typename T, typename Comp>
void splay_tree<T, Comp>::rotateRight(Node* node)
{
  if(node == nullptr)
    throw std::domain_error("Right rotation over null node!");

  Node* father    = node->parent;
  Node* leftChild = node->left;

  if(leftChild != nullptr)
  {
    node->left        = leftChild->right;
    node->parent      = leftChild;
    leftChild->parent = father;
    leftChild->right  = node;

    if(node->left != nullptr)  node->left->parent = node;
    if(father != nullptr)
      {if(node == father->left)  father->left = leftChild;
       else                      father->right= leftChild;}
    else
      root = leftChild;
  }
}

template<typename T, typename Comp>
void splay_tree<T, Comp>::rotateLeft(Node* node)
{
  if(node == nullptr)
    throw std::domain_error("Left rotation over null node!");

  Node* father     = node->parent;    //Father
  Node* rightChild = node->right;     //Right child

  if(rightChild != nullptr)
  {
    node->right        = rightChild->left;
    node->parent       = rightChild;
    rightChild->parent = father;
    rightChild->left   = node;

    if(node->right != nullptr)  node->right->parent = node;
    if(father != nullptr)
      {if(node == father->left)  father->left = rightChild;
       else                      father->right= rightChild;}
    else
      root = rightChild;
  }
}


template<typename T, typename Comp>
bool splay_tree<T, Comp>::insert(Node* &node, Node* father, T const& elem)
{
  if(node == nullptr)
  {
    node = new Node(nullptr, elem, nullptr, father);
    splay(node);
    return true;
  }
  else if(Comp(node->elem,elem))   return insert(node->right, node, elem);
  else if(Comp(elem, node->elem))  return insert(node->left,  node, elem);
  else                            {splay(node); return false;}
}

template<typename T, typename Comp>
bool splay_tree<T, Comp>::erase(Node* &node, Node* father, T const& elem)
{
  if(node == nullptr)             {splay(father); return false;}
  else if(Comp(node->elem, elem))  return erase(node->right,node, elem);
  else if(Comp(elem, node->elem))  return erase(node->left, node, elem);
  else
  {
    Node* lessGreater = lessGreater(node);

    return true;
  }
}

template<typename T, typename Comp>
bool splay_tree<T, Comp>::search(Node* node, Node* father, T const& elem)
{
  if(node == nullptr)             {splay(father); return false;}
  else if(Comp(node->elem, elem))  return search(node->right, node, elem);
  else if(Comp(node->elem, elem))  return search(node->left,  node, elem);
  else                            {splay(node);   return true;}
}

#endif //SPLAY_TREE_H
