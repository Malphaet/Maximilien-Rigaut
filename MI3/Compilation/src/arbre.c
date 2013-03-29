#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "dico.h"
#include "utils.h"

/** @file arbre.c The syntax tree */
/** Create a type object (int) 
 * @return The aforementionned object*/
n_type *cree_n_type_int(void){
    n_type *n = malloc(sizeof(n_type)); CHECK_PTR(n);
    n->type = t_int;
    DPRINT;return n;
}

/** Create a type object (bool)
 * @return The aforementionned object*/
n_type *cree_n_type_bool(void){
    n_type *n = malloc(sizeof(n_type)); CHECK_PTR(n);
    n->type = t_bool;
    DPRINT;return n;
}

/** Create a type object (array) holding variables of type @param t beginning at @param debut ending at @param fin
 * @return The aforementionned object*/
n_type *cree_n_type_array(n_type *t, int debut, int fin){
    n_type *n = malloc(sizeof(n_type)); CHECK_PTR(n);
    n->type = t_array;
    n->debut = debut;
    n->fin = fin;
    n->arrayof = t;
    DPRINT;return n;
}

/** Create a function call named @param fonction with the argument @param args
 * @return The aforementionned object*/
n_appel *cree_n_appel(char *fonction, n_l_exp *args){
    n_appel *n = malloc(sizeof(n_appel)); CHECK_PTR(n);
    n->fonction = fonction;
    n->args = args;
    //! @todo update
    //if (cherche(fonction)<0) PLCC_WARNING("%s doesn't exist",fonction)
    DPRINT;return n;
}

/** Create a program with the functions @param fonctions the variables @param variables and the instructions @param corps
 * @return The aforementionned object*/
n_prog *cree_n_prog(n_l_dec *variables, n_l_fun_dec *fonctions, n_instr *corps){
    n_prog *n = malloc(sizeof(n_prog)); CHECK_PTR(n);
    n->variables = variables;
    n->fonctions = fonctions;
    n->corps = corps;
    DPRINT;return n;
}

/** Create a variable named @param nom
 * @return The aforementionned object*/
n_var *cree_n_var_simple(char *nom){
    n_var *n = malloc(sizeof(n_var)); CHECK_PTR(n);
    n->type = simple;
    n->nom = nom;
    //! @todo update
    //if (cherche(nom)<0) PLCC_WARNING("%s doesn't exist",nom); // Maybe you create it for declaration
    DPRINT;return n;
}

/** Create an indexed variable (an array cell) named @param nom with the index @param indice
 * @return The aforementionned object*/
n_var *cree_n_var_indicee(char *nom, n_exp *indice){
    n_var *n = malloc(sizeof(n_var)); CHECK_PTR(n);
    n->type = indicee;
    n->nom = nom;
    n->indice = indice;
    //! @todo check existence
    //if (cherche(nom)<0) PLCC_WARNING("%s doesn't exist",nom);
    DPRINT;return n;
}

/** Create an expression (operation) with @param op as operation betweed @param op1 and @param op2
 * @return The aforementionned object*/
n_exp *cree_n_exp_op(operation op, n_exp *op1, n_exp *op2){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = opExp;
    n->u.opExp_.op = op;
    n->u.opExp_.op1 = op1;
    n->u.opExp_.op2 = op2;
    //! @todo check types
    DPRINT;return n;
}

/** Create an expression (call) with @param app as called object
 * @return The aforementionned object*/
n_exp *cree_n_exp_appel(n_appel *app){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = appelExp;
    n->u.appel = app;
    //! @todo check
    //if (cherche(app)<0) PLCC_WARNING("%s doesn't exist",app);
    DPRINT;return n;
}

/** Create an expression (variable) with @param var as variable object
 * @return The aforementionned object*/
n_exp *cree_n_exp_var(n_var *var){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = varExp;
    n->u.var = var;
    DPRINT;return n;
}

/** Create an expression (entier) with @param entier as integer object
 * @return The aforementionned object*/
n_exp *cree_n_exp_entier(int entier){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = intExp;
    n->u.entier = entier;
    DPRINT;return n;
}

/** Create an expression (boolean) with true as value
 * @return The aforementionned object*/
n_exp *cree_n_exp_true(){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = trueExp;
    DPRINT;return n;
}

/** Create an expression (boolean) with false as value
 * @return The aforementionned object*/
n_exp *cree_n_exp_false(){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = falseExp;
    DPRINT;return n;
}

/** Create an expression (read) from input
 * @return The aforementionned object*/
n_exp *cree_n_exp_lire(){
    n_exp *n = malloc(sizeof(n_exp)); CHECK_PTR(n);
    n->type = lireExp;
    DPRINT;return n;
}

/** Create a list of expression with @param tete as fist element and @param queue as pointer to the next element
 * @return The aforementionned object*/
n_l_exp *cree_n_l_exp(n_exp *tete, n_l_exp *queue){
    n_l_exp *n = malloc(sizeof(n_l_exp)); CHECK_PTR(n);
    n->tete = tete;
    n->queue = queue;
    DPRINT;return n;
}

