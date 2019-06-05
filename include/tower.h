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



typedef enum{
	ROCKET, LASER, MITRAILLETTE, HYBRIDE
}TypeTower;

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

Tower* createTower(int index, float x, float y, TypeTower type, Tower ** list);
void constructTower(Tower** list);
TypeTower choixTower(int clickX, int clickY);
int countTower(TypeTower type);
Tower *getTower(int index, Tower *listTower);


#endif