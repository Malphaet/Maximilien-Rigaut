/*
 * corrector.c
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

#include "corrector.h"


int main (int argc, char *argv[]){
	FILE*f;
	int nb=6;
	int res;
	char str[100],bests[100];
	if (argc<3) OUT("Usage: corrector <word> <dico>");
	
	f=fopen(argv[2],"r");
	while(0<fscanf(f,"%s\n",str)){
		res=levenshtein(argv[1],str);
		if (res<=nb){
			nb=res;
			printf("%d %d %s\n",nb,res,str);
			strcpy(bests,str);
		}
	}
	printf("Best match %s %d\n",bests,nb);
	fclose(f);
	return 0;
}
