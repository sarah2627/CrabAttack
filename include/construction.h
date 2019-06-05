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


typedef enum{
	RADAR, USINE, MUNITIONS
}TypeConstruction;

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

Construction* createConstruction(int index, float x, float y, TypeConstruction type, Construction ** list);
void constructConstruction(Construction ** list);
TypeConstruction choixConstruction(int clickX, int clickY);
Construction * getConstruction(int index, Construction * listConstruction);
void VerifBatiment(Construction *batiment, Tower *listTower);
void VerifTower(Construction * listbatiment, Tower *tour);


#endif