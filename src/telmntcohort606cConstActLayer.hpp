/* *************************************************************
TELMNTCOHORT606CCONSTACTLAYER.HPP - Container class to hold land 
  cover cohort characteristics.
  
Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
 
************************************************************* */

#ifndef ELMNTCOHORT606_H
#define ELMNTCOHORT606_H

#include "temconsts606.hpp"
#include "bioms423.hpp"
#include "inorgn60.hpp"

struct ElmntCohort60
{      
  // Index for agricultural crop type used for
  //   parameterization
  int agcmnt;

  // Number of growing degree days in croplands
  double aggrowdd;

  // Current value of decomposition parameter in croplands 
  double agkd;

  // Index to indicate whether cohort was in
  //   agriculture during the previous year
  int agprvstate;

  // Index to indicate whether cohort is in
  //   agriculture during the current year
  int agstate;

  double c2n;

  // Area covered by cohort (square kilometers)
  //   during current year 
  long chrtarea;

  // Index for vegetation community type used for
  //   parameterization
  int cmnt;

  double cneven;

  // Container for estimates of active layer depth when active 
  //   layer is held constant
  double constActLayer[CYCLE];
  
  // Carbon and nitrogen flux lost during conversion of land to
  //    agriculture
  Biomass convrtflx;

  double cropprveetmx;
  double cropprvleafmx;
  double cropprvpetmx;

  Biomass cropResidue;

  double croptopt;

  // Index for current vegetation type
  int currentveg;

  // Counter of months since disturbance
  int distmnthcnt;

  // Flag to indicate that a disturbance has occurred
  //   in a particular year.  Different values represent
  //   different types of disturbances:
  //   0 = no disturbance
  //   1 = sustained disturbed state 
  //         (e.g. conversion to agriculture or urban state)
  //   2 = timber harvest
  //   3 = fire
  int disturbflag;
     
  // Month in which disturbance occurred
  // (e.g. 1 = January, ...., 12 = December)
  int disturbmonth;

  // Monthly soil temperature at 10 cm
  double dst10[CYCLE];

  // Maximum monthly estimated evapotranspiration
  //   during the current year
  double eetmx;

  // Index to indicate if crops are fertilized (= 1)
  //   or not (= 0)
  int fertflag;

  // Counter of months since fire disturbance
  int firemnthcnt;

  // Monthly reintroduction of N volatilized in fires
  //   back to the soil (as N deposition)
  InorgN60 firendep;

  Biomass formPROD10;
  Biomass formPROD100;

  double fprevozone;

  // Fire return frequency
  int FRI;

  Biomass initPROD1[CYCLE];
  Biomass initPROD10[10];
  Biomass initPROD100[100];

 // Index to indicate if crops are irrigated (= 1)
  //   or not (= 0)
  int irrgflag;

  // Current value of decomposition parameter in 
  //   natural ecosystems
  double kd;

  double natprveetmx;
  double natprvleafmx;
  double natprvpetmx;
  double natseedC;
  double natseedSTRN;
  double natseedSTON;
  double natsoil;
  double nattopt;
  double natyreet;
  double natyrpet;

  double newleafmx;

  double newtopt;

  // "Non-reactive soil organic carbon
  double nonsolc;

  // "Non-reactive soil organic nitrogen
  double nonsoln;

  InorgN60 nretent;
  InorgN60 nsretent;
  InorgN60 nvretent;

  // Maximum monthly potential evapotranspiration 
  //   during current year
  double petmx;

  int potveg;

  // Air temperature that occurred 2 months ago
  double prev2tair;
  
  // Atmospheric CO2 concentration during the previous month
  double prevco2;

  Biomass prevCropResidue;

  // Soil temperature at 10cm during the previous month
  double prevdst10;

  Biomass prevPROD1;
  Biomass prevPROD10;
  Biomass prevPROD100;

  // Snowpack during the previous month
  double prevspack;

  // Air temperature of the previous month
  double prevtair;

  // Unnormalized relative leaf area of the previous month
  double prevunrmleaf;

  // Value of y[] during previous time step
  double prevy[MAXSTATE];

  double prod10par;

  double prod100par;

  int productYear;

  // Crop net primary production during the previous month
  double prvcropnpp;

  // Maximum monthly estimated evapotranspiration
  //   during the previous year
  double prveetmx;

  // Maximum relative leaf area of cohort
  //   during the previous year 
  double prvleafmx;

  // Maximum monthly potential evapotranspiration
  //   during the previous year
  double prvpetmx;

  int qc;

  double sconvert;

  Biomass sconvrtflx;

  Biomass slash;

  double slashpar;

  // Source cohort for current cohort
  int srcCohort;

  // Age of cohort
  int standage;

  double STMdst0;

  double STMdst5;

  double STMdst10;

  double STMdst20;

  double STMdst50;

  double STMdst100;

  double STMdst200;

  double STMdx9[MAXNODES];

  double STMfrontd;

  double STMfrontd2;

  int STMis9;

  double STMsmass9;

  double STMt9[MAXNODES];

  double STMthawbegin1;

  double STMthawbegin2;

  double STMthawend1;

