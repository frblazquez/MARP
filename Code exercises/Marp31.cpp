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

//----------------------------------------------------------------------------//
//--------------------------- MÉTODOS AÑADIDOS -------------------------------//
//----------------------------------------------------------------------------//
// Francisco Javier Blázquez Martínez ----------------------- frblazqu@ucm.es //
/*
bool esBipartito() const
{
  if(_V <= 1)  return true;

  bool bipartito = true, oposite;
  int vertex, adyacente;

  bool marcado[_V];    for(int i = 0; i < _V; i++) marcado[i]   = false;
  bool rojoNegro[_V];  for(int i = 0; i < _V; i++) rojoNegro[i] = false;
  std::vector<int> pendientes;

  for(int i = 0; i < _V && bipartito; i++)
  {
    if(!marcado[i])
    {
      pendientes.push_back(i);
      marcado[i] = true;      // Lo marcamos como visitado
      rojoNegro[i] = true;    // El primer vértice de la componente conexa es rojo (true)

      while(!pendientes.empty() && bipartito)
      {
        vertex   = pendientes.back(); pendientes.pop_back(); // Tomamos el vértice
        oposite  = (rojoNegro[vertex]? false : true);        // Color distinto para los adyacentes

        for(int j=0; j<_ady[vertex].size(); j++)
        {
          adyacente = _ady[vertex][j];             // Tomamos el vértice adyacente

          if(!marcado[adyacente])
          {
            marcado[adyacente]   = true;
            rojoNegro[adyacente] = oposite;
            pendientes.push_back(adyacente);
          }
          else bipartito &= (rojoNegro[adyacente] == oposite);
        }
      }

    }
  }

  return bipartito;
}
*/
