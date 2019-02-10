/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Priority queue with a max-heap and dinamic behaviour.
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
  int numEvents, gravity; cin >> numEvents;
  char c; string aux;

  while(numEvents)
  {
    PriorityQueue<pair<int,pair<int,string>>> cola; // {int, int, string}

    for(int i = 0; i < numEvents; i++)
    {
      cin >> c;

      if(c == 'A')
      {
        cout << cola.top().second.second << '\n'; cola.pop();
      }
      else
      {
        cin >> aux >> gravity;
        cola.push({-gravity, {i,aux}}); // We push -1*gravity to have a reverse ordenation
      }

    }

    cout << "----\n";
    cin >> numEvents;
  }

  return 0;
}
