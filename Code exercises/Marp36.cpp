/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Is it possible for a truck with a width given
*              to move from a point to other in a city?
*/

/*
*   This problem is implemented following a graph implementation available at: 
*   https://github.com/frblazquez/MARP/tree/master/Implementations
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

/*
  PROBLEMA 36 MÉTODOS ALGORÍTMICOS EN RESOLUCIÓN DE PROBLEMAS

  Devuelve true si existe un camino entre el vértice ini y end donde en todas
  las aristas del camino se verifica que valor_arista > value.

  En el caso del problema del camión devuelve true si existe un camino entre
  los dos vértices por el que puede transitar un camión de anchura value.

 bool puedePasar(int init, int end, Valor value)
 {
   bool esPosible = false;
   int vertex, adyacente; Valor edgeValue;
   bool marcado[_V];  for(int i=0;i<_V;i++) marcado[i] = false;
   std::vector<int> nexts;

   nexts.push_back(init);
   marcado[init] = true;

   while(!esPosible && !nexts.empty())
   {
      vertex = nexts.back(); nexts.pop_back();

      for(int j=0; j<_ady[vertex].size() && !esPosible; j++)
      {
        adyacente = _ady[vertex][j].otro(vertex);
        edgeValue = _ady[vertex][j].valor();

        if(edgeValue >= value)
        {
          if(adyacente == end) esPosible=true;
          else if(!marcado[adyacente])
          {
            marcado[adyacente] = true;
            nexts.push_back(adyacente);
          }
        }
      }
   }

   return esPosible;
 }*/
