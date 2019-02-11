/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Maximize the sum of positives differences of the pairs.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int numPartidos, aux, maxGan; cin >> numPartidos;

  while(numPartidos)
  {
    vector<int> puntos_rivales, puntos_locales; maxGan = 0;

    for(int i = 0; i < numPartidos; i++)
    {cin >> aux; puntos_rivales.push_back(aux);}

    for(int i = 0; i < numPartidos; i++)
    {cin >> aux; puntos_locales.push_back(aux);}

    sort(puntos_locales.begin(), puntos_locales.end());
    sort(puntos_rivales.begin(), puntos_rivales.end());

    for(int i = 0; i < numPartidos; i++)
    {
      if(puntos_locales[numPartidos - i - 1] > puntos_rivales[i])
        maxGan += puntos_locales[numPartidos - i - 1] - puntos_rivales[i];
    }

    cout << maxGan << '\n';
    cin >> numPartidos;
  }

  return 0;
}
