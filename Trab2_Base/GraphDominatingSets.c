//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira - Nov 2025
//
// GraphDominatingSets - Computing Vertex Dominating Sets for UNDIRECTED graphs
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphIsDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinWeightDominatingSet FUNCTION ***/

#include "GraphDominatingSets.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IndicesSet.h"
#include "instrumentation.h"

//
// TO BE COMPLETED
//
// Check if the given set is a dominating set for the graph
// Return 1 if true, or 0 otherwise
//
// A dominating set is a set of graph vertices such that every other
// graph vertex not in the set is adjacent to a graph vertex in the set
//
int GraphIsDominatingSet(const Graph* g, IndicesSet* vertSet) { //MIGUEL
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  assert(IndicesSetIsEmpty(vertSet) == 0);

  IndicesSet* allVerts = GraphGetSetVertices(g);

  int vIdx = IndicesSetGetFirstElem(allVerts);
  while(vIdx!=-1){
    if(!IndicesSetContains(vertSet, vIdx)){
      IndicesSet* adj = GraphGetSetAdjacentsTo(g,vIdx);
      IndicesSet* adjCopy = IndicesSetCreateCopy(adj);
      IndicesSetIntersection(adjCopy, vertSet);

      if(IndicesSetIsEmpty(adjCopy)){
        IndicesSetDestroy(&adjCopy);
        IndicesSetDestroy(&adj);
        IndicesSetDestroy(&allVerts);
        return 0;
      }

      IndicesSetDestroy(&adjCopy);
      IndicesSetDestroy(&adj);  
    }
    vIdx = IndicesSetGetNextElem(allVerts);
  }
  IndicesSetDestroy(&allVerts);
  return 1;
}

//
// TO BE COMPLETED
//
// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  //
  // TO BE COMPLETED
  //

  // Change this according to your algorithm
  IndicesSet* result = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  return result;
}

//
// TO BE COMPLETED
//
// Compute a MIN WEIGHT VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the dominating set
//
IndicesSet* GraphComputeMinWeightDominatingSet(const Graph* g) { //MIGUEL
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  //perguntar se é necessário assertar que é grafo com pesos, provavelmente sim
  
  double* pesos = GraphComputeVertexWeights(g);
  IndicesSet* current = IndicesSetCreateEmpty(GraphGetVertexRange(g));
  double bestPeso = -1;
  IndicesSet* result = NULL;

  do{
    if(!IndicesSetIsEmpty(current) && GraphIsDominatingSet(g, current)){
      double peso = 0;
      int v = IndicesSetGetFirstElem(current);
      while(v != -1){
        peso += pesos[v];
        v = IndicesSetGetNextElem(current);
      }

      if(result == NULL || peso < bestPeso){
        if(result != NULL){
          IndicesSetDestroy(&result);
        }
        result = IndicesSetCreateCopy(current);
        bestPeso = peso;
      }

    }

  } while(IndicesSetNextSubset(current) != 0);

  IndicesSetDestroy(&current);
  free(pesos);
  
  return result;
}
