/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* TD2                         */
/*-----------------------------*/

/* ========= Includes =========*/

#include <stdio.h>

/* ======== Prototype =========*/
void shorten(int A[], int sizeA);

/* =========== Main ===========*/

int main(void){
	int A[10]={13,0,0,1,0,0,5,6};
	int i;
	shorten(A,10);
	for (i=0;i<8;i++){
	    printf("%d , ",A[i]);
	}
	printf("\n");
	return 0;
}

/* ========= Functions ========*/

void shorten(int A[], int sizeA){
    int w;
    int r;
    int succes=0;
    for (w=r=0;w<sizeA;w++){
        if (A[r]==0){
            for (succes=0;w<sizeA;w++){
                if (A[w]!=0){
                    succes=1;
                    A[r]=A[w];
                    A[w]=0;
                    break;
                }
            }
            if (!succes) return;
        }
        r++;
    }
}
