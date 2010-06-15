/*
 *  arguments.h
 *  Created by Serhii Tsyba (sertsy@gmail.com) on 26.05.10.
 *
 * This file containes data and routines needed to compute the arguments of the
 * ELP theory:
 *      a) ELP arguments: W₁, W₂, W₃, T and ϖ. These are used to compute
 *         Delaunay arguments (see below). W₁ is also used to compute the
 *         longitude of the Moon's position.
 *      b) Delaunay arguments: D, l', l and F. These are used to compute the
 *         argument of the sine (or cosine) when computing Fourier and/or
 *         Poisson series.
 *      c) Planetary arguments for all eight planets are used when computing
 *         the argument of the sine of planetary perturbations series.
 *
 * Three functions are provided to compute each set of the corresponding
 * arguments. Arguments are calculated from polinomyal functions of time:
 *
 *                  λ = λ₀ + λ₁t + λ₂t² + λ₃t³ + λ₄t⁴
 *
 * where coefficients λᵢ are given constants.
 * t is the amount of Julian centuries since the beginning pf the epoch J2000.
 *
 * Functions may compute ELP and Delaunay arguments using up to five elements
 * in a serie. This is specified as a second parameter of each corresponding
 * function. Planetary arguments can only be computed with linear polynomials.
 *
 * For each of arguments arrays enumerations are given for more convinient
 * access.
 *
 * Both data and outputs of the functions are measured in arcseconds.
 */

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#define TOTAL_ELP2000_ARGUMENTS 5
#define TOTAL_DELAUNAY_ARGUMENTS 4
#define TOTAL_PLANETARY_ARGUMENTS 8

#define FULL_SERIES_TOTAL_TERMS 5
#define LINEAR_SERIES_TOTAL_TERMS 2

/*
 * An enumeration provided for convinient access to ELP2000 arguments
 * coefficients data.
 */
enum ELP_arguments {
    W1 = 0,         // mean mean longitude of the Moon
    W2 = 1,         // mean longitude of the lunar perigee
    W3,             // mean longitude of the lunar ascending node
    T,              // mean heliocentric mean longitude of the Earth-Moon
                    // barycenter
    OBP = 4,        // mean longitude of the perhelion of the Earth-Moon
                    // barycenter
};

/*
 * An enumeration provided for convinient access to Delaunay arguments
 * coefficients data.
 */
enum Delaunay_arguments {
    D = 0,      // Moon's mean (solar) elongation
    LP = 1,     // Sun's mean anomaly
    L,          // Moon's mean anomaly
    F = 3       // Moon's mean argument of latitude
};

/*
 * An enumeration provided for convinient access to planetary longiude and
 * motions data.
 */
enum Planets {
    MERCURY = 0,
    VENUS = 1,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE = 6
};
/*
 * Computes precession argument used in calculating Earth figure perturbations.
 * Argument is computed using linear series (i.e. up to linear power of t).
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 5
 */
double compute_precession_argument(double t);

/*
 * Computes arguments of the ELP theory (W₁, W₂, W₃, T and ϖ'). They are used
 * to compute Delaunay arguments as well as W₁ is used directly in computation
 * of heliocentric lunar longitude.
 * Arguments are computed for a given time instant t, measured in Julian
 * centuries since the beginning of the epoch J2000.
 * ELP uses a series to compute these arguments. Full series consist of five
 * elements, i.e. till fourth power of t. Linear series (two terms only) are
 * used when computing anything besides Main Problem. Use defines
 * FULL_SERIES_TOTAL_TERMS and LINEAR_SERIES_TOTAL_TERMS to specify desired
 * amount of elements in the series.
 * Output is written into array arguments, which should contain at least the
 * amount of elements that series length specifies. Units are arcseconds.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 4
 */
void compute_elp2000_arguments(double t, int n, double arguments[]);

/*
 * Computes Delaunay arguments (D, l', l, F). Delaunay arguments are computed
 * from ELP arguments given their formulas and not from series terms.
 * Never the less, terms for delaunay arguments are given here for consistency.
 * Arguments are computed for a given time instant t, measured in Julian
 * centuries since the beginning of the epoch J2000.
 * ELP uses a series to compute these arguments. Full series consist of five
 * elements, i.e. till fourth power of t. Linear series (two terms only) are
 * used when computing anything besides Main Problem. Use defines
 * FULL_SERIES_TOTAL_TERMS and LINEAR_SERIES_TOTAL_TERMS to specify desired
 * amount of elements in the series.
 * Output is written into array arguments, which should contain at least the
 * amount of elements that series length specifies. Units are arcseconds.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 4
 */void compute_delaunay_arguments(double t, int n, double arguments[]);

/*
 * Computes planetary arguments needed for computation of planetary
 * perturbations. Terms for such computations are taken from VSOP87 theory
 * up to a second term.
 * Arguments are computed for a given time instant t, measured in Julian
 * centuries since the beginning of the epoch J2000.
 * Output is written into array arguments, which should contain at least the
 * amount of elements that series length specifies. Units are arcseconds.
 *
 * Source: M. Chapront-Touzè, J. Chapront, G. Francou. Lunar Solution ELP
 *         version ELP 2000-82B, 2001 (1985), p. 5
 */
void compute_planetary_arguments(double t, double arguments[]);

#endif // ARGUMENTS_H