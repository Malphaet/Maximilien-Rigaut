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

char**ten_bests(char*word,lclist**tuples,lclist**hashd){
	char tuple[4]={0,0,0,0},*news;
	unsigned int i,j,max,hash,*nbmatching,val,max2;
	lclist**suggests;		/* Value that each tuple suggests */
	lclist*node;
/*	lclist*qualified=make_lclist();*/
	char**bests;
	
	max=strlen(word);
	news=calloc(max+3,sizeof(char));
	suggests=calloc(max,sizeof(lclist*));
	bests=calloc(11,sizeof(char*));
	nbmatching=calloc(HASH_DSIZ,sizeof(unsigned int));
	
	if (!news) ERROR("Malloc new word");
	if (!suggests) ERROR("Malloc suggestion list");
	if (!bests) ERROR("Malloc result list");
	if (!nbmatching) ERROR("Malloc number of matching tuples");
	
	/* Check into the dictionnary for existence */
	node=hashd[jhash(word)];
	if (node) while ((node=node->next)!=NULL) if (strcmp(word,node->data)==0){
		bests[0]=node->data;
		printf("Sending %s\n",node->data);
		return bests;
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
	for (i=0;i<max;i+=1){
		node=suggests[i];
		if (node) while((node=node->next)!=NULL) nbmatching[jhash(node->data)]++;
	}
	
	/* Extract best suggestions */
	for (i=0;i<HASH_DSIZ;i+=1){
		if (nbmatching[i]) {
			/* Collisions may occur, however levenshtein will take care of that */
			node=hashd[i];
			while ((node=node->next)!=NULL) {
				max2=strlen(node->data);
				if (((nbmatching[i]*10)/(max+max2-nbmatching[i]))>2){
					val=100-(100*levenshtein(node->data,word))/(1+(max>max2?max:max2));
					if ((100*levenshtein(node->data,word))/(1+(max>max2?max:max2))>100) 
						printf("WTF %s %s %d %d\n",node->data,word,levenshtein(word,node->data),1+(max>max2?max:max2));
					if (val<101) bests[10-(val/10)]=node->data;
					else printf("%s sounds weird (%d)\n",node->data,val);
				}
			}
		}
	}
	
	
	free(news);
/*	drop_lclist(qualified);*/
	free(suggests);
	return bests;
}


#define GT(t,i,j) t[(i)+(j)*(l)]
/** The levenshtein function
 * Made to understand unicode characters
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
	return cost;
}
#undef GT

/** Hash the given word according to the java string hash function
 * This function returns a HASH_SIZE bytes checksum
 *
 * ##Experimental measures
 * ### Scattering
 * + The XORing give a ±70% scattering variation.
 * + The modulus gives a ±150% scattering variation.
 * The goal being a 0% scattering variation (that is to say, a perfectly uniform hash function).
 * ### Speed
 * The XORing runs 17% faster in average than the modulus function.
 * ### Collisions
 * Hashing a word dictionnary the XOR function 
 */
unsigned int jhash(const char*word){
	unsigned int i,hash=0,l=strlen(word),finalhash=-1,mask=-1;
	for (i=0;i<l;i++) hash=((hash<<HASH_POWR)-hash+(unsigned int)word[i])%HASH_DSIZ;
	
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
	
	while(0<fscanf(f,"%[^\n]\n",str)){
		/* Calculate hash */
		hashdict_addword(hashd,jhash(str),str,0);
	}
	fclose(f);
		
	return hashd;
}

/** Build the 3-tuple dictionnary*/
lclist**build_3tupledict(char*path){
	FILE*f;
	lclist**tupled;
	char str[200],tuple[4]={0,0,0,0},*news;
	unsigned int i,j,max,hash;
	
	/* Three chars of 8 bits can store up to 16777215 variables */
	if ((f=fopen(path,"r"))==NULL) ERROR("Opening file error");
	tupled=calloc(HASH_DSIZ,sizeof(lclist*));
	if (!tupled) ERROR("Malloc tuple table");
	
	strcpy(str,path);
	while(0<fscanf(f,"%[^\n]\n",str)){
		max=strlen(str);
		news=calloc(max+3,sizeof(char));
		strcpy(news+1,str);
		news[0]='$';news[max+1]='$';
		
		for (i=0;i<max;i+=1){
			for (j=0;j<3;j+=1) tuple[j]=news[i+j];
			hash=jhash(tuple);
			hashdict_addword(tupled,hash,str,1);
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
 * @param careless Check if collisions are genuine
 * This function works in a very particular fashion, 
 * in the way that is doesn't calculate the hash and solve the collision,
 * but relie on the calling function to provide the tools for it
 */
void hashdict_addword(lclist**hashd,unsigned int hash,char*str,int careless){
	char *sve_str;
	unsigned int max=strlen(str);
	lclist*node,*new_node,*old_node;
	
	/* Either the hash generate collision */
	old_node=node=hashd[hash];
	if (node) {
		/* If the hash is already present, skip it */
		if (!careless) while ((node=node->next)!=NULL) {old_node=node; if (strcmp(node->data,str)==0) return;}
	/* Either it doesn't */
	} else hashd[hash]=old_node=make_lclist();
	
	/* Create new node */
	sve_str=malloc(sizeof(char)*(max+1));
	if (!sve_str) ERROR("Malloc index string");
	
	/* Add the string to the list */
	strcpy(sve_str,str);
	if (careless) add_lclist(old_node,sve_str);
	else{
		new_node=malloc(sizeof(lclist));		if (!new_node) ERROR("Malloc new node");
		new_node->data=sve_str;
		new_node->next=NULL;
		old_node->next=new_node;
	}

}

/** Check if the string is in the hashed values */
int hashdict_in(lclist**hashd,char*str){
	lclist*node;
	unsigned int hash=jhash(str);
	if (!(node=hashd[hash])) return 0;
	
	while((node=node->next)!=NULL) if (strcmp(node->data,str)) return 1;
	return 0;
}

int strheq(const char*w1,const char*w2){
	return jhash(w1)!=jhash(w2);
}
