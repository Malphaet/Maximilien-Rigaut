/*
 * utils.h
 * This file is part of TP4
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP4 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP4. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __UTILS_H__
#define __UTILS_H__

/* ========= Defines ==========*/
/* Functions */
#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define ERROR(msg)	{WHERE; perror(msg);printf("\n");exit(EXIT_FAILURE);}
#define OUT(msg)	{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}
#define FPRINT(msg)	{fprintf(stdout,msg);fflush(stdout);}
#endif /* __UTILS_H__ */

