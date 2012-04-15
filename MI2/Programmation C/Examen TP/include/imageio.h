/**
 \file imageio.h
 \brief Fonctions de lecture/écriture des images.
 
 Format supportés: pgm ASCII.\n
 \n
 Created by Valentin Emiya on 06/03/12.\n
 Copyright (c) 2012 LIF. All rights reserved.
*/

#ifndef _imageio_h
#define _imageio_h

#include "image_types.h"

/**
 \brief Lit une image pgm ASCII
 
 \param filename nom du fichier à lire
 \return pointeur vers la structure d'image
 */
Image * pgm_read(char * filename);

/**
 \brief Ecrit une image au format pgm ASCII
 
 \param filename nom du fichier image à écrire
 \param pointeur vers la structure d'image à écrire
 \param max valeur maximale de niveau de gris à utiliser
 */
void pgm_write(char * filename, Image *p_image, int max);

#endif
