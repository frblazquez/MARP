/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Assign works minimising overlap in a critical interval.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int iniInter, finInter, numTrabajos, ini, fin;
  cin >> iniInter >> finInter >> numTrabajos;

  while(iniInter || finInter || numTrabajos)
  {
    vector<pair<int,int>> trabajos;

    for(int i = 0; i < numTrabajos; i++)
    {
      cin >> ini >> fin;

      if(ini<finInter && fin>iniInter) trabajos.push_back({ini, fin});
    }

    sort(trabajos.begin(), trabajos.end());

    int partialIni = iniInter, partialEnd = iniInter, i = 0, necesarios = 1, workIni, workEnd;
    bool imposible = false;

    while(i<trabajos.size() && partialEnd<finInter && !imposible)
    {
      workIni = trabajos[i].first;
      workEnd = trabajos[i].second;

      if(workIni>partialEnd)  // It's not possible to cover all the interval
        imposible = true;
      else if(workIni<=partialIni)
      {
        if(workEnd > partialEnd)
        {
          partialEnd = workEnd;
        }
      }
      else if(workEnd > partialEnd)
      {
        necesarios++;

        partialIni = partialEnd;
        partialEnd = workEnd;
      }

      i++;
    }

    if(imposible || partialEnd<finInter)  cout << "Imposible\n";
    else                                  cout << necesarios << endl;
    cin >> iniInter >> finInter >> numTrabajos;
  }

  return 0;
}
