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

/** @file clist.h Chained lists */

#ifndef __LLISTS_H__
#define __LLISTS_H__
#include "utils.h"
#include <stdlib.h>
/* ======== Defines ========= */
#define DATATYPE char*				/**< The type of data handled by the lists */
#define LPOP_ERROR NULL			/**< Extremely important for automation */

/* ======== Structures ========= */

/** A chained list structure */
typedef struct lchained_list {
	DATATYPE data;	/**< The stored data, of type DATATYPE */
	struct lchained_list*next; /**< The adress of the next list member */
} lclist;

/* ======== Prototype ========= */

lclist*	 make_lclist			();									/**< Make a new chained list */
void	 drop_lclist			(lclist*);							/**< Drop the list */
void	 add_lclist				(lclist*,DATATYPE);					/**< Add an element to the list */
DATATYPE pop_lclist				(lclist*);							/**< Delete the first element of the list */
int		 len_lclist				(lclist*);							/**< Lenght of the list */

#endif /* __LLISTS_H__ */
