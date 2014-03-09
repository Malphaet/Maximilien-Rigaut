/*
 * skiplib.c
 * This file is part of Algorithms 2013
 *
 * Copyright (C) 2013 - Maximilien Rigaut
 *
 * Algorithms 2013 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Algorithms 2013 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Algorithms 2013. If not, see <http://www.gnu.org/licenses/>.
 */

#include "skiplib.h"
#include "utils.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"

// PROTOTYPE


// PRIVATE FUNCTIONS

// Create a skiplist
SkipList*sk_create(double percent){
	SkipList*s=malloc(sizeof(SkipList));
	sk_node*n=malloc(sizeof(sk_node));
	if(!s) ERROR("Malloc error");
	if(!n) ERROR("Malloc error");
	
	n->next=calloc(32,sizeof(sk_node*));
	if(!n->next) ERROR("Malloc error");
	
	s->level=-1; s->percent=percent; s->size=0;
	s->head=n;
	printf("Skiplist\n | Percent - %f\n | Id - %p \n | Head - %p\n",percent,(void*)s,(void*)n);
	// We'll need a random generator, it's a good idea to initialise it at some point
	srand((unsigned int)time(NULL));
	return s;
}

// Delete a skiplist and every value assotiated to it
void sk_delete(SkipList*l){
	sk_node*next_node=l->head->next[0],*node;
	while (next_node){
		node=next_node;
		next_node=next_node->next[0];
		free(node->value); free(node->next); free(node);
	}
	free(l->head->next); free(l->head); free(l);
}

// MAIN FUNCTIONS

//* Find if a SkipList contains an element
int sk_contains(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	/* If the last element before they key is the key itself, the list contains, else it aint*/
	sk_node*last_node=l->head;
	int res,lvl=l->level;
	
	while (lvl>=0){
		if (last_node->next[lvl]) {
			res=key_compare(last_node->next[lvl]->value,key);
			if (res==0) return 1;
			if (res<0) {
				last_node=last_node->next[lvl];
				continue;
			}
			// If the next node is after our node and we are level 0, then we found the place
			if (!lvl) return 0; 
		}
		last_node=last_node->next[lvl--];
	}
	return 0;
}


//* Find the position it should be, if exist, do the post actions, else add it
void sk_add(SkipList*l,t_key key,int key_compare(t_key,t_key),void post_actions(sk_node*,t_key)){
	// Initalise the new node
	int i=0,lvl=l->level,size=1;
	sk_node*n=malloc(sizeof(sk_node));
	sk_node*last_node=l->head,*tmp_node;
	if (!n) ERROR("Malloc error");
	
	// Randomly generate the size
	for(i=0;i<32;i++) if (rand()%2) size++; else break;// @Todo use the random percent
	n->next=calloc((size+1),sizeof(sk_node*));
	n->value=key;
	if (!n->next) ERROR("Malloc Error");
	
	printf("Int : %2d {%d}\n",*((int*)n->value),size);
	while (lvl>=0){
		if (last_node->next[lvl]) i=key_compare(key,last_node->next[lvl]->value);
		else {
			if (lvl<size) last_node->next[lvl]=n; lvl--;
			continue;
		}
		if (i==0) { // The node already exist
			post_actions(last_node->next[lvl],key);
			free(n->next); free(n);
			return;
		}
		if (i<0)// The current node is before ours
			last_node=last_node->next[lvl];
		else {	// The current node is after ours
			if (size>=lvl){ // If the node is as hight as the current level, insert it
				printf(" ] %p [%d] -> %p (%d)\n",(void*)last_node,lvl,(void*)last_node->next[lvl],
					*((int*)last_node->next[lvl]->value));
				tmp_node=last_node->next[lvl];
				last_node->next[lvl]=n;
				n->next[lvl]=tmp_node;
				printf(" [ %p [%d] -> %p (%d)\n",(void*)last_node,lvl,(void*)last_node->next[lvl],
					*((int*)last_node->next[lvl]->value));
			}
			lvl--;
		}
	}
	while (l->level<size) {
		l->head->next[++l->level]=n;
		printf(" | %p [%d] -> %p (%d)\n",(void*)l->head,l->level,(void*)n,*((int*)n->value));
	}
	l->size++;
}

