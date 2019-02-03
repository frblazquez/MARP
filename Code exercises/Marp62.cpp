/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
using namespace std;

int main()
{
  string s1, s2; cin >> s1 >> s2;
  char a_i; int b_j, delta;

  while(cin)
  {
    int board[s1.size()+1][s2.size()+1];

    for(int i = 0; i <= s1.size(); i++) board[i][0] = 0;
    for(int i = 0; i <= s2.size(); i++) board[0][i] = 0;

    for(int i = 1; i <= s1.size(); i++)
    {
      a_i = s1[i-1]; b_j = 1; delta = 0;

      for(int j = 1; j <= s2.size(); j++)
      {
        if(s2[j-1] == a_i) {b_j = j; delta = 1;}

        board[i][j] = max(board[i-1][j], delta + board[i-1][b_j-1]);
      }
    }

    cout << board[s1.size()][s2.size()] << '\n';
    cin >> s1 >> s2;
  }

  return 0;
}
