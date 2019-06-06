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

/// \Structure enum pour les types de monstres
typedef enum{
	ROUGE, BLEU, MASSACREUR
}TypeMonster;

/// \Structure monstre
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

/// \brief créer un nouveau monstre
/// \param nbvague : la vague où l'on se trouve
/// \param index : l'index de notre monstre
/// \param begin : l'index de début de la position de notre monstre
/// \param type : le type de notre monstre
/// \param direction : le noeud où doit aller notre monstre
/// \param X et Y : la position de notre monstre
/// \param list : la liste de nos monstres auquelle on va rajouter notre nouveau monstre
/// \return EXIT_FAILURE si problème sinon retourne notre nouveau monstre
Monster* createMonster(int nbvague,int index, int begin, TypeMonster type, Node* direction, float X, float Y, Monster** list);

/// \brief prend la texture en fonction du type
/// \param list : liste des monstres
void constructMonster(Monster ** list);

/// \brief on choisit le type en fonction de la vague
/// \param vague : la vague où l'on se trouve
/// \return le type de monstre de notre vague
TypeMonster chooseMonster(int vague);

/// \brief cherche notre monstre à partir d'un index dans notre liste
/// \param index : l'index du monstre qu'on cherche
/// \param listMonster : la liste de nos monstres
/// \return un pointeur qui pointe sur un monstre de notre liste 
Monster *getMonster(int index, Monster *listMonster);

/// \brief on supprime un mosntre de notre liste
/// \param monstre : le monstre que l'on veut supprimer
/// \param listMonster : la liste de nos monstres
/// \return notre nouvelle liste de monstres
Monster * deleteMonster(Monster *monstre, Monster *listMonster);

#endif