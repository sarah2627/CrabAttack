#include <stdio.h>
#include <stdlib.h>

#include "image.h"


int newImage(Image *image, unsigned int width, unsigned int height)
{
  // allocation mémoire
  image->data = (unsigned char*) malloc(sizeof(unsigned char) * 3 * width * height);
  if(image->data == NULL){
    printf("newImage : error bad memory allocation.\n");
    return EXIT_FAILURE;
  }

  // définit largeur et hauteur
  image->width  = width;
  image->height = height;

  return EXIT_SUCCESS;
}



void freeImage(Image *image)
{
  if(image != NULL) {
    if(image->data != NULL)	{
	    free(image->data);
      image->data= NULL;
    }

    image->width  = 0;
    image->height = 0;
	}
}



int saveImagePPM(Image *image, char *filename)
{
  // ouvre le fichier
  FILE *myfile;
  myfile = fopen(filename,"wt");

  // sauvegarde les données
  if (myfile)
  {
    // génère l'entete
    char header[100]; 
    sprintf(header,"P6\n\n%d %d\n255\n",image->width,image->height);
    fprintf(myfile,"%s",header);

    // écrit les données
    fwrite(image->data,sizeof(unsigned char),image->width*image->height*3,myfile);

    // fermer le fichier
    fclose(myfile);
  }
  else
  {
    printf("saveImagePPM : error opening file %s.\n",filename);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}



// lire que les P6
int loadImagePPM(Image *image, char *filename)
{
  FILE *myFile = NULL;
  char chaine[255];
  unsigned int width,height;

  // ouvre le fichier
  if (!(myFile = fopen(filename, "rt")))
    {
      printf("loadImagePPM : error opening file %s.\n",filename);
      return EXIT_FAILURE;
    }

  // lit l'entete
  fscanf(myFile,"%s\n",chaine);

  // lit les commentaires
  do{ 
    fgets(chaine,255,myFile);
  } while (chaine[0]=='#');
  
  // lit la largeur et la longueur
  sscanf(chaine,"%d %d",&width,&height);

  // lit le "255"
  fscanf(myFile,"%s\n",chaine);

  // allocation mémoire
  if(newImage(image,width,height) == EXIT_FAILURE){
    printf("loadImagePPM : memory allocation error\n");
    return EXIT_FAILURE;
  }

  // lit les données
  fread(image->data, sizeof (unsigned char), width*height * 3, myFile);

  // ferme le fichier
  fclose(myFile);

  return EXIT_SUCCESS;
}