/* **************************************************************
*****************************************************************
TELM606CNOFERT2000.H - Determines the interface among CLM, LCLUC 
  and TEM modules.  Nitrogen fertilizers are assumed to be 
  applied to croplands from 1950 to 2000, but then no fertilizers
  are assumed to be applied after year 2000.
  
Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

*****************************************************************
************************************************************** */

#ifndef TELM606_H
#define TELM606_H

const int TQCZEROFLAG = 31;


//Modules representing climate and TEM

#include "tclm606b.h"   // TEMelmnt60 uses the TEMclm60 class

// TEMelmnt60 uses the Elmntcohort60 
#include "telmntcohort606c.hpp"  

#include "tlcluc606.h" // TEMelmnt60 uses the TEMlcluc60 class
#include "ttem606cNoFert2000.h" // TEMelmnt60 uses the TTEM60 class

// Modules describing the interface with spatially explicit 
//   data sets

#include "tclmdat606.h"  //TEMelmnt60 uses the Clmdata60 class
#include "tsoldat606.h"  //TEMelmnt60 uses the Soildata60 class
#include "telvdat605.h"  //TEMelmnt60 uses the Elevdata60 class
#include "ttemdat606.h"  //TEMelmnt60 uses the Temdata60 class

class TEMelmnt60
{

  public:

     TEMelmnt60();

     enum outkey
     {
       I_VEGC,     I_SOLC,     I_NSOLC,     I_DOC,      I_TSOLC,       
       I_CO2G,     I_CO2W,     I_HCO3,      I_RHCO3,    I_ALK,      
       I_CROPC,    I_NATVEGC,  I_AGPRDC,    I_PROD10C,  I_PROD100C,  
       I_TOTPRDC,  I_RESIDC,   I_TOTEC,     I_TOTGC,    I_TOTC,     
       
       I_INGPP,    I_GPP,      I_FOZONE,    I_FINDOZONE, I_INNPP,     
       I_NPP,      I_GPR,      I_RVMNT,     I_RVGRW,     I_ABVGPR,    
       I_ROOTGPR,  I_ISOPREN,  I_TERPEN,    I_ORVOC,     I_OVOC,      
       I_VOC,      I_LTRFALC,  I_CDCMP,     I_RH,        I_FORAGEC,   
       I_MANUREC,  I_ANIMALR,  I_RSOIL,     I_DOCP,      I_LCHDOC,  
       I_ERDPOC,   I_NEP,      I_CO2DISS,   I_LCHCO2,    I_HCO3P,   
       I_RHCO3P,   I_LCHHCO3,  I_LCHALK,   
       
       I_CNVRTC,   I_VCNVRTC,  I_SCNVRTC,   I_SLASHC,   I_CFLX,     
       I_AGSTUBC,  I_AGFPRDC,  I_PRDF10C,   I_PRDF100C, I_TOTFPRDC, 
       I_FRESIDC,  I_AGPRDFC,  I_PRD10FC,   I_PRD100FC, I_TOTPRDFC, 
       I_RESIDFC,  I_NCE,      I_NECB,

       I_AGINGPP,  I_NATINGPP, I_AGGPP,     I_NATGPP,   I_AGINNPP,
       I_NATINNPP, I_AGNPP,    I_NATNPP,    I_AGGPR,    I_NATGPR,
       I_AGRVMNT,  I_NATRVMNT, I_AGRVGRW,   I_NATRVGRW, I_AGLTRC,
       I_NATLTRC,

       I_VEGN,     I_STRN,     I_STON,      I_SOLN,     I_NSOLN,    
       I_DON,      I_TSOLN,    I_AVLN,      I_NH4,      I_NO3,
       I_CROPN,    I_NATVEGN,  I_CSTRN,     I_NATSTRN,  I_CSTON,    
       I_NATSTON,  I_AGPRDN,   I_PROD10N,   I_PROD100N, I_TOTPRDN,  
       I_RESIDN,

       I_NINP,     I_TOTNDEP,   I_NH4DEP,   I_NO3DEP,   I_FIRENDEP,
       I_BNFIX,    I_SNFIX,     I_ANFIX,    I_INNUP,    I_INNH4UP,  
       I_INNO3UP,  I_VNUP,      I_VNH4UP,   I_VNO3UP,   I_VSUP,     
       I_VLUP,     I_VNMBL,     I_VNRSRB,   I_LTRFALN,  I_NDCMP,    
       I_DONP,     I_GMIN,      I_NH4IMM,   I_NO3IMM,   I_NIMM,     
       I_NMIN,     I_AIMMNH4,   I_AMMN,     I_AIMMNO3,  I_NTRF,     
       I_NO3P,     I_NOP,       I_N2OP,     I_N2P,      I_DNTRF,    
       I_FORAGEN,  I_MANUREN,   I_URINE,    I_NLST,     I_NH3FLX,    
       I_NOFLX,    I_N2OFLX,    I_N2FLX,    I_LCHNO3,   I_LCHDON,    
       I_ERDPON,   I_NENB,
      
       I_CNVRTN,   I_VCNVRTN,  I_SCNVRTN,   I_SLASHN,   I_NRETNT,   
       I_NVRTNT,   I_NSRTNT,   I_AGFRTN,    I_AGSTUBN,  I_AGFPRDN,  
       I_PRDF10N,  I_PRDF100N, I_TOTFPRDN,  I_FRESIDN,  I_AGPRDFN,  
       I_PRD10FN,  I_PRD100FN, I_TOTPRDFN,  I_RESIDFN,
      
