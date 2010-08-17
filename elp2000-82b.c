/*
 * elp2000.c
 * Created by Serhii Tsyba (sertsy@gmail.com) on 21.04.10.
 */

#include "mainprob.h"
#include "earthfig.h"
#include "planetary1.h"
#include "planetary2.h"
#include "tidal.h"
#include "moonfig.h"
#include "relativistic.h"
#include "solarecc.h"

#include "elp2000-82b.h"
#include "series.h"
#include "arguments.h"

#include <math.h>

spherical_point geocentric_moon_position(double t)
{
    double delaunay_arguments[TOTAL_DELAUNAY_ARGUMENTS];        // Delaunay arguments
    double elp2000_arguments[TOTAL_ELP2000_ARGUMENTS];          // ELP2000 arguments
    double planetary_arguments[TOTAL_PLANETARY_ARGUMENTS];      // planetary arguments
    double zeta;                                                // argument of the precession precession (ζ)
    spherical_point sp;                                         // result position of the Moon

    // each coordinate (longitude, latitude and radial distance) is computed by adding together results of each serie:
    // Main Porblem and all perturbations; then, Moon's mean mean longitude (W₁) must be added to the value of the
    // longitude to find the actual position
    
    // computing Delaunay arguments (non reduced)
    compute_delaunay_arguments(t, FULL_SERIES_TOTAL_TERMS, delaunay_arguments);
    
    // computing Main Problem
    sp.longitude = compute_serie_a_sin(delaunay_arguments, main_problem_longitude_multipliers,
                                       main_problem_longitude_coefficients, TOTAL_MAIN_PROBLEM_LONGITUDE_TERMS);
    sp.latitude = compute_serie_a_sin(delaunay_arguments, main_problem_latitude_multipliers,
                                      main_problem_latitude_coefficients, TOTAL_MAIN_PROBLEM_LATITUDE_TERMS);
    sp.distance = compute_serie_a_cos(delaunay_arguments, main_problem_distance_multipliers,
                                      main_problem_distance_coefficients, TOTAL_MAIN_PROBLEM_DISTANCE_TERMS);

    // recomputing reduced Delaunay arguments
    compute_delaunay_arguments(t, LINEAR_SERIES_TOTAL_TERMS, delaunay_arguments);
    // computing ELP2000 arguments
    compute_elp2000_arguments(t, LINEAR_SERIES_TOTAL_TERMS, elp2000_arguments);
    // computing precession argument
    zeta = compute_precession_argument(t);

    // computing Earth figure perturbations (constant)
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, earth_figure_longitude_0_multipliers,
                                    earth_figure_longitude_0_coefficients, TOTAL_EARTH_FIGURE_LONGITUDE_0_TERMS);
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, earth_figure_latitude_0_multipliers,
                                   earth_figure_latitude_0_coefficients, TOTAL_EARTH_FIGURE_LATITUDE_0_TERMS);
    sp.distance += compute_serie_b(zeta, delaunay_arguments, earth_figure_distance_0_multipliers,
                                   earth_figure_distance_0_coefficients, TOTAL_EARTH_FIGURE_DISTANCE_0_TERMS);

    // computing Earth figure perturbations (linear)
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, earth_figure_longitude_0_multipliers,
                                    earth_figure_longitude_0_coefficients, TOTAL_EARTH_FIGURE_LONGITUDE_0_TERMS) * t;
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, earth_figure_latitude_0_multipliers,
                                   earth_figure_latitude_0_coefficients, TOTAL_EARTH_FIGURE_LATITUDE_0_TERMS) * t;
    sp.distance += compute_serie_b(zeta, delaunay_arguments, earth_figure_distance_0_multipliers,
                                   earth_figure_distance_0_coefficients,TOTAL_EARTH_FIGURE_DISTANCE_0_TERMS) * t;

    // computing planetary arguments
    compute_planetary_arguments(t, planetary_arguments);

    // computing planetary 1 perturbations (constant)
    sp.longitude += compute_serie_c(planetary_arguments, delaunay_arguments, planetary1_longitude_0_multipliers,
                                    planetary1_longitude_0_coefficients, TOTAL_PLANETARY1_LONGITUDE_0_TERMS);
    sp.latitude += compute_serie_c(planetary_arguments, delaunay_arguments, planetary1_latitude_0_multipliers,
                                   planetary1_latitude_0_coefficients, TOTAL_PLANETARY1_LATITUDE_0_TERMS);
    sp.distance += compute_serie_c(planetary_arguments, delaunay_arguments, planetary1_distance_0_multipliers,
                                   planetary1_distance_0_coefficients, TOTAL_PLANETARY1_DISTANCE_0_TERMS);

    // computing planetary 1 perturbations (linear)
    sp.longitude += compute_serie_c(planetary_arguments, delaunay_arguments, planetary1_longitude_1_multipliers,
                                    planetary1_longitude_1_coefficients, TOTAL_PLANETARY1_LONGITUDE_1_TERMS) * t;
    sp.latitude += compute_serie_c(planetary_arguments, delaunay_arguments, planetary1_latitude_1_multipliers,
                                   planetary1_latitude_1_coefficients, TOTAL_PLANETARY1_LATITUDE_1_TERMS) * t;
    sp.distance += compute_serie_c(planetary_arguments, delaunay_arguments, planetary1_distance_1_multipliers,
                                   planetary1_distance_1_coefficients, TOTAL_PLANETARY1_DISTANCE_1_TERMS) * t;

    // computing planetary 2 perturbations (constant)
    sp.longitude += compute_serie_d(planetary_arguments, delaunay_arguments, planetary2_longitude_0_multipliers,
                                    planetary2_longitude_0_coefficients, TOTAL_PLANETARY2_LONGITUDE_0_TERMS);
    sp.latitude += compute_serie_d(planetary_arguments, delaunay_arguments, planetary2_latitude_0_multipliers,
                                   planetary2_latitude_0_coefficients, TOTAL_PLANETARY2_LATITUDE_0_TERMS);
    sp.distance += compute_serie_d(planetary_arguments, delaunay_arguments, planetary2_distance_0_multipliers,
                                   planetary2_distance_0_coefficients, TOTAL_PLANETARY2_DISTANCE_0_TERMS);

    // computing planetary 2 perturbations (linear)
    sp.longitude += compute_serie_d(planetary_arguments, delaunay_arguments, planetary2_longitude_1_multipliers,
                           planetary2_longitude_1_coefficients, TOTAL_PLANETARY2_LONGITUDE_1_TERMS) * t;
    sp.latitude += compute_serie_d(planetary_arguments, delaunay_arguments, planetary2_latitude_1_multipliers,
                           planetary2_latitude_1_coefficients, TOTAL_PLANETARY2_LATITUDE_1_TERMS) * t;
    sp.distance += compute_serie_d(planetary_arguments, delaunay_arguments, planetary2_distance_1_multipliers,
                           planetary2_distance_1_coefficients, TOTAL_PLANETARY2_DISTANCE_1_TERMS) * t;

    // computing tidal effects (constant)
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, tidal_longitude_0_multipliers,
                           tidal_longitude_0_coefficients, TOTAL_TIDAL_LONGITUDE_0_TERMS);
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, tidal_latitude_0_multipliers,
                           tidal_latitude_0_coefficients, TOTAL_TIDAL_LATITUDE_0_TERMS);
    sp.distance += compute_serie_b(zeta, delaunay_arguments, tidal_distance_0_multipliers,
                           tidal_distance_0_coefficients, TOTAL_TIDAL_DISTANCE_0_TERMS);

    // computing tidal effects (linear)
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, tidal_longitude_1_multipliers,
                           tidal_longitude_1_coefficients, TOTAL_TIDAL_LONGITUDE_1_TERMS) * t;
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, tidal_latitude_1_multipliers,
                           tidal_latitude_1_coefficients, TOTAL_TIDAL_LATITUDE_1_TERMS) * t;
    sp.distance += compute_serie_b(zeta, delaunay_arguments, tidal_distance_1_multipliers,
                           tidal_distance_1_coefficients, TOTAL_TIDAL_DISTANCE_1_TERMS) * t;

    // computing Moon figure perturbations
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, moon_figure_longitude_multipliers,
                           moon_figure_longitude_coefficients, TOTAL_MOON_FIGURE_LONGITUDE_TERMS);
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, moon_figure_latitude_multipliers,
                           moon_figure_latitude_coefficients, TOTAL_MOON_FIGURE_LATITUDE_TERMS);
    sp.distance += compute_serie_b(zeta, delaunay_arguments, moon_figure_distance_multipliers,
                           moon_figure_distance_coefficients, TOTAL_MOON_FIGURE_DISTANCE_TERMS);

    // computing relativistic perturbations
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, relativistic_longitude_multipliers,
                           relativistic_longitude_coefficients, TOTAL_RELATIVISTIC_LONGITUDE_TERMS);
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, relativistic_latitude_multipliers,
                           relativistic_latitude_coefficients, TOTAL_RELATIVISTIC_LATITUDE_TERMS);
    sp.distance += compute_serie_b(zeta, delaunay_arguments, relativistic_distance_multipliers,
                           relativistic_distance_coefficients, TOTAL_RELATIVISTIC_DISTANCE_TERMS);

    // computing planetary perturbations (solar eccentricity) (quadratic)
    sp.longitude += compute_serie_b(zeta, delaunay_arguments, planetary_longitude_2_multipliers,
                           planetary_longitude_2_coefficients, TOTAL_PLANETARY_LONGITUDE_2_TERMS) * t * t;
    sp.latitude += compute_serie_b(zeta, delaunay_arguments, planetary_latitude_2_multipliers,
                           planetary_latitude_2_coefficients, TOTAL_PLANETARY_LATITUDE_2_TERMS) * t * t;
    sp.distance += compute_serie_b(zeta, delaunay_arguments, planetary_distance_2_multipliers,
                           planetary_distance_2_coefficients, TOTAL_PLANETARY_DISTANCE_2_TERMS) * t * t;

    // recomputing full ELP2000 arguments
    compute_elp2000_arguments(t, FULL_SERIES_TOTAL_TERMS, elp2000_arguments);
    
    // adding mean mean longitude of the Moon (W₁)
    sp.longitude += elp2000_arguments[W1];

    return sp;
}

