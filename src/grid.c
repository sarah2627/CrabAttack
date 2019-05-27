#include "grid.h"

tileType getColor(unsigned char r, unsigned char g, unsigned char b, Map map)
{
    if(r == map.in.red && g == map.in.green && b == map.in.blue)
    {
        printf("type in\n");
        return in;
    }
    if(r == map.out.red && g == map.out.green && b == map.out.blue)
    {
        printf("type out\n");
        return out;
    }
     if(r == map.chemin.red && g == map.chemin.green && b == map.chemin.blue)
    {
        printf("type chemin\n");
        return chemin;
    }
    if(r == map.construct.red && g == map.construct.green && b == map.construct.blue)
    {
        printf("type construct\n");
        return construct;
    }
     if(r == map.noeud.red && g == map.noeud.green && b == map.noeud.blue)
    {
        printf("type noeud\n");
        return noeud;
    }
     if(r == map.sea.red && g == map.sea.green && b == map.sea.blue)
    {
        printf("type sea\n");
        return sea;
    }
    else 
    {
        return 0;
    }
}


void printType(tileType type)
{
    switch (type)
    {
    case in :
        printf("in");
        break;
    case out :
        printf("out");
        break;
    case chemin :
        printf("chemin");
        break;
    case construct :
        printf("construct");
        break;
    case noeud :
        printf("noeud");
        break;
    case sea :
        printf("sea");
        break;
    default:
        break;
    }
}

void createTableau(Image image, int w, int h, Map map, Case tabCase[w][h])
{
    int positionY=0;
    for(int i=15; i<image.height; i+=30)
    {
        int positionX = 0;
        for(int j=15; j<image.width; j+=30)
        {
            Case newCase;
            unsigned char r = image.data[((i*image.width + j)*3)];
            unsigned char g = image.data[((i*image.width + j)*3)+1];
            unsigned char b = image.data[((i*image.width + j)*3)+2];
            newCase.type = getColor(r,g,b,map);
            newCase.vide = 0;
            newCase.x = positionX;
            newCase.y = positionY; 
            tabCase[positionX][positionY] = newCase;
            positionX++;
        }
        positionY++;
    }
    printf("fini\n");
    
}
