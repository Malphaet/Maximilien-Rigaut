/**
 \file image_utils.c
 
 Created by Valentin Emiya on 06/03/12.\n
 Copyright (c) 2012 LIF. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "image_utils.h"

void affiche_image(Image * p_image)
{
    int i,j;
    double valeur_pixel;
    for (i=0; i<p_image->height && i<7; i++)
    {   /* affichage de la ligne i */
        for (j=0; j<p_image->width && j<25; j++)
        {
            /* affichage du pixel à la position [i][j] */
            valeur_pixel = p_image->data[i][j];
            if (valeur_pixel==0)
                printf(" ");
            else if (valeur_pixel==1)
                printf("@");
            else if (valeur_pixel>.5)
                printf("#");
            else
                printf("+");
        }
        printf("\n");
    }
}

void free_image(Image *p_image)
{
    /* On libère l'espace des données (un seul bloc) */
    free(p_image->data[0]);
    
    /* On libère le tableau de pointeurs sur les lignes */
    free(p_image->data);
    
    /* On libère la structure d'image */
    free(p_image);
}

Image *create_image(int width, int height)
{
    double *p_data;
    int i;
    
    /* Allocation de mémoire pour la structure d'image */
    Image *p_image = malloc(sizeof(Image));
    assert(p_image);
    
    /* Définition des champs height et width */
    p_image->height = height;
    p_image->width = width;
    
    /* Allocation de mémoire pour le tableau de pointeur vers les lignes */
    p_image->data = malloc(height*sizeof(double *));
    assert(p_image->data);
    
    /* Allocation de mémoire les données (en un seul bloc) */
    p_data = malloc(height*width*sizeof(double));
    assert(p_data);
    
    /* Initialisation des pointeurs de lignes:
       le début de la ligne i se situe à p_data+décalage de i*width*sizeof(double)  
     */
    for (i=0; i<height; i++)
        p_image->data[i] = p_data+i*width;
    
    return p_image;
}

Image *copy_image(Image *p_image)
{
    int i,j;
    /* Création de l'image en mémoire */
    Image *p_image_res = create_image(p_image->width,p_image->height);
    
    /* Copie du contenu */
    for (i=0; i<p_image->height; i++)
        for (j=0; j<p_image->width; j++)
            p_image_res->data[i][j] = p_image->data[i][j];
    
    return p_image_res;
}

