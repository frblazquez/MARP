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

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>
using namespace std;

template<class T>
class vector
{
private:

    unsigned int size;
    unsigned int capacity;
    T* arrayElems;

    const int initSize = 10;            // !! >= 1 !!
    const float ampliateFactor = 2.0;   // !! >  1 !!
    const float reduceLimit = 0.25;     // !! 0 < x < 1 !!
    const float reduceFactor = 0.5;     // !! reduceLimit < x < 1 !!

public:

    vector()
    {
        size = 0;
        capacity = initSize;
        arrayElems = new T[capacity];
    }

    ~vector()
    {
      delete [] arrayElems;
    }

    T& operator[](int i) const
    {
        if(0 > i || i >= size)
            throw std::out_of_range("Out of range exception!");

        return arrayElems[i];
    }

    void push_back(T elem)
    {
      if(size == capacity)
        ampliate();

      arrayElems[size] = elem;
      size++;
    }

    void push_front(T elem)
    {
      if(size == capacity)
        ampliate();

      for(int i = size; i > 0; i--)
        arrayElems[i] = arrayElems[i-1];

      arrayElems[0] = elem;
      size++;
    }

    void pop_back()
    {
      size--;

      if(size/capacity <= reduceFactor)
        reduce();
    }

    void pop_front()
    {
      for(int i = 1; i < size; i++)
        arrayElems[i-1] = arrayElems[i];

      size--;

      if(size/capacity <= reduceFactor)
        reduce();
    }

    void print()
    {
      for(int i = 0; i < size; i++)
        cout << arrayElems[i] << " ";

      cout << endl;
    }

    T& front()
    {
      return arrayElems[0];
    }

    T& back()
    {
      return arrayElems[size -1];
    }

    bool empty()
    {
      return size == 0;
    }

private:

  void ampliate()
  {
    T* arrayBefore = arrayElems;

    capacity  *= ampliateFactor;
    arrayElems = new T[capacity];

    //This won't work if the type T have not defined the operator
    //'=' as a way of copying elements.

    for(int i = 0; i < size; i++)
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

    for(int i = 0; i < size; i++)
      arrayElems[i] = arrayBefore[i];

    delete [] arrayBefore;
  }

};

#endif // VECTOR_H
