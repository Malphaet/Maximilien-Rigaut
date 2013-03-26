/*
 * dico.c
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

/** @file dico.c The table of symbols */
#include "dico.h"

/** Add a variable to the table */
int ajoutevariable(char *nom, n_type *type){
	variable v;
	int ind=cherche(nom);
	v.type=type; v.nom=nom; v.mode=context_var;
	PLCC_INFO("Adding variable %s %s(%d)",v.nom,ind>=0?dico.tab[ind].nom:"",ind);
	if (context_var==GLOBAL) {
		if (ind>=0) return 0;
		v.adresse=adresseGlobaleCourante++;
		dico.tab[dico.base++]=v; dico.sommet=dico.base;
	} else {
		if (ind<dico.base) {PLCC_WARNING("declaration of %s shadowing global variable",nom);}
		else if (ind>0) return 0;
		if (dico.sommet++>MAX_DICO) PLCC_ERROR("symbol table full");
		v.adresse=adresseLocaleCourante++;
		dico.tab[dico.sommet]=v;
	}
	return 1;
}

/** Add a function to the table */
int ajoutefonction(char *nom, n_type *type, n_l_dec *param){
	if (ajoutevariable(nom,type)==0) return 0;
	if (context_var==GLOBAL) dico.tab[dico.base-1].param=param;
	else dico.tab[dico.sommet-1].param=param;
	return 1;
}

/** Lookup for a local variable in the dictionary, return it's index or -1 if not found */
int cherchelocale(char *nom){
	int i;
	for(i=0;i<dico.base;i++) if (strcmp(dico.tab[i].nom,nom)==0) return i;
	return -1;
}

/** Lookup for a variable in the dictionary, return it's index or -1 if not found */
int cherche(char *nom){
	int i;
	for(i=0;i<dico.sommet;i++) if (strcmp(dico.tab[i].nom,nom)==0) return i;
	return -1;
}

void afficherDico(){
	int i;
	for(i=0;i<dico.sommet;i++) printf("%d %s\n",i,dico.tab[i].nom);
}
/** Return the adress of the variable */
int adresse(int v){
	return dico.tab[v].adresse;
}

/** Enter a function (switch context to local) */
void entreefonction(void){
	context_var=LOCAL;
	dico.sommet=dico.base;
	adresseLocaleCourante=0;
}
/** Exit that function (switch context to global) */
void sortiefonction(void){
	context_var=GLOBAL;
	//while (dico.sommet>dico.base) free(dico.tab[dico.sommet--].nom,type,...);
	dico.sommet=dico.base;
}
