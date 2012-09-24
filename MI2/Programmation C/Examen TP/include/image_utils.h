/**
 \file image_utils.h
 \brief Fonctions utilitaires pour manipuler des images: création, suppression, copie, etc.
 
 Created by Valentin Emiya on 06/03/12.\n
 Copyright (c) 2012 LIF. All rights reserved.
*/

#ifndef _image_utils_h
#define _image_utils_h

#include "image_types.h"

/**
 \brief Affichage rudimentaire d'une image.
 
 Affiche partiellement et en mode ASCII une image.
 \param p_image pointeur vers l'image à afficher
 */
void affiche_image(Image *p_image);

/**
 \brief Libère l'espace mémoire occupé par une image.
 
 \param p_image pointeur vers l'image à supprimer
 */
void free_image(Image *p_image);

/**
 \brief Crée une image.
 
 Crée une structure d'image à partir de ses dimensions, en allouant dynamiquement tout l'espace nécessaire en mémoire.
 \param width largeur (nombre de colonnes)
 \param height hauteur (nombre de lignes)
 \return pointeur vers la structure d'image créée
 */
Image *create_image(int width, int height);

/**
 \brief Copie en profondeur d'une structure d'image
 
 Copie la structure et les données retatives à une image.
 \param pointeur vers la structure d'image à copier
 \return pointeur vers la copie de la structure d'image
 */
Image *copy_image(Image *p_image);

#endif
