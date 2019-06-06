#include "node.h"
#define MAX_TAILLE 20

// création d'un noeud
Node* createNode(int x, int y, int type, int index, Node** lstnode) {
	Node* node = (Node*)malloc(sizeof(Node));
	if(node == NULL) {
		fprintf(stderr, "Node non alloué");
        exit(1);
	}
    node->index = index;
    node->type = type;
	node->x = x;
	node->y = y;
    node->next = NULL;
	node->successors = (AdjacenceList)malloc(MAX_TAILLE*sizeof(AdjacentNode));
    (*node).successors= NULL;
    
    Node * tmp = *lstnode;
    if(tmp==NULL)
    {
        *lstnode = node;
    }
    else
    {
         while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = node;
    }

	return node;
}


// ajout liste successeur
void addSuccessors(int value, AdjacenceList *list)
{
 
    AdjacentNode* new = (AdjacentNode *)malloc(sizeof(AdjacentNode));

    if(!new) {
        exit(EXIT_FAILURE);
    }
    new->index = value;
    new->next = NULL;

    AdjacentNode *temp = *list;
   
    if (temp==NULL) 
    { 
        *list = new;
    }
    else{
        while (temp->next != NULL) {
  
            temp = temp->next;
       
        }

        temp->next = new;
    }

}

