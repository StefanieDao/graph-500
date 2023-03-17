#include <stdexcept>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tuple>
#include <iostream>
using namespace std;

typedef tuple<int64_t, int64_t, int32_t> E;
typedef struct {
    int64_t V, // number of vertices
            E, // number of edges
            *N, // from ID  
            *F; // to ID
    int32_t *W; // weights
} csr;

int cmpfunc (const void * a, const void * b) {
   return ( *(int64_t*)a - *(int64_t*)b );
}

csr build_graph (E* edge_list, int num_vertices, int num_edges) {
    csr graph;
    graph.V = num_vertices;
    graph.E = num_edges;
    graph.N = (int64_t*) calloc(1 + (size_t) graph.V, sizeof (*graph.N));
    graph.F = (int64_t*) calloc((size_t) graph.E, sizeof (*graph.F));
    graph.W = (int32_t*) malloc(graph.E * sizeof(int32_t));

    // sort edgelist
    //qsort(edge_list[0], 4, 3*sizeof (int64_t*), cmpfunc);

    for (int i = 0; i < num_edges; i++) {
        auto a = get<0>(edge_list[i]);
        auto b = get<1>(edge_list[i]);
        if (a == b) {   
            continue;  
            graph.E--;
        }
        graph.N[a]++;
        graph.N[b]++;
    }
    int64_t t = 0;
    for (int j = 0; j <= graph.V; j++) {
        t += graph.N[j];
        graph.N[j] = t;
    }
    //assert((int64_t)(graph.N[graph.V]/2) == graph.E);

    for (int k = 0; k < num_edges; k++) {
        auto a = get<0>(edge_list[k]);
        auto b = get<1>(edge_list[k]);
        auto w =get<2>(edge_list[k]); 
        graph.F[--graph.N[a]] = b;
        graph.W[graph.N[a]] = w;
        graph.F[--graph.N[b]] = a;
        graph.W[graph.N[b]] = w;
    }
    /*for (int l = 0; l <= graph.V; l++) {
        qsort(graph.F + graph.N[l], (size_t)(graph.N[l+1]-graph.N[l]), sizeof* graph.F, cmpfunc);
    }
    */
    printf("V = %lld E = %lld\n"
    "N: ", graph.V, graph.E);
    for (int64_t a = 0; a <= graph.V; a++) {
        printf(" %lld", graph.N[a]);
    }
    printf("\n" "F: ");
    for (int64_t a = 0; a < graph.E; a++) {
        printf(" %lld", graph.F[a]);
    }
    printf("\n" "W: ");
    for (int64_t a = 0; a < graph.E; a++) {
        printf(" %d", graph.W[a]);
    }
    printf("\n"); 
    
} 

int main() {
    E test[] = { E(0, 2, 10), E(0, 3, 10), E(1, 0, 23), E(1, 3, 14), E(1, 5, 16),
         E(2, 0, 20), E(2, 5, 23), E(3, 1, 21), E(3, 4, 51), E(4, 1, 22), E(5, 0, 12), E(5, 2, 12) }; 
    build_graph(test, 6, 12);
    return 0;
}




