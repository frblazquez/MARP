#include "splay_tree.h"
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
  splay_tree<int> arbol;

  /* FOR MANUAL TESTING!
  int  opcode = 2, aux;

  while(opcode != -1)
  {
    cin >> aux;

    try
    {
      if(opcode == 0)      arbol.print();
      else if(opcode == 1) arbol.find(aux);
      else if(opcode == 2) arbol.insert(aux);
      else if(opcode == 3) arbol.erase(aux);
      else if(opcode == 4) {if(arbol.empty())  cout << "VACIO\n";
                            else               cout << "NO VACIO\n";}
    }
    catch (const char* msg)
    {
      cerr << msg << endl;
    }
    catch (exception &e)
    {
      cout << e.what() << endl;
    }

    cin >> opcode;
  }*/

  /* FOR AUTOMATIC TEST
  srand(time(NULL));

  int upLimit = 1000, nextValue;

  try
  {
    for(int i = 0; i < 1000; i++)
    {
      nextValue = rand()%upLimit;
      arbol.insert(nextValue);
    }

    for(int i = 0; i < 1000; i++)
    {
      nextValue = rand()%upLimit;
      arbol.find(nextValue);
    }

    for(int i = 0; i < 4000; i++)
    {
      nextValue = rand()%upLimit;
      arbol.erase(nextValue);
    }
  }
  catch (const char* msg)
  {
    cerr << msg << endl;
  }
  catch (exception &e)
  {
    cout << e.what() << endl;
  }

  arbol.print(); */

  return 0;
}
