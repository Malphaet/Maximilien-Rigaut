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

SkipList*sk_create(double percent){
	SkipList*s=malloc(sizeof(SkipList));
	if(!s) ERROR("Malloc error");
	s->insertPoint=malloc(32*sizeof(SkipList));
	if(!s->insertPoint) ERROR("Malloc error");
	
	s->level=0; s->percent=percent; s->size=0;
	s->head=s->insertPoint;
	return s;
}

//Skiplist*sk_find(SkipList*l,void*key,int key_compare(void*,void*)){
	//Find t
//}
int sk_contains(SkipList*l, t_key key, int key_compare(t_key,t_key)){
	l++;
	//Look first item
	//If not, get next (aka, move left, compare, come back and down or poursue, or fail)
	//Return fail or sucess
	return key_compare(key,key);
}

void sk_add(SkipList*l, t_key key){
	//Find the position it should be, if exist, do nothing, if it doesn't: add it?
	l++;key=key;
}

void sk_remove(SkipList*l,t_key key){
	l++;key=key;
}

void*sk_tolist(SkipList*l){
	l++;
	return NULL;
}

char*sk_tostring(SkipList*l){
	l++;
	return "";
}
