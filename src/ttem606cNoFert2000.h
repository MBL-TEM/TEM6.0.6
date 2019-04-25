/* *************************************************************
****************************************************************
TTEM606CNOFERT2000.H - Terrestrial Ecosystem Model Version 6.0.6
  Nitrogen fertilizers are assumed to be applied to croplands
  between years 1950 and 2000, but then no fertilizers are 
  assumed to be applied to croplands after year 2000.
****************************************************************

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  



References:

VERSION 4.1

Tian, H., J.M. Melillo, D.W. Kicklighter, A.D. McGuire and J.
  Helfrich.  1999. The sensitvity of terrestrial carbon storage to
  historical climate variability and atmospheric CO2 in the United
  States.  Tellus 51B: 414-452.

VERSION 4.2

McGuire, A.D., S. Sitch, J.S. Clein, R. Dargaville, G. Esser, J. Foley,
  M. Heimann, F. Joos, J. Kaplan, D.W. Kicklighter, R.A. Meier, J.M.
  Melillo, B. Moore III, I.C. Prentice, N. Ramankutty, T. Reichenau,
  A. Schloss, H. Tian, L.J. Williams and U. Wittenberg (2001) Carbon
  balance of the terrestrial biosphere in the twentieth century:
  analyses of CO2, climate and land use effects with four process-
  based ecosystem models.  Global Biogeochemical Cycles 15: 183-206.

Tian, H., J.M. Melillo, D.W. Kicklighter, S. Pan, J. Liu, A.D. McGuire
  and B. Moore III (2003) Regional carbon dynamics in monsoon Asia
  and its implications for the global carbon cycle. Global and
  Planetary Change 37: 201-217.

VERSION 4.3

Felzer, B., D. Kicklighter, J. Melillo, C. Wang, Q. Zhuang, and 
  R. Prinn (2004) Effects of ozone on net primary production and 
  carbon sequestration in the conterminous United States using a 
  biogeochemistry model. Tellus 56B: 230-248.

VERSION 5.0

Zhuang, Q., A.D. McGuire, J.M. Melillo, J.S. Clein, R.J.
  Dargaville, D.W. Kicklighter, R.B. Myneni, J. Dong, V.E.
  Romanovsky, J. Harden and J.E. Hobbie (2003) Carbon cycling in
  extratropical terrestrial ecosystems of the Northern Hemisphere
  during the 20th century: a modeling analysis of the influences
  of soil thermal dynamics. Tellus 55B: 751-776.

VERSION 6.0

Hayes, D. J., A. D. McGuire, D. W. Kicklighter, K. R. Gurney, T. 
  J. Burnside, and J. M. Melillo (2011) Is the northern high-
  latitude land-based CO2 sink weakening? Global Biogeochemical 
Cycles 25, GB3018, doi: 10.1029/2010GB003813.

Kicklighter, D. W., D. J. Hayes, J. W. McClelland, B. J. 
  Peterson, A. D. McGuire and J. M. Melillo (in press) Insights 
  and issues with simulating terrestrial DOC loading of arctic 
river networks. Ecological Applications.

McGuire, A. D., D. J. Hayes, D. W. Kicklighter, M. Manizza, 
  Q. Zhuang, M. Chen, M. J. Follows, K. R. Gurney, J. W. 
  McClelland, J. M. Melillo, B. J. Peterson and R. G. Prinn 
  (2010) An analysis of the carbon balance of the Arctic Basin 
  from 1997 to 2006. Tellus 62B, 455-474, 
  doi: 10.1111/j.1600-0889.2010.00497.x.

Tian, H., J. Melillo, C. Lu, D. Kicklighter, M. Liu, W. Ren, 
  X. Xu, G. Chen, C. Zhang, S. Pan, J. Liu and S. Running (2011) 
  China's terrestrial carbon balance: contributions from 
  multiple global change factors. Global Biogeochemical Cycles 
  25, GB1007, doi: 10.1029/2010GB003838.


Runge - Kutta - Fehlberg (RKF) adaptive integrator:

Cheney, W., and D. Kincaid.  1985.  Numerical mathematics and
  computing.  Second edition.  Brooks/ Col Publishing Co.  Monterey,
  CA.  pp. 325-328.

****************************************************************
************************************************************** */

#ifndef TTEM606_H
#define TTEM606_H

#include "protocol605.hpp"
 
#include "temconsts606.hpp"

#include<cstdio>

  using std::printf;

#include<iostream>

  using std::cout;
  using std::cin;
  using std::ios;
  using std::cerr;
  using std::endl;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<cstdlib>

  using std::exit;
  using std::atof;
  using std::atoi;

#include<cmath>

  using std::exp;
  using std::fabs;
  using std::modf;
  using std::pow;

#include<vector>

  using std::vector;
    
#include<string>
  
  using std::string;

#include<cstring>


