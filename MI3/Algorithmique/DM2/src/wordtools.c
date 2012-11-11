/*
 * wordtools.c
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

#include "wordtools.h"

#define GT(t,i,j) t[(i)+(j)*(l)]
/** The levenshtein function
 * Made to understand unicode characters
 */
int levenshtein(char*w1,char*w2){
	int cost,i,j,w_i=0,w_j=0;
	u_int32_t w1_val;
	int l=u8_strlen(w1)+1,l2=u8_strlen(w2)+1;
	int*table=calloc(1,sizeof(int)*(l)*(l2));

	if (table==NULL) ERROR("Malloc table");
	for (i=0;i<l;i+=1) GT(table,i,0)=i;
	for (i=0;i<l2;i+=1) GT(table,0,i)=i;
	
	for (i=1;i<l;i+=1) {
		w1_val=u8_nextchar(w1,&w_i);w_j=0;
		for (j=1;j<l2;j+=1){
			cost=w1_val==u8_nextchar(w2,&w_j)?0:1;
			GT(table,i,j)=min3(GT(table,i,j-1)+1,GT(table,i-1,j)+1,(GT(table,i-1,j-1)+cost));
		}
	}
	
	cost=GT(table,i-1,j-1);
	free(table);
	return cost;
}
#undef GT

/** Hash the given word according to the java string hash function
 * This function returns a HASH_SIZE bytes checksum
 *
 * Take note that the XORing give a decrease of 17% in efficency, for an increase of 25% in entropy (experimental measures)
 * The test is 
 */
unsigned int jhash(char*word){
	unsigned int i,hash=0,l=strlen(word),finalhash=-1,mask=-1;
	for (i=0;i<l;i++) hash=(hash<<HASH_POWR)-hash+(unsigned int)word[i];
	
	/* Strip the checksum (Here some XORing for entropy purposes) */
	mask=mask>>(sizeof(int)*8-HASH_SIZE);
	do{
		finalhash=(finalhash^hash)&mask;
		hash=hash<<HASH_SIZE;
	} while(hash);

	return finalhash;
}

/** Build the hash dictionnary of the file at the given path 
 */
lclist**build_hashdict(char*path){
	FILE*f;
	lclist**hashd;
	char str[200];

	if ((f=fopen(path,"r"))==NULL) ERROR("Opening file error");
	hashd=calloc(HASH_DSIZ,sizeof(lclist*));
	if (!hashd) ERROR("Malloc hash table");
	
	while(0<fscanf(f,"%s\n",str)){
		hashdict_addword(hashd,str);
	}
	fclose(f);
		
	return hashd;
}

/** Custom wordsplitting function 
 * Adds all the 3-tuples of the $word$ to the dictionnary 
 */
void hashdict_addword(lclist**hashd,char*str){
	char *sve_str;
	unsigned int hash,max=strlen(str);
	lclist*node;
	
	/* Calculate hash */
	hash=jhash(str);
	
	/* Either the hash generate collision */
	if (hashd[hash]) {
		node=hashd[hash];
		/* If the hash is already present, skip it */
		while ((node=node->next)!=NULL) {if (strcmp(node->data,str)==0) continue;}
	/* Either it doesn't */
	} else hashd[hash]=make_lclist();
	
	/* Add the string to the list */
	sve_str=malloc(sizeof(char)*(max+1));
	if (!sve_str) ERROR("Malloc index string");
	strcpy(sve_str,str);
	add_lclist(hashd[hash],sve_str);
}


int str_eq(char*w1,char*w2){
	while(w1++==w2++) if (!w1|!w2) return 0;
	return 1;
}
