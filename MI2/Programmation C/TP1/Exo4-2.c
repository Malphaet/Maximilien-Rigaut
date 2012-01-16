/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exo 4                 */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	int i,n,x;
	unsigned long int temp=1;
	printf("Entrez un nombre: ");
	scanf("%i",&x);
	printf("Entrez une puissance: ");
	scanf("%i",&n);
	for(i=1;i<=n;i++){
		temp*=x;
		printf("%i^%i=%lu\n",x,i,temp);
	}
	return 0;
}
