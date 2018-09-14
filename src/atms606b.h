/* **************************************************************
*****************************************************************
ATMS606.H - object describes physical characteristics of the
	       atmosphere

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
                                                                                                                                                       
*****************************************************************
************************************************************** */

// Class uses global constants CYCLE and MAXRTIME

#ifndef ATMS606_H
#define ATMS606_H

#include "temconsts606.hpp"
#include "inorgn60.hpp"      // Atmospere60 uses InorgN60 class


class Atmosphere60
{

  public:

     Atmosphere60();

/* *************************************************************
		 Public Functions
************************************************************* */

     /* Determine Potential Evapotranspiration based on 
        algorithms from Jensen M. E. and H. R. Haise (1963) 
        Estimating evapotranspiration from solar radiation.  
        Journal of the Irrigation and Drainage Division 4: 
        14-41.  */

     void petjh( const double& nirr,
                 const double& tair,
                 const int& pdm );

     // Determine in precipitation occurs as rain or snow

     void precsplt( const double& prec,
                    const double& tair,
                    double& rain,
                    double& snowfall );

     void resetMonthlyFluxes( void );
     
     void resetYrFluxes( void );


     // "Get" and "Set" private variables

     // aot40 **************************************************
     
     inline double getAOT40( void ) { return aot40; }

     inline void setAOT40( const double& paot40 ) 
     { 
       aot40 = paot40; 
     }

     // avetair ************************************************
     
     inline double getAVETAIR( void ) { return avetair; }

     inline void setAVETAIR( const double& pavetair ) 
     { 
       avetair = pavetair; 
     }

     // clds ***************************************************
     
     inline double getCLDS( void ) { return clds; }

     inline void setCLDS( const double& pclds ) 
     { 
       clds = pclds; 
     }


     // co2 ****************************************************
     
     inline double getCO2( void ) { return co2; }

     inline void setCO2( const double& pco2 ) { co2 = pco2; }

     
     // co2level ***********************************************
     
     inline double getCO2LEVEL( void ) { return co2level; }

     inline void setCO2LEVEL( const double& pco2level ) 
     { 
       co2level = pco2level; 
     }

 
     // girr ***************************************************
     
     inline double getGIRR( void ) { return girr; }

     inline void setGIRR( const double& pgirr ) 
     { 
       girr = pgirr; 
     }


     // initco2 ************************************************
     
     inline double getINITCO2( void ) { return initco2; }

     inline void setINITCO2( const double& pinitco2 ) 
     { 
       initco2 = pinitco2; 
     }


     // mxtair *************************************************
     
     inline double getMXTAIR( void ) { return mxtair; }

     inline void setMXTAIR( const double& pmxtair ) 
     { 
       mxtair = pmxtair; 
     }


     // ndays[] ************************************************
     
     inline double getNDAYS( const int& pdm ) 
     { 
       return ndays[pdm]; 
     }


     // ndep ***************************************************
     
     inline InorgN60 getNDEP( void ) { return ndep; }


     // ndep.nh4 ***********************************************
     
     inline double getNH4DEP( void ) { return ndep.nh4; }

     inline void setNH4DEP( const double& pnh4dep ) 
     { 
       ndep.nh4 = pnh4dep; 
     }

     // ndep.no3 ***********************************************
     
     inline double getNO3DEP( void ) { return ndep.no3; }

     inline void setNO3DEP( const double& pno3dep ) 
     { 
       ndep.no3 = pno3dep; 
     }

     // ndep.total *********************************************
     inline double getTOTNDEP( void ) { return ndep.total; }

     inline void setTOTNDEP( const double& ptotndep ) 
     { 
       ndep.total = ptotndep; 
     }


     // nirr ***************************************************
     
     inline double getNIRR( void ) { return nirr; }

     inline void setNIRR( const double& pnirr ) 
     { 
       nirr = pnirr; 
     }


     // par ****************************************************
     
     inline double getPAR( void ) { return par; }

     inline void setPAR( const double& ppar ) { par = ppar; }


     // pet ****************************************************
     
     inline double getPET( void ) { return pet; }

     inline void setPET( const double& ppet ) { pet = ppet; }


     // petmx **************************************************
     
     inline double getPETMX( void ) { return petmx; }

     inline void setPETMX( const double& ppetmx ) 
     { 
       petmx = ppetmx; 
     }


     // prec ***************************************************
     
     inline double getPREC( void ) { return prec; }

     inline void setPREC( const double& pprec ) 
     { 
       prec = pprec; 
     }


     // prev2tair **********************************************
     
     inline double getPREV2TAIR( void ) { return prev2tair; }

     inline void setPREV2TAIR( const double& pprev2tair ) 
     { 
       prev2tair = pprev2tair; 
     }


     // prevco2 ************************************************
     
     inline double getPREVCO2( void ) { return prevco2; }

     inline void setPREVCO2( const double& pprevco2 ) 
     { 
       prevco2 = pprevco2; 
     }


     // prevtair ***********************************************
     
     inline double getPREVTAIR( void ) { return prevtair; }

     inline void setPREVTAIR( const double& pprevtair ) 
     { 
       prevtair = pprevtair; 
     }


     // prvpetmx ***********************************************
     
     inline double getPRVPETMX( void ) { return prvpetmx; }

     inline void setPRVPETMX( const double& pprvpetmx ) 
     { 
       prvpetmx = pprvpetmx; 
     }


