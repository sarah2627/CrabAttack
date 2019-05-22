#include "tower.h"

//création d'une tour

Tower* createTower(float x, float y, TypeTower type)
{
    Tower * newTower = malloc(sizeof(Tower));
    printf("Tour 3\n");
    if(newTower == NULL)
    {
        fprintf(stderr,"erreur allocation tour");
        exit(EXIT_FAILURE);
    }

    newTower->posX = x;
    newTower->posY = y;
    newTower->type = type;
    newTower->nextTower = NULL;

    switch(type){
        case ROCKET:
            newTower->puissance = 12;
            newTower->cadence= 100;
            newTower->cout = 1000;
            newTower->portee = 200;
            break;
        case LASER:
            newTower->puissance = 12;
            newTower->cadence= 100;
            newTower->cout = 1000;
            newTower->portee = 200;
            break;
        case MITRAILLETTE:
            newTower->puissance = 12;
            newTower->cadence= 100;
            newTower->cout = 1000;
            newTower->portee = 200;
            break;
        case HYBRIDE:
            newTower->puissance = 12;
            newTower->cadence= 100;
            newTower->cout = 1000;
            newTower->portee = 200;
            break;

        default:
            break;
    }
    printf("Tour créé yeaaaaaah\n");
   return newTower; 
}


//choix de la tour depuis le menu
TypeTower choixTower(int clickX, int clickY){
    TypeTower type;

    //choix rocket
    if(clickX > 441 && clickX < 479 && clickY > 752 && clickY < 789){
        type = ROCKET;
        printf("OK rocket\n");
    }
    //choix laser
    else if(clickX > 521 && clickX < 560 && clickY > 752 && clickY < 789){
        type = LASER;
        printf("OK laser\n");
    }
    //choix mitraillette
    else if(clickX > 600 && clickX < 638 && clickY > 752 && clickY < 789){
        type = MITRAILLETTE;
        printf("OK mitraillette\n");
    }
    //choix 
    else if(clickX > 680 && clickX < 720 && clickY > 752 && clickY < 789){
        type = HYBRIDE;
        printf("OK hybride\n");
    }
    else{
        fprintf(stderr, "erreur lors du choix du type\n");
    }
    return type;
}

//construction de la tour

void constructTower(Tower* use){
    GLuint tower_texture;
    //Tower* use = tower;

    if(use != NULL){
        switch(use->type){
            case ROCKET:
                tower_texture = Texture_Load("./images/tower_rocket.png", 31, 31);
                break;
            case LASER:
                tower_texture = Texture_Load("./images/tower_laser.png", 31, 31);
                break;
            case MITRAILLETTE:
                tower_texture = Texture_Load("./images/tower_mitraillette.png", 31, 31);
                break;
            case HYBRIDE:
                tower_texture = Texture_Load("./images/tower_rocket.png", 31, 31);
                break;
            default:
                break;
        }
    }

    float posY = 1 - (use->posY);
    //printf("%f\n", posY);
    drawMap(tower_texture, use->posX, posY , 0.05, 0.05);

    use = use->nextTower;

}
