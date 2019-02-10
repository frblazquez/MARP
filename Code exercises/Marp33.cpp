/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Connected components problem in a matrix of pixels.
*/

#include <iostream>
using namespace std;

const int MAX_DIM = 100;

void marcarComponente(bool matrix[100][100], int rowPos, int colPos, int numRows, int numCols);

int main()
{
  int high,width; cin >> width >> high;
  bool matrix[100][100];

  while(cin)
  {
    char c;

    for(int i = 0; i < high; i++)
    for(int j = 0; j < width; j++)
    {
      cin >> c;

      if(c == 'X') matrix[i][j] = false;  //Black cell
      else         matrix[i][j] = true;   //White cell
    }

    int numConectedComponets = -1;

    for(int i = 0; i < high; i++)
    for(int j = 0; j < width; j++)
    {
      if(matrix[i][j])
      {
        numConectedComponets++;
        marcarComponente(matrix,i,j,high,width);
      }
    }

    cout << numConectedComponets << '\n';
    cin >> width >> high;
  }

  return 0;
}

void marcarComponente(bool matrix[100][100], int rowPos, int colPos, int numRows, int numCols)
{
  if(matrix[rowPos][colPos])
  {
    matrix[rowPos][colPos] = false;

    if(rowPos+1<numRows) marcarComponente(matrix, rowPos+1, colPos, numRows, numCols);
    if(colPos+1<numCols) marcarComponente(matrix, rowPos, colPos+1, numRows, numCols);
    if(rowPos-1>=0)      marcarComponente(matrix, rowPos-1, colPos, numRows, numCols);
    if(colPos-1>=0)      marcarComponente(matrix, rowPos, colPos-1, numRows, numCols);
  }
}
