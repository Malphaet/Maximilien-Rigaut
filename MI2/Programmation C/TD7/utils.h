/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

#ifndef __UTILS__
#define __UTILS__
/* ========= Defines ==========*/
#define deploy 0

#define TEST(p) if ((p)==NULL) {printf("Error in file %s.\n    > function:%s - line:%d\n    > NULL pointer error\n",__FILE__, __func__,__LINE__); exit(EXIT_FAILURE);}

#if deploy
	#define OUT(a,b) {FILE *file = fopen("./output.txt","a+"); fprintf(file,(a),(b)); fclose(file);};
#else
	#define OUT(a,b) printf(file,(a),(b));
#endif

#endif
