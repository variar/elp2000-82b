/*
 * series.h
 * Created by Serhii Tsyba (sertsy@gmail.com) on 08.06.10.
 *
 * This file contains routines to compute series of the ELP theory. Expressions for the series are
 *
 *                                  A{sin|cos}(i₁D + i₂l' + i₃l + i₄F)
 *
 * for the Main Problem, where sine is used when computing longitual and latitudal variables and cosine when computing
 * radial distance. For the sake of simplicity two separate are given for both sine and cosine expressions.
 *      
 *                                Asin(i₁ζ + i₂D + i₃l' + i₄l + i₅F + φ)
 *
 * for Earth figure, Moon figure, relativistic perturbations, tidal effects and second order planetary perturbations.
 * For series other than of Earth figure perturbations multiplier i₁ is always zero.
 *
 *              Asin(i₁Me + i₂V + i₃T + i₄Ma + i₅J + i₆S + i₇U + i₈N + i₉D + i₁₀l + i₁₁F + φ)
 *
 * for the first type of planetary perturbations.
 *
 *              Asin(i₁Me + i₂V + i₃T + i₄Ma + i₅J + i₆S + i₇U + i₈D + i₉l + i₁₀l' + i₁₁F + φ)
 *
 * for the second type of planetary perturbations.
 *
 * For each of the above mentioned series a separate function is given. Each function deals with one dimensional
 * arrays for multipliers and coefficiens. Adopted indexing of the arguments may be seen from definitions of
 * corresponding arrays.
 *
 * The last argument of each function corresponds to the size of the serie. Note, that size of the serie does not
 * match with the length of the multipliers or coefficients arrays, which is rather a multiple of it, depending on the
 * amount of arguments in each of these arrays. Use provided size definitions for each of the arrays for convinience.
 */

#ifndef SERIES_H
#define SERIES_H

/*
 * Computes a sine Fourier serie for the Main Problem of the ELP theory given the Delaunay arguments, array of
 * mutipliers, array of coefficients and the size of the serie.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 2
 */
double compute_serie_a_sin(double delaunay_arguments[], int multipliers[], double coefficients[], int n);

/*
 * Computes a cosine Fourier serie for the Main Problem of the ELP theory given the Delaunay arguments, array of
 * mutipliers, array of coefficients and the size of the serie.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 2
 */
double compute_serie_a_cos(double delaunay_arguments[], int multipliers[], double coefficients[], int n);

/*
 * Computes a Poisson serie for either Earth figure perturbations, Moon figure perturbations, relativistic
 * perturbations, tidal effects or second order planetary perturbations of the ELP theory given planetary arguments,
 * delaunay arguments, array of mutipliers, array of coefficients and the size of the serie.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 2
 */
double compute_serie_b(double precession, double delaunay_arguments[], int multipliers[], double coefficients[], int n);

/*
 * Computes a Poisson serie for the first type of planetary perturbations of the ELP theory given planetary arguments,
 * delaunay arguments, array of mutipliers, array of coefficients and the size of the serie.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 3
 */
double compute_serie_c(double planetary_arguments[], double delaunay_arguments[], int multipliers[], double coefficients[], int n);

/*
 * Computes a Poisson serie for the second type of planetary perturbations of the ELP theory given planetary arguments,
 * delaunay arguments, array of mutipliers, array of coefficients and the size of the serie.
 *
 * Source: Lunar Solution ELP 2000-82B. Explanatory note, p. 3
 */
double compute_serie_d(double planetary_arguments[], double delaunay_arguments[], int multipliers[], double coefficients[], int n);

#endif // SERIES_H