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
  // Análise de complexidade
  InstrReset();
  InstrName[0] = "Comparações";
  InstrName[1] = "Iterações";
  InstrName[2] = "Chamadas a outras funções";
  InstrName[3] = NULL;
  InstrCount[0] = 0; //medirá comprações
  InstrCount[1] = 0; //medirá iterações
  InstrCount[2] = 0; //medirá chamadas a outras funções
 
  IndicesSet* result = NULL;
  IndicesSet* current = IndicesSetCreateEmpty(GraphGetVertexRange(g));
  InstrCount[2] += 2;

  // Na primeira comparação, bestSize deve ser o maior número possível
  // De modo a que tome o valor do primeiro size
  int bestSize = INT_MAX;

  do {
    InstrCount[2]++;
    if (!IndicesSetIsEmpty(current)){
      InstrCount[2]++; 
      if (GraphIsDominatingSet(g, current)){
        InstrCount[2]++; 
        int size = IndicesSetGetNumElems(current);
        
        InstrCount[0]++; 
        if (size < bestSize){
          InstrCount[0]++; 
          if (result != NULL){
            IndicesSetDestroy(&result);
            InstrCount[2]++;
          }

          result = IndicesSetCreateCopy(current); 
          InstrCount[2]++; 
          bestSize = size; 
        }
      }
    }

    InstrCount[1]++; 
    InstrCount[2]++; 
  } while (IndicesSetNextSubset(current));

  InstrPrint();
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
  InstrCount[1] = 0; //medirá iterações internas
  InstrCount[2] = 0; //medirá iterações globais
  InstrCount[3] = 0; //medirá chamadas a outras funções

  InstrCount[3]+=2;
  double* pesos = GraphComputeVertexWeights(g);
  IndicesSet* current = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  // Na primeira comparação, bestPeso deve ser o maior número possível
  // De modo a que tome o valor do primeiro peso
  double bestPeso = DBL_MAX;

  IndicesSet* result = NULL;

  do{
    InstrCount[3]++;
    if(!IndicesSetIsEmpty(current)){
      InstrCount[3]++;
      if(GraphIsDominatingSet(g, current)){
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
    }
      
    InstrCount[2]++;
    InstrCount[3]++;
  } while(IndicesSetNextSubset(current));

  //InstrCalibrate();
  InstrPrint();
  IndicesSetDestroy(&current);
  free(pesos);
  
  return result;
}
