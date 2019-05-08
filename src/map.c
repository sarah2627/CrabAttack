#include "map.h"
#define TAILLE_MAX 50

Map loadMap(char *filename)
{
    FILE* fichierITD = fopen(filename, "r");
    printf("fichier name :%s\n", filename);
    if (fichierITD != NULL)
    {
         Map map;
        if(readMap(fichierITD, &map)) {
            return map;
        }
        fclose(fichierITD);
        exit(EXIT_FAILURE);
    }
    else 
    {
        printf("Impossible d'ouvrir la fichier.itd\n");
        exit(EXIT_FAILURE);
    }
   
}

int readMap(FILE * fichierITD, Map * map)
{
    // première ligne : @ITD 1
    char type[7] = "";
    fgets(type, 5, fichierITD);
    if(strcmp(type, "@ITD") != 0)
    {
        printf("le type est faux\n");
        return 0;
    }
    int numero;
    fscanf(fichierITD, "%d\n", &numero);
    if(numero != 1) {
       printf("le numero est faux\n");
       return 0;
    }

    // deuxième ligne : commentaire
    char commentaire;
    fscanf(fichierITD, "%c", &commentaire);
    if(commentaire != '#')
    {
        printf("il n'y a pas de commentaire\n");
        return 0;
    }
    char ligneCommentaire[TAILLE_MAX]= "";
    fgets(ligneCommentaire, TAILLE_MAX, fichierITD);
    printf("%s", ligneCommentaire);

    //troisième ligne : carte
    char carte[6]="";
    fgets(carte, 6, fichierITD);
    if(strcmp(carte, "carte") != 0)
    {
        printf("il n'y a pas de carte\n");
        return 0;
    }
    fgetc(fichierITD);
    char fichiercarte[15]="";
    fgets(fichiercarte, 15, fichierITD);
    printf("fichier :%s", fichiercarte);

    char* extension = strstr(fichiercarte, ".ppm");
    if(extension == NULL){
        printf("l'image n'est pas au bon format\n");
        return 0;
    }
    else {
        //on enlève le "\n" du .ppm
        int taille = strlen(fichiercarte);
        fichiercarte[taille-1] = '\0';   
        (*map).carte = fichiercarte;
    }

    //quatrième ligne : couleur chemin
    char chemin[7]="";
    int cheminR, cheminG, cheminB;
    fgets(chemin, 7, fichierITD);
    if(strcmp(chemin, "chemin") ==0)
    {
        fscanf(fichierITD, "%d %d %d\n", &cheminR, &cheminG, &cheminB);
        if(cheminR < 0 || cheminR > 255 || cheminG < 0 || cheminG > 255 || cheminB < 0 || cheminB > 255) {
            printf("probleme couleurs chemin\n");
            return 0;
        }
        else {
            (*map).chemin = newColor(cheminR, cheminG, cheminB);
        } 
    }
    else 
    {
        printf("il n'y a pas de chemin\n");
        return 0;
    }

    //cinquième ligne : couleur noeud
    char noeud[6]="";
    int noeudR, noeudG, noeudB;
    fgets(noeud, 6, fichierITD);
    if(strcmp(noeud, "noeud") ==0)
    {
        fscanf(fichierITD, "%d %d %d\n", &noeudR, &noeudG, &noeudB);
        if(noeudR < 0 || noeudR > 255 || noeudG < 0 || noeudG > 255 || noeudB < 0 || noeudB > 255) {
            printf("probleme couleurs noeud\n");
            return 0;
        }
        else {
            (*map).noeud = newColor(noeudR, noeudG, noeudB);
        } 
    }
    else 
    {
        printf("il n'y a pas de noeud\n");
        return 0;
    }

    //sixième ligne : couleur construct
    char construct[10]="";
    int constructR, constructG, constructB;
    fgets(construct, 10, fichierITD);
    if(strcmp(construct, "construct") ==0)
    {
        fscanf(fichierITD, "%d %d %d\n", &constructR, &constructG, &constructB);
        if(constructR < 0 || constructR > 255 || constructG < 0 || constructG > 255 || constructB < 0 || constructB > 255) {
            printf("probleme couleurs construct\n");
            return 0;
        }
        else {
            (*map).construct = newColor(constructR, constructG, constructB);
        } 
    }
    else 
    {
        printf("il n'y a pas de construct\n");
        return 0;
    }

    //septième ligne : couleur in
    char in[3]="";
    int inR, inG, inB;
    fgets(in, 3, fichierITD);
    if(strcmp(in, "in") ==0)
    {
        fscanf(fichierITD, "%d %d %d\n", &inR, &inG, &inB);
        if(inR < 0 || inR > 255 || inG < 0 || inG > 255 || inB < 0 || inB > 255) {
            printf("probleme couleurs in\n");
            return 0;
        }
        else {
            (*map).in = newColor(inR, inG, inB);
        } 
    }
    else 
    {
        printf("il n'y a pas de in\n");
        return 0;
    }

    //huitième ligne : couleur out
    char out[4]="";
    int outR, outG, outB;
    fgets(out, 4, fichierITD);
    if(strcmp(out, "out") ==0)
    {
        fscanf(fichierITD, "%d %d %d\n", &outR, &outG, &outB);
        if(outR < 0 || outR > 255 || outG < 0 || outG > 255 || outB < 0 || outB > 255) {
            printf("probleme couleurs out\n");
            return 0;
        }
        else {
            (*map).out = newColor(outR, outG, outB);
        } 
    }
    else 
    {
        printf("il n'y a pas de out\n");
        return 0;
    }

    //nombre de noeuds vérification
    int nbNode;
    fscanf(fichierITD, "%d\n", &nbNode);
    int curseur;
    curseur = ftell(fichierITD);
    int nbLignes = 0;
    char chaine[TAILLE_MAX] = "";
    while (fgets(chaine, TAILLE_MAX, fichierITD) != NULL)
    {
        printf("%s", chaine);
        nbLignes ++;
    }
  
    printf("\nnbnode = %d, nbligne = %d\n", nbNode, nbLignes);
    if(nbNode != nbLignes) {
        printf ("Nombre de noeuds différent du nombre de lignes\n");
        return 0;
    }
    else {
        (*map).nbNode = nbNode;
    }

    fseek(fichierITD, curseur, SEEK_SET);

    // Chargement de la carte
    char file[30] = "images/";
    strcat(file, fichiercarte);
    SDL_Surface* carteSurface = IMG_Load("images/image.ppm");
    if(carteSurface == NULL) {
        fprintf(stderr, "impossible de charger la carte %s\n", file);
        return 0;
    }
    // création d'un tableau à partir de l'image ppm
    Image image;
    if(loadImagePPM(&image, "images/image.ppm") !=EXIT_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;

    Node *node = NULL;

    while((getline(&line, &len, fichierITD)) != -1) {
        
       printf("%s", line);
       int tmp = 0;
       int nbArgument =0;
       int index =0;
       int type=0;
       int width=0;
       int height=0;

       while(sscanf(line, "%d", &tmp) == 1)
       {
           printf("tmp = %d\n", tmp);
           if(nbArgument == 0)
           {
               if(tmp<0 || tmp>nbNode)
               {
                    fprintf(stderr, "Erreur: index incorrect\n");
                   return 0;
               }
               else
               {
                   index = tmp;
               }
               
              
           }
           if(nbArgument == 1)
           {
               //verification
               if(tmp < 1 || tmp > 4)
               {
                   fprintf(stderr, "Erreur: type incorrect\n");
                   return 0;
               }else
               {
                    type=tmp;
               }
              
           }
           if(nbArgument == 2)
           {
               printf("width : %d\n", carteSurface->w);
               if(tmp < 0 || tmp > carteSurface->w)
               {
                   fprintf(stderr, "Erreur: largeur incorrecte\n");
                   return 0;
               }
               else
               {
                   width = tmp;
               }
               
           }
           if(nbArgument == 3)
           {
               
               if(tmp < 0 || tmp > carteSurface->h)
               {
                   fprintf(stderr, "Erreur: hauteur incorrecte\n");
                   return 0;
               }else
               {
                    height = tmp;
                    /*
                    if(map->noeud.red == image.data[width*height] && map->noeud.green == image.data[width*height+1] && map->noeud.blue == image.data[width*height+2]) 
                    {
                        node = createNode(width,height,type,index);
                    }
                    */
                    node = createNode(width,height,type,index);
                    printf("\n%p", node);
                    printf("\nsfeqrgrg\n");
               }
               
           }
           if(nbArgument > 3)
           {
               
               if(tmp < nbNode)
               {
                   printf("ca va?\n");
                   printf("%p", node);
                 addSuccessors(tmp, node->successors);
                    printf("oui!\n");
               }
               else
               {
                   fprintf(stderr, "Erreur: index des successeurs incorrect\n");
                   return 0;
               }
            }
            nbArgument ++;
            line+=2;  
       }
    }


    SDL_FreeSurface(carteSurface);
    return 1;


}


Color newColor(float r, float g, float b){

	Color color;

	color.red = r;
	color.green = g;
	color.blue = b;

	return color;

}

