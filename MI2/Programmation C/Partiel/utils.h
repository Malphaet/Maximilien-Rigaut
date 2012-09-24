/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

#ifndef __UTILS__
#define __UTILS__
/* ========= Defines ==========*/

#define TEST(p) if (!(p)) {printf("Error in file %s.\n    > function:%s - line:%d\n    > NULL pointer error\n",__FILE__, __func__,__LINE__); exit(EXIT_FAILURE);}

#endif
