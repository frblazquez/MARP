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
  int numVertex, numEdges; cin >> numVertex >> numEdges;
  int init,end,width, numQueries;

  while(cin)
  {
    GrafoValorado<int> streetMap(numVertex);

    for(int i = 0; i<numEdges; i++)
    {
      cin >> init >> end >> width;

      streetMap.ponArista({init-1,end-1,width});
    }

    cin >> numQueries;

    for(int i = 0; i<numQueries; i++)
    {
      cin >> init >> end >> width;

      if(streetMap.puedePasar(init-1,end-1,width))  cout << "SI\n";
      else                                          cout << "NO\n";
    }

    cin >> numVertex >> numEdges;
  }

  return 0;
}
