/*
 * clist.c
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

#include "clist.h"

/** @file clist.c Chained lists source */
/** @defgroup lclist Small chained lists functions
 * @brief Minimalistic way of supporting chained lists
 * @{
*/

/** Make a new chained list 
 * @return Return an empty clist
 */
lclist* make_lclist(){
	lclist*l=malloc(sizeof(lclist));
	l->data=LPOP_ERROR;
	l->next=NULL;
	if (l==NULL) ERROR("Clist creation error");
	return l;
}

/** Drop the list 
 * @param l The clist to drop
 */
void drop_lclist(lclist*l){
	lclist*next,*curr;
	for (curr=l;(next=curr->next)!=NULL;curr=next) free(curr);
	free(curr);
}

/** Add an element to the list 
 * @param l The clist to add to
 * @param data The data to add
 */
void add_lclist(lclist*l,DATATYPE data){
	lclist*new=malloc(sizeof(lclist));
	new->data=data;
	new->next=l->next;
	l->next=new;
}

/** Delete the first element of the list
 * @param l The list to pop the last element$
 * @return The value popped (You should free it properly if needed)
 */
DATATYPE pop_lclist(lclist*l){
	DATATYPE ret; lclist*new;
	if (l->next==NULL) return LPOP_ERROR;

	ret=l->next->data; new=l->next->next;
	free(l->next); l->next=new;

	return ret;
}

/** Lenght of the list 
 * @param l The list to mesure
 * @return The size of the list
 */
int len_lclist(lclist*l){
	int ln=0; lclist*curr=l;
	while ((curr=curr->next)!=NULL) ln++;
	return ln;
}
/** @} */
