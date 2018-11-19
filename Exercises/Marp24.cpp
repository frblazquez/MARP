/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include "PriorityQueue.h"
using namespace std;

int main()
{
  int numValues; cin >> numValues;

  while(numValues)
  {
    PriorityQueue<int> underMedian;
    PriorityQueue<int> overMedian;

    int aux; cin >> aux;
    underMedian.push(-aux);

    cout << 2*aux; if(numValues != 1) cout << " ";

    for(int i = 1; i < numValues; i++)
    {
      cin >> aux;

      // We insert the elem
      if(aux <= -underMedian.top())
        underMedian.push(-aux);
      else
        overMedian.push(aux);

      // Forbidden cases:
      if(underMedian.size() > overMedian.size() + 1)
      {
        overMedian.push(-underMedian.top());
        underMedian.pop();
      }
      if(overMedian.size() > underMedian.size())
      {
        underMedian.push(-overMedian.top());
        overMedian.pop();
      }

      // Base cases:
      if(underMedian.size() == overMedian.size()+1)
        cout << 2*(-underMedian.top());

      if(underMedian.size() == overMedian.size())
        cout << overMedian.top() - underMedian.top();

      if(numValues != i+1) cout << " ";
    }

    cout << '\n';
    cin >> numValues;
  }

  return 0;
}