#ifdef CALIBRATE_TEM
  #include<ncurses.h>
  #include<cctype>
    using std::toupper;
#endif


#ifdef CALIBRATE_TEM
  // Additional global constants

  const int WSY = 9;
  const int CSY = 9;
  const int NSY = 9;
  const int STSY = 10;
  const int GSY = 9;
#endif


// Objects describing basic components of the ecosystem

#include "bioms423.hpp"   // TTEM uses Biomass class


// Objects describing the structure of the ecosystem

#include "atms606b.h"    // TTEM uses Atmosphere60 class
#include "tveg606cNoFert2000.h" // TTEM uses Tveg60 class
#include "tsoil606b.h"  // TTEM uses Tsoil60 class
#include "tmcrb606b.h"   // TTEM uses Tmicrobe60 class

// Objects describing the effects of human activities on the ecosystem

#include "humnact606cNoFert2000.h" // TTEM uses Humnact60 class


class TTEM60 : public ProcessXML60
{

  public:

     TTEM60();

     enum temkey
     {
       I_VEGC,        I_SOLC,       I_DOC,      
       
       I_STRN,        I_STON,       I_SOLN,       I_DON,       I_NH4,      
       I_NO3,
                        
       I_SM,          I_RGRW,       I_SGRW,

       I_UNRMLF,      I_LEAF,       I_LAI,        I_FPC,

       I_INGPP,       I_GPP,        I_FOZONE,     I_FINDOZONE, I_INNPP,    
       I_NPP,         I_GPR,        I_RVMNT,      I_RVGRW,     I_ABVGPR,   
       I_ROOTGPR,     I_LTRFALC,    I_CDCMP,      I_RH,        I_DOCP,     
       I_LCHDOC,      I_ERDPOC,
             

       I_AGFRTN,      I_BNFIX,      I_SNFIX,      I_ANFIX,     I_INNUP,
       I_INNH4UP,     I_INNO3UP,    I_VNUP,       I_VNH4UP,    I_VNO3UP,   
       I_VSUP,        I_VLUP,       I_VNMBL,      I_VNRSRB,    I_LTRFALN,     
       I_NDCMP,       I_DONP,     
       I_GMIN,        I_NH4IMM,     I_NIMM,       I_NMIN,      I_AIMMNH4,  
       I_AIMMNO3,     I_AMMN,       I_NTRF,       I_NO3P,      I_NOP,      
       I_N2OP,        I_N2P,        I_DNTRF,      I_NH3FLX,    I_NOFLX,    
       I_N2OFLX,      I_N2FLX,      I_LCHNH4,     I_LCHNO3,    I_LCHDON,   
       I_ERDPON,

       I_AGIRRIG,     I_INEET,      I_EET,        I_RPERC,     I_SPERC,    
       I_RRUN,        I_SRUN,     

       I_NSOLC,       I_TSOLC,      I_TOTEC,      I_TOTC, 
       
       I_VEGN,        I_NSOLN,      I_TSOLN,      I_AVLN,
       
       I_SNWPCK,      I_AVLW,       I_VSM,        I_PCTP,     
       
       I_FORAGEC,     I_MANUREC,    I_ANIMALR,    I_RSOIL,     I_NEP,      
       I_NCE,         I_NECB, 
       
       I_FORAGEN,     I_MANUREN,    I_URINE,      I_NINP,       I_NLST,     
       I_NENB,
       
       I_PET,         I_SNWINF,     I_WYLD,
       
       I_AGPRDC,      I_PROD10C,    I_PROD100C,   I_TOTPRDC,  
       
       I_RESIDC,      I_AGSTUBC,     
       
       I_AGPRDN,      I_PROD10N,    I_PROD100N,   I_TOTPRDN,
       
       I_RESIDN,      I_AGSTUBN,
       
       I_CNVRTC,      I_VCNVRTC,    I_SCNVRTC,    I_SLASHC,   I_CFLX,     
       
       I_CNVRTN,      I_VCNVRTN,    I_SCNVRTN,    I_SLASHN,   
       I_NTOTRTNT,    I_NH4RTNT,    I_NO3RTNT,
       I_VNTOTRTNT,   I_VNH4RTNT,   I_VNO3RTNT,
       I_SNTOTRTNT,   I_SNH4RTNT,   I_SNO3RTNT, 

       I_AGFPRDC,     I_AGFPRDN,    I_FRESIDC,    I_FRESIDN,  I_AGPRDFC,
       I_AGPRDFN,     I_RESIDFC,    I_RESIDFN,  
       
       I_PRDF10C,     I_PRDF10N,    I_PRD10FC,    I_PRD10FN,  I_PRDF100C,  
       I_PRDF100N,    I_PRD100FC,   I_PRD100FN,   I_TOTFPRDC, I_TOTFPRDN, 
       I_TOTPRDFC,    I_TOTPRDFN,

