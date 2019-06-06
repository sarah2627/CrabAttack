#include "grid.h"

tileType getColor(unsigned char r, unsigned char g, unsigned char b, Map map)
{
    // retourne le type en fonction de nos RGB données
    if(r == map.in.red && g == map.in.green && b == map.in.blue)
    {
        return in;
    }
    if(r == map.out.red && g == map.out.green && b == map.out.blue)
    {
        return out;
    }
     if(r == map.chemin.red && g == map.chemin.green && b == map.chemin.blue)
    {
        return chemin;
    }
    if(r == map.construct.red && g == map.construct.green && b == map.construct.blue)
    {
        return construct;
    }
     if(r == map.noeud.red && g == map.noeud.green && b == map.noeud.blue)
    {
        return noeud;
    }
     if(r == map.sea.red && g == map.sea.green && b == map.sea.blue)
    {
        return sea;
    }
    else 
    {
        return 0;
    }
}


void printType(tileType type)
{
    // affiche les types, utilisé lors des vérifications pour la construction de la carte
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
            // on reprend les données rgb de notre image d'après son tableau data
            unsigned char r = image.data[((i*image.width + j)*3)]; 
            unsigned char g = image.data[((i*image.width + j)*3)+1];
            unsigned char b = image.data[((i*image.width + j)*3)+2];
            // on cherche le type correspondant à la case
            newCase.type = getColor(r,g,b,map);
            newCase.x = positionX;
            newCase.y = positionY; 
            newCase.videTower = 0;
            newCase.videBat = 0;
            tabCase[positionX][positionY] = newCase;
            positionX++;
        }
        positionY++;
    }
    
}
