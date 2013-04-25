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

/* ========= Includes ======= */
#include <stdio.h>

/* ========= Colors ======= */ 
#ifdef COLORS
#define C_GREY    "\033[1;30m"
#define C_CLEAR   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_BLACK   "\033[30m"
#define C_ORANGE  "\033[1;31m"
#define C_GREEN   "\033[1;32m"
#define C_YELLOW  "\033[1;33m"
#define C_RED     "\033[31m"
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
#define C_ORANGE  ""
#define C_GREEN   ""
#define C_YELLOW  ""
#define C_BLUE    ""
#define C_MAGENTA ""
#define C_CYAN    ""
#define C_WHITE   ""
#endif

/* ====== Definitions =======*/
#define SIZE_TEXT 521
extern char yytext[SIZE_TEXT],*file_in_progress;
extern FILE *yyin;
extern unsigned int line_number,char_number,word_size;

/* ========= Defines ==========*/

#define PLCC_WHERE(out) fprintf(out,"%s%s:%s%d:%d:%s",C_YELLOW,file_in_progress,C_YELLOW,line_number,char_number,C_CLEAR)
#define ERROR(msg)	{WHERE; perror(msg);exit(EXIT_FAILURE);}
#define PLCC_ERROR(...)       {PLCC_WHERE(stderr);\
                                    fprintf(stderr,"%s plcc error: %s",C_ORANGE,C_CLEAR);\
				    fprintf(stderr,__VA_ARGS__);\
				    fprintf(stderr,"%s\n",C_CLEAR);\
				    exit(EXIT_FAILURE);}

#define PLCC_WARNING(...)	{WHERE;PLCC_WHERE(stderr);\
				    fprintf(stderr,"%s plcc warning: %s",C_YELLOW,C_CLEAR);\
				    fprintf(stderr,__VA_ARGS__);\
                                    fprintf(stderr,"%s\n",C_CLEAR);}
                                    
#define PLCC_INFO(...)	      {PLCC_WHERE(stdout);\
				    fprintf(stdout," plcc info: ");\
				    fprintf(stdout,__VA_ARGS__);\
                                    fprintf(stdout,"\n");}
				    
#define OUT(msg)		{WHERE; fprintf(stderr,msg);fprintf(stderr,"\n");exit(EXIT_FAILURE);}
#define CHECK_PTR(ptr)	do {if (ptr==NULL) OUT("Allocation error, exiting");} while (0);
#define CHECK_VAR(var) do {if (cherche(var)<0) PLCC_ERROR("%s doesn't exist",var);} while (0);


#ifdef DEBUG
#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define DPRINT {printf("%sAt %s%3d (%02d:%02d)%s of %s:%s %s%s\n",\
                  C_GREY,C_ORANGE,__LINE__,line_number,char_number,C_GREY,__FILE__,C_GREEN,__func__,C_CLEAR);}
#else
#define WHERE		printf("In %s line %d (%s)\n",__FILE__,__LINE__,__func__)
#define DPRINT 
#endif

#endif
