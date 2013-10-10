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

#ifndef __SKIPLIB_H__
#define __SKIPLIB_H__

#define t_key void*

typedef struct s_node {
	t_key value;
	struct s_node** next;
} sk_node;

typedef struct s_skip_list {
	struct s_node* head;
	int level; // The max level of skipping
	double percent; // The percentage of elements that will be skipped
	long size; // Size of the SkipList
	/* boolean bool; //???*/
	struct s_node** insertPoint; // Table for methods ???
} SkipList;

/* Prototype */

SkipList*sk_create(double);
sk_node*sk_find_last(SkipList*l,t_key key,int key_compare(t_key,t_key));
int sk_contains(SkipList*l,t_key key,int key_compare(t_key,t_key));
void sk_add(SkipList*l,t_key key,int key_compare(t_key,t_key),void post_actions(sk_node*,t_key));

/*int sk_contains(SkipList*, void*, int key_compare(void*,void*));
void sk_add(SkipList*,void*);
void sk_remove(SkipList*,void*);
void*sk_tolist(SkipList*);
char*sk_tostring(SkipList*);
*/

#endif
