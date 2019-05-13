#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>

#include "map.h"

int main()
{
    Map map;
    Image image; //l'image qu'on va parcourir
    map = loadMap("./data/map_day.itd", &image);
    char file[30] = "images/";
    strcat(file, map.carte);
    printf("file = %s", file);
    printf("afficher chemin : %s", map.carte);
    printMapNode(map);
    int index = 3;
    Node * node = getNode(index, map);
    
    freeImage(&image);
    return 0;
}
