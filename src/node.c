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

AdjacentNode *findLast(AdjacenceList list)
{
    if(list)
    {
        while (list->next != NULL)
        {
            list = list->next;
            printf("%p", list);
        }
        return list;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
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

    AdjacentNode *tmp = list;
    printf("%p\n", tmp);
    printf("%p\n", tmp->next);
    tmp = tmp->next;
    printf("%p\n", tmp);
    printf("%p\n", tmp->next);
tmp = tmp->next;
    printf("%p\n", tmp);
    printf("%p\n", tmp->next);
    printf("%p\n", tmp->next->next);


    /*if (tmp) {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        //list->next = new;
    }*/

}