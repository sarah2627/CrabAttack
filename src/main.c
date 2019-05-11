#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <GL/glut.h>

#include "map.h"
#include "draw.h"
#include "image.h"
#include "node.h"
#include "tower.h"

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Imac Towards Defends";

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv)
{
    Map map;
    Image image; //l'image qu'on va parcourir
    GLuint texture_map;

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

    //chargement de l'image
    /*map = loadMap("./data/map_day.itd", &image);
    char file[30] = "images/";
    strcat(file, map.carte);
    printf("file = %s", file);*/

    char image_path[] = "./images/lafinale.png";
    SDL_Surface* carte = IMG_Load(image_path);
    if(NULL == carte){
        fprintf(stderr, "Echec du chargement de l'image%s\n", image_path);
        exit(EXIT_FAILURE);
    }
    float width = (float)carte->w;
    float height = (float)carte->h;
    
    reshape(&surface, carte->w, carte->h);
    //texture_map = Texture_Load(image_path);

    //Initialisation de la texture
    GLuint texture_id;

    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    switch(carte->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", image_path);
            return EXIT_FAILURE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, carte->w, carte->h, 0, format, GL_UNSIGNED_BYTE, carte->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        // Dessin de la map
        drawMap(texture_id, width, height);

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
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
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
    
    return EXIT_SUCCESS;
}