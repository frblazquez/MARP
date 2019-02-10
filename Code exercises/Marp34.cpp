/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Maximum size of a connected component in a
*              dinamic insertion situation.
*/

#include <iostream>
#include <unordered_map>
using namespace std;

int photo[1000000]; //Global variable BAD PRACTISE!!

int theFather(int pos)
{
  //It's its own father
  if(photo[pos]==pos) return pos;

  //Find it's father and update it
  photo[pos] = theFather(photo[pos]);

  return photo[pos];
}

void comp_union(int row, int col, int numRows, int numCols, unordered_map<int, int> &sizesMap, int &max)
{
  int father1, father2, comp1Size, comp2Size;

  for(int i = -1; i<=1; i++)
  for(int j = -1; j<=1; j++)
  {
    //Never out of range!
    if((i!=0 || j!=0) && 0<=(row+i) && (row+i)<numRows && 0<=(col+j) && (col+j)<numCols)
    {
      //If it's a spot
      if(photo[(row+i)*numCols + (col+j)] != -1)
      {
        father1 = theFather((row+i)*numCols + (col+j));
        father2 = theFather(row*numCols + col);

        //If the new spot joins non connected components
        if(father1 != father2)
        {
          comp1Size = sizesMap[father1];
          comp2Size = sizesMap[father2];

          if(comp1Size < comp2Size) swap(father1, father2);

          photo[father2] = father1;
          sizesMap[father1] = comp1Size + comp2Size;
          sizesMap.erase(father2);

          if((comp1Size + comp2Size)>max) max=(comp1Size + comp2Size);
        }
      }
    }
  }
}

void union_inicio(int row, int col, int numRows, int numCols, unordered_map<int, int> &sizesMap, int &max)
{
  int father1, father2, comp1Size, comp2Size;

  for(int i = -1; i<1;      i++)
  for(int j = -1; j<(-2)*i; j++)
  {
    //Siempre que estemos en el rango buscamos manchas
    if(0<=(row+i) && (row+i)<numRows && 0<=(col+j) && (col+j)<numCols)
    {
      //If it's a spot
      if(photo[(row+i)*numCols + (col+j)] != -1)
      {
        father1 = theFather((row+i)*numCols + (col+j));
        father2 = theFather(row*numCols + col);

        //If spot by and spot are not connected yet
        if(father1 != father2)
        {
          comp1Size = sizesMap[father1];
          comp2Size = sizesMap[father2];

          if(comp1Size < comp2Size) swap(father1, father2);

          photo[father2] = father1;
          sizesMap[father1] = comp1Size + comp2Size;
          sizesMap.erase(father2);

          if((comp1Size + comp2Size)>max) max=(comp1Size + comp2Size);
        }
      }
    }
  }
}

int main()
{
  char c;  int numRows, numCols, numPhotos, maxUnidos, row,col;
  cin >> numRows >> numCols;

  while(cin)
  {
    cin.get(c);                                   //Reads the last end line
    maxUnidos = 0;                                //Maximal connected component
    unordered_map<int, int> father_componentSize; //Component father and size

    //------------------------- DATA LECTURE ---------------------------------//
    for(int i=0; i<numRows; i++){
    for(int j=0; j<numCols; j++)
    {
      cin.get(c);

      if(c==' ')  photo[i*numCols + j] = -1;
      else
      {
        photo[i*numCols + j] = (i*numCols + j);
        father_componentSize[i*numCols + j] = 1; if(maxUnidos==0) maxUnidos = 1;
        union_inicio(i,j,numRows, numCols, father_componentSize, maxUnidos);
      }
    } cin.get(c); /* gets the end linde char */ }
    //------------------------------------------------------------------------//

    cout << maxUnidos;
    cin >> numPhotos;

    //-------------------------- NEW SPOTS -----------------------------------//
    for(int k=0; k<numPhotos; k++)
    {
      cin >> row >> col; row--; col--;

      if(photo[row*numCols + col] != -1) /* Intentionally */;
      else
      {
        photo[row*numCols + col] = row*numCols + col;
        father_componentSize[row*numCols + col] = 1; if(maxUnidos==0) maxUnidos = 1;
        comp_union(row,col,numRows,numCols,father_componentSize, maxUnidos);
      }

      cout << " " << maxUnidos;
    }
    //------------------------------------------------------------------------//

    cout << '\n';
    cin >> numRows >> numCols;
  }

  return 0;
}
