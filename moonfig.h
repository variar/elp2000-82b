/*
 * This file holds data to compute Poisson series of the Moon figure perturbations of ELP theory for three spherical
 * variables: longitude, latitude and distance.
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
 *      ELP28 - Moon figure perturbations, longitude
 *      ELP29 - Moon figure perturbations, latitude
 *      ELP30 - Moon figure perturbations, distance
 */

#ifndef MOONFIG_H
#define MOONFIG_H

#define TOTAL_MOON_FIGURE_LONGITUDE_TERMS 20
#define TOTAL_MOON_FIGURE_LATITUDE_TERMS 12
#define TOTAL_MOON_FIGURE_DISTANCE_TERMS 14

int moon_figure_longitude_multipliers[TOTAL_MOON_FIGURE_LONGITUDE_TERMS * 5] = {
    0, 0, 0, 0, 1,
    0, 0, 0, 1, -1,
    0, 0, 0, 2, -2,
    0, 0, 0, 3, -2,
    0, 0, 1, -1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 1, 0,
    0, 1, 0, -1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, -1, 0,
    0, 2, -1, -1, 0,
    0, 2, -1, 0, 0,
    0, 2, 0, -3, 0,
    0, 2, 0, -2, 0,
    0, 2, 0, -1, 0,
    0, 2, 0, 0, -2,
    0, 2, 0, 0, 0,
    0, 2, 1, -2, 0,
    0, 2, 1, -1, 0,
    0, 2, 1, 0, 0
};
int moon_figure_latitude_multipliers[TOTAL_MOON_FIGURE_LATITUDE_TERMS * 5] = {
    0, 0, 0, 1, -1,
    0, 0, 0, 1, 0,
    0, 0, 0, 1, 1,
    0, 0, 0, 2, -3,
    0, 0, 0, 2, -1,
    0, 0, 1, -1, -1,
    0, 0, 1, 0, -1,
    0, 0, 1, 0, 1,
    0, 0, 1, 1, 1,
    0, 2, 0, -2, -1,
    0, 2, 0, -2, 1,
    0, 2, 0, 0, -1
};
int moon_figure_distance_multipliers[TOTAL_MOON_FIGURE_DISTANCE_TERMS * 5] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 1,
    0, 0, 0, 0, 2,
    0, 0, 0, 1, 0,
    0, 0, 0, 3, -2,
    0, 0, 1, -1, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 1, 0,
    0, 2, -1, -1, 0,
    0, 2, -1, 0, 0,
    0, 2, 0, -2, 0,
    0, 2, 0, -1, 0,
    0, 2, 1, -1, 0,
    0, 2, 1, 0, 0
};

double moon_figure_longitude_coefficients[TOTAL_MOON_FIGURE_LONGITUDE_TERMS * 3] = {
    303.96185, 0.00004, 0.075,
    259.88393, 0.00016, 5.997,
    0.43020, 0.00040, 2.998,
    0.43379, 0.00002, 0.077,
    359.99858, 0.00014, 0.082,
    359.99982, 0.00223, 1.000,
    359.99961, 0.00014, 0.070,
    359.99331, 0.00009, 1.127,
    359.99537, 0.00001, 0.081,
    0.06418, 0.00003, 8.850,
    180.00095, 0.00004, 0.095,
    180.00014, 0.00003, 0.042,
    179.98126, 0.00001, 0.067,
    179.98366, 0.00025, 0.564,
    179.99638, 0.00014, 0.087,
    179.95864, 0.00003, 0.474,
    179.99904, 0.00002, 0.040,
    179.99184, 0.00002, 1.292,
    0.00313, 0.00002, 0.080,
    359.99965, 0.00002, 0.039
};
double moon_figure_latitude_coefficients[TOTAL_MOON_FIGURE_LATITUDE_TERMS * 3] = {
    0.02199, 0.00003, 5.997,
    245.99067, 0.00001, 0.075,
    0.00530, 0.00001, 0.037,
    0.42283, 0.00002, 0.073,
    0.74505, 0.00001, 0.076,
    359.99982, 0.00001, 0.039,
    359.99982, 0.00010, 0.081,
    359.99982, 0.00010, 0.069,
    359.99982, 0.00001, 0.036,
    179.98356, 0.00001, 0.066,
    179.98353, 0.00001, 0.086,
    179.99478, 0.00005, 0.088
};
double moon_figure_distance_coefficients[TOTAL_MOON_FIGURE_DISTANCE_TERMS * 3] = {
    90.00000, 0.00130, 99999.999,
    213.95720, 0.00003, 0.075,
    270.03745, 0.00002, 0.037,
    90.07597, 0.00004, 0.075,
    270.43429, 0.00002, 0.077,
    89.99919, 0.00013, 0.082,
    270.00007, 0.00022, 1.000,
    269.99903, 0.00011, 0.070,
    89.99815, 0.00002, 0.095,
    90.00052, 0.00003, 0.042,
    269.98585, 0.00005, 0.564,
    89.99863, 0.00013, 0.087,
    269.99982, 0.00002, 0.080,
    269.99982, 0.00003, 0.039
};

#endif // MOONFIG_H