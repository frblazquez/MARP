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
  int length, numCuts, aux;
  cin >> length >> numCuts;

  while(length || numCuts)
  {
    // Lectura de los cortes en el tablero
    vector<int> cuts;

    cuts.push_back(0);

    for(int i = 0; i < numCuts; i++)
    {cin >> aux; cuts.push_back(aux);}

    cuts.push_back(length);

    // Tabla de programación dinámica
    int board[numCuts+2][numCuts+2];

    // 1.- Inicialización
    for(int i = 0; i < 2;           i++)
    for(int j = 0; j < numCuts+2-i; j++)
      board[j][j+i] = 0;

    // 2.- Rellenado
    int minimum;

    for(int i = 2; i < numCuts+2;   i++)
    for(int j = 0; j < numCuts+2-i; j++)
    {
      minimum = -1;

      for(int k = 1; k < i; k++)
      {
        aux = board[j][j+k] + board[j+k][j+i];

        if(minimum == -1 || aux < minimum) minimum = aux;
      }

      board[j][j+i] = minimum + 2*(cuts[j+i] - cuts[j]);
    }

    cout << board[0][numCuts+1] << '\n';
    cin >> length >> numCuts;
  }

  return 0;
}
