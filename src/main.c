#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>
#include <SDL/SDL_mixer.h>

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

    //lecture du fichier ITD et construction de la map
    Map map;
    Image image; //l'image qu'on va parcourir
    map = loadMap("./data/map_day.itd", &image);
    char file[30] = "images/";
    strcat(file, map.carte);
    int chemin[map.nbNode];
    Node *final = getNode(1, map);
    
    //creer mon tableau, une grille de mon image
    int nbCaseW = image.width/30;
    int nbCaseH = image.height/30;
    Case tabCase[nbCaseW][nbCaseH];
    createTableau(image, nbCaseW, nbCaseH,map, tabCase);

    //variable pour le changement de textures
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

    //Argent
    int argent = 1000;
    //chaine de caractere qui stocke l'argent convertit en chaine de caracteres
    char char_argent[10];
    char argent_restant[10];

    //Vagues
    char char_vagues[3];
    char *textvaguestotales = "/50";
    //chaine de caractere qui stocke l'argent convertit en chaine de caracteres
    char vagues_restantes[3];

    GLuint texture_map;

    //Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }

    //Initialisation GLUT
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
    //glGenTextures(1, &texture_map);
    texture_map = Texture_Load(carte, 630, 630);

    //Menu du départ
    GLuint texture_begin = Texture_Load("./images/texture_fond.png", 630, 630);
    GLuint texture_bouton_lancer = Texture_Load("./images/bouton_lancer_partie.png", 630, 630);
    GLuint texture_bouton_guide = Texture_Load("./images/bouton_guide_du_jeu.png", 630, 630);

    //Guide du jeu
    GLuint texture_fond_guide = Texture_Load("./images/guide_du_jeu_fond.png", 630, 630);
    GLuint texture_guide = Texture_Load("./images/guide_du_jeu_parchemin.png", 630, 630);
    GLuint texture_guide_du_jeu = Texture_Load("./images/guide_du_jeu.png", 631, 631);
    GLuint texture_bouton_retour = Texture_Load("./images/retour_menu.png", 630, 631);

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

    //Initialisation des variables pour les tours
    Tower *listTower = NULL;
    Tower *newTower = NULL;
    int posTower = 0;
    int positionTowerX = 0;
    int positionTowerY = 0;
    int supprTower = 0;

     //Initialisation des variables pour les batiments
    Construction *listConstruction = NULL;
    Construction *newConstruction = NULL;
    int posConstruction = 0;
    int positionConstructionX = 0;
    int positionConstructionY = 0;
    int indexBat = 1;

    TypeTower towertype = -1;
    TypeConstruction constructiontype = -1;
    int indexTower = 1;

    //on cherche le chemin le plus court
    cheminDijkstra(map, chemin);

    //Initialisation des variables pour les monstres
    Monster *listMonster = NULL;
    int indexBegin =0;
    int beginMonster = 0;
    // on cherche notre node d'entrée dans notre tableau
    for(int i = 0; i<map.nbNode; i++)
    {
        if(chemin[i] == 0)
        {
            beginMonster = i;
        }
    }
    indexBegin = beginMonster;
    int indexMonster = 1;
    TypeMonster monsterType;
    Node * begin = getNode(chemin[indexBegin], map);
    int indexDirection = indexBegin - 1;
    Node * direction = getNode(chemin[indexDirection], map);

    int movMonster = 0;
    int nbvagues = 1;
    int nbMonster = 0;
    int times = 0;

    //Ajout du son
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
        {
            printf("%s", Mix_GetError());
        }
        Mix_Music *musique; //Création du pointeur de type Mix_Music
        musique = Mix_LoadMUS("./images/daft-punk-make-love-official-audio.mp3"); //Chargement de la musique
        Mix_PlayMusic(musique, -1); //Jouer infiniment la musique


    /* Boucle principale */
    int loop = 1;

      while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        // on est dans le menu
        if (chgtTexture == 0)
        {
            drawMap(texture_begin, 0.5, 0.5, 1, 1);
            drawMap(texture_bouton_lancer, 0.5, 0.5, 1, 1);
            drawMap(texture_bouton_guide, 0.5, 0.5, 1, 1);

            // on réinitialise la map à nouveau (si on retourne dans le menu par exemple)
            listTower = NULL;
            listMonster = NULL;
            listConstruction = NULL;
            createTableau(image, nbCaseW, nbCaseH,map, tabCase);
            argent = 1000;
            jeu->start = 0;
            movMonster = 0;
            nbvagues = 1;
            nbMonster = 0;
            times = 0;

        }

        // on est dans la page "but du jeu"
        if(chgtTexture == 1)
        {
            drawMap(texture_fond_guide, 0.5, 0.5, 1, 1);
            drawMap(texture_guide, 0.5, 0.5, 1, 1);
            drawMap(texture_bouton_retour, 0.5, 0.5, 1, 1);
        }

        // on est dans la map, on lance la partie
        if(chgtTexture == 2)
        {
            //Dessin de la map
            drawMap(texture_map, 0.5, 0.5, 1, 1);

            //Dessin du menu de jeu
            drawMap(texture_menu, 0.5, 0.5, 1, 1);

            //Affichage de l'argent restant
            sprintf(char_argent, "%d", argent);
            sprintf(argent_restant, "%s", char_argent);
            printText(GLUT_BITMAP_HELVETICA_18, argent_restant, 0.17, 0.115);

            //Affichage du nombre de vagues
            sprintf(char_vagues, "%d", nbvagues);
            sprintf(vagues_restantes, "%s%s", char_vagues, textvaguestotales);
            printText(GLUT_BITMAP_HELVETICA_18, vagues_restantes, 0.5, 0.96);

            //Affichage du guide du jeu
            if(jeu->aide == 1){
                drawMap(texture_guide_du_jeu, 0.5, 0.5, 1, 1);
            }

            // le joueur doit placer une tour pour enclencher le jeu et faire apparaitre les monstres
            if( listTower != NULL || listConstruction != NULL)
            {
                jeu->start = 1;
            }
            
            /********************************** TOUR ****************************************/

            // après verification de la position
            if(posTower != 0){
                int tabX = positionTowerX/30;
                int tabY = positionTowerY/30;


                int coutTower =0;
                coutTower = countTower(towertype);

                // on vérifie qu'il n'y a pas déjà une tour ou un batiment ou qu'on est bien dans une zone constructible
                if(tabCase[tabX][tabY].videTower == 0 && tabCase[tabX][tabY].videBat == 0 && tabCase[tabX][tabY].type == construct){
                   
                    
                    //verification de l'argent pour l'achat de la tour
                    if(argent >= coutTower){

                        tabCase[tabX][tabY].videTower = indexTower;
                        newTower = createTower(indexTower, positionTowerX, positionTowerY, towertype, &listTower);
                        argent = argent - newTower->cout;
                        sprintf(char_argent, "%d\n", argent);
                        sprintf(argent_restant, "%s", char_argent);
                        VerifTower(listConstruction,newTower);
                        towertype = -1;
                        posTower = 0;
                        indexTower++;
                    }
                    constructiontype = -1;
                    posTower = 0;    
                }
            }

            // on construit les tours de notre liste
            constructTower(&listTower);

            // affiche les informations des tours en bas du menu
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

            // affiche les informations des tours sur la map
            if(info_tower_rocket == 1){
                drawMap(texture_info_rocket_map, positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }
            if(info_tower_laser == 1){
                drawMap(texture_info_laser_map, positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }
            if(info_tower_mitraillette == 1){
                drawMap(texture_info_mitraillette_map, positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }
            if(info_tower_hybride == 1){
                drawMap(texture_info_hybride_map,positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }

            // On vérifie si un monstre est à proximité de la tour
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
                    // on calcule la distance entre notre tour et notre monstre
                    H2 = pow(A,2) + pow(B,2);
                    H=sqrt(H2);
                    // on vérifie si la tour peut tirer en fonction de sa cadence
                    if(times%verifTower->cadence == 0)
                    {
                        // si la distance est plus petite que la portée de notre tour on tire
                        if(H <= verifTower->portee){
                        float lineTX = verifTower->posX/630.0;
                        float lineTY = 1-verifTower->posY/630.0;
                        float lineMX = verifMonster->X/630.0;
                        float lineMY = 1-verifMonster->Y/630.0;
                        glLineWidth(4);
                        glBegin(GL_LINES);
                            glColor3ub(255,0,0);
                            glVertex2f( lineTX , lineTY);
                            glVertex2f(lineMX , lineMY);
                            glColor3ub(255, 255, 255);
                        glEnd();
                        verifMonster->pdv -= verifTower->puissance; 

                            // si le monstre n'a plus de point de vie
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
                }
                verifTower = verifTower->nextTower;
            }

            //récupère les informations des tours sur la map en fonction de la position de la souris
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

            // si on veut supprimer une tour
            if(supprTower == 1)
            {
                // on vérifie que la case est bien occupée par une tour
                if(tabCase[positionX/30][positionY/30].videTower != 0)
                {
                    int indexSuppr = tabCase[positionX/30][positionY/30].videTower;
                    Tower * TowerSupp = getTower(indexSuppr, listTower);
                    listTower = deleteTower(TowerSupp, listTower);
                    tabCase[positionX/30][positionY/30].videTower = 0;
                    argent = argent + TowerSupp->cout;
                    sprintf(char_argent, "%d\n", argent);
                    sprintf(argent_restant, "%s", char_argent);
                    supprTower = 0;
                }
            }

            /********************************** MONSTRE ****************************************/
            // si le jeu commence et n'est pas en pause
            if(jeu->start == 1 && jeu->pause%2 == 0){

                // on crée une liste de 10 monstres par vague
                if(times%80 == 0 && nbMonster <= 9){
                    
                    monsterType = chooseMonster(nbvagues);
                    indexBegin = beginMonster;
                    indexDirection = indexBegin - 1;
                    begin = getNode(chemin[indexBegin], map);
                    direction = getNode(chemin[indexDirection], map);
                    Monster *firstmonster = createMonster(nbvagues,indexMonster, indexDirection, monsterType, direction, begin->x, begin->y, &listMonster);
                    indexMonster++;
                    nbMonster++;
                  
                }
                // on crée une nouvelle vague
                else if(times%600 == 0 && nbMonster == 10)
                {
                     //1000 millisecondes = 1 seconde ; 
                    
                        if(listMonster == NULL)
                        {
                            nbMonster = 0;
                            nbvagues ++;
                        }
                }

                // on affiche nos monstres sur la map
                constructMonster(&listMonster);
                // on déplace le monstre
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
                                // si il a atteint sa destination, on change son noeud direction
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
                            // le monstre est arrivé à la sortie
                            //printf("perdu\n");
                            movMonster = 1;
                            jeu->perdu = 3;
                        }
                        mov = mov->next;
                    }
                }

                times++; 

                // si on a vaincu tous les monstres des 50 vagues, on gagne la partie
                 if(nbvagues == 50 && listMonster == NULL)
                {
                    jeu->gagne = 4;
                    chgtTexture = 4;
                    jeu->start = 0;
                }
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

                // on vérifie qu'il n'y a pas de batiment, de tour et que l'emplacement est constructible
                if(tabCase[tabX][tabY].videBat == 0 && tabCase[tabX][tabY].videTower == 0 && tabCase[tabX][tabY].type == construct){
                    

                    //verification de l'argent pour l'achat du batiment
                    if(argent >= coutConstruction){
                        tabCase[tabX][tabY].videBat = indexBat;
                        newConstruction = createConstruction(indexBat,mapX, mapY, constructiontype, &listConstruction);
                        argent = argent - newConstruction->cout;
                        sprintf(char_argent, "%d\n", argent);
                        sprintf(argent_restant, "%s", char_argent);
                        VerifBatiment(newConstruction, listTower);
                        indexBat++;
                    }
                    constructiontype = -1;
                    posConstruction = 0;
                }
            }
            // on affiche la liste de nos batiments sur notre map
            constructConstruction(&listConstruction);

            // affiche les informations en bas du menu
            if(nbinfo_construction_radar == 1){
                drawMap(texture_info_radar, 0.23, 0.18, 0.25, 0.20);
            }
            if(nbinfo_construction_usine == 1){
                drawMap(texture_info_usine, 0.30, 0.18, 0.25, 0.20);
            }
            if(nbinfo_construction_munitions == 1){
                drawMap(texture_info_munitions, 0.38, 0.18, 0.25, 0.20);
            }

            // affiche les informations sur la map
            if(info_construction_radar == 1){
                drawMap(texture_info_radar_map, positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }
            if(info_construction_usine == 1){
                drawMap(texture_info_usine_map, positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }
            if(info_construction_munitions == 1){
                drawMap(texture_info_munitions_map, positionRX/630.0, 1 - positionRY/630.0, 0.25, 0.18);
            }
            
            // on récupère les informations des batiments sur la map
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

            
        }

        // si on perd
        if(jeu-> perdu == 3)
        {
            drawMap(texture_gameover, 0.5, 0.5, 1, 1);
        }

        // si on gagne
        if(jeu->gagne == 4)
        {
            drawMap(texture_win, 0.5, 0.5, 1, 1);
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

                    //passe sa souris sur le bouton pour afficher le guide du jeu
                    if(positionRX > 511 && positionRX < 540 && positionRY > 6 && positionRY < 36){
                        jeu->aide = 1;
                    }
                    else
                    {
                        jeu->aide = 0;
                    }
                    break;

                //test clic droit et clic gauche
                case SDL_MOUSEBUTTONUP:
                    //printf("clic en (%d, %d)\n", e.button.x, e.button.y);

                    switch(e.button.button) 
                    {
                        case SDL_BUTTON_LEFT:
                            //printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                            positionX = e.button.x;
                            positionY = e.button.y;

                            //clique sur le bouton pour mettre le jeu en pause
                            if(positionX > 550 && positionX < 580 && positionY > 6 && positionY < 36){
                                jeu->pause ++;
                            }

                             //clique sur le bouton pour quitter la partie et revenir au menu principal
                            if(positionX > 590 && positionX < 620 && positionY > 6 && positionY < 36){
                                chgtTexture = 0;
                                jeu->perdu = 0;
                                jeu->gagne = 0;
                               // printf("Quitter partie, retour menu \n");
                            }

                            //clique sur le bouton pour supprimer une tour
                            if(positionX > 0 && positionX < 152 && positionY > 583 && positionY < 619){
                                supprTower = 1;
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

    //Liberation de la memoire allouee sur le GPU pour la texture
    glDeleteTextures(1, &texture_map);

    glDeleteTextures(1,&texture_begin);
    glDeleteTextures(1,&texture_bouton_lancer);
    glDeleteTextures(1,&texture_bouton_guide);

    glDeleteTextures(1,&texture_fond_guide);
    glDeleteTextures(1,&texture_guide);
    glDeleteTextures(1,&texture_guide_du_jeu);
    glDeleteTextures(1,&texture_bouton_retour);

    glDeleteTextures(1,&texture_menu);

    glDeleteTextures(1,&texture_win);

    glDeleteTextures(1,&texture_gameover);

    glDeleteTextures(1,&texture_info_rocket);
    glDeleteTextures(1,&texture_info_laser);
    glDeleteTextures(1,&texture_info_mitraillette);
    glDeleteTextures(1,&texture_info_hybride);

    glDeleteTextures(1,&texture_info_rocket_map);
    glDeleteTextures(1,&texture_info_laser_map);
    glDeleteTextures(1,&texture_info_mitraillette_map);
    glDeleteTextures(1,&texture_info_hybride_map);

    glDeleteTextures(1,&texture_info_radar);
    glDeleteTextures(1,&texture_info_usine);
    glDeleteTextures(1,&texture_info_munitions);

    glDeleteTextures(1,&texture_info_radar_map);
    glDeleteTextures(1,&texture_info_usine_map);
    glDeleteTextures(1,&texture_info_munitions_map);

    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API

    //Liberation de la mémoire occupee par img
    SDL_FreeSurface(surface);
    //FreeTexture(texture_begin);
    //Liberation des ressources associees a la SDL
    SDL_Quit();
    freeImage(&image);
    free(jeu);
    return EXIT_SUCCESS;
   
}
