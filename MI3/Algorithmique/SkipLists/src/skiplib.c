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

// PROTOTYPE


// PRIVATE FUNCTIONS

// Doc and test
SkipList*sk_create(double percent){
	SkipList*s=malloc(sizeof(SkipList));
	if(!s) ERROR("Malloc error");
	s->insertPoint=malloc(32*sizeof(sk_node*));
	if(!s->insertPoint) ERROR("Malloc error");
	
	s->level=0; s->percent=percent; s->size=0;
	s->head=s->insertPoint[0];
	
	// We'll need a random generator, it's a good idea to initialise it at some point
	srand(time(NULL));
	return s;
}

// Doc and test
sk_node*sk_find_last(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	sk_node*last_node=l->head;
	int res,lvl=l->level;
	while (lvl>=0){
		res=key_compare(last_node,key);
		if (res==0) return last_node;
		if (res<0) {
			if (last_node->next[lvl]==NULL) return last_node;
			last_node=last_node->next[lvl];
			continue;
		}
		if (!l->level) return last_node;
		last_node=last_node->next[lvl--];
	}
	return last_node;
}

// MAIN FUNCTIONS

int sk_contains(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	/* If the last element before they key is the key itself, the list contains, else it aint*/
	return key_compare(sk_find_last(l,key,key_compare),key)==0;
}

void sk_add(SkipList*l,t_key key,int key_compare(t_key,t_key),void post_actions(sk_node*,t_key)){
	//Find the position it should be, if exist, do nothing, if it doesn't: add it?
	
	// Initalise the new node
	int i=0,lvl=l->level,size=0;
	sk_node*n=malloc(sizeof(sk_node));
	sk_node*last_node=l->head,*tmp_node;
	if (!n) ERROR("Malloc error");
	
	// Randomly generate the size
	for(i=0;i<32;i++) while (rand()%2) size++;
	n->next=malloc(sizeof(sk_node*)*size);
	while (lvl>0){
		i=key_compare(last_node,key);
		if (i==0) {
			post_actions(last_node,key);
			free(n->next); free(n);
			return;
		}
		if (i<0) n->next[lvl]=last_node; // Let's suppose that it's the last linking possible
		else {
			tmp_node=n->next[lvl];
			n->next[lvl]=tmp_node->next[lvl];
			tmp_node->next[lvl]=n;
			lvl--;
		}
	}
	while (l->level<size) l->insertPoint[l->level++]=n;
}


void sk_remove(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	sk_node*last_node=sk_find_last(l,key,key_compare);
	// Find all nodes that link to it, and skip it, then free the memory
	if (key_compare(last_node,key)==0) {
		
	} else return;
}

void*sk_tolist(SkipList*l){
	l++;
	return NULL;
}

char*sk_tostring(SkipList*l,char*key_to_str(t_key)){
	l++;
	return key_to_str(NULL);
}


// INT FUNCTIONS
// CHAR FUNCTIONS
