#include "splay_tree.h"
#include <iostream>
using namespace std;

int main()
{
  splay_tree<int> arbol;

  int* puntero1; int* puntero2;
  int numero1 = 5, numero2 = 10;

  puntero1 = &numero1;
  puntero2 = &numero2;

  if(puntero1==puntero2)
    cout << "Punteros iguales\n";
  else
    cout << "Punteros distintos\n";

  puntero2 = &numero1;

  if(puntero1==puntero2)
    cout << "Punteros iguales\n";
  else
    cout << "Punteros distintos\n";

  return 0;
}
