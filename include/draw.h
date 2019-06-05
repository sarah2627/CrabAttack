#ifndef DRAW_H__
#define DRAW_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14
//chargement d'une image
//SDL_Surface* Image_Load(char* image_path);
//chargement d'une texture
GLuint Texture_Load(char* image_path,float texWidth, float texHeight);
//Texture_Load("./images/tower_rocket", &tower_texture, imgTower);

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);

void drawOrigin();
void drawSquare(int filled);
void drawCircle(int filled);
void drawRoundedSquare(int filled);
void drawMap(GLuint texture_id, float x , float y , float width, float height);

char *choixMenu(float clickX, float clickY);
void constructMenu();
void printText(void *text, char *info, float x, float y);

#endif
