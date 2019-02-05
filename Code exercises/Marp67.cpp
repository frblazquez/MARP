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

const int INFINITY = 100000000;

int main()
{
  int numValues, numCoins, value, cost;
  cin >> numValues;

  while(cin)
  {
    // Lectura de datos:
    vector<pair<int,int>> values_coins;

    for(int i = 0; i < numValues; i++)
    {cin >> value; values_coins.push_back({value, 0});}

    for(int i = 0; i < numValues; i++)
    {cin >> numCoins; values_coins[i].second = numCoins;}

    cin >> cost;

    // Tabla de programación dinámica
    int board[cost + 1]; board[0] = 0; int k;

    for(int i = 1; i <= cost; i++) board[i] = INFINITY;

    for(int i = 0; i < numValues; i++)
    for(int j = cost - values_coins[i].first; j >= 0; j--)
    {
      if(board[j] != INFINITY)
      {
        k = 1;

        while(k <= values_coins[i].second         &&                  // Queden monedas de este tipo
              j + k*values_coins[i].first <= cost &&                  // No nos pasemos del coste
              board[j + k*values_coins[i].first] > board[j] + k)      // Mejoremos el número de monedas
        {
          board[j + k*values_coins[i].first]  = board[j] + k;         // Guardamos el nuevo mínimo
          k++;
        }

      }
    }

    /*for(int i = 0; i <= cost; i++)
      cout << board[i].first << " ";
      cout << endl;
    for(int i = 0; i <= cost; i++)
      cout << board[i].second << " ";
      cout << endl;*/

      if(board[cost] == INFINITY) cout << "NO\n";
      else
      {
        cout << "SI " << board[cost] << '\n';
        /*
        for(int i = 0; i <= cost; i++)
        {
          if(board[i] == INFINITY)
            cout << "- ";
          else
            cout << board[i] << " ";
        }
          cout << endl;

        for(int i = 0; i < numValues; i++)
          values_coins[i].second = 0;

        value = cost; k = 0;

        while(value != 0)
        {
          if(board[value - values_coins[k].first] == board[value] -1)
            {values_coins[k].second++; value -= values_coins[k].first;}
          else
            k++;
        }

        cout << "SI ";

        for(int i = 0; i < numValues-1; i++)
          cout << values_coins[i].second << " ";

        cout << values_coins[numValues-1].second << '\n';*/
      }

      cin >> numValues;
    }


  return 0;
}
