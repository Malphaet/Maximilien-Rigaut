 /*
 * plcc.c
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


#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "yylex.h"
#include "yyparse.h"
#include "dico.h"

char yytext[SIZE_TEXT],*file_in_progress;
FILE *yyin;
unsigned int line_number=1,char_number=0,word_size=0,adresseGlobaleCourante=0,adresseLocaleCourante=0;
int context_var=GLOBAL;

int main(int argc, char **argv) {
	if (argc<2) OUT("plcc error : Not enough arguments");
	
	yyin = fopen(argv[1], "r");
	file_in_progress=argv[1];
	if(yyin == NULL) ERROR("plcc error : File not found");
	
	uc = yylex();
	//#ifdef DEBUG
	//while (uc != 0) {
		//printf("%2d:%2d  -  %3d:%s\n",line_number,char_number,uc ,yytext);
		//uc = yylex();
	//}
	//#else
	Programme(); 
	//#endif
	return 0;
}
