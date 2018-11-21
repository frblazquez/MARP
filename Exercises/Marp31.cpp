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
  int numVertex, numEdges;
  cin >> numVertex;

  while(cin)
  {
    cin >> numEdges;

    Grafo graph(numVertex);

    int origin, end;
    for(int i = 0; i < numEdges; i++)
    {
      cin >> origin >> end;
      graph.ponArista(origin, end);
    }

    if(graph.esBipartito()) cout << "SI\n";
    else                    cout << "NO\n";

    cin >> numVertex;
  }

  return 0;
}
