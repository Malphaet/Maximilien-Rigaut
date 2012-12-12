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


#define init_sugg_thread(i,j)	P->vMin=i;\
								P->vMax=j;\
								P->hashd=hashd;\
								P->qualified=qualified;\
								P->found_hashs=found_hashs;\
								P->nbmatching=nbmatching;\
								P->word=word;\
								P->max=max;\
								P->MAX=MAX;

							
/** @file corrector.c Word corrector */
/** @defgroup correctf Correction functions 
 * @brief A handful correction function
 * @{
 */

struct params{
	int vMin;					// Thread dependent
	int vMax;					// Thread dependent
	lclist**hashd; 				// Frozen
	lclist**qualified;			// Mutex protected
	unsigned int*found_hashs;	// Frozen
	int*nbmatching; 			// Frozen
	char*word;					// Frozen
	int max;					// Frozen
	int MAX;					// Frozen
};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void*add_suggestions(void*par){
	struct params*P=(struct params*)par;
	lclist*node;
	int max2,MAX2,val,j;
	unsigned int hash;
	
	#define newW ((char*)node->data) //< The current word
	/* Extract best suggestions */
	for (j=P->vMin;j<P->vMax;j+=1){ 
		/* Assign hash and node. Hash collisions may occur, however levenshtein will take care of that */
		node=P->hashd[hash=P->found_hashs[j]];
		while ((node=node->next)!=NULL) {
			/* Avoid words with error on the first letter, cruel but efficient.
			 * Exception are special first letters (error on hyphens) 
			 *   and h as fisrt letter (not pronounced he sometimes leads to mistakes) */
			if (newW[0]>0 && newW[0]!=P->word[0] && P->word[0]!='h') continue;
			
			alllen(newW,&max2,&MAX2);
			/* Only analyse the guesses who are invert-jacquard-close to the word to correct 
			 * Due to the new nature of ::nbmatching, it became necessary to invert the jacquard distance to avoid 0 div error */
			if ((((P->max+max2-(P->nbmatching[hash])))/(P->nbmatching[hash]+1))<6){
				/* Calculate the ponderated levenshtein distance */
				val=(val=levenshtein(newW,P->word,MAX2+1,P->MAX+1)+P->max-P->nbmatching[hash])>0?val:0;
				/* Add the guess to results if close enough to the initial word */
				pthread_mutex_lock(&mutex);
				if (val<ERROR_LIMIT){
					if (!P->qualified[val]) P->qualified[val]=make_lclist();
					add_lclist(P->qualified[val],newW);
				}
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	return NULL;
}


/** Find the ten best correction guesses for the given word
 * @todo Make the function Leak free
 * @param word The word to correct
 * @param tuples The tuples hashes 
 * @param hashd The dictionnary hash 
 * @return The list of the ten (or less) best guesses
 */
char**ten_bests(char*word,lclist**tuples,lclist**hashd){
	char tuple[4]={0,0,0,0},*news,**bests;
	unsigned int hash,*found_hashs;
	int *nbmatching,max=0,max2=0,MAX=0,MAX2=0,i,j=1,founds=0,k=0,l=0,val;
	lclist**suggests,**tweaks;		/* Value that each tuple suggests */
	lclist**qualified,*node;
	struct params*P;
	pthread_t thread_id[MAX_THREADS];
	
	/* Variable initialisation */
	alllen(word,&max,&MAX);
	news=calloc(max+3,sizeof(char));		if (!news) ERROR("Malloc new word"); //freed
	suggests=calloc(max,sizeof(lclist*));	if (!suggests) ERROR("Malloc suggestion list"); //freed
	tweaks=calloc(max<<4,sizeof(lclist*));	if (!tweaks) ERROR("Malloc tweaks list"); //freed
	bests=calloc(SIZE_LIST+1,sizeof(char*));		if (!bests) ERROR("Malloc result list"); //later freed
	nbmatching=calloc(HASH_DSIZ,sizeof(unsigned int));	if (!nbmatching) ERROR("Malloc number of matching tuples");//freed
	qualified=calloc(101,sizeof(lclist*));	if (!qualified) ERROR("Malloc qualified words"); //freed
	found_hashs=malloc(705600*sizeof(unsigned int)); if (!found_hashs) ERROR("Malloc found hashes"); //freed
	
	/* Check into the dictionnary for existence */
	node=hashd[jhash(word)];
	if (node) while ((node=node->next)!=NULL) if (strcmp(word,(char*)node->data)==0){
		bests[0]=(char*)node->data; j=1; //bests[1]=NULL;
		goto finish;
	}
	
	/* Analyse the tuples */
	strcpy(news+1,word);
	news[0]='$';news[max+1]='$';
	
	#define t(i)	tuple[i] 							//< The i-th letter of the tuple
	#define w(j)	news[i+j]							//< The i-th letter of the current word
	#define S(j) 	substitutions[0][1][j]				//< The j-th letter to substitute to
	#define s(j) 	substitutions[0][0][j]				//< The j-th letter of the substitution
	#define addtuple	hash=jhash(tuple);\
						suggests[k++]=tuples[hash];		//< Add the current tuple
	#define addtweak	hash=jhash(tuple);\
						tweaks[l++]=tuples[hash];		//< Add the current tweak
					
	for (i=0;i<max;i+=1){
		t(0)=w(0);
		if (w(1)==s(0)) {
			if (w(2)==s(1)){
				t(0)=w(0); t(1)=S(0); t(2)=S(1);
				addtweak;
				t(0)=S(0); t(1)=S(1); t(2)=w(3);
				addtweak;
			}
		}
		t(1)=w(1);
		t(2)=w(2);
		addtuple;
	}
	
	/* Calculate number of matching tuples */
	for (i=0;i<k;i+=1){
		node=suggests[i];
		if (node) while((node=node->next)!=NULL) {
			/* Save the hash, and number of encountering of the given data */
			hash=jhash((char*)node->data); 
			if ((++nbmatching[hash])==1) found_hashs[founds++]=hash;
		}
	}
	for (i=0;i<l;i+=1){
		node=tweaks[i];
		while((node=node->next)!=NULL) {
			/* The special values are weighted a little more, to compensate */
			hash=jhash((char*)node->data);
			if ((nbmatching[hash]+=5)==5) found_hashs[founds++]=hash;
		}
	}
	
	for(i=0;i<MAX_THREADS;i++){
		if (!(P=malloc(sizeof(struct params)))) ERROR("Thread params");
		init_sugg_thread((i*founds/MAX_THREADS),((i+1)*founds/MAX_THREADS));
		pthread_create(&thread_id[i], NULL, add_suggestions, P);
	}
	
	for(j=0;j<MAX_THREADS;j++) pthread_join(thread_id[j], NULL);

	j=0;
	for (i=0;i<ERROR_LIMIT;i++){
		node=qualified[i];
		if (node){ 
			while((node=node->next)!=NULL)	
				if (j<SIZE_LIST) bests[j++]=(char*)node->data; 
				else goto finish; // As soon as the list is full, get out
			drop_lclist(qualified[i]);
		}
	}

	
	/* Clean and exit */
	finish:
		bests[j]=NULL;
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
	printf("   M    F    N\n%3.2f%% %3.2f%% %3.2f%%\n",((float)stats[0]*100)/st,((float)stats[1]*100)/st,((float)stats[2]*100)/st);
	
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
	for (i=0;i<SIZE_LIST;i+=1) {
		if (founds[i]!=NULL) {
			if (strcmp(goal,founds[i])==0){st=(i!=0);break;}
		} else break;
	}
	/* No matchs, display the guesses */
	#ifdef build_tests
	if (st==2) {
		printf("Analysing %s...(%s) led to no match\n",str,goal);
		for (i=0;i<SIZE_LIST;i+=1) if (founds[i])printf("%s ",founds[i]);
		printf("\n");
	}
	#endif
	
	return st;
}
/** @} */

/** Process correction over the given parameters */
int main (int argc, char *argv[]){
	if (argc<3) OUT("Usage: corrector <dictonnary> <mistake file>");

	printf("%s %d\n","œil",jhash("œil"));
	printf("%s %d\n","oeil",jhash("oeil"));

	#ifdef build_tests
		exec_tests
	#endif
	correct_all(argv[1],argv[2]);
	
	return 0;
}
