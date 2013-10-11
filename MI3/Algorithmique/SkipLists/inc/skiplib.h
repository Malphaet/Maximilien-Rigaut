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

/* Mandatory structures */

typedef struct s_node {
	t_key value;
	struct s_node** next;
} sk_node;

typedef struct s_skip_list {
	struct s_node* head;	// The first "node", containing links to every other node
	int level; 				// The max level of skipping
	double percent; 		// The percentage of elements that will be skipped
	long size; 				// Size of the SkipList
} SkipList;

struct char_size {
	int size;
	char* txt;
};

/* Prototype */

SkipList*	sk_create	(double);
void 		sk_delete	(SkipList*);
sk_node*	sk_find_last(SkipList*l,t_key key,int key_compare(t_key,t_key));
int 		sk_contains	(SkipList*l,t_key key,int key_compare(t_key,t_key));
void 		sk_remove	(SkipList*l,t_key key,int key_compare(t_key,t_key));
void 		sk_add		(SkipList*l,t_key key,int key_compare(t_key,t_key),void post_actions(sk_node*,t_key));
t_key 		sk_tolist	(SkipList*);
char*		sk_tostring	(SkipList*,struct char_size key_to_str(t_key));
			
/* Predefined fonctions */
void 		sk_no_action(sk_node*,t_key);
int 		sk_compint	(t_key,t_key);
void 		sk_add_int	(SkipList*,int);
int			sk_compstr	(t_key,t_key);
void 		sk_add_str	(SkipList*,char*);
int			sk_contains_int(SkipList*,int);
void 		sk_remove_int(SkipList*,int);



struct char_size
			int_to_str(t_key);
struct char_size
			char_to_str(t_key);

/* Macros */
#define sk_tostring_int(l) sk_tostring(l,int_to_str)
#define sk_tostring_str(l) sk_tostring(l,char_to_str)
#define sk_contains_str(l,i) sk_contains_str(l,i,sk_compstr)

#endif
