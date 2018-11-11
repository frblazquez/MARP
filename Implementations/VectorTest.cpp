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
*   Test for the vector class designed.
*
*/

#include "Vector.h"
#include <assert.h>
#include <iostream>
using namespace std;

int main()
{
  vector<int> v;

  assert(v.size() == 0);

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_front(0);

  v.print();

  assert(v.size() == 6);
  assert(v.front() == 0);
  assert(v.back() == 5);
  assert(v[1] == 1);
  assert(v[2] == 2);
  assert(v[5] == 5);

  v.pop_back();
  v.pop_back();
  v.pop_back();
  v.pop_back();

  return 0;
}
