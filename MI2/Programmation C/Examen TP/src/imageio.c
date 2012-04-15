/**
 \file imageio.c
 
 Created by Valentin Emiya on 06/03/12.\n
 Copyright (c) 2012 LIF. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "imageio.h"
#include "image_utils.h"

Image * pgm_read(char * filename)
{
    int i,j,valeur_pixel; /* i=indice de ligne, j=indice de colonne */
    Image *p_image;
    int magic_number;
    int max, width, height;
    FILE *fid = fopen(filename,"r"); /* Ouverture du fichier */
    assert(fid);
    
    /* Lecture de l'en-tête */
    fscanf(fid,"P%d",&magic_number); /* nombre magique */
    fscanf(fid,"%d",&width); /* Largeur de l'image (codée en caractères ASCII) */
    fscanf(fid,"%d",&height); /* Hauteur de l'image (codée en caractères ASCII) */
    fscanf(fid,"%d",&max); /* La valeur maximale utilisée pour coder les niveaux de gris */

    /* Lit les données de l'image (en ASCII) ligne par ligne (for sur la hauteur en 1er) */
    p_image = create_image(width,height);
    for (i=0; i<height; i++)
        for (j=0; j<width; j++)
        {
            fscanf(fid,"%d",&valeur_pixel);
            p_image->data[i][j] = ((double) valeur_pixel)/max;
        }
    
    /* fermeture du fichier */
    fclose(fid);
    return p_image;
}

 void pgm_write(char * filename, Image *p_image, int max)
{
    int i,j, magic_number=2; /* i=indice de ligne, j=indice de colonne */
    FILE *fid = fopen(filename,"w");
    assert(fid);
    
    /* Ecriture de l'en-tête */
    fprintf(fid,"P%d\n",magic_number); /* nombre magique */
    fprintf(fid,"%d ",p_image->width); /* Largeur de l'image (codée en caractères ASCII) */
    fprintf(fid,"%d\n",p_image->height); /* Hauteur de l'image (codée en caractères ASCII) */
    fprintf(fid,"%d\n",max); /* La valeur maximale utilisée pour coder les niveaux de gris */
    
    /* Ecrit les données au format ASCII, ligne par ligne */
    for (i=0; i<p_image->height; i++)
    {
        for (j=0; j<p_image->width; j++)
        {
            fprintf(fid,"%d ",(int) (p_image->data[i][j]*max));
        }
        fprintf(fid,"\n");
    }
    
    /* fermeture du fichier */
    fclose(fid);
}

