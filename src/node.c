#include "node.h"
#define MAX_TAILLE 20


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



void addSuccessors(int value, AdjacenceList *list)
{
    //printf("hello\n");
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
            //printf("yo\n");
   
            temp = temp->next;
           
            //printf("momo\n");
        }
   
        //printf("alors?\n");
        temp->next = new;
    }

}

