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

/*
---------------------------------------------------------------------------------------------
| Operation         | Cost |            Description               |       Exceptions        |
|--------------------------------------------------------------------------------------------
| queue()           | O(1) |  Creates an empty queue              |                         |
| ~queue()          | O(n) |  Frees the dinamic memory reserved   |                         |
| push(elem)        | O(1) |  Adds an element to the queue        |                         |
| pop()             | O(1) |  Deletes the first element           | out_of_range when empty |
| int size()        | O(1) |  Returns the size of the queue       |                         |
| bool empty()      | O(1) |  Returns true if the queue is empty  |                         |
| elem& front()     | O(1) |  Returns the first element           | out_of_range when empty |
---------------------------------------------------------------------------------------------
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

  unsigned int numElems;
  Node* first;
  Node* last;

public:

  queue()
  {
    numElems = 0;
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

  bool empty() const
  {
    return numElems == 0;
  }

  int size() const
  {
    return numElems;
  }

  const T& front() const
  {
    if(numElems == 0)
      throw std::domain_error("The queue is empty!");

    return first->elem;
  }

  void pop()
  {
    if(numElems == 0)
      throw std::domain_error("The queue is empty!");

    Node* aux = first;
    first = first->next;
    delete aux;
    numElems--;

    if(first == nullptr) last = nullptr;
  }

  void push(T const& elem)
  {
    Node* aux = new Node;
    aux->elem = elem;

    if(numElems == 0)
      {first = aux; last = aux;}
    else
       last->next = aux;

    last = aux;
    numElems++;
  }


};


#endif // QUEUE_H
