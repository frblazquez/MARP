/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Minimum number of moves in Stairs-Snakes game to 
*              win with a determinated board state.
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
    numCells = boardSize*boardSize;                         //Total number of cells
    for(int i = 0; i < numCells; i++) board[i] = numCells;  //Board initialization
    unordered_map<int, int> snakes,stairs;                  //We keep a map instead a graph 
                                                            //for snakes and stairs
                                                            
    /*
      Each cell of board[] is an integer that represents the minimum number
      of moves needed for reachin that cell from the initial position.
        
      We are going to simulate a game, exploring all posible states following
      number of moves order.
    */

    //Reads the snakes
    for(int i = 0; i < numSnakes; i++)
    {cin >> init >> end; snakes[init-1] = end-1;}

    //Reads the stairs
    for(int i = 0; i < numStairs; i++)
    {cin >> init >> end; stairs[init-1] = end-1;}

    // --------------------------------------------------------------------- //
    vector<int> nexts, actual; actual.push_back(0); board[0] = 0;
    int numMoves = 0, position, maxTriviales;
    bool ended = false;

    while(!ended)
    {
      numMoves++;

      while(!ended && !actual.empty())
      {
      position = actual.back(); actual.pop_back();
      maxTriviales = -1;

      for(int j = 1; j <= maxSteps && !ended; j++)
      {
        if(position+j == numCells-1)           // We reach the last cell
          ended = true;
        else if(board[position+j] > numMoves)  // Non reached yet cell
        {
          board[position+j] = numMoves;

        if(snakes.count(position+j) != 0)      // Snake case!
        {
          board[snakes[position+j]] = numMoves;
          nexts.push_back(snakes[position+j]);
        }
        else if(stairs.count(position+j) != 0) // Stair case!
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

    if(!ended) {actual = nexts; nexts.clear();}
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
    // move is a wrong strategy !! 

    cout << numMoves;
    cin >> boardSize >> maxSteps >> numSnakes >> numStairs;
  }

  return 0;
}
*/
