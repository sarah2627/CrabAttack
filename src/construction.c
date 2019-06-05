#include "construction.h"

//création d'un batiment
Construction* createConstruction(int index,float x, float y, TypeConstruction type, Construction ** list)
{
    Construction * newConstruction = malloc(sizeof(Construction));
    if(newConstruction == NULL)
    {
        fprintf(stderr,"erreur allocation construction");
        exit(EXIT_FAILURE);
    }
    newConstruction->index = index;
    newConstruction->posX = x;
    newConstruction->posY = y;
    newConstruction->type = type;
    newConstruction->nextConstruction = NULL;

    Construction *tmp = *list;
    if(tmp == NULL){
        *list = newConstruction;
    }
    else{
        while(tmp->nextConstruction != NULL){
            tmp = tmp->nextConstruction;
        }
        tmp->nextConstruction = newConstruction;
    }

    switch(type){
        case RADAR:
            newConstruction->portee = 15;
            newConstruction->cout = 500;
            break;
        case USINE:
            newConstruction->portee = 15;
            newConstruction->cout = 200;
            break;
        case MUNITIONS:
            newConstruction->portee = 15;
            newConstruction->cout = 400;
            break;

        default:
            break;
    }
   return newConstruction; 
}


//choix du batiment depuis le menu
TypeConstruction choixConstruction(int clickX, int clickY){
    TypeConstruction type;

    //choix radar
    if(clickX > 196 && clickX < 218 && clickY > 572 && clickY < 602){
        type = RADAR;
        printf("OK radar\n");
    }
    //choix usine
    else if(clickX > 239 && clickX < 263 && clickY > 572 && clickY < 602){
        type = USINE;
        printf("OK usine\n");
    }
    //choix munitions
    else if(clickX > 285 && clickX < 320 && clickY > 572 && clickY < 602){
        type = MUNITIONS;
        printf("OK munitions\n");
    }
    else{
        fprintf(stderr, "erreur lors du choix du type\n");
    }
    return type;
}

//construction du batiment
void constructConstruction(Construction** list){
    GLuint construction_texture;
    Construction *tmp = *list;
    if(tmp != NULL)
    {   
        switch(tmp->type){
            case RADAR:
                construction_texture = Texture_Load("./images/construction_radar.png", 31, 31);
                break;
            case USINE:
                construction_texture = Texture_Load("./images/construction_usine.png", 31, 31);
                break;
            case MUNITIONS:
                construction_texture = Texture_Load("./images/construction_munitions.png", 31, 31);
                break;
            default:
                break; 
        }
        float posY = 1 - (tmp->posY);
        drawMap(construction_texture, tmp->posX, posY , 0.05, 0.05);
        tmp = tmp->nextConstruction;
    }
    //printf("construct construction ok\n");
}

int countConstruction(TypeConstruction type){
    int cout;
    if(type == RADAR)
    {
       cout = 500; 
    }
    if(type == USINE)
    {
       cout = 200; 
    }
    if(type == MUNITIONS)
    {
       cout = 400; 
    }
    return cout;
}

Construction * getConstruction(int index, Construction * listConstruction){
    if(listConstruction == NULL){
        fprintf(stderr, "erreur liste nulle\n");
        return NULL;
    }
    else{
        Construction *actuel = listConstruction;
        while(actuel != NULL){
            if(actuel->index == index)
            {
                return actuel;
            }
            actuel = actuel->nextConstruction;
        }
        return NULL;
    }
}