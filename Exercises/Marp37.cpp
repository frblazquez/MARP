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
  int numIslas, numPuentes, ini, fin, coste, minCosteProyecto;
  cin >> numIslas;

  while(cin)
  {
    cin >> numPuentes;

    GrafoValorado<int> conexiones(numIslas);

    for(int i = 0; i < numPuentes; i++)
    {
      cin >> ini >> fin >> coste;
      conexiones.ponArista({ini-1, fin-1, coste});
    }

    minCosteProyecto = conexiones.minCoste();

    if(minCosteProyecto == -1)  cout << "No hay puentes suficientes\n";
    else                        cout << minCosteProyecto << '\n';

    cin >> numIslas;
  }

  return 0;
}

/*
   MARP 37 - ALGORITMO DE PRIM

   Minimo coste de un camino que pase por todos los vértices

int minCoste()
{
  int minCoste = 0, numAristas = 0, ini, fin, coste;               //Parámetros de control
  priority_queue<pair<int, pair<int,int>>> aristas;                //Cola de prioridad de aristas
  bool marcado[_V]; for(int i = 0; i < _V; i++) marcado[i]=false;  //Para saber si un vértice ya está unido

  //Empezamos por el cero
  marcado[0] = true;

  for(int i = 0; i < _ady[0].size(); i++)
  {
    fin   = _ady[0][i].otro(0);
    coste = _ady[0][i].valor();

    aristas.push({-coste, {0, fin}});
  }

  //Vamos ampliando nuestro camino
  while(numAristas != _V-1 && !aristas.empty())
  {
    ini   = aristas.top().second.first;
    fin   = aristas.top().second.second;
    coste = aristas.top().first*(-1);
    aristas.pop();

    if(!marcado[fin])
    {
      marcado[fin] = true;
      numAristas++;
      minCoste += coste;

      for(int i = 0; i < _ady[fin].size(); i++)
      {
        if(!marcado[_ady[fin][i].otro(fin)])
          aristas.push({-_ady[fin][i].valor(), {fin, _ady[fin][i].otro(fin)}});
      }
    }
  }

  if(numAristas == _V-1)      return minCoste;
  else                        return -1;
}*/
