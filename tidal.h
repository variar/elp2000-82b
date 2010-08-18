/*
 * This file holds data to compute Poisson series of the tidal effects of ELP theory for three spherical variables:
 * longitude, latitude and distance.
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
 *      ELP22 - Moon figure perturbations, longitude
 *      ELP23 - Moon figure perturbations, latitude
 *      ELP24 - Moon figure perturbations, distance
 *      ELP25 - Moon figure perturbations, longitude/t
 *      ELP26 - Moon figure perturbations, latitude/t
 *      ELP27 - Moon figure perturbations, distance/t
 */

#ifndef TIDAL_H
#define TIDAL_H

#define TOTAL_TIDAL_LONGITUDE_0_TERMS 3
#define TOTAL_TIDAL_LATITUDE_0_TERMS 2
#define TOTAL_TIDAL_DISTANCE_0_TERMS 2

#define TOTAL_TIDAL_LONGITUDE_1_TERMS 6
#define TOTAL_TIDAL_LATITUDE_1_TERMS 4
#define TOTAL_TIDAL_DISTANCE_1_TERMS 5

int tidal_longitude_0_multipliers[TOTAL_TIDAL_LONGITUDE_0_TERMS * 5] = {
    0, 1, 1, -1, -1,
    0, 1, 1, 0, -1,
    0, 1, 1, 1, -1
};
int tidal_latitude_0_multipliers[TOTAL_TIDAL_LATITUDE_0_TERMS * 5] = {
    0, 1, 1, 0, -2,
    0, 1, 1, 0, 0
};
int tidal_distance_0_multipliers[TOTAL_TIDAL_DISTANCE_0_TERMS * 5] = {
    0, 1, 1, -1, -1,
    0, 1, 1, 1, -1
};

double tidal_longitude_0_coefficients[TOTAL_TIDAL_LONGITUDE_0_TERMS * 3] = {
    192.93665, 0.00004, 0.075,
    192.93665, 0.00082, 18.600,
    192.93665, 0.00004, 0.076
};
double tidal_latitude_0_coefficients[TOTAL_TIDAL_LATITUDE_0_TERMS * 3] = {
    192.93663, 0.00004, 0.074,
    192.93664, 0.00004, 0.075
};
double tidal_distance_0_coefficients[TOTAL_TIDAL_DISTANCE_0_TERMS * 3] = {
    282.93665, 0.00004, 0.075,
    102.93665, 0.00004, 0.076
};

int tidal_longitude_1_multipliers[TOTAL_TIDAL_LONGITUDE_1_TERMS * 5] = {
    0, 0, 0, 1, 0,
    0, 0, 0, 2, 0,
    0, 2, 0, -2, 0,
    0, 2, 0, -1, 0,
    0, 2, 0, 0, 0,
    0, 2, 0, 1, 0
};
int tidal_latitude_1_multipliers[TOTAL_TIDAL_LATITUDE_1_TERMS * 5] = {
    0, 0, 0, 0, 1,
    0, 0, 0, 1, -1,
    0, 0, 0, 1, 1,
    0, 2, 0, 0, -1
};
int tidal_distance_1_multipliers[TOTAL_TIDAL_DISTANCE_1_TERMS * 5] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 1, 0,
    0, 0, 0, 2, 0,
    0, 2, 0, -1, 0,
    0, 2, 0, 0, 0
};

double tidal_longitude_1_coefficients[TOTAL_TIDAL_LONGITUDE_1_TERMS * 3] = {
    0.00000, 0.00058, 0.075,
    0.00000, 0.00004, 0.038,
    0.00000, 0.00002, 0.564,
    0.00000, 0.00021, 0.087,
    0.00000, 0.00009, 0.040,
    0.00000, 0.00001, 0.026
};
double tidal_latitude_1_coefficients[TOTAL_TIDAL_LATITUDE_1_TERMS * 3] = {
    180.00000, 0.00005, 0.075,
    0.00000, 0.00003, 5.997,
    0.00000, 0.00003, 0.037,
    0.00000, 0.00001, 0.088
};
double tidal_distance_1_coefficients[TOTAL_TIDAL_DISTANCE_1_TERMS * 3] = {
    90.00000, 0.00356, 99999.999,
    270.00000, 0.00072, 0.075,
    270.00000, 0.00003, 0.038,
    270.00000, 0.00019, 0.087,
    270.00000, 0.00013, 0.040
};

#endif // TIDAL_H