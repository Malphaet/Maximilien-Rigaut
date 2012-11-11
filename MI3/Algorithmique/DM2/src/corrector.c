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

/* Defines */
#define exec_tests 	printf("Testing hash function\n");\
					test_jhash();\
					printf("Testing hash dict building function\n");\
					test_hashtable();

#ifdef build_tests
	#include "tests.c"
#endif


/* Various correction functions */

/** Print the best match amongst a dictionnary */
char*best_match(char*word,char*path){
	FILE*f;
	int nb=6,res;
	char str[100],*bests=malloc(sizeof(char)*100);
	if (!bests) ERROR("Malloc");
	f=fopen(path,"r");
	while(0<fscanf(f,"%s\n",str)){
		res=levenshtein(word,str);
		if (res<=nb){
			nb=res;
			printf("%d %d %s\n",nb,res,str);
			strcpy(bests,str);
		}
	}
	fclose(f);
	return bests;
}

int main (int argc, char *argv[]){
	if (argc<2) OUT("Usage: corrector <dico>");
	
	#ifdef build_tests
	exec_tests
	#endif
	
/*	binary_print(argv[argc-1]);*/
	build_hashdict(argv[1]);
/*	best_match(argv[1],argv[2]);*/
	return 0;
}
