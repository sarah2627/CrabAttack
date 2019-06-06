#ifndef DRAW_H__
#define DRAW_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
//#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/// \brief permet de charger une texture
/// \param image_path : chemin de l'image que l'on veut
/// \param texWidth : la largeur de notre texture
/// \param texHeight : la hauteur de notre texture
GLuint Texture_Load(char* image_path, float texWidth, float texHeight);

/// \brief permet de redimensionner la fenetre SDL
/// \param surface : la surface que l'on veut redimensionner
/// \param width : la largeur de notre surface
/// \param height : la hauteur de notre surface
void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);


/// \brief permet de créer un carre ou un rectangle
/// \param filled : savoir si notre forme est pleine ou non
void drawSquare(int filled);

/// \brief permet de créer un objet à partir d'un texture
/// \param texture_id : la texture
/// \param x : la position en x de notre texture
/// \param y : la position en y de notre texture
/// \param width : la largeur de notre texture
/// \param height : la hauteur de notre texture
void drawMap(GLuint texture_id, float x , float y , float width, float height);

/// \brief permet d'afficher un texte
/// \param text : la police à utiliser
/// \param info : le texte à afficher
/// \param x : la position en x du texte à afficher
/// \param y : la position en y du texte à afficher

void printText(void *text, char *info, float x, float y);

#endif
