//
//  main.c
//  analysis
//
//  Created by REAL CYH on 10/2/19.
//  Copyright © 2019 REAL CYH. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "prioQ.h"

#define INF 1.0/0

typedef struct Vertex {
    int index;
    double dist;
//    PrioQ * list;
    struct Vertex * preVertex;
} Vertex;


//PrioQ **adjList_create(char name[], int N, FILE *fpRead) {


//Vertex *graph_create(char name[], int N, FILE *fpRead) {
//    Vertex *A= malloc(N*sizeof(struct Vertex));
//    if (A == NULL) {
//        printf("Error: malloc failed in creating graph.\n");
//        return 0;
//    }
//
//    int nodeIndex, edgeIndex;
//    double edgeWeight;
//    int i;
//    for (i=0; i<N; i++) {
//        A[i].index = i;
//        // printf("%d ", A[i].index);
//        A[i].dist = INF;  // inf
//        A[i].preVertex = NULL;
//        A[i].list = PQ_create();
//    }
//    while (!feof(fpRead)) {
//        fscanf(fpRead, "%d %d %lf", &nodeIndex, &edgeIndex, &edgeWeight);
//        int isSucceed = 0;
//        isSucceed = PQ_insert(A[nodeIndex].list, edgeIndex, edgeWeight);
//        printf("%d %d %f\n", A[nodeIndex].index, edgeIndex, edgeWeight);
//        if (!isSucceed) {
//            printf("Adjacency list generating error.\n");
//            return 0;
//        }
//    }
//    fclose(fpRead);
//
//    return A;
//}

Vertex *dijkstra(PrioQ ** A, int N, int i) {
    Vertex * nodes =malloc((N+1)*sizeof(struct Vertex));
    PrioQ * PQ = PQ_create();
    bool visited[N];
    
    int j;
    int index = -1;
    for (j=0; j<N; j++) {
        nodes[j].index = j;
        nodes[j].dist = INF;
        nodes[j].preVertex = NULL;
        visited[j] = false;
    }
    nodes[i].dist = 0;
    PQ_insert(PQ, i, nodes[i].dist);
    //PQ_print(PQ);
    while (PQ_count(PQ)) {
        index = PQ_delete(PQ);
        PrioQ * p = A[index];
        //printf("delete:%d\n", index);
        visited[index] = true;
        while (p->next != NULL) {
            if (!visited[p->next->edgeIndex] && (nodes[index].dist+p->next->weight)<nodes[p->next->edgeIndex].dist ) {
                
                PQ_insert(PQ, p->next->edgeIndex, (nodes[index].dist+p->next->weight));
                //printf("%d: %f\n", p->next->edgeIndex, (path[index].dist+p->next->weight));
                nodes[p->next->edgeIndex].dist = (nodes[index].dist+p->next->weight);
                nodes[p->next->edgeIndex].preVertex = &nodes[index];
            }
            p = p->next;
        }
    }
    nodes[N].index = index;
    nodes[N].dist = nodes[index].dist;
    nodes[N].preVertex = &nodes[index];
    //printf("\nlast:%d %f", path[N].index, path[N].dist);

    return nodes;
}


int main(int argc, const char * argv[]) {
    char name[] = "topology";
    int N, i;
    int nodeIndex, edgeIndex;
    double edgeWeight;
    
    FILE *fpRead = fopen(name,"r");
    if (fpRead == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    fscanf(fpRead, "%d", &N);
//  create adjacency list
    PrioQ *A[N];
    for (i=0; i<N; i++) {
        A[i] = PQ_create();
    }
    while (!feof(fpRead)) {
        fscanf(fpRead, "%d %d %lf", &nodeIndex, &edgeIndex, &edgeWeight);
        int isSucceed = 0;
        isSucceed = PQ_insert(A[nodeIndex], edgeIndex, edgeWeight);
        //printf("%d %d %f\n", nodeIndex, edgeIndex, edgeWeight);
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
    
    Vertex *V[N];
    PrioQ *path[N];
    double maxDist[N];
    double diameter = 0;

    for (i=0; i<N; i++) {
        path[i] = PQ_create();
    }
    
    for (i=0; i<N; i++) {
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
    FILE *fpWrite = fopen("output", "w");
    
    printf("%f\n", diameter);
    fprintf(fpWrite, "%f\n", diameter);
    for (i=0; i<N; i++) {
        printf("%d %f ", i, maxDist[i]);
        fprintf(fpWrite, "%d %f ", i, maxDist[i]);
        PQ_print(path[i]);
        PQ_print_file(path[i], fpWrite);
    }
    
    for (i=0; i<N; i++) {
        PQ_free(path[i]);
        PQ_free(A[i]);
        free (V[i]);
    }
    return 0;
}
