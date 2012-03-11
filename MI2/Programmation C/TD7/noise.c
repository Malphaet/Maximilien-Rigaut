/*
 * noise.c
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
#include <time.h>
/* ========= Defines ==========*/
#define WIDTH 1024
#define HEIGHT 777
void noise(int, double M[HEIGHT][WIDTH]);
/* =========== Main ===========*/

int main(void){
	double M[HEIGHT][WIDTH];
	noise(4,M);
	return 0;
}

void noise(int prob, double M[HEIGHT][WIDTH]){
	int i=WIDTH,j=HEIGHT;
	srand(time(NULL));
	while(i--) while (j--) if (rand()%prob) M[i][j]=0;
}
