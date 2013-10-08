/*
 * utils.h
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

 
#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/** @file utils.h Utilities header
 *
 * All utilities are defined and documented here
 */


/* ========= Defines ==========*/
int verbose; /**< Verbosity of the program */

/** Print the current position on the program */
#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
/** Print the current error, with the error message @a msg and exits */
#define ERROR(msg)	{WHERE; perror(msg);printf("\n");exit(EXIT_FAILURE);}
/** Exits the program with the message @a msg */
#define OUT(msg)	{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}
/** Print @a msg in stdout and flush */
#define FPRINT(msg)	{fprintf(stdout,msg);fflush(stdout);}
/** Return the max beetween the two parameters */
#define min(a,b)	((a)<(b)?(a):(b))

/** Initialise the timer */
#define TIMER_INIT struct timeval tvBegin, tvEnd
/** Start the timer */
#define TIMER_STRT gettimeofday(&tvBegin, NULL)
/** Stop the timer */
#define TIMER_STOP gettimeofday(&tvEnd, NULL)
/** Get the time interval */
#define TIMER_USEC ((tvEnd.tv_usec+1000000*tvEnd.tv_sec)-(tvBegin.tv_usec+1000000*tvBegin.tv_sec))

/* Prototype */
void			binary_print			(char*);
char*			itobin					(int,unsigned int);
char* 			atobin					(char*);

#endif /* __UTILS_H__ */

