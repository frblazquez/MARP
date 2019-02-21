/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*/

const int MAX_SONGS = 25;

int numSongs;                     // Número de trabajos a repartir y número de funcionarios
int bestSol;                      // Mejor solución hasta el momento
int space;                        // Espacio libre en cada cara
int songs[MAX_SONGS][2];          // Canción -> [duración, puntuación]
int allSpace[MAX_SONGS];          // Máxima puntuación si caben todas las restantes

struct tSolucion
{
  int free1;
  int free2;
  int level;
  int points;

  // EL OPERADOR < EN REALIDAD ESTÁ DEFINIDO COMO > PARA INVERTIR EL ORDEN EN LA COLA
  bool operator<(tSolucion const& t2) const
  {
    // PARA ORDENAR POR DENSIDAD DE PUNTUACIÓN
    /*
    if(free1==space && free2==space)          return false; // No hemos grabado nada
    if(t2.free1==space && t2.free2==space)    return true;// El otro disco está vacío

    // Si no, el menor es el de menor densidad de puntuación
    return (points/(2*space -free1-free2)) > (t2.points/(2*space -t2.free1-t2.free2));
    */

    // PARA ORDENAR POR PUNTUACIÓN
    return points>t2.points;
  }
};

#include <iostream>
#include "PriorityQueue.h"
using namespace std;

void maxPoints(PriorityQueue<tSolucion> &cola)
{
  tSolucion actual, siguiente;

  while(!cola.empty())
  {
    actual = cola.top(); cola.pop();

    if(actual.level+1 == numSongs) // Último nivel
    {
      /* Ya se actualiza todo al introducir valores en la cola! */;
    }
    else
    {
      siguiente = actual;
      siguiente.level++;

      cola.push(siguiente);     // Optamos por no meter esta canción a la cinta

      if(actual.free1 >= songs[actual.level][0])
      {
        siguiente.free1  -= songs[actual.level][0];
        siguiente.points += songs[actual.level][1];

        if(siguiente.free1 >= siguiente.free2)
        {
          if(siguiente.points>bestSol)
            bestSol = siguiente.points;

          if(siguiente.points + allSpace[siguiente.level] > bestSol)
            cola.push(siguiente);
        }

        siguiente.free1  += songs[actual.level][0];
        siguiente.points -= songs[actual.level][1];
      }
      if(actual.free2 >= songs[actual.level][0])
      {
        siguiente.free2  -= songs[actual.level][0];
        siguiente.points += songs[actual.level][1];

        if(siguiente.points>bestSol) bestSol = siguiente.points;

        if(siguiente.points + allSpace[siguiente.level] > bestSol)
          cola.push(siguiente);
      }
    }
  }

}

int main()
{
  cin >> numSongs;

  while(numSongs)
  {
    cin >> space;

    // Leemos las canciones, duración y puntuación
    for(int i = 0; i < numSongs; i++)
    for(int j = 0; j < 2;        j++)
      cin >> songs[i][j];

    // Preparamos el vector de óptimos
    allSpace[numSongs-1] = songs[numSongs-1][1];

    for(int i = numSongs-2; i >= 0; i--)
      allSpace[i] = allSpace[i+1] + songs[i][1];

    tSolucion first;

    first.free1 = space;
    first.free2 = space;
    first.level = 0;
    first.points = 0;

    bestSol = 0;

    PriorityQueue<tSolucion> cola;
    cola.push(first);

    maxPoints(cola);

    cout << bestSol << endl;
    cin >> numSongs;
  }

  return 0;
}
