#include <iostream>
#include <unordered_map>
using namespace std;

const int MAX_PIXELS = 1000000;

typedef int picture[MAX_PIXELS];

int father(int pos, picture &photo)
{
  if(photo[pos] == pos)    return pos;        //Buscamos aquel que se apunte a sí mismo
  else
  {
    int posFather = father(photo[pos],photo); //Si no es padre, hallamos el padre de su padre
    photo[pos] = posFather;                   //Ya que subimos, aprovechamos para reducir la distancia al padre

    return posFather;
  }
}

void comp_union(int pos, int pos_by, int &max, picture &photo, unordered_map<int, int> &component_size)
{
  //En vez de trabajar con las posiciones de las casillas trabajamos con las componentes conexas,
  //representadas por los padres
  int comp1Father = father(pos, photo),
      comp2Father = father(pos_by, photo);

  //Agregamos la componente de pos_by a la de pos si son de distintas componentes
  if(comp1Father != comp2Father)
  {
    int comp1Size = component_size[comp1Father],
        comp2Size = component_size[comp2Father];

    //Hacemos la componente de menor tamaño hija de la mayor
    if(comp1Size < comp2Size) swap(comp1Father,comp2Father);

    //Un padre <=> una componente conexa <=> un tamaño en el mapa
    //Los padres que pasan a ser hijos son borrados del mapa
    //Actualizamos el tamaño y el máximo
    photo[comp2Father] = comp1Father;
    component_size[comp1Father] += component_size[comp2Father];
    component_size.erase(comp2Father);

    if(component_size[comp1Father]>max) max = component_size[comp1Father];
  }
}


int main()
{
  picture photo; //Picture <=> int[1000000]

  char c; int numPhotos, row,col, pos, pos_by, max;
  int numRows, numCols; cin >> numRows >> numCols; cin.get(c); //reads end line char

  while(cin)
  {
    unordered_map<int, int> component_size; max = 0;

    // Lectura de datos
    for(int i = 0; i < numRows; i++)
    {
    for(int j = 0; j < numCols; j++)
    {
      cin.get(c); pos = numRows*i + j;

      if(c == ' ') photo[pos] = -1;
      else
      {
        photo[pos] = pos;               //Si es una mancha, la marcamos y la uniremos
        component_size[pos] = 1;        //a cualquier componente conexa a su alrededor
        if(max == 0) max = 1;           //si esta existe.

        for(int k = -1; k < 1;    k++)    //k perteneciente a {-1,0}
        for(int l = -1; l < -2*k; l++)    //l perteneciente a {-1,0,1} si k=-1 {-1} si k=0
        {
          if(0 <= i+k && 0 <= j+l && j+l < numCols) //Siempre en el rango
          {
            pos_by = numRows*(i+k) + (j+l);

            if(photo[pos_by] != -1) comp_union(pos,pos_by,max,photo,component_size);
          }
        }
      }
      }

      cin.get(c);
    }

    /*for(int i = 0; i < numRows; i++)
    {
    for(int j = 0; j < numCols; j++)
    {
      cout << photo[i*numRows + j] << " ";
    }
    cout << endl;
    }*/

    cout << max;
    cin >> numPhotos;

    // Consultas
    for(int i = 0; i < numPhotos; i++)
    {
      cin >> row >> col; row--; col--;

      pos = row*numRows + col;    //Por simplicidad

      if(photo[pos] == -1)        //Si no es ya de una componente conexa
      {
      photo[pos] = pos;           //La marcamos como contaminada
      component_size[pos] = 1;    //El tamaño de su mancha es 1
      if(max == 0) max = 1;

      for(int k = -1; k <= 1; k++)
      for(int l = -1; l <= 1; l++)
      {
        //Siempre que estemos en el rango y no sea la propia posición
        if(0 <= row+k && row+k <numRows && 0 <= col+l && col+l < numCols && (l!=0 || k!= 0))
        {
          pos_by = numRows*(row+k) + (col+l);

          if(photo[pos_by] != -1) comp_union(pos,pos_by,max,photo,component_size);
        }
      }
      }

      /*for(int i = 0; i < numRows; i++)
      {
      for(int j = 0; j < numCols; j++)
      {
        cout << photo[i*numRows + j] << " ";
      }
      cout << endl;
      }*/

      cout << " " << max;
    }

    cout << '\n';
    cin >> numRows >> numCols; cin.get(c);
  }

  return 0;
}
