package ucm.fdi.marp;

import ucm.fdi.marp.SplayTree;
import java.util.Random;
import java.util.Scanner;

public class SplayTreeTest
{
	public static void main(String args[])
	{

		/* 
		*       FOR AUTOMATIC TESTING
		*
		SplayTree<Integer> arbol = new SplayTree<Integer>();

		Random rand = new Random();

		int upLimit = 1000, nextValue;

		try
		{
		  for(int i = 0; i < 1000; i++)
		  {
		    nextValue = rand.nextInt(upLimit);
		    arbol.insert(nextValue);
		  }

		  for(int i = 0; i < 1000; i++)
		  {
		    nextValue = rand.nextInt(upLimit);
		    arbol.find(nextValue);
		  }

		  for(int i = 0; i < 4000; i++)
		  {
		    nextValue = rand.nextInt(upLimit);
		    arbol.erase(nextValue);
		  }
		}
		catch (Exception e)
		{
		  System.out.println(e.getMessage());
		}

		arbol.print(); */

		/*
		*   	FOR MANUAL TESTING
        *
	    int  opcode = 2, aux;
		Scanner in = new Scanner(System.in);

		while(opcode != -1)
		{
			aux = in.nextInt();

			try
			{
				if(opcode == 0)      arbol.print();
				else if(opcode == 1) arbol.find(aux);
				else if(opcode == 2) arbol.insert(aux);
				else if(opcode == 3) arbol.erase(aux);
				else if(opcode == 4) {if(arbol.empty())  System.out.println("VACIO");
									  else               System.out.println("NO VACIO");}
			}
			catch (Exception e)
			{
				System.out.println(e.getMessage());
			}

			opcode = in.nextInt();
		}*/
	}
}
