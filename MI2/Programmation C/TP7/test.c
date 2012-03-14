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
#include "image_utils.h"
#include "image_io.h"


/* ========= Defines ==========*/

/* =========== Main ===========*/

int main(void){
	Image *image=pgm_read("test.pgm");
	pgm_write("image.pgm",image);
	return 0;
}

/* ========= Functions ========*/

