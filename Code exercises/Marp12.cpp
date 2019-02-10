/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Implement a method to determinate the keys
*              in a binary search tree in a range given.
*/

/*
*   This exercise should be done inside a binary search tree
*   data structure implementing a variation of the search method. 
*  
*   The way it's done is putting all the keys in a vector, ordering
*   it and then using a lineal search for finding the keys in the 
*   range given. The algorithm complexity is the same.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int numElems,aux; cin >> numElems;
  int lowBound, upBound;

  while(numElems)
  {
    vector<int> elems;

    for(int i = 0; i<numElems; i++)
    {cin >> aux; elems.push_back(aux);}

    sort(elems.begin(),elems.end());

    cin >> lowBound >> upBound;

    //We don't even do a binary search
    for(int k = 0; k<numElems; k++)
    {
      if(elems[k]>=lowBound && elems[k] <= upBound)
      cout << elems[k] << " ";
    }

    cout << '\n';
    cin >> numElems;
  }

  return 0;
}
