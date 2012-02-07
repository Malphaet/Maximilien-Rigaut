/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

#ifndef TP4
#define TP4
/* ========= Includes =========*/

/* ========= Defines ==========*/
/* ========= Typedef ==========*/
/* ======== Prototype =========*/
int string_length(char *s);
int string_cmp(char *s1,char *s2);
int string_length_cmp(char *s1,char *s2);

void string_flip(char *s);

void print_string(char *s);
void print_table_strings(char **t,int N);
void print_slice(char *s,int N);

void melting_sort(char **t1,int N);
void melt(char **t1,char **t2,int N1,int N2);

#endif
