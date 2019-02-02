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
  int baseRow[500];     //Actual row
  int boardSize, actualNum, last, lastlast, maxim, pos;
  cin >> boardSize;

  while(cin)
  {
    for(int i = 0; i < boardSize; i++)
      cin >> baseRow[i];

    for(int i = 1; i < boardSize; i++)
    {
      cin >> actualNum;
      lastlast = actualNum + std::max(baseRow[0], baseRow[1]);

      cin >> actualNum;
      last = actualNum + std::max(baseRow[0],max(baseRow[1],baseRow[2]));

      for(int j = 2; j < boardSize-1; j++)
      {
        baseRow[j-2] = lastlast;
        lastlast = last;

        cin >> actualNum;
        last = actualNum + max(baseRow[j-1], max(baseRow[j], baseRow[j+1]));
      }

      cin >> actualNum;
      actualNum += max(baseRow[boardSize-1], baseRow[boardSize-2]);

      baseRow[boardSize-3] = lastlast;
      baseRow[boardSize-2] = last;
      baseRow[boardSize-1] = actualNum;
    }

    maxim = 0; pos = 0;

    for(int i = 0; i < boardSize; i++)
    {
      if(baseRow[i] > maxim) {maxim = baseRow[i]; pos = i+1;}
    }

    cout << maxim << " " << pos << endl;

    cin >> boardSize;
  }

  return 0;
}
