#ifndef DRAW_H__
#define DRAW_H__

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//chargement d'une image
SDL_Surface* Image_Load(char* image_path);
//chargement d'une texture
GLuint Texture_Load(char* image_path);

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height);

void drawOrigin();
void drawSquare(int filled);
void drawCircle(int filled);
void drawRoundedSquare(int filled);


#endif
