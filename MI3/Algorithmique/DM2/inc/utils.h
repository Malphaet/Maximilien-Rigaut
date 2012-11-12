/*
 * utils.h
 * This file is part of liblsockets
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * liblsockets is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * liblsockets is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liblsockets. If not, see <http://www.gnu.org/licenses/>.
 */


 
#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/** @file utils.h Utilities
 *
 * All utilities are defined and documented here
 */

/** @def WHERE 
 * Print the current position on the program 
 */

/** @def ERROR(msg) 
 * Print the current error, with the error message @a msg and exits
 */

/** @def OUT(msg) 
 * Exits the program with the message @a msg
 */

/** @def FPRINT(msg) 
 * Print @a msg in stdout and flush 
 */

/* ========= Defines ==========*/
int verbose; /*< Verbosity of the program */

/* Functions */

#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define ERROR(msg)	{WHERE; perror(msg);printf("\n");exit(EXIT_FAILURE);}
#define OUT(msg)	{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}
#define FPRINT(msg)	{fprintf(stdout,msg);fflush(stdout);}
#define min(a,b)	((a)<(b)?(a):(b))

#define TIMER_INIT struct timeval tvBegin, tvEnd
#define TIMER_STRT gettimeofday(&tvBegin, NULL)
#define TIMER_STOP gettimeofday(&tvEnd, NULL)
#define TIMER_USEC ((tvEnd.tv_usec+1000000*tvEnd.tv_sec)-(tvBegin.tv_usec+1000000*tvBegin.tv_sec))

int 			Salem 					(FILE*);
/* Debug purpose */
void			binary_print			(char*);
char*			itobin					(int,unsigned int);
char* 			atobin					(char*);

#endif /* __UTILS_H__ */

