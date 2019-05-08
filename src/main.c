#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>

#include "map.h"

int main()
{
    Map map;
    Image image; //l'image qu'on va parcourir
    map = loadMap("./data/carte.itd", &image);
    freeImage(&image);
    return 0;
}
