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

/* Under code small number for size gain and fast memory access */
char *tintable(char *table,char nbits, int nbchars){
	char dec=8/nbits-1;
	char *u=malloc((nbchars+1)>>dec); tintype r=u; TEST(u);
	char temp,i=0;
	/*if (nbchars%nbits) *(u+(nbchars>>nbits))=*(table+nbchars);*/
	nbchars>>=dec;
	for (temp=0;nbchars--;*u++=temp) for (temp=0,i=0;i<(8/nbits);i++) temp+=(*table++<<(i*nbits));
	return r;
}

void print_tintable(char *table,char dsize, int n){
	char a,b;
	while (n--){
		a=*table>>dsize; b=*table-(a<<4);
		/*printf("%s=(%s,%s)\n",bytemap(*table),bytemap(a),bytemap(b));*/
		printf("%i=(%i,%i)\n",*table,a,b); table++;
	}
}

char *bytemap(char x){
	char i;
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
