/* Definit la table des symboles.
 */
#ifndef __DICO__
#define __DICO__

#include "syntabs.h"

/* taille max de la table */
#define MAX_DICO 100

/* modes d'écriture de la table */
#define GLOBAL 0
#define LOCAL 1
#define FONCTION 2

/* variable */
typedef struct {
  char *nom;
  n_type *type;   /* type (de retour pour les fonctions) */
  n_l_dec *param; /* paramètres pour les fonctions, NULL sinon */
  int adresse;    /* en memoire */
  int mode;       /* GLOBAL, LOCAL, FONCTION */
} variable;

/* dico :
                <- MAX_DICO
  -----------
  |         |
  | (vide)  |   <- sommet
  -----------
  |variables|
  |locales  |   <- base
  -----------
  |variables|
  |globales |   <- 0
  -----------
*/

struct {
  variable tab[MAX_DICO];
  int base;
  int sommet;
} dico;

/* ajoute des noms dans la table */
int ajoutevariable(char *nom, n_type *type);
int ajoutefonction(char *nom, n_type *type, n_l_dec *param);
/* cherche une variable; renvoie 
    - l'indice de la table
    - (-1) s'il n'est pas dedans */
int cherchelocale(char *nom);
int cherche(char *nom);
/* renvoie l'adresse (locale ou globale) de la variable */
int adresse(int v);
/* passe en contexte local / global */
void entreefonction(void);
void sortiefonction(void);

#endif

