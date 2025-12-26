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
#include <float.h>
#include <limits.h>

#include "Graph.h"
#include "IndicesSet.h"
#include "instrumentation.h"


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


// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  IndicesSet* result = NULL;
  IndicesSet* current = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  // Na primeira comparação, bestSize deve ser o maior número possível
  // De modo a que tome o valor do primeiro size
  int bestSize = INT_MAX;

  do {
    if (!IndicesSetIsEmpty(current) && GraphIsDominatingSet(g, current)){
      int size = IndicesSetGetNumElems(current);

      if (size < bestSize){
        if (result != NULL)
          IndicesSetDestroy(&result);

        result = IndicesSetCreateCopy(current); 
        bestSize = size; 
      }
    }
  } while (IndicesSetNextSubset(current));

  IndicesSetDestroy(&current);

  return result;
}

// Compute a MIN WEIGHT VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the dominating set
//
IndicesSet* GraphComputeMinWeightDominatingSet(const Graph* g) { //MIGUEL
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  //perguntar se é necessário assertar que é grafo com pesos, provavelmente sim
  InstrReset();
  InstrName[0] = "Comparações";
  InstrName[1] = "Iterações internas";
  InstrName[2] = "Iterações globais";
  InstrName[3] = "Chamadas a outras funções";
  InstrCount[0] = 0; //medirá comprações
  InstrCount[1] = 0;
  InstrCount[2] = 0; 
  InstrCount[3] = 0;

  InstrCount[3]+=2;
  double* pesos = GraphComputeVertexWeights(g);
  IndicesSet* current = IndicesSetCreateEmpty(GraphGetVertexRange(g));
  double bestPeso = DBL_MAX;
  IndicesSet* result = NULL;

  do{
    InstrCount[3]+=2;
    if(!IndicesSetIsEmpty(current) && GraphIsDominatingSet(g, current)){
      double peso = 0;
      int v = IndicesSetGetFirstElem(current);
      InstrCount[3]++;
      while(v != -1){
        peso += pesos[v];
        v = IndicesSetGetNextElem(current);
        InstrCount[1]++;
        InstrCount[3]++;
      }

      InstrCount[0]++;
      if(peso < bestPeso){
        InstrCount[0]++;
        if(result != NULL){
          InstrCount[3]++;
          IndicesSetDestroy(&result);
        }
        InstrCount[3]++;
        result = IndicesSetCreateCopy(current);
        bestPeso = peso;
      }

    }
    InstrCount[0]++;
    InstrCount[2]++;
    InstrCount[3]++;
  } while(IndicesSetNextSubset(current) != 0);

  //InstrCalibrate();
  InstrPrint();
  IndicesSetDestroy(&current);
  free(pesos);
  
  return result;
}
