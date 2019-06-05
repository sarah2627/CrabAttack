#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>

#include "grid.h"
#include "map.h"
#include "draw.h"
#include "tower.h"
#include "monster.h"
#include "construction.h"
#include "jeu.h"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 630;
static const unsigned int WINDOW_HEIGHT = 630;
static const char WINDOW_TITLE[] = "Imac Towards Defends";

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main()
{
    //initialisation du jeu
    Jeu* jeu;
    jeu = (Jeu*)malloc(sizeof(Jeu));
    jeu->start= 0;
    jeu->aide= 0;
    jeu->perdu= 0;
    jeu->gagne= 0;
    jeu->pause= 0;
    jeu->regle= 0;

    Map map;
    Image image; //l'image qu'on va parcourir
    map = loadMap("./data/map_day.itd", &image);
    char file[30] = "images/";
    strcat(file, map.carte);
    //printMapNode(map);
    int chemin[map.nbNode];

    Node *final = getNode(1, map);
    
    //creer mon tableau, une grille de mon image
    int nbCaseW = image.width/30;
    int nbCaseH = image.height/30;
    Case tabCase[nbCaseW][nbCaseH];
    createTableau(image, nbCaseW, nbCaseH,map, tabCase);

    ///////// Partie SDL ////////////
    GLuint texture_map;

    int chgtTexture = 0;

    //variable informations tours
    int nbinfo_tower_rocket = 0;
    int nbinfo_tower_laser = 0;
    int nbinfo_tower_mitraillette = 0;
    int nbinfo_tower_hybride = 0;
    int info_tower_rocket = 0;
    int info_tower_laser = 0;
    int info_tower_mitraillette = 0;
    int info_tower_hybride = 0;

    //variable informations batiments
    int nbinfo_construction_radar = 0;
    int nbinfo_construction_usine = 0;
    int nbinfo_construction_munitions = 0;
    int info_construction_radar = 0;
    int info_construction_usine = 0;
    int info_construction_munitions = 0;

    //variable pour le guide du jeu
    int guide_du_jeu = 0;

    //Argent
    int argent = 1000;
    //chaine de caractere qui stocke l'argent convertit en chaine de caracteres
    char *noix_de_coco = " PAS ASSEZ DE NOIX DE COCO";
    char char_argent[10];
    char argent_restant[10];

    TypeTower towertype = -1;
    TypeConstruction constructiontype = -1;
    int indexTower = 1;

    //Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }

    //Initialisation GLUT = necessaire ??
    char *myargv[1];
    int myargc = 1;
    myargv[0] = strdup("test");
    glutInit(&myargc, myargv);

    //Ouverture d'une fenetre et creation d'un contexte OpenGL 
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Initialisation du titre de la fenetre
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    char carte[] = "./images/map_day.png";
    texture_map = Texture_Load(carte, 630, 630);

    //Menu du départ
    GLuint texture_begin = Texture_Load("./images/texture_fond.png", 630, 630);
    GLuint texture_bouton_lancer = Texture_Load("./images/bouton_lancer_partie.png", 630, 630);
    GLuint texture_bouton_guide = Texture_Load("./images/bouton_guide_du_jeu.png", 630, 630);

    //Guide du jeu
    GLuint texture_fond_guide = Texture_Load("./images/guide_du_jeu_fond.png", 630, 630);
    GLuint texture_guide = Texture_Load("./images/guide_du_jeu_parchemin.png", 630, 630);
    GLuint texture_bouton_quitter = Texture_Load("./images/bouton_quitter.png", 31, 31);
    GLuint texture_guide_du_jeu = Texture_Load("./images/guide_du_jeu.png", 630, 630);

    //Chargement de la texture du menu de jeu
    GLuint texture_menu = Texture_Load("./images/menu_jeu.png", 630, 630);

    //Chargement de la texture quand le joueur perd
    GLuint texture_win = Texture_Load("./images/win.png", 631, 630);

    //Chargement de la texture quand le joueur gagne
    GLuint texture_gameover = Texture_Load("./images/game_over.png", 631, 630);

    //Chargement de la texture des infos des tours
    GLuint texture_info_rocket = Texture_Load("./images/infos_rocket_prix.png", 151, 111);
    GLuint texture_info_laser = Texture_Load("./images/infos_laser_prix.png", 151, 111);
    GLuint texture_info_mitraillette = Texture_Load("./images/infos_mitraillette_prix.png", 151, 111);
    GLuint texture_info_hybride = Texture_Load("./images/infos_hybride_prix.png", 151, 111);

    //Chargement de la texture des infos des tours sur la carte
    GLuint texture_info_rocket_map = Texture_Load("./images/infos_rocket.png", 151, 101);
    GLuint texture_info_laser_map = Texture_Load("./images/infos_laser.png", 151, 101);
    GLuint texture_info_mitraillette_map = Texture_Load("./images/infos_mitraillette.png", 151, 101);
    GLuint texture_info_hybride_map = Texture_Load("./images/infos_hybride.png", 151, 101);

    //Chargement de la texture des infos des batiments
    GLuint texture_info_radar = Texture_Load("./images/infos_radar_prix.png", 151, 111);
    GLuint texture_info_usine = Texture_Load("./images/infos_usine_prix.png", 151, 111);
    GLuint texture_info_munitions = Texture_Load("./images/infos_munitions_prix.png", 151, 111);

    //Chargement de la texture des infos des batiments sur la carte
    GLuint texture_info_radar_map = Texture_Load("./images/infos_radar.png", 151, 101);
    GLuint texture_info_usine_map = Texture_Load("./images/infos_usine.png", 151, 101);
    GLuint texture_info_munitions_map = Texture_Load("./images/infos_munitions.png", 151, 101);

    int positionX = 0;
    int positionY = 0;
    int positionRX = 0;
    int positionRY = 0;

    //Create Tower
    Tower *listTower = NULL;
    Tower *newTower = NULL;
    int posTower = 0;
    int positionTowerX = 0;
    int positionTowerY = 0;

    //Create Construction
    Construction *listConstruction = NULL;
    Construction *newConstruction = NULL;
    int posConstruction = 0;
    int positionConstructionX = 0;
    int positionConstructionY = 0;
    int indexBat = 1;

    cheminDijkstra(map, chemin);
    printf("hellooooooooooooooooo\n");
    printf("tableau 2 = %d\n", chemin[2]);

    //Create Monster
    Monster *listMonster = NULL;
    int indexBegin =0;
    int beginMonster = 0;
    for(int i = 0; i<map.nbNode; i++)
    {
        if(chemin[i] == 0)
        {
            beginMonster = i;
        }
    }
    indexBegin = beginMonster;
    printf("begin index %d\n", indexBegin);
    /*
    Node * begin = getNode(chemin[indexBegin], map);
    Monster *firstmonster = NULL;
    int indexDirection = indexBegin - 1;
    Node * direction = getNode(chemin[indexDirection], map);
    */
    Monster *firstmonster = NULL;
    int indexMonster = 1;
    TypeMonster monsterType;
    Node * begin = getNode(chemin[indexBegin], map);
    int indexDirection = indexBegin - 1;
    Node * direction = getNode(chemin[indexDirection], map);
    //printf("position begin %f %f\n", begin->x, begin->y );
    //printf("position direction %f %f\n", direction->x, direction->y );

    int movMonster = 0;
    int nbvagues = 1;
    int nbMonster = 0;
    int times = 0;

    /* Boucle principale */
    int loop = 1;

      while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        if (chgtTexture == 0)
        {
            drawMap(texture_begin, 0.5, 0.5, 1, 1);
            drawMap(texture_bouton_lancer, 0.5, 0.5, 1, 1);
            drawMap(texture_bouton_guide, 0.5, 0.5, 1, 1);

            listTower = NULL;
            listMonster = NULL;
            createTableau(image, nbCaseW, nbCaseH,map, tabCase);
            argent = 1000;
            jeu->start = 0;
        }

        if(chgtTexture == 1)
        {
            constructMenu();
        }

        if(chgtTexture == 2)
        {
            //Dessin de la map
            drawMap(texture_map, 0.5, 0.5, 1, 1);

            //Dessin du menu de jeu
            drawMap(texture_menu, 0.5, 0.5, 1, 1);

            //Affichage de l'argent restant
            sprintf(char_argent, "%d", argent);
            sprintf(argent_restant, "%s", char_argent);
            printText(GLUT_BITMAP_HELVETICA_18, argent_restant, 0.12, 0.135);

            if(guide_du_jeu == 1){
                drawMap(texture_guide_du_jeu, 0.5, 0.5, 1, 1);
            }
            
            /********************************** TOUR ****************************************/

            // après verification de la postion
            if(posTower != 0){
                int tabX = positionTowerX/30;
                int tabY = positionTowerY/30;

                float mapX = positionTowerX/630.0;
                float mapY = positionTowerY/630.0;

                int coutTower =0;
                coutTower = countTower(towertype);

                if(tabCase[tabX][tabY].videTower == 0 && tabCase[tabX][tabY].videBat == 0 && tabCase[tabX][tabY].type == construct){
                   
                    
                    //verification de l'argent pour l'achat de la tour
                    if(argent >= coutTower){
                        tabCase[tabX][tabY].videTower = indexTower;
                        newTower = createTower(indexTower, positionTowerX, positionTowerY, towertype, &listTower);
                        argent = argent - newTower->cout;
                        sprintf(char_argent, "%d\n", argent);
                        sprintf(argent_restant, "%s", char_argent);
                        towertype = -1;
                        posTower = 0;
                        indexTower++;
                    }
                }
                /*
                else
                {
                    printf("Can not construct tower here\n");
                }*/
            }

            constructTower(&listTower);
            if(nbinfo_tower_rocket == 1){
                drawMap(texture_info_rocket, 0.50, 0.18, 0.25, 0.20);
            }
            if(nbinfo_tower_laser == 1){
                drawMap(texture_info_laser, 0.60, 0.18, 0.25, 0.20);
            }
            if(nbinfo_tower_mitraillette == 1){
                drawMap(texture_info_mitraillette, 0.70, 0.18, 0.25, 0.20);
            }
            if(nbinfo_tower_hybride == 1){
                drawMap(texture_info_hybride, 0.80, 0.18, 0.25, 0.20);
            }

            // sur la map
            if(info_tower_rocket == 1){
                drawMap(texture_info_rocket_map, positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }
            if(info_tower_laser == 1){
                drawMap(texture_info_laser_map, positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }
            if(info_tower_mitraillette == 1){
                drawMap(texture_info_mitraillette_map, positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }
            if(info_tower_hybride == 1){
                drawMap(texture_info_hybride_map,positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }

            Tower *verifTower = listTower;
            while(verifTower != NULL)
            {
                Monster *verifMonster = listMonster;
                while(verifMonster != NULL){
                    double A = 0;
                    double B = 0;
                    double H2 = 0;
                    double H = 0;
                    if(verifTower->posX >= verifMonster->X){
                        A = verifTower->posX - verifMonster->X;
                    }
                    if(verifTower->posX < verifMonster->X){
                        A = verifMonster->X - verifTower->posX;
                    }
                    if(verifTower->posY >= verifMonster->Y){
                        B = verifTower->posY - verifMonster->Y;
                    }
                     if(verifTower->posY < verifMonster->Y){
                        B = verifMonster->Y - verifTower->posY;
                    }
                    
                    H2 = pow(A,2) + pow(B,2);
                    H=sqrt(H2);
                    //printf("A = %lf B= %lf hauteur = %lf\n", A, B, H );
                    //H = sqrt(pow(A,2) + pow(B,2));
                    //H = 20;
                    if(times%verifTower->cadence == 0)
                    {
                        if(H <= verifTower->portee){
                        //printf("pdv = %d\n", verifMonster->pdv );
                        //printf("KILLLL\n");
                        verifMonster->pdv -= verifTower->puissance; 
                        //printf("pdv = %d\n", verifMonster->pdv );
                        if(verifMonster->pdv == 0 || verifMonster->pdv < 0)
                        {
                            argent = argent + (verifMonster->gain*nbvagues);
                            sprintf(char_argent, "%d\n", argent);
                            sprintf(argent_restant, "%s", char_argent);
                            listMonster =  deleteMonster(verifMonster, listMonster);
                        }
                        }
                    }
                    
                verifMonster = verifMonster->next;
                //printf("KILLLL2\n");
                }
                verifTower = verifTower->nextTower;
                //printf("KILLLL3\n");
            }

            /********************************** MONSTRE ****************************************/
            if(jeu->start == 1 && jeu->pause%2 == 0){

                
                if(times%80 == 0 && nbMonster <= 4){
                    
                    monsterType = chooseMonster(nbvagues);
                    indexBegin = beginMonster;
                    indexDirection = indexBegin - 1;
                    begin = getNode(chemin[indexBegin], map);
                    direction = getNode(chemin[indexDirection], map);
                    firstmonster = createMonster(nbvagues,indexMonster, indexDirection, monsterType, direction, begin->x, begin->y, &listMonster);
                    indexMonster++;
                    nbMonster++;
                    //printf("getMOnster = %d\n", getMonster(indexMonster,listMonster)->indexMonster);
                }
                else if(times%600 == 0 && nbMonster == 5)
                {
                     //1000 millisecondes = 1 seconde ; faire pause :
                    
                        if(listMonster == NULL)
                        {
                            printf("on est là %d\n", times);
                            nbMonster = 0;
                            nbvagues ++;
                        }
                   
                }

                constructMonster(&listMonster);
                Monster *mov = listMonster;
                if(movMonster == 0){
                    while (mov != NULL){

                        float monsterX = mov->X;
                        float monsterY = mov->Y;
                        float directionX = mov->direction->x;
                        float directionY = mov->direction->y;
                        if(mov->direction != NULL){
                            if(directionY == monsterY)
                            {
                                if(directionX > monsterX)
                                {
                                    mov->X += 1*mov->vitesse;
                                }
                                else
                                {
                                    mov->X -= 1*mov->vitesse;
                                }
                            }
                            else
                            {
                                if(directionY > monsterY)
                                {
                                    mov->Y += 1*mov->vitesse;
                                }
                                else
                                {
                                    mov->Y -= 1*mov->vitesse;
                                }
                            }
                            if(monsterX == directionX && monsterY == directionY)
                            {
                                mov->indexBegin -= 1;
                                if(mov->indexBegin > 0)
                                {
                                    direction = getNode(chemin[mov->indexBegin], map);
                                    mov->direction = direction;
                                }  
                                if (mov->indexBegin == 0)
                                {
                                    direction = final;
                                    mov->direction = direction;
                                } 
                                if (mov->indexBegin < 0)
                                {
                                    mov->direction = NULL;
                                }                           
                            }
                        }
                        if(mov->direction == NULL)
                        {
                            printf("perdu\n");
                            movMonster = 1;
                            chgtTexture = 3;
                        }
                        mov = mov->next;
                    }
                }

                 times++; 
            }

            //informations des tours sur la map
            if(tabCase[positionRX/30][positionRY/30].videTower != 0)
            {
                Tower * findTower = getTower(tabCase[positionRX/30][positionRY/30].videTower, listTower );
                if(findTower->type == ROCKET)
                {
                    info_tower_rocket = 1;
                }
                else
                {
                    info_tower_rocket = 0;
                }
                if(findTower->type == LASER)
                {
                    info_tower_laser = 1;
                }
                else
                {
                    info_tower_laser = 0;
                }
                if(findTower->type == MITRAILLETTE)
                {
                    info_tower_mitraillette = 1;
                }
                else
                {
                    info_tower_mitraillette = 0;
                }
                if(findTower->type == HYBRIDE)
                {
                    info_tower_hybride = 1;
                }
                else
                {
                    info_tower_hybride = 0;
                }
            }
            else
            {
                info_tower_rocket = 0;
                info_tower_laser = 0;
                info_tower_mitraillette = 0;
                info_tower_hybride = 0;
            }

            /********************************** BATIMENTS ****************************************/

            // après verification de la postion
            if(posConstruction != 0){
                int tabX = positionConstructionX/30;
                int tabY = positionConstructionY/30;

                float mapX = positionConstructionX;
                float mapY = positionConstructionY;

                int coutConstruction = 0;
                coutConstruction = countConstruction(constructiontype);

                if(tabCase[tabX][tabY].videBat == 0 && tabCase[tabX][tabY].videTower == 0 && tabCase[tabX][tabY].type == construct){
                    

                    //verification de l'argent pour l'achat du batiment
                    if(argent >= coutConstruction){
                        tabCase[tabX][tabY].videBat = indexBat;
                        newConstruction = createConstruction(indexBat,mapX, mapY, constructiontype, &listConstruction);
                        argent = argent - newConstruction->cout;
                        sprintf(char_argent, "%d\n", argent);
                        sprintf(argent_restant, "%s", char_argent);
                        VerifBatiment(newConstruction, listTower,  nbCaseW, nbCaseH, tabCase);
                        indexBat++;
                    }
                    constructiontype = -1;
                    posConstruction = 0;
                }
                /*
                else{
                    printf("Can not construct batiments here\n");
                }*/
            }
            constructConstruction(&listConstruction);

            if(nbinfo_construction_radar == 1){
                drawMap(texture_info_radar, 0.23, 0.18, 0.25, 0.20);
            }
            if(nbinfo_construction_usine == 1){
                drawMap(texture_info_usine, 0.30, 0.18, 0.25, 0.20);
            }
            if(nbinfo_construction_munitions == 1){
                drawMap(texture_info_munitions, 0.38, 0.18, 0.25, 0.20);
            }

            // Portée des bâtiments
            
            //informations des tours sur la map
            if(tabCase[positionRX/30][positionRY/30].videBat != 0)
            {
                Construction * findConstruction = getConstruction(tabCase[positionRX/30][positionRY/30].videBat, listConstruction);
                if(findConstruction->type == RADAR)
                {
                    info_construction_radar = 1;
                }
                else
                {
                    info_construction_radar = 0;
                }
                if(findConstruction->type == USINE)
                {
                    info_construction_usine = 1;
                }
                else
                {
                    info_construction_usine = 0;
                }
                if(findConstruction->type == MUNITIONS)
                {
                    info_construction_munitions = 1;
                }
                else
                {
                    info_construction_munitions = 0;
                }
            }
            else
            {
                info_construction_radar = 0;
                info_construction_usine = 0;
                info_construction_munitions = 0;
            }

            // sur la map
            if(info_construction_radar == 1){
                drawMap(texture_info_radar_map, positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }
            if(info_construction_usine == 1){
                drawMap(texture_info_usine_map, positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }
            if(info_construction_munitions == 1){
                drawMap(texture_info_munitions_map, positionRX/630.0, positionRY/630.0, 0.25, 0.18);
            }
        }

        // if you lose
        if(chgtTexture == 3)
        {
            drawMap(texture_gameover, 0.5, 0.5, 1, 1);
        }

        // if you win
        if(chgtTexture == 4)
        {
            //drawMap(texture_win, 0.5, 0.5, 1, 1);
        }

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }

            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
        
            if( e.type == SDL_KEYDOWN 
                && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                loop = 0; 
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Redimensionnement fenetre */
                case SDL_VIDEORESIZE:
                    reshape(&surface, e.resize.w, e.resize.h);
                    break;

                case SDL_MOUSEMOTION:
                    positionRX = e.motion.x;
                    positionRY = e.motion.y;

                    //menu des batiments
                    if(positionRX > 196 && positionRX < 220 && positionRY > 572 && positionRY < 603){
                        nbinfo_construction_radar = 1;
                    }
                    else{
                        nbinfo_construction_radar = 0;
                    }
                    if(positionRX > 239 && positionRX < 264 && positionRY > 572 && positionRY < 603){
                        nbinfo_construction_usine = 1;
                    }
                    else{
                        nbinfo_construction_usine = 0;
                    }
                    if(positionRX > 284 && positionRX < 320 && positionRY > 572 && positionRY < 603){
                        nbinfo_construction_munitions = 1;
                    }
                    else{
                        nbinfo_construction_munitions = 0;
                    }

                    //menu des tours 
                    if(positionRX > 337 && positionRX < 385 && positionRY > 564 && positionRY < 612){
                        nbinfo_tower_rocket = 1;
                    }
                    else{
                        nbinfo_tower_rocket = 0;
                    }
                    if(positionRX > 404 && positionRX < 454 && positionRY > 564 && positionRY < 612){
                        nbinfo_tower_laser = 1;
                    }
                    else{
                        nbinfo_tower_laser = 0;
                    }
                    if(positionRX > 474 && positionRX < 521 && positionRY > 564 && positionRY < 612){
                        nbinfo_tower_mitraillette = 1;
                    }
                    else{
                        nbinfo_tower_mitraillette = 0;
                    }
                    if(positionRX > 541 && positionRX < 589 && positionRY > 564 && positionRY < 612){
                        nbinfo_tower_hybride = 1;
                    }
                    else{
                        nbinfo_tower_hybride = 0;
                    }
                    break;

                //test clic droit et clic gauche
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);

                    switch(e.button.button) 
                    {
                        case SDL_BUTTON_LEFT:
                            printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                            positionX = e.button.x;
                            positionY = e.button.y;

                            if(positionX > 511 && positionX < 540 && positionY > 6 && positionY < 36){
                                guide_du_jeu;
                            }

                            if(positionX > 550 && positionX < 580 && positionY > 6 && positionY < 36){
                                jeu->pause ++;
                            }

                            if(positionX > 590 && positionX < 620 && positionY > 6 && positionY < 36){
                                chgtTexture = 0;
                            }

                            //choix du type de la tour
                            if(positionX > 332 && positionX < 607 && positionY > 558 && positionY < 623){
                                towertype = choixTower(positionX, positionY);
                                constructiontype = -1;
                            }
                            if(towertype != -1)
                            {
                                positionTowerX = positionX;
                                positionTowerY = positionY;
                                posTower = 1; 
                            }

                            //choix du type d'un batiment
                            if(positionX > 179 && positionX < 332 && positionY > 558 && positionY < 623){
                                constructiontype = choixConstruction(positionX, positionY);
                                towertype = -1;
                            }
                            if(constructiontype != -1)
                            {
                                positionConstructionX = positionX;
                                positionConstructionY = positionY;
                                posConstruction = 1; 
                            }
                        break;
                    
                        case SDL_BUTTON_RIGHT:
                            printf("test clic droit ok\n");
                            positionRX = e.button.x;
                            positionRY = e.button.y;
                        break;

                        default:
                            break;
                    }
                    break;


                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    switch (e.key.keysym.sym){
                        case SDLK_a:
                        chgtTexture = 1;
                        break;

                        case SDLK_m:
                        chgtTexture = 0;
                        break;

                        case SDLK_r:
                        jeu->start = 1;
                        break;

                        case SDLK_s:
                        chgtTexture = 2;
                        break;

                        default:
                        break;
                    }
                break;
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
       
        elapsedTime = SDL_GetTicks() - startTime;
    }

    //Liberation de la mémoire occupee par background
    //SDL_FreeSurface(background_map);

    //Liberation de la memoire allouee sur le GPU pour la texture
    glDeleteTextures(1, &texture_map);

    //Liberation de la mémoire occupee par img
    SDL_FreeSurface(surface);

    //Liberation des ressources associees a la SDL
    SDL_Quit();
    freeImage(&image);
    return EXIT_SUCCESS;
   
    //return 0;
}
