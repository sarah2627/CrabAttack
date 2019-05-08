#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>

#include "map.h"

int main()
{
    Map map;
    map = loadMap("./data/carte.itd");
    printf("chat");

    return 0;
}
