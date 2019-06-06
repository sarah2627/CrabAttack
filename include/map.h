#ifndef MAP__
#define MAP__

#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "node.h"
#include "image.h"

#define TAILLE_MAX 50

/// \ Structure color
 typedef struct color
{
    unsigned char red;
    unsigned char blue;
    unsigned char green;
} Color;

/// \ Structure map
 typedef struct map
 {
    char *carte; // image ppm
    int nbNode;
    Node *listenode; 
    Color chemin;
    Color noeud;
    Color construct;
    Color in;
    Color out;
    Color sea;
 } Map;
 

/// \brief charge le fichier ITD
/// \param filename : le nom de notre fichier
/// \param image : la structure image où on va stocker notre map
/// \return notre map après avoir lu notre fichier
Map loadMap(char *filename, Image *image);

/// \brief lie le fichier ITD
/// \param fichierITD : le fichier qu'on va lire
/// \param map : la structure de notre map qu'on va remplir
/// \param image : la structure image où on va stocker notre map
/// \return 1 si c'est lu sinon 0 si erreur lors de la lecture
 int readMap(FILE * fichierITD, Map * map, Image *image);

/// \brief affiche notre liste de noeuds
/// \param map : la structure de notre map où se trouve notre liste de noeuds
void printMapNode(Map map);

/// \brief cherche notre noeud à partir d'un index dans notre liste
/// \param index : l'index du noeud qu'on cherche
/// \param map : la structure de notre map où se trouve notre liste de noeuds
/// \return un pointeur qui pointe sur un noeud de notre liste 
Node * getNode(int index, Map map);

/// \brief créer une nouvelle couleur
/// \param r, g, b : paramètres de notre couleur
/// \return une nouvelle color
Color newColor(float r, float g, float b);

/// \brief cherche le plus court chemin à partir de notre liste de noeuds
/// \param map : la structure de notre map où se trouve notre liste de noeuds
/// \param tabChemin : notre tableau qui va contenir notre plus court chemin
void cheminDijkstra(Map map, int* tabChemin);


 
#endif