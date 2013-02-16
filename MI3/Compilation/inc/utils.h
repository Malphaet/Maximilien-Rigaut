/*
 * utils.h
 * 
 * Copyright 2013 Maximilien Rigaut <max[dot]rigaut[at]orange.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 */

/* ===== Global variables =====*/

extern char yytext[512],*file_in_progress;
extern FILE *yyin;
extern unsigned int line_number,char_number;

/* ========= Defines ==========*/

#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define PLCC_WHERE printf("In %s line %d:%d\n",file_in_progress,line_number,char_number)
#define ERROR(msg)	{WHERE; perror(msg);printf("\n");exit(EXIT_FAILURE);}
#define PLCC_ERROR(...) {	fprintf(stderr,"plcc error: ");\
							PLCC_WHERE;\
							fprintf(stderr,__VA_ARGS__);\
							fprintf(stderr,"\n");\
							exit(EXIT_FAILURE);}

#define OUT(msg)	{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}
