/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Minimize the sum of differences of the pairs.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int numPeople, aux, diff; cin >> numPeople;

  while(numPeople)
  {
    vector<int> people, skis; diff = 0;

    for(int i = 0; i < numPeople; i++)
    {cin >> aux; people.push_back(aux);}

    for(int i = 0; i < numPeople; i++)
    {cin >> aux; skis.push_back(aux);}

    sort(people.begin(), people.end());
    sort(skis.begin(), skis.end());

    for(int i = 0; i < numPeople; i++)
      diff += abs(people[i] - skis[i]);

    cout << diff << '\n';
    cin >> numPeople;
  }

  return 0;
}
