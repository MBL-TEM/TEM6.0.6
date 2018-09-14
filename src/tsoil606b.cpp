/* *************************************************************
****************************************************************
TSOIL606B.CPP - object describing general characteristics of soil

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

****************************************************************
************************************************************* */

#include<cstdio>

  using std::printf;

#include<iostream>

  using std::cin;
  using std::cout;
  using std::ios;
  using std::cerr;
  using std::endl;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<cstdlib>

  using std::exit;
  using std::atof;
  using std:: atoi;
  
#include<cmath>

  using std::exp;
  using std::pow;
  
#include<string>
  
  using std::string;


#include "tsoil606b.h"

/* *************************************************************
************************************************************* */

Tsoil60::Tsoil60( void ) : ProcessXML60() 
{
  int dcmnt;

  text  = -99;
  wsoil = -99;

  pctsand = MISSING;
  pctsilt = MISSING;
  pctclay = MISSING;
  psiplusc = MISSING;


  awcapmm = MISSING;
  fldcap = MISSING;
  wiltpt = MISSING;
  totpor = MISSING;

  snowpack = MISSING;
  prevspack = MISSING;

  avlh2o = MISSING;
  moist = MISSING;
  pcfc = MISSING;
  pctp = MISSING;
  vsm = MISSING;

  rgrndh2o = MISSING;
  sgrndh2o = MISSING;

  snowinf = MISSING;
  rperc = MISSING;
  sperc = MISSING;
  rrun = MISSING;
  srun = MISSING;
  h2oyld = MISSING;
    
  nonReactiveOrg.carbon = MISSING;
  nonReactiveOrg.nitrogen = MISSING;

  org.carbon = MISSING;
  org.nitrogen = MISSING;

  availn.total = MISSING;
  availn.nh4 = MISSING;
  availn.no3 = MISSING;

  abioticNimmob = MISSING;

  leachNO3 = MISSING;
  leachDOM.carbon = MISSING;
  leachDOM.nitrogen = MISSING;

  nh3flux = MISSING;
  noflux = MISSING;
  n2oflux = MISSING;
  n2flux = MISSING;

  yrsnowpack = MISSING;

  yravlh2o = MISSING;
  yrsmoist = MISSING;
  yrpctp = MISSING;
  yrvsm = MISSING;
  meanvsm = MISSING;

  yrrgrndh2o = MISSING;
  yrsgrndh2o = MISSING;

  yrsnowinf = MISSING;
  yrrperc = MISSING;
  yrsperc = MISSING;
  yrrrun = MISSING;
  yrsrun = MISSING;
  yrh2oyld = MISSING;

  yrnonorgc = MISSING;
  yrnonorgn = MISSING;

  yrorgc = MISSING;
  yrorgn = MISSING;
  yrc2n = MISSING;

  yravln.total = MISSING;
  yravln.nh4 = MISSING;
  yravln.no3 = MISSING;

  yrabNimmob = MISSING;

  ninput = MISSING;
  yrnin = MISSING;

  nlost = MISSING;
  yrnlost = MISSING;

  yrlchNO3 = MISSING;
  yrlchDOM.carbon = MISSING;
  yrlchDOM.nitrogen = MISSING;

  yrnoflx = MISSING;
  yrn2oflx = MISSING;
  yrn2flx = MISSING;

  fldcapa = MISSING;
  fldcapb = MISSING;
  
  pctpora = MISSING;
  pctporb = MISSING;

  for( dcmnt = 0; dcmnt < MAXCMNT; ++dcmnt )
  {
     DOCpar[dcmnt] = MISSING;
     DONparcut[dcmnt] = MISSING;
     DONpar1a[dcmnt] = MISSING;
     DONpar1b[dcmnt] = MISSING;
     DONpar2a[dcmnt] = MISSING;
     DONpar2b[dcmnt] = MISSING;
     lchDOMpar[dcmnt] = MISSING;
     lchNO3parcut[dcmnt] = MISSING;
     lchNO3par1a[dcmnt] = MISSING;
     lchNO3par1b[dcmnt] = MISSING;
     lchNO3par2a[dcmnt] = MISSING;
     lchNO3par2b[dcmnt] = MISSING;
     maxdocCN[dcmnt] = MISSING;
     mindocCN[dcmnt] = MISSING;
     nonReactiveOMpar[dcmnt] = MISSING;
     propReactA[dcmnt] = MISSING;
     propReactB[dcmnt] = MISSING;
     minrootz[dcmnt] = MISSING;
     rootza[dcmnt] = MISSING;
     rootzb[dcmnt] = MISSING;
     rootzc[dcmnt] = MISSING;
  }

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

void Tsoil60::getecd( ofstream& rflog1 )
{

  string ecd;

  cout << "Enter name of the soil (.ECD) data file with parameter values: ";
  cout << endl;

  cin >> ecd;

  rflog1 << "Enter name of the soil (.ECD) data file with parameter values: ";
  rflog1 << ecd << endl;

  getecd( ecd );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::getecd( const string& ecd )
{
  ifstream infile;


  infile.open( ecd.c_str(), ios::in );

  if( !infile )
  {
    cerr << endl << "Cannot open " << ecd;
    cerr << " for soil ECD input" << endl;

    exit( -1 );
  }

  getXMLNode( infile, "soilECD" );

  pctpora = getXMLdouble( infile, "soilECD", "pctpora" );
  pctporb = getXMLdouble( infile, "soilECD", "pctporb" );

  fldcapa = getXMLdouble( infile, "soilECD", "fldcapa" );
  fldcapb = getXMLdouble( infile, "soilECD", "fldcapb" );

  wiltpta = getXMLdouble( infile, "soilECD", "wiltpta" );
  wiltptb = getXMLdouble( infile, "soilECD", "wiltptb" );

  infile.close();

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tsoil60::getThawedReactiveSOMProp( const int& pdcmnt )
{
  double propReact;
  
  if( activeLayer < rootz )
  {
    if( rootz > ZERO )
    {	
      propReact = propReactA[pdcmnt] * (activeLayer / rootz)
                  / (propReactB[pdcmnt] + (activeLayer / rootz)); 	
    }
    else { propReact = ZERO; }
  }
  else { propReact = 1.000000000000000; }
  
  return propReact;
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::lake( const double& tair,
                    const double& prec,
                    double& rain,
                    double& snowfall,
       		    const double& pet,
                    double& eet )
{

  rgrndh2o = ZERO;
  sperc = ZERO;
  snowpack = ZERO;
  sgrndh2o = ZERO;
  moist = ZERO;

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

  eet = pet;
  h2oyld = prec - pet;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::percol( const double& rain, const double& avlh2o )
{

  double extra;
  double recharge;
  sperc = ZERO;
  rperc = ZERO;

  recharge = rain + snowinf;
  
  if( recharge <= ZERO ) { recharge = 0.001; }
  
  if(( avlh2o + rain + snowinf - eet ) > awcapmm)
  {
    extra = rain + snowinf + avlh2o - awcapmm - eet;

    sperc = snowinf * extra / recharge;
  
    rperc = rain * extra / recharge;
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::resetEcds( const int& pcmnt )
{
  if( psiplusc <= lchNO3parcut[pcmnt] )
  {
    lchNO3par = (lchNO3par1a[pcmnt] * psiplusc) 
                + lchNO3par1b[pcmnt];
  }
  else
  {
    lchNO3par = (lchNO3par2a[pcmnt] * psiplusc)
                + lchNO3par2b[pcmnt];
  }

  if( lchNO3par < ZERO ) { lchNO3par = ZERO; }
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::resetMonthlyFluxes( void )
{
  // Reset monthly fluxes to zero

  // Carbon fluxes
  
  leachDOM.carbon = ZERO;
  erodePOM.carbon = ZERO;


  // Nitrogen fluxes
  
  abioticNimmob = ZERO;

  nh3flux = ZERO;
  noflux = ZERO;
  n2oflux = ZERO;
  n2flux = ZERO;
  leachNO3 = ZERO;
  leachDOM.nitrogen = ZERO;
  erodePOM.nitrogen = ZERO;

  ninput = ZERO;
  nlost = ZERO;

  // Water fluxes
  
  ineet = ZERO;
  eet = ZERO;
  rperc = ZERO;
  sperc = ZERO;
  rrun = ZERO;
  srun = ZERO;

  snowinf = ZERO;
  h2oyld = ZERO;
    	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::resetYrFluxes( void )
{
  // Reset annual fluxes and summary variables to zero
  
  // Annual carbon storage

  yrorgc = ZERO;
  yrDOM.carbon = ZERO;
  yrnonorgc = ZERO;


  // Annual nitrogen storage

  yrorgn = ZERO;
  yrDOM.nitrogen = ZERO;
  yravln.nh4 = ZERO;
  yravln.no3 = ZERO;

  yrnonorgn = ZERO;
  yrc2n = ZERO;
  yravln.total = ZERO;

  // Annual water storage

  yravlh2o = ZERO;
  yrsmoist = ZERO;
  yrvsm = ZERO;
  yrpctp = ZERO;
  yrsnowpack = ZERO;
  yrrgrndh2o = ZERO;
  yrsgrndh2o = ZERO;


  // Annual carbon fluxes

  yrlchDOM.carbon = ZERO;
  yrerodePOM.carbon = ZERO;


  // Annual nitrogen fluxes

  yrabNimmob = ZERO;

  yrnh3flx = ZERO;
  yrnoflx = ZERO;
  yrn2oflx = ZERO;
  yrn2flx = ZERO;
  yrlchNO3 = ZERO;
  yrlchDOM.nitrogen = ZERO;
  yrerodePOM.nitrogen = ZERO;

  yrnin = ZERO;
  yrnlost = ZERO;

  // Annual water fluxes

  yrineet = ZERO;
  yreet = ZERO;
  yrrperc = ZERO;
  yrsperc = ZERO;
  yrrrun = ZERO;
  yrsrun = ZERO;

  yrsnowinf = ZERO;
  yrh2oyld = ZERO;

  // Soil thermal dynamics

  yrtsoil = ZERO;
  yrdst10 = ZERO;
  
  stm.resetYr(); 
  	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tsoil60::rrunoff( const double& rgrndh2o )
{

  double rrunof;

  rrunof = 0.5 * (rgrndh2o + rperc);

  return rrunof;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::setDOMleaching( const int& pdcmnt,
                              const double& soilc,
                              const double& soiln,
                              const double& soilh2o,
                              const double& rain,
                              const double& eet )
{
  double solcn;
  double relDOM;

  if( soiln > ZERO && soilh2o > ZERO )
  {
    solcn = soilc / soiln;

    if( solcn >= maxdocCN[pdcmnt] ) { relDOM = 1.000000; }
    else
    {
      if( solcn > mindocCN[pdcmnt] )
      {
        relDOM = ((solcn - mindocCN[pdcmnt])
                  / (maxdocCN[pdcmnt] - mindocCN[pdcmnt]));
      }
      else { relDOM = ZERO; }
    }

    leachDOM.carbon = DOCpar[pdcmnt] * relDOM * soilc / soilh2o;

    leachDOM.carbon *= ((rain + snowinf- eet)
                       + (activeLayer * 1000.0))
                       / (activeLayer * 1000.0);


    leachDOM.nitrogen = DONpar * relDOM * soiln / soilh2o;

    leachDOM.nitrogen *= ((rain + snowinf- eet)
                         + (activeLayer * 1000.0))
                         / (activeLayer * 1000.0);
  }
  else
  {
    leachDOM.carbon = ZERO;
    leachDOM.nitrogen = ZERO;
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::setKH2O( const double& vsm, 
                       const int& moistlim )
{
  double vfc;
  
  if( 0 == moistlim ) 
  { 
    vfc = pcfldcap * 0.01;

    kh2o = pow( vfc, 3.0 ); 
  }
  else 
  { 
    if( vsm > 1.0 ) { kh2o = 1.0; }
    else { kh2o = pow( vsm, 3.0 ); }
  }

	
};

/* *************************************************************
************************************************************* */

/* *************************************************************
************************************************************* */

void Tsoil60::setTraceGasFluxes( const double& nh3vol,
                                 const double& noprd,
                                 const double& n2oprd,
                                 const double& n2prd  )
{

  nh3flux = nh3vol;
  noflux = noprd;
  n2oflux = n2oprd;
  n2flux = n2prd;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::showecd( void )
{

  cout << endl << "                   SOIL CHARACTERISTICS OF SITE";
  cout << endl << endl;
  
  printf( "PSAND    = %5.2lf      PSILT = %5.2lf      PCLAY = %5.2lf\n",
          pctsand,
          pctsilt,
          pctclay );

  printf( "POROSITY = %5.2lf   PCFLDCAP = %5.2lf   PCWILTPT = %5.2lf\n",
          pctpor,
          pcfldcap,
          pcwiltpt );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tsoil60::snowmelt( const double& elev,
                        const double& tair,
                        const double& prevtair,
                        const double& psnowpack )
{

  double snowflux = ZERO;

  if( tair >= -1.0 )
  {
    if( elev <= 500.0 ) { snowflux = psnowpack;}
    else
    {
      if( prevtair < -1.0 ) { snowflux = 0.5 * psnowpack; }
      else { snowflux = psnowpack; }
    }
  }

  if( snowflux < ZERO ) { snowflux = ZERO; }

  return snowflux;
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tsoil60::srunoff( const double& elev,
                         const double& tair,
                         const double& prevtair,
                         const double& prev2tair,
                         const double& sgrndh2o )
{

  double srunof = 0.0;

  if( tair >= -1.0 )
  {
    if( prevtair < -1.0 )
    {
      srunof = 0.1 * (sgrndh2o + sperc);
    }
    else
    {
      if( prev2tair < -1.0 )
      {
	if( elev <= 500.0 )
        {
          srunof = 0.5 * (sgrndh2o + sperc);
        }
	else { srunof = 0.25 * (sgrndh2o + sperc); }
      }
      else { srunof = 0.5 * (sgrndh2o + sperc); }
    }
  }

  return srunof;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::updateActiveLayerRootZ( void )
{

  totpor  = activeLayer * pctpor * 10.0;
  fldcap  = activeLayer * pcfldcap * 10.0;
  wiltpt  = activeLayer * pcwiltpt * 10.0;

  awcapmm = fldcap - wiltpt;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::updateHydrology( const double& elev,
                               const double& tair,
                               const double& prevtair,
                               const double& prev2tair,
                               const double& rain,
                               const double& pet,
                               const double& sh2o,
                               const double& rgrndh2o,
                               const double& sgrndh2o,
                               const int& irrgflag,
                               double& irrigate,
                               const int& pdm )
{
  double xrain;


  // Determine available water (avlh2o)
    
  avlh2o = (sh2o * activeLayer / rootz) - wiltpt; 

  if( avlh2o < ZERO )
  {
    avlh2o = ZERO;
  }


  // Determine initial eet (ineet)

  ineet = xeet( rain, pet, avlh2o, pdm );


  if( ineet > (rain + snowinf + avlh2o) )
  {
    ineet = rain + snowinf + avlh2o;
  }

  if( ineet < ZERO ) { ineet = ZERO; }


  if( 1 == irrgflag && ineet < pet )
  {
    // If irrigated, add just enough water to overcome 
    //   moisture limitations

    irrigate = pet - ineet;
    
    xrain = rain + irrigate;


    // Determine adjusted eet when irrigated

    eet = xeet( xrain, pet, avlh2o, pdm );
  }
  else
  {
    irrigate = ZERO;
    xrain = rain;

    eet = ineet;
  }

  // Determine monthly percent total porosity (pctp)
  //   of active layer
  
  pctp = (100.0 * sh2o * activeLayer / rootz) / totpor;


  // Determine volumetric soil moisture (vsm) of active layer
  
  vsm = sh2o / (rootz * 1000.0);
 
  if( vsm <= ZERO ) { vsm = 0.001; }
  
  
  // Determine percolation of rain water (rperc) and snow melt 
  //   water (sperc) through the soil profile
  
  percol( xrain, avlh2o );

  if( (avlh2o + snowinf + rain + irrigate - eet - rperc - sperc)
       < ZERO )
  {
    eet = avlh2o + snowinf + rain + irrigate - rperc - sperc;
  }


  // Determine runoff derived from rain (soil.rrun) and/or
  //   snow (soil.srun)

  rrun = rrunoff( rgrndh2o );

  srun = srunoff( elev,
                  tair,
                  prevtair,
                  prev2tair,
                  sgrndh2o );
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::updateLeachingLosses( const int& pdcmnt,
                                    const double& doc,
                                    const double& don,
                                    const double& soilno3, 
                                    const double& soilh2o )
{

  // Determine monthly leaching of DOC, DON and NO3
  
  if( (activeLayer <= MINACTLAYERZ) 
      || (rrun + srun) <= ZERO  
      || soilh2o <= ZERO )
  {
    leachDOM.carbon = ZERO;
    leachDOM.nitrogen = ZERO;
    leachNH4 = ZERO;
    leachNO3 = ZERO;   
  }
  else
  {
    // DOC leaching
    
    leachDOM.carbon = doc / soilh2o;
    
    leachDOM.carbon *= (rrun + srun);

    leachDOM.carbon *= lchDOMpar[pdcmnt];

    if( leachDOM.carbon < ZERO ) { leachDOM.carbon = ZERO; }
    
    // DON leaching
    
    leachDOM.nitrogen = don / soilh2o;

    leachDOM.nitrogen *= (rrun + srun);

    leachDOM.nitrogen *= lchDOMpar[pdcmnt];
    
    if( leachDOM.nitrogen < ZERO ) { leachDOM.nitrogen = ZERO; }
  
    // NH4 leaching

    leachNH4 = ZERO;

    // NO3 leaching
    
    leachNO3 = soilno3/ soilh2o;
    
    leachNO3 *= (rrun + srun);

    leachNO3 *= lchNO3par;
    
    if( leachNO3 < ZERO ) { leachNO3 = ZERO; }
  }
  	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::updateRootZ( const int& pdcmnt )
{
  rootz = (rootza[pdcmnt] * pow( psiplusc, 2.0 ))
          + (rootzb[pdcmnt] * psiplusc)
          + rootzc[pdcmnt];

  if( rootz < minrootz[pdcmnt] ) { rootz = minrootz[pdcmnt]; }

  pctpor = (pctpora * psiplusc) + pctporb;
  pcfldcap = (fldcapa * psiplusc) + fldcapb;
  pcwiltpt = (wiltpta * psiplusc) + wiltptb;

  totpor  = rootz * pctpor * 10.0;
  fldcap  = rootz * pcfldcap * 10.0;
  wiltpt  = rootz * pcwiltpt * 10.0;

  awcapmm = fldcap - wiltpt;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

double Tsoil60::xeet( const double& rain, 
                      const double& pet,
                      const double& avlh2o,  
                      const int& pdm )
{

  const double edpar = 5.0;

  double aet;
  double def;
  double dsm;
  double ep;
  double gm;
  double prob;
  double rbar;

  if( (rain+snowinf) >= pet )
  {
    aet = pet;
  }
  else
  {
    gm = (1.0 - exp( -edpar * avlh2o / awcapmm) ) 
         / (1.0 - exp( -edpar ));

    ep = pet / ndays[pdm];
    def = ep + awcapmm - avlh2o;
    prob = 1.0 - exp( -0.005*(rain + snowinf) );

    if( prob != ZERO ) 
    { 
      rbar = (rain + snowinf) / (ndays[pdm] * prob); 
    }
    else { rbar = ZERO; }

    if( rbar != ZERO )
    {
      dsm = rbar*prob*(gm + ((1.0-gm) * exp( -ep/rbar )) 
            - exp( -def/rbar )) 
            - (ep*gm);
    }
    else {
      dsm = -ep*gm;
    }

    dsm *= ndays[pdm];

    aet = rain + snowinf - dsm;
    
    if( aet > pet ) { aet = pet; }
  }

  return aet;
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tsoil60::xtext( const int& pdcmnt,
                     const double& pctsilt,
                     const double& pctclay )
{

  totpor = fldcap = wiltpt = MISSING;
  awcapmm =  MISSING;

  psiplusc = (pctsilt + pctclay) * 0.01;
  
  if( psiplusc < 0.01 ) { psiplusc = 0.01; }

  rootz = (rootza[pdcmnt] * pow( psiplusc, 2.0 ))
          + (rootzb[pdcmnt] * psiplusc)
          + rootzc[pdcmnt];

  if( rootz < minrootz[pdcmnt] ) { rootz = minrootz[pdcmnt]; }

  pctpor = (pctpora * psiplusc) + pctporb;
  pcfldcap = (fldcapa * psiplusc) + fldcapb;
  pcwiltpt = (wiltpta * psiplusc) + wiltptb;

  totpor  = rootz * pctpor * 10.0;
  fldcap  = rootz * pcfldcap * 10.0;
  wiltpt  = rootz * pcwiltpt * 10.0;

  awcapmm = fldcap - wiltpt;

};

