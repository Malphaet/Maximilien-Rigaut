/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exo2                  */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	double a,b,c;
	printf("Entrez un nombre\n");
	scanf("%lf",&a);
	printf("Entrez un autre nombre\n");
	scanf("%lf",&b);
	c=a*b;
	if(c>0) c=1;
	else c=-1;
	printf("Resultat: %f\n",c);
	return 0;
}
