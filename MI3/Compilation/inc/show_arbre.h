/*
 * show_arbre.h
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

#ifndef __SHOW_ARBRE_H__
#define __SHOW_ARBRE_H__

/*------ PROGRAMME ------*/
void		show_n_prog             (n_prog*);

/*------ INSTRUCTIONS ------*/
void 		show_n_instr			(n_instr*l);

/*------ LISTES D'OBJETS------*/
void		show_n_l_fun_dec		(n_l_fun_dec*l);
void		show_n_l_exp			(n_l_exp*l);
void		show_n_l_instr			(n_l_instr*l);
void		show_n_l_dec			(n_l_dec*l);

/*------ TYPES ------*/
void       show_n_type		        (n_type*);

/*------ DECLARATIONS ------*/
void		show_n_dec_var         (n_dec*d);
void		show_n_dec_fonc        (n_fun_dec*d);

/*------ EXPRESSIONS ------*/
void 		show_n_exp				(n_exp*e);
void 		show_n_appel			(n_appel*a);
void 		show_n_var				(n_var*v);



#endif
