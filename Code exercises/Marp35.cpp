/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

//Si da timelimit es porque tienes el esquema de union-find con path-compression
//pero sin contemplar que en las uniones el de menor profundidad sea el hijo del de mayor prof.
//se puede hacer de esta otra forma añadiendo un mapa para controlar padres-tamaño.

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int father(vector<int> &componentes, int pos)
{
  //Si el elemento es un padre lo devolvemos
  if(componentes[pos] == pos) return pos;

  //Si no hallamos su padre y actualizamos su "puntero"
  componentes[pos] = father(componentes, componentes[pos]);

  return componentes[pos];
}

int main()
{
  int alto, ancho, maxSalto, numArboles, row, col;
  cin >> alto >> ancho >> maxSalto >> numArboles;

  while(cin)
  {
    alto++; ancho++;                                    // Teniendo en cuenta que va de [0,ancho) [0,alto)

    std::vector<int> arboles(alto*ancho, -1);           // For the union-find schema (-1 means empty)
    std::vector<pair<int,int>> cortados;                // For knowing the cut-order

    for(int i = 0; i < numArboles; i++)                 // Reads the trees in reverse-cut order
    {cin >> row >> col; cortados.push_back({row,col});}

    //--------------------------------------------------//
    // Union find schema:
    // We'll be placing trees in their position where they
    // were cut (int the order they were cut) until we can
    // connect the last and the first position.
    //--------------------------------------------------//

    int last = alto*ancho -1, i = cortados.size(), pos, rowPos, colPos;
    int pos_by, father_by, father_act;

    arboles[0]    = 0;
    arboles[last] = last;

    /*
    for(int i = 0; i< alto;  i++){
    for(int j = 0; j< ancho; j++)
    {
      cout << arboles[i*ancho + j] << " ";
    } cout << '\n';}*/

    // if(alto <= maxSalto+1 && ancho <= maxSalto+1) cout << '\n'; <= AÚN SE PUEDE!

    // Mientras que no estén en la misma componente conexa y queden árboles
    while(father(arboles,0)!=father(arboles,last) && i>0)
    {
      //Decrementamos para apuntar al árbol cortado
      i--;

      //Ponemos el árbol que fue cortado
      rowPos = cortados[i].first;
      colPos = cortados[i].second;
      pos = rowPos*ancho + colPos;
      arboles[pos] = pos;

      /*
      for(int i = 0; i< alto;  i++){
      for(int j = 0; j< ancho; j++)
      {
        cout << arboles[i*ancho + j] << " ";
      } cout << '\n';}*/

      //Lo unimos con las componentes colindantes (los que distan menos que maxSalto)
      for(int k = -maxSalto; k<= maxSalto; k++)
      for(int l = -maxSalto; l<= maxSalto; l++)
      {
        //Siempre que no nos salgamos fuera de la matriz! (y no estemos en la posición del árbol colocado)
        if((k!=0||l!=0) && 0<=rowPos+k && rowPos+k<alto && 0<=colPos+l && colPos+l<ancho &&
           sqrt(k*k + l*l)<=maxSalto) // CONDICIÓN CRÍTICA!! DISTANCIA EUCLÍDEA!!
        {
          pos_by = (rowPos+k)*ancho + (colPos+l);

          if(arboles[pos_by] != -1)
          {
            //Tenemos que unir el árbol añadido con esta componente!!
            father_act = father(arboles,pos);
            father_by  = father(arboles,pos_by);

            //Nos da igual incluso si ya están en la misma componente
            arboles[father_act] = father_by;
          }
        }
      }

      /*
      for(int i = 0; i< alto;  i++){
      for(int j = 0; j< ancho; j++)
      {
        cout << arboles[i*ancho + j] << " ";
      } cout << '\n';}*/

    }

    if(father(arboles,0) != father(arboles,last))
      cout << "NUNCA SE PUDO\n";
    else
      cout << cortados[i].first << " " << cortados[i].second << '\n';

    cin >> alto >> ancho >> maxSalto >> numArboles;
  }

  return 0;
}
