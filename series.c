/*
 *  series.c
 *  Created by Serhii Tsyba on 08.06.10.
 */

#include "series.h"
#include "arguments.h"
#include <math.h>

#define PI 3.14159265358    // numeric value of π

double radian(double d)
{
    // 1 radian = π/180°
    return d * PI / 180.0;
}

double compute_serie_a_sin(double delaunay_arguments[], int multipliers[][4],
                           double coefficients[][7], int n)
{
    double acc;     // accumualtive variable holding the sum of a serie
    double arg;     // accumulating variable holding the argument of a sine
    int i, j;       // loop index variables
    
    for (i = 0, acc = 0.0; i < n; i++){
        // adding Delaunay arguments
        for (j = D, arg = 0.0; j <= F; j++)
            arg += multipliers[i][j] * delaunay_arguments[j];
        
        // computing the current term of the serie
        acc += coefficients[i][0] * sin(radian(arg / ARCSECONDS_IN_DEGREE));
    }
    
    return acc;
}

double compute_serie_a_cos(double delaunay_arguments[], int multipliers[][4],
                           double coefficients[][7], int n)
{
    double acc;     // accumualtive variable holding the sum of a serie
    double arg;     // accumulating variable holding the argument of a cosine
    int i, j;       // loop index variables
    
    for (i = 0, acc = 0.0; i < n; i++){
        // adding Delaunay arguments
        for (j = D, arg = 0.0; j <= F; j++)
            arg += multipliers[i][j] * delaunay_arguments[j];
        
        // computing the current term of the serie
        acc += coefficients[i][0] * cos(radian(arg / ARCSECONDS_IN_DEGREE));
    }
    
    return acc;
}

double compute_serie_b(double precession, double delaunay_arguments[],
                       int multipliers[][5], double coefficients[][3], int n)
{
    double acc;     // accumualtive variable holding the sum of a serie
    double arg;     // accumulating variable holding the argument of a sine
    int i, j;       // loop index variables
    
    for (i = 0, acc = 0.0; i < n; i++){
        // adding precession argument
        arg = multipliers[i][0] * precession;
        
        // adding Delaunay arguments
        for (j = D; j <= F; j++)
            arg += multipliers[i][j + 1] * delaunay_arguments[j];
        
        // computing the current term of the serie
        acc += coefficients[i][1] * sin(radian(arg / ARCSECONDS_IN_DEGREE) +
                                        radian(coefficients[i][0]));
    }
    
    return acc;
}

double compute_serie_c(double planetary_arguments[], double delaunay_arguments[],
                       int multipliers[][11], double coefficients[][3], int n)
{
    double acc;     // accumualtive variable holding the sum of a serie
    double arg;     // accumulating variable holding the argument of a sine
    int i, j;       // loop index variables
    
    for (i = 0; acc = 0.0; i < n, i++){
        // adding planetary arguments
        for (j = MERCURY, arg = 0.0; j <= NEPTUNE; j++)
            arg += multipliers[i][j] * planetary_arguments[j];
        
        // adding Delaunay arguments except l'
        arg += multipliers[i][j++] * delaunay_arguments[D];
        arg += multipliers[i][j++] * delaunay_arguments[L];
        arg += multipliers[i][j++] * delaunay_arguments[F];
        
        // computing the current term of the serie
        acc += coefficients[i][1] * sin(radian(arg / ARCSECONDS_IN_DEGREE) +
                                        radian(coefficients[i][0]));
    }
    
    return acc;
}

double compute_serie_d(double planetary_arguments[], double delaunay_arguments[],
                       int multipliers[][11], double coefficients[][3], int n)
{
    double acc;     // accumualtive variable holding the sum of a serie
    double arg;     // accumulating variable holding the argument of a sine
    int i, j;       // loop index variables
    
    for (i = 0; acc = 0.0; i < n, i++){
        // adding planetary arguments except Neptune
        for (j = MERCURY, arg = 0.0; j <= URANUS; j++)
            arg += multipliers[i][j] * planetary_arguments[j];
        
        // adding Delaunay arguments
        for (j = D; j <= F; j++)
            arg += multipliers[i][TOTAL_PLANETARY_ARGUMENTS + j] * delaunay_arguments[j];
        
        // computing the current term of the serie
        acc += coefficients[i][1] * sin(radian(arg / ARCSECONDS_IN_DEGREE) +
                                        radian(coefficients[i][0]));
    }
    
    return acc;
}