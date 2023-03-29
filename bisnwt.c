#include <stdio.h>
#include <math.h>
#include "bisnwt.h"



int bisnwt (double a, double b, double *arr, double *dlt, double tol, 
			int maxit, double (*f)(double,void*),
			double (*df)(double,void*), void *prm) {

	double dif = a - b; 
	double c = (a + b)/2; 
	double f_a = (*f)(a,prm);  
	double f_c; 
	
	while (1) {	
		//printf("Bisecció; \n"); 		
		/*mentre la longitud de l'interval faig Bisecció*/
		while (fabs(dif) > *dlt){
			c = (a + b)/2; 
			//printf("a  %5.5f | b  %5.5f | c -> %5.5f \n", a, b, c); 
			f_c = (*f)(c, prm); 
			if (f_a*f_c <= 0 ){
				b = c; 
				dif = a -b; 
			} else {
				a = c; 
				f_a = (*f)(a,prm); 
				dif  = a - b; 
			}						
		}
		//printf("\n"); 
		/* Si la delta és més petita que la tolerància,	l'apuntador *arr
		 quedarà apuntant al punt mitja de l'últim interval de la bisecció */ 
							
		if (*dlt <= tol){
			*arr = c; 
			return -1; 
		} else {
			//printf("Newton; \n");
			//printf("valor de c %f \n", c); 
			/* Faig bisecció a partir de la c, fins que s'hagi convergit o 
			 a un màxim d'iterats */ 
			double x0, x1; 
			x1 = c; 
			for (int i = 1; i <= maxit ; i++ ){
				
				x0 = x1; 
				//printf("x0 -> %5.5f |",x0); 
				x1 = x0 - ((*f)(x0,prm)/(*df)(x0,prm)); 
				//printf(" x1 -> %5.5f  \n", x1);  
				//printf("dif   %f \n", fabs(x1 - x0)); 
				if (fabs(x1 - x0) < tol){
					*arr = x1;
					//printf("  i  %d  \n", i);  
					return i; 					
				}
			}
			//printf("\n"); 	
			/* En el cas en què no s'hagi convergit, divideixo la delta
			 * entre dos i torno a començar */		
			*dlt /= 2; 
			//printf("Delta actual %5.5f \n\n", *dlt); 
		}	
	}
}



