#include <stdio.h>
#include <math.h>
#include "bisnwt.h"

#define TOL 1e-12
#define MAXIT 10

double funcio (double x, void *prm) {
   return exp(x)-2;
}

double derivada (double x, void *prm) {
   return exp(x);
}

int main (void) {

   double a=-9, b=1, arrel, delta=0.01;
   int aux; 
   aux = bisnwt(a,b,&arrel,&delta,TOL,MAXIT,&funcio,&derivada,NULL);
   printf(" n iterats %d \n", aux); 
   return 0;	

}
