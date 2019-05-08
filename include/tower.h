#ifndef TOWER__
#define TOWER__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tower
{
  int puissance;
  int portee;
  int cadence;
  char *type;
  int cout;
  int posX;
  int posY;
  struct tower *nextTower; 
  
}Tower;

Tower* createTower(int x, int y, char *type);

#endif