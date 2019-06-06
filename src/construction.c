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
            newConstruction->portee = 100;
            newConstruction->cout = 500;
            break;
        case USINE:
            newConstruction->portee = 100;
            newConstruction->cout = 200;
            break;
        case MUNITIONS:
            newConstruction->portee = 100;
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
    }
    //choix usine
    else if(clickX > 239 && clickX < 263 && clickY > 572 && clickY < 602){
        type = USINE;
    }
    //choix munitions
    else if(clickX > 285 && clickX < 320 && clickY > 572 && clickY < 602){
        type = MUNITIONS;
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
    while(tmp != NULL)
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
        float posY = 1 - (tmp->posY/630.0);
        float posX = tmp->posX/630.0;
        drawMap(construction_texture, posX, posY , 0.05, 0.05);
        tmp = tmp->nextConstruction;
    }
}

// connaitre le cout de la construction en fonction d'un type 
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

// on cherche un batiment
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


// on vérifie si le batiment est à coté d'une tour
void VerifBatiment(Construction * batiment, Tower *listTower)
{

    Construction * verifBat = batiment;   
    Tower * verifTower = listTower;
        while (verifTower != NULL)
        {
            double A = 0;
            double B = 0;
            double H2 = 0;
            double H = 0; 
            double result = 0;
            if(verifBat->posX >= verifTower->posX){
                A = verifBat->posX - verifTower->posX;
            }
            if(verifBat->posX < verifTower->posX){
                A = verifTower->posX - verifBat->posX;
            }
            if(verifBat->posY >= verifTower->posY){
                B = verifBat->posY - verifTower->posY;
            }
            if(verifBat->posY < verifTower->posY){
                B = verifTower->posY - verifBat->posY;
            }
            // on calcule la distance entre le batiment et la tour
            H2 = pow(A,2) + pow(B,2);
            H=sqrt(H2);
            // si la tour est dans la portée du batiment
            if(H <= verifBat->portee)
            {
                if(verifBat->type == RADAR)
                {
                    // on augmente la porte de 25%
                    result = (verifTower->portee*25)/100; 
                    verifTower->portee += result; 
                    
                }
                if(verifBat->type == USINE)
                {
                    // on augmente la puissance de 25%
                    result = (verifTower->puissance*25)/100; 
                    verifTower->puissance += result; 
          
                }
                if(verifBat->type == MUNITIONS)
                {
                    // on augmente la cadence de 25%
                    result = (verifTower->cadence*25)/100;
                    verifTower->cadence += result; 
              
                }
                
            }
            verifTower = verifTower->nextTower;
        }

}


// on vérifie si la tour est à coté d'un batiment
void VerifTower(Construction * listbatiment, Tower *tour)
{

    Construction * verifBat = listbatiment;   
    Tower * verifTower = tour;
        while (verifBat != NULL)
        {
            double A = 0;
            double B = 0;
            double H2 = 0;
            double H = 0; 
            double result = 0;
            if(verifBat->posX >= verifTower->posX){
                A = verifBat->posX - verifTower->posX;
            }
            if(verifBat->posX < verifTower->posX){
                A = verifTower->posX - verifBat->posX;
            }
            if(verifBat->posY >= verifTower->posY){
                B = verifBat->posY - verifTower->posY;
            }
            if(verifBat->posY < verifTower->posY){
                B = verifTower->posY - verifBat->posY;
            }
            // on calcule la distance entre le batiment et la tour
            H2 = pow(A,2) + pow(B,2);
            H=sqrt(H2);
            // si la tour est dans la portée du batiment
            if(H <= verifBat->portee)
            {
                if(verifBat->type == RADAR)
                {
                    // on augmente la porte de 25%
                    result = (verifTower->portee*25)/100; 
                    verifTower->portee += result; 
                   
                }
                if(verifBat->type == USINE)
                {
                    // on augmente la puissance de 25%
                    result = (verifTower->puissance*25)/100; 
                    verifTower->puissance += result; 
                 
                }
                if(verifBat->type == MUNITIONS)
                {
                    // on augmente la cadence de 25%
                    result = (verifTower->cadence*25)/100;
                    verifTower->cadence += result; 
                   
                }
                
            }
            verifBat = verifBat->nextConstruction;
        }

}