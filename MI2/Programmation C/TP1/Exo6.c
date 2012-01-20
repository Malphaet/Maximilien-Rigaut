/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exercice 6            */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	int max,min,sum,nb,i;
	int start;
	float moy;
	i=0; sum=0;
	start=1; /* Initialisation de Max et Min */
	while (1){
		printf("Entrez un nombre: ");
		scanf("%d",&i);
		if (i<0) break;
		if (start) {
			min=max=i;
			start=0;
		}
		if (i<min) min=i;
		if (i>max) max=i;
		sum+=i;
		nb++;
	}
	if (nb>0) moy=(float)sum/nb;
	else moy=0;
	printf("Max=%d, Min=%d, Somme=%d, Moyenne=%f\n",max,min,sum,moy);
	return 0;
}
