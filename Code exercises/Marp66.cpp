/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int numBuckets, aux;
  cin >> numBuckets;

  while(numBuckets)
  {
    // Lectura de los datos de la entrada
    vector<int> buckets;

    for(int i = 0; i < numBuckets; i++)
    {cin >> aux; buckets.push_back(aux);}

    // Tabla de programación dinámica
    int board[numBuckets][numBuckets];

    for(int i = 0; i < numBuckets; i++)
      board[i][i] = buckets[i];

    for(int i = 0; i < numBuckets-1; i++)
      board[i][i+1] = max(buckets[i],buckets[i+1]);

    int delta = 1 - numBuckets%2;
    int op1, op2;

    for(int i = 2 + delta; i < numBuckets; i += 2)
    for(int j = 0; j + i < numBuckets; j++)
    {
      // Op1: We take the bucket j+i
      if(buckets[j] > buckets[j+i-1])
        op1 = buckets[j+i] + board[j+1][j+i-1];
      else
        op1 = buckets[j+i] + board[j][j+i-2];

      // Op2: We take the bucket j
      if(buckets[j+1] > buckets[j+i])
        op2 = buckets[j] + board[j+2][j+i];
      else
        op2 = buckets[j] + board[j+1][j+i-1];

      board[j][j+i] = max(op1, op2);
    }

    cout << board[0][numBuckets-1] << '\n';
    cin >> numBuckets;
  }

  return 0;
}
