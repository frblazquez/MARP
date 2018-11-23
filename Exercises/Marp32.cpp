/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
  int boardSize, maxSteps, numSnakes, numStairs, numCells, init, end;
  cin >> boardSize >> maxSteps >> numSnakes >> numStairs;

  int board[10000];

  while(boardSize != 0)
  {
    numCells = boardSize*boardSize;                         //Número total de celdas
    for(int i = 0; i < numCells; i++) board[i] = numCells;  //Inicialización del tablero
    unordered_map<int, int> snakes,stairs;                  //Declaración de serpientes y escaleras

    //Leemos las serpientes
    for(int i = 0; i < numSnakes; i++)
    {cin >> init >> end; snakes[init-1] = end-1;}

    //Leemos las escaleras
    for(int i = 0; i < numStairs; i++)
    {cin >> init >> end; stairs[init-1] = end-1;}

    // --------------------------------------------------------------------- //
    vector<int> nexts, actual; actual.push_back(0); board[0] = 0;
    int numMoves = 0, position, maxTriviales;
    bool terminado = false;

    while(!terminado)
    {
      numMoves++;

      while(!terminado && !actual.empty())
      {
      position = actual.back(); actual.pop_back();
      maxTriviales = -1;

      for(int j = 1; j <= maxSteps && !terminado; j++)
      {
        if(position+j == numCells-1)           // Si es la celda final
          terminado = true;
        else if(board[position+j] > numMoves)  // Si es una celda no pasada ya
        {
          board[position+j] = numMoves;

        if(snakes.count(position+j) != 0)     // Si es comienzo de una serpiente
        {
          board[snakes[position+j]] = numMoves;
          nexts.push_back(snakes[position+j]);
        }
        else if(stairs.count(position+j) != 0)// Si es comienzo de una escalera
        {
          board[stairs[position+j]] = numMoves;
          nexts.push_back(stairs[position+j]);
        }
        else
          maxTriviales = position+j;
        }
      }

      if(maxTriviales != -1) nexts.push_back(maxTriviales);
    }

    if(!terminado) {actual = nexts; nexts.clear();}
    }

    cout << numMoves << endl;
    cin >> boardSize >> maxSteps >> numSnakes >> numStairs;
  }

  return 0;
}

/*
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{
  int boardSize, maxSteps, numSnakes, numStairs, init, end;
  cin >> boardSize >> maxSteps >> numSnakes >> numStairs;

  while(boardSize != 0)
  {
    vector<int> stairsInit, snakesInit;
    unordered_map<int,int> snakeInit_end, stairInit_end;

    //------------------------------ DATA READING ----------------------------//
    for(int i = 0; i<numSnakes; i++)
    {
      cin >> init >> end;

      snakesInit.push_back(init);
      snakeInit_end[init] = end;
    }

    for(int i = 0; i<numStairs; i++)
    {
      cin >> init >> end;

      stairsInit.push_back(init);
      stairInit_end[init] = end;
    }

    sort(stairsInit.begin(), stairsInit.end());
    sort(snakesInit.begin(), snakesInit.end());
    //------------------------------------------------------------------------//

    int initPosition = 1, numMoves = 0;

    // This approach won't work, going as further as possible in a single
    // move may be a wrong strategy.

    cout << numMoves;
    cin >> boardSize >> maxSteps >> numSnakes >> numStairs;
  }

  return 0;
}
*/
