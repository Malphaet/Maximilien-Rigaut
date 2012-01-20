/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exo3                  */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	int h,m,s;
	printf("Secondes: ");
	scanf("%i",&s);
	h=s/(60*60);
	s-=h*60*60;
	m=s/60;
	s-=m*60;
	printf("Cela represente %i heures %i minutes et %i secondes\n",h,m,s);
	return 0;
}