// Doc and test
void sk_remove(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	sk_node*last_node=l->head,*node;
	int lvl=l->level; int res;
	
	node=l->head->next[lvl];
	while (lvl>=0){
		if (!node) {lvl--; node=last_node; continue;}
		res=key_compare(node->value,key);
		printf("%d o %d = %d\n",*((int*)node->value),*((int*)key),res);
		
		if (res>0) {last_node=node; node=node->next[lvl];}
		if (res<0) lvl--;
		if (res==0) {
			last_node->next[lvl]=node->next[lvl];
			if (lvl==0) {
				free(node->next); free(node->value); free(node);
				l->size--;
				break;
			}
			node=last_node->next[--lvl];
		}
		
	}
	last_node=l->head; lvl=l->level;
	while (!last_node->next[lvl--]) l->level--;
}

// Doc and test
t_key sk_tolist(SkipList*l){
	t_key*list;int i=0; sk_node*last_node=l->head->next[0];
	
	if (l->size==0) return NULL;
	list=malloc(sizeof(void*)*l->size);
	if (!list) ERROR("Malloc error");
	
	while (last_node!=NULL) list[i++]=(t_key)last_node->value;
	
	return list;
}

// Doc and test
char*sk_tostring(SkipList*l,struct char_size key_to_str(t_key)){
	char**str,*res,*tmp; int size=0,nb=0,i=0; sk_node*last_node=l->head->next[0];
	struct char_size cs;
	
	if (!l->size) return calloc(1,sizeof(char));
	str=malloc(sizeof(char*)*l->size);
	if (!str) ERROR("Malloc error");
	
	while(last_node!=NULL) {
		cs=key_to_str(last_node->value);
		size+=cs.size; str[i++]=cs.txt; nb++;
		last_node=last_node->next[0];
	}
	
	res=malloc(sizeof(char)*(size+nb+1));
	if (!res) ERROR("Malloc Error");
	
	size=0;i=0;
	while(i<nb){
		tmp=str[i];
		do {res[size++]=*tmp++;} while (*tmp);
		free(str[i]); i++; res[size++]=' ';
	}
	
	free(str);
	res[size++]=0;
	return res;
}


void sk_print(SkipList*l){
	int *coupling[2],**table,max_l=0,i;
	sk_node*node=l->head;
	coupling[0]=malloc(sizeof(int)*l->size);
	coupling[1]=malloc(sizeof(int)*l->size);
	table=malloc(sizeof(int*)*l->level);
	for(i=0;i<l->level;i++) table[i]=malloc(sizeof(int)*l->size);
	for(i=0;i<l-size;i++) {
		table[9][i]=node->value;
		coupling[0][i]=node->value;
		coupling[1][i]=i;
		node=node->next;
	}
}

// INT FUNCTIONS
int sk_compint(t_key a,t_key b){
	if (!b|!a) return -1;
	return *((int*)b)-*((int*)a);
}

struct char_size int_to_str(t_key key){
	struct char_size ret;
	int nb=*((int*)key); ret.size=0;
	
	while (nb) {ret.size++; nb/=10;}
	ret.txt=malloc(sizeof(char)*(ret.size+1));
	if (!ret.txt) ERROR("Malloc Error");
	
	sprintf(ret.txt,"%d",*((int*)key));
	return ret;
}

void sk_add_int(SkipList*l,int key){
	int *i=malloc(sizeof(int));
	if (!i) ERROR("Malloc Error");
	*i=key;
	sk_add(l,(t_key) i,sk_compint,sk_no_action);
}

int	sk_contains_int(SkipList*l,int key){
	return sk_contains(l,(t_key)(&key),sk_compint);
}

void sk_remove_int(SkipList*l,int key){
	sk_remove(l,(t_key)(&key),sk_compint);
}

// CHAR FUNCTIONS

int sk_compstr(t_key a,t_key b){
	return strcmp((char*)a,(char*)b)==0;
}

struct char_size char_to_str(t_key key){
	struct char_size ret;
	ret.size=strlen((char*)key);
	ret.txt=malloc(sizeof(char)*(ret.size+1));
	if (!ret.txt) ERROR("Malloc Error");
	
	strcpy(ret.txt,(char*)key);
	return ret;
}

// GENERAL FUNCTIONS
void sk_no_action(sk_node*n,t_key k){
	(void)n;(void)k;
}
