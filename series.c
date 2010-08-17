/*
 * series.c
 * Created by Serhii Tsyba (sertsy@gmail.com) on 08.06.10.
 */

#include "series.h"
#include "arguments.h"
#include <math.h>

#define SERIE_A_TOTAL_MULTIPLIERS 4
#define SERIE_A_TOTAL_COEFFICIENTS 7
#define SERIE_B_TOTAL_MULTIPLIERS 5
#define SERIE_B_TOTAL_COEFFICIENTS 3
#define SERIE_C_TOTAL_MULTIPLIERS 11
#define SERIE_C_TOTAL_COEFFICIENTS 3
#define SERIE_D_TOTAL_MULTIPLIERS 11
#define SERIE_D_TOTAL_COEFFICIENTS 3

#define MERCURY 0
#define URANUS 6
#define NEPTUNE 7

double compute_serie_a_sin(double delaunay_arguments[], int multipliers[], double coefficients[], int n)
{
    double acc;                 // accumualtive variable holding the sum of a serie
    double arg;                 // accumulating variable holding the argument of a sine
    int i, j;                   // loop index variables
    
    for (i = 0, acc = 0.0; i < n; i++){
        // adding Delaunay arguments
        for (j = D, arg = 0.0; j <= F; j++)
            arg += multipliers[i * SERIE_A_TOTAL_MULTIPLIERS + j] * delaunay_arguments[j];
        
        // converting argument from arcseconds to radians (π = 648000")
        arg *= M_PI / 648000.0;

        // computing the current term of the serie
        acc += coefficients[i * SERIE_A_TOTAL_COEFFICIENTS] * sin(arg);
    }

    return acc;
}

double compute_serie_a_cos(double delaunay_arguments[], int multipliers[], double coefficients[], int n)
{
    double acc;                 // accumualtive variable holding the sum of a serie
    double arg;                 // accumulating variable holding the argument of a cosine
    int i, j;                   // loop index variables

    for (i = 0, acc = 0.0; i < n; i++){
        // adding Delaunay arguments
        for (j = D, arg = 0.0; j <= F; j++)
            arg += multipliers[i * SERIE_A_TOTAL_MULTIPLIERS + j] * delaunay_arguments[j];
        
        // converting argument from arcseconds to radians (π = 648000")
        arg *= M_PI / 648000.0;

        // computing the current term of the serie
        acc += coefficients[i * SERIE_A_TOTAL_COEFFICIENTS] * cos(arg);
    }

    return acc;
}

double compute_serie_b(double precession, double delaunay_arguments[], int multipliers[], double coefficients[], int n)
{
    double acc;                 // accumualtive variable holding the sum of a serie
    double arg;                 // accumulating variable holding the argument of a sine
    int i, j;                   // loop index variables

    for (i = 0, acc = 0.0; i < n; i++){
        // adding precession argument
        arg = multipliers[i * SERIE_B_TOTAL_MULTIPLIERS] * precession;

        // adding Delaunay arguments
        for (j = D; j <= F; j++)
            arg += multipliers[i * SERIE_B_TOTAL_MULTIPLIERS + j + 1] * delaunay_arguments[j];
        
        // adding phase to the value of the argument
        arg += coefficients[i * SERIE_B_TOTAL_COEFFICIENTS];
        
        // converting argument from arcseconds to radians (π = 648000")
        arg *= M_PI / 648000.0;

        // computing the current term of the serie
        acc += coefficients[i * SERIE_B_TOTAL_COEFFICIENTS + 1] * sin(arg);
    }

    return acc;
}

double compute_serie_c(double planetary_arguments[], double delaunay_arguments[], int multipliers[], double coefficients[], int n)
{
    double acc;                 // accumualtive variable holding the sum of a serie
    double arg;                 // accumulating variable holding the argument of a sine
    int i, j;                   // loop index variables
    
    for (i = 0; acc = 0.0; i < n, i++){
        // adding planetary arguments from Mercury to Neptune
        for (j = MERCURY, arg = 0.0; j <= NEPTUNE; j++)
            arg += multipliers[i * SERIE_C_TOTAL_MULTIPLIERS + j] * planetary_arguments[j];

        // adding Delaunay arguments except l' argument
        arg += multipliers[i * SERIE_C_TOTAL_MULTIPLIERS + j + 1] * delaunay_arguments[D];
        arg += multipliers[i * SERIE_C_TOTAL_MULTIPLIERS + j + 1] * delaunay_arguments[L];
        arg += multipliers[i * SERIE_C_TOTAL_MULTIPLIERS + j + 1] * delaunay_arguments[F];
        
        // adding phase to the value of the argument
        arg += coefficients[i * SERIE_C_TOTAL_COEFFICIENTS];
        
        // converting argument from arcseconds to radians (π = 648000")
        arg *= M_PI / 648000.0;        

        // computing the current term of the serie
        acc += coefficients[i * SERIE_C_TOTAL_COEFFICIENTS + 1] * sin(arg);
    }

    return acc;
}

double compute_serie_d(double planetary_arguments[], double delaunay_arguments[], int multipliers[], double coefficients[], int n)
{
    double acc;             // accumualtive variable holding the sum of a serie
    double arg;             // accumulating variable holding the argument of a sine
    int i, j;               // loop index variables

    for (i = 0; acc = 0.0; i < n, i++){
        // adding planetary arguments from Mercury to Uranus
        for (j = MERCURY, arg = 0.0; j <= URANUS; j++)
            arg += multipliers[i * SERIE_D_TOTAL_MULTIPLIERS + j] * planetary_arguments[j];

        // adding Delaunay arguments
        for (j = D; j <= F; j++)
            arg += multipliers[i * SERIE_D_TOTAL_MULTIPLIERS + TOTAL_PLANETARY_ARGUMENTS + j] * delaunay_arguments[j];
        
        // adding phase to the value of the argument
        arg += coefficients[i * SERIE_D_TOTAL_COEFFICIENTS];
        
        // converting argument from arcseconds to radians (π = 648000")
        arg *= M_PI / 648000.0;

        // computing the current term of the serie
        acc += coefficients[i * SERIE_D_TOTAL_COEFFICIENTS + 1] * sin(arg);
    }

    return acc;
}