       I_CROPC,       I_NATVEGC,    I_CROPN,      I_NATVEGN,  I_CSTRN,
       I_NATSTRN,     I_CSTON,      I_NATSTON,

       I_CROPULF,     I_NATULF,     I_CROPLEAF,   I_NATLEAF, I_CROPLAI,
       I_NATLAI,      I_CROPFPC,    I_NATFPC,

       I_AGINGPP,     I_NATINGPP,   I_AGGPP,      I_NATGPP,   I_AGINNPP,
       I_NATINNPP,    I_AGNPP,      I_NATNPP,     I_AGGPR,    I_NATGPR,
       I_AGRVMNT,     I_NATRVMNT,   I_AGRVGRW,    I_NATRVGRW, I_AGLTRC,
       I_NATLTRC,

       I_AGSNFX,      I_NATSNFX,    I_AGINNUP,    I_NATINNUP, I_AINNH4UP,
       I_NINNH4UP,    I_AINNO3UP,   I_NINNO3UP,   I_AGVNUP,   I_NATVNUP,
       I_AGVNH4UP,    I_NVNH4UP,    I_AGVNO3UP,   I_NVNO3UP,  I_AGVSUP,
       I_NATVSUP,     I_AGVLUP,     I_NATVLUP,    I_AGVNMBL,  I_NATVNMBL,
       I_AGVNRSRB,    I_NVNRSRB,    I_AGLTRN,     I_NATLTRN,

       I_TSOIL,       I_DST0,       I_DST5,       I_DST10,    I_DST20,
       I_DST50,       I_DST100,     I_DST200,     I_FRONTD,   I_THAWBE,
       I_THAWEND,     I_THAWPCT,    I_ACTLAYER,

       I_TOTNDEP,     I_NH4DEP,     I_NO3DEP,   
       I_FIRENTOTDEP, I_FIRENH4DEP, I_FIRENO3DEP,

       I_CO2G,        I_CO2W,       I_HCO3,       I_RHCO3,    I_ALK, 
       I_CO2DISS,     I_LCHCO2,     I_HCO3P,      I_RHCO3P,   I_LCHHCO3,  
       I_LCHALK, 
       
       I_ISOPREN,  I_TERPEN,   I_ORVOC,    I_OVOC,     I_VOC
     };

//     #ifdef CALIBRATE_TEM    
       enum scykey { NOCKEY,       GET_VEGC,    

                     GET_LEAF,     GET_LAI,      GET_FPC,      

                     GET_SOLC,     GET_DOC,      GET_NSOLC,   
                     GET_TSOLC,

                     GET_INGPP,    GET_GPP,     GET_INNPP,
                     GET_NPP,      GET_GPR,     GET_RVMNT,
                     GET_RVGRW,    GET_LTRFALC, GET_AGSTUBC,
                     GET_CDCMP,    GET_RH,      GET_RSOIL,   
                     GET_LCHDOC,   GET_NEP,     GET_NECB,

                     GET_D40,      GET_FOZONE,


                     GET_CNVRTC,   GET_VCNVRTC, GET_SCNVRTC,
                     GET_SLASHC,   GET_CFLX,    GET_NCE,

                     GET_AGPRDC,   GET_PROD10C, GET_PROD100C,
                     GET_RESIDC,

                     GET_AGFPRDC,  GET_PRDF10C, GET_PRDF100C,
                     GET_FRESIDC,

                     GET_AGPRDFC,  GET_PRD10FC, GET_PRD100FC,
                     GET_TOTPRDFC, GET_RESIDFC };

       enum snykey { NONKEY,       GET_STRN,    GET_STON,
                     GET_SOLN,     GET_DON,     GET_NSOLN,   
                     GET_TSOLN,    GET_NH4,     GET_NO3,

                     GET_NINP,     GET_TNDEP,   GET_NH4DEP,
                     GET_NO3DEP,   GET_AGFRTN,  GET_BNFIX,
                     GET_SNFIX,    GET_ANFIX,   GET_INNUP,   
                     GET_INNH4UP,  GET_INNO3UP, GET_VNUP,    
                     GET_VNH4UP,   GET_VNO3UP,  GET_VSUP,    
                     GET_VLUP,     GET_VNMBL,   GET_VNRSRB,  
                     GET_LTRFALN,  GET_AGSTUBN, GET_NDCMP,   
                     GET_DONP,     GET_GMIN,    GET_NH4IMM,  
                     GET_NO3IMM,   GET_NIMM,    GET_NMIN, 
                     GET_LCHNH4,   GET_LCHNO3,  GET_LCHDON,  
                     GET_NLST,     GET_NENB,

                     GET_CNVRTN,   GET_VCNVRTN, GET_SCNVRTN,
                     GET_SLASHN,   GET_NRETNT,  GET_NVRTNT,
                     GET_NSRTNT,

                     GET_AGPRDN,   GET_PROD10N, GET_PROD100N,
                     GET_RESIDN,

