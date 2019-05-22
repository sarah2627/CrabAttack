static float aspectRatio;
/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 200.;
/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;
/* Subdivisions cercle */
static const int CIRCLE_SUBDIVS = 2<<5;

#include "draw.h"

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
    /*if( aspectRatio > 1) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }*/
}


// Chargement de l'image 
/*SDL_Surface* Image_Load(char* image_path){
    SDL_Surface* image = IMG_Load(image_path);
    if(NULL == image) {
        fprintf(stderr, "Echec du chargement de l'image %s\n", image_path);
        exit(EXIT_FAILURE);
    }
    return image;
}*/


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

    /* Liberation de la memoire allouee sur le GPU pour la texture */
    //glDeleteTextures(1, &texture_id);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(image);

    return texture_id ;
}

//////////////////////////////////////
///////////OBJETS CANONIQUES//////////
//////////////////////////////////////
void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}


//Fonction qui dessine un rectangle avec une texture, une largeur et une hauteur
void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}

void drawCircle(int filled) 
{
    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    for(i = 0; i < CIRCLE_SUBDIVS; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));
    }
    glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));

    glEnd();
}

void drawRoundedSquare(int filled)
{
    const float r = 0.1;
    const float s = 1. / 2;
    const float t = s - r;

    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f(s, t);
    for(i = 1; i < CIRCLE_SUBDIVS / 4; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t);
    }
    glVertex2f(t, s);
    glVertex2f(-t, s);
    for(i = CIRCLE_SUBDIVS / 4; i < CIRCLE_SUBDIVS / 4 * 2; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t);
    }
    glVertex2f(-s, t);
    glVertex2f(-s, -t);
    for(i = CIRCLE_SUBDIVS / 4 * 2; i < CIRCLE_SUBDIVS / 4 * 3; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t);
    }
    glVertex2f(-t, -s);
    glVertex2f(t, -s);
    for(i = CIRCLE_SUBDIVS / 4 * 3; i < CIRCLE_SUBDIVS / 4 * 4; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r + t, 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)) * r - t);
    }
    glVertex2f(s, -t);
    glVertex2f(s, t);

    glEnd();
}


void drawMap(GLuint texture_id, float x , float y , float width, float height){
    if (texture_id != NULL)
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
    return 1;
}

/*
char* choixMenu(float clickX, float clickY){
    char* choix = 0;
    //choix partie
    if(clickX > 405 && clickX < 430 && clickY > 790 && clickY < 750){
        choix = "PARTIE";
    }
    //choix guide
    else if(clickX > 147 && clickX < 648 && clickY > 711 && clickY < 593){
        choix = "GUIDE";
    }
    else{
        fprintf(stderr, "erreur lors du choix du type\n");
        //return "0";
    }
    return choix;
}

*/

//construction de la tour
void constructMenu(){
        GLuint texture_fond_guide = Texture_Load("./images/guide_du_jeu_fond.png", 630, 630);
        GLuint texture_guide = Texture_Load("./images/guide_du_jeu_parchemin.png", 630, 630);
        GLuint texture_bouton_quitter = Texture_Load("./images/bouton_quitter.png", 31, 31);
        drawMap(texture_fond_guide, 0.5, 0.5, 1, 1);
        drawMap(texture_guide, 0.5, 0.5, 1, 1);
        drawMap(texture_bouton_quitter, 0.85, 0.85, 0.1, 0.1);
}
