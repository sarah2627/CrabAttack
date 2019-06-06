#ifndef IMAGE_H__
#define IMAGE_H__

/// \brief structure image
typedef struct Image{
  unsigned char *data;
  unsigned int width;
  unsigned int height;
}Image;


/// \brief alloue une nouvelle image en mémoire.
/// \param image: pointeur sur image.
/// \param width: largeur de l'image.
/// \param height: hauteur de l'image.
/// \return EXIT_FAILURE si problème sinon EXIT_SUCCESS.
int newImage(Image *image, unsigned int width, unsigned int height);

/// \brief libère l'image en mémoire.
/// \param image: pointeur sur image.
void freeImage(Image *image);

/// \brief sauvegarde une image au format PPM P6.
/// \param image: pointeur sur l'image à sauvegarder.
/// \param filename: char chaine de caratère contenant le nom de l'image qu'on veut sauvegarder.
/// \return EXIT_FAILURE si problème sinon EXIT_SUCCESS.
int saveImagePPM(Image *image, char *filename);

/// \brief charge une image au format PPM P6.
/// \param image: pointeur sur l'image à charger.
/// \param filename: char array containing the filename of the image to load.
/// \return EXIT_FAILURE  si problème sinon EXIT_SUCCESS.
int loadImagePPM(Image *image, char *filename);

#endif