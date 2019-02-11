/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Minimize the number of connections needed.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int numEdificios, ini, fin;
  cin >> numEdificios;

  while(numEdificios)
  {
    vector<pair<int,int>> edificios;

    for(int i = 0; i < numEdificios; i++)
    {cin >> ini >> fin; edificios.push_back({ini, fin});}

    sort(edificios.begin(), edificios.end());

    int i = 0, numTunels = 0; ini = -1; fin = -1;

    while(i<edificios.size())
    {
      // If the next building is out our interval, tunel necessary, new interval.
      if(edificios[i].first >= fin)
      {
        numTunels++;

        ini = edificios[i].first;
        fin = edificios[i].second;
      }
      // If the intersection of the new building and our interval is not empty,
      // we restrict our interval to the intersection.
      else
      {
        ini = max(ini, edificios[i].first);
        fin = min(fin, edificios[i].second);
      }

      i++;
    }

    cout << numTunels << '\n';
    cin >> numEdificios;
  }

  return 0;
}
