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
  int numEvents, gravity; cin >> numEvents;
  char c; string aux;

  while(numEvents)
  {
    PriorityQueue<pair<int,pair<int,string>>> cola;

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
        cola.push({-gravity, {i,aux}});
      }

    }

    cout << "----\n";
    cin >> numEvents;
  }

  return 0;
}
