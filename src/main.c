#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 
#include <GL/glut.h>

#include "grid.h"
#include "map.h"
#include "draw.h"
#include "tower.h"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Imac Towards Defends";

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main()
{
    Map map;
    Image image; //l'image qu'on va parcourir
    map = loadMap("./data/map_day.itd", &image);
    char file[30] = "images/";
    strcat(file, map.carte);
    printf("file = %s", file);
    printf("afficher chemin : %s", map.carte);
    printMapNode(map);
    int index = 3;
    Node * node = getNode(index, map);

    //creer mon tableau, une grille de mon image
    int nbCaseW = image.width/30;
    int nbCaseH = image.height/30;
    Case tabCase[nbCaseW][nbCaseH];
    createTableau(image, nbCaseW, nbCaseH,map, tabCase);
 
    printType(tabCase[6][6].type);
    printf("trouvé\n");

///////// Partie SDL ////////////
    GLuint texture_map;

    int chgtTexture = 0;
    int nbinfo_laser = 0;

    //Tower* tower = createTower(0.5, 0.5, ROCKET);
    TypeTower towertype = -1;

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

    //Chargement de la texture du menu
    GLuint texture_menu = Texture_Load("./images/menu_tour.png", 131, 31);
    GLuint texture_bouton_palmier1 = Texture_Load("./images/tower_rocket2.png", 31, 31);
    GLuint texture_bouton_palmier2 = Texture_Load("./images/tower_mitraillette2.png", 31, 31);
    GLuint texture_bouton_palmier3 = Texture_Load("./images/tower_laser2.png", 31, 31);
    GLuint texture_bouton_palmier4 = Texture_Load("./images/tower_hybride2.png", 31, 31);

    //Chargement de la texture des infos des tours
    GLuint texture_info_laser = Texture_Load("./images/info_laser.png", 151, 101);


    int positionX = 0;
    int positionY = 0;
    int positionRX = 0;
    int positionRY = 0;


    /* Boucle principale */
    int loop = 1;

    Tower *newtoto;
    newtoto = createTower(0.5, 0.5, LASER);

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
        }

        if(chgtTexture == 1)
        {
            constructMenu();
        }

        if(chgtTexture == 2)
        {
            //Dessin de la map
            drawMap(texture_map, 0.5, 0.5, 1, 1);

            //Dessin du menu
            drawMap(texture_menu, 0.5, 0.5, 0.45, 0.07);

            //Dessin des boutons
            drawMap(texture_bouton_palmier1, 0.55, 0.012, 0.05, 0.05);
            drawMap(texture_bouton_palmier2, 0.65, 0.012, 0.05, 0.05);
            drawMap(texture_bouton_palmier3, 0.75, 0.012, 0.05, 0.05);
            drawMap(texture_bouton_palmier4, 0.85, 0.012, 0.05, 0.05);
            
            // après verification de la postion
            constructTower(newtoto);

            if(nbinfo_laser = 1){
                drawMap(texture_info_laser, 0.5, 0.5, 0.5, 0.5);
            }
        }

        //constructTower(tower);

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

                /* Clic souris */
                    /*
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    positionX = e.button.x;
                    positionY = e.button.y;
                    
                    if(positionX > 408 && positionX < 749 && positionY < 795 && positionY > 748){
                        towertype = choixTower(positionX, positionY);
                    }
                    else{
                        if(towertype != -1)
                        {
                            printf("tour");
                            newtoto->posX = positionX/630.0;
                            newtoto->posY = positionY/630.0;
                            
                            printf("Tour ctyuy");
                        }
                    }
                    break;
                    */

                    //test clic droitet clic gauche
                    case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);

                    switch(e.button.button) 
                    {
                        case SDL_BUTTON_LEFT:
                            printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                            positionX = e.button.x;
                            positionY = e.button.y;
                    
                    if(positionX > 408 && positionX < 749 && positionY < 795 && positionY > 748){
                        towertype = choixTower(positionX, positionY);
                    }
                    else{
                        if(towertype != -1)
                        {
                            printf("tour");
                            newtoto->posX = positionX/800.0;
                            newtoto->posY = positionY/800.0;
                            
                            printf("Tour ctyuy");
                        }
                    }
                    break;
                    
                        case SDL_BUTTON_RIGHT:
                            printf("test clic droit ok\n");
                            positionRX = e.button.x;
                            positionRY = e.button.y;
                            if(positionRX > 521 && positionRX < 560 && positionRY > 752 && positionRY < 789){
                                nbinfo_laser = 1;
                            }
                
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
                        //printf("test touche pressee\n");
                        chgtTexture = 1;
                        break;

                        case SDLK_m:
                        //printf("test touche pressee\n");
                        chgtTexture = 0;
                        break;

                        case SDLK_s:
                        //printf("test touche pressee\n");
                        chgtTexture = 2;
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
