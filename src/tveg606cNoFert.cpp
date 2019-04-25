/* *************************************************************
****************************************************************
TVEG606CNOFERT.CPP - object describing characteristics of 
  vegetation used in the Terrestrial Ecosystem Model (TEM).
  Fertilizers are never assumed to be applied to croplands.
  
Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  
           
****************************************************************
************************************************************* */

#include "tveg606cNoFert.h"

Tveg60::Tveg60()
{
  int dcmnt;

  foliageFlag = 0;

  leafFlag = 0;

  plant.carbon = MISSING;
  plant.nitrogen = MISSING;

  strctrl.carbon = MISSING;
  strctrl.nitrogen = MISSING;

  labile.carbon = MISSING;
  labile.nitrogen = MISSING;

  ltrfal.carbon = MISSING;
  ltrfal.nitrogen = MISSING;

  nmobil = MISSING;
  nresorb = MISSING;

  inuptake.total = MISSING;
  inuptake.nh4 = MISSING;
  inuptake.no3 = MISSING;

  nuptake.total = MISSING;
  nuptake.nh4 = MISSING;
  nuptake.no3 = MISSING;

  suptake = MISSING;
  luptake = MISSING;

  ingpp = MISSING;
  gpp = MISSING;

  innpp = MISSING;
  npp = MISSING;

  rm = MISSING;
  rg = MISSING;
  gpr = MISSING;
  rootResp = MISSING;

  nfix = MISSING;
  lnfix = MISSING;

  unnormleaf = MISSING;
  leaf = MISSING;

  lai = MISSING;
  fpc = MISSING;


  inprodcn = MISSING;

  yrcarbon = MISSING;
  yrnitrogen = MISSING;

  yrstructn = MISSING;
  yrc2n = MISSING;

  yrstoren = MISSING;

  yrltrfalc = MISSING;
  yrltrfaln = MISSING;

  yringpp = MISSING;
  yrgpp = MISSING;

  yrinnpp = MISSING;
  yrnpp = MISSING;

  yrgpr = MISSING;
  yrrmaint = MISSING;
  yrrgrowth = MISSING;

  yrinnfix = MISSING;
  yrnfix = MISSING;
  yrsnfix = MISSING;
  yrlnfix = MISSING;

  yrinnup.total = MISSING;
  yrinnup.nh4 = MISSING;
  yrinnup.no3 = MISSING;

  yrnup.total = MISSING;
  yrnup.nh4 = MISSING;
  yrnup.no3 = MISSING;

  yrsup = MISSING;
  yrlup = MISSING;

  yrnmobil = MISSING;
  yrnrsorb = MISSING;


  yrinpr = MISSING;
  yrprod = MISSING;

  yrunleaf = MISSING;
  yrleaf = MISSING;

  yrfpc = MISSING;
  alleaf = MISSING;
  foliage = MISSING;

  leafyrs = 10;

  for( dcmnt = 0; dcmnt < MAXCMNT; ++dcmnt )
  {
    c2na[dcmnt] = MISSING;
    c2nb[dcmnt] = MISSING;
    c2nmin[dcmnt] = MISSING;
    cnmin[dcmnt] = MISSING;
    initcneven[dcmnt] = MISSING;

    aleaf[dcmnt] = MISSING;
    bleaf[dcmnt] = MISSING;
    cleaf[dcmnt] = MISSING;
    initleafmx[dcmnt] = MISSING;
    minleaf[dcmnt] = MISSING;
    unleaf12[dcmnt] = MISSING;

    cov[dcmnt] = MISSING;
    fpcmax[dcmnt] = MISSING;
    sla[dcmnt] = MISSING;

    kleafc[dcmnt] = MISSING;
    leafmxc[dcmnt] = MISSING;

    cmaxcut[dcmnt] = MISSING;
    cmax1a[dcmnt] = MISSING;
    cmax1b[dcmnt] = MISSING;
    cmax2a[dcmnt] = MISSING;
    cmax2b[dcmnt] = MISSING;

    kc[dcmnt] = MISSING;
    ki[dcmnt] = MISSING;

    tmax[dcmnt] = MISSING;
    tmin[dcmnt] = MISSING;
    toptmin[dcmnt] = MISSING;
    toptmax[dcmnt] = MISSING;

    gva[dcmnt] = MISSING;

    tref[dcmnt] = MISSING;
    qref[dcmnt] = MISSING;
    alpha[dcmnt] = MISSING;
    beta[dcmnt] = MISSING;
    gamma[dcmnt] = MISSING;

    nfixadjust[dcmnt] = MISSING;
    nfixpara[dcmnt] = MISSING;
    nfixparb[dcmnt] = MISSING;
    
    nmaxcut[dcmnt] = MISSING;
    nmax1a[dcmnt] = MISSING;
    nmax1b[dcmnt] = MISSING;
    nmax2a[dcmnt] = MISSING;
    nmax2b[dcmnt] = MISSING;

    nupnh4cut[dcmnt] = MISSING;
    nupnh41a[dcmnt] = MISSING;
    nupnh41b[dcmnt] = MISSING;
    nupnh42a[dcmnt] = MISSING;
    nupnh42b[dcmnt] = MISSING;

    nupno3cut[dcmnt] = MISSING;
    nupno31a[dcmnt] = MISSING;
    nupno31b[dcmnt] = MISSING;
    nupno32a[dcmnt] = MISSING;
    nupno32b[dcmnt] = MISSING;

      kn1[dcmnt] = MISSING;
    kvnh4[dcmnt] = MISSING;
    kvno3[dcmnt] = MISSING;

    cfall[dcmnt] = MISSING;
    nfall[dcmnt] = MISSING;

    labncon[dcmnt] = MISSING;
  }

  cneven = MISSING;
  c2n = MISSING;
  dc2n = MISSING;
  adjc2n = MISSING;

  newleafmx = MISSING;
  prvleafmx = MISSING;

  cmax = MISSING;

  topt = MISSING;
  newtopt = MISSING;

  kr = MISSING;

  nmax = MISSING;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::boundTOPT( const int& pcmnt )
{
  if( topt > toptmax[pcmnt] ) {	topt = toptmax[pcmnt]; }

  if( topt < toptmin[pcmnt] ) { topt = toptmin[pcmnt]; }
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::deltaleaf( const int& pdcmnt,
                          const double& eet,
                          const double& prveetmx,
                          const double& prvleaf )
{

  double normeet;
  double unnormleaf;
  double maxeet;

  if( prveetmx <= ZERO ) { maxeet = 1.0; }
  else { maxeet = prveetmx; }
  
  normeet = eet / maxeet;

  unnormleaf = (aleaf[pdcmnt] * normeet)
               + (bleaf[pdcmnt] * prvleaf)
               + cleaf[pdcmnt];

  if( unnormleaf < (0.5 * minleaf[pdcmnt]) )
  {
    unnormleaf = 0.5 * minleaf[pdcmnt];
  }

  if( unnormleaf > 1.000000000 )
  {
    unnormleaf = 1.000000000;
  }

  return unnormleaf;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::gppxclm( const int& pdcmnt,
                        const double& co2,
                        const double& par,
                        const double& temp,
                        const double& gv,
                        const double& leaf,
                        const double& foliage,
                        const double& thawpercent )
{

  double gpp;


/* *************************************************************
   gpp:    gpp as influenced by carbon dioxide (co2), moisture
	   (gv), phenology (leaf), photosynthetically active
	   radiation (par), air temperature (temp) and freeze-
	   thaw index (thawpercent)

************************************************************* */

  gpp  = co2 * gv;
  gpp *= cmax * foliage / (kc[pdcmnt] + gpp);
  gpp *= leaf * par / (ki[pdcmnt] + par);
  gpp *= temp;
  gpp *= thawpercent;

  return gpp;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::gppxio3( const double& fozone,
                        const double& eetpet )
{
  double findozone;

  if( ZERO == fozone )
  {
    findozone = 1.0;
  }
  else
  {
    findozone = (1.0-1.0/fozone) * eetpet + (1.0/fozone);
  }

  return findozone;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::gppxo3( const int& pdcmnt,
                       const double& gpp,
                       const double& d40,
                       const double& eetpet )
{
  double fozone;

  fozone = 1.0 - (o3para[pdcmnt] * pow( 10.0, -6 )
           * (o3parb[pdcmnt] + o3parc[pdcmnt] * gpp) * d40);

  fozone = 1 - eetpet + (eetpet*fozone);

  fozone = fozone + fprevozone - 1.0;

  // Keep fozone between 0.0 and 1.0
  
  if( fozone <= ZERO )
  {
    fozone = ZERO;
  }
  
  if( fozone >= 1.0 )
  { 
    fozone = 1.000000;
  }


  return fozone;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::nupnh4xclm( const int& pdcmnt,
                           const double& soilh2o,
                           const double& nh4,
                           const double& respq10,
                           const double& ksoil,
                           const double& foliage,
                           const double& fozone )
{

/* *************************************************************
   nuptake:  uptake of ammonium by plants as influenced by
	     ammonium concentration (nh4), moisture
	     (ksoil), ozone, and air temperature (respq10)
************************************************************* */

  double nuptake;

  if( ZERO == soilh2o ) { nuptake = ZERO; }
  else
  {
    nuptake  = (nh4 * ksoil) / soilh2o;
    nuptake *= nupnh4 * foliage / (kvnh4[pdcmnt] + nuptake);
    nuptake *= respq10;
    nuptake *= fozone;  
  }

  return nuptake;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::nupno3xclm( const int& pdcmnt,
                           const double& soilh2o,
                           const double& no3,
                           const double& respq10,
                           const double& ksoil,
                           const double& foliage,
                           const double& fozone )
{

/* *************************************************************
   nuptake:  uptake of nitrate by plants as influenced by
	     soil nitrate concentration (no3), moisture
	     (ksoil), ozone, and air temperature (respq10)
************************************************************* */

  double nuptake;

  if( ZERO == soilh2o ) { nuptake = ZERO; }
  else
  {
    nuptake  = (no3 * ksoil) / soilh2o;
    nuptake *= nupno3 * foliage / (kvno3[pdcmnt] + nuptake);
    nuptake *= respq10;
    nuptake *= fozone;
  }

  return nuptake;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::nupxclm( const int& pdcmnt,
                        const double& soilh2o,
                        const double& availn,
                        const double& respq10,
                        const double& ksoil,
                        const double& foliage,
                        const double& fozone )
{

/* *************************************************************
   nuptake:  uptake of nitrogen by plants as influenced by
	     available nitrogen concentration (availn), moisture
	     (ksoil), ozone, and air temperature (respq10)
************************************************************* */

  double nuptake;

  if( ZERO == soilh2o ) { nuptake = ZERO; }
  else
  {
    nuptake  = (availn * ksoil) / soilh2o;
    nuptake *= nmax * foliage / (kn1[pdcmnt] + nuptake);
    nuptake *= respq10;
    nuptake *= fozone;
  }

  return nuptake;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void Tveg60::resetEcds( const int& pcmnt,
                        const double& psiplusc )
{
  // Initialize TEM parameters dependent upon a grid cell's
  //   soil texture

  if( psiplusc <= cmaxcut[pcmnt] )
  {
    cmax = (cmax1a[pcmnt] * psiplusc) + cmax1b[pcmnt];
  }
  else
  {
    cmax = (cmax2a[pcmnt] * psiplusc) + cmax2b[pcmnt];
  }

  if( cmax < ZERO ) { cmax = ZERO; }
  
  if( psiplusc <= nupnh4cut[pcmnt] )
  {
    nupnh4 = (nupnh41a[pcmnt] * psiplusc) + nupnh41b[pcmnt];
  }
  else
  {
    nupnh4 = (nupnh42a[pcmnt] * psiplusc) + nupnh42b[pcmnt];
  }

  if( nupnh4 < ZERO ) { nupnh4 = ZERO; }
  
  if( psiplusc <= nupno3cut[pcmnt] )
  {
    nupno3 = (nupno31a[pcmnt] * psiplusc) + nupno31b[pcmnt];
  }
  else
  {
    nupno3 = (nupno32a[pcmnt] * psiplusc) + nupno32b[pcmnt];
  }

  if( nupno3 < ZERO ) { nupno3 = ZERO; }
  
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void Tveg60::resetMonthlyFluxes( void )
{
  // Reset monthly fluxes to zero
  
  ingpp = ZERO;
  gpp = ZERO;
  fozone = ZERO;
  findozone = ZERO;

  innpp = ZERO;
  npp = ZERO;
  
  gpr = ZERO;
  rm = ZERO;
  rg = ZERO;
  abvgrndResp = ZERO;
  rootResp = ZERO;
   
  ltrfal.carbon = ZERO;

  nfix = ZERO;

  inuptake.total = ZERO;
  inuptake.nh4 = ZERO;
  inuptake.no3 = ZERO;

  nuptake.total = ZERO;
  nuptake.nh4 = ZERO;
  nuptake.no3 = ZERO;

  suptake = ZERO;
  luptake = ZERO;
  nmobil = ZERO;
  nresorb = ZERO;

  ltrfal.nitrogen = ZERO;
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::resetNEWTOPT( const int& pcmnt, 
                           const double& tair, 
                           const double& unnrmleaf )
{
  if( ZERO == aleaf[pcmnt] 
      && ZERO == bleaf[pcmnt]
      && 1.0 == cleaf[pcmnt] )
  {
    if( tair > newtopt ) { newtopt = tair; }
  }
  else
  {
    if( unnrmleaf > newleafmx )
    {
      newleafmx = unnrmleaf;

      newtopt = tair;
    }
  }
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::resetYrFluxes( void )
{
  // Reset annual fluxes and summary variables to zero

  yrcarbon = ZERO;

  yrstructn = ZERO;
  yrstoren = ZERO;

  yrnitrogen = ZERO;
  yrc2n = ZERO;

  yrthawpct = ZERO;

  // Phenology

  yrunleaf = ZERO;
  yrleaf = ZERO;
  yrlai = ZERO;
  yrfpc = ZERO;

  // Carbon fluxes
  
  yringpp = ZERO;
  yrgpp = ZERO;
  yrinnpp = ZERO;
  yrnpp = ZERO;
  yrgpr = ZERO;
  yrrmaint = ZERO;
  yrrgrowth = ZERO;
  yrabvgrndResp = ZERO;
  yrrootResp = ZERO;

  yrvoc.isoprene = ZERO;
  yrvoc.monoterpene = ZERO;
  yrvoc.otherReactive = ZERO;
  yrvoc.other = ZERO;
  yrvoc.total = ZERO;

  yrltrfalc = ZERO;

  // Nitrogen fluxes
  
  yrnfix = ZERO;

  yrinnup.total = ZERO;
  yrinnup.nh4 = ZERO;
  yrinnup.no3 = ZERO;

  yrnup.total = ZERO;
  yrnup.nh4 = ZERO;
  yrnup.no3 = ZERO;

  yrsup = ZERO;
  yrlup = ZERO;
  yrnmobil = ZERO;
  yrnrsorb = ZERO;

  yrltrfaln = ZERO;

};
/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::rmxclm( const int& pdcmnt,
                       const double& vegc,
                       const double& respq10 )
{

/* *************************************************************
   rm: plant maintenance respiration as influenced by plant
       biomass (vegc) and air temperature (respq10)
************************************************************* */

  const double kr25 = 9.648;
  
  double krm;

  double rmaint;

  krm = rmmax[pdcmnt] * initcneven[pdcmnt] / kr25;
 
  rmaint = vegc * rmmax[pdcmnt] / (krm + vegc);
  rmaint *= respq10;

  return rmaint;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Tveg60::setGV( const double& eet,
                      const double& pet,
                      const int& moistlim )
{
  double tstgv;

/* tstgv: effect of moisture on primary productivity */

  if( 0 == moistlim )
  {
    tstgv = 1.0;
  }
  else
  {
    if( ZERO == pet ) { tstgv = ZERO; }
    else if( eet / pet <= 0.1 )
    {
      tstgv = (-10.0 * pow( (eet / pet), 2.0 ))
              + (2.9 * (eet / pet));
      
      if( tstgv < ZERO ) { tstgv = ZERO; }
    }
    else
    {
      tstgv = 0.1 + (0.9 * eet / pet);
    }
  }

  return tstgv;
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::setNewRESPQ10( const int& pdcmnt, const double& tair )
{
/* *************************************************************
 respq10: effect of temperature on plant respiration

 Amthor, J. (in review)
************************************************************* */

  double raq10;

  raq10 = qref[pdcmnt]
          * exp( -1.0 * alpha[pdcmnt] * (tair - tref[pdcmnt]) );

  respq10 = pow( raq10, (tair - tref[pdcmnt])/10.0 )
            / ( 1.0 + exp( beta[pdcmnt] - tair )
                + exp( tair - gamma[pdcmnt] ));

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::setTEMP( const int& pdcmnt, const double& tair )
{
  /* temp: effect of temperature on primary productivity */

  if( tair <= tmin[pdcmnt] || tair >= tmax[pdcmnt] )
  {
    temp = 0.0;
  }
  else
  {
    if( tair >= topt && tair <= toptmax[pdcmnt] )
    {
      temp = 1.0;
    }
    else
    {
      if( tair > tmin[pdcmnt] && tair < topt )
      {
	temp = (tair - tmin[pdcmnt])
               * (tair - tmax[pdcmnt])
               / ((tair - tmin[pdcmnt])
               * (tair - tmax[pdcmnt])
               - pow( (tair - topt), 2.0 ));
      }
      else
      {
	temp = (tair - tmin[pdcmnt])
               * (tair - tmax[pdcmnt])
               / ((tair - tmin[pdcmnt])
               * (tair - tmax[pdcmnt])
               - pow( (tair - toptmax[pdcmnt]), 2.0 ));
      }
    }
  }
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::setThawPercent( const double& pprevdst10,
                             const double& pdst10,
                             const double& pnextdst10 )
{

  double dst10;
  double prevdst10;
  double nextdst10;
  
  // Calculate the thawing-proportion in early month and later fall

  if( ZERO == pdst10 ) { dst10 = 0.001; }
  else { dst10 = pdst10; }
  
  if( ZERO == pprevdst10 ) { prevdst10 = 0.002; }
  else { prevdst10 = pprevdst10; }
  
  if( ZERO == pnextdst10 ) { nextdst10 = 0.003; }
  else { nextdst10 = pnextdst10; }
  
  
  // Conditions of - - -
  if( (prevdst10 < ZERO)
       && (dst10 < ZERO)
       && (nextdst10 < ZERO) )
  {
    thawpercent = ZERO;
  }

  // Conditions of + + +
  if( (prevdst10 > ZERO)
       && (dst10 > ZERO)
       && (nextdst10 > ZERO) )
  {
    thawpercent = 1.0;
  }

  // Conditions of + - +
  if( (prevdst10 > ZERO)
       && (dst10 < ZERO)
       && (nextdst10 > ZERO) )
  {
     thawpercent = ((prevdst10 + dst10 + nextdst10) / 3.0 ) / 3.0;
  }

  // Conditions of + + -
  if( (prevdst10 > ZERO)
       && (dst10 > ZERO)
       && (nextdst10 < ZERO) )
  {
     thawpercent = ((prevdst10 + dst10 + nextdst10) / 3.0 ) / 4.0;    
  }

  // Conditions of - + +
  if( (prevdst10 < ZERO)
       && (dst10 > ZERO)
       && (nextdst10 > ZERO) )
  {
     thawpercent = ((prevdst10 + dst10 + nextdst10) / 3.0 ) / 6.0;    
  }

  // Conditions of - - +
  if( (prevdst10 < ZERO)
       && (dst10 < ZERO)
       && (nextdst10 > ZERO) )
  {
     thawpercent = ((prevdst10 + dst10 + nextdst10) / 3.0 ) / 5.0;    
  }

  // Conditions of + - -
  if( (prevdst10 > ZERO)
       && (dst10 < ZERO)
       && (nextdst10 < ZERO))
  {
     thawpercent = ((prevdst10 + dst10 + nextdst10) / 3.0 ) / 4.0;    
  }

  // Conditions of - + -
  if( (prevdst10 < ZERO)
       && (dst10 > ZERO)
       && (nextdst10 < ZERO) )
  {
     thawpercent = ((prevdst10 + dst10 + nextdst10) / 3.0 ) / 3.0;
  }


  if( thawpercent > 1.0 ) { thawpercent = 1.000000; }
  if( thawpercent < ZERO ) { thawpercent = ZERO; }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void Tveg60::showecd( const int& pdcmnt )
{

  printw ("\n             VEGETATION PARAMETERS INFLUENCED BY CLIMATE\n\n\n" );
  printw( "  KI = %6.2lf  KC = %6.2lf  KVNH4 = %6.4lf  KVNO3 = %6.4lf  GVA = %8.4lf\n\n",
          ki[pdcmnt],
          kc[pdcmnt],
          kvnh4[pdcmnt],
          kvno3[pdcmnt],
          gva[pdcmnt] );

  printw( "   TMIN = %5.1lf    TOPTMIN = %5.1lf   TOPTMAX = %5.1lf   TMAX = %5.1lf\n\n",
          tmin[pdcmnt],
          toptmin[pdcmnt],
          toptmax[pdcmnt],
          tmax[pdcmnt] );

  printw( " TREF = %7.5lf  QREF = %7.5lf  ALPHA = %7.5lf  BETA = %7.5lf  GAMMA = %7.5lf\n",
		  tref[pdcmnt],
		  qref[pdcmnt],
		  alpha[pdcmnt],
		  beta[pdcmnt],
		  gamma[pdcmnt] );

  refresh();

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void Tveg60::showleaf( const int& pdcmnt )
{

  printw("\n         PARAMETERS FOR THE LEAF PHENOLOGY MODEL\n\n\n" );
  printw( "     ALEAF = %7.5lf     BLEAFC = %8.5lf        CLEAF = %8.5lf\n",
          aleaf[pdcmnt],
          bleaf[pdcmnt],
          cleaf[pdcmnt] );

  printw( "   MINLEAF = %4.2lf       MAXLEAF = %7.4lf      UNLEAF12 = %7.4lf\n",
          minleaf[pdcmnt],
          initleafmx[pdcmnt],
          unleaf12[pdcmnt] );

  refresh();
};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::updateC2N( const int& pdcmnt,
                        const double& yreet,
                        const double& yrpet,
                        const double& currentco2,
                        const double& initco2 )
{
  if( yrpet != ZERO )
  {
    c2n = c2nb[pdcmnt] + c2na[pdcmnt]*(yreet/yrpet);
  }
  else { c2n = c2nb[pdcmnt]; }

  if( c2n < c2nmin[pdcmnt] ) { c2n = c2nmin[pdcmnt]; }
  
  adjc2n = 1.0 + (dc2n * (currentco2 - initco2));
  c2n *= adjc2n;
  cneven = initcneven[pdcmnt] * adjc2n;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::updateDynamics( const int& pdcmnt,
                             const double& co2,
                             const double& aot40,
                             const InorgN60& ndep,
                             const InorgN60& extraN,
                             const double& par,
                             const double& pet,
                             const double& prevmaxpet,
                             const double& eet,
                             const double& prevmaxeet,
                             const double& vegc,
                             const double& structn,
                             const double& labilen,
                             const double& soilh2o,
                             const double& soilnh4,
                             const double& soilno3,
                             const int& moistlim,
                             const int& nfeed,
                             const int& o3flag,
                             const int& agstate,
                             const int& agperennial,
                             const int& year,
                             const int& fertflag,
                             const double& ksoil,
                             const double& netnmin,
                             const double& ammnvol,
                             const double& nitrif,
                             const double& no3prod,
                             double& agfertn )
{	
  double eetpet;
  double gv;
  
  // Determine stage of seasonal phenology

  if( 0 == leafFlag )
  { 
    if( 0 == moistlim )
    {
      unnormleaf = deltaleaf( pdcmnt,
                              pet,
                              prevmaxpet,
                              prevunrmleaf );
    }
    else
    {
      unnormleaf = deltaleaf( pdcmnt,
                              eet,
                              prevmaxeet,
                              prevunrmleaf );                           
    }

    if( prvleafmx <= ZERO ) { leaf = ZERO; }
    else 
    { 
      if( prvleafmx > 1.000000000 )
      {
        prvleafmx = 1.000000000;
      }

      leaf = unnormleaf / prvleafmx; 
    }
    

    if( leaf < minleaf[pdcmnt] )
    {
      leaf = minleaf[pdcmnt];
    }

    if( leaf > 1.0 ) { leaf = 1.0; }
  }

  // gv: effect of moisture on primary productivity

  gv = setGV( eet, pet, moistlim );

 
  // Determine Gross Primary Production if nitrogen is not
  //   limiting (veg.ingpp)

  ingpp = gppxclm( pdcmnt,
                   co2,
                   par,
                   temp,
                   gv,
                   leaf,
                   foliage,
                   thawpercent );

  if( ingpp < ZERO ) { ingpp = ZERO; }
 

  /* ozone: effect of surface ozone on gpp */

  if( 0 == o3flag )
  {
    fozone = 1.000000;
    fprevozone = 1.000000;
    findozone = 1.000000;
  }
  else
  {
    if( ZERO == pet )
    {
      eetpet = ZERO;
    }  
    else
    {
      eetpet = eet / pet;
    }

    fozone = gppxo3( pdcmnt,
                     ingpp,
                     aot40,
                     eetpet );

    ingpp *= fozone;
  }

  if( ingpp < ZERO ) { ingpp = ZERO; }


  // Determine Maintenance Respiration of vegetation (veg.rm)

  rm = rmxclm( pdcmnt, vegc, respq10 );

  if( rm < ZERO ) { rm = ZERO; }


  // Determine Net Primary Production if nitrogen is not
  //   limiting (veg.innpp) and Growth Respiration (veg.rg)

  innpp = ingpp - rm;

  rg = ZERO;
  if( innpp > ZERO )
  {
    rg  = 0.2 * innpp;
    innpp *= 0.8;
  }


  // Determine monthly loss of carbon and nitrogen in litterfall

  ltrfal.carbon = cfall[pdcmnt] * vegc;
  if( ltrfal.carbon < ZERO )
  {
    ltrfal.carbon = ZERO;
  }

  ltrfal.nitrogen = nfall[pdcmnt] * structn;
  
  if( ltrfal.nitrogen < ZERO )
  {
    ltrfal.nitrogen = ZERO;
  }


  // Determine nitrogen uptake by vegetation if carbon is not
  //   limiting (veg.inuptake)

  inuptake.nh4 = nupnh4xclm( pdcmnt,
                             soilh2o,
                             soilnh4,
                             respq10,
                             ksoil,
                             foliage,
                             fozone );

  inuptake.no3 = nupno3xclm( pdcmnt,
                             soilh2o,
                             soilno3,
                             respq10,
                             ksoil,
                             foliage,
                             fozone );

 if( 1 == dbug )
  {
    cout << " soilh2o = " << soilh2o;
    cout << " ksoil = " << ksoil;
    cout << " soilnh4 = " << soilnh4;
    cout << " inuptake.nh4 = " << inuptake.nh4 << endl;
    cout << " soilno3 = " << soilno3;
    cout << " inuptake.no3 = " << inuptake.no3 << endl;
  }

  if( inuptake.nh4 > soilnh4 + ndep.nh4 + extraN.nh4 + netnmin 
                     - ammnvol - nitrif )
  {
    inuptake.nh4 = soilnh4 
                   + ndep.nh4
                   + extraN.nh4 
                   + netnmin 
                   - ammnvol 
                   - nitrif;
  }

  if( inuptake.nh4 < ZERO )
  {
    inuptake.nh4 = ZERO;
  }


  if( inuptake.no3 > soilno3 + ndep.no3 + no3prod )
  {
    inuptake.no3 = soilno3 + ndep.no3 + no3prod;
  }

  if( inuptake.no3 < ZERO ) { inuptake.no3 = ZERO; }


  inuptake.total = inuptake.nh4 + inuptake.no3;


  // Determine how interactions between carbon and nitrogen
  //   availability influence primary production, litterfall
  //   and nitrogen uptake

  gpp = ingpp;
  npp = innpp;


  // Assume CROP NPP is always positive or zero

  if( 1 == agstate && 0 == agperennial )
  {
     if( npp < ZERO ) { npp = ZERO; }
  }
 
 
  nuptake.total = inuptake.total;

  nuptake.no3 = inuptake.no3;

  nuptake.nh4 = nuptake.total - nuptake.no3;

  if( nuptake.nh4 < ZERO )
  {
    nuptake.nh4 = ZERO;
    nuptake.no3 = nuptake.total;
  }

  suptake = nuptake.total;
  luptake = ZERO;

  nmobil = ZERO;
  nresorb = ZERO;


  // Nitrogen feedback of GPP ( 1 == nfeed)

  if( 1 == nfeed )
  {
    // Determine nitrogen resorption (veg.nresorb)
    
    if( ltrfal.nitrogen
         <= (ltrfal.carbon / cneven) )
    {
      nresorb = (ltrfal.carbon / cneven) - ltrfal.nitrogen;
    }
    else
    {
      nresorb = ZERO;
    }

    if( vegc > ZERO )
    {
      nresorb *= (structn / vegc) * c2n;
    }


    // Determine if monthly primary production is carbon-limited  
    //   or nitrogen-limited
    
    if( (nuptake.total + labilen + nfix) < 0.000001 )
    {
      inprodcn = innpp / 0.000001;
    }
    else 
    {
      inprodcn = innpp / (nuptake.total + labilen + nfix);
    }
    

    if( 1 == dbug )
    {
      cout << "inprodcn = " << inprodcn;
      cout << " nuptake.total = " << nuptake.total;
      cout << " labilen = " << labilen;
      cout << " nfix = " << nfix;
      cout << " cneven = " << cneven << endl;
    }

    // If primary production is nitrogen-limited, 
    //   (i.e., veg.inprodcn > veg.cneven) revaluate NPP, RG and 
    //   GPP based on nitrogen availability
     
    if( inprodcn > cneven )
    {
      if( 1 == fertflag )
      {
        // Assume nitrogen is never limiting if fertilized
        // Also assume that fertilized crops are based solely 
        //   on a nitrate economy
          
//        nuptake.no3 = (npp / cneven) - labilen - nfix;

//        if( nuptake.no3 > inuptake.no3 )
//        {
          // Ramp up fertilizer use between 1950 and 1990
//          if( year <= 1950 ) 
//          { 
//            agfertn = ZERO; 
//          }
//          else if( year > 1950 && year < 1990 )
//          { 
//            agfertn = (nuptake.no3 - inuptake.no3) 
//                      * ((double)(year - 1950)/ 40.0 );
//          }
//          else 
//          {
//            agfertn = nuptake.no3 - inuptake.no3;
//          }
//        }
//        else
//        {
        agfertn = ZERO;
//        }

        nuptake.no3 = inuptake.no3 + agfertn; 

        nuptake.total = nuptake.no3;
        nuptake.nh4 = ZERO;
      }

      if( 1 == dbug ) 
      { 
        cout << "Init NPP = " << npp; 
        cout << " nuptake.total = " << nuptake.total;
      }
      
      npp = cneven * (nuptake.total + labilen + nfix);

      if( 1 == dbug ) { cout << " Updated NPP = " << npp << endl; }

      if( npp < ZERO ) { npp = ZERO; }

      rg = 0.25 * npp;

      gpp = npp + rg + rm;

      if( gpp < ZERO ) { gpp = ZERO; }

      nmobil = labilen;

      suptake = nuptake.total;
      luptake = ZERO;
    }

  if( 1 == dbug )
  {
    cout << "GPP2 = " << gpp;
    cout << " NPP = " << npp;
    cout << " gv = " << gv;
    cout << " foliage = " << foliage << endl;
  }

    // If primary production is carbon-limited, 
    //   (i.e., veg.inprodcn < veg.cneven) revaluate nitrogen
    //   uptake by vegetation based on carbon availability

    if( inprodcn <= cneven )
    {
      nuptake.nh4 = nuptake.nh4
                    * (inprodcn - cnmin[pdcmnt])
                    * (inprodcn - 2 * cneven + cnmin[pdcmnt]);

      nuptake.nh4 /= ((inprodcn - cnmin[pdcmnt])
                     * (inprodcn - 2 * cneven + cnmin[pdcmnt]))
                     - pow( inprodcn - cneven, 2.0 );


      if( nuptake.nh4 > soilnh4 + ndep.nh4 + extraN.nh4 + netnmin 
                        - ammnvol - nitrif )
      {
        nuptake.nh4 = soilnh4 
                      + ndep.nh4
                      + extraN.nh4 
                      + netnmin 
                      - ammnvol 
                      - nitrif;
      }

      if ( nuptake.nh4 < ZERO )
      {
        nuptake.nh4 = ZERO;
      }

      nuptake.no3 = nuptake.no3
                    * (inprodcn - cnmin[pdcmnt])
                    * (inprodcn - 2 * cneven + cnmin[pdcmnt]);

      nuptake.no3 /= ((inprodcn - cnmin[pdcmnt])
                     * (inprodcn - 2 * cneven + cnmin[pdcmnt]))
                     - pow( inprodcn - cneven, 2.0 );


      if( nuptake.no3 > soilno3 + ndep.no3 + extraN.no3 + no3prod )
      {
        nuptake.no3 = soilno3 
                      + ndep.no3 
                      + extraN.no3
                      + no3prod;
      }

      if ( nuptake.no3 < ZERO )
      {
        nuptake.no3 = ZERO;
      }

      nuptake.total = nuptake.nh4 + nuptake.no3;


      // Drawdown N from labile N pool first to satisfy N
      //   requirement before taking up any nitrogen from the 
      //   soil
      
      if ( labilen >= (npp / cneven - nfix) )
      {
        nmobil = npp / cneven - nfix;
	
	      if ( nmobil < ZERO && vegc > 0.01 )
        {
	        nmobil *= (structn / vegc) * c2n;
	      }     
	
	      suptake = ZERO;
      }
      else
      {
        nmobil = labilen;
	
	      suptake = (npp / cneven) - nmobil - nfix;

	      if( suptake < ZERO ) 
	      { 
	        suptake = ZERO; 
	      }
	
	      if( suptake > nuptake.total )
        {
          suptake = nuptake.total;
        }
      }

      // Determine vegetation nitrogen uptake for the labile
      //   N pool
      
      if( (labilen + nuptake.total - suptake + nresorb - nmobil) 
           < (labncon[pdcmnt] * (structn + suptake 
           - ltrfal.nitrogen - nresorb + nmobil + nfix)) )
      {
        luptake = nuptake.total - suptake;
      }
      else
      {
        luptake = (labncon[pdcmnt] 
                  * (structn + suptake - ltrfal.nitrogen
                  - nresorb + nmobil + nfix))  
                  - (labilen + nresorb - nmobil);

	      if( luptake < ZERO ) { luptake = ZERO; }

	      nuptake.total = suptake + luptake;

        nuptake.nh4 = nuptake.total - nuptake.no3;

        if( nuptake.nh4 < ZERO )
        {
          nuptake.nh4 = ZERO;
          nuptake.no3 = nuptake.total;
        }
      }
    }
  }


  // Determine Gross Plant Respiration (veg.gpr)

  gpr = rm + rg;


  // Determine Root Respiration (veg.rootResp)

  rootResp = gpr * rroot[pdcmnt];


  // Determine Aboveground plant respiration (veg.abvgrdResp)

  abvgrndResp = gpr - rootResp;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Tveg60::updateFoliage( const int& pdcmnt,
                            const double& vegc,
			    const double& eet_mature )
{

  double trans_mature;
  
  if( 0 == foliageFlag )
  {
    alleaf = leafmxc[pdcmnt]
             /(1.0 + kleafc[pdcmnt] * exp( cov[pdcmnt] * vegc ));

    lai = sla[pdcmnt] * alleaf * leaf;

    foliage = alleaf / leafmxc[pdcmnt];
  }

  fpc = 1.0;

  trans_mature = eet_mature * proptrans[pdcmnt];
  
  transpiration = trans_mature * foliage;
  
};

