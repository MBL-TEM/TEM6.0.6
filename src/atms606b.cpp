/* **************************************************************
*****************************************************************
ATMS602.CPP - object describes physical characteristics of the
	       atmosphere

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>   

****************************************************************
************************************************************* */

#include<cmath>
  using std::exp;
  
#include "atms606b.h"

Atmosphere60::Atmosphere60()
{
  // Number of days per month
  
  ndays[0] = 31;
  ndays[1] = 28;
  ndays[2] = 31;
  ndays[3] = 30;
  ndays[4] = 31;
  ndays[5] = 30;
  ndays[6] = 31;
  ndays[7] = 31;
  ndays[8] = 30;
  ndays[9] = 31;
  ndays[10] = 30;
  ndays[11] = 31;
	
};

/* *************************************************************
************************************************************* */

/* *************************************************************
************************************************************* */

void Atmosphere60::petjh( const double& nirr, 
                          const double& tair,
                          const int& pdm )
{

  double f;
  double rt;

  f = ((9.0/5.0) * tair) + 32.0;
  rt = nirr * 0.016742;
  pet = ((0.014*f) - 0.37) * rt * ndays[pdm];

  if( pet <= ZERO ) { pet = 0.001; }

};

/* *************************************************************
************************************************************* */

/* *************************************************************
************************************************************* */

void Atmosphere60::precsplt( const double& prec, 
                             const double& tair,
                             double& rain, 
                             double& snowfall )
{


/* *************************************************************
	Willmott's assumptions on snow/rain split:
************************************************************** */

  if( tair >= -1.0 )
  {
    rain = prec;
    snowfall = ZERO;
  }
  else
  {
    rain = ZERO;
    snowfall = prec;
  }

};

/* *************************************************************
************************************************************* */

/* *************************************************************
************************************************************* */

void Atmosphere60::resetMonthlyFluxes( void )
{
  // Reset monthly fluxes to zero

  pet = ZERO;

};
/* *************************************************************
************************************************************* */

/* *************************************************************
************************************************************* */

void Atmosphere60::resetYrFluxes( void )
{
  // Reset annual fluxes and summary variables to zero	

  yrrain = ZERO;
  yrsnowfall = ZERO;
  yrpet = ZERO;

  yrndep.total = ZERO;
  yrndep.nh4 = ZERO;
  yrndep.no3 = ZERO;

};
                   

