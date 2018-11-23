/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include "GrafoValorado.h"
using namespace std;

int main()
{
  int numIslands, numBridges; cin >> numIslands >> numBridges;
  int init,end, cost;

  while(cin)
  {
    GrafoValorado<int> archipelago(numIslands);

    for(int i = 0; i < numBridges; i++)
    {
      cin >> init >> end >> cost;
      archipelago.ponArista({init-1,end-1,cost});
    }

    int minCost = archipelago.recorreTodosBarato();

    if(minCost == -1) cout << "No hay puentes suficientes\n";
    else              cout << minCost << '\n';

    cin >> numIslands >> numBridges;
  }

  return 0;
}
