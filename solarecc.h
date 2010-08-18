/*
 * This file holds data to compute Poisson series of the planetary perturbations (solar eccentricity) of second order
 * terms of ELP theory for three spherical variables: longitude, latitude and distance.
 *
 * Given the series expression
 *
 *                                  Σ Asin(i₁ζ + i₂D + i₃l' + i₄l + i₅F + φ)
 *
 * Each array of multipliers viariables holds five values consequently
 *
 *                                              i₁ i₂ i₃ i₄ i₅
 *
 * The value of i₁ (multiplier for precession argument ζ) is always 0.
 *
 * Each array of coefficients holds three values consequently
 *
 *                                                  φ A P
 *
 * Each of the size definitions specifies the size of each record. Approximate period value P is not used during
 * computations of series but is kept for the sake of consistency of ELP data structures.
 *
 * This data was adapted from ELP data files at Centre de Donées astronomiques de Strasbourg public resource:
 * http://vizier.cfa.harvard.edu/viz-bin/ftp-index?VI/79
 *
 * Files
 *      ELP34 - Relativistic perturbations (solar eccentricity), longitude/t²
 *      ELP35 - Relativistic perturbations (solar eccentricity), latitude/t²
 *      ELP36 - Relativistic perturbations (solar eccentricity), distance/t²
 */

#ifndef SOLARECC_H
#define SOLARECC_H

#define TOTAL_PLANETARY_LONGITUDE_2_TERMS 28
#define TOTAL_PLANETARY_LATITUDE_2_TERMS 13
#define TOTAL_PLANETARY_DISTANCE_2_TERMS 19

int planetary_longitude_2_multipliers[TOTAL_PLANETARY_LONGITUDE_2_TERMS * 5] = {
    0, 0, 1, -2, 0,
    0, 0, 1, -1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 1, 0,
    0, 0, 1, 2, 0,
    0, 0, 2, -1, 0,
    0, 0, 2, 0, 0,
    0, 0, 2, 1, 0,
    0, 1, 1, 0, 0,
    0, 2, -2, -1, 0,
    0, 2, -2, 0, 0,
    0, 2, -2, 1, 0,
    0, 2, -1, -2, 0,
    0, 2, -1, -1, 0,
    0, 2, -1, 0, -2,
    0, 2, -1, 0, 0,
    0, 2, -1, 1, 0,
    0, 2, 0, -1, 0,
    0, 2, 0, 0, 0,
    0, 2, 1, -2, 0,
    0, 2, 1, -1, 0,
    0, 2, 1, 0, -2,
    0, 2, 1, 0, 0,
    0, 2, 1, 1, 0,
    0, 2, 2, -1, 0,
    0, 4, -1, -2, 0,
    0, 4, -1, -1, 0,
    0, 4, -1, 0, 0
};
int planetary_latitude_2_multipliers[TOTAL_PLANETARY_LATITUDE_2_TERMS * 5] = {
    0, 0, 1, -1, -1,
    0, 0, 1, -1, 1,
    0, 0, 1, 0, -1,
    0, 0, 1, 0, 1,
    0, 0, 1, 1, -1,
    0, 0, 1, 1, 1,
    0, 2, -2, 0, -1,
    0, 2, -1, -1, -1,
    0, 2, -1, -1, 1,
    0, 2, -1, 0, -1,
    0, 2, -1, 0, 1,
    0, 2, -1, 1, -1,
    0, 2, 1, 0, -1
};
int planetary_distance_2_multipliers[TOTAL_PLANETARY_DISTANCE_2_TERMS * 5] = {
    0, 0, 1, -2, 0,
    0, 0, 1, -1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 1, 0,
    0, 0, 1, 2, 0,
    0, 0, 2, -1, 0,
    0, 1, 1, 0, 0,
    0, 2, -2, -1, 0,
    0, 2, -2, 0, 0,
    0, 2, -1, -2, 0,
    0, 2, -1, -1, 0,
    0, 2, -1, 0, 0,
    0, 2, -1, 1, 0,
    0, 2, 0, 0, 0,
    0, 2, 1, -1, 0,
    0, 2, 1, 0, 0,
    0, 2, 1, 1, 0,
    0, 2, 2, -1, 0,
    0, 4, -1, -1, 0
};

double planetary_longitude_2_coefficients[TOTAL_PLANETARY_LONGITUDE_2_TERMS * 3] = {
    0.00000, 0.00007, 0.039,
    0.00000, 0.00108, 0.082,
    0.00000, 0.00487, 1.000,
    0.00000, 0.00080, 0.070,
    0.00000, 0.00006, 0.036,
    0.00000, 0.00004, 0.089,
    0.00000, 0.00011, 0.500,
    0.00000, 0.00002, 0.066,
    180.00000, 0.00013, 0.075,
    180.00000, 0.00011, 0.105,
    180.00000, 0.00012, 0.044,
    180.00000, 0.00001, 0.028,
    180.00000, 0.00006, 0.360,
    180.00000, 0.00150, 0.095,
    180.00000, 0.00002, 0.322,
    180.00000, 0.00120, 0.042,
    180.00000, 0.00011, 0.027,
    0.00000, 0.00002, 0.087,
    0.00000, 0.00003, 0.040,
    180.00000, 0.00002, 1.292,
    0.00000, 0.00021, 0.080,
    0.00000, 0.00001, 0.903,
    0.00000, 0.00018, 0.039,
    0.00000, 0.00002, 0.026,
    0.00000, 0.00004, 0.074,
    180.00000, 0.00002, 0.046,
    180.00000, 0.00003, 0.028,
    180.00000, 0.00001, 0.021
};
double planetary_latitude_2_coefficients[TOTAL_PLANETARY_LATITUDE_2_TERMS * 3] = {
    0.00000, 0.00005, 0.039,
    0.00000, 0.00004, 0.857,
    0.00000, 0.00004, 0.081,
    0.00000, 0.00005, 0.069,
    0.00000, 0.00004, 1.200,
    0.00000, 0.00004, 0.036,
    180.00000, 0.00002, 0.107,
    180.00000, 0.00005, 0.340,
    180.00000, 0.00006, 0.042,
    180.00000, 0.00022, 0.097,
    180.00000, 0.00006, 0.027,
    180.00000, 0.00001, 0.042,
    0.00000, 0.00009, 0.081
};
double planetary_distance_2_coefficients[TOTAL_PLANETARY_DISTANCE_2_TERMS * 3] = {
    90.00000, 0.00005, 0.039,
    90.00000, 0.00095, 0.082,
    270.00000, 0.00036, 1.000,
    270.00000, 0.00077, 0.070,
    270.00000, 0.00004, 0.036,
    90.00000, 0.00003, 0.089,
    90.00000, 0.00012, 0.075,
    90.00000, 0.00007, 0.105,
    90.00000, 0.00014, 0.044,
    270.00000, 0.00007, 0.360,
    90.00000, 0.00111, 0.095,
    90.00000, 0.00149, 0.042,
    90.00000, 0.00009, 0.027,
    270.00000, 0.00004, 0.040,
    270.00000, 0.00018, 0.080,
    270.00000, 0.00023, 0.039,
    270.00000, 0.00002, 0.026,
    270.00000, 0.00003, 0.074,
    90.00000, 0.00003, 0.028
};

#endif // SOLARECC_H