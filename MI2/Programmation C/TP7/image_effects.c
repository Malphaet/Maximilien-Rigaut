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
#define im(i,j) *(image->pixels+sub2ind((i),(j),image->width))
/* ========= Functions ========*/

void effect_binarization(Image *image,float threshold){
	int i,j;
	if (threshold<-1||threshold>1) threshold=0.5;
	for (i=0;i<image->width;i+=1)
		for (j=0;j<image->height;j+=1)
			im(i,j)=(im(i,j)>threshold)?1:0;
}

void effect_negative(Image *image){
	int i,j;
	for (i=0;i<image->width;i+=1)
		for (j=0;j<image->height;j+=1)
			im(i,j)=1-im(i,j);
}

void effect_noise(Image *image, float percent){
	int i,j;
	int level=(int)(percent*100);
	srand(time(NULL));
	for (i=0;i<image->width;i+=1)
		for (j=0;j<image->height;j+=1)
			if ((rand()%100)<level) im(i,j)=0;
}
#undef im
