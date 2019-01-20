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
  int numCases, numPilas, voltaje, aux; cin >> numCases;

  while(numCases--)
  {
    vector<int> pilas;

    cin >> numPilas >> voltaje;

    for(int i = 0; i < numPilas; i++)
    {cin >> aux; pilas.push_back(aux);}

    sort(pilas.begin(), pilas.end());

    int ini = 0, fin = pilas.size()-1, numPosibles = 0;

    while(ini < fin)
    {
      if(pilas[ini] + pilas[fin] >= voltaje)
      {
        numPosibles++;
        fin--;
      }

      ini++;
    }

    cout << numPosibles << '\n';
  }

  return 0;
}
