ELP2000-82B
===========

<img border="15" align="right" src=https://dl.dropbox.com/u/4936034/Referred/ELP2000-82B.png>

Given library provides functionality to compute lunar positions and thus allowing contruction of lunar ephemerides.

It is based on semi-analytical **theory ELP version ELP 2000-82B** developed by **M. Chapront-Touzé** and **J. Chapront**
at Bureau des Longitude, Paris, France.

To find information on the theory itself, refer to the following original papers:

1. M. Chapront-Touzé and J. Chapront. The lunar ephemeris ELP 2000. Astronomy and Astrophysics, vol. 124, 1983,
   pp. 50-62.
2. M. Chapront-Touzé and J. Chapront. ELP 2000-85: a semi-analytical lunar ephemeris adequate for historical times.
   Astronomy and Astrophysics, vol. 190, 1988, pp. 342-352.
3. Lunar Solution ELP 2000-82B. Explanatory note.
4. J. Chapront and G. Francou. The lunar theory ELP revisited. Introduction of new planetary perturbations.
   Astronomy and Astrophysics, vol. 404, 2003, pp. 735-742.
   
As well as data files found through [Vizier Catalon FTP service](http://vizier.cfa.harvard.edu/viz-bin/ftp-index?VI/79).

This library is implemented in C and needs be linked only against math library.

Provided files contain the following functionality

* **elp2000-82b** is the main file of interest. It contains routines that compute lunar positions depending on desired
  output coordinates and reference frame. Refer to the header comments for more information.
* **arguments** contains routines that compute arguments of the ELP theory. Among such, this file contains a routine
  to compute mean lunar arguments (Delaunay arguments), that may come in need while performing various lunar
  computations.
* **series** contains auxiliary routines that compute Fourier and Poisson series of the ELP theory.
* All other header files define arrays of coefficients of ELP theory and are of no practical use outside given library.

If you find any errors or inconsistencies with this software, you are very welcome to contact me at
[sertsy@gmail.com](mailto:sertsy@gmail.com).

Serhii Tsyba
17.08.2010
Helsinki, Finland