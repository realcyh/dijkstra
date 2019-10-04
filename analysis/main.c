//
//  main.c
//  analysis
//
//  Created by REAL CYH on 10/2/19.
//  Copyright © 2019 REAL CYH. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "prioQ.h"
#include "dijkstra.h"


int main(int argc, const char * argv[]) {
    char name[] = "topology100";   //topology
    char output[] = "output_100"; //output
    int N, i;
    int nodeIndex, edgeIndex;
    double edgeWeight;
    clock_t start, finish;
    double time;
    
    FILE *fpRead = fopen(name,"r");
    if (fpRead == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    fscanf(fpRead, "%d", &N);
    // create adjacency list to represent the graph
    // each A[i] points to a priority queue represents all the nodes
    // connected to node i with edge weight
    PrioQ *A[N];
    for (i=0; i<N; i++) {
        A[i] = PQ_create();
    }
    while (!feof(fpRead)) {
        fscanf(fpRead, "%d %d %lf", &nodeIndex, &edgeIndex, &edgeWeight);
        int isSucceed = 0;
        isSucceed = PQ_insert(A[nodeIndex], edgeIndex, edgeWeight);
        //printf("%d %d %f\n", nodeIndex, edgeIndex, edgeWeight);
        //PQ_print(A[nodeIndex]);
        if (!isSucceed) {
            printf("Adjacency list generating error.\n");
            return 0;
        }
    }
    fclose(fpRead);
//  adjacency list created

//    Vertex *A;
//    A = graph_create(name, N, fpRead);
        
//    Vertex *v;
//    v = dijkstra(A, N, 2);
//    printf("\nlast:%d %f", v[N].index, v[N].dist);
//    Vertex *p;
//    p = v[N].preVertex;
//    while (p != NULL) {
//        printf("%d ", p->index);
//        p = p->preVertex;
//    }
    start = clock();
    Vertex *V[N];
    PrioQ *path[N];
    double maxDist[N];
    double diameter = 0;

    for (i=0; i<N; i++) {
        path[i] = PQ_create();
    }
    
    for (i=0; i<N; i++) { // call dijkstra for N times
        V[i] = dijkstra(A, N, i);
        Vertex *q;
        q = V[i][N].preVertex;
        maxDist[i] = V[i][N].dist;
        if (diameter<maxDist[i]) {
            diameter = maxDist[i];
        }
        while (q) {
            PQ_insert(path[i], q->index, q->dist);
            //printf("%d", q->index);
            q = q->preVertex;
        }
    }
    finish = clock();
    time = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f seconds\n", time);
    
    FILE *fpWrite = fopen(output, "w");
    printf("%f\n", diameter);
    fprintf(fpWrite, "%f\n", diameter);
    for (i=0; i<N; i++) {
        //printf("%d %f ", i, maxDist[i]);
        fprintf(fpWrite, "%d %f ", i, maxDist[i]);
        //PQ_print(path[i]);
        PQ_print_file(path[i], fpWrite);
    }
    fclose(fpWrite);
    // release memory
    for (i=0; i<N; i++) {
        PQ_free(path[i]);
        PQ_free(A[i]);
        free (V[i]);
    }
    return 0;
}