spherical_point geocentric_moon_position_of_date(double t)
{
    spherical_point sp;         // geocentric Moon position referred to ELP reference frame
    double p;                   // accumulated precession between J2000 and a given date
    
    // calculating Moon's position referred to ELP reference frame
    sp = geocentric_moon_position(t);
    
    // computing accumulated precession between J2000 and a given date
    p = 5029.0966 * t + 1.1120 * t * t + 0.000077 * t * t * t - 0.00002353 * t * t * t * t;
    
    // adding accumulated precession to the longitude of Moon's position
    sp.longitude += p;
    
    return sp;
}

cartesian_3d_point geocentric_moon_position_cartesian(double t)
{
    spherical_point sp;         // a value in spherical coordinates
    cartesian_3d_point rp;      // resulting value in rectangular coordiantes (reference frame of ELP2000)

    // computing Moon's position in spherical coordinates
    sp = geocentric_moon_position(t);
    
    // converting longitude and latitude from arcseconds to radians (π = 368000")
    sp.longitude *= M_PI / 648000.0;
    sp.latitude *= M_PI / 648000.0;
    
    // converting to rectangular coordinates
    rp.x = sp.distance * cos(sp.longitude) * cos(sp.latitude);
    rp.y = sp.distance * sin(sp.longitude) * cos(sp.latitude);
    rp.z = sp.distance * sin(sp.latitude);
    
    return rp;
}

