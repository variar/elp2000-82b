/*
 * arguments.h
 * Created by Serhii Tsyba (sertsy@gmail.com) on 26.05.10.
 *
 * This file containes routines to compute the arguments of the ELP theory:
 *
 *      a) ELP 2000 arguments:
 *              mean mean longitude of the Moon, denoted as W₁
 *              mean longitude of the lunar perigee, denoted as W₂
 *              mean longitude of the lunar ascending node, denoted as W₃
 *              mean heliocentric mean longitude of the Earth-Moon barycenter, denoted as T
 *              mean longitude of the perhelion of the Earth-Moon barycenter, denoted as ϖ'
 *         arguments W₁, W₂ and W₃ are referred to the ELP 2000 reference frame and arguments T and ϖ' are referred to
 *         the mean dynamycal ecliptic and and equinox of J2000.
 *
 *      b) Delaunay arguments:
 *              mean (solar) elongation of the Moon, denoted as D
 *              mean anomaly of the Sun, denoted as l'
 *              mean anomaly of the Moon, denoted as l
 *              mean argument of latitude of the Moon, denoted as F
 *
 *      c) Planetary arguments, i.e. mean longitudes of the planets, at a given date for all eight planets coming from
 *              semi-analytical planetary theory VSOP82 developed by P. Bretagnon.
 *
 * Each of the above mentioned arguments is given as a polynomial function of t
 *
 *                                  λ = λ₀ + λ₁t + λ₂t² + λ₃t³ + λ₄t⁴
 * 
 * where t is time measured in Julian centuries since the beginning of the epoch J2000 till a date on which the
 * arguments are to be computed.
 *
 * Three functions are given to compute above mentioned arguments. ELP 2000 and Delaunay arguments may be computed
 * with polynomials of up to forth power of t. However, linear polynomials are also used during computations of lunar
 * positions. To specify which power of polynomial to be taken, use provided definitions FULL_SERIES_TOTAL_TERMS and
 * LINEAR_SERIES_TOTAL_TERMS with corresponding functions. Planetary arguments are always computed with linear
 * polynomials.
 *
 * Output of all functions is measured in arcseconds.
 */

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#define TOTAL_ELP2000_ARGUMENTS 5       // total amount of ELP arguments: W₁, W₂, W₃, T and ϖ'
#define TOTAL_DELAUNAY_ARGUMENTS 4      // total amount of Delaunay arguments: D, l', l and F
#define TOTAL_PLANETARY_ARGUMENTS 8     // total amount of planetary arguments for each planet in the Solar system

#define FULL_SERIES_TOTAL_TERMS 5
#define LINEAR_SERIES_TOTAL_TERMS 2

/*
 * An enumeration indexing ELP 2000 arguments.
 */
enum ELP_arguments {
    W1 = 0,             // mean mean longitude of the Moon (W₁)
    W2 = 1,             // mean longitude of the lunar perigee (W₂)
    W3,                 // mean longitude of the lunar ascending node (W₃)
    T,                  // mean heliocentric mean longitude of the Earth-Moon barycenter (T)
    OBP = 4,            // mean longitude of the perhelion of the Earth-Moon barycenter (ϖ')
};

/*
 * An enumeration indexing Delaunay arguments.
 */
enum Delaunay_arguments {
    D = 0,              // Moon's mean (solar) elongation (D)
    LP = 1,             // Sun's mean anomaly (l')
    L,                  // Moon's mean anomaly (l)
    F = 3               // Moon's mean argument of latitude (F)
};

/*
 * Computes precession argument (ζ) used in calculating Earth figure perturbations.
 * Argument is computed using linear series (i.e. up to linear power of t).
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 7
 */
double compute_precession_argument(double t);

/*
 * Computes ELP 2000 arguments (W₁, W₂, W₃, T and ϖ') given time instant (t) measured in Julian centuries since the
 * beginning of the epoch J2000 and the size of the polynomial used during computations. Use provided definitions for
 * convinience.
 * Output is written into given array and is measured in arcseconds.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 5
 */
void compute_elp2000_arguments(double t, int n, double arguments[]);

/*
 * Computes Delaunay arguments (D, l', l, F) given time instant (t) measured in Julian centuries since the beginning of
 * the epoch J2000 and the size of the polynomial used during computations. Use provided definitions for convinience.
 * Output is written into given array and is measured in arcseconds.
 *
 * Source:Lunar Solution ELP 2000-82B. Explanatory note, p. 5
 */void compute_delaunay_arguments(double t, int n, double arguments[]);

/*
 * Computes mean longitudes of the major planets of the Solar System (planetary arguments) given time instant (t)
 * measured in Julian centuries since the beginning of the epoch J2000.
 * Output is written into given array and is measured in arcseconds.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 8
 */
void compute_planetary_arguments(double t, double arguments[]);

#endif // ARGUMENTS_H