/** Create an instruction (increment) with @param incr as incremented expresion
 * @return The aforementionned object*/
n_instr *cree_n_instr_incr(n_exp *incr){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = incrInst;
    n->u.incr = incr;
    //! @todo check type
    DPRINT;return n;
}

/** Create an instruction (if) with @param test as test and @param alors as true expression and @param sinon as false expression
 * @return The aforementionned object*/
n_instr *cree_n_instr_si(n_exp *test, n_instr *alors, n_instr *sinon){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = siInst;
    n->u.si_.test = test;
    n->u.si_.alors = alors;
    n->u.si_.sinon = sinon;
    //! @todo check type
    DPRINT;return n;
}

/** Create an instruction (while) with @param test as test and @param faire as expression to do as long as the expression is true
 * @return The aforementionned object*/
n_instr *cree_n_instr_tantque(n_exp *test, n_instr *faire){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = tantqueInst;
    n->u.tantque_.test = test;
    n->u.tantque_.faire = faire;
    //! @todo check type
    DPRINT;return n;
}

/** Create an instruction (affect) with @param var as variable to affect to and @param exp as expression to affect
 * @return The aforementionned object*/
n_instr *cree_n_instr_affect(n_var *var, n_exp *exp){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = affecteInst;
    n->u.affecte_.var = var;
    n->u.affecte_.exp = exp;
    //! @todo check types, existence
    //if (cherche(var->nom)<0) PLCC_WARNING("%s doesn't exist",var->nom);
    DPRINT;return n;
}

/** Create a list of instructions with @param tete as fist element and @param queue as pointer to the next element
 * @return The aforementionned object*/
n_l_instr *cree_n_l_instr(n_instr *tete, n_l_instr *queue){
    n_l_instr *n = malloc(sizeof(n_l_instr)); CHECK_PTR(n);
    n->tete = tete;
    n->queue = queue;
    DPRINT;return n;
}

/** Create an instruction (block) with @param liste as a list of expressions
 * @return The aforementionned object*/
n_instr *cree_n_instr_bloc(n_l_instr *liste){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = blocInst;
    n->u.liste = liste;
    DPRINT;return n;
}

/** Create an instruction (call) with @param app as callable
 * @return The aforementionned object*/
n_instr *cree_n_instr_appel(n_appel *app){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = appelInst;
    n->u.appel = app;
    //! @todo check existence
    //if (cherche(app->fonction)<0) PLCC_WARNING("%s doesn't exist",app->fonction);
    DPRINT;return n;
}

/** Create an instruction (write) with @param expression as writable
 * @return The aforementionned object*/
n_instr *cree_n_instr_ecrire(n_exp *expression){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = ecrireInst;
    n->u.ecrire_.expression = expression;
    DPRINT;return n;
}

/** Create an instruction (void)
 * @return The aforementionned object*/
n_instr *cree_n_instr_vide(void){
    n_instr *n = malloc(sizeof(n_instr)); CHECK_PTR(n);
    n->type = videInst;
    DPRINT;return n;
}

/** Create a variable declaration with @param nom as name and @param t as type
 * @return The aforementionned object*/
n_dec *cree_n_dec_var(char *nom, n_type *t){
    n_dec *n = malloc(sizeof(n_dec)); CHECK_PTR(n);
    n->type = t;
    n->nom = nom;
    ajoutevariable(nom,t);
    DPRINT;return n;
}
/** Create a function declaration with @param nom as name, @param t as return type, 
 * @param param as parameters, @param variables as vars and @param corps as body
 * @return The aforementionned object*/
n_fun_dec *cree_n_dec_fonc(char *nom, n_type *t, n_l_dec *param, n_l_dec *variables, n_prog *corps){
    n_fun_dec *n = malloc(sizeof(n_fun_dec)); CHECK_PTR(n);
    n->nom = nom;
    n->type = t;
    n->param = param;
    n->variables = variables;
    n->corps = corps;
    ajoutefonction(nom,t,param);
    DPRINT;return n;
}

/** Create a list of variables declarations with @param tete as fist element and @param queue as pointer to the next element
 * @return The aforementionned object*/
n_l_dec *cree_n_l_dec(n_dec *tete, n_l_dec *queue){
    n_l_dec *n = malloc(sizeof(n_l_dec)); CHECK_PTR(n);
    n->tete = tete;
    n->queue = queue;
    DPRINT;return n;
}

/** Create a list of function declarations with @param tete as fist element and @param queue as pointer to the next element
 * @return The aforementionned object*/
n_l_fun_dec *cree_n_l_fun_dec(n_fun_dec *tete, n_l_fun_dec *queue){
    n_l_fun_dec *n = malloc(sizeof(n_l_fun_dec)); CHECK_PTR(n);
    n->tete = tete;
    n->queue = queue;
    DPRINT;return n;
}
