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

#ifdef build_tests
	#include "tests.c"
#endif

/** @file corrector.c Word corrector */
/** @defgroup correctf Correction functions 
 * @{
 */

/** Find the best match amongst a dictionnary
 * @param word The word to correct
 * @param path The dictionnay path
 * @return The best match according to the levenshtein function
 */
char*best_match(char*word,char*path){
	FILE*f;
	int nb=6,res;
	char str[100],*bests=malloc(sizeof(char)*100);
	if (!bests) ERROR("Malloc");
	f=fopen(path,"r");
	while(0<fscanf(f,"%[^\n]\n",str)){
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

/** Correct all word in the given path
 * @param dict The dictionnary adress
 * @param errs The error file adress
 * + Load the words to correct from the given path
 * + Create the necessary structures to proceed due correction
 * + Time and proceed all corrections
 */
void correct_all(char*dict,char*errs){
	FILE*f;
	int stats[3]={0,0,0},st;
	char str[100],goal[100];
	lclist**hashd=build_hashdict(dict);
	lclist**tuples=build_3tupledict(dict);
	TIMER_INIT;
	
	printf("Starting analysis...\n");
	if ((f=fopen(errs,"r"))==NULL) ERROR("Opening file");
	
	TIMER_STRT;
	while ((fscanf(f,"%[^>]>%[^\n]\n",str,goal))>0){
		/* Find bests matches */
		st=correct(str,goal,hashd,tuples);
		stats[st]++;
	}
	/* Display results */
	TIMER_STOP;
	st=stats[0]+stats[1]+stats[2];
	printf("Analysis complete, lasted %ldms.\n%d words were first guess, %d were amongs the guesses and %d weren't found.\n",
	TIMER_USEC/1000,stats[0],stats[1],stats[2]);
	printf("   M    F    N\n%3d%% %3d%% %3d%%\n",stats[0]*100/st,stats[1]*100/st,stats[2]*100/st);
}

/** Find bests corrections for the given string
 * @param str The string to look correction for
 * @param goal The string that should be found
 * @param hashd The hash dictionnary
 * @param tuples The hash dictionnary of tuples
 * 
 * @return The status of the request 0: found 2: not found
 */
int correct(char*str,char*goal,lclist**hashd,lclist**tuples){
	int st,i;
	char**founds;
	
	//printf("Analysing %s...(%s)\n",str,goal);
	founds=ten_bests(str,tuples,hashd);
	
	/* Show the score */
	st=2;
	for (i=0;i<10;i+=1) {
		if (founds[i]!=NULL) {
			if (strcmp(goal,founds[i])==0){st=(i!=0);break;}
		} else break;
	}
	
	/* No matchs, display the guesses */
	#ifdef build_tests
	if (st==2) {
		printf("Analysing %s...(%s) led to no match\n",str,goal);
		for (i=0;i<10;i+=1) if (founds[i])printf("%s ",founds[i]);
		printf("\n");
	}
	#endif
	return st;
}
/** @} */

/** Process correction over the given parameters */
int main (int argc, char *argv[]){
	if (argc<3) OUT("Usage: corrector <dictonnary> <mistake file>");
	
	#ifdef build_tests
		exec_tests
	#endif
	correct_all(argv[1],argv[2]);
	
	return 0;
}
