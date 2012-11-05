/*
 * levenshtein.c
 * This file is part of Algorithms 2012
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Algorithms 2012 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Algorithms 2012 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Algorithms 2012. If not, see <http://www.gnu.org/licenses/>.
 */

#include "levenshtein.h"

#define GT(t,i,j) t[(i)+(j)*(l)]
#define Min(a,b,c) min(min((a),(b)),(c))

int levenshtein(char*w1,char*w2){
	int i,j;
	int l=strlen(w1)+1,l2=strlen(w2)+1;
	int*table=calloc(1,sizeof(int)*(l)*(l2));
	int cost;

	if (table==NULL) {
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	for (i=0;i<l;i+=1) GT(table,i,0)=i;
	for (i=0;i<l2;i+=1) GT(table,0,i)=i;
	
	for (i=1;i<l;i+=1) for (j=1;j<l2;j+=1){
		cost=(w1[i-1]==w2[j-1])?0:1;
		GT(table,i,j)=Min(GT(table,i,j-1)+1,GT(table,i-1,j)+1,(GT(table,i-1,j-1)+cost));
	}
	
	cost=GT(table,i-1,j-1);
	free(table);
	return cost;
}

#undef GT
#undef Min
