#include "splay_tree.h"
#include <iostream>
using namespace std;

int main()
{
  splay_tree<int> arbol;

  if(arbol.insert(0))
    cout << "Insertado\n";
  else
    cout << "No insertado\n";

  if(arbol.empty())
    cout << "La raiz es un puntero nullo\n";
  else
    cout << "La insercion se ha hecho bien\n";

  if(arbol.erase(0))
    cout << "Eliminado\n";
  else
    cout << "No eliminado\n";

  return 0;
}
