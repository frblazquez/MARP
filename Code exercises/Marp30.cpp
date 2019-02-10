/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Size of the maximum connected component of a graph.
*/

/*
*   This problem is implemented following a graph implementation available at: 
*   https://github.com/frblazquez/MARP/tree/master/Implementations
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
      friends.ponArista(init-1, end-1);     // We add the edge
    }

    cout << friends.numElemsMayorCompConexa() << endl;
  }

  return 0;
}


/*
*   This method should be added to Graph class.
*

int numElemsMayorCompConexa() const
{
  if(_V == 0)  return 0;

  std::vector<bool> marcados(_V, false);   // Para marcar los vértices visitados
  std::vector<int>  pendientes;            // Para guardar los vértices por explorar
  int maxElemsComponente = 1, numElemsEstaComponente;

  for(int i = 0; i < _V; i++)
  {
    if(!marcados[i])
    {
    numElemsEstaComponente = 1;

    pendientes.push_back(i);
    marcados[i] = true;

    while(!pendientes.empty())
    {
      int vertex = pendientes.back(); pendientes.pop_back();

      for(int j = 0; j < _ady[vertex].size(); j++)
      {
        int ady = _ady[vertex][j]; // ady es adyacente a vertex

        // Si el vértice no está marcado, uno más de la componente conexa
        if(!marcados[ady])
        {
          numElemsEstaComponente++;
          pendientes.push_back(ady);
          marcados[ady] = true;

          if(numElemsEstaComponente > maxElemsComponente)
             maxElemsComponente = numElemsEstaComponente;
        }
      }
    }
  }
  }

  return maxElemsComponente;
}*/
