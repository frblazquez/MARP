package ucm.fdi.marp;

import ucm.fdi.marp.SplayTree;

public class SplayTreeTest
{
	public static void main(String args[])
	{
    SplayTree<Integer> arbol = new SplayTree<Integer>();

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

	}
}

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
