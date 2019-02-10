/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Find the minimum cost for an addition.
*/

/*
*   This problem is implemented following a priority queue implementation
*   not in C++ STL.
*
*   Available at: https://github.com/frblazquez/MARP/tree/master/Implementations
*/

#include <iostream>
#include "PriorityQueue.h"
using namespace std;

int main()
{
  int numElems, aux; cin >> numElems;

  while(numElems)
  {
    PriorityQueue<long long int> sumasParciales;

    for(int i = 0; i < numElems; i++)
    {cin >> aux; sumasParciales.push(aux);}

    long long int op1, op2, minEffort = 0;

    while(!sumasParciales.empty())
    {
      op1 = sumasParciales.top(); sumasParciales.pop();
      if(sumasParciales.empty()) break;
      op2 = sumasParciales.top(); sumasParciales.pop();

      sumasParciales.push(op1 + op2);
      minEffort += op1 + op2;
    }

    cout << minEffort << '\n';
    cin >> numElems;
  }

  return 0;
}
