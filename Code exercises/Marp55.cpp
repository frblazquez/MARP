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
  int numFilms, horaIni, minIni, duracion, quedaLibre, numPosibles, nextFilm; char c;
  cin >> numFilms;

  while(numFilms)
  {
    vector<pair<int,int>> films;
    numPosibles = 0; quedaLibre = -11; nextFilm = 0;

    for(int i = 0; i < numFilms; i++)
    {
      cin >> horaIni >> c >> minIni >> duracion;
      films.push_back({horaIni*60 + minIni + duracion, horaIni*60 + minIni});
    }

    sort(films.begin(), films.end());

    while(nextFilm < numFilms)
    {
      if(films[nextFilm].second >= quedaLibre+10)
      {
        numPosibles++;
        quedaLibre = films[nextFilm].first;
      }

      nextFilm++;
    }

    cout << numPosibles << '\n';
    cin >> numFilms;
  }

  return 0;
}
