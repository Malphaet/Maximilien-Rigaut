/*
 * corrector.h
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

/** @file corrector.h Word correction header */

#ifndef __CORRECTOR_H__
#define __CORRECTOR_H__

/* Includes */

#include "wordtools.h"
#include <pthread.h>

#define MAX_THREADS 4

/** Substitutions to perform */
char*substitutions[][2]={
	{"oe","œ"}
};

char**			ten_bests				(char*,lclist**,lclist**); /**< Return the ten best guesses for the given word */
void			correct_all				(char*,char*);				/**< Correct all words, compare */	
int				correct					(char*,char*,lclist**,lclist**);	/**< Correct a string */
#endif /* __CORRECTOR_H__ */



