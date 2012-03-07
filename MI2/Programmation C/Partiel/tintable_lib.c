/*
 * tintable_lib.c
 * This file is part of Tintable
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Tintable is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Tintable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */



/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "tintable_lib.h"
#include "utils.h"


/* ========= Defines ==========*/

/* ========= Functions ========*/

tintype tintable(int *table,int n){
	tintype u=malloc((n+1)/2); tintype r=u; TEST(u);
	if (n%2) *(u+n/2)=*(table+n);
	n>>=1;
	while (n--) *u++=(*table++<<4)+*(table+++1);
	return r;
}

void print_tintable(tintype table,int n){
	char a,b;
	while (n--){
		a=*table>>4; b=*table-(a<<4);
		/*printf("%s=(%s,%s)\n",bytemap(*table),bytemap(a),bytemap(b));*/
		printf("%i=(%i,%i)\n",*table,a,b); table++;
	}
}

char *bytemap(int x){
	int i;
	char *u=malloc(10); char *r=u; TEST(r);
	for (i=0;i<8;i++){
		if (x & 0x80) *u++='1';
		else *u++='0';
		if (i==3) *u++=' ';
		x<<=1;
	}
	*u='\0';
	return r;
}
