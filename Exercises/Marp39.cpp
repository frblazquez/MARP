#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

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

   GrafoDirigidoValorado(int v) : _V(v), _E(0), _ady(_V) { minCostFromV[0] = 0; for(int i=1; i<v; i++) minCostFromV[i]=-1; }
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
*/
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
}

int costeCasaMensajeroHasta(int w)
{
  return minCostFromV[w];
}

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//

private:
   int _V;   // número de vértices
   int _E;   // número de aristas
   std::vector<AdysDirVal<Valor>> _ady;   // vector de listas de adyacentes

   //MARP39.CPP!
   int minCostFromV[10000];
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
  int numHouses, numConections, ini, end, cost, casaMensajero, numPackages;

  cin >> numHouses >> numConections;

  while(cin)
  {
    GrafoDirigidoValorado<int> ida(numHouses);
    GrafoDirigidoValorado<int> vuelta(numHouses);

    for(int i = 0; i < numConections; i++)
    {
      cin >> ini >> end >> cost;

      ida.ponArista({ini-1, end-1, cost});
      vuelta.ponArista({end-1,ini-1,cost});
    }

    cin >> casaMensajero >> numPackages;

    ida.casaMensajeroEn(casaMensajero-1);
    vuelta.casaMensajeroEn(casaMensajero-1);

    int costeTotal = 0, nextHouse, houseCostIda, houseCostVuelta;
    bool possible = true;

    for(int i = 0; i<numPackages; i++)
    {
      cin >> nextHouse;

      if(possible)
      {
        houseCostIda = ida.costeCasaMensajeroHasta(nextHouse-1);
        houseCostVuelta = vuelta.costeCasaMensajeroHasta(nextHouse-1);

        possible = (houseCostIda != -1 && houseCostVuelta != -1);
        costeTotal += houseCostIda + houseCostVuelta;
      }
    }

    if(possible) cout << costeTotal << '\n';
    else         cout << "Imposible\n";

    cin >> numHouses >> numConections;
  }

  return 0;
}
