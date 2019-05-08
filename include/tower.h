#ifndef TOWER__
#define TOWER__

typedef struct tower
{
  int puissance;
  int portée;
  int cadence;
  char type;
  int cout;
  int posX;
  int posY;
  struct tower *nextTower; 
  
}Tower;

#endif