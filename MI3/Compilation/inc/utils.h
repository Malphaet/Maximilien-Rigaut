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
#ifndef __UTIL_H__
#define __UTIL_H__
#define SIZE_TEXT 521

#include <stdio.h>
extern char yytext[SIZE_TEXT],*file_in_progress;
extern FILE *yyin;
extern unsigned int line_number,char_number,word_size;

#ifdef DEBUG
#define C_GREY    "\033[1;30m"
#define C_CLEAR   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_BLACK   "\033[30m"
#define C_RED     "\033[1;31m"
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_BLUE    "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN    "\033[36m"
#define C_WHITE   "\033[37m"
#else
#define C_GREY    ""
#define C_CLEAR   ""
#define C_BOLD    ""
#define C_BLACK   ""
#define C_RED     ""
#define C_GREEN   ""
#define C_YELLOW  ""
#define C_BLUE    ""
#define C_MAGENTA ""
#define C_CYAN    ""
#define C_WHITE   ""
#endif
/* ========= Defines ==========*/

#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define PLCC_WHERE printf("In %s line %d:%d\n",file_in_progress,line_number,char_number)
#define ERROR(msg)	{WHERE; perror(msg);printf("\n");exit(EXIT_FAILURE);}
#define PLCC_ERROR(...) {	fprintf(stderr,"plcc error: ");\
							PLCC_WHERE;\
							fprintf(stderr,__VA_ARGS__);\
							fprintf(stderr,"\n");\
							exit(EXIT_FAILURE);}
#define PLCC_WARNING(...)	{PLCC_WHERE;\
							fprintf(stderr,"plcc warning: ");\
							fprintf(stderr,__VA_ARGS__);}

#define OUT(msg)	{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}

#ifdef DEBUG
#define DPRINT {printf("%sAt %s%3d (%02d:%02d)%s of %s:%s %s%s\n",\
                  C_GREY,C_RED,__LINE__,line_number,char_number,C_GREY,__FILE__,C_GREEN,__func__,C_CLEAR);}
#else
#define DPRINT 
#endif

#endif