                     GET_AGFPRDN,  GET_PRDF10N, GET_PRDF100N,
                     GET_FRESIDN,
                     GET_AGPRDFN,  GET_PRD10FN, GET_PRD100FN,
                     GET_TOTPRDFN, GET_RESIDFN, GET_FIRENDEP,

                     GET_L2SN };

       enum swykey { NOWKEY,    GET_SH2O,   GET_PCTP,   GET_VSM,
                     GET_AVLW,  GET_SNWPK,  GET_RGRW,   GET_SGRW,

                     GET_RAIN,  GET_SNWFAL, GET_SNWINF, GET_AGIRRIG,
                     GET_PET,   GET_INEET,  GET_EET,    GET_RPERC,
                     GET_SPERC, GET_RRUN,  GET_SRUN,    GET_WYLD };

       enum sstykey { NOSTKEY,     GET_TSOIL,   GET_DST00, 
                      GET_DST05,   GET_DST10,   GET_DST20,
                      GET_DST50,   GET_DST100,  GET_DST200,

                      GET_FRONTD,  GET_ACTLAY,
                      GET_THAWPCT, GET_THWBEG1, GET_THWEND1,  
                      GET_THWBEG2, GET_THWEND2 };

       enum sgykey { NOGKEY,      GET_GNH4,    GET_GNO3,
                     GET_GNMIN,   GET_NTRF,    GET_DNTRF,
                     GET_AIMMNH4, GET_AMMN,    GET_AIMMNO3, 
                     GET_NO3P,    GET_NOP,     GET_N2OP,    
                     GET_N2P,     GET_NH3FLX,  GET_NOFLX,   
                     GET_N2OFLX,  GET_N2FLX,   GET_GNLST, };
//     #endif

/* **************************************************************
			Public Functions
************************************************************** */

     void askODE( ofstream& rflog1 );

//     #ifdef CALIBRATE_TEM
       void displayOptionalCflx( const scykey& s );
       void displayOptionalNflx( const snykey& s );
       void displayOptionalSoilTemp( const sstykey& s );
       void displayOptionalTraceGas( const sgykey& s );
       void displayOptionalWflx( const swykey& s );
//     #endif
     
     int ecdqc( const int& dcmnt );

     void ECDsetODEstate( const int& pdcmnt,
                          const double& psiplusc );
 
     void getco2( void );

     void getCropSpecificECD( const int& dv, 
                              const string& agecd );


//     #ifdef CALIBRATE_TEM
       double getOptionalCflx( const int& optflx );

       double getOptionalNflx( const int& optflx );

       double getOptionalSoilTemp( const int& optflx );

       double getOptionalTraceGas( const int& optflx );

       double getOptionalWflx( const int& optflx );
//     #endif


     void getVegSpecificECD( const int& numcmnt, 
                             ofstream& rflog1 );

     void getVegSpecificECD( const int& dv, 
                             const string& ecd );
     
     void initrun( ofstream& rflog1 );

     int monthlyTransient( const int& outyr,
                           const int& pdm,
                           const double& outtol,
                           ofstream& rflog1 );

     #ifdef CALIBRATE_TEM
       inline scykey& next( scykey& s )
       {
         return s = (GET_RESIDFC == s) ? GET_VEGC : scykey( s+1 );
       }

       inline sgykey& next( sgykey& s )
       {
         return s = (GET_GNLST == s) ? GET_GNH4 : sgykey( s+1 );
       }

       inline snykey& next( snykey& s )
       {
         return s = (GET_L2SN == s) ? GET_STRN : snykey( s+1 );
       }

       inline sstykey& next( sstykey& s )
       {
         return s = (GET_THWEND2 == s) ? GET_TSOIL : sstykey( s+1 );
       }

       inline swykey& next( swykey& s )
       {
         return s = (GET_WYLD == s) ? GET_SH2O : swykey( s+1 );
       }

       inline scykey& prev( scykey& s )
       {
         return s = (GET_VEGC == s) ? GET_RESIDFC : scykey( s-1 );
       }

       inline sgykey& prev( sgykey& s )
       {
         return s = (GET_GNH4 == s) ? GET_GNLST : sgykey( s-1 );
       }

       inline snykey& prev( snykey& s )
       {
         return s = (GET_STRN == s) ? GET_L2SN : snykey( s-1 );
       }

       inline sstykey& prev( sstykey& s )
       {
         return s = (GET_TSOIL == s) ? GET_THWEND2 : sstykey( s-1 );
       }

       inline swykey& prev( swykey& s )
       {
         return s = (GET_SH2O == s) ? GET_WYLD : swykey( s-1 );
       }
     #endif

     void resetMonthlyELMNTFluxes( void );

     void resetYrFluxes( void );

     void setELMNTecd( const int& pdcmnt,
                       const double& psiplusc );

     void setEquilC2N( const int& pdcmnt,
                       const double& co2 );

