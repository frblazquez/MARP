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

#include <iostream>
#include "Queue.h"
#include <assert.h>
using namespace std;

int main()
{
  queue<int> cola;

  assert(cola.size() == 0);

  cola.push(0);
  cola.push(1);
  cola.push(2);
  cola.push(3);

  assert(cola.front() == 0); cola.pop(); cout << cola.front() << endl;
  assert(cola.front() == 1); cola.pop(); cout << cola.front() << endl;
  assert(cola.front() == 2); cola.pop(); cout << cola.front() << endl;
  assert(cola.front() == 3); cola.pop(); cout << cola.front() << endl; //Exception

  return 0;
}