       I_AGSNFX,   I_NATSNFX,  I_AGINNUP,   I_NATINNUP, I_AINNH4UP,
       I_NINNH4UP, I_AINNO3UP, I_NINNO3UP,  I_AGVNUP,   I_NATVNUP,
       I_AGVNH4UP, I_NVNH4UP,  I_AGVNO3UP,  I_NVNO3UP,  I_AGVSUP,
       I_NATVSUP,  I_AGVLUP,   I_NATVLUP,   I_AGVNMBL,  I_NATVNMBL,
       I_AGVNRSRB, I_NVNRSRB,  I_AGLTRN,    I_NATLTRN,

       I_UNRMLF,   I_LEAF,     I_LAI,       I_FPC,

       I_CROPULF,  I_NATULF,   I_CROPLEAF,  I_NATLEAF, I_CROPLAI,
       I_NATLAI,   I_CROPFPC,  I_NATFPC,

       I_AVLW,     I_SM,       I_VSM,       I_PCTP,     I_SNWPCK,
       I_RGRW,     I_SGRW,

       I_SNWINF,   I_AGIRRIG,  I_PET,       I_INEET,    I_EET,      
       I_RPERC,     I_SPERC,   I_RRUN,      I_SRUN,     I_WYLD,

       I_TSOIL,    I_DST0,     I_DST5,      I_DST10,    I_DST20,
       I_DST50,    I_DST100,   I_DST200,    I_FRONTD,   I_THAWBE,
       I_THAWEND,  I_THAWPCT,  I_ACTLAYER,
     }; 

/* *************************************************************
		 Public Function Declarations
************************************************************* */

     void atmswritemiss( ofstream fout[NUMATMS],
                         const vector<string>& predname,
                         const int& pdyr,
                         const int& atmspred,
                         const double value );

     void atmswritepred( ofstream fout[NUMATMS],
                         const vector<string>& predname,
                         const int& atmspred );

     int coregerr( ofstream& rflog1,
                   const string& varname1,
                   const double& col1,
		   const double& row1,
                   const string& varname2,
                   const double& col2,
		   const double& row2 );

     int equilibrateTEM( const int& pichrt,
                         const double& ptol, 
                         ofstream& rflog1 );

     void getTEMCohortState( const int& pichrt,
                             const int& pdm );

     void initializeCohortTEMState( const int& pichrt );

     void outputTEMmonth( const int& pdm );

     void readBinaryCohortState( ifstream& ifstate,
                                 const int& pichrt );

     void readCohortState( ifstream& ifstate,
                           const int& pichrt );
     
     void saveTEMCohortState( const int& pichrt );

     void setCohortTEMState( const ElmntCohort60& firstchrt,
                             ElmntCohort60& targetchrt );
     
     int setGIStopography( ofstream& flog1,
                           int& ftlerr,
                           FILE* fstxt,
                           FILE*felev );
          
     void setTEMequilState( ofstream& rflog1,
                            const int& equil,
                            const int& totsptime,
                            const int& pichrt );

     void setTEMmiss( const int& pdyr,
                      const int& equil,
                      const int& totsptime,
                      const int& pichrt );

     void temwritepred( ofstream fout[NUMTEM],
                        const vector<string>& predname,
                        const int& pdyr,
                        const int& pichrt,
                        const int& ntempred );

     void updateTEMmonth( ofstream& rflog1,
                          const int& equil,
                          const int& totsptime,
                          const int& outyr,
                          const int& pdm,
                          const int& pichrt );

     void writeBinaryCohortState( ofstream& ofstate,
                                  const int& pichrt );

     void writeCohortState( ofstream& ofstate,
                            const int& pichrt );

/* *************************************************************
		 Public Variables
************************************************************* */

     int atmstotyr[MAXRTIME];
     
     // Mean annual air temperature
     double avetair;

     long carea;

     double climate[NUMATMS][CYCLE+1];
     
     TEMclm60 clm;

     ElmntCohort60 cohort[MAXCHRTS];
     
     double col;

     string contnent;
     
     int fatalerr;

     double lat;

     TEMlcluc60 lcluc;

     double lon;

     int lonlatflag;
     
     // Maximum number of cohorts in an element
     //   during the current year
     int maxcohorts;
     
     // Maximum monthly air temperature during the year
     double mxtair;

     // Maximum number of "natural" cohorts in an element
     int natcohorts;

     // Number of climate predicted variables
     int natmspred;
     
     // Number of TEM predicted variables
     int ntempred;

     double output[NUMTEM][CYCLE];
     
     int outyr;

     // Maximum number of cohorts in an element
     //   during the previous year
     int prvmxcohrts;

     string region;
     
     double row;

     long subarea;

     TTEM60 tem;

     int totpred;

     int ttotyr[MAXRTIME];

     int wrtyr;

     // Annual precipitation during the year
     double yrprec;
     
     int year;

/* *************************************************************
		 Private Function Declarations
************************************************************* */

  private:

     int temgisqc( const long& subarea,
                   const double& pctsilt,
                   const double& pctclay,
                   const int& cmnt,
                   const double& elev,
                   const double& nirr,
                   const double& par,
		   const double& tair,
                   const double& mxtair,
                   const double& avtair,
                   const double& yrprec,
                   const double& rain,
                   const double& snowfall,
                   const double& co2,
                   const double& aot40,
                   const InorgN60& ndep );

     int transqc( const int& pcmnt,
                  int& maxyears,
                  int& totyr,
                  double plantc[CYCLE] );

};

#endif
