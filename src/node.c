#include "node.h"

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
	node->successors = malloc(sizeof(AdjacenceList));
	return node;
}

AdjacenceList findLast(AdjacenceList list)
{
    if(list)
    {
        while (list !=NULL)
         {
            list = list->next;
         }
            return list;
    }
    else
    {
        exit(1);
    }
}

void addSuccessors(int value, AdjacenceList list)
{
    printf("hello\n");
    AdjacentNode* new = malloc(sizeof(AdjacentNode));
    printf("cool");
    if(!new)
    {
        exit(EXIT_FAILURE);
    }
    new->index = value;
    new->next = 0;
    findLast(list)->next = new;

}