#include <assert.h>

#include "Graph.h"
#include "GraphDominatingSets.h"
#include "IndicesSet.h"

int main(void) {
    FILE* file = fopen("G_2.txt", "r");
    Graph* g02 = GraphFromFile(file);
    fclose(file);
    // Displaying in DOT format
    GraphDisplayDOT(g02);
    printf("\n");
}