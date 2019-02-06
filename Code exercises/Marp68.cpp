/*
*   Copyright © 2019
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

const int MINTS_DAY = 60*24;

int main()
{
  int filmIni, filmEnd, duration;
  int numFilms; char c;
  cin >> numFilms;

  while(numFilms)
  {
    vector<pair<int,int>> filmIni_duration;

    for(int i = 0; i < numFilms; i++)
    {
      cin >> filmIni >> c >> filmEnd >> duration;

      filmIni_duration.push_back({60*filmIni + filmEnd, duration});
    }

    sort(filmIni_duration.begin(), filmIni_duration.end());

    // Máximo tiempo que puedo estar viendo películas si estoy ocupado hasta el minuto j.
    // Si no hay películas empezamos en 0.
    int maxTime[MINTS_DAY + 11]; for(int i = 0; i < MINTS_DAY + 11; i++) maxTime[i] = 0;

    for(int i = numFilms-1; i >= 0; i--)
    {
      filmIni  = filmIni_duration[i].first;
      duration = filmIni_duration[i].second;
      filmEnd  = filmIni + duration;

      for(int j = 0; j <= filmIni; j++)
      {
        if(duration + maxTime[filmEnd + 10] > maxTime[j])
          maxTime[j] = duration + maxTime[filmEnd + 10];
      }

      /*for(int i = 0; i < 30; i++)
        cout << maxTime[i] << " ";
        cout << '\n';*/
    }

    cout << maxTime[0] << endl;
    cin >> numFilms;
  }

  return 0;
}
