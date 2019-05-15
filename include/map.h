#ifndef MAP__
#define MAP__

#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "node.h"
#include "image.h"

#define TAILLE_MAX 50

 typedef struct color
{
    unsigned char red;
    unsigned char blue;
    unsigned char green;
} Color;


 typedef struct map
 {
    char *carte; // image ppm
    int nbNode;
    Node *listenode; // Node* listenode = malloc(sizeof(Node));
    Color chemin;
    Color noeud;
    Color construct;
    Color in;
    Color out;
    Color sea;
 } Map;
 


 Map loadMap(char *filename, Image *image);
 int readMap(FILE * fichierITD, Map * map, Image *image);
 void printMapNode(Map map);
 Node * getNode(int index, Map map);
 Color newColor(float r, float g, float b);

 
#endif