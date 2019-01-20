/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include "GrafoDirigidoValorado.h"
using namespace std;

int main()
{
  int numVertex,aux; cin >> numVertex;
  int numEdges, init,end, findTime, totalTime;

  while(numVertex)
  {
    vector<int> page_loadTime;
    GrafoDirigidoValorado<int> internet(numVertex);

    for(int i = 0; i < numVertex; i++)
    {cin >> aux; page_loadTime.push_back(aux);}

    cin >> numEdges;

    for(int i = 0; i < numEdges; i++)
    {
      cin >> init >> end >> findTime;
      internet.ponArista({init-1,end-1,findTime + page_loadTime[end-1]});
    }

    totalTime = internet.dePrimeroAUltimoRapido();

    if(totalTime == -1) cout << "IMPOSIBLE\n";
    else                cout << totalTime + page_loadTime[0] << '\n';

    cin >> numVertex;
  }

  return 0;
}

//----------------------------------------------------------------------------//
//---------------------------- MARP38.CPP ------------------------------------//

   /*
      This method returns the minimum cost of going from vertex 0 to vertex _V-1.
      If this is not possible returns -1 as error value.
   //
   int dePrimeroAUltimoRapido()
   {
     bool marcado[_V];            for(int i=0; i<_V; i++) marcado[i] = false;
     int  minCostFrom0[_V];
     std::vector<int> nexts;

     marcado[0] = true;
     minCostFrom0[0] = 0;
     nexts.push_back(0);

     int vertex, adyacente, edgeCost, vertexCost;

     while(!nexts.empty())
     {
       vertex = nexts.back(); nexts.pop_back();
       vertexCost = minCostFrom0[vertex];

       for(int j = 0; j < _ady[vertex].size(); j++)
       {
         adyacente = _ady[vertex][j].to();
         edgeCost =  _ady[vertex][j].valor();

         if(!marcado[adyacente] || vertexCost+edgeCost < minCostFrom0[adyacente])
         {
           marcado[adyacente]      = true;
           minCostFrom0[adyacente] = vertexCost + edgeCost;

           //Solo nos interesa explorar caminos que nos lleven más rápido al último vértice
           if(!marcado[_V-1] || minCostFrom0[adyacente]<minCostFrom0[_V-1])
           nexts.push_back(adyacente);
         }
       }

     }

     if(marcado[_V-1])  return minCostFrom0[_V-1];
     else               return -1;
   }

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------*/
