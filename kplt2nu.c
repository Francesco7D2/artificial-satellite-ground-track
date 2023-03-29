#include <stdio.h>
#include <math.h>
#include "bisnwt.h"


#define PI 3.14159265358979323846

#define TOL 1e-12
#define MAXIT 10


typedef struct{
	double M; 
	double e; 
	} kplt_prm; 


double f_Kepler (double E, void *prm) {
   return (E - ((kplt_prm*)prm)->e*(sin(E)) - ((kplt_prm*)prm)->M);
}

double d_Kepler (double E, void *prm) {
   return (1.0  - ((kplt_prm*)prm)->e*(cos(E)));
}



int main (int argc, char *argv[]) {
   double e, T, M0, tf;
   int nt; 
   int i; 
   double M,t_i; 
   double a, b, arrel;  
   double delta=10;
   if (argc<6
         || sscanf(argv[1], "%lf", &e)!=1
         || sscanf(argv[2], "%lf", &T)!=1
         || sscanf(argv[3], "%lf", &M0)!=1
         || sscanf(argv[4], "%lf", &tf)!=1
         || sscanf(argv[5], "%d", &nt)!=1
      ) {
      fprintf(stderr,"%s e T M0 tf nt\n", argv[0]);
      return -1;
   }
/* ... Més coses  ... */
	kplt_prm kepler_prm; 
	kepler_prm.e = e; 
	
	double v; 
	double div, part_e, part_f; 
	double interval = tf/nt; 
	

	 
	 
	for (i = 0; i <= nt;  i++){
		t_i = i*(interval); 
		/*En la memòria s'explica com s'ha arribat a la següent 
		 * expressió per calcular l'anomalia mitjana */
		M = 2*PI*(t_i)/T + M0; 
		a = M - PI; 
		b = M + PI; 
		/* Un cop tenim la M, trobem la E amb ajuda de bisnwt */
		kepler_prm.M = M; 
		bisnwt(a,b,&arrel,&delta,TOL,MAXIT,&f_Kepler,&d_Kepler,&kepler_prm);
		
		
		/*  Calculem els valors que ens serviran per corregir la v */
		div = arrel/(2*PI); 
		part_e = floor(div); 
		part_f = div - part_e;    
		
		/* Calculem la v */
		v = acos((e - cos(arrel))/(e*cos(arrel) - 1.0)); 
		
		/* "Posem" la v a la mitja volta corresponent */
		if (part_f < 0.5) {
			v = v + (2*part_e)*PI ; 
		} else {
			v = -v + (2*part_e + 2)*PI;
		}
		printf("%.16f %.16f %.16f \n", t_i, M, v); 
		/* per mostar a la memòria els resultats
		 * printf("%.5f %.5f %.5f \n", t_i, M, v); */
	}	
   return 0;
}










