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
 * @brief A handful correction function
 * @{
 */

/** Find the ten best correction guesses for the given word
 * @todo Make the function Leak free
 * @param word The word to correct
 * @param tuples The tuples hashes 
 * @param hashd The dictionnary hash 
 * @return The list of the ten (or less) best guesses
 */
char**ten_bests(char*word,lclist**tuples,lclist**hashd){
	char tuple[4]={0,0,0,0},*news,**bests;
	unsigned int hash,*nbmatching,val,*found_hashs;
	int max,max2,MAX,MAX2,i,j,founds;
	lclist**suggests;		/* Value that each tuple suggests */
	lclist**qualified,*node;
	
	/* Variable initialisation */
	//max=strlen(word);
	alllen(word,&max,&MAX);
	news=calloc(max+3,sizeof(char));		if (!news) ERROR("Malloc new word"); //freed
	suggests=calloc(max,sizeof(lclist*));	if (!suggests) ERROR("Malloc suggestion list"); //freed
	bests=calloc(11,sizeof(char*));		if (!bests) ERROR("Malloc result list"); //later freed
	nbmatching=calloc(HASH_DSIZ,sizeof(unsigned int));	if (!nbmatching) ERROR("Malloc number of matching tuples");//freed
	qualified=calloc(101,sizeof(lclist*));	if (!qualified) ERROR("Malloc qualified words"); //freed
	found_hashs=malloc(705600*sizeof(unsigned int)); if (!found_hashs) ERROR("Malloc found hashes"); //freed
	
	/* Check into the dictionnary for existence */
	node=hashd[jhash(word)];
	if (node) while ((node=node->next)!=NULL) if (strcmp(word,(char*)node->data)==0){
		bests[0]=(char*)node->data; bests[1]=NULL;
		goto finish;
	}
	
	/* Analyse the tuples */
	strcpy(news+1,word);
	news[0]='$';news[max+1]='$';
	
	for (i=0;i<max;i+=1){
		for (j=0;j<3;j+=1) tuple[j]=news[i+j];
		hash=jhash(tuple);
		suggests[i]=tuples[hash];
	}
	
	/* Calculate number of matching tuples */
	founds=0;
	for (i=0;i<max;i+=1){
		node=suggests[i];
		if (node) while((node=node->next)!=NULL) {
			hash=jhash((char*)node->data);
			if ((++nbmatching[hash])==1) found_hashs[founds++]=hash;
		}
	}
	
	/** Extract best suggestions 
	 *  @todo Make this readable
	 */
	for (j=0;j<founds;j+=1){ 
		/* Collisions may occur, however levenshtein will take care of that */
		hash=found_hashs[j];
		node=hashd[hash];
		while ((node=node->next)!=NULL) {
			/* Avoid words with error on the first letter, cruel but efficient */
			if (((char*)node->data)[0]!=word[0]) continue;
			//max2=strlen((char*)node->data);
			alllen((char*)node->data,&max2,&MAX2);
			/* Only analyse the guesses who are jacquard-close to the word to correct */
			if (((nbmatching[hash]*10)/(max+max2-nbmatching[hash]))>1){
				/* Calculate the ponderated levenshtein distance */
				val=levenshtein((char*)node->data,word,MAX2+1,MAX+1);
				
				/* Add the guess to results */
				if (!qualified[val]) qualified[val]=make_lclist();
				add_lclist(qualified[val],(void*)node->data);
			}
		}
		
	}
	
	j=0;
	for (i=0;i<100;i++){
		node=qualified[i];
		if (node){ 
			while((node=node->next)!=NULL) if (j<10) bests[j++]=(char*)node->data;
			drop_lclist(qualified[i]);
		}
	}
	bests[j]=NULL;
	
	/* Clean and exit */
	finish:
		free(news);
		free(suggests);
		free(nbmatching);
		free(found_hashs);
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
	int stats[3]={0,0,0},st,i;
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
	
	for(i=0;i<HASH_DSIZ;i++) if (hashd[i]) drop_lclist(hashd[i]);
	for(i=0;i<HASH_DSIZ;i++) if (tuples[i]) drop_lclist(tuples[i]);
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
	//if (st==2) {
		//printf("Analysing %s...(%s) led to no match\n",str,goal);
		//for (i=0;i<10;i+=1) if (founds[i])printf("%s ",founds[i]);
		//printf("\n");
	//}
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
