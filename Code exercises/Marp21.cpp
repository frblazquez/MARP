/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Data sending in a dinamic order.
*/

/*
*   This problem is implemented following a priority queue implementation
*   not in C++ STL.
*
*   Available at: https://github.com/frblazquez/MARP/tree/master/Implementations
*/

#include <iostream>
#include "PriorityQueue.h"
#include <unordered_map>
using namespace std;

int main()
{
  int numUsers; cin >> numUsers;
  int id, period, requests;

  while(numUsers)
  {
    PriorityQueue<pair<int,int>> cola;
    unordered_map<int,int> userId_period;

    for(int i = 0; i < numUsers; i++)
    {
      cin >> id >> period;

      cola.push({period,id});
      userId_period[id] = period;
    }

    cin >> requests;

    int nextId, nextTime;

    for(int i = 0; i < requests; i++)
    {
      nextId   = cola.top().second;
      nextTime = cola.top().first;
      cola.pop();
      cola.push({nextTime + userId_period[nextId], nextId});

      cout << nextId << '\n';
    }

    cout << "----\n";
    cin >> numUsers;
  }

  return 0;
}
