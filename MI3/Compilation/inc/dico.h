/* Definit la table des symboles.*/
#ifndef __DICO__
#define __DICO__

#include "arbre.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>


/*---------- Defines -----------*/
#define MAX_DICO 100

#define GLOBAL 0
#define LOCAL 1
#define FONCTION 2

/*-------- Variables -----------*/
extern int context_var;
extern unsigned int adresseGlobaleCourante,adresseLocaleCourante;


/*---------- Typedef -----------*/
typedef struct {
  char *nom;
  n_type *type;   /* Type (de retour pour les fonctions) */
  n_l_dec *param; /* Paramètres pour les fonctions, NULL sinon */
  int adresse;    /* En memoire */
  int mode;       /* GLOBAL, LOCAL, FONCTION */
} variable;

struct {
  variable tab[MAX_DICO];
  int base;
  int sommet;
} dico;


/*-------- Prototype -----------*/

int ajoutevariable(char *nom, n_type *type);
int ajoutefonction(char *nom, n_type *type, n_l_dec *param);

int cherchelocale(char *nom);
int cherche(char *nom);
int adresse(int v);

void entreefonction(void);
void sortiefonction(void);

#endif
