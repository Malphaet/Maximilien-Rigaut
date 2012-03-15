/*
 * image_io.c
 * This file is part of TP7
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP7 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP7 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "image_utils.h"
#include "types_image.h"


/* ========= Defines ==========*/
 
/* ========= Functions ========*/

Image *pgm_read(char *nom){
	FILE *file=fopen(nom,"r");
	Image *image; int width,height,max_intens,val,i,j;
	fscanf(file,"P2 %d %d %d",&width,&height,&max_intens);
	image=create_image(width,height);
	for (i=0;i<width;i+=1)
		for (j=0;j<height;j+=1){
			fscanf(file,"%d ",&val);
			*(image->pixels+sub2ind(i,j,width))=(float) val/max_intens;
		}
	fclose(file);
	return image;
}

void pgm_write(char* nom,Image* image){
	FILE *file=fopen(nom,"w");
	int i,j;
	fprintf(file,"P2 %d %d %d\n",image->width,image->height,INTENSITY_MAX);
	for (i=0;i<image->height;i+=1){
		for (j=0;j<image->width;j+=1)
			fprintf(file,"%d ",(int) (INTENSITY_MAX**(image->pixels+sub2ind(i,j,image->width))));
		fprintf(file,"\n");
	}
	fclose(file);
}

char colors[]={5,' ','+','%','#','@'};
char color(float value){
	if (value==1) return *(colors+*colors);
	return *(colors + (int) (value**colors)+1);
}

void print_image(Image* image,int maxw,int maxh){
	int i,j;
	if (maxh<0) maxh=image->height;
	if (maxw<0) maxw=image->width;
	for (i=0;i<maxw;i+=1){
		for (j=0;j<maxh;j+=1)
			printf("%c ",color(*(image->pixels+sub2ind(i,j,image->width))));
		printf("\n");
	}
}
