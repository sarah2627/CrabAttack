#ifndef TOWER__
#define TOWER__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "draw.h"


/// \Structure enum pour les types de tower
typedef enum{
	ROCKET, LASER, MITRAILLETTE, HYBRIDE
}TypeTower;

/// \Structure tower
typedef struct tower
{
	TypeTower type;
	int index;
    int puissance;
    int portee;
    int cadence;
    int cout;
    float posX;
    float posY;
    struct tower *nextTower; 
  
}Tower;

/// \brief créer une nouvelle tour
/// \param index : l'index de la tour
/// \param x et y : position de notre tour
/// \param type : le type de notre tour
/// \param list : la liste de nos tours auquelle on va rajouter notre nouvelle tour
/// \return EXIT_FAILURE si problème sinon retourne notre nouvelle tour
Tower* createTower(int index, float x, float y, TypeTower type, Tower ** list);

/// \brief prend la texture en fonction du type
/// \param list : liste des tours
void constructTower(Tower** list);

/// \brief définit le type de notre tour en fonction de la position X et Y
/// \param clickX : la position X du click de la souris
/// \param clickY : la position Y du click de la souris
/// \return le type de notre tour
TypeTower choixTower(int clickX, int clickY);

/// \brief cherche le cout d'une tour en fonction de son type
/// \param type : le type de notre tour
/// \return le cout de la tour
int countTower(TypeTower type);

/// \brief cherche notre tour à partir d'un index dans notre liste
/// \param index : l'index de la tour qu'on cherche
/// \param listTower : la liste de nos tours
/// \return un pointeur qui pointe sur une tour de notre liste 
Tower *getTower(int index, Tower *listTower);

/// \brief on supprime une tour de notre liste
/// \param tower : la tour qu'on veut supprimer
/// \param listTower : la liste de nos tours
/// \return notre nouvelle liste de tours 
Tower * deleteTower(Tower *tower, Tower *listTower);


#endif