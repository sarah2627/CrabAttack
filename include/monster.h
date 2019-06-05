#ifndef MONSTER_H__
#define MONSTER_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "map.h"
typedef enum{
	ROUGE, BLEU, MASSACREUR
}TypeMonster;

typedef struct monster
{
	TypeMonster type;
	int indexMonster;
	int indexBegin;
	int pdv;
	int pdvMax;
	int gain;
	int resistance;
	float vitesse;
	Node* direction;
	float X;
	float Y;
	struct monster *next;	
}Monster;

Monster* createMonster(int nbvague,int index, int begin, TypeMonster type, Node* direction, float X, float Y, Monster** list);
void constructMonster(Monster ** list);
TypeMonster chooseMonster(int vague);
Monster *getMonster(int index, Monster *listMonster);
Monster * deleteMonster(Monster *monstre, Monster *listMonster);

#endif