  double STMthawend2;

  double STMtsoil;

  double STMwater9[MAXNODES];

  double STMweight9[MAXSNODES];

  double STMx9[MAXNODES];

  double STMxfa9[MAXNODES];

  double STMxfb9[MAXNODES];

  int subtype;

  int tillflag;

  double topt;

  int tqc;

  double vconvert;

  Biomass vconvrtflx;

  double vrespar;
  
  double wfpsoff;

  double y[MAXSTATE];
  
  double yragstubC;
  
  double yragstubN;

  double yrammonvol;
  
  double yrcflux;
  
  double yrconvrtC;
  
  double yrconvrtN;
  
  double yrdecayPROD1C;
  
  double yrdecayPROD10C;
  
  double yrdecayPROD100C;

  double yrdecayPROD1N;
  
  double yrdecayPROD10N;
  
  double yrdecayPROD100N;
  
  double yrdecayTOTPRODC;

  double yrdecayTOTPRODN;
 
  double yrdecompC;

  double yrdecompN;
  
  double yrdenitrif;

  double yrDOCleach;
  
  double yrDOCprod;

  double yrDONleach;
  
  double yrDONprod;
  
  double yreet;
  
  double yrfertn;
  
  double yrfluxResidueC;
  
  double yrfluxResidueN;

  double yrformPROD1C;
  
  double yrformPROD10C;
  
  double yrformPROD100C;

  double yrformPROD1N;
  
  double yrformPROD10N;
  
  double yrformPROD100N;
  
  double yrformResidueC;
  
  double yrformResidueN;

  double yrformTOTPRODC;

  double yrformTOTPRODN;

  double yrfpc;

  double yrgmin;
  
  double yrgpp;
  
  double yrgpr;
  
  double yrh2oyld;
  
  double yrimmob;

  double yrimmobabN;

  double yrimmobNH4;
  
  double yrineet;
  
  double yringpp;
  
  double yrinnpp;
  
  double yrinnup;

  double yrinnupNH4;

  double yrinnupNO3;
  
  double yrirrig;
  
  double yrlai;
    
  double yrleaf;

  double yrltrfalc;

  double yrltrfaln;
  
  double yrN2flx;
   
  double yrN2Oflx;

  double yrNH3flx;

  double yrNOflx;
   
  double yrN2prd;
   
  double yrN2Oprd;
 
  double yrnce;

  double yrndep;
  
  double yrndepNH4;
  
  double yrndepNO3;
  
  double yrnecb;  

  double yrnenb;  

  double yrnep;
  
  double yrNfixBiol;

  double yrNfixAsymb;

  double yrNfixSymb;
  
  double yrNH4leach;

  double yrninput;

  double yrnitrif;
  
  double yrnlost;
  
  double yrnmin;
    
  double yrNOprd;
  
  double yrNO3leach;

  double yrNO3prd;
  
  double yrnpp;
  
  InorgN60 yrnrent;
    
  InorgN60 yrnsrent;
  
  double yrnup;

  double yrnupNH4;

  double yrnupNO3;

  InorgN60 yrnvrent;
  
  double yrpet;
  
  double yrPOCerode;

  double yrPONerode;
  
  double yrrgrndh2o; 
  
  double yrrh;
    
  double yrrain;
  
  double yrrperc;
  
  double yrrrun;

  double yrsconvrtC;

  double yrsconvrtN;
  
  double yrsgrndh2o;

  double yrslashC;

  double yrslashN;
  
  double yrsnowfall;

  double yrsnowinf;

  double yrsnowpack;
  
  double yrsoilavlH2O;
  
  double yrsoilavlN;

  double yrsoilavlNH4;

  double yrsoilavlNO3;
  
  double yrsoilDOC;
  
  double yrsoilDON;

  double yrsoilmoist;
  
  double yrsoilnonorgC;
  
  double yrsoilnonorgN;
  
  double yrsoilorgC;
  
  double yrsoilorgN;

  double yrsoilpctp;
  
  double yrsoilResp;
  
  double yrsoiltotorgC;

  double yrsoiltotorgN;
  
  double yrsoilvsm;

  double yrsperc;
  
  double yrsrun;

  double yrSTMdst0;

  double yrSTMdst5;

  double yrSTMdst10;

  double yrSTMdst20;

  double yrSTMdst50;

  double yrSTMdst100;

  double yrSTMdst200;

  double yrSTMfrontd;

  double yrSTMfrontd2;

  double yrSTMthawbegin1;

  double yrSTMthawbegin2;

  double yrSTMthawend1;

  double yrSTMthawend2;

  double yrSTMtsoil;
     
  double yrthawpct;
  
  double yrtotalC;
  
  double yrunleaf;

  double yrvconvrtC;
  
  double yrvconvrtN;

  double yrvegabvgrndResp;
  
  double yrvegC;
    
  double yrveglup;

  double yrvegN;

  double yrvegnmobil;

  double yrvegnrsorb;

  double yrvegrgrowth;

  double yrvegrmaint;

  double yrvegrootResp;
  
  double yrvegstoN;
  
  double yrvegstrN;

  double yrvegsup;

};

#endif
