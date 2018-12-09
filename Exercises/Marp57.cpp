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
  int iniInter, finInter, numTrabajos, ini, fin;
  cin >> iniInter >> finInter >> numTrabajos;

  while(iniInter || finInter || numTrabajos)
  {
    vector<pair<int,int>> trabajos;

    for(int i = 0; i < numTrabajos; i++)
    {
      cin >> ini >> fin;

      ini = max(ini, iniInter);
      fin = min(fin, finInter);

      if(fin>iniInter && ini<finInter) trabajos.push_back({ini, fin});
    }

    sort(trabajos.begin(), trabajos.end());

    int cubiertoIniTotal, cubiertoIni, cubiertoFinTotal, cubiertoFin, i, necesarios;
    bool imposible = false;

    cubiertoIniTotal = iniInter;  cubiertoIni = iniInter-1;
    cubiertoFinTotal = iniInter;  cubiertoFin = iniInter;
    i = 0; necesarios = 0;

    while(cubiertoFinTotal<finInter && i<trabajos.size())
    {
      if(trabajos[i].first > cubiertoFin)
        imposible = true;
      else if(trabajos[i].second>cubiertoFin && trabajos[i].first>cubiertoIni)
      {
        necesarios++;

        cubiertoIni = cubiertoFin;
        cubiertoFin = trabajos[i].second;
        cubiertoFinTotal = trabajos[i].second;
      }
      else
      {
        cubiertoFin = trabajos[i].second;
        cubiertoFinTotal = trabajos[i].second;
      }

      i++;
    }

    if(cubiertoFinTotal<finInter || imposible) cout << "Imposible\n";
    else                                       cout << necesarios << '\n';

    cin >> iniInter >> finInter >> numTrabajos;
  }

  return 0;
}
