/*
 * code3.h
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef __CODE3_H__
#define __CODE3_H__

/* List of code3 operations */
typedef enum {c3_add, c3_sub, c3_times, c3_div, c3_mod, 
	      c3_eql, c3_dif, c3_inf, c3_sup, c3_infeq, c3_supeq, 
	      c3_or, c3_and, c3_no, c3_neg, 	      
	      read, write, load, store, ltab, stab, loadimm,
	      addimm, jump, jumpif0, param, call, entering, exiting} 
  c3_op;


/* The code is a list of 3-tuples*/
struct three_tuple {
  c3_op op;
  int arg1;
  int arg2;
  char *var;
} *code; 

int size_code3; /**< Total size of code3 */
int line_code3; /**< Ligne courante du tableau */


void add_line(c3_op op, int arg1, int arg2, char *var);
void init_code();
void walk_code(n_prog *n);
void show_code(FILE*);
void walk_inst(n_instr*);
void walk_exp(n_exp*);
#endif
