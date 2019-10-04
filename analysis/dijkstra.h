//
//  dijkstra.h
//  analysis
//
//  Created by REAL CYH on 10/4/19.
//  Copyright © 2019 REAL CYH. All rights reserved.
//

#ifndef dijkstra_h
#define dijkstra_h

#include <stdio.h>
#include <stdbool.h>
#include "prioQ.h"

#define INF 1.0/0

typedef struct Vertex { // store each node's information in dijkstra
    int index;
    double dist;
//    PrioQ * list;
    struct Vertex * preVertex;
} Vertex;

Vertex *dijkstra(PrioQ ** A, int N, int i) {
    Vertex * nodes =malloc((N+1)*sizeof(struct Vertex));
    // create a array of struct Vertex of size N+1
    // use the last one to store the largest distance and the last node in the path
    PrioQ * PQ = PQ_create();
    // create a priority queue in order to relax nodes
    bool visited[N];
    // use a bool array of size N to see if the node has already been visited
    // the index of the array equals to the index of each nodes
    
    int j;
    int index = -1;
    for (j=0; j<N; j++) { // initialize each node's index, weight/distance and predecessor
        nodes[j].index = j;
        nodes[j].dist = INF;
        nodes[j].preVertex = NULL;
        visited[j] = false; // marked all the nodes as not visited yet
    }
    nodes[i].dist = 0; // set the source node's distance to 0
    PQ_insert(PQ, i, nodes[i].dist); // insert the first node to the priority queue
    //PQ_print(PQ);
    while (PQ_count(PQ)) { // when the priority queue is not empty
        index = PQ_delete(PQ); // delete the first node of the priority queue
        PrioQ * p = A[index]; // find the adjacency list with source node's index as 'index'
        //printf("delete:%d\n", index);
        visited[index] = true; // set the deleted node as visited
        while (p->next != NULL) { // when the adjacency list with source index is not empty
            if (!visited[p->next->edgeIndex] && (nodes[index].dist+p->next->weight)<nodes[p->next->edgeIndex].dist ) {
                // dijkstra algorithm
                // relax(u,v)
                // if (u.d+w<v.d) set v.d = u.d+v, set v.p = u
                PQ_insert(PQ, p->next->edgeIndex, (nodes[index].dist+p->next->weight));
                // insert the node to the priority queue
                //printf("%d: %f\n", p->next->edgeIndex, (path[index].dist+p->next->weight));
                nodes[p->next->edgeIndex].dist = (nodes[index].dist+p->next->weight);
                // update distance
                nodes[p->next->edgeIndex].preVertex = &nodes[index];
                // update predecessor
            }
            p = p->next; // go through the whole list started with source index
        }
    }
    // set the last item of nodes to store max distance and the last node of the path
    nodes[N].index = index;
    nodes[N].dist = nodes[index].dist;
    nodes[N].preVertex = &nodes[index];
    //printf("\nlast:%d %f", path[N].index, path[N].dist);

    return nodes;
}

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

#endif /* dijkstra_h */
