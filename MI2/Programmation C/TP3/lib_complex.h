/*-----------------------------*/
/* Copyleft Maximilien Rigaut  */
/*-----------------------------*/

#ifndef LIB_COMPLEX_H
#define LIB_COMPLEX_H
/* ========= Defines ==========*/
/* ========= Typedef ==========*/
typedef struct {double re,im;} Complex;

/* ======== Prototype =========*/
void printComplex(Complex c);
Complex addComplex(Complex c1,Complex c2);
Complex mulComplex(Complex c1, Complex c2);
Complex double2Complex(double f);

Complex subComplex(Complex c1, Complex c2);
Complex divComplex(Complex c1, Complex c2);
double argComplex(Complex c);
double modComplex(Complex c);
int isequalComplex(Complex c1,Complex c2);

#endif
