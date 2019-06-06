#include "draw.h"

static float aspectRatio;
/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(
        0,1, 
        0,1);
}

// Création d'un carré
void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0,255,0);
        glVertex2f(0.0, 0.0);
        glColor3ub(255, 255, 255);

    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glColor3ub(0,255,0);
    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);
    glColor3ub(255, 255, 255);
    glEnd();
}


// Initialisation de la texture (à partir de l'image)
GLuint Texture_Load(char* image_path,float texWidth, float texHeight){
    GLuint texture_id;

    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_Surface* image = IMG_Load(image_path);

    GLenum format;

    switch(image->format->BytesPerPixel) {
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

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(image);

    return texture_id ;
}

// on dessine les éléments sur la map à partir d'une texture
void drawMap(GLuint texture_id, float x , float y , float width, float height){
    if (texture_id)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
        glPushMatrix();
            glBegin(GL_QUADS);
               glTexCoord2d(0, 0); 
               glVertex2f(x-width/2,y+height/2);
               glTexCoord2d(0, 1); 
               glVertex2f(x-width/2,y-height/2);
               glTexCoord2d(1, 1); 
               glVertex2f(x+width/2,y-height/2);
               glTexCoord2d(1, 0); 
               glVertex2f(x+width/2,y+height/2);
            glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        fprintf(stderr, "Erreur de texture\n");
    }
}

//afficher un texte
void printText(void *text, char *info, float x, float y)
{
    const unsigned char* tmp = info;
    glPushMatrix();
        glColor3ub(28, 46, 79);
        glRasterPos2f(x, y);
        glutBitmapString(text, tmp);
    glPopMatrix();
    glColor3ub(255, 255, 255);
}
