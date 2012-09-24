/*
 * test.c
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

/* =========== Main ===========*/

int main(void){
	dot B=bary("dots.txt");
	FILE *res=fopen("bary.txt","w");
	fprintf(res,"(%f,%f,%f)\n",B.x,B.y,B.z);
	fclose(res);
	return 0;
}
