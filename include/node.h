#ifndef NODE__
#define NODE__

#include <stdlib.h>
#include <stdio.h>

/**
 * Chaque noeud portera une liste d'adjacence (indices des noeuds auxquels il est lié)
*/

/// \Structure adjacentNode
typedef struct adjacentNode 
{
    int index;
    struct adjacentNode *next;
} AdjacentNode, *AdjacenceList;

/// \Structure node
typedef struct node
{
    int index;
    int type;
    float x;
    float y;
    struct node *next;
    AdjacenceList successors; 
}Node;

/// \brief créer un nouveau noeud
/// \param x,y : la position de notre noeud
/// \param index : l'index de notre noeud
/// \param type : le type de notre noeud
/// \param node : notre liste de noeuds
/// \return EXIT_FAILURE si problème sinon retourne notre nouveau noeud
Node* createNode(int x, int y, int type, int index, Node** node);

/// \brief ajoute un successeur à ma liste
/// \param value : index du noeud successeur
/// \param list : la liste des successeurs
void addSuccessors(int value, AdjacenceList *list);

#endif

