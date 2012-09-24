/*
 * image_io.h
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

#ifndef __IMAGE_IO_H__
#define __IMAGE_IO_H__

/* ========= Includes =========*/

/* ========= Defines ==========*/

/* ========= Typedef ==========*/
/* ======== Prototype =========*/
Image *pgm_read(char*);			/* Tested */
void pgm_write(char*,Image*);	/* Tested */
char color(float);					/* Tested */
void print_image(Image*,int,int);	/* Tested */


#endif /* __IMAGE_IO_H__ */
