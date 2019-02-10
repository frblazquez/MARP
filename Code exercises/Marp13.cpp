/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Find the kth element in a BST.
*/

/*
*   This problem is designed to modify a BST data structure adding a
*   new attribute to their nodes in order to know the number of
*   descending nodes. Then, with a simple modification of the search
*   method we can get the solution.
*
*   However, our solution is much simpler, but much less educational.
*   We put all the data in a vector and then we sort it.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main()
{
  int numElems,aux; cin >> numElems;
  int numQueries, querie;

  while(numElems)
  {
    vector<int> elems;              // To store the elements
    unordered_set<int> elems2;      // To avoid repetitions

    for(int i = 0; i<numElems; i++)
    {
      cin >> aux;

      if(elems2.count(aux) == 0)
      {
        elems.push_back(aux);
        elems2.insert(aux);
      }
    }

    sort(elems.begin(),elems.end());

    cin >> numQueries;

    for(int i = 0; i < numQueries; i++)
    {
      cin >> querie;

      if(querie > elems.size()) cout << "??\n";
      else                      cout << elems[querie-1] << '\n';
    }

    cout << "----\n";
    cin >> numElems;
  }

  return 0;
}
