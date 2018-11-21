/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include "Grafo.h"
using namespace std;

int main()
{
  int numCases; cin >> numCases;
  int numVertex, numEdges;
  int init, end;

  while(numCases--)
  {
    cin >> numVertex >> numEdges;

    Grafo friends(numVertex);

    for(int i = 0; i < numEdges; i++)
    {
      cin >> init >> end;
      friends.ponArista(init-1, end-1);
    }

    cout << friends.numElemsMayorCompConexa() << endl;
  }

  return 0;
}
