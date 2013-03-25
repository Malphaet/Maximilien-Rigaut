#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "utils.h"



n_type *cree_n_type_int(void){
  n_type *n = malloc(sizeof(n_type));
  n->type = t_int;
  DPRINT;return n;
}

n_type *cree_n_type_bool(void){
  n_type *n = malloc(sizeof(n_type));
  n->type = t_bool;
  DPRINT;return n;
}

n_type *cree_n_type_array(n_type *t, int debut, int fin){
  n_type *n = malloc(sizeof(n_type));
  n->type = t_array;
  n->debut = debut;
  n->fin = fin;
  n->arrayof = t;
  DPRINT;
  DPRINT;return n;
}

n_appel *cree_n_appel(char *fonction, n_l_exp *args)
{
  n_appel *n = malloc(sizeof(n_appel));
  n->fonction = fonction;
  n->args = args;
  DPRINT;
  DPRINT;return n;
}

n_prog *cree_n_prog(n_l_dec *variables, n_l_fun_dec *fonctions, n_instr *corps)
{
  n_prog *n = malloc(sizeof(n_prog));
  n->variables = variables;
  n->fonctions = fonctions;
  n->corps = corps;
  DPRINT;return n;
}

n_var *cree_n_var_simple(char *nom)
{
  n_var *n = malloc(sizeof(n_var));
  n->type = simple;
  n->nom = nom;
  DPRINT;return n;
}

n_var *cree_n_var_indicee(char *nom, n_exp *indice)
{
  n_var *n = malloc(sizeof(n_var));
  n->type = indicee;
  n->nom = nom;
  n->indice = indice;
  DPRINT;return n;
}

n_exp *cree_n_exp_op(operation op, n_exp *op1, n_exp *op2)
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = opExp;
  n->u.opExp_.op = op;
  n->u.opExp_.op1 = op1;
  n->u.opExp_.op2 = op2;
  DPRINT;return n;
}

n_exp *cree_n_exp_appel(n_appel *app)
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = appelExp;
  n->u.appel = app;
  DPRINT;return n;
}

n_exp *cree_n_exp_var(n_var *var)
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = varExp;
  n->u.var = var;
  DPRINT;return n;
}

n_exp *cree_n_exp_entier(int entier)
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = intExp;
  n->u.entier = entier;
  DPRINT;return n;
}

n_exp *cree_n_exp_true()
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = trueExp;
  DPRINT;return n;
}

n_exp *cree_n_exp_false()
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = falseExp;
  DPRINT;return n;
}

n_exp *cree_n_exp_lire()
{
  n_exp *n = malloc(sizeof(n_exp));
  n->type = lireExp;
  DPRINT;return n;
}


n_l_exp *cree_n_l_exp(n_exp *tete, n_l_exp *queue)
{
  n_l_exp *n = malloc(sizeof(n_l_exp));
  n->tete = tete;
  n->queue = queue;
  DPRINT;return n;
}

n_instr *cree_n_instr_incr(n_exp *incr)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = incrInst;
  n->u.incr = incr;
  DPRINT;return n;
}

n_instr *cree_n_instr_si(n_exp *test, n_instr *alors, n_instr *sinon)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = siInst;
  n->u.si_.test = test;
  n->u.si_.alors = alors;
  n->u.si_.sinon = sinon;
  DPRINT;return n;
}

n_instr *cree_n_instr_tantque(n_exp *test, n_instr *faire)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = tantqueInst;
  n->u.tantque_.test = test;
  n->u.tantque_.faire = faire;
  DPRINT;return n;
}

n_instr *cree_n_instr_affect(n_var *var, n_exp *exp)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = affecteInst;
  n->u.affecte_.var = var;
  n->u.affecte_.exp = exp;
  DPRINT;return n;
}

n_l_instr *cree_n_l_instr(n_instr *tete, n_l_instr *queue)
{
  n_l_instr *n = malloc(sizeof(n_l_instr));
  n->tete = tete;
  n->queue = queue;
  DPRINT;return n;
}

n_instr *cree_n_instr_bloc(n_l_instr *liste)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = blocInst;
  n->u.liste = liste;
  DPRINT;return n;
}

n_instr *cree_n_instr_appel(n_appel *app)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = appelInst;
  n->u.appel = app;
  DPRINT;return n;
}

n_instr *cree_n_instr_ecrire(n_exp *expression)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = ecrireInst;
  n->u.ecrire_.expression = expression;
  DPRINT;return n;
}

n_instr *cree_n_instr_vide(void)
{
  n_instr *n = malloc(sizeof(n_instr));
  n->type = videInst;
  DPRINT;return n;
}

n_dec *cree_n_dec_var(char *nom, n_type *t)
{
  n_dec *n = malloc(sizeof(n_dec));
  n->type = t;
  n->nom = nom;
  DPRINT;return n;
}

n_fun_dec *cree_n_dec_fonc(char *nom, n_type *t, n_l_dec *param, n_l_dec *variables, n_prog *corps)
{
  n_fun_dec *n = malloc(sizeof(n_fun_dec));
  n->nom = nom;
  n->type = t;
  n->param = param;
  n->variables = variables;
  n->corps = corps;
  DPRINT;return n;
}

n_l_dec *cree_n_l_dec(n_dec *tete, n_l_dec *queue)
{
  n_l_dec *n = malloc(sizeof(n_l_dec));
  n->tete = tete;
  n->queue = queue;
  DPRINT;return n;
}

n_l_fun_dec *cree_n_l_fun_dec(n_fun_dec *tete, n_l_fun_dec *queue)
{
  n_l_fun_dec *n = malloc(sizeof(n_l_fun_dec));
  n->tete = tete;
  n->queue = queue;
  DPRINT;return n;
}

