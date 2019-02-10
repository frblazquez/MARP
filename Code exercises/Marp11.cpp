/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Double degree in Mathematics - Computer engineering
*   Complutense University, Madrid
*
*   Statement: Implement a method to check wether a tree 
*              has AVL structure or not.
*/

#include <iostream>
using namespace std;

// Returns true iff the arbol read is AVL
bool readTree();
bool balancedSearchTree(int &altura, int& maxim, int& minim);

int main()
{
  int numCases; cin >> numCases;

  while(numCases--)
  {
    if(readTree())
      cout << "SI\n";
    else
      cout << "NO\n";
  }

  return 0;
}

// Just for hiding the attributes needed for calling balancedSearchTree()
bool readTree()
{
  int aux, maxim, minim;

  return balancedSearchTree(aux, maxim, minim);
}

bool balancedSearchTree(int &altura, int &maxim, int &minim)
{
  int c; cin >> c;

  if(c == -1) {altura = 0; maxim = -1; minim = -1; return true;} //-1 means undefined!

  // Non base case!
  int maxDcha, minDcha, alturaDcha; bool hojaDcha = false;
  int maxIzq, minIzq, alturaIzq;    bool hojaIzq  = false;

  bool avlIzq  = balancedSearchTree(alturaIzq,  maxIzq,  minIzq);
  bool avlDcha = balancedSearchTree(alturaDcha, maxDcha, minDcha);

  if(maxIzq  == -1) {maxIzq  = c; minIzq  = c; hojaIzq  = true;}
  if(maxDcha == -1) {maxDcha = c; minDcha = c; hojaDcha = true;}

  altura = max(alturaDcha, alturaIzq) + 1;
  maxim  = max(maxDcha, maxIzq);
  minim  = min(minDcha, minIzq);

  bool maxCondition = (hojaIzq  || maxIzq  < c);  //Just to avoid leaf case
  bool minCondition = (hojaDcha || minDcha > c);  //We let it be a special case

  return avlDcha && avlIzq && abs(alturaDcha - alturaIzq) <= 1 && maxCondition && minCondition;
}
