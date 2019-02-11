/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Calculate the maximum number of overlaps of the given intervals.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int numActividades, aux, necesarios, max; cin >> numActividades;

  while(numActividades)
  {
    vector<int> inicios, finales; necesarios = 0; max = 0;

    for(int i = 0; i < numActividades; i++)
    {cin >> aux; inicios.push_back(aux);
     cin >> aux; finales.push_back(aux);}

    // If equal end time, we took first the lower initial time interval.
    // This is why we order twice
    sort(inicios.begin(), inicios.end());
    sort(finales.begin(), finales.end());

    int apunta_inicios = 0, apunta_finales = 0;

    while(apunta_inicios < numActividades)
    {
      if(inicios[apunta_inicios] < finales[apunta_finales])
      {
        necesarios++; if(necesarios>max) max = necesarios;
        apunta_inicios++;
      }
      else
      {
        necesarios--;
        apunta_finales++;
      }
    }

    cout << max-1 << '\n';
    cin >> numActividades;
  }

  return 0;
}
