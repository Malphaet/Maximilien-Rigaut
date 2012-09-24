/*
 * gene_lib.h
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


#ifndef __GENELIB__
#define __GENELIB__
/* ========= Includes =========*/

/* ========= Defines ==========*/


/* ========= Typedef ==========*/

typedef struct person{
	char *name;
	char *firstname;
	int birthdate;
	int deathdate;
	struct person *father;
	struct person *mother;
	struct person *consort;
	struct pointer *childs;
	struct pointer *ex_consorts;
} *PERSONNE;

typedef struct pointer{
	struct person *value;
	struct pointer *next;
} *POINTEUR;

/* ======== Prototype =========*/
PERSONNE cree_personne(char*, char*, int, int);
void affiche_personne_abbrev(PERSONNE);
POINTEUR liste_vide(void);
void ajoute_personne(PERSONNE, POINTEUR);
void affiche_liste_abbrev(POINTEUR);
void ajoute_pere_enfant(PERSONNE,PERSONNE);
void ajoute_mere_enfant(PERSONNE, PERSONNE);
void ajoute_conjoint(PERSONNE, PERSONNE);
void ajoute_ex_onjoint(PERSONNE, PERSONNE);
void divorce(PERSONNE);
void affiche_personne(PERSONNE);
#endif
