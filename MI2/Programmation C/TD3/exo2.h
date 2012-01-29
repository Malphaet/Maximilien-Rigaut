/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/* Model                       */
/*-----------------------------*/
#ifndef EXO2_H
	#define EXO2_H

	#ifdef DEBUG
		#define D_PRINT printf("n=%d at %d\n",n,__LINE__);
	#else
		#define D_PRINT
	#endif

	#define x 1+2

	#define A 0
	#define B A
	#define A 1

#endif
