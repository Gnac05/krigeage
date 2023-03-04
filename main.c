#include "main.h"

int main(){
	double X[5] = {0,1,2,3,4};
	double F[5] = {0,1,1,2,2};
	printf("SPLINE LINEAR\n");
	metho_krigeage(g_spline_linear, 1, 1, &X[0], &F[0], 5);
	
	printf("\n\nSPLINE CUBIQUE\n");
	metho_krigeage(g_spline_cubique, 1, 1, &X[0], &F[0], 5);
}
