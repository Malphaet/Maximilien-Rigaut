/*
 * gene_lib.c
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

/* ========= Includes =========*/

#include <stdio.h>
#include <stdlib.h>
#include "gene_lib.h"
#include "utils.h"


/* ========= Defines ==========*/

/* ========= Functions ========*/
/* --------- Personnes --------*/

PERSONNE cree_personne(char *name, char *firstname, int birthdate, int deathdate){
	PERSONNE person=(PERSONNE) malloc(sizeof(struct person));
	TEST(person);
	person->name=name;
	person->firstname=firstname;
	person->birthdate=birthdate;
	person->deathdate=deathdate;
	person->father=NULL;
	person->mother=NULL;
	person->consort=NULL;
	person->childs=liste_vide();
	person->ex_consorts=liste_vide();
	
	return person;
}


/*------- Liste Personnes -----*/

POINTEUR liste_vide(void){
	POINTEUR liste=malloc(sizeof(struct pointer)); TEST(liste);
	liste->value=NULL;
	liste->next=NULL;
	return liste;
}

void ajoute_personne(PERSONNE n_person, POINTEUR liste){
	POINTEUR ltemp=liste->next;
	PERSONNE ptemp=liste->value;
	POINTEUR node=malloc(sizeof(struct pointer)); TEST(node);
	
	liste->next=node;
	liste->value=n_person;
	node->value=ptemp;
	node->next=ltemp;
}

void ajoute_pere_enfant(PERSONNE father,PERSONNE child){
	ajoute_personne(child,father->childs);
	child->father=father;
}
void ajoute_mere_enfant(PERSONNE mother, PERSONNE child){
	ajoute_personne(child,mother->childs);
	child->mother=mother;
}

void ajoute_conjoint(PERSONNE x, PERSONNE y){
	x->consort=y;
	y->consort=x;
}

void ajoute_ex_onjoint(PERSONNE x, PERSONNE y){
	ajoute_personne(y,x->ex_consorts);
	ajoute_personne(x,y->ex_consorts);
}

void divorce(PERSONNE x){
	if (!x->consort) return;
	ajoute_personne(x->consort,x->ex_consorts);
	ajoute_personne(x,x->consort->ex_consorts);
	
	x->consort->consort=NULL;
	x->consort=NULL;
}

void affiche_personne(PERSONNE x){
	affiche_personne_abbrev(x);
	OUTNF("\nPere: "); if (x->father) affiche_personne_abbrev(x->father);
	OUTNF("\nMere: "); if (x->mother) affiche_personne_abbrev(x->mother);
	OUTNF("\nEnfant(s): ");	affiche_liste_abbrev(x->childs);
	OUTNF("\nConjoint(e): "); if (x->consort) affiche_personne_abbrev(x->consort);
	OUTNF("\nEx-Conjoints(es): ");affiche_liste_abbrev(x->ex_consorts);
	OUTNF("\n");
}
/*---------- Affichage --------*/

void affiche_personne_abbrev(PERSONNE person){
	OUT("%s ",person->firstname);
	OUT("%s ",person->name);
	OUT("(%d-",person->birthdate);
	OUT("%d); ",person->deathdate);
}

void affiche_liste_abbrev(POINTEUR liste){
	while(liste->next){
		affiche_personne_abbrev(liste->value);
		liste=liste->next;
	}
}
