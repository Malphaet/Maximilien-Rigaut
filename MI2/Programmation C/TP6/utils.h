/*
 * utils.h
 * This file is part of Genelib
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Genelib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Genelib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */



#ifndef __UTILS__
#define __UTILS__
/* ========= Defines ==========*/
#define deploy 1

#define TEST(p) if ((p)==NULL) {printf("Error in file %s.\n    > function:%s - line:%d\n    > NULL pointer error\n",__FILE__, __func__,__LINE__); exit(EXIT_FAILURE);}

#if deploy
	#define OUT(a,b) {FILE *file = fopen("./output.txt","a+"); fprintf(file,(a),(b)); fclose(file);};
	#define OUTNF(a) {FILE *file = fopen("./output.txt","a+"); fprintf(file,(a)); fclose(file);};
#else
	#define OUT(a,b) printf((a),(b));
	#define OUTNF(a) printf((a));
#endif

#endif
