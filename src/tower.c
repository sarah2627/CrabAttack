#include "tower.h"

Tower* createTower(int x, int y, char *type)
{
    Tower * newTower = malloc(sizeof(Tower));

    if(newTower == NULL)
    {
        fprintf(stderr,"erreur allocation tour");
        exit(EXIT_FAILURE);
    }

    newTower->posX = x;
    newTower->posY = y;
    newTower->type = type;
    newTower->nextTower = NULL;

    if(strcmp(type, "ROCKET") == 0)
    {
        newTower->puissance = 12;
        newTower->cadence = 100;
        newTower->cout = 1000;
        newTower->portee = 200;
    }else 
        {
            if(strcmp(type, "LASER") == 0)
            {
                newTower->puissance = 12;
                newTower->cadence = 100;
                newTower->cout = 1000;
                newTower->portee = 200;
            }
            else
            {
                if(strcmp(type, "MITRAILLETTE") == 0)
                {
                    newTower->puissance = 12;
                    newTower->cadence = 100;
                    newTower->cout = 1000;
                    newTower->portee = 200;
                }
                else
                    {
                        if(strcmp(type, "HYBRIDE") == 0)
                        {
                            newTower->puissance = 12;
                            newTower->cadence = 100;
                            newTower->cout = 1000;
                            newTower->portee = 200;
                        }
                        else
                        {
                        fprintf(stderr,"pas de type de tour");
                        exit(EXIT_FAILURE);
                        }
                    }
                    
            }
                
        }
    return newTower;
    
}