     // rain ***************************************************
     
     inline double getRAIN( void ) { return rain; }

     inline void setRAIN( const double& prain ) 
     { 
       rain = prain; 
     }


     // snowfall ***********************************************
     
     inline double getSNOWFALL( void ) { return snowfall; }

     inline void setSNOWFALL( const double& psnowfall ) 
     { 
       snowfall = psnowfall; 
     }


     // tair ***************************************************
     
     inline double getTAIR( void ) { return tair; }
        
     inline void setTAIR( const double& ptair ) 
     { 
       tair = ptair; 
     }

     // yrndep.nh4 ***********************************************
     
     inline double getYRNH4DEP( void ) { return yrndep.nh4; }

     inline void setYRNH4DEP( const double& pyrnh4dep ) 
     { 
       yrndep.nh4 = pyrnh4dep; 
     }

     inline void updateYRNH4DEP( const double& pnh4dep ) 
     { 
       yrndep.nh4 += pnh4dep; 
     }

     // yrndep.no3 ***********************************************
     
     inline double getYRNO3DEP( void ) { return yrndep.no3; }

     inline void setYRNO3DEP( const double& pyrno3dep ) 
     { 
       yrndep.no3 = pyrno3dep; 
     }

     inline void updateYRNO3DEP( const double& pno3dep ) 
     { 
       yrndep.no3 += pno3dep; 
     }

     // yrndep.total *********************************************
     inline double getYRTOTNDEP( void ) { return yrndep.total; }

     inline void setYRTOTNDEP( const double& pyrtotndep ) 
     { 
       yrndep.total = pyrtotndep; 
     }

     inline void updateYRTOTNDEP( const double& ptotndep ) 
     { 
       yrndep.total += ptotndep; 
     }

     // yrpet ***************************************************
     
     inline double getYRPET( void ) { return yrpet; }
        
     inline void setYRPET( const double& pyrpet ) 
     { 
       yrpet = pyrpet; 
     }

     inline void updateYRPET( const double& ppet ) 
     { 
       yrpet += ppet; 
     }

     // yrprec ***************************************************
     
     inline double getYRPREC( void ) { return yrprec; }
        
     inline void setYRPREC( const double& pyrprec ) 
     { 
       yrprec = pyrprec; 
     }

     inline void updateYRPREC( const double& pprec ) 
     { 
       yrprec += pprec; 
     }
  
     // yrrain ***************************************************
     
     inline double getYRRAIN( void ) { return yrrain; }
        
     inline void setYRRAIN( const double& pyrrain ) 
     { 
       yrrain = pyrrain; 
     }

     inline void updateYRRAIN( const double& prain ) 
     { 
       yrrain += prain; 
     }

     // yrsnowfall *********************************************
     
     inline double getYRSNOWFALL( void ) { return yrsnowfall; }
        
     inline void setYRSNOWFALL( const double& pyrsnowfall ) 
     { 
       yrsnowfall = pyrsnowfall; 
     }

     inline void updateYRSNOWFALL( const double& psnowfall ) 
     { 
       yrsnowfall += psnowfall; 
     }


/* **************************************************************
		 Public Variables
************************************************************** */

     // Number of days per month     
     double ndays[CYCLE];   


   private:
   
/* **************************************************************
		 Private Variables
************************************************************** */

     // Atmospheric ozone AOT 40 index (i.e. ozone 
     //   concentrations above 40 ppb-hr)
     double aot40;

     // Mean annual air temperature (degrees C)
     double avetair;

     // Cloudiness (%)    
     double clds;   
     
     // Atmospheric carbon dioxide concentration (ppmv)
     double co2; 

     // Constant atmospheric CO2 concentration (ppmv) used to 
     //   calibrate TEM or equilibrate TEM at beginning of 
     //   extrapolation     
     double co2level;

     // Gross Irradiance (cal/(sq. cm * day))
     double girr;


     // initial CO2 concentration (ppmv)     
     double initco2;     

     // Maximum monthly air temperature (degrees C)
     double mxtair;


     // Monthly N deposition (mg N / (sq. meter * month)
     InorgN60 ndep;

     // Net Irradiance   (cal/(sq. cm * day))
     double nirr;

     // Photosynthetically Active Radiation  (cal/(sq.cm * day))
     double par;

     // Monthly potential evapotranspiration (mm / month)
     double pet;

     // Maximum PET of current year (mm / month)
     double petmx;

     // Total Precipitation (mm / month)
     double  prec;
     
     // Previous Month's Atmospheric CO2 Concentration (ppmv)
     double prevco2;

     // Previous Month's Air Temperature (degrees C)
     double prevtair;

     // Previous 2 Month's Air Temperature (degrees C)
     double prev2tair;

     // Maximum PET of previous year (mm / month)
     double prvpetmx;

     // Rainfall (mm / month)     
     double  rain;       

     // Snowfall (mm / month)     
     double  snowfall;   

     // Surface Air Temperature (degrees C)
     double tair;

    // Annual NH4, NO3, and total N deposition 
    //   (mg N / (sq. meter * year))
     InorgN60 yrndep;

     // Annual potential evapotranspiration (mm / year)
     double yrpet;

     // Annual total precipitation (mm / year)
     double yrprec;

     // Annual sum of rainfall (mm / year)
     double yrrain;

     // Annual snow ( mm / year)    
     double yrsnowfall;         

};

#endif
