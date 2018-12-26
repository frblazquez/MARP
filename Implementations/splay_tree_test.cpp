#include "splay_tree.h"
using namespace std;

int main()
{
  splay_tree<int> arbol; int  opcode = 2, aux;

  while(opcode != -1)
  {
    cin >> aux;

    if(opcode == 0)      arbol.print();
    else if(opcode == 1) arbol.search(aux);
    else if(opcode == 2) arbol.insert(aux);

    cin >> opcode;
  }

  return 0;
}