cartesian_3d_point geocentric_moon_position_cartesian_of_J2000(double t)
{
    cartesian_3d_point rp;      // position of the Moon in rectangular coordinates referred to the ELP2000 reference frame
    cartesian_3d_point re2000p; // position of the Moon in rectangular coordinates referred to the internal mean ecliptic
                                // and equinox of J2000
    double p, q;                // intermediate auxiliary convertion variables from Laskar's series
    
    // computing Moon's position in rectangular coordinates referred to the ELP2000 reference frame
    rp = geocentric_moon_position_cartesian(t);
    
    // computing p and q
    p = 0.10180391e-4 * t + 0.47020439e-6 * t * t - 0.5417367e-9 * t * t * t -
    0.2507948e-11 * t * t * t * t + 0.463486e-14 * t * t * t * t * t;
    q = -0.113469002e-3 * t + 0.12372674e-6 * t * t + 0.12654170e-8 * t * t * t -
    0.1371808e-11 * t * t * t * t - 0.320334e-14 * t * t * t * t * t;
    
    // performing rotation of ELP2000 reference frame into mean dynamical ecliptic and equinox of J2000
    re2000p.x = (1 - 2 * p * p) * rp.x + 2 * p * q * rp.y + 2 * p * sqrt(1 - p * p - q * q) * rp.z;
    re2000p.y = 2 * p * q * rp.x + (1 - 2 * q * q) * rp.y -  2 * q * sqrt(1 - p * p - q * q) * rp.z;
    re2000p.z = -2 * p * sqrt(1 - p * p - q * q) * rp.x + 2 * q * sqrt(1 - p * p - q * q)  * rp.y + (1 - 2 * p * p - 2 * q * q) * rp.z;
    
    return re2000p;
}

cartesian_3d_point geocentric_moon_position_cartesian_of_FK5(double t)
{
    cartesian_3d_point re2000p;     // position of the Moon in rectangular coordianted referred to the internal mean
                                    // ecliptic and equinox of J2000
    cartesian_3d_point rfk5p;       // position of the Moon in rectangular coordinates referred to the FK5 equator ♈FK5
                                    // (mean equator and rotational mean equinox of J2000)
    
    // computing Moon's position in rectangular coordinates referred to the internal mean ecliptic and equinox of J2000
    re2000p = geocentric_moon_position_cartesian_of_J2000(t);
    
    // performing transformation to rectangular coordinates referred to the FK5 equator
    rfk5p.x =  1.000000000000 * re2000p.x + 0.000000437913 * re2000p.y - 0.000000189859 * re2000p.z;
    rfk5p.y = -0.000000477299 * re2000p.x + 0.917482137607 * re2000p.y - 0.397776981791 * re2000p.z;
    rfk5p.z =  0.000000000000 * re2000p.x + 0.397776981701 * re2000p.y + 0.917482137607 * re2000p.z;
    
    return rfk5p;
}