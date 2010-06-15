/*
 *  arguments.c
 *  Created by Serhii Tsyba on 08.06.10.
 */

#include "arguments.h"

/*
 * Precession constant in J2000 (p).
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 8
 */
static const double precession_constant = 5029.0966;

/*
 * Table of coefficients of series for arguments of ELP theory. Units are
 * arcseconds. Last coefficient for ῶ' (0.0) are added for consistiency.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 10
 */
static double elp2000_arguments_coefficients[TOTAL_ELP2000_ARGUMENTS][FULL_SERIES_TOTAL_TERMS] = {
    // Mean mean longitude of the Moon (W₁) coefficients
    {785939.95571, 1732559343.73604, -5.8883, 0.006604, -0.00003169},
    // Mean longitude of the lunar perigee (W₂) coefficients
    {300071.67475, 14643420.2632, -38.2776, -0.045047, 0.00021301},
    // Mean longitude of the lunar ascending node (W₃) coefficients
    {450160.39816, -6967919.3622, 6.3622, 0.007625, -0.00003586},
    // Mean heliocentric mean longitude of the Earth-Moon  barycenter (T) coefficients
    {361679.22059, 129597742.2758, -0.0202, 0.000009, 0.00000015},
    // Mean longitude of the perhelion of the Earth-Moon barycenter (ῶ') coefficients
    {370574.42753, 1161.2283, 0.5327, -0.000138, 0.0}
};

/*
 * Table of coefficients of series for Delaunay arguments. Units are arcseconds.
 * Last coefficient for l' (0.0) are added for consistiency.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 10
 */
static double delaunay_arguments_coefficients[TOTAL_DELAUNAY_ARGUMENTS][FULL_SERIES_TOTAL_TERMS] = {
    // Mean (solar) elongation of the Moon (D = W₁ - T + π) coefficients
    {1072260.735120, 1602961601.4603, -5.8681, 0.006595, -0.00003184},
    // Mean anomaly of the Sun (l' = T - ῶ') coefficients
    {1287104.793060, 129596581.0474, -0.5529, 0.000147, 0.0},
    // Mean anomaly of the Moon (l = W₁ - W₂) coefficients
    {485868.280960, 1717915923.4728, 323893, 0.051651, -0.0002447},
    // Mean argument of latitude of the Moon (F = W₁ - W₃) coefficients
    {335779.557550, 1739527263.0983, -12.2505, -0.001021, 0.00000417}
};

/*
 * Planetary longitudes in J2000 and mean their motions. Units are arcsenconds
 * for longitudes and arcseconds / cy for motions.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 7
 */
static double planetary_arguments_coefficients[TOTAL_PLANETARY_ARGUMENTS][LINEAR_SERIES_TOTAL_TERMS] = {
    {908103.25986, 538101628.68898},    // Mercury
    {655127.28305, 210664136.43355},    // Venus
    {361679.22059, 129597742.2758},     // Earth (T from ELP2000 arguments)
    {1279559.78866, 68905077.59284},    // Mars
    {123665.34212, 10925660.42861},     // Jupiter
    {180278.89694, 4399609.65932},      // Saturn
    {1130598.01841, 1542481.19393},     // Uranus
    {1095655.19575, 786550.32074}       // Neptune
};

double compute_precession_argument(double t)
{
    int i;          // loop index variable
    double tn;      // progreesive variable holding n-th power of t at n-th
    double w1;      // Moon mean mean longitude (W₁ of ELP arguments)
    
    // computing W₁ of ELP arguments reduced to linear terms
    for (i = 0, w1 = 0.0, tn = 1.0; i < LINEAR_SERIES_TOTAL_TERMS; i++, tn *= t)
        w1 += elp2000_arguments_coefficients[W1][i] * tn;
    
    // computing precession argument
    return w1 + precession_constant * t;
}

void compute_elp2000_arguments(double t, int n, double arguments[])
{
    int i, j;       // loop index variables
    double tn;      // progreesive variable holding n-th power of t at n-th
                    // iteration of the loop (i.e. for n+1 term of the serie)
    
    // computing variables W₁ through ϖ'
    for (i = W1; i <= OBP; i++){
        for (j = 0, arguments[i] = 0.0, tn = 1.0; j < n; j++, tn *= t)
            arguments[i] += elp2000_arguments_coefficients[i][j] * tn;
    }
}

void compute_delaunay_arguments(double t, int n, double arguments[])
{
    // variable that holds intermediate ELP arguments
    double elp2000_arguments[TOTAL_ELP2000_ARGUMENTS];
    
    // computing ELP arguments
    compute_elp2000_arguments(t, n, elp2000_arguments);
    
    // computing Delaunay arguments from ELP arguments
    // 180.0 * 3600.0 is π in arcseconds
    arguments[D] = elp2000_arguments[W1] - elp2000_arguments[T] + 180.0 * 3600.0;
    arguments[LP] = elp2000_arguments[T] - elp2000_arguments[OBP];
    arguments[L] = elp2000_arguments[W1] - elp2000_arguments[W2];
    arguments[F] = elp2000_arguments[W1] - elp2000_arguments[W3];
    
    /* 
     NOTE!
     
     For some reason computing Delaunay arguments using series and terms
     provided yeilds in a non consistent result (for instant, for
     t = 0.477905544147844) for the argument l'. Namely, value computed using
     series differs from value computed from Delaunay arguments (l' = T - ϖ').
     The following code is kept for consistency.

     int i, j;       // loop index variables
     double tn;      // progreesive variable holding n-th power of t at n-th
                     // iteration of the loop (i.e. for n+1 term of the serie)
    
     for (i = 0; i < TOTAL_DELAUNAY_ARGUMENTS; i++){
         for (j = 0, arguments[i] = 0.0, tn = 1.0; j < n; j++, tn *= t)
             arguments[i] += delaunay_arguments_coefficients[i][j] * tn;
     }
    */
}

void compute_planetary_arguments(double t, double arguments[])
{
    int i;          // loop index variable
    
    // computing planetary arguments, they are represented by
    // linear series, i.e. λ = λ₀ + λ₁ * t.
    for (i = 0; i < TOTAL_PLANETARY_ARGUMENTS; i++){
        arguments[i] = planetary_arguments_coefficients[i][0];
        arguments[i] += planetary_arguments_coefficients[i][1] * t;
    }
}