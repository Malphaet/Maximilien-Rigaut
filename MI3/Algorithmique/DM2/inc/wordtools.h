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

/** @file wordtools.h Word analysis utilities headers */
/** @file wordtools.c Word analysis utilities source */

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
#define min3(a,b,c) min(min((a),(b)),(c))	/**< Minimal value between three */

/* Hash */
#define HASH_S_SIZE 16 		/**< Size of the checksum (in bits) */
#define HASH_M_SIZE 20 		/**< Size of the checksum (in bits) */
#define HASH_L_SIZE 24 		/**< Size of the checksum (in bits) */
#define HASH_SIZE	 HASH_M_SIZE/**< Dictionnary standard size */

#define HASH_S_DSIZ 65536		/**< Dictionnary size (2**HASH_SIZE) */
#define HASH_M_DSIZ 1048576	/**< Dictionnary size (2**HASH_SIZE) */
#define HASH_L_DSIZ 16777216	/**< Dictionnary size (2**HASH_SIZE) */
#define HASH_DSIZ	 HASH_M_DSIZ/**< Dictionnary standard size */

#define jhash(x)	 jhash_char((x),HASH_SIZE)	/**< Link to the hash function, for flexibility purpose */
#define jhash_S(x)  jhash_char((x),HASH_S_SIZE) /**< Small sized hash */
#define jhash_M(x)  jhash_char((x),HASH_M_SIZE) /**< Medium sized hash */
#define jhash_L(x)  jhash_char((x),HASH_L_SIZE) /**< Large sized hash */

#define HASH_POWR 5			/**< Power of two to elevate the checksum */

/*==== Prototype ====*/
unsigned int	levenshtein				(char*,char*);			/* The levenshtein functions */
unsigned int 	jhash_char				(const char*,int);		/* Hash function */
lclist**		build_hashdict			(char*);				/* Build the hash dictionnary */
void 			hashdict_addword		(lclist**,unsigned int,char*,int); /* Add the word into the dictionnary */
int 			hashdict_in				(lclist**,char*);		/* Is the word into the dictionnary */
lclist**		build_3tupledict		(char*);				/* Build the 3tuples */
int				strheq					(const char*,const char*); /* Are the word hashes equals ? */

#endif /* __LEVENSHTEIN__H__ */

