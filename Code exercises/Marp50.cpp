/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Minimize the number of sections needed to cover
               every hole read.
*/

#include <iostream>
using namespace std;

int main()
{
  int numHoles, length, numParches, maxTapados, next;
  cin >> numHoles >> length;

  while(cin)
  {
    numParches = 0; maxTapados = -1;

    for(int i = 0; i < numHoles; i++)
    {
      cin >> next;

      if(next > maxTapados)
      {
        numParches++;
        maxTapados = next+length;
      }
    }

    cout << numParches << '\n';
    cin >> numHoles >> length;
  }

  return 0;
}
