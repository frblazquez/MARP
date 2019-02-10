/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Detect overlap in a set of tasks.
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
  int numTasks, numPeriodTasks, minsCheck;

  cin >> numTasks >> numPeriodTasks >> minsCheck;

  while(cin)
  {
    PriorityQueue<pair<int,pair<int,int>>> cola;

    int init,end,period;

    for(int i = 0; i < numTasks; i++)
    {
      cin >> init >> end;

      cola.push({init, {end-init, -1}});
    }

    for(int i = 0; i < numPeriodTasks; i++)
    {
      cin >> init >> end >> period;

      cola.push({init, {end-init, period}});
    }

    bool overlap = false;

    int lastInit   = cola.top().first;
    int lastLong   = cola.top().second.first;
    int lastPeriod = cola.top().second.second;
    cola.pop();

    if(lastPeriod != -1)
      cola.push({(lastInit + lastPeriod), {lastLong, lastPeriod}});

    while(!overlap && !cola.empty() && (cola.top().first)< minsCheck)
    {
      if(cola.top().first < lastInit + lastLong)
        overlap = true;

      else
      {
        lastInit   = cola.top().first;
        lastLong   = cola.top().second.first;
        lastPeriod = cola.top().second.second;
        cola.pop();

        if(lastPeriod != -1)
          cola.push({(lastInit + lastPeriod), {lastLong, lastPeriod}});
      }
    }

    if(overlap) cout << "SI\n";
    else        cout << "NO\n";

    cin >> numTasks >> numPeriodTasks >> minsCheck;
  }

  return 0;
}
