#include "splay_tree.h"
#include <iostream>
using namespace std;

int main()
{
  splay_tree<int> arbol;

  if(arbol.empty()) cout << "Vacío\n";
  else              cout << "No vacío\n";

  return 0;
}
