/*
//  temperature.c
//  
//
//  Created by Valentin Emiya on 15/04/12.
//  Modified by Maximilien Rigaut 16/04/12.
//  Copyright (c) 2012 LIF. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image_types.h"
#include "imageio.h"
#include "image_utils.h"
#include "assert.h"
#include "temperature.h"

/* Fonctions de la partie 1 */
double moyenne_temperature(Image *p_image)
{
    int i,j;
    double moyenne=0;
    for (i=0;i<p_image->height;i+=1)
    	for (j=0;j<p_image->width;j+=1)
    		moyenne+=p_image->data[i][j];
    return moyenne/(p_image->width*p_image->height);
}

#define SQR(a) ((a)*(a))
double ecart_type_temperature(Image *p_image)
{
    int i,j;
    double ecart_type=0,moyenne=moyenne_temperature(p_image);
    for (i=0;i<p_image->height;i+=1)
    	for (j=0;j<p_image->width;j+=1)
    		ecart_type+=SQR(p_image->data[i][j]-moyenne);
    return sqrt(ecart_type/(p_image->width*p_image->height));
}

Stat_Temperature *stat_temperature(Image *p_image)
{
	Stat_Temperature *stat=malloc(sizeof(Stat_Temperature));
	if (!stat) exit(EXIT_FAILURE);
	stat->moyenne=moyenne_temperature(p_image);
	stat->ecart_type=ecart_type_temperature(p_image);
	return stat;
}

/* Fonctions de la partie 2 */
#define VAL p_image->data[i][j]
double lancer(Image *p_image, int i, int j)
{
	while (!VAL){
		i+=rand()%3-1;
		j+=rand()%3-1;
	}
	return VAL;
}

void estime_temperature(Image *p_image, int nb_lancers)
{
    int k,i=0,j=0;
    double moy;
    for (i=0;i<p_image->height;i+=1)
    	for (j=0;j<p_image->width;j+=1){
    		moy=0;
    		for (k=0;k<nb_lancers;k+=1) moy+=lancer(p_image,i,j);
			p_image->data[i][j]=moy/nb_lancers;
		}
}

/* Fonctions de la partie 3 */

void place_radiateur(Image *p_image){
    /* A MODIFIER */
}


