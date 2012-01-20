/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TP1 - Exo 4                 */
/*-----------------------------*/


#include <stdio.h>

int main(void){
	int i,n;
	unsigned long int temp=1;
	printf("Entrez un nombre: ");
	scanf("%i",&n);
	for(i=1;i<=n;i++){
		temp=temp<<1;
		printf("2^%i=%lu\n",i,temp);
	}
	return 0;
}
