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
    splay_tree()                  {root = nullptr; lower = Comp();}
   ~splay_tree()                  {free_up_memory(root);}

    void print()                  {print(root, 0);}
    bool empty()                  {return root == nullptr;}
    void stupid_test()            {splay(nullptr);}

    //For iterative implementations
    bool insert(T const& elem);
    bool erase(T const& elem);
    bool find(T const& elem);

    //For recursive implementations
    //bool find(Node* node, Node* father, T const& elem);
    //bool insert(Node* &node, Node* father, T const& elem);
    //bool erase(Node* &node, Node* father, T const& elem);

  protected:

    struct Node
    {
      T     elem;
      Node* left;
      Node* right;
      Node* parent;

      Node(Node* l, T const& e, Node* r, Node* p) : elem(e),left(l),right(r),parent(p) {}
    };

    Node* root;
    Comp  lower;

    void splay(Node* node);                                 // Brings node pointed to the root keeping binary tree structure
    void rotateRight(Node* node);                           // Rotates right from node pointed
    void rotateLeft(Node* node);                            // Rotates left  from node pointed

    void free_up_memory(Node* node);                        // Frees up the dinamic memory occupied
    void print(Node* node, int level);                      // Just to depurate the code
};


template<typename T, typename Comp>
void splay_tree<T, Comp>::rotateRight(Node* node)
{
  if(node == nullptr)
    throw std::domain_error("Right rotation over null node!");

  Node* father    = node->parent;   //Father
  Node* leftChild = node->left;     //Left child

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

      if(grandParent->left       && node == grandParent->left->left)    //Zig-zig
       {rotateRight(grandParent);
        rotateRight(node->parent);}
      else if(grandParent->right && node == grandParent->right->right)  //Zag-zag
        {rotateLeft(grandParent);
         rotateLeft(node->parent);}
      else if(grandParent->left  && node == grandParent->left->right)   //Zag-Zig
        {rotateLeft(node->parent);
         rotateRight(grandParent);}
      else if(grandParent->right && node == grandParent->right->left)   //Zig-zag
        {rotateRight(node->parent);
         rotateLeft(grandParent);}
      else
        throw "Illegal state reached during splay operation!";
    }
  }
}

template<typename T, typename Comp>
bool splay_tree<T, Comp>::insert(T const& elem)
{
  Node* father = nullptr; Node* node = root;

  while(node != nullptr)
  {
    father = node;

         if(lower(elem, node->elem))     node = node->left;
    else if(lower(node->elem, elem))     node = node->right;
    else {splay(node); return false;} // The element is already in the tree
  }

  node = new Node(nullptr, elem, nullptr, father);

  if(father != nullptr)
    {if(lower(elem, father->elem)) father->left = node;
     else                          father->right= node;}
  else
    root = node;

  splay(node);  return true;
}

/*
template<typename T, typename Comp>
bool splay_tree<T, Comp>::insert(Node* &node, Node* father, T const& elem)
{
  if(node == nullptr)
  {
    node = new Node(nullptr, elem, nullptr, father);
    splay(node);
    return true;
  }
  else if(less(node->elem,elem))   return insert(node->right, node, elem);
  else if(less(elem, node->elem))  return insert(node->left,  node, elem);
  else                             {splay(node); return false;}
}
*/

template<typename T, typename Comp>
bool splay_tree<T, Comp>::find(T const& elem)
{
  Node* father = nullptr; Node* node = root;

  while(node != nullptr)
  {
    father = node;

         if(lower(elem, node->elem))     node = node->left;
    else if(lower(node->elem, elem))     node = node->right;
    else {splay(node); return true;} // The element is already in the tree
  }

  if(father != nullptr) splay(father);

  return false;
}

/*
template<typename T, typename Comp>
bool splay_tree<T, Comp>::search(Node* node, Node* father, T const& elem)
{
  // WARNING!!
  // Case when node is the rooot is not controlled!!
  if(node == nullptr)               {splay(father); return false;}
  else if(lower(node->elem, elem))   return search(node->right, node, elem);
  else if(lower(node->elem, elem))   return search(node->left,  node, elem);
  else                              {splay(node);   return true;}
}
*/

