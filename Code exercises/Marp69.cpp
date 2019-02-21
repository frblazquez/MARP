/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*/

const int MAX_WORKS = 20;

int numWorks;                     // Número de trabajos a repartir y número de funcionarios
int bestTime;                     // Mejor solución hasta el momento
int board[MAX_WORKS][MAX_WORKS];  // board[i][j] es lo que tarda el funcionario i en el trabajo j
int minim[MAX_WORKS];             // mínimo tiempo que tarda el funcionario i
int maxim[MAX_WORKS];             // máximo tiempo que tarda el funcionario i
//bool taken[MAX_WORKS];            // indica si un trabajo ha sido ya elegido o no

struct tSolucion
{
  int optimista;
  int current;
  int level;
  bool taken[MAX_WORKS];

  bool operator<(tSolucion const& t2) const
  {
    return optimista < t2.optimista;
  }
};

#include <iostream>
#include "PriorityQueue.h"
using namespace std;

void minTime(PriorityQueue<tSolucion> &cola)
{
  tSolucion actual, siguiente;

  while(!cola.empty() && cola.top().optimista < bestTime)
  {
    actual    = cola.top(); cola.pop();

    for(int i = 0; i < numWorks; i++)
      siguiente.taken[i] = actual.taken[i];

    for(int j = 0; j < numWorks; j++)
    {
      if(!actual.taken[j])
      {
        if(actual.level == numWorks-1)
        {
          if(actual.current + board[actual.level][j] < bestTime)
            bestTime = actual.current + board[actual.level][j];
        }
        else
        {
          siguiente.taken[j] = true;

          siguiente.level     = actual.level+1;
          siguiente.current   = actual.current + board[actual.level][j];
          siguiente.optimista = siguiente.current + minim[siguiente.level];

          if(siguiente.optimista < bestTime)
            cola.push(siguiente);

          siguiente.taken[j] = false;
        }
      }
    }
  }
}

int main()
{
  cin >> numWorks; int mini, maxi; tSolucion first;

  while(numWorks)
  {
    for(int i = 0; i < numWorks; i++)
    for(int j = 0; j < numWorks; j++)
      cin >> board[i][j];

    // Calculamos los mínimos de cada funcionario (y máximos)
    for(int i = 0; i < numWorks; i++)
    {
      mini = board[i][0];
      maxi = board[i][0];

      for(int j = 1; j < numWorks; j++)
      {
        if(board[i][j] < mini)  mini = board[i][j];
        if(board[i][j] > maxi)  maxi = board[i][j];
      }

      minim[i] = mini;
      maxim[i] = maxi;
    }

    // Calculamos ahora el mínimo tiempo de completación (y máximos)
    for(int i = numWorks-2; i >= 0; i--)
    {
      minim[i] += minim[i+1];
      maxim[i] += maxim[i+1];
    }

    /*
    for(int i = 0; i < numWorks; i++)
      cout << minim[i] << " ";
      cout << endl;

    for(int i = 0; i < numWorks; i++)
      cout << maxim[i] << " ";
      cout << endl;
    */

    // Preparamos la llamada al método
    for(int i = 0; i < numWorks; i++)
      first.taken[i] = false;

    first.level   = 0;
    first.current = 0;
    first.optimista = minim[0];

    bestTime = maxim[0]; // Más grande (o igual) que cualquier posible solución

    PriorityQueue<tSolucion> cola;
    cola.push(first);

    minTime(cola);  // Calcula el mínimo tiempo para el tablero

    cout << bestTime << endl;
    cin >> numWorks;
  }

  return 0;
}
