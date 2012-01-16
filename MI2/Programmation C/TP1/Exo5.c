/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exo5                  */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	int vals[5]={500,200,20,4,2};
	int nb[5]={0,0,0,0,0};
	int size=5; /* Size of arrays */
	int somme,i,sum;
	printf("Entrez une somme: ");
	scanf("%i",&somme);
	i=0; sum=somme; /*On conserve trace de la valeur initiale */
	for(i=0;i<size;i++){
		nb[i]=somme/vals[i];
		somme%=vals[i];
		if (!somme) break;
	}
	printf("La somme %i, se decompose en :\n",sum);
	for(i=0;i<size;i++){
		if (nb[i]>1) printf("    %i billets de %i\n",nb[i],vals[i]);
		else printf("    %i billet de %i\n",nb[i],vals[i]);
	}
	printf("    Reste %i\n",somme);
	return 0;
}
