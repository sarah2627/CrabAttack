#ifndef GRID__
#define GRID__

#include "map.h"
#include "tower.h"

typedef enum {
    in,
    out,
    chemin,
    construct,
    noeud,
    sea
}tileType;

typedef struct caseTab
{
    int x;
    int y;
    tileType type;
    int vide;
}Case;

tileType getColor(unsigned char r, unsigned char g, unsigned char b, Map map);
void printType(tileType type);
void createTableau(Image image, int w, int h, Map map, Case tabCase[w][h]);

#endif