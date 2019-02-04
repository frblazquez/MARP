/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

/*
    This solution can easily be improved with just a few modifications:
      - Adjacent matrix is simetric because of the non-directed graph condition.
      - It's possible to stop the maximum search before (last part).
      - Floyd algorithm is not necessary if we can know that the graph is not conected.
*/

#include <iostream>
#include <unordered_map>
using namespace std;

const int INFINITY = 500; // Maximum number of people (vertex) = 500

int main()
{
  int numPeople, numRelations;
  string person1, person2;
  cin >> numPeople >> numRelations;

  while(cin)
  {
    // Board where we are keeping distance among people
    int distance[numPeople][numPeople];

    for(int i = 0; i < numPeople; i++)
    for(int j = 0; j < numPeople; j++)
      distance[i][j] = INFINITY;

    for(int i = 0; i < numPeople; i++)
      distance[i][i] = 0;


    // Now we read the people and transform them in numbers
    unordered_map<string, int> person_code;
    int numPeopleRead = 0, auxC_k;

    for(int i = 0; i < numRelations; i++)
    {
      cin >> person1 >> person2;

      if(person_code.count(person1) == 0) person_code[person1] = numPeopleRead++;
      if(person_code.count(person2) == 0) person_code[person2] = numPeopleRead++;

      distance[person_code[person1]][person_code[person2]] = 1;
      distance[person_code[person2]][person_code[person1]] = 1;
    }

    // if(numPeopleRead < numPeople) Here, under a few conditions, we are able
    //                               to know wether is disconected or not

    // (FLOYD ALGORITHM) Now we get the minimum distance from each vertex to each other
    for(int k = 0; k < numPeople; k++)
    for(int i = 0; i < numPeople; i++)
    for(int j = 0; j < numPeople; j++)
    {
      auxC_k = distance[i][k] + distance[k][j];

      if(auxC_k < distance[i][j])  distance[i][j] = auxC_k;
    }

    /*for(int i = 0; i < numPeople; i++)
    {
      for(int j = 0; j < numPeople; j++)
        cout << distance[i][j] << " ";
        cout << endl;
    }*/

    // Get the maximum and print the solution
    int maximum = 0;

    for(int i = 0;   i < numPeople; i++)
    for(int j = i+1; j < numPeople; j++)
    {
      if(distance[i][j] > maximum) maximum = distance[i][j];
    }

    if(maximum == INFINITY) cout << "DESCONECTADA\n";
    else                    cout << maximum << '\n';

    cin >> numPeople >> numRelations;
  }


  return 0;
}
