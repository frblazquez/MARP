/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Design a method to check wether a tree is 
*              balanced or not.
*/

#include <iostream>
using namespace std;

bool equilibradoArbolLeido(int &altura);

int main()
{
  int altura, numCases; cin >> numCases;

  while(numCases--)
  {
      if(equilibradoArbolLeido(altura))
        cout << "SI\n";
      else
        cout << "NO\n";
  }

  return 0;
}

bool equilibradoArbolLeido(int &altura)
{
  char elem; cin >> elem;

  if(elem == '.') {altura = 0; return true; }
  else
  {
    int alturaIzq, alturaDcha;
    bool equilIzq, equilDcha;

    equilIzq  = equilibradoArbolLeido(alturaIzq);
    equilDcha = equilibradoArbolLeido(alturaDcha);
    altura    = max(alturaDcha, alturaIzq) + 1;

    return equilDcha && equilIzq && abs(alturaIzq - alturaDcha) <= 1;
  }
}
