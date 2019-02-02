/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int availableTime, numChests, depth, coins;

  cin >> availableTime;

  while(cin)
  {
    cin >> numChests;

    vector<pair<int,int>> chests; chests.push_back({0,0});

    for(int i = 0; i < numChests; i++)
    {
      cin >> depth >> coins;
      chests.push_back({depth,coins});
    }

    int profit[numChests+1][availableTime+1];

    for(int i = 0; i <= numChests; i++)     profit[i][0] = 0;
    for(int i = 0; i <= availableTime; i++) profit[0][i] = 0;

    for(int i = 1; i <= numChests; i++)
    for(int j = 1; j <= availableTime; j++)
    {
      if(j < 3*chests[i].first) profit[i][j] = profit[i-1][j];
      else  profit[i][j] = max(profit[i-1][j], profit[i-1][j-3*chests[i].first] + chests[i].second);
    }

    vector<pair<int,int>> solution;
    int i = numChests, j = availableTime;

    while(i > 0)
    {
      if(profit[i][j] != profit[i-1][j])
        {solution.push_back(chests[i]); j-= 3*chests[i].first;}

      i--;
    }

    cout << profit[numChests][availableTime] << '\n';
    cout << solution.size() << '\n';

    for(int i = solution.size()-1; i>= 0; i--)
      cout << solution[i].first << " " << solution[i].second << '\n';

    cout << "----\n";

    cin >> availableTime;
  }

  return 0;
}

/* This doesn't work, overrides the chests taken

int main()
{
  int availableTime, numChests, depth, coins, index;

  cin >> availableTime;

  while(cin)
  {
    cin >> numChests;

    int maxProfit[availableTime + 1];         // Maximum profit for each time available
    pair<int,int> chest[availableTime + 1];   // Wich chest take for each time available

    for(int i = 0; i <= availableTime; i++) maxProfit[i] = 0;

    for(int i = 0; i < numChests; i++)
    {
      cin >> depth >> coins;

      for(int j = availableTime; j>= 3*depth; j--)
      {
        if(maxProfit[j] < maxProfit[j-3*depth] + coins)
        {
          chest[j] = {depth, coins};
          maxProfit[j] = maxProfit[j-3*depth] + coins;
        }
      }

      /*for(int j = 1; j<= availableTime; j++)
        cout << maxProfit[j] << " ";
        cout << endl;

      for(int j = 1; j<= availableTime; j++)
        cout << chest[j].first << '-' << chest[j].second << " ";
        cout << endl;/
    }

    cout << maxProfit[availableTime] << endl;

    index = availableTime;
    vector<pair<int,int>> solution;

    while(index > 0 && maxProfit[index] != 0)
    {
      solution.push_back(chest[index]);
      index -= 3*chest[index].first;
    }

    cout << solution.size() << '\n';

    for(int k = solution.size()-1; k >= 0; k--)
      cout << solution[k].first << " " << solution[k].second << '\n';

    cout << "----\n";

    cin >> availableTime;
  }

  return 0;
}*/
