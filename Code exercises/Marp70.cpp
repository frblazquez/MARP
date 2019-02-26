/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*/

#include <iostream>
#include <algorithm>
#include "Data structures/PriorityQueue.h"
using namespace std;

// TO STORE SONGS (DURATION-PUNTUATION)
struct song
{
  int duration;   // Song duration
  int points;     // Song points

  // To order decreasingly in desnity of points order
  bool operator<(song const& song2) const
  {
    double d1 = points, d2 = song2.points;

    return d1/duration > d2/song2.duration;
  }
};

// TO STORE PARTIAL SOLUTIONS WITH A PRIORITY (OPTIMIST SOLUTION)
struct solution
{
  int pesimist;   // Just one solution possible from this node
  int optimist;   // Upper bound to the solution
  int points;     // Points of the partial solution
  int level;      // Deepness of the exploration
  int free1;      // Free space in the upperside
  int free2;      // Free space in the underside

  solution() :
    pesimist(0),
    optimist(0),
    points(0),
    level(0),
    free1(0),
    free2(0) {};

  solution(int pes, int opt, int pts, int lev, int f1, int f2) :
    pesimist(pes),
    optimist(opt),
    points(pts),
    level(lev),
    free1(f1),
    free2(f2) {};

  bool operator<(solution const& sol2) const
  {
    if(optimist > sol2.optimist)        return true;
    else if(optimist == sol2.optimist)  return points > sol2.points;
    else                                return false;
  }
};

const int MAX_SONGS = 25;

int numSongs;             // Number of songs of the case
int bestSolution;         // Best solution at this moment of the exploration process
int space;                // Free space of the empty disk at each face
song songs[MAX_SONGS];    // Songs for the current exploration
int minDurations[MAX_SONGS];

int optimist(int level, int free1, int free2);
int pesimist(int level, int free1, int free2);
void explore(PriorityQueue<solution> & queue);

int main()
{
  cin >> numSongs;

  while(numSongs)
  {
    cin >> space;

    // We read the songs
    for(int i = 0; i < numSongs; i++)
      cin >> songs[i].duration >> songs[i].points;

    // We order the songs (density of points decreasingly)
    sort(songs, songs+numSongs);

    minDurations[numSongs-1] = songs[numSongs-1].duration;

    for(int i = numSongs-2; i >= 0; i--)
      minDurations[i] = min(minDurations[i], minDurations[i+1]);

    // To  print the songs
    //for(int i = 0; i < numSongs; i++)
    //  cout << songs[i].points << " " << songs[i].duration << endl;

    PriorityQueue<solution> queue;
    solution first;

    first.free1    = space;
    first.free2    = space;
    first.level    = 0;
    first.points   = 0;
    first.optimist = optimist(0, space, space);
    first.pesimist = pesimist(0, space, space);

    bestSolution = first.pesimist;

    queue.push(first);

    explore(queue);

    cout << bestSolution << '\n';
    cin >>  numSongs;
  }

  return 0;
}

// Greedy algorithm to find the best possible solution if we can fragment the songs
int optimist(int level, int free1, int free2)
{
  int points = 0, freeSpace = free1 + free2;

  while(freeSpace)
  {
    if(freeSpace >= songs[level].duration)
      {points += songs[level].points; freeSpace -= songs[level].duration;}
    else
      {points += (songs[level].points*freeSpace)/songs[level].duration; freeSpace = 0;}
  }

  return points;
}

// Put songs in free1 if possible, else in free2 if possible, else next song
int pesimist(int level, int free1, int free2)
{
  int points = 0;

  while(level < numSongs && (free1 >= minDurations[level] || free2 >= minDurations[level]))
  {
    if(free1 >= songs[level].duration)
      {points += songs[level].points; free1 -= songs[level].duration;}
    else if(free2 >= songs[level].duration)
      {points += songs[level].points; free2 -= songs[level].duration;}

    level++;
  }

  return points;
}

void explore(PriorityQueue<solution> & queue)
{
  solution act; song levelSong; int opt,pes;

  while(!queue.empty() && queue.top().optimist > bestSolution)
  {
    act  = queue.top(); queue.pop();
    levelSong = songs[act.level];

    if(act.level == numSongs-1)
    {
      if(act.free1 >= levelSong.duration || act.free2 >= levelSong.duration)
        if(act.points + levelSong.points > bestSolution)
          bestSolution = max(bestSolution, act.points + levelSong.points);
    }
    else if(act.free1 >= minDurations[act.level] || act.free2 >= minDurations[act.level])
    {
      if(act.free1 >= levelSong.duration)
        queue.push({act.pesimist,
                    act.optimist,
                    act.points + levelSong.points,
                    act.level+1,
                    act.free1 - levelSong.duration,
                    act.free2});

      if(act.free2 >= levelSong.duration)
      {
        // Optimist bound is the same, Is pesimist bound stable too?
        if(act.free1 >= levelSong.duration)
          pes = act.points + levelSong.points + pesimist(act.level+1, act.free1, act.free2-levelSong.duration);
        else
          pes = act.pesimist;

        if(pes > bestSolution) bestSolution = pes;

        queue.push({pes,
                    act.optimist,
                    act.points + levelSong.points,
                    act.level+1,
                    act.free1,
                    act.free2 - levelSong.duration});
      }

      opt = act.points + optimist(act.level+1, act.free1, act.free2);

      if(opt > bestSolution)
      {
        pes = act.points + pesimist(act.level+1, act.free1, act.free2);

        if(pes > bestSolution)
          bestSolution = pes;

        queue.push({pes,
                    opt,
                    act.points,
                    act.level+1,
                    act.free1,
                    act.free2});
      }
    }
  }
}

/*
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
    /

    // PARA ORDENAR POR PUNTUACIÓN
    return points>t2.points;
  }
};

#include <iostream>
#include "Data structures/PriorityQueue.h"
using namespace std;

void maxPoints(PriorityQueue<tSolucion> &cola)
{
  tSolucion actual, siguiente;

  while(!cola.empty())
  {
    actual = cola.top(); cola.pop();

    if(actual.level+1 == numSongs) // Último nivel
    {
      // Ya se actualiza todo al introducir valores en la cola! ;
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
*/
