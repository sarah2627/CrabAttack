#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>

#include "grid.h"
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

    int nbCaseW = image.width/30;
    int nbCaseH = image.height/30;
    Case tabCase[nbCaseW][nbCaseH];
    createTableau(image, nbCaseW, nbCaseH,map, tabCase);
 
    printType(tabCase[6][6].type);
    printf("trouvé\n");
    
    freeImage(&image);
    return 0;
}
