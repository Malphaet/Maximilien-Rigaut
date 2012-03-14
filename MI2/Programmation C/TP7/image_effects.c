/*
 * image_effects.c
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
#include <time.h>
#include "image_effects.h"
#include "utils.h"
#include "image_utils.h"
#include "types_image.h"

/* ========= Defines ==========*/

/* ========= Functions ========*/

void effect_binarization(Image *image){
	int i,j;
	float val;
	for (i=0;i<image->width;i+=1)
		for (j=0;j<image->height;j+=1){
			val=*(image->pixels+sub2ind(i,j,image->width));
			val=val>0.5?1:0;
		}
}

void effect_negative(Image *image){
	int i,j;
	float val;
	for (i=0;i<image->width;i+=1)
		for (j=0;j<image->height;j+=1){
			val=*(image->pixels+sub2ind(i,j,image->width));
			val=1-val;
		}
}

void effect_noise(Image *image, int level){
	int i,j;
	srand(time(NULL));
	for (i=0;i<image->width;i+=1)
		for (j=0;j<image->height;j+=1)
			if (rand()%level) *(image->pixels+sub2ind(i,j,image->width))=0;
}
