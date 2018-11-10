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

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template<class T>
class queue
{
private:

  struct Node
  {
    T elem;
    Node* next;

    Node() : elem(), next(nullptr) {}
  };

  unsigned int size;
  Node* first;
  Node* last;

public:

  queue()
  {
    size  = 0;
    first = nullptr;
    last  = nullptr;
  }

  ~queue()
  {
    Node* aux;

    while(first != nullptr)
    {
      aux = first;
      first = first->next;
      delete aux;
    }

    last = nullptr;
  }

  bool empty()
  {
    return size == 0;
  }

  T& front()
  {
    return first->elem;
  }

  void pop()
  {
    if(size == 0)
      throw std::domain_error("The queue is empty!");

    Node* aux = first;
    first = first->next;
    delete aux;
    size--;

    if(first == nullptr) last = nullptr;
  }


};


#endif // QUEUE_H