     void setEquilEvap( const double& nirr,
                        const double& tair,
                        const int& pdm );

     void setPrevState( void );
     
     int stepmonth( const int& dyr,
                    const int& pdm,
                    int& intflag,
                    const double& tol,
                    ofstream& rflog1 );

     int testEquilibrium( void );

     void updateYearSummary( void );
     
     void writesitecd( ofstream& fout, const int& dcmnt );


     // "Get" and "Set" private variables and parameters   
     
     // bnfix **************************************************
     
     inline double getBNFIX( void ) { return bnfix; }


     // doccut ***************************************************
     
     inline double getDOCCUT( const int& pcmnt )
     {
       return doccut[pcmnt];
     }

     inline void setDOCCUT( const double& pdoccut, 
                            const int& pcmnt )
     {
       doccut[pcmnt] = pdoccut;
     }

     // doc1a ***************************************************
     
     inline double getDOC1A( const int& pcmnt )
     {
       return doc1a[pcmnt];
     }

     inline void setDOC1A( const double& pdoc1a, 
                           const int& pcmnt )
     {
       doc1a[pcmnt] = pdoc1a;
     }

     // doc1b ***************************************************
     
     inline double getDOC1B( const int& pcmnt )
     {
       return doc1b[pcmnt];
     }

     inline void setDOC1B( const double& pdoc1b, 
                           const int& pcmnt )
     {
       doc1b[pcmnt] = pdoc1b;
     }


     // doc2a ***************************************************
     
     inline double getDOC2A( const int& pcmnt )
     {
       return doc2a[pcmnt];
     }

     inline void setDOC2A( const double& pdoc2a, 
                           const int& pcmnt )
     {
       doc2a[pcmnt] = pdoc2a;
     }

     // doc2b ***************************************************
     
     inline double getDOC2B( const int& pcmnt )
     {
       return doc2b[pcmnt];
     }

     inline void setDOC2B( const double& pdoc2b, 
                           const int& pcmnt )
     {
       doc2b[pcmnt] = pdoc2b;
     }


      // doncut ***************************************************
     
     inline double getDONCUT( const int& pcmnt )
     {
       return doncut[pcmnt];
     }

     inline void setDONCUT( const double& pdoncut, 
                            const int& pcmnt )
     {
       doncut[pcmnt] = pdoncut;
     }


     // don1a ***************************************************
     
     inline double getDON1A( const int& pcmnt )
     {
       return don1a[pcmnt];
     }

     inline void setDON1A( const double& pdon1a, 
                           const int& pcmnt )
     {
       don1a[pcmnt] = pdon1a;
     }

     // don1b ***************************************************
     
     inline double getDON1B( const int& pcmnt )
     {
       return don1b[pcmnt];
     }

     inline void setDON1B( const double& pdon1b, 
                           const int& pcmnt )
     {
       don1b[pcmnt] = pdon1b;
     }


     // don2a ***************************************************
     
     inline double getDON2A( const int& pcmnt )
     {
       return don2a[pcmnt];
     }

     inline void setDON2A( const double& pdon2a, 
                           const int& pcmnt )
     {
       don2a[pcmnt] = pdon2a;
     }

     // don2b ***************************************************
     
     inline double getDON2B( const int& pcmnt )
     {
       return don2b[pcmnt];
     }

     inline void setDON2B( const double& pdon2b, 
                           const int& pcmnt )
     {
       don2b[pcmnt] = pdon2b;
     }


     // maxit ***************************************************
     
     inline int getMAXIT( void )
     {
       return maxit;
     }

     inline void setMAXIT( const int& pmaxit )
     {
       maxit = pmaxit;
     }


     // maxitmon*************************************************
     
     inline long getMAXITMON( void )
     {
       return maxitmon;
     }

     inline void setMAXITMON( const long& pmaxitmon )
     {
       maxitmon = pmaxitmon;
     }


    // nce ****************************************************
     
     inline double getNCE( void ) { return nce; }


     // nep ****************************************************
     
     inline double getNEP( void ) { return nep; }


     // nh4a ***************************************************
     
     inline double getNH4A( const int& pcmnt )
     {
       return nh4a[pcmnt];
     }

     inline void setNH4A( const double& pnh4a, 
                          const int& pcmnt )
     {
       nh4a[pcmnt] = pnh4a;
     }

     // nh4b ***************************************************
     
     inline double getNH4B( const int& pcmnt )
     {
       return nh4b[pcmnt];
     }

     inline void setNH4B( const double& pnh4b, 
                          const int& pcmnt )
     {
       nh4b[pcmnt] = pnh4b;
     }

      // no3cut ***************************************************
     
     inline double getNO3CUT( const int& pcmnt )
     {
       return no3cut[pcmnt];
     }

     inline void setNO3CUT( const double& pno3cut, 
                            const int& pcmnt )
     {
       no3cut[pcmnt] = pno3cut;
     }


