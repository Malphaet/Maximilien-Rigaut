/*
 * levenshtein.h
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

#ifndef __LEVENSHTEIN__H__
#define __LEVENSHTEIN__H__

/*==== Includes ====*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "utils.h"
#include "utf8.h"
#include "clist.h"

/*==== Defines ====*/
#define min3(a,b,c) min(min((a),(b)),(c))
/* Hash */
#define HASH_SIZE 20 		/**< Size of the checksum (in bits) */
#define HASH_DSIZ 1048577	/**< Dictionnary size (2**HASH_SIZE-1) */
#define HASH_POWR 5			/**< Power of two to elevate the checksum */

/*==== Prototype ====*/
int 			levenshtein				(char*,char*);			/* The levenshtein functions */
unsigned int 	jhash					(char*);				/* Hash function */
lclist**		build_hashdict			(char*);				/* Build the hash dictionnary */
void 			hashdict_addword		(lclist**,unsigned int,char*);		/* Add the word into the dictionnary */
int 			hashdict_in				(lclist**,char*);		/* Is the word into the dictionnary */
lclist**		build_3tupledict		(char*);				/* Build the 3tuples */
#endif /* __LEVENSHTEIN__H__ */

