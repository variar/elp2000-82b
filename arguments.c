/*
 * arguments.c
 * Created by Serhii Tsyba (sertsy@gmail.com) on 08.06.10.
 */

#include "arguments.h"

/*
 * Precession constant in J2000 (p).
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP version ELP 2000-82B, 2001 (1985), p. 8
 */
static const double precession_constant = 5029.0966;

/*
 * Coefficients of the ELP theory arguments W₁, W₂, W₃, T and ϖ' axpressed in arceconds.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP version ELP 2000-82B, 2001 (1985), p. 10
 */
static double elp2000_arguments_coefficients[TOTAL_ELP2000_ARGUMENTS * FULL_SERIES_TOTAL_TERMS] = {
    // coefficients of the mean mean longitude of the Moon (W₁)
    785939.95571, 1732559343.73604, -5.8883, 0.006604, -0.00003169,
    // coefficients of the mean longitude of the lunar perigee (W₂)
    300071.67475, 14643420.2632, -38.2776, -0.045047, 0.00021301,
    // coefficients of the mean longitude of the lunar ascending node (W₃)
    450160.39816, -6967919.3622, 6.3622, 0.007625, -0.00003586,
    // coefficients of the mean heliocentric mean longitude of the Earth-Moon  barycenter (T)
    361679.22059, 129597742.2758, -0.0202, 0.000009, 0.00000015,
    // coefficients of the mean longitude of the perhelion of the Earth-Moon barycenter (ϖ')
    370574.42753, 1161.2283, 0.5327, -0.000138, 0.0
};

/*
 * Coefficients of the planetary arguments from semi-analytical planetary solution VSOP82 developed by P. Bretagnon
 * expressed in arcseconds.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP version ELP 2000-82B, 2001 (1985), p. 7
 */
static double planetary_arguments_coefficients[TOTAL_PLANETARY_ARGUMENTS * LINEAR_SERIES_TOTAL_TERMS] = {
    908103.25986, 538101628.68898,    // Mercury
    655127.28305, 210664136.43355,    // Venus
    361679.22059, 129597742.2758,     // Earth (T from ELP2000 arguments)
    1279559.78866, 68905077.59284,    // Mars
    123665.34212, 10925660.42861,     // Jupiter
    180278.89694, 4399609.65932,      // Saturn
    1130598.01841, 1542481.19393,     // Uranus
    1095655.19575, 786550.32074       // Neptune
};

double compute_precession_argument(double t)
{
    int i;                      // loop index variable
    double tn;                  // progreesive variable holding n-th power of t at n-th iteration of the loop
    double w1;                  // mean mean longitude of the Moon (W₁ of ELP arguments)

    // computing W₁ of ELP arguments reduced to linear terms
    for (i = 0, w1 = 0.0, tn = 1.0; i < LINEAR_SERIES_TOTAL_TERMS; i++, tn *= t)
        w1 += elp2000_arguments_coefficients[W1 * TOTAL_ELP2000_ARGUMENTS + i] * tn;

    // computing precession argument ζ = W₁ + pt
    return w1 + precession_constant * t;
}

void compute_elp2000_arguments(double t, int n, double arguments[])
{
    int i, j;                   // loop index variables
    double tn;                  // progreesive variable holding n-th power of t at n-th iteration of the loop

    // computing variables W₁ through ϖ'
    for (i = W1; i <= OBP; i++){
        for (j = 0, arguments[i] = 0.0, tn = 1.0; j < n; j++, tn *= t)
            arguments[i] += elp2000_arguments_coefficients[i * 5 + j] * tn;
    }
}

void compute_delaunay_arguments(double t, int n, double arguments[])
{
    double elp2000_arguments[TOTAL_ELP2000_ARGUMENTS];    // ELP 2000 arguments

    // computing ELP arguments
    compute_elp2000_arguments(t, n, elp2000_arguments);

    // computing Delaunay arguments from ELP arguments
    // D = W₁ - T + π (π = 648000")
    arguments[D] = elp2000_arguments[W1] - elp2000_arguments[T] + 648000.0;
    // l' = T - ϖ'
    arguments[LP] = elp2000_arguments[T] - elp2000_arguments[OBP];
    // l = W₁ - W₂
    arguments[L] = elp2000_arguments[W1] - elp2000_arguments[W2];
    // F = W₁ - W₃
    arguments[F] = elp2000_arguments[W1] - elp2000_arguments[W3];
}

void compute_planetary_arguments(double t, double arguments[])
{
    int i;                      // loop index variable

    // computing planetary arguments, which are given by linear polynomials, i.e. λ = λ₀ + λ₁ * t.
    for (i = 0; i < TOTAL_PLANETARY_ARGUMENTS; i++){
        arguments[i] = planetary_arguments_coefficients[i * 2];
        arguments[i] += planetary_arguments_coefficients[i * 2 + 1] * t;
    }
}