     // no31a **************************************************
     
     inline double getNO31A( const int& pcmnt )
     {
       return no31a[pcmnt];
     }

     inline void setNO31A( const double& pno31a, 
                           const int& pcmnt )
     {
       no31a[pcmnt] = pno31a;
     }

     // no31b **************************************************
     
     inline double getNO31B( const int& pcmnt )
     {
       return no31b[pcmnt];
     }

     inline void setNO31B( const double& pno31b, 
                           const int& pcmnt )
     {
       no31b[pcmnt] = pno31b;
     }

     // no32a **************************************************
     
     inline double getNO32A( const int& pcmnt )
     {
       return no32a[pcmnt];
     }

     inline void setNO32A( const double& pno32a, 
                           const int& pcmnt )
     {
       no32a[pcmnt] = pno32a;
     }

     // no32b **************************************************
     
     inline double getNO32B( const int& pcmnt )
     {
       return no32b[pcmnt];
     }

     inline void setNO32B( const double& pno32b, 
                           const int& pcmnt )
     {
       no32b[pcmnt] = pno32b;
     }

     // necb ***************************************************
     
     inline double getNECB( void ) { return necb; }


     // nenb ***************************************************
     
     inline double getNENB( void ) { return nenb; }


     // prevy **************************************************
     
     inline double getPREVY( const int& i ) { return prevy[i]; }

     inline void setPREVY( const double& pprevy, const int& i )
     {
       prevy[i] = pprevy;
     }


     // rsoil **************************************************
     
     inline double getRSOIL( void ) { return rsoil; }


     // solca **************************************************
     
     inline double getSOLCA( const int& pcmnt )
     {
       return solca[pcmnt];
     }

     inline void setSOLCA( const double& psolca, 
                           const int& pcmnt )
     {
       solca[pcmnt] = psolca;
     }


     // solcb **************************************************
     
     inline double getSOLCB( const int& pcmnt )
     {
       return solcb[pcmnt];
     }

     inline void setSOLCB( const double& psolcb, 
                           const int& pcmnt )
     {
       solca[pcmnt] = psolcb;
     }


     // solna **************************************************
     
     inline double getSOLNA( const int& pcmnt )
     {
       return solna[pcmnt];
     }

     inline void setSOLNA( const double& psolna, 
                           const int& pcmnt )
     {
       solna[pcmnt] = psolna;
     }


     // solnb **************************************************
     
     inline double getSOLNB( const int& pcmnt )
     {
       return solnb[pcmnt];
     }

     inline void setSOLNB( const double& psolnb, 
                           const int& pcmnt )
     {
       solnb[pcmnt] = psolnb;
     }


     // stona **************************************************
     
     inline double getSTONA( const int& pcmnt )
     {
       return stona[pcmnt];
     }

     inline void setSTONA( const double& pstona, 
                           const int& pcmnt )
     {
       stona[pcmnt] = pstona;
     }


     // stonb **************************************************
     
     inline double getSTONB( const int& pcmnt )
     {
       return stonb[pcmnt];
     }

     inline void setSTONB( const double& pstonb, 
                           const int& pcmnt )
     {
       stonb[pcmnt] = pstonb;
     }


     // strna **************************************************
     
     inline double getSTRNA( const int& pcmnt )
     {
       return strna[pcmnt];
     }

     inline void setSTRNA( const double& pstrna, 
                           const int& pcmnt )
     {
       strna[pcmnt] = pstrna;
     }


     // strnb **************************************************
     
     inline double getSTRNB( const int& pcmnt )
     {
       return strnb[pcmnt];
     }

     inline void setSTRNB( const double& pstrnb, 
                           const int& pcmnt )
     {
       strnb[pcmnt] = pstrnb;
     }


     // totalc *************************************************
     
     inline double getTOTALC( void ) { return totalc; }


     // vegca **************************************************
     
     inline double getVEGCA( const int& pcmnt )
     {
       return vegca[pcmnt];
     }

     inline void setVEGCA( const double& pvegca, 
                           const int& pcmnt )
     {
       vegca[pcmnt] = pvegca;
     }


     // vegcb **************************************************
     
     inline double getVEGCB( const int& pcmnt )
     {
       return vegcb[pcmnt];
     }

     inline void setVEGCB( const double& pvegcb, 
                           const int& pcmnt )
     {
       vegcb[pcmnt] = pvegcb;
     }


     // y ******************************************************
          
     inline double getY( const int& i ) { return y[i]; }

     inline void setY( const double& py, const int& i )
     {
       y[i] = py;
     }

     // yrbnfix ************************************************
     
     inline double getYRBNFIX( void )
     {
       return yrbnfix;
     }

     inline void setYRBNFIX( const double& pyrbnfix )
     {
       yrbnfix = pyrbnfix;
     }

     inline void updateYRBNFIX( const double& pbnfix )
     {
       yrbnfix += pbnfix;
     }

