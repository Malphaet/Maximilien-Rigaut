/** @file dico.h Table des symboles */
#ifndef __DICO__
#define __DICO__

/*---------- Inculdes -----------*/
#include "arbre.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>


/*---------- Defines -----------*/
#define GLOBAL 0        /**< Context global */
#define LOCAL 1         /**< Context local */
#define FONCTION 2      /**< Inside Function */

/*-------- Variables -----------*/
extern int context_var; /**< The current context of variables (GLOBAL or LOCAL) */
extern unsigned int adresseGlobaleCourante, /**< The current global variable index */
  adresseLocaleCourante;    /**< The current local variable index */

/*---------- Typedef -----------*/
/** A variable used in the program */
typedef struct {
  char *nom;      /**< Le nom de la variable */
  n_type *type;   /**< Type (de retour pour les fonctions) */
  n_l_dec *param; /**< Paramètres pour les fonctions, NULL sinon */
  int adresse;    /**< En memoire */
  int mode;       /**< GLOBAL, LOCAL, FONCTION */
} variable;


struct {
  variable tab[MAX_DICO]; /**< The list of variables */
  int base;               /**< The last global variable */
  int sommet;             /**< The last local variable */
} dico; /**< The variable dictionnary itself */


/*-------- Prototype -----------*/

int ajoutevariable(char *nom, n_type *type);
int ajoutefonction(char *nom, n_type *type, n_l_dec *param);

int sizeof_type(n_type*type);
int cherchelocale(char *nom);
int cherche(char *nom);
int adresse(int v);

void afficherDico();
void entreefonction(void);
void sortiefonction(void);

#endif
