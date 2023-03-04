#include <stdio.h> 
#include <stdlib.h>
#include "cblas.h"
#include "lapacke.h"

// Definition of type of function which return double and take two arguments double
typedef double(*callback_g)(double, double);

// fonction power
double power(double base, int exponent);

void metho_krigeage(callback_g g, int nbDim, int deg, double *X, double *F, int nbPoint);

double g_spline_linear(double xi, double xj);

double g_spline_cubique(double xi, double xj);