     // yrnce ************************************************
     
     inline double getYRNCE( void )
     {
       return yrnce;
     }

     inline void setYRNCE( const double& pyrnce )
     {
       yrnce = pyrnce;
     }

     inline void updateYRNCE( const double& pnce )
     {
       yrnce += pnce;
     }

    // yrnep ************************************************
     
     inline double getYRNEP( void )
     {
       return yrnep;
     }

     inline void setYRNEP( const double& pyrnep )
     {
       yrnep = pyrnep;
     }

     inline void updateYRNEP( const double& pnep )
     {
       yrnep += pnep;
     }

    // yrnecb ************************************************
     
     inline double getYRNECB( void )
     {
       return yrnecb;
     }

     inline void setYRNECB( const double& pyrnecb )
     {
       yrnecb = pyrnecb;
     }

     inline void updateYRNECB( const double& pnecb )
     {
       yrnecb += pnecb;
     }

    // yrnenb ************************************************
     
     inline double getYRNENB( void )
     {
       return yrnenb;
     }

     inline void setYRNENB( const double& pyrnenb )
     {
       yrnenb = pyrnenb;
     }

     inline void updateYRNENB( const double& pnenb )
     {
       yrnenb += pnenb;
     }

    // yrrsoil ************************************************
     
     inline double getYRRSOIL( void )
     {
       return yrrsoil;
     }

     inline void setYRRSOIL( const double& pyrrsoil )
     {
       yrrsoil = pyrrsoil;
     }

     inline void updateYRRSOIL( const double& prsoil )
     {
       yrrsoil += prsoil;
     }
     
    // yrtotalc ************************************************
     
     inline double getYRTOTALC( void )
     {
       return yrtotalc;
     }

     inline void setYRTOTALC( const double& pyrtotalc )
     {
       yrtotalc = pyrtotalc;
     }

     inline void updateYRTOTALC( const double& ptotalc )
     {
       yrtotalc += ptotalc;
     }
                          

/* *************************************************************
			 Public Variables
************************************************************** */

     
     #ifdef CALIBRATE_TEM
       // Directory paths to calibration data
       string cal43dir;
       string cal50dir;
       string cal60dir;

       // Input Ecd files with calibration data
       string soilfile;
       string rootfile;
       string vegfile;
       string leaffile;
       string mcrvfile;
       string agfile;
       string snowfile;
       string slayerfile;
     #endif
     
     #ifdef CALIBRATE_TEM
       int adapttol;
     #endif
     
     Humanact60 ag;

     Atmosphere60 atms;

     static int avlnflag;
     
     static int baseline;

     #ifdef CALIBRATE_TEM
       int calwind;
     #endif
     
     int climitflg;

     static double ctol;

     int dbug;

     static int diffyr;

     // Counter of months since disturbance
     int distmnthcnt;
     
     // Flag to indicate that a disturbance has occurred
     //   in a particular year.  Different values represent
     //   different types of disturbances:
     //   0 = no disturbance
     //   1 = sustained disturbed state 
     //         (e.g., conversion to agriculture or urban areas)
     //   2 = timber harvest
     //   3 = fire
     int disturbflag;
     
     // Month in which disturbance occurred
     // (e.g. 1 = January, ...., 12 = December)
     int disturbmonth;   

     double elev;              // elevation (m)

     static int endeq;

     static int endyr;

     static int equil;

     // index for vegetation type (ez = veg.temveg-1)
     int ez;

     ifstream fecd;

     // Counter of months since fire disturbance
     int firemnthcnt;

     static int initbase;

     int initFlag;

     static double inittol;

     #ifdef CALIBRATE_TEM
       int intbomb;
     #endif

     static int intflag;

     static int maxnrun;

     static int maxyears;

     Tmicrobe60 microbe;

     static int moistlim;

     int nattempt;

     static int nfeed;

     double nfert;

     static double ntol;

     static int o3flag;

     int predflag;

     vector<string> predstr;

     int qualcon[MAXRTIME];

     int retry;

     static int rheqflag;

     static int runsize;

     #ifdef CALIBRATE_TEM
       scykey scy[CSY];
       sgykey sgy[GSY];
       snykey sny[NSY];
       sstykey ssty[STSY];
       swykey swy[WSY];
     #endif
     
     Tsoil60 soil;


     static int startyr;

     static int strteq;

     double tol;

     #ifdef CALIBRATE_TEM
       int tolbomb;
    
       int topwind;
     #endif

     int totyr;

     Tveg60 veg;

     static int wrtyr;

     static double wtol;


     // Site ECD variables

     string version;
     string sitename;
     string developer;
     double sitecol;
     double siterow;
     long updated;
     string description;


/* **************************************************************
		     Protected Variables
************************************************************** */

//  protected:

     int dbugflg;


  private:

/* **************************************************************
		 Private Functions
************************************************************** */

