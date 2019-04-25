/* *************************************************************
****************************************************************
HUMANACT606CNOFERT2000.CPP - describes human disturbances to 
  natural ecosystems where nitrogen fertilizers are assumed to
  be added to croplands from 1950 to 2000, but then no fertilzers
  are applied to croplands after year 2000.
  
Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the file license.txt at 
<https://github.com/MBL-TEM/TEM6.0.6/>   
  
****************************************************************
************************************************************* */

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
  using std::pow;
    
#include<string>
  
  using std::string;

#include "humnact606cNoFert2000.h"


/* *************************************************************
************************************************************* */

Humanact60::Humanact60()
{

  int i;
  int dcmnt;
  int dm;
  c2n = 54.29;

  state = 0;
  prvstate = 0;

  massbalflg = 1;
  fertflag = 0;
  irrgflag = 0;
  frostflag = 0;
  
  mez = CROPVEG - 1;

  productYear = 0;

  prevPROD1.carbon = ZERO;
  prevPROD1.nitrogen = ZERO;

  prevPROD10.carbon = ZERO;
  prevPROD10.nitrogen = ZERO;

  prevPROD100.carbon = ZERO;
  prevPROD100.nitrogen = ZERO;

  prevCropResidue.carbon = ZERO;
  prevCropResidue.nitrogen = ZERO;

  cropResidue.carbon = ZERO;
  cropResidue.nitrogen = ZERO;

  for( dm = 0; dm < CYCLE; ++dm )
  {  
    initPROD1[dm].carbon = ZERO;
    initPROD1[dm].nitrogen = ZERO;
  }

  for( i = 0; i < 10; ++i )
  {
    initPROD10[i].carbon = ZERO;
    initPROD10[i].nitrogen = ZERO;
  }
  
  for( i = 0; i < 100; ++i )
  {
    initPROD100[i].carbon = ZERO;
    initPROD100[i].nitrogen = ZERO;
  }

  // Initialize parameters to missing value

  prod10par = MISSING;
  prod100par = MISSING;
  sconvert = MISSING;
  slashpar = MISSING;
  vconvert = MISSING;
  vrespar = MISSING;

  for( dcmnt = 0; dcmnt < MAXCMNT; ++dcmnt )
  {
    cropseedC[dcmnt] = MISSING;
    cropseedSTRN[dcmnt] = MISSING;
    cropseedSTON[dcmnt] = MISSING;
    harvstC[dcmnt] = MISSING;
    harvstN[dcmnt] = MISSING;
    nsretconv[dcmnt] = MISSING;
    nvretconv[dcmnt] = MISSING;
    residueC[dcmnt] = MISSING;
    residueN[dcmnt] = MISSING;
    tillfactor[dcmnt] = MISSING;
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::conversion( const int& pdcmnt,
                             const double& vegc,
                             const double& vstrn,
                             const double& vston,
                             const double& soilc,
                             const double& soiln )
{
  // Assume annual conversion fluxes are partitioned equally 
  //   across each of 12 months - determine monthly fluxes
  
  slash.carbon = slashpar * vegc / (double) CYCLE;
  slash.nitrogen = slashpar  * (vstrn + vston) / (double) CYCLE;

  vconvrtflx.carbon = (vconvert * vegc) / (double) CYCLE;
  sconvrtflx.carbon =  (sconvert * soilc)/ (double) CYCLE;

  convrtflx.carbon = vconvrtflx.carbon + sconvrtflx.carbon;

  vconvrtflx.nitrogen = ((1.0 - nvretconv[pdcmnt]) 
                        * vconvert 
                        * (vstrn + vston))
                        / (double) CYCLE;
                                
  sconvrtflx.nitrogen = ((1.0 - nsretconv[pdcmnt]) 
                        * sconvert * soiln)
                        / (double) CYCLE;
                                
  convrtflx.nitrogen = vconvrtflx.nitrogen + sconvrtflx.nitrogen;
                               
  nvretent.total = (nvretconv[pdcmnt] * vconvert * (vstrn + vston)) 
                    / (double) CYCLE;

  nvretent.no3 = 0.5 * nvretent.total;
  nvretent.nh4 = nvretent.total - nvretent.no3;

  nsretent.total = (nsretconv[pdcmnt] * sconvert * soiln) 
                    / (double) CYCLE;

  nsretent.no3 = 0.5 * nsretent.total;
  nsretent.nh4 = nsretent.total - nsretent.no3;
  
  nretent.total = nvretent.total + nsretent.total;
  nretent.nh4 = nvretent.nh4 + nsretent.nh4;
  nretent.no3 = nvretent.no3 + nsretent.no3;
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::createWoodProducts( const int& pdyr,
                                     const double& vegc,
                                     const double& vstrn,
                                     const double& vston )
{
  int i;

  formPROD10.carbon  = prod10par * vegc;
  formPROD10.nitrogen  = prod10par * (vstrn + vston);
  formPROD100.carbon = prod100par * vegc;
  formPROD100.nitrogen = prod100par * (vstrn + vston);

  if( pdyr < productYear )
  {
    productYear += pdyr;
  }
  else { productYear = pdyr; }

  i = productYear%10;
  initPROD10[i].carbon = formPROD10.carbon;
  initPROD10[i].nitrogen = formPROD10.nitrogen;

  i = productYear%100;
  initPROD100[i].carbon = formPROD100.carbon;
  initPROD100[i].nitrogen = formPROD100.nitrogen;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::decayProducts( void )
{

  int i;
  int dm;
  double yrtrash;

  PROD1decay.carbon  = ZERO;
  PROD1decay.nitrogen  = ZERO;

  for( dm = 0; dm < CYCLE; ++dm )
  {
    PROD1decay.carbon += initPROD1[dm].carbon / (double) CYCLE;

    PROD1decay.nitrogen += initPROD1[dm].nitrogen 
                          / (double) CYCLE;
  }


  PROD10decay.carbon  = ZERO;
  PROD10decay.nitrogen  = ZERO;


  for( i = 0; i < 10; ++i )
  {
    yrtrash = initPROD10[i].carbon * 0.10 / (double) CYCLE;
    PROD10decay.carbon += yrtrash;
    yrtrash = initPROD10[i].nitrogen * 0.10 / (double) CYCLE;
    PROD10decay.nitrogen += yrtrash;
  }


  PROD100decay.carbon = ZERO;
  PROD100decay.nitrogen = ZERO;
  
  for( i = 0; i < 100; ++i )
  {
    yrtrash = initPROD100[i].carbon * 0.01 / (double) CYCLE;
    PROD100decay.carbon += yrtrash;
    yrtrash = initPROD100[i].nitrogen * 0.01 / (double) CYCLE;
    PROD100decay.nitrogen += yrtrash;
  }

  TOTPRODdecay.carbon = PROD1decay.carbon
                        + PROD10decay.carbon
                        + PROD100decay.carbon;

  TOTPRODdecay.nitrogen = PROD1decay.nitrogen
                          + PROD10decay.nitrogen
                          + PROD100decay.nitrogen;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::frostDamage( const double& vegc,
                              const double& vstrn, 
                              const double& vston )
{ 
  frostflag = 1;
  
  // Assume all crop biomass becomes stubble
  
  stubble.carbon = vegc;
  stubble.nitrogen = (vstrn+vston);

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::grazing( const double& vegc,
                          const double& strn )
{
  // Assume 5 percent of vegetation biomass is consumed each
  //   month

  forage.carbon = vegc * 0.05;
  forage.nitrogen = strn * 0.05;

  // Assume 83 percent of forage carbon is respired and 50
  //   percent of nitrogen is mineralized in livestock
  //   metabolism

  animalresp = forage.carbon * 0.83;
  urine = forage.nitrogen * 0.50;

  // Assume remaineder of forage is returned to soil as manure

  manure.carbon = forage.carbon * 0.17;
  manure.nitrogen = forage.nitrogen * 0.50;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::harvest( const int& pdm,
                          const double& vegc,
                          const double& vstrn, 
                          const double& vston )
{
  double initresidueC;
  double initresidueN;

  // Determine crop production

  cropprod.carbon = vegc * harvstC[cmnt];

  if( cropprod.carbon < ZERO )
  {
    cropprod.carbon = ZERO;
  }

  cropprod.nitrogen = (vstrn+vston) * harvstN[cmnt];

  if( cropprod.nitrogen < ZERO )
  {
    cropprod.nitrogen = ZERO;
  }

  initPROD1[pdm].carbon  = cropprod.carbon;
  initPROD1[pdm].nitrogen  = cropprod.nitrogen;


  // Determine amount of carbon and nitrogen left
  // in crop residue

   initresidueC = vegc - cropprod.carbon;

  if( initresidueC < ZERO )
  {
    initresidueC = ZERO;
  }

  initresidueN = (vstrn+vston) - cropprod.nitrogen;

  if( initresidueN < ZERO )
  {
    initresidueN = ZERO;
  }

  // Determine amount of carbon and nitrogen in
  // crop residue that will be lost from ecosystem

  formCropResidue.carbon = initresidueC
                           * residueC[cmnt];

  formCropResidue.nitrogen = initresidueN
                             * residueN[cmnt];


  // Determine amount of stubble carbon and nitrogen
  // added to soils

  stubble.carbon = initresidueC
                   * ( 1.000000 - residueC[cmnt]);

  stubble.nitrogen = initresidueN
                     * ( 1.000000 - residueN[cmnt]);

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::resetMonthlyDisturbFluxes( void )
{
  // Initialize disturbance carbon fluxes to zero

  convrtflx.carbon = ZERO;
  vconvrtflx.carbon = ZERO;
  sconvrtflx.carbon = ZERO;
  slash.carbon = ZERO;

  // Initialize nitrogen fluxes during conversion to zero

  convrtflx.nitrogen = ZERO;
  vconvrtflx.nitrogen = ZERO;
  sconvrtflx.nitrogen = ZERO;
  slash.nitrogen = ZERO;

  nretent.total = ZERO;
  nretent.nh4 = ZERO;
  nretent.no3 = ZERO;

  nvretent.total = ZERO;
  nvretent.nh4 = ZERO;
  nvretent.no3 = ZERO;

  nsretent.total = ZERO;
  nsretent.nh4 = ZERO;
  nsretent.no3 = ZERO;

  cropResidueFlux.carbon = ZERO;
  cropResidueFlux.nitrogen = ZERO;  
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::resetMonthlyFluxes( void )
{
  // Reset monthly fluxes to zero
  
  fertn = ZERO;
  
  irrigate = ZERO;

  // Initialize stubble to zero
  
  stubble.carbon = ZERO;
  stubble.nitrogen = ZERO;

  cflux = ZERO;

  
  // Initialize carbon fluxes related to formation and 
  //   decomposition of products and crop residue to zero

  cropprod.carbon = ZERO;
  cropprod.nitrogen = ZERO;

  formCropResidue.carbon = ZERO;
  formCropResidue.nitrogen = ZERO;

  PROD1decay.carbon = ZERO;
  PROD1decay.nitrogen = ZERO;

  formPROD10.carbon = ZERO;
  formPROD10.nitrogen = ZERO;

  PROD10decay.carbon = ZERO;
  PROD10decay.nitrogen = ZERO;

  formPROD100.carbon = ZERO;
  formPROD100.nitrogen = ZERO;

  PROD100decay.carbon = ZERO;
  PROD100decay.nitrogen = ZERO;

  formTOTPROD.carbon = ZERO;
  formTOTPROD.nitrogen = ZERO;

  TOTPRODdecay.carbon = ZERO;
  TOTPRODdecay.nitrogen = ZERO;

	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::resetPROD( void )
{
  int i;
  int dm;

  prevPROD1.carbon = ZERO;
  prevPROD1.nitrogen = ZERO;

  prevPROD10.carbon = ZERO;
  prevPROD10.nitrogen = ZERO;

  prevPROD100.carbon = ZERO;
  prevPROD100.nitrogen = ZERO;

  prevCropResidue.carbon = ZERO;
  prevCropResidue.nitrogen = ZERO;

  cropResidue.carbon = ZERO;
  cropResidue.nitrogen = ZERO;
 
  for( dm = 0; dm < CYCLE; ++dm )
  {
    initPROD1[dm].carbon = ZERO;
    initPROD1[dm].nitrogen = ZERO;
  }

  for( i = 0; i < 10; ++i )
  {
    initPROD10[i].carbon = ZERO;
    initPROD10[i].nitrogen = ZERO;
  }
  for( i = 0; i < 100; ++i )
  {
    initPROD100[i].carbon = ZERO;
    initPROD100[i].nitrogen = ZERO;
  }

  PROD1.carbon = ZERO;
  PROD1.nitrogen = ZERO;

  PROD10.carbon = ZERO;
  PROD10.nitrogen = ZERO;

  PROD100.carbon = ZERO;
  PROD100.nitrogen = ZERO;

  TOTPROD.carbon = ZERO;
  TOTPROD.nitrogen = ZERO;

  PROD1decay.carbon = ZERO;
  PROD1decay.nitrogen = ZERO;

  formPROD10.carbon  = ZERO;
  formPROD10.nitrogen  = ZERO;

  PROD10decay.carbon  = ZERO;
  PROD10decay.nitrogen  = ZERO;

  formPROD100.carbon = ZERO;
  formPROD100.nitrogen = ZERO;

  PROD100decay.carbon = ZERO;
  PROD100decay.nitrogen = ZERO;

  formTOTPROD.carbon = ZERO;
  formTOTPROD.nitrogen = ZERO;

  TOTPRODdecay.carbon = ZERO;
  TOTPRODdecay.nitrogen = ZERO;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::resetYrFluxes( void )
{
  // Reset annual fluxes and summary variables to zero

  yrfertn = ZERO;

  yrirrig = ZERO;

  yrstubC = ZERO;
  yrstubN = ZERO;

  // Annual carbon fluxes from agricultural conversion

  yrconvrtC = ZERO;
  yrvconvrtC = ZERO;
  yrsconvrtC = ZERO;
  yrslashC = ZERO;
  yrcflux = ZERO;

 // Annual nitrogen fluxes from agricultural conversion

  yrconvrtN = ZERO;
  yrvconvrtN = ZERO;
  yrsconvrtN = ZERO;
  yrslashN = ZERO;

  yrnrent.total = ZERO;
  yrnvrent.nh4 = ZERO;
  yrnrent.no3 = ZERO;

  yrnvrent.total = ZERO;
  yrnvrent.nh4 = ZERO;
  yrnvrent.no3 = ZERO;

  yrnsrent.total = ZERO;
  yrnsrent.nh4 = ZERO;
  yrnsrent.no3 = ZERO;

  // Annual carbon and nitrogen fluxes in the formation of 
  //   agricultural products

  yrformPROD1C   = ZERO;
  yrformPROD1N   = ZERO;


 // Annual carbon and nitrogen flux from crop residue formation

  yrformResidueC = ZERO;
  yrformResidueN = ZERO;

  // Annual carbon and nitrogen fluxes in the decomposition of 
  //   agricultural products

  yrdecayPROD1C   = ZERO;
  yrdecayPROD1N   = ZERO;

 // Annual carbon and nitrogen fluxes from burning crop residue

  yrfluxResidueC = ZERO;
  yrfluxResidueN = ZERO;

  // Annual carbon and nitrogen fluxes resulting from 
  //   formation of 10-year wood products

  yrformPROD10C  = ZERO;
  yrformPROD10N  = ZERO;

  // Annual carbon and nitrogen fluxes resulting from 
  //   decomposition of 10-year wood products

  yrdecayPROD10C  = ZERO;
  yrdecayPROD10N  = ZERO;

  // Annual carbon and nitrogen fluxes resulting from 
  //   formation of 100-year wood products

  yrformPROD100C = ZERO;
  yrformPROD100N = ZERO;

  // Annual carbon and nitrogen fluxes resulting from 
  //   decomposition of 100-year wood products

  yrdecayPROD100C = ZERO;
  yrdecayPROD100N = ZERO;

  // Annual carbon and nitrogen fluxes resulting from 
  //   formation of all agricultural and wood products

  yrformTOTPRODC = ZERO;
  yrformTOTPRODN = ZERO;

  // Annual carbon and nitrogen fluxes resulting from 
  //   decomposition of all agricultural and wood products

  yrdecayTOTPRODC = ZERO;
  yrdecayTOTPRODN = ZERO;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::setAgricFlags( ofstream& rflog1 )
{

  cout << "Are agricultural soils tilled?" << endl;
  cout << "Enter 0 for no:" << endl;
  cout << "Enter 1 for yes:" << endl;
  
  cin >> tillflag;

  rflog1 << "Are agricultural soils tilled?" << endl;
  rflog1 << "Enter 0 for no:" << endl;
  rflog1 << "Enter 1 for yes:" << endl;
  rflog1 << tillflag << endl << endl;

};

/* *************************************************************
************************************************************* */


/* **************************************************************
************************************************************** */

void Humanact60::setFireNDEP( void )
{
  double newndep;
  double frftemp;

  // Determine firendep from total nitrogen volatilized during 
  //   fire for reintroduction to the soil (Note: 
  //   vconvrtflx.nitrogen and sconvrtflx.nitrogen are monthly
  //   fluxes that occur over a time period of a year
  
  newndep = vconvrtflx.nitrogen + sconvrtflx.nitrogen;

  
  // Determine the potential number of years until next fire 
  //   event (i.e. Fire Return Interval or FRI)
  
  frftemp = FRI;

  if( frftemp > MAXFRI ) { frftemp = MAXFRI; }

  
  // Assume that (1/FRI) of newndep is deposited each month
  
  firendep.total = newndep / (frftemp-1);

  firendep.no3 = 0.5 * firendep.total;
  firendep.nh4 = firendep.total - firendep.no3;  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::setNoCrops( const int& pdm )
{
  cropprod.carbon = ZERO;
  cropprod.nitrogen = ZERO;

  formCropResidue.carbon = ZERO;
  formCropResidue.nitrogen = ZERO;

  if( frostflag != 1 )
  {
    stubble.carbon = ZERO;
    stubble.nitrogen = ZERO;
  }
  
  frostflag = 0;
  
  initPROD1[pdm].carbon = ZERO;
  initPROD1[pdm].nitrogen = ZERO;
  
  	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::setNoGrazing( void )
{
  forage.carbon = ZERO;
  forage.nitrogen = ZERO;

  manure.carbon = ZERO;
  manure.nitrogen = ZERO;

  animalresp = ZERO;

  urine = ZERO;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::setNoWoodProducts( const int& pdyr )
{
  int i;
  	
  formPROD10.carbon = ZERO;
  formPROD10.nitrogen = ZERO;

  formPROD100.carbon = ZERO;
  formPROD100.nitrogen = ZERO;
  
  if( pdyr < productYear )
  {
    productYear += pdyr;
  }
  else { productYear = pdyr; }

  i = productYear%10;
  initPROD10[i].carbon = ZERO;
  initPROD10[i].nitrogen = ZERO;

  i = productYear%100;
  initPROD100[i].carbon = ZERO;
  initPROD100[i].nitrogen = ZERO;
	
};


/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::updateCropResidue( void )
{

  cropResidue.carbon = prevCropResidue.carbon
                       + formCropResidue.carbon
                       - cropResidueFlux.carbon;

  cropResidue.nitrogen = prevCropResidue.nitrogen
                         + formCropResidue.nitrogen
                         - cropResidueFlux.nitrogen;

};
/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::updateCropResidueFluxes( void )
{
  int kdm;

  cropResidueFlux.carbon = ZERO;
  cropResidueFlux.nitrogen = ZERO;

  if ( 1 == state )
  {
    for( kdm = 0; kdm < CYCLE; ++kdm )
    {
      if( harvstC[cmnt] > 0.000001 )
      {
        cropResidueFlux.carbon += initPROD1[kdm].carbon
                                  * (1.000000 - harvstC[cmnt])
                                  / harvstC[cmnt]
                                  * residueC[cmnt]
                                  / (double) CYCLE;
      }
      else { cropResidueFlux.carbon = ZERO; }

      if( harvstN[cmnt] > 0.000001 )
      {
        cropResidueFlux.nitrogen += initPROD1[kdm].nitrogen
                                    * (1.000000 - harvstN[cmnt])
                                    / harvstN[cmnt]
                                    * residueN[cmnt]
                                    / (double) CYCLE;
      }
      else { cropResidueFlux.nitrogen = ZERO; }
    }
  }

};
/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::updateProducts( void )
{
  int i;

  // Carbon in Products

  PROD1.carbon = prevPROD1.carbon 
                 + cropprod.carbon 
                 - PROD1decay.carbon;
  
  if( PROD1.carbon < 0.1 )
  {
    PROD1.carbon = ZERO;

    for(i = 0; i < CYCLE; ++i )
    {
      initPROD1[i].carbon = ZERO;
      initPROD1[i].nitrogen = ZERO;
    }
  }

  PROD10.carbon = prevPROD10.carbon
                  + formPROD10.carbon
                  - PROD10decay.carbon;
  
  if( PROD10.carbon < 0.1 )
  {
    PROD10.carbon = ZERO;

    for(i = 0; i < 10; ++i )
    {
      initPROD10[i].carbon = ZERO;
      initPROD10[i].nitrogen = ZERO;
    }
  }

  PROD100.carbon = prevPROD100.carbon
                   + formPROD100.carbon
                   - PROD100decay.carbon;
  
  if( PROD100.carbon < 0.1 )
  {
    PROD100.carbon = ZERO;
    for(i = 0; i < 100; ++i )
    {
      initPROD100[i].carbon = ZERO;
      initPROD100[i].nitrogen = ZERO;
    }
  }

  TOTPROD.carbon = PROD1.carbon
                   + PROD10.carbon
                   + PROD100.carbon;

  // Nitrogen in Products

  PROD1.nitrogen = prevPROD1.nitrogen
                   + cropprod.nitrogen
                   - PROD1decay.nitrogen;
  
  if( PROD1.nitrogen < 0.000001 )
  {
    PROD1.nitrogen = ZERO;
  }

  PROD10.nitrogen = prevPROD10.nitrogen
                    + formPROD10.nitrogen
                    - PROD10decay.nitrogen;
  
  if( PROD10.nitrogen < 0.000001 )
  {
    PROD10.nitrogen = ZERO;
  }

  PROD100.nitrogen = prevPROD100.nitrogen
                     + formPROD100.nitrogen
                     - PROD100decay.nitrogen;
  
  if( PROD100.nitrogen < 0.000001 )
  {
    PROD100.nitrogen = ZERO;
  }

  TOTPROD.nitrogen = PROD1.nitrogen
                     + PROD10.nitrogen
                     + PROD100.nitrogen;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Humanact60::updateTotalProductFormation( void )
{
  // Carbon in Total Product Formation

  formTOTPROD.carbon = cropprod.carbon
                       + formPROD10.carbon
                       + formPROD100.carbon;

  // Nitrogen in Total Product Formation

  formTOTPROD.nitrogen = cropprod.nitrogen
                         + formPROD10.nitrogen
                         + formPROD100.nitrogen;


};

