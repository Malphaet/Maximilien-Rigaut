/*
 * bary.c
 * This file is part of TD7
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TD7 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TD7 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "bary.h"
#include "utils.h"


/* ========= Defines ==========*/

/* ========= Functions ========*/

dot bary(char *stream){
	dot r;
	double X=0,Y=0,Z=0; double x,y,z;
	int number=0;
	FILE *file=fopen(stream,"r");
	while (fscanf(file, " ( %lf , %lf , %lf) ",&x,&y,&z)!=EOF){
		X+=x; Y+=y; Z+=z; number++;
	}
	fclose(file);
	r.x=X/number; r.y=Y/number; r.z=Z/number;
	return r;
}
