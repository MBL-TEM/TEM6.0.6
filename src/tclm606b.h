/* *************************************************************
****************************************************************
TCLM606B.H - describes climate module used by TEM

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
                                         
****************************************************************
************************************************************* */

#ifndef TCLM606_H
#define TCLM606_H



// TEMclm uses the global constants CYCLE, MISSING, NUMATMS 
//   and NUMATMS
#include "temconsts606.hpp"

// TEMclm60 inherits class Atmosphere60
#include "atms606b.h"        


class TEMclm60 : public Atmosphere60
{

  public:

     TEMclm60();

     enum clmkey { I_GIRR,   I_NIRR,   I_PAR,    I_CLDS, I_TAIR,
                   I_PREC,   I_RAIN,   I_SNWFAL, I_CO2,  I_AOT40,  
                   I_TNDEP,  I_NH4DEP, I_NO3DEP };

/* *************************************************************
		 Public Functions
************************************************************* */

     // Get file names of input data sets

     void initCO2( ofstream& rflog1 );
     void initNdep( ofstream& rflog1 );
     void initO3 ( ofstream& rflog1 );
     void initPrec( ofstream& rflog1 );
     void initSolarRad( ofstream& rflog1 );
     void initTair( ofstream& rflog1 );


     /* Determine cloudiness based on solar radiation at the top
        of the atmosphere and solar radiation at the top of the
        vegetation canopy */

     double mkclds( const double& girr, const double& nirr );

     double mkd40( const double& lon,
                   const double& lat,
	  	   const string& contnent,
                   const double& o3,
	  	   const int& pdm );

     void setCldsFlags( ofstream& rflog1, const int& requil );
     void setCO2Flags( ofstream& rflog1, const int& requil );
     void setNdepFlags( ofstream& rflog1, const int& requil );
     void setO3Flags( ofstream& rflog1, const int& requil );
     void setPrecFlags( ofstream& rflog1, const int& requil );
     void setTairFlags( ofstream& rflog1, const int& requil );

     /* Determine solar radiation at the top of the atmosphere (i.e.,
        "gross irradiance" or GIRR) based on the solar constant, time
        of year and latitude as described by S. M. Turton (1986)
        Solar radiation under cloudless skies.  Weatherwise 39:
        223-224.  */

     double xgirr( const double& plat, 
                   const int& pdm, 
                   double& psumday );

     /* Determine solar radiation at the top of the vegetation canopy
        (i.e., "net irradiance" or NIRR) based on GIRR and cloudiness */

     double xnirr( const double& clds, const double& girr );

     /* Determine phototsynthetically active radiation (PAR) based on
        NIRR and cloudiness.  Algorithm determined by Jim Raich from
        a variety of studies [e.g., McCree (1966) Agricul. Meteorol.
        3: 353-366; Stigter and Musabilha (1982) Journal of Applied
        Ecology 19: 853-858] that indicate that cloud cover increases
        the proportion of PAR. */

     double xpar( const double& clds, const double& nirr );


/* *************************************************************
		 Public Variables
************************************************************* */


     // "Do data sets have cloudiness data or NIRR data?" flag
     int cldflag;     

     ifstream fco2;

     // Name of file extension and beginning of file name
     //  for cloudiness data

     string icldsend;
     string icldsfname;

     // Name of file extension and beginning of file name
     //  for atmospheric CO2 concentration data

     string ico2end;
     string ico2fname;

     // Name of file extension and beginning of file name
     //  for gross irradiance (i.e., solar radiation at the
     //  top of the atmosphere) data

     string igirrend;
     string igirrfname;

     // Name of file extension and beginning of file name
     //  for atmospheric nitrogen deposition data

     string independ;
     string indepfname;

     // Name of file extension and beginning of file name
     //  for net irradiance (i.e. solar radiation at the 
     //  top of the vegetation canopy) data

     string inirrend;
     string inirrfname;

     // Name of file extension and beginning of file name
     //  for ozone (i.e. AOT40) data

     string io3end;
     string io3fname;

     // Name of file extension and beginning of file name
     //  for photosynthetically active radiation data

     string iparend;
     string iparfname;

     // Name of file extension and beginning of file name
     //  for precipitation data

     string iprecend;
     string iprecfname;

     // Name of file extension and beginning of file name
     //  for air temperature data
     
     string itairend;
     string itairfname;

     int parflag;     // Read in PAR from spatially explicit data sets?

     int predflag;    // Write climate module output to files?

     // Names of climate output variables
     
     vector<string> predstr;

     int sradflag;    // Run solar radiation module?

     // Initial year of transient portion of simulation
     
     int startyr;     

     // Flag for transient cloudiness data 
     //   ( =0 for long-term mean data
     //      1 for transient data)

     int tcldsflag;


     // Flag for transient atmospheric CO2 data 
     //   ( =0 for long-term mean data
     //      1 for transient data)

     int tco2flag;

     // Flag for transient atmospheric N deposition data 
     //   ( =0 for long-term mean data
     //      1 for transient data)

     int tndepflag;

     // Flag for transient ozone (AOT40) data 
     //   ( =0 for long-term mean data
     //      1 for transient data)

     int to3flag;

     // Flag for transient precipitation data 
     //   ( =0 for long-term mean data
     //      1 for transient data)

     int tprecflag;


     // Flag for transient air temperature data 
     //   ( =0 for long-term mean data
     //      1 for transient data)

     int ttairflag;

     // Year represented by the climate data 
     
     int year;

     // Number of days since beginning of year
     
     double yrsumday;


};

#endif
