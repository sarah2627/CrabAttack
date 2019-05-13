#ifndef NODE__
#define NODE__

#include <stdlib.h>
#include <stdio.h>

/**
 * Chaque noeud portera une liste d'adjacence (indices des noeuds auxquels il est lié)
*/

typedef struct adjacentNode 
{
    int index;
    struct adjacentNode *next;
} AdjacentNode, *AdjacenceList;

typedef struct node
{
    int index;
    int type;
    float x;
    float y;
    struct node *next;
    AdjacenceList successors; 
}Node;


Node* createNode(int x, int y, int type, int index, Node** node);
void addSuccessors(int value, AdjacenceList *list);

#endif

