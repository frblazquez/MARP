/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
  string s1; cin >> s1;

  while(cin)
  {
    // INICIALIZACIÓN
    pair<int,pair<int,int>> subpalindrome[s1.size()][s1.size()];

    for(int i = 0; i < s1.size(); i++)
      subpalindrome[i][i]   = {1, {i,i}};

    for(int i = 1; i < s1.size(); i++)
      subpalindrome[i][i-1] = {0,{-1,-1}};

    // RELLENADO
    for(int i = 1; i < s1.size();   i++)
    for(int j = 0; j < s1.size()-i; j++)
    {
      if(s1[j] == s1[j+i])
      {
        subpalindrome[j][j+i].first = 2 + subpalindrome[j+1][j+i-1].first;
        subpalindrome[j][j+i].second.first = j+1;
        subpalindrome[j][j+i].second.second= j+i-1;
      }
      else if(subpalindrome[j][j+i-1].first > subpalindrome[j+1][j+i].first)
      {
        subpalindrome[j][j+i].first  = subpalindrome[j][j+i-1].first;
        subpalindrome[j][j+i].second.first = j;
        subpalindrome[j][j+i].second.second= j+i-1;
      }
      else
      {
        subpalindrome[j][j+i].first  = subpalindrome[j+1][j+i].first;
        subpalindrome[j][j+i].second.first = j+1;
        subpalindrome[j][j+i].second.second= j+i;
      }
    }

    // RECONSTRUCCIÓN DE LA SOLUCIÓN
    string s2 = "";
    int k = 0, l = s1.size()-1;

    while(l > k)
    {
      if(subpalindrome[k][l].second.first == k+1 && subpalindrome[k][l].second.second == l-1)
      {
        s2.push_back(s1[k]);

        k++; l--;
      }
      else if(subpalindrome[k][l].second.first == k+1)
        k++;
      else
        l--;
    }

    if(k == l)
    {
      s2.push_back(s1[k]);

      for(int m = s2.size() - 2; m >= 0; m--) s2.push_back(s2[m]);
    }
    else
      for(int m = s2.size() - 1; m >= 0; m--) s2.push_back(s2[m]);

    cout << s2 << '\n';
    cin >> s1;
  }

  return 0;
}


/* TIME LIMIT - MEMORY LIMIT
#include <iostream>
using namespace std;

int main()
{
  string s1, s2, s3; cin >> s1;
  char a_k; int index;

  while(cin)
  {
    string board[s1.size()][s1.size()];

    for(int i = 0; i < s1.size(); i++)
      board[i][i] = s1[i];

    for(int i = 1; i < s1.size(); i++)
      board[i][i-1] = "";

    for(int i = 1; i < s1.size(); i++)
    {
      for(int j = 0; j < s1.size()-i; j++)
      {
        // Aquí tenemos que calcular board[j][j+i] !!
        a_k = s1[j];

        index = j+i;
        while(s1[index] != a_k) index--;

        // Aquí ya tenemos index apuntando a un char == a_k
        if(index == j || board[j+1][j+i].size() >= 2 + board[j+1][index-1].size())
          board[j][j+i] = board[j+1][j+i];
        else
          board[j][j+i] = a_k + board[j+1][index-1] + a_k;
      }

    }

    cout << board[0][s1.size()-1] << '\n';
    cin >> s1;
  }

  return 0;
}*/
