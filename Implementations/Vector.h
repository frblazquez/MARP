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
*   Vector TAD implementation. List of elements (generic type), accessible by
*   position in constant time and with auto expansion and contraction. The
*   implementation consists on a dinamic memory array.
*/

/*
----------------------------------------------------------------------------------------------------------
| Operation         | Cost | Worst case |            Description               |       Exceptions        |
|--------------------------------------------------------------------------------------------------------|
| vector()          | O(1) |    O(1)    |  Creates an empty vector             |                         |
| ~vector()         | O(n) |    O(n)    |  Frees the dinamic memory reserved   |                         |
| push_back(elem)   | O(1) |    O(n)    |  Adds an element to the vector end   |                         |
| push_front(elem)  | O(n) |    O(n)    |  Adds an element to the vector front |                         |
| bool empty()      | O(1) |    O(1)    |  Returns true if the vector is empty |                         |
| pop_back()        | O(1) |    O(n)    |  Deletes the last element            | out_of_range when empty |
| pop_front()       | O(n) |    O(n)    |  Deletes the first element           | out_of_range when empty |
| elem& operator [k]| O(1) |    O(1)    |  Returns de (k-1)th element          | out_of_range when k out |
| elem& front()     | O(1) |    O(1)    |  Returns the first element           | out_pf_range when empty |
| elem& back()      | O(1) |    O(1)    |  Returns the last element            | out_of_range when empty |
----------------------------------------------------------------------------------------------------------
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
using namespace std;

template<class T>
class vector
{
private:

    unsigned int numElems;
    unsigned int capacity;
    T* arrayElems;

    const int initSize = 5;            // !! >= 1 !!
    const float ampliateFactor = 2.0;   // !! >  1 !!
    const float reduceLimit = 0.25;     // !! 0 < x < 1 !!
    const float reduceFactor = 0.5;     // !! reduceLimit < x < 1 !!

public:

    vector()
    {
        numElems = 0;
        capacity = initSize;
        arrayElems = new T[capacity];
    }

    ~vector()
    {
      delete [] arrayElems;
    }

    T& operator[](int i) const
    {
        if(0 > i || i >= numElems)
            throw std::out_of_range("Out of range exception!");

        return arrayElems[i];
    }

    bool empty()
    {
      return numElems == 0;
    }

    int size()
    {
      return numElems;
    }

    void push_back(T elem)
    {
      if(numElems == capacity)
        ampliate();

      arrayElems[numElems] = elem;
      numElems++;
    }

    void push_front(T elem)
    {
      if(numElems == capacity)
        ampliate();

      for(int i = numElems; i > 0; i--)
        arrayElems[i] = arrayElems[i-1];

      arrayElems[0] = elem;
      numElems++;
    }

    void pop_back()
    {
      if(empty())
        throw std::out_of_range("The vector has no elements!");

      numElems--;

      if(capacity > initSize && float(numElems)/capacity <= reduceLimit) //Cast to float needed!
        reduce();
    }

    void pop_front()
    {
      if(empty())
        throw std::out_of_range("The vector is empty!");

      for(int i = 1; i < numElems; i++)
        arrayElems[i-1] = arrayElems[i];

      numElems--;

      if(capacity > initSize && float(numElems)/capacity <= reduceLimit) //Cast to float needed!
        reduce();
    }

    void print()
    {
      for(int i = 0; i < numElems; i++)
        cout << arrayElems[i] << " ";

      cout << endl;
    }

    T& front()
    {
      if(empty())
        throw std::out_of_range("The vector is empty!");

      return arrayElems[0];
    }

    T& back()
    {
      if(empty())
        throw std::out_of_range("The vector is empty!");

      return arrayElems[numElems -1];
    }


private:

  void ampliate()
  {
    T* arrayBefore = arrayElems;

    capacity  *= ampliateFactor;
    arrayElems = new T[capacity];

    //This won't work if the type T have not defined the operator
    //'=' as a way of copying elements.

    for(int i = 0; i < numElems; i++)
      arrayElems[i] = arrayBefore[i];

    delete [] arrayBefore;
  }

  void reduce()
  {
    T* arrayBefore = arrayElems;

    capacity *= reduceFactor;
    arrayElems = new T[capacity];

    //This won't work if the type T have not defined the operator
    //'=' as a way of copying elements.

    for(int i = 0; i < numElems; i++)
      arrayElems[i] = arrayBefore[i];

    delete [] arrayBefore;
  }

};

#endif // VECTOR_H
