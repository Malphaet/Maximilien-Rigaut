#include <stdio.h>
#include <stdlib.h>
#include "lexemes.h"
#include "yylex.h"

extern char yytext[100];
FILE *yyin;

/* unite lexicale (lexeme) en cours */
int uc; 

/* affichage des balises */
void baliseouvrante(char *s);
void balisefermante(char *s);
void balisefeuille(char *s, char *val);

/* liste des fonctions liées au règles */
void programme();
/* ... */



/********** main */

int main(int argc, char **argv) {
  yyin = fopen(argv[1], "r");
  if(yyin == NULL){
    fprintf(stderr, "impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }

  uc = yylex(); // première fois
  programme(); 
  return 0;
}


/********** Début des règles */

void programme(){
/*
  Programme -> PROGRAM ID ';' Corps '.'
*/
  char *s = "programme";
  baliseouvrante(s);

  /* ... */

  balisefermante(s);
}

/*
  Corps ->[ VAR ListeDeclVar ';' ] { DeclProcFun ';' } BlocInstr
  ListeDeclVar -> DeclVar{ ';' DeclVar }
  DeclVar -> ID { ',' ID } ':' Type
  Type -> INTEGER | BOOLEAN | ARRAY '[' NUMERAL '..' NUMERAL ']' OF Type
  DeclProcFun -> DeclProcedure | DeclFunction 
  DeclProcedure -> PROCEDURE ID [ '(' ListeDeclVar ')' ] ; Corps 
  DeclFunction -> FUNCTION ID '(' ListeDeclVar ')' ':' Type ';' Corps 
  
  Instruction -> AffectInstr | AppelProcedure | IfInstr | WhileInstr | BlocInstr | Empty 
  AffectInstr -> Variable AFFECT Expression 
  AppelProcedure -> ID [ '(' ParameterList ')' ] 
  AppelFunction -> ID '(' ListeParam ')'
  ListeParam -> Expression [ ',' Expression ] 
  IfInstr -> IF Expression THEN Instruction [ ELSE Instruction ] 
  WhileInstr -> WHILE Expression DO Instruction 
  BlocInstr -> BEGIN Instruction { ';' Instruction } END 
  
  Expression -> Simpleexpression [ Relation Simpleexpression ]
  Relation -> '<' | '=' | '>' | INFEG | DIFF | SUPEG 
  Simpleexpression -> Facteur [ OpAdd Simpleexpression ] 
  OpAdd -> '+' | '-' | OR
  Facteur -> [ RelationUnaire ] Predicat [ OpMult Facteur ] 
  RelationUnaire -> '-' | NOT
  OpMult -> '*' | DIV | MOD | AND
  Predicat -> AppelFunction | NUMERAL | Variable | '(' Expression ')' 
  Variable -> ID [ '[' Expression ']' ] 
*/

/********** Affichage */

void baliseouvrante(char *s){
  printf("<%s>\n",s);
}

void balisefermante(char *s){
  printf("</%s>\n",s);
}

void balisefeuille(char *s, char *val){
  printf("<%s>%s</%s>\n",s , val, s);
}

