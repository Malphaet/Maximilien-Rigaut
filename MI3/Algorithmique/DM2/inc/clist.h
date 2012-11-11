/*
 * clist.h
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


#ifndef __LLISTS_H__
#define __LLISTS_H__
#include "utils.h"
#include <stdlib.h>
/* ======== Defines ========= */
#define DATATYPE char*
#define LPOP_ERROR NULL			/**< Extremely important for automation */

/* ======== Structures ========= */
/** 
 * @brief A chanined list structure
 */

typedef struct int_chained_list {
	DATATYPE data;
	struct int_chained_list*next;
} lclist;

/* ======== Prototype ========= */

lclist*	 make_lclist			();									/* [Public]: Make a new chained list */
void	 drop_lclist			(lclist*);							/* [Public]: Drop the list */
void	 add_lclist				(lclist*,DATATYPE);					/* [Public]: Add an element to the list */
DATATYPE pop_lclist				(lclist*);							/* [Public]: Delete the first element of the list */
int		 len_lclist				(lclist*);							/* [Public]: Lenght of the list */

#endif /* __LLISTS_H__ */
