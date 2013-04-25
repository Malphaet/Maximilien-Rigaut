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

/** @file plcc.c The compiler itself */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "yylex.h"
#include "yyparse.h"
#include "dico.h"
#include "code3.h"
#ifdef MK_TREE
#include "show_arbre.h"
#endif

char yytext[SIZE_TEXT], /**< The analysed lexeme */
	 *file_in_progress;  /**< The name of the file currently analysed */
FILE *yyin;				 /**< The file currently analysed */

unsigned int line_number=1,char_number=0,word_size=0,adresseGlobaleCourante=0,adresseLocaleCourante=0;
int context_var=GLOBAL;

/** Main function of the compiler, not much of a parser, just load the necessary, and process
 * @param argc Number of arguments
 * @param argv The arguments
 * @return 1 in case of sucess, 0 otherwise
 */
int main(int argc, char **argv) {
	n_prog*p=NULL; FILE*yyout=NULL;
	
	if (argc<2) OUT("plcc error : Not enough arguments");
	if ((yyin=fopen(file_in_progress=argv[1],"r")) == NULL) ERROR("plcc error");
	if (argc>2) if ((yyout=fopen(argv[2], "w+"))==NULL) ERROR("plcc error");
	
	uc = yylex();
	#ifdef MK_LEX
		do {printf("%s%3d %s%s%s\n",C_GREEN,uc,C_ORANGE,yytext,C_CLEAR);} while ((uc=yylex())!=0);p+=1;
	#else
		p=Programme();
		#ifdef MK_TREE
		show_n_prog(p);
		#endif
		#ifdef MK_C3
			walk_code(p);
			show_code(yyout);
		#endif
		free(p);
	#endif
	fclose(yyin); if (argc>2) fclose(yyout);
	return 0;
}
