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
  int numRods, rod, cost, goalRod;

  cin >> numRods >> goalRod;

  while(cin)
  {
    int possibilities[goalRod+1];         // To keep the number of ways for making the rod
    int minCost[goalRod+1];               // To keep the minimun cost for making the rod
    int minRods[goalRod+1];               // To keep the minimum number of rods necessaries

    for(int i = 0; i <= goalRod; i++)
      possibilities[i] = 0;

    possibilities[0] = 1;
    minCost[0] = 0;
    minRods[0] = 0;

    for(int i = 0; i<numRods; i++)
    {
      cin >> rod >> cost;

      for(int j = goalRod; j >= rod; j--)
      {
        if(possibilities[j - rod] > 0)
        {
          if(possibilities[j] == 0 || minCost[j] > minCost[j-rod] + cost)
            minCost[j] = minCost[j-rod] + cost;
          if(possibilities[j] == 0 || minRods[j] > minRods[j-rod] + 1)
            minRods[j] = minRods[j-rod] + 1;

          possibilities[j] += possibilities[j-rod];
        }
      }
    }

    if(possibilities[goalRod] == 0) cout << "NO\n";
    else cout << "SI " << possibilities[goalRod] << " " << minRods[goalRod] << " " << minCost[goalRod] << '\n';

    cin >> numRods >> goalRod;
  }

  return 0;
}
