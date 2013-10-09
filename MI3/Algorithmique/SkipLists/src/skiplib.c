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


// PROTOTYPE


// PRIVATE FUNCTIONS

// Doc and test
SkipList*sk_create(double percent){
	SkipList*s=malloc(sizeof(SkipList));
	if(!s) ERROR("Malloc error");
	s->insertPoint=malloc(32*sizeof(sk_node));
	if(!s->insertPoint) ERROR("Malloc error");
	
	s->level=0; s->percent=percent; s->size=0;
	s->head=s->insertPoint;
	return s;
}

//SkipList*sk_add_node(sk_node*node,t_key*key){

//}

// Doc and test
sk_node*sk_find_last(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	sk_node*last_node=l->head;
	int res;
	while (1){
		res=key_compare(last_node,key);
		if (res==0) return last_node;
		if (res<0) {
			if (last_node->head==NULL) return last_node;
			last_node=last_node->head;
			continue;
		}
		if (!l->level) return last_node;
		last_node=last_node->insertPoint[last_node->level-1];
	} 
}

// MAIN FUNCTIONS

int sk_contains(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	/* If the last element before they key is the key itself, the list contains, else it aint*/
	return key_compare(sk_find_last(l,key),key)==0;
}

void sk_add(SkipList*l,t_key key,int key_compare(t_key,t_key),void post_actions(sk_node,t_key)){
	//Find the position it should be, if exist, do nothing, if it doesn't: add it?
	sk_node*last_node=sk_find_last(l,key);
	if (key_compare(last_node,key)==0) post_actions(last_node,key);
	else {
		// Do the linking adding and creating
	}
}


void sk_remove(SkipList*l,t_key key,int key_compare(t_key,t_key)){
	l++;key=key;
}

void*sk_tolist(SkipList*l){
	l++;
	return NULL;
}

char*sk_tostring(SkipList*l,char*key_to_str(key)){
	l++;
	return "";
}


// INT FUNCTIONS
// CHAR FUNCTIONS
