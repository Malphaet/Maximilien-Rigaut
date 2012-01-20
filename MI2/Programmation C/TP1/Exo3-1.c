/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exo3                  */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	int h,m,s;
	printf("Heure: ");
	scanf("%i",&h);
	printf("Minute: ");
	scanf("%i",&m);
	printf("Secondes: ");
	scanf("%i",&s);
	printf("Cela represente %i secondes\n",60*60*h+60*m+s);
	return 0;
}
