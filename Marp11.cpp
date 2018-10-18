/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
using namespace std;

// Returns true iff the arbol read is AVL
bool leeArbolAVL();
bool deBusquedaYEquilibrado(int &altura, int& maxim, int& minim);

int main()
{
  int numCases; cin >> numCases;

  while(numCases--)
  {
    if(leeArbolAVL())
      cout << "SI\n";
    else
      cout << "NO\n";
  }

  return 0;
}

bool leeArbolAVL()
{
  int aux, maxim, minim;

  return deBusquedaYEquilibrado(aux, maxim, minim);
}

bool deBusquedaYEquilibrado(int &altura, int &maxim, int &minim)
{
  int c; cin >> c;

  if(c == -1) {altura = 0; maxim = -1; minim = -1; return true;} //-1 means undefined!

  // Non trivial case!
  int maxDcha, minDcha, alturaDcha; bool hojaDcha = false;
  int maxIzq, minIzq, alturaIzq;    bool hojaIzq = false;

  bool avlIzq  = deBusquedaYEquilibrado(alturaIzq,  maxIzq,  minIzq);
  bool avlDcha = deBusquedaYEquilibrado(alturaDcha, maxDcha, minDcha);

  if(maxIzq  == -1) {maxIzq  = c; minIzq  = c; hojaIzq  = true;}
  if(maxDcha == -1) {maxDcha = c; minDcha = c; hojaDcha = true;}

  altura = max(alturaDcha, alturaIzq) + 1;
  maxim  = max(maxDcha, maxIzq);
  minim  = min(minDcha, minIzq);

  bool maxCondition = (hojaIzq  || maxIzq  < c);  //Pequeña chapuza para evitar hojas
  bool minCondition = (hojaDcha || minDcha > c);  //Así si es una hoja les permitimos saltarse el máximo

  return avlDcha && avlIzq && abs(alturaDcha - alturaIzq) <= 1 && maxCondition && minCondition;
}