template<typename T, typename Comp>
bool splay_tree<T, Comp>::erase(T const& elem)
{
  Node* father = nullptr; Node* node = root;

  while(node)
  {
         if(lower(elem, node->elem))   {father = node; node = node->left;}
    else if(lower(node->elem, elem))   {father = node; node = node->right;}
    else break; // node points to a node with elem inside
  }

  if(node == nullptr) {if(father) splay(father); return false;}

  if(!node->left && !node->right)   // LEAF CASE
  {
    if(node->parent == nullptr) root = nullptr;
    else
    {
      if(node == node->parent->left)  node->parent->left = nullptr;
      else                            node->parent->right= nullptr;
    }
  }
  else if(!node->left)              // ONLY RIGHT SUBTREE
  {
    if(node->parent == nullptr) {root = node->right; root->parent = nullptr;}
    else
    {
      node->right->parent = node->parent;
      if(node == node->parent->left)  node->parent->left = node->right;
      else                            node->parent->right= node->right;
    }
  }
  else if(!node->right)             // ONLY LEFT SUBTREE
  {
      if(node->parent == nullptr) {root = node->left;  root->parent = nullptr;}
      else
      {
        node->left->parent = node->parent;
        if(node == node->parent->left)  node->parent->left = node->left;
        else                            node->parent->right= node->left;
      }
  }
  else                              // BOTH CHILDREN EXISTS
  {
    // We get the less greater
    Node* lessGreater = node->right; while(lessGreater->left) lessGreater = lessGreater->left;

    // We 'disconnect' it temporally from its position
    if(lessGreater->right)
    {
      lessGreater->right->parent = lessGreater->parent;

      if(lessGreater == lessGreater->parent->right) lessGreater->parent->right = lessGreater->right;
      else                                          lessGreater->parent->left  = lessGreater->right;
    }
    else
    {
      if(lessGreater == lessGreater->parent->right)  lessGreater->parent->right = nullptr;
      else                                           lessGreater->parent->left  = nullptr;
    }

    // We replace node to delete with the less greater element
    lessGreater->left  = node->left;   if(node->left)   node->left->parent = lessGreater;
    lessGreater->right = node->right;  if(node->right)  node->right->parent= lessGreater;
    lessGreater->parent= node->parent;

    if(node->parent)
      {if(node == node->parent->left) node->parent->left = lessGreater;
       else                           node->parent->right= lessGreater;}
    else
      root = lessGreater;
  }

  delete node;  if(father) splay(father);
  return true;
}

/*
template<typename T, typename Comp>
bool splay_tree<T, Comp>::erase(Node* &node, Node* father, T const& elem)
{
  // WARNING!!
  // Case when node is the rooot is not controlled!!
  if(node == nullptr)              {splay(father); return false;}
  else if(lower(node->elem, elem))  return erase(node->right,node, elem);
  else if(lower(elem, node->elem))  return erase(node->left, node, elem);
  else // node points the node we want to delete!
  {
    // Before the deletion we are going to preserve the binary tree structure
    if(!node->right && !node->left) // Leaf case
    {
      std::cout << "Borrando una hoja\n";

      if(node->parent == nullptr) root = nullptr;
      else
      {
        if(node == node->parent->left)  node->parent->left = nullptr;
        else                            node->parent->right= nullptr;
      }
    }
    else if(!node->right)           // Node to delete hasn't right subtree
    {
      std::cout << "Borrando un nodo sin hijo derecho\n";

      if(node->parent == nullptr) {root = node->left;  root->parent = nullptr;}
      else
      {
        node->left->parent = node->parent;
        if(node == node->parent->left)  node->parent->left = node->left;
        else                            node->parent->right= node->left;
      }
    }
    else if(!node->left)            // Node to delete hasn't left  subtree
    {
      std::cout << "Borrando un nodo sin hijo izquierdo\n";

      if(node->parent == nullptr) {root = node->right; root->parent = nullptr;}
      else
      {
        node->right->parent = node->parent;
        if(node == node->parent->left)  node->parent->left = node->right;
        else                            node->parent->right= node->right;
      }
    }
    else                            // We have right and left subtree
    {
      std::cout << "Borrando un nodo de los chungos\n";
      // We get the less greater
      Node* lessGreater = node->right; while(lessGreater->left) lessGreater = lessGreater->left;

      // We 'disconnect' it temporally from its position
      if(lessGreater->right)
      {
        if(lessGreater == lessGreater->parent->right)
         {lessGreater->parent->right = lessGreater->right;
          lessGreater->right->parent = lessGreater->parent;}
        else
         {lessGreater->parent->left  = lessGreater->right;
          lessGreater->right->parent = lessGreater->parent;}
      }
      else
      {
        if(lessGreater == lessGreater->parent->right)  lessGreater->parent->right = nullptr;
        else                                           lessGreater->parent->left  = nullptr;
      }

      // We replace node to delete with the less greater element
      lessGreater->left  = node->left;   if(node->left)   node->left->parent = lessGreater;
      lessGreater->right = node->right;  if(node->right)  node->right->parent= lessGreater;
      lessGreater->parent= node->parent;

      if(node->parent)
        {if(node == node->parent->left) node->parent->left = lessGreater;
         else                           node->parent->right= lessGreater;}
      else
        root = lessGreater;
    }

    delete node;
    return true;
  }
}
*/

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

#endif //SPLAY_TREE_H
