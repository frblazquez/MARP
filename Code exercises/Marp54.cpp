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
      if(edificios[i].first >= fin)
      {
        numTunels++;

        ini = edificios[i].first;
        fin = edificios[i].second;
      }
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
