/*
*   Copyright (c) 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics-Computer engineering.
*   Complutense university, Madrid.
*
*
*   Description:
*
*/

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template<class T>
class binary_tree
{

private:

  struct TreeNode
  {
    T elem;
    TreeNode* left;
    TreeNode* right;
  };

  unsigned int numElems;
  TreeNode * root;

public:

  binary_tree()
  {
    numElems = 0;
    root = nullptr;
  }

  ~binary_tree()
  {
    libera(root);
  }

  bool empty() const
  {
    return numElems == 0;
  }

  int size() const
  {
    return numElems;
  }

  void insert(T const& elem)
  {
    
  }

private:

  void libera(TreeNode* ptr)
  {
    if(ptr != nullptr)
    {
      libera(ptr->left);
      libera(ptr->right);
      delete ptr;
    }
  }
};


#endif // BINARY_TREE_H
