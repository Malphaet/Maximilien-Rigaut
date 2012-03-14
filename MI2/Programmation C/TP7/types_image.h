/*
 * types_image.h
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



#ifndef __TYPES_IMAGE__
#define __TYPES_IMAGE__

/* ========= Includes =========*/

/* ========= Defines ==========*/

#define INTENSITY_MAX 255

/* ========= Typedef ==========*/

typedef struct image_struct
{
	int width;
	int height;
	float *pixels;
} Image;


/* ======== Prototype =========*/

#endif
