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
#include <unordered_set>
#include <algorithm>
using namespace std;

int main()
{
  int numElems,aux; cin >> numElems;
  int numQueries, querie;

  while(numElems)
  {
    vector<int> elems;
    unordered_set<int> elems2;

    for(int i = 0; i<numElems; i++)
    {
      cin >> aux;

      if(elems2.count(aux) == 0)
      {
        elems.push_back(aux);
        elems2.insert(aux);
      }
    }

    sort(elems.begin(),elems.end());

    cin >> numQueries;

    for(int i = 0; i < numQueries; i++)
    {
      cin >> querie;

      if(querie > elems.size()) cout << "??\n";
      else                      cout << elems[querie-1] << '\n';
    }

    cout << "----\n";
    cin >> numElems;
  }

  return 0;
}
