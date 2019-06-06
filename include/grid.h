#ifndef GRID__
#define GRID__

#include "map.h"

/// \Structure enum pour les types de case
typedef enum {
    in,
    out,
    chemin,
    construct,
    noeud,
    sea
}tileType;

/// \ Structure case
typedef struct caseTab
{
    int x;
    int y;
    tileType type;
    int videTower;
    int videBat;

}Case;


/// \brief cherche le type de la case en fonction de RGB
/// \param r,g,b : le RGB
/// \param map : la structure de notre carte
/// \return le type de notre case
tileType getColor(unsigned char r, unsigned char g, unsigned char b, Map map);

/// \brief fonction créée lors des vérifications, affiche le type donné
/// \param type : le type de notre case
void printType(tileType type);

/// \brief on rempli un tableau à deux dimensins à partir de notre image
/// \param image: l'image qu'on lit
/// \param w,h : la hauteur et largeur de notre image
/// \param map : notre structure map
/// \param tabCase : notre tableau qu'on va remplir
void createTableau(Image image, int w, int h, Map map, Case tabCase[w][h]);

#endif