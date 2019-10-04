//
//  prioQ.h
//  analysis
//
//  Created by REAL CYH on 10/2/19.
//  Copyright © 2019 REAL CYH. All rights reserved.
//

#ifndef prioQ_h
#define prioQ_h
#include <stdio.h>
#include <stdlib.h>

typedef struct PrioQ{
    struct PrioQ *next;
    int edgeIndex;
    double weight;
//    double priority;
//    void *pData;
}PrioQ;

PrioQ *PQ_create() {
    void * ret;
    PrioQ *first;
    first = malloc(sizeof(PrioQ)); // allocate memory to the first node
    if (first == NULL) {  // If there is not enough resourse
        printf("Error: malloc failed in PQ_create.\n");
        ret = NULL;
    } else {
        first->next = NULL;
        ret = first;
    }
    return ret;
}

/* Insert a node to the priority queue according to a ascending order of key
 * Smallest key means highest priority
 * If there is no resourse or the operation failed, return 0
 * If the insertion succeed, return 1
 */
int PQ_insert(PrioQ *PQ, int index, double key) {
    int isSucceeded = 0;  // to tell if the insertion succeed
    PrioQ *new_node;
    new_node = malloc(sizeof(PrioQ));
    if (PQ == NULL) {
        printf("Error: cannot find PQ.\n");
    } else if (new_node == NULL) {
        printf("Error: malloc failed in PQ_insert.\n");
    } else {
        /*
         * Find the right position to insert the new node using key
         * Change the content of "next" pointer of the new node and the node before it
         */
        new_node->weight = key;
        new_node->edgeIndex = index;
        if (PQ->next == NULL) {
            PQ->next = new_node;  // first node
            new_node->next = NULL;
        } else {  // middle node
            PrioQ *p = PQ;  // a temporary pointer
            while (p->next) {
                if (key > p->next->weight) {
                    p = p->next;
                    continue;
                } else {
                    new_node->next = p->next;
                    p->next = new_node;
                    break;
                }
            }
            if (p->next == NULL) {  // last node
                p->next = new_node;
                new_node->next = NULL;
            }
        }
        isSucceeded = 1;
    }
    return isSucceeded;
}

/* Delete the node with highest priority
 * If the operation failed, return NULL
 * If the deletion succeed, return the pointer of data and wirte the priority value into key's address
 */
int PQ_delete(PrioQ *PQ) {
    int ret = -1;
    if (PQ == NULL) {
        printf("Error: cannot find PQ.\n");
    } else if (PQ->next == NULL) {
        printf("The priority queue is empty.\n");
    } else {
        /* Delete the first node of the priority queue
         * Revise the first pointer point to the second node
         */
        //*key = PQ->next->weight;
        int index = PQ->next->edgeIndex;
        PQ->next = PQ->next->next;
        ret = index;
    }
    return ret;
}

/* Count the number of nodes in the priority queue
 */
unsigned int PQ_count(PrioQ *PQ) {
    int cnt = 0;
    if (PQ==NULL) {
        printf("Error: cannot find PQ.\n");
    } else {
        PrioQ *p;
        for (p=PQ; p->next; p=p->next) {
            cnt++;
        }
    }
    return cnt;
}

/* Print all the priority values in ascending sequence without changing the contents of the priority queue
 */
void PQ_print(PrioQ *PQ) {
    if (PQ == NULL) {
        printf("Error: cannot find PQ.\n");
    } else if (PQ->next == NULL) {
        printf("The priority queue is empty.\n");
    } else {
        PrioQ *p;
        //printf("The priority of all the items(from high(smallest key) to low(largest key)):\n");
        for (p=PQ; p->next != NULL; p=p->next) {
//            printf("%d:%lf ", p->next->edgeIndex, p->next->weight);
            printf("%d ", p->next->edgeIndex);
        }
        printf("\n");
    }
}

void PQ_print_file(PrioQ *PQ, FILE *fpWrite) {
    if (!PQ ) {
        printf("Error: cannot find PQ.\n");
    } else if (!fpWrite) {
        printf("Error: cannot open file.\n");
    } else {
        PrioQ *p;
        for (p=PQ; p->next; p=p->next) {
            fprintf(fpWrite, "%d ", p->next->edgeIndex);
        }
        fprintf(fpWrite, "\n");
    }
}

/* Delete the whole queue and free the memory
 */
void PQ_free(struct PrioQ *PQ) {
    if (PQ == NULL) {
    } else if (PQ->next == NULL) {
        free(PQ);
    } else {
        while (PQ->next) {
            PrioQ *p = PQ->next;
            PQ->next = PQ->next->next;
            free(p);
        }
        free(PQ);
        free(PQ->next);
    }
    PQ = NULL;
}


#endif /* prioQ_h */
