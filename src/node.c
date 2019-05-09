#include "node.h"
#define MAX_TAILLE 20


Node* createNode(int x, int y, int type, int index) {
	Node* node = (Node*)malloc(sizeof(Node));
	if(node == NULL) {
		fprintf(stderr, "Node non alloué");
        exit(1);
	}
    node->index = index;
    node->type = type;
	node->x = x;
	node->y = y;
	node->successors = (AdjacenceList)malloc(MAX_TAILLE*sizeof(AdjacentNode));
    (*node).successors= NULL;
	return node;
}



void addSuccessors(int value, AdjacenceList list)
{
    printf("hello\n");
    AdjacentNode* new = (AdjacentNode *)malloc(sizeof(AdjacentNode));
    printf("cool");

    if(!new) {
        exit(EXIT_FAILURE);
    }

    new->index = value;
    new->next = NULL;

    AdjacentNode *temp = list;
    //temp = list;
   
   
    if (temp==NULL) 
    { 
        temp = new;
    }
    else{
        while (temp->next != NULL) {
            printf("yo\n");
            printf("%p\n", temp);
            temp = temp->next;
            printf("%p\n", temp);
            printf("momo\n");
        }
   
        printf("alors?\n");
        temp->next = new;
    }

}