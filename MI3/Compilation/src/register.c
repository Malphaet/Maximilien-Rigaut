/*
 * register.c
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
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "register.h"
#include "arbre.h"
#include "code3.h"
#include "utils.h"


/* Use Two lines		
 * c3_add, c3_sub, c3_times, c3_div, c3_mod, 
 * c3_eql, c3_dif, c3_inf, c3_sup, c3_infeq, c3_supeq, 
 * c3_or, c3_and, ltab, stab

 *	(use 1 line )
	c3_no, c3_neg, param addimm store jumpif0 write
	
 *	(dont use lines)
	load jump read call loadimm entering exiting
*/

/*typedef enum {c3_add, c3_sub, c3_times, c3_div, c3_mod, 
	      c3_eql, c3_dif, c3_inf, c3_sup, c3_infeq, c3_supeq, 
	      c3_or, c3_and, c3_no, c3_neg, 	      
	      read, write, load, store, ltab, stab, loadimm,
	      addimm, 
	      jump, jumpif0, param, call, entering, exiting} */
	      
int*dernier_appel;

#define NOT_OP(a) (code[i].op!=(a))
#define ADD_IF(a) if (i>(a)) (a)=i;
void trouve_dernier_appel(){
	int i;
	dernier_appel=malloc(line_code3*sizeof(int));
	for(i=0;i<line_code3;i++) dernier_appel[i]=-1;
	
	for(i=0;i<line_code3;i++) 
		if (NOT_OP(jump)&NOT_OP(read)&NOT_OP(call)&NOT_OP(loadimm)&NOT_OP(entering)&NOT_OP(exiting)&NOT_OP(load)){
			if (NOT_OP(c3_no)&NOT_OP(c3_neg)&NOT_OP(param)&NOT_OP(addimm)&NOT_OP(store)&NOT_OP(jumpif0)&NOT_OP(write)){
				// The Two arguments are used
				ADD_IF(dernier_appel[code[i].arg1]);
				ADD_IF(dernier_appel[code[i].arg2]);
			} else {
				// Only the first argument is used
				ADD_IF(dernier_appel[code[i].arg1]);
			}
	}
	//for(i=0;i<line_code3;i++) printf("%i | %i\n",i,dernier_appel[i]);
}
#undef NOT_OP
#undef ADD_IF

int registre_libre(int ligne){
	int i;
	//if ((i=registre_associe(ligne))>0) return i; // The line already is in the register
	for(i=0;i<SIZE_REGISTER;i++) if (registre[i]!=-1) {
		registre[i]=ligne; return i;
	}
	return -1;
}

int registre_associe(int ligne){
	int i;
	for(i=0;i<SIZE_REGISTER;i++) if (registre[i]==ligne){
		return i;
	}
	return -1;
}
