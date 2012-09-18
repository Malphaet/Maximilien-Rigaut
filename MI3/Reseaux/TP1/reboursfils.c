/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

/* ========= Defines ==========*/
int countdown(void);

/* =========== Main ===========*/

int main(void){
	int val=1;
	int stat,p,nb_fils=0;
	while (val){
		scanf("%d",&val);
		if (val==0){
			while (nb_fils--) {
				wait(&stat);
			}
			printf("Execution done, you are a wonderful human being.\n");
			exit(0);
		}
		while(val--){
			p=fork();
			if (p==0) {
				countdown();
			}
			nb_fils++;
		}
	}
	return 0;
}

/* ========= Functions ========*/

/* Fils */
int countdown(){
	int i;
	for (i = 10; i > 0; i--) {
		printf("%d\n",i);
		sleep(1);
	}
	exit(0);
}
