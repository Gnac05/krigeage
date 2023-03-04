#include "main.h"

double g_spline_linear(double xi, double xj){
	double h = abs(xi - xj);
	return h;
}

double g_spline_cubique(double xi, double xj){
	double h = abs(xi - xj);
	return power(h,3);
}
