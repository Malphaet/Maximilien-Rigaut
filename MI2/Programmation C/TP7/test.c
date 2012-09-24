/*
 * test.c
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
#include "types_image.h"
#include "image_utils.h"	/* Tested */
#include "image_effects.h"	/* Tested */
#include "image_io.h" 		/* Tested */


/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	Image *image=pgm_read("test.pgm");
	Image *image2=copy_image(image);
	Image *effect_image;
	free_image(image);
	pgm_write("image.pgm",image2);
	/*printf("(%d,%d)=>(%d)=>(%d,%d)\n",4,5,sub2ind(4,5,10),ind2col(54,10),ind2row(54,10));*/
	print_image(image2,10,10);

	printf("Effect:binarization(0.5)\n");
		effect_image=copy_image(image2);
		effect_binarization(effect_image,0.5);
		print_image(effect_image,-1,-1);
	printf("Effect:binarization(0.7)\n");
		effect_image=copy_image(image2);
		effect_binarization(effect_image,0.7);
		print_image(effect_image,-1,-1);
	printf("Effect:negative\n");
		effect_image=copy_image(image2);
		effect_negative(effect_image);
		print_image(effect_image,-1,-1);
	printf("Effect:noise (50/100)\n");
		effect_image=copy_image(image2);
		effect_noise(effect_image,0.5);
		print_image(effect_image,-1,-1);
	printf("Effect:noise (20/100)\n");
		effect_image=copy_image(image2);
		effect_noise(effect_image,0.2);
		print_image(effect_image,-1,-1);
	return 0;
}

/* ========= Functions ========*/

