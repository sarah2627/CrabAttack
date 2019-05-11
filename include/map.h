#ifndef MAP__
#define MAP__

#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

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
    Node *listenode;
    Color chemin;
    Color noeud;
    Color construct;
    Color in;
    Color out;
 } Map;
 

 Map loadMap(char *filename, Image *image);
 int readMap(FILE * fichierITD, Map * map, Image *image);
 Color newColor(float r, float g, float b);
 
#endif