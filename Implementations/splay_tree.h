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
#include <iostream>

template<typename T, typename Comp = std::less<T>>
class splay_tree
{
  public:
    splay_tree()                 { root = nullptr; lower = Comp(); }
    bool empty()                 { return root == nullptr; }
    bool insert(T const& elem)   { return insert(root, nullptr, elem); }
    bool erase(T const& elem)    { return erase( root, nullptr, elem); }
    bool search(T const& elem)   { return search(root, nullptr, elem); }
    ~splay_tree()                { free_up_memory(root); }
    void print()                 { print(root, 0); }

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

    // Atributes
    Node* root;
    Comp lower;

    // Private methods
    void splay(Node* node);                                 // Brings node pointed to the root keeping binary tree structure
    void rotateRight(Node* node);                           // Rotates right from node pointed
    void rotateLeft(Node* node);                            // Rotates left  from node pointed

    void free_up_memory(Node* node);                        // Frees up the dinamic memory occupied
    bool insert(Node* &node, Node* father, T const& elem);  // Insert elem in the subtree with node as root (true inserted)
    bool search(Node* node, Node* father, T const& elem);   // Returns true if elem is present in the subtree with node as root
    bool erase(Node* &node, Node* father, T const& elem);   // Erase elem in the subtree with node as root (true if elem was in the tree)
    Node* lessGreater(Node* node);                          // Returns a pointer to less greater node than node given
    void print(Node* node, int level);                      // Just to depurate the code
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
  if(node == nullptr)
    throw std::domain_error("Splay over null node!");

  while(node->parent)
  {
    if(!node->parent->parent)  //Direct child from root!
    {
      if(node->parent->left == node)  rotateRight(node->parent);
      else                            rotateLeft(node->parent);
    }
    else                       //Node has grandfather
    {
      Node* grandParent = node->parent->parent;

      if(grandParent->left && node == grandParent->left->left)          //Zig-zig
       {rotateRight(grandParent);
        rotateRight(node->parent);}
      else if(grandParent->right && node == grandParent->right->right)  //Zag-zag
        {rotateLeft(grandParent);
         rotateLeft(node->parent);}
      else if(grandParent->left && node == grandParent->left->right)   //Zag-Zig
        {rotateLeft(node->parent);
         rotateRight(grandParent);}
      else                                                             //Zig-zag
        {rotateRight(node->parent);
         rotateLeft(grandParent);}
    }
  }
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
    if(father     != nullptr)
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
    if(father      != nullptr)
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
  else if(lower(node->elem,elem))   return insert(node->right, node, elem);
  else if(lower(elem, node->elem))  return insert(node->left,  node, elem);
  else                             {splay(node); return false;}
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
  if(node == nullptr)               {splay(father); return false;}
  else if(lower(node->elem, elem))   return search(node->right, node, elem);
  else if(lower(node->elem, elem))   return search(node->left,  node, elem);
  else                              {splay(node);   return true;}
}

template<typename T, typename Comp>
void splay_tree<T, Comp>::print(Node* node, int level)
{
  if(node != nullptr)
  {
    std::cout << level << ':' << node->elem << " ";

    print(node->left,  level+1);
    print(node->right, level+1);
  }
}

#endif //SPLAY_TREE_H
