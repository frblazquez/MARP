/*
*   Copyright © 2018
*
*   Francisco Javier Blázquez Martínez ~ frblazqu@ucm.es
*
*   Doble grado Ingeniería informática - Matemáticas
*   Universidad Complutense de Madrid
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <queue>
using namespace std;

template <typename Valor>
class AristaDirigida_impl
{
public:
   AristaDirigida_impl(int v, int w, Valor valor) : v(v), w(w), _valor(valor) {};
   int from()     const { return v; }
   int to()       const { return w; }
   Valor valor()  const { return _valor; }
private:
   int v, w;
   Valor _valor;
};

template <typename Valor>
class AristaDirigida
{
public:
   AristaDirigida() : pimpl(nullptr) {};
   AristaDirigida(int v, int w, Valor valor) : pimpl(std::make_shared<AristaDirigida_impl<Valor>>(v, w, valor)) {};
   int from()    const { return pimpl->from(); }
   int to()      const { return pimpl->to(); }
   Valor valor() const { return pimpl->valor(); }
private:
   std::shared_ptr<AristaDirigida_impl<Valor>> pimpl;
};

template <typename Valor>
using AdysDirVal = std::vector<AristaDirigida<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoDirigidoValorado {
public:

   GrafoDirigidoValorado(int v) : _V(v), _E(0), _ady(_V) , toExplore() {for(int i=0; i<v; i++) minCosteTo[i]=-1;}
   int V() const { return _V; }
   int E() const { return _E; }
   void ponArista(AristaDirigida<Valor> arista)
   {
      int v = arista.from();
      int w = arista.to();
      if (v >= _V || w >= _V) throw std::invalid_argument("Vertice inexistente");
      ++_E;
      _ady[v].push_back(arista);
   }

//----------------------------------------------------------------------------//
//------------------------------ MARP39.CPP ----------------------------------//

/*
  This method makes the attribute minCostFromV have for each position i the minimun
  cost of going form v vertex to i.
*
void casaMensajeroEn(int v)
{
  int vertex, toVertexCost,adyacente, edgeCost;
  std::vector<int> nexts;

  minCostFromV[v] = 0;
  nexts.push_back(v);

  while(!nexts.empty())
  {
    vertex = nexts.back(); nexts.pop_back();
    toVertexCost = minCostFromV[vertex];

    for(int j = 0; j<_ady[vertex].size(); j++)
    {
      adyacente = _ady[vertex][j].to();
      edgeCost  = _ady[vertex][j].valor();

      if(minCostFromV[adyacente] == -1 || minCostFromV[adyacente]>toVertexCost+edgeCost)
      {
        minCostFromV[adyacente]=toVertexCost+edgeCost;
        nexts.push_back(adyacente);
      }
    }
  }
}*/

/*
void casaMensajeroEn(int v)
{
  minCostFromV[v] = 0;
  nexts.push({0, v});
}

int costeCasaMensajeroHasta(int w)
{
  int vertex, adyacente, edgeCost, vertexCost;

  // No vacía, elemento no encontrado aún en la componente o se puede mejorar
  while(!nexts.empty() && (minCostFromV[w] == -1 || -nexts.top().first<minCostFromV[w]))
  {
    vertex = nexts.top().second; vertexCost = minCostFromV[vertex]; nexts.pop();

    for(int j = 0; j < _ady[vertex].size(); j++)
    {
      adyacente = _ady[vertex][j].to();
      edgeCost = _ady[vertex][j].valor();

      if(minCostFromV[adyacente]==-1 || minCostFromV[adyacente]>vertexCost+edgeCost)
      {
        minCostFromV[adyacente] = vertexCost + edgeCost;
        nexts.push({-minCostFromV[adyacente], adyacente});
      }
    }
  }

  return minCostFromV[w];
}
*/
void casaMensajeroEn(int casa)
{
  minCosteTo[casa] = 0;
  toExplore.push({0, casa});
}

int costeACasa(int destino)
{
  int vertex, toVertexCost, adyacente, edgeCost;

  //Mientras que podamos seguir explorando y queramos seguir explorando (no encontrado o no mejorable)
  while(!toExplore.empty() && (minCosteTo[destino] == -1 || (-1)*toExplore.top().first < minCosteTo[destino]))
  {
    vertex = toExplore.top().second; toVertexCost = minCosteTo[vertex]; toExplore.pop();

    for(int j = 0; j < _ady[vertex].size(); j++)
    {
      adyacente = _ady[vertex][j].to(); edgeCost = _ady[vertex][j].valor();

      if(minCosteTo[adyacente]==-1 || minCosteTo[adyacente]>toVertexCost+edgeCost)
      {
        minCosteTo[adyacente] = toVertexCost + edgeCost;
        toExplore.push({(-1)*minCosteTo[adyacente], adyacente});
      }
    }

  }

  return minCosteTo[destino];
}

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//

private:
   int _V;   // número de vértices
   int _E;   // número de aristas
   std::vector<AdysDirVal<Valor>> _ady;   // vector de listas de adyacentes

   //MARP39.CPP
   int minCosteTo[10000];
   priority_queue<pair<int,int>> toExplore;
};

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
  int numCasas, numCaminos, ini, fin, esfuerzo;
  cin >> numCasas;

  while(cin)
  {
    cin >> numCaminos;

    GrafoDirigidoValorado<int> mapaIda(numCasas);
    GrafoDirigidoValorado<int> mapaVuelta(numCasas);

    for(int i = 0; i < numCaminos; i++)
    {
      cin >> ini >> fin >> esfuerzo;

      mapaIda.ponArista({ini-1,fin-1,esfuerzo});
      mapaVuelta.ponArista({fin-1,ini-1,esfuerzo});
    }

    bool posible = true;
    int casaRepartidor, numPaquetes, nextCasa, costeIda, costeVuelta, costeTotal = 0;

    cin >> casaRepartidor >> numPaquetes;

    mapaIda.casaMensajeroEn(casaRepartidor-1);
    mapaVuelta.casaMensajeroEn(casaRepartidor-1);

    for(int i = 0; i < numPaquetes; i++)
    {
      cin >> nextCasa;

      if(posible)
      {
        costeIda    = mapaIda.costeACasa(nextCasa-1);
        costeVuelta = mapaVuelta.costeACasa(nextCasa-1);

        costeTotal += (costeIda + costeVuelta);
        posible = (costeIda != -1 && costeVuelta != -1);
      }
    }

    if(posible) cout << costeTotal << '\n';
    else        cout << "Imposible\n";

    cin >> numCasas;
  }

  return 0;
}
