/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
using namespace std;

int main()
{
  int boardSize, maxSteps, numSnakes, numStairs, init, end;
  cin >> boardSize >> maxSteps >> numSnakes >> numStairs;

  while(boardSize != 0)
  {
    

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