     int adapt( const int& numeq, 
                double pstate[], 
                const double& ptol, 
                const int& pdm );

     void asphaltDynamics( const int& dm, double pstate[] );

     int boundcon( double ptstate[],
                   double err[],
                   const double& ptol );

     void delta( const int& dm,
                 double pstate[],
                 double pdstate[] );

     void cropDynamics( const int& dm, double pstate[] );

     void getenviron( const int& pdyr,
                      const int& pdm,
                      ofstream& rflog1 );

     void lakeDynamics( const int& dm, double pstate[] );

     void lawnDynamics( const int& dm, double pstate[] );

     void massbal( double y[NUMEQ], 
                   double prevy[MAXSTATE] );

     void natvegDynamics( const int& dm, double pstate[] );

     void pastureDynamics( const int& dm, double pstate[] );

     #ifdef CALIBRATE_TEM
       void pcdisplayDT( const double& tottime,
                         const double& deltat );

       void pcdisplayMonth( const int& dyr,
                            const int& dm );

       void pcdisplayODEerr( const int& test, 
                             double pstate[] );
     #endif

     void resetODEflux( void );

     void rkf( const int& numeq, 
               double pstate[], 
               double& pdt, 
               const int& pdm );
                 
     void step( const int& numeq, 
                double pstate[], 
                double pdstate[], 
                double ptstate[], 
                double& pdt );


/* **************************************************************
		     Private Variables
************************************************************** */

     // Biological Nitrogen Fixation      
     double bnfix;    // (g N / (sq. meter * month))

     // Net Carbon Exchange (NCE)
     double nce;

     // Net Ecosystem Production
     double nep;      // (g C / (sq. meter * month))

     // Net Terrestrial Carbon Balance (NECB)
     double necb;     // (g C / (sq. meter * month))

     // Net Terrestrial Nitrogen Balance (NENB)
     double nenb;     // (g C / (sq. meter * month))

     // Values of ODE state variables for previous month 
     double prevy[MAXSTATE];

     // Soil respiration (heterotropic + root respiration)
     double rsoil;    // (g C / (sq. meter * month))

     // Total carbon storage (veg.plant + soil.org)
     double totalc;   // (g C/sq. meter)

     // Values of ODE state variables for current month
     double y[NUMEQ];

     double yrbnfix;  // (g N / (sq. meter * year))

     double yrnce;

     double yrnep;    // (g C / (sq. meter * year))

     double yrnecb;   // (g C / (sq. meter * year))

     double yrnenb;   // (g N / (sq. meter * year))
     
     double yrrsoil;  // (g C / (sq. meter * year))

     double yrtotalc;

    
     // Adaptive integrator variables

     int blackhol;
     static int maxit;
     static long maxitmon;

     int syint;
     int test;

     double dum4[NUMEQ];
     double error[NUMEQ];
     
     double dum5[NUMEQ];
     double dumy[NUMEQ];

     double ydum[NUMEQ];
     double dy[NUMEQ];
     double yprime[NUMEQ];
     double rk45[NUMEQ];

     double f11[NUMEQ];
     double f2[NUMEQ];
     double f13[NUMEQ];
     double f3[NUMEQ];
     double f14[NUMEQ];
     double f4[NUMEQ];
     double f15[NUMEQ];
     double f5[NUMEQ];
     double f16[NUMEQ];
     double f6[NUMEQ];


     static double  a1;

     static double  a3;
     static double a31;
     static double a32;

     static double  a4;
     static double a41;
     static double a42;
     static double a43;

     static double  a5;
     static double a51;
     static double a52;
     static double a53;
     static double a54;

     static double  b1;
     static double  b3;
     static double  b4;
     static double  b5;

     static double  b6;
     static double b61;
     static double b62;
     static double b63;
     static double b64;
     static double b65;

     double dummy;


/* **************************************************************
			Private Parameters
************************************************************** */

     double vegca[MAXCMNT];
     double vegcb[MAXCMNT];

     double strna[MAXCMNT];
     double strnb[MAXCMNT];

     double stona[MAXCMNT];
     double stonb[MAXCMNT];

     double solca[MAXCMNT];
     double solcb[MAXCMNT];

     double solna[MAXCMNT];
     double solnb[MAXCMNT];

     double doccut[MAXCMNT];
     double doc1a[MAXCMNT];
     double doc1b[MAXCMNT];
     double doc2a[MAXCMNT];
     double doc2b[MAXCMNT];

     double doncut[MAXCMNT];
     double don1a[MAXCMNT];
     double don1b[MAXCMNT];
     double don2a[MAXCMNT];
     double don2b[MAXCMNT];

     double nh4a[MAXCMNT];
     double nh4b[MAXCMNT];

     double no3cut[MAXCMNT];
     double no31a[MAXCMNT];
     double no31b[MAXCMNT];
     double no32a[MAXCMNT];
     double no32b[MAXCMNT];


 };

#endif
