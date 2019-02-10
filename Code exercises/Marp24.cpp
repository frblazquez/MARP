/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Keep the median of a set of numbers in spite of insertions.
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
  int numValues; cin >> numValues;

  while(numValues)
  {
    PriorityQueue<int> underMedian;     // Two heaps, they transfer data each other
    PriorityQueue<int> overMedian;      // to keep the size invariant

    int aux; cin >> aux;
    underMedian.push(-aux);             // -1*aux to have reverse ordenation (max heap)

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
