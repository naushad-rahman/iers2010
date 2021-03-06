#include "iers2010.hpp"

/**
 * @details  This function computes the global total FCULb mapping function 
 *           (Mendes et al. 2002). There is no dependence on meteorological
 *           data for this function.
 *           This function is a translation/wrapper for the fortran FCUL_B
 *           subroutine, found here : 
 *           http://maia.usno.navy.mil/conv2010/software.html
 * 
 * @param[in]  dlat  Latitude given in degrees (North Latitude)
 * @param[in]  dhgt  Height given in meters (mean sea level)
 * @param[in]  doy   Day of the year
 * @param[in]  elev  Elevation angle in degrees
 * @param[out] fcul  Mapping function to scale total delay (Note 1)
 * @return           An integer, always zero
 * 
 * @note
 *    -# These coefficients are based on a LS adjustment of 87766 (cleaned)
 *    set of traces, based on Ciddor routines to compute refractivity,
 *    according to IUGG recommendations (1999).
 *    -# Status: Class 1 model
 *
 * @verbatim
 *    given input: LATITUDE = 30.67166667D0 degrees (McDonald Observatory)
 *                  HEIGHT_M = 2075D0 meters (mean sea level)
 *                  DOY      = 224D0 (August 12, 2009)
 *                  ELEV_DEG = 15D0 degrees (See Mendes et al.)
 *     expected output: FCUL_B = 3.800758725284345996D0
 * @endverbatim
 * 
 * @version 2009 August 14
 *
 * @cite iers2010
 * Mendes, V.B., G. Prates, E.C. Pavlis, D.E. Pavlis, 
 * and R.B. Langley (2002). "Improved mapping functions for
 * atmospheric refraction correction in SLR", Geophysical 
 * Res. Lett., 29(10), 1414, doi:10.1029/2001GL014394, 2002
 * 
 */
int iers2010::fcul_b (const double& dlat,const double& dhgt,const double& doy,
    const double& elev,double& fcul)
{
    #ifdef USE_EXTERNAL_CONSTS
        constexpr double PI   (DPI);
    #else
        constexpr double PI   (3.14159265358979323846e0);
    #endif
    
    // Convert elevation angle to radians
    double epsilon  ( elev * (PI/180e0) );
    double sine     ( sin (epsilon) );
    // Add 182.5 to day of year to account for southern hemisphere
    double doy_c (doy);
    if (dlat<.0e0)
        doy_c += (365.25e0/2.0e0);
    double cosdoy ( cos ((doy_c - 28.0e0) * 2.0e0 * PI / 365.25e0) );
    double cosphi ( cos (dlat*(PI/180.0e0)) );


    // Define coefficients used in the model
    double a10 (  0.116131e-02 );
    double a11 ( -0.9338e-5    );
    double a12 ( -0.5958e-8    );
    double a13 ( -0.24627e-07  );
    double a14 (  0.12864e-03  );

    double a20 (  0.298151e-02 );
    double a21 ( -0.569e-05    );
    double a22 ( -0.1655e-07   );
    double a23 ( -0.2725e-07   );
    double a24 (  0.3020e-04   );

    double a30 (  0.681839e-01 );
    double a31 (  0.935e-04    );
    double a32 ( -0.2394e-06   );
    double a33 (  0.304e-07    );
    double a34 ( -0.2308e-02   );

    // a, b, and c in Marini continued fraction (Eq. 5)
    double dlat2 ( dlat * dlat );
    double a1 ( a10 + a11*cosdoy + a12*dlat2*cosdoy
       + a13 * dhgt + a14*cosphi );
    double a2 ( a20 + a21*cosdoy + a22*dlat2*cosdoy
       + a23 * dhgt + a24*cosphi );
    double a3 ( a30 + a31*cosdoy + a32*dlat2*cosdoy
       + a33 * dhgt + a34*cosphi );

    // numerator in continued fraction
    double map_zen ( (1.0e0 + a1/(1.0e0 + a2/(1.0e0+a3))) );

    // result
    fcul = map_zen/(sine+a1/(sine+a2/(sine+a3)));

    // return
    return 0;
}
