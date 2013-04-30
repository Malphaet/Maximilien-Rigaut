/** @file arbre.h The syntax tree */
#ifndef __ARBRE__
#define __ARBRE__

/*---------- Typedef -----------*/
typedef struct n_l_instr_ n_l_instr;
typedef struct n_instr_ n_instr;
typedef struct n_exp_ n_exp;
typedef struct n_l_exp_ n_l_exp;
typedef struct n_var_ n_var;
typedef struct n_l_dec_ n_l_dec;
typedef struct n_dec_ n_dec;
typedef struct n_type_ n_type;
typedef struct n_l_fun_dec_ n_l_fun_dec;
typedef struct n_fun_dec_ n_fun_dec;
typedef struct n_prog_ n_prog;
typedef struct n_appel_ n_appel;

/*---------- Structs -----------*/

/** A program object */
struct n_prog_ {
    n_l_dec *variables;     /**< The variables of the said program */
    n_l_fun_dec *fonctions; /**< The functions of the said program */
    n_instr *corps;         /**< The body of the said program (a bloc of instructions) */
};

/** A type object */
struct n_type_ {
    enum {t_int, t_bool, t_array, t_real} type; /**< The type so to speak */
    struct n_type_ *arrayof;            /**< If it's an array: The type of the array's objects */
    int debut;                           /**< The begginning of the array */
    int fin;                             /**< The ending of the said array */
};

/** A variable declaration object */
struct n_dec_ {
    char *nom;              /**< The name of the said variable */
    n_type *type;           /**< The type of the said variable */
};

/** A function declaration object */
struct n_fun_dec_{
    char *nom;              /**< The name of the said function */
    n_type *type;           /**< The return type of the said function */
    n_l_dec *variables;     /**< The variables of the said function */
    n_l_dec *param;         /**< The parameters of the said function */
    n_prog *corps;          /**< The body of the said function */
};

/** A function call object */
struct n_appel_{
    char *fonction;         /**< The name of the said function */
    n_l_exp *args;          /**< The arguments given to the said function */
};

/** Enumeration of all possibles operations */
typedef enum {plus, moins, fois, divise, modulo, egal, diff, inf, sup, infeg, supeg, ou, et, non, negatif,c_int,c_bool,c_real} operation;

/** An expression object */
struct n_exp_ {
    enum{varExp, intExp,realExp, opExp, trueExp, falseExp, appelExp, lireExp} type; /**< The type of the aforementioned expression */
    union{
        struct{operation op; struct n_exp_ *op1; struct n_exp_ *op2;} opExp_;
        n_var *var;     /**< The variable contained by the said expression */
        int entier;     /**< The integer contained by the said expresion */
        double real;    /**< The real contained by the said expresion */
        n_appel *appel; /**< The function call containned by the said expression */
    }u;  /**< The operation of the said expression */
};

/** A variable object (can be a table or simple var) */
struct n_var_ {
    enum {simple, indicee} type;    /**< The nature (array or simple) of the said variable */
    char *nom;                      /**< The name of the said variable */
    n_exp *indice;                  /**< The indice in the array */
};

/** An instruction object (can hold a lot of different instruction) */
struct n_instr_ {
    enum {incrInst,affecteInst,siInst,tantqueInst,appelInst,ecrireInst,videInst,blocInst} 
        type; /**< The nature of the expression */
    union{
        n_exp *incr;
        struct{n_exp *test; struct n_instr_ *alors; struct n_instr_ *sinon;} si_;
        struct{n_exp *test; struct n_instr_ *faire;} tantque_;
        n_appel *appel;
        struct{n_var *var; n_exp *exp;} affecte_;
        struct{n_exp *expression;} retour_;
        struct{n_exp *expression;} ecrire_;
        n_l_instr *liste;
    }u; /**< The instruction itself */
};

/** A list of expression object (as a chain of elements) */
struct n_l_exp_ {
    n_exp *tete;                /**< The first expression */
    struct n_l_exp_ *queue;     /**< The pointer to the next element in the chain */
};

/** A list of instruction object (as a chain of elements) */
struct n_l_instr_ {
    n_instr *tete;              /**< The first instruction */
    struct n_l_instr_ *queue;   /**< The pointer to the next element in the chain */
};

/** A list of variable declaration object (as a chain of elements) */
struct n_l_dec_{
    n_dec *tete;                /**< The first variable */
    struct n_l_dec_ *queue;     /**< The pointer to the next element in the chain */
};

/** A list of function declaration object (as a chain of elements) */
struct n_l_fun_dec_{
    n_fun_dec *tete;            /**< The first function declaration */
    struct n_l_fun_dec_*queue; /**< The pointer to the next element in the chain */
};

/*======= Prototype ==========*/

/*------ PROGRAMME ------*/
n_prog      *cree_n_prog            (n_l_dec *variables, n_l_fun_dec *fonctions, n_instr *corps);

/*------ TYPES ------*/
n_type      *cree_n_type_int        (void);
n_type      *cree_n_type_bool       (void);
n_type      *cree_n_type_real       (void);
n_type      *cree_n_type_array      (n_type *t, int debut, int fin);

/*------ DECLARATIONS ------*/
n_dec       *cree_n_dec_var         (char *nom, n_type *t);
n_fun_dec   *cree_n_dec_fonc        (char *nom, n_type *t, n_l_dec *param, n_l_dec *variables, n_prog *corps);

/*------ EXPRESSIONS ------*/
n_exp       *cree_n_exp_op          (operation type, n_exp *op1, n_exp *op2);
n_exp       *cree_n_exp_entier      (int entier);
n_exp       *cree_n_exp_real        (double real);
n_exp       *cree_n_exp_var         (n_var *var);
n_exp       *cree_n_exp_appel       (n_appel *app);
n_exp       *cree_n_exp_lire        (void);
n_exp       *cree_n_exp_true        (void);
n_exp       *cree_n_exp_false       (void);
n_appel     *cree_n_appel           (char *fonction, n_l_exp *args);
n_var       *cree_n_var_simple      (char *nom);
n_var       *cree_n_var_indicee     (char *nom, n_exp *indice);

/*------ INSTRUCTIONS ------*/

n_instr     *cree_n_instr_incr      (n_exp *incr);
n_instr     *cree_n_instr_si        (n_exp *test, n_instr *alors, n_instr *sinon);
n_instr     *cree_n_instr_bloc      (n_l_instr *liste);
n_instr     *cree_n_instr_tantque   (n_exp *test, n_instr *faire);
n_instr     *cree_n_instr_affect    (n_var *var, n_exp *exp);
n_instr     *cree_n_instr_appel     (n_appel *appel);
n_instr     *cree_n_instr_ecrire    (n_exp *expression);
n_instr     *cree_n_instr_vide      (void);

/*------ LISTES D'OBJETS------*/
n_l_fun_dec *cree_n_l_fun_dec       (n_fun_dec *tete, n_l_fun_dec *queue);
n_l_exp     *cree_n_l_exp           (n_exp *tete, n_l_exp *queue);
n_l_instr   *cree_n_l_instr         (n_instr *tete, n_l_instr *queue);
n_l_dec     *cree_n_l_dec           (n_dec *tete, n_l_dec *queue);
#endif
