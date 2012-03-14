/*
 * image_utils.c
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
#include "utils.h"


/* ========= Defines ==========*/


/* ========= Functions ========*/

Image *create_image(int width,int height){
	float *table=malloc(sizeof(float)*width*height);
	Image *image=malloc(sizeof(Image));
	P_TEST(image); P_TEST(table);
	image->width=width;
	image->height=height;
	image->pixels=table;
	return image;
}

Image *copy_image(Image* image){
	Image *image_copy=malloc(sizeof(Image));
	float *table_copy=malloc(sizeof(image->width*image->height));
	int size=image->width*image->height,i;
	P_TEST(image_copy);P_TEST(table_copy);
	image_copy->width=image->width;
	image_copy->height=image->height;
	for (i=0;i<size;i+=1) table_copy[i]=image->pixels[i];
	image_copy->pixels=table_copy;
	return image_copy;
}
void free_image(Image *image){
	free(image->pixels);
	free(image);
}

int sub2ind(int i,int j,int width){
	return width*j+i;
}

int ind2row(int k,int width){
	return width/k;
}

int ind2col(int k,int width){
	return k%width;
}

char colors[]={4,'#','%','+',' '};
char color(float value){
	return *(colors + (int) value**colors);
}


