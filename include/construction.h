#ifndef CONSTRUCTION_H__
#define CONSTRUCTION_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "tower.h"
#include "draw.h"

/// \Structure enum pour les types de construction 
typedef enum{
	RADAR, USINE, MUNITIONS
}TypeConstruction;

/// \Structure construction
typedef struct construction
{
	TypeConstruction type;
	int index;
    int portee;
    int cout;
    float posX;
    float posY;
    struct construction *nextConstruction; 
}Construction;

/// \brief créer une nouvelle construction
/// \param index : l'index de la construction
/// \param x et y : position de notre construction
/// \param type : le type de notre construction
/// \param list : la liste de nos constructions auquelle on va rajouter notre nouvelle construction
/// \return EXIT_FAILURE si problème sinon retourne notre nouvelle construction
Construction* createConstruction(int index, float x, float y, TypeConstruction type, Construction ** list);

/// \brief prend la texture en fonction du type
/// \param list : liste des constructions
void constructConstruction(Construction ** list);

/// \brief définit le type de notre construction en fonction de la position X et Y
/// \param clickX : la position X du click de la souris
/// \param clickY : la position Y du click de la souris
/// \return le type de notre construction 
TypeConstruction choixConstruction(int clickX, int clickY);

/// \brief cherche notre construction à partir d'un index dans notre liste
/// \param index : l'index de la construction qu'on cherche
/// \param listConstruction : la liste de nos constructions
/// \return un pointeur qui pointe sur une construction de notre liste 
Construction * getConstruction(int index, Construction * listConstruction);

/// \brief on vérifie si le batiment est à proximité d'une tour
/// \param batiment : le batiment qu'on vient de créer
/// \param listTower : la liste des tours 
void VerifBatiment(Construction *batiment, Tower *listTower);

/// \brief on vérifie si le batiment est à proximité d'une tour
/// \param batiment : le batiment qu'on vient de créer
/// \param listTower : la liste des tours 
void VerifTower(Construction * listbatiment, Tower *tour);

/// \brief cherche le cout d'une construction en fonction de son type
/// \param type : le type de notre construction 
/// \return le cout de la construction
int countConstruction(TypeConstruction type);


#endif