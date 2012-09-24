/**
 \file image_types.h
 \brief Types définis pour les images générales.
 
 Created by Valentin Emiya on 06/03/12.\n
 Copyright (c) 2012 LIF. All rights reserved.
*/

#ifndef _image_types_h
#define _image_types_h

/** La structure image sert à stocker une image comme une matrice de double compris entre 0 et 1. */
typedef struct {
    /** Largeur de l'image */
    int width;
    /** Hauteur de l'image */
    int height;
    /** Données ASCII de l'image: un tableau de pointeurs vers chaque ligne de l'image */
    double **data;
} Image;

#endif
