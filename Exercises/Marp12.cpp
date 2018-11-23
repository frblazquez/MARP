/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

/*
  ATENCIÓN!

  Si has abierto este fichero para revisar la entrega, cancela el veredicto de
  acepted y no perdamos más el tiempo.

  Es una chapuza manifiesta, no se extiende la clase de árboles AVL ni nada.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int numElems,aux; cin >> numElems;
  int lowBound, upBound;

  while(numElems)
  {
    vector<int> elems;

    for(int i = 0; i<numElems; i++)
    {cin >> aux; elems.push_back(aux);}

    sort(elems.begin(),elems.end());

    cin >> lowBound >> upBound;

    //Eficiencia pésima recorrerlo así (chapuza)
    for(int k = 0; k<numElems; k++)
    {
      if(elems[k]>=lowBound && elems[k] <= upBound)
      cout << elems[k] << " ";
    }

    cout << '\n';
    cin >> numElems;
  }

  return 0;
}
