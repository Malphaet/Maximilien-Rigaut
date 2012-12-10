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

#define GT(t,i,j) t[(i)+(j)*(l)] /**< Acess to element t[i,j] */
/** The levenshtein function
 * Note that the function return the ponderated levenshtein function with 2 digits precision.
 * @param w1,w2 The words to compare
 * @return the distance, in permutation and additions/deletion between the two words aka the levenshtein distance
 */
unsigned int levenshtein(char*w1,char*w2){
	int cost,i=1,j=1,w_i=0,w_j=0;
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
	return (100*(cost))/(1+(l>l2?l:l2));
}
#undef GT

/** Hash the given word according to the java string hash function
 * @param word The word to hash
 * @param hash_size Size of the hash (in bits)
 
 * @return The unsigned int of the hash
 */
unsigned int jhash_char(const char*word,int hash_size){
	unsigned int hash=0,finalhash=-1,mask=-1;
	const char*letter=word;
	while (*letter!=0) hash=((hash<<HASH_POWR)-hash+(unsigned int)*(letter++));
	
	/* Strip the checksum (Here some XORing for entropy purposes) */
	mask=mask>>(sizeof(int)*8-hash_size);
	do{
		finalhash=(finalhash^hash)&mask;
		hash=hash<<hash_size;
	} while(hash);

	return finalhash;
}

/** Build the hash dictionnary of the file at the given path */
lclist**build_hashdict(char*path){
	FILE*f;
	lclist**hashd;
	char str[200];

	if ((f=fopen(path,"r"))==NULL) ERROR("Opening file error");
	hashd=calloc(HASH_DSIZ,sizeof(lclist*)); if (!hashd) ERROR("Malloc hash table");
	
	while(0<fscanf(f,"%[^\n]\n",str)){
		/* Calculate hash */
		hashdict_addword(hashd,jhash(str),str,0,strlen(str));
	}
	fclose(f);
		
	return hashd;
}

/** Build the 3-tuple dictionnary */
lclist**build_3tupledict(char*path){
	FILE*f;
	lclist**tupled;
	char str[200],tuple[4]={0,0,0,0};
	char*news;
	unsigned int i,j,max,hash;
	
	/* Three chars of 8 bits can store up to 16777215 variables */
	if ((f=fopen(path,"r"))==NULL) ERROR("Opening file error");
	if (!(tupled=calloc(HASH_DSIZ,sizeof(lclist*))))ERROR("Malloc tuple table");
	
	while(0<fscanf(f,"%[^\n]\n",str)){
		max=strlen(str);
		news=calloc(max+3,sizeof(char));
		strcpy(news+1,str);
		news[0]='$';news[max+1]='$';
		
		for (i=0;i<max;i+=1){
			for (j=0;j<3;j+=1) tuple[j]=news[i+j];
			hash=jhash(tuple);
			hashdict_addword(tupled,hash,str,1,max);
		}
		free(news);
	}
	fclose(f);
		
	return tupled;
}

/** Add a word to a dictionnary
 * @param hashd The hash dictionnary (a chained list)
 * @param hash The hash of the given object
 * @param str The object hashed, to store if unique
 * @param subhash Check if collisions are genuine
 * This function works in a very particular fashion, 
 * in the way that is doesn't calculate the hash and solve the collision,
 * but relie on the calling function to provide the tools for it.
 */
void hashdict_addword(lclist**hashd,unsigned int hash,char*str,int subhash,unsigned int max){
	char *sve_str;
	//unsigned int max=strlen(str);
	lclist*node,*new_node,*old_node;
	
	old_node=node=hashd[hash];
	/* Either the hash generate collision */
	if (node) {
		/* If the hash is already present, skip it */
		/** @todo Find a better redondency check */
		if (!subhash) while ((node=node->next)!=NULL) {old_node=node; if (strcmp((char*)node->data,str)==0) return;}
	/* Either it doesn't */
	} else hashd[hash]=old_node=make_lclist();
	
	/* Create new node */
	sve_str=malloc(sizeof(char)*(max+1)); if (!sve_str) ERROR("Malloc index string");
	
	/* Add the string to the list */
	strcpy(sve_str,str);
	if (subhash) add_lclist(old_node,(void*)sve_str);
	else{
		new_node=malloc(sizeof(lclist));	if (!new_node) ERROR("Malloc new node");
		new_node->data=(void*)sve_str;
		new_node->next=NULL;
		old_node->next=new_node;
	}
}

/** Check if the string is in the hashed values 
 * @param hashd The hash dictionnary
 * @param str The string to look for in the dictionnary
 * @return true if the word is in false otherwise */
int hashdict_in(lclist**hashd,char*str){
	lclist*node;
	unsigned int hash=jhash(str);
	if (!(node=hashd[hash])) return 0;
	
	while((node=node->next)!=NULL) if (strcmp((char*)node->data,str)) return 1;
	return 0;
}

/** Compare the jhash function between two strings 
 * @param w1,w2 The words to compare
 * @return 1 if differents 0 if equal (for conformity purpose with strcmp) */
int strheq(const char*w1,const char*w2){
	return jhash(w1)!=jhash(w2);
}
