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

template<typename T, typename Comp = std::less<T>>
class splay_tree
{
  public:
    splay_tree()                 { root = nullptr; }
    bool empty()                 { return root == nullptr; }
    bool insert(T const& elem)   {      }
    bool erase(T const& elem)    {      }
    bool search(T const& elem)   {      }
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
    bool erase(Node* &node, Node* father, T const& elem);   // Erase elem in the subtree with node as root (true if elem was in the tree)
    bool search(Node* node, Node* father, T const& elem);   // Returns true if elem is present in the subtree with node as root
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
  while(node->parent != nullptr)
  {
    if(node->parent->parent == nullptr)
    {
      if(node->parent->left == node)  rotateRight(node->parent);
      else                            rotateLeft(node->parent);
    }
    else if(node->parent->parent->left == node->parent) // grandfather -left child- father
    {
      if(node->parent->left == node){                    // father -left child- node
        rotateRight(node->parent->parent);
        rotateRight(node->parent);
      } else {                                            // father -right child- node
        rotateLeft(node->parent);
        rotateRight(node->parent);
      }
    } else {                                               // grandfather -right child- father
      if(node->parent->right == node){                 // father -right child- node
        rotateLeft(node->parent->parent);
        rotateLeft(node->parent);
      } else {                                             // father -left child- node
        rotateRight(node->parent);
        rotateLeft(node->parent);
      }
    }
  }
}

template<typename T, typename Comp>
void splay_tree<T, Comp>::rotateRight(Node* node)
{

}

template<typename T, typename Comp>
void splay_tree<T, Comp>::rotateLeft(Node* node)
{

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
  if(node == nullptr)         {splay(father); return false;}
  else if(node->elem > elem)  return erase(node->left, node, elem);
  else if(node->elem < elem)  return erase(node->right,node, elem);
  else
  {


    return true;
  }
}

template<typename T, typename Comp>
bool splay_tree<T, Comp>::search(Node* node, Node* father, T const& elem)
{
  if(node == nullptr)             {splay(father); return false;}
  else if(node->elem == elem)     {splay(node);   return true;}
  else if(node->elem >  elem)      return search(node->left, node, elem);
  else                             return search(node->right, node, elem);
}


#endif //SPLAY_TREE_H
