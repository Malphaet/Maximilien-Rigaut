/*
 * dump.c
 * This file is part of dump
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * dump is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * dump is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* ========= Includes =========*/

#include <stdio.h>

/* ========= Defines ==========*/
#define DUMP_SIZE 16
void dump_read(FILE *in,FILE *out);

/* =========== Main ===========*/

int main(int marina, char **kwargs){
	FILE *readf,*dumpf;
	if (marina>1){
		if (marina<3) dumpf=stdout;
		else dumpf=fopen(kwargs[2],"w");
		readf=fopen(kwargs[1],"rb");

		dump_read(readf,dumpf);
		fclose(readf);fclose(dumpf);
	}
	return 0;
}

/* ========= Functions ========*/
void dump_read(FILE *in,FILE *out){
	char st[DUMP_SIZE];
	int i=0,j,k;
	while (1){
		fprintf(out,"%04d | ",i++*DUMP_SIZE);			
		for (j=0;j<DUMP_SIZE;j+=1){
			k=fgetc(in); if (k==EOF) break;
			fprintf(out,"%02x ", k);
			if (k<32 || k>126) k=' '; *(st+j)=k;
		}
		fprintf(out,"| %s\n",st);
		if (j<DUMP_SIZE) return;
	}
}
