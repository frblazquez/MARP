/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include <unordered_map>
using namespace std;

int photo[1000000]; //Global variable BAD PRACTISE!!

int theFather(int pos)
{
  //Si es un padre devuelve directamente su posición
  if(photo[pos]==pos) return pos;

  //Si no es un padre, haya su padre y actualiza su puntero
  photo[pos] = theFather(photo[pos]);

  return photo[pos];
}

void comp_union(int row, int col, int numRows, int numCols, unordered_map<int, int> &sizesMap, int &max)
{
  int father1, father2, comp1Size, comp2Size;

  for(int i = -1; i<=1; i++)
  for(int j = -1; j<=1; j++)
  {
    //Siempre que estemos en el rango buscamos manchas
    if((i!=0 || j!=0) && 0<=(row+i) && (row+i)<numRows && 0<=(col+j) && (col+j)<numCols)
    {
      //Si en efecto es una mancha
      if(photo[(row+i)*numRows + (col+j)] != -1)
      {
        father1 = theFather((row+i)*numRows + (col+j));
        father2 = theFather(row*numRows + col);

        //Si la colindante y la actual no están ya en la misma mancha
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
      //Si en efecto es una mancha
      if(photo[(row+i)*numRows + (col+j)] != -1)
      {
        father1 = theFather((row+i)*numRows + (col+j));
        father2 = theFather(row*numRows + col);

        //Si la colindante y la actual no están ya en la misma mancha
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
    maxUnidos = 0;                                //Tamaño de la mancha más grande
    unordered_map<int, int> father_componentSize; //Padre de la componente conexa y tamaño de esta

    //------------------------- LECTURA DE DATOS -----------------------------//
    for(int i=0; i<numRows; i++){
    for(int j=0; j<numCols; j++)
    {
      cin.get(c);

      if(c==' ')  photo[i*numRows + j] = -1;
      else
      {
        photo[i*numRows + j] = (i*numRows + j);
        father_componentSize[i*numRows + j] = 1;
        union_inicio(i,j,numRows, numCols, father_componentSize, maxUnidos);
      }
    } cin.get(c); /* gets the end linde char */ }
    //------------------------------------------------------------------------//

    cout << maxUnidos;
    cin >> numPhotos;

    //-------------------------- NUEVAS MANCHAS ------------------------------//
    for(int k=0; k<numPhotos; k++)
    {
      cin >> row >> col; row--; col--;

      if(photo[row*numRows + col] != -1) /* Intentionally */;
      else
      {
        photo[row*numRows + col] = row*numRows + col;
        father_componentSize[row*numRows + col] = 1;
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
