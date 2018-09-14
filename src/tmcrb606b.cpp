/* **************************************************************
*****************************************************************
TMCRB606B.CPP - object describing characteristics of soil microbes
              used in the Terrestrial Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

*****************************************************************
************************************************************** */

#include "tmcrb606b.h"

/* **************************************************************
************************************************************** */

Tmicrobe60::Tmicrobe60()
{
  int dcmnt;

  // Initialize variables to MISSING values

  dq10 = MISSING;
  
  rh = MISSING;

  nfix = MISSING;

  grossnmin = MISSING;
  immnh4 = MISSING;
  immob = MISSING;
  netnmin = MISSING;

  ammnvol = MISSING;

  nitrif = MISSING;
  no3prod = MISSING;
  noprod = MISSING;
  n2oprod = MISSING;
  n2prod = MISSING;
  denitrif = MISSING;

  yrrh = MISSING;

  yrnfix = MISSING;

  yrgmin = MISSING;
  yrimmnh4 = MISSING;
  yrimmb = MISSING;
  yrnmin = MISSING;

  yrammnvol = MISSING;

  yrnitrif = MISSING;
  yrno3prd = MISSING;
  yrnoprd = MISSING;
  yrn2oprd = MISSING;
  yrn2prd = MISSING;
  yrdenitrf = MISSING;

  for( dcmnt = 0; dcmnt < MAXCMNT; ++dcmnt )
  {
     alpha[dcmnt] = MISSING;
     ammnpar[dcmnt] = MISSING;
     beta[dcmnt] = MISSING;
     cnsoil[dcmnt] = MISSING;
     DOCpar[dcmnt] = MISSING;
     DONparcut[dcmnt] = MISSING;
     DONpar1a[dcmnt] = MISSING;
     DONpar1b[dcmnt] = MISSING;
     DONpar2a[dcmnt] = MISSING;
     DONpar2b[dcmnt] = MISSING;
     gamma[dcmnt] = MISSING;
     kdcut[dcmnt] = MISSING;
     kd1a[dcmnt] = MISSING;
     kd1b[dcmnt] = MISSING;
     kd2a[dcmnt] = MISSING;
     kd2b[dcmnt] = MISSING;
  }
};

/* **************************************************************
*************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::gminFastxClm( const double& soilorgc,
                                 const double& soilorgn,
                                 const double& rh )
{

  double gmin = ZERO;

  if( soilorgc > ZERO && soilorgn > ZERO )
  {
    gmin = (soilorgn / soilorgc) * rh;
  }

  return gmin;
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::gminSlowxClm( const int& pdcmnt,
                                 const double& soilorgc,
                                 const double& soilorgn,
                                 const double& rh )
{

  double gmin;

  gmin = ZERO;
  
  if( soilorgc > ZERO && soilorgn > ZERO )
  {
    gmin   = (soilorgn / soilorgc) * rh;

    if( gmin >= ZERO )
    {
      gmin *= (soilorgn/soilorgc) * cnsoil[pdcmnt];
    }
    else { gmin *= (soilorgc/soilorgn) / cnsoil[pdcmnt]; }
  }

  return gmin;

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::nimmFastxClm( const int& pdcmnt,
                                 const double& nimm,
                                 const double& soilh2o,
                                 const double& availn,
                                 const double& decay,
                                 const double& rh,
                                 const double& ksoil )
{
  double fimmb;
  double immob = ZERO;
  
  if( availn > ZERO && soilh2o > ZERO )
  {
    immob = (availn * ksoil) / soilh2o;
    immob /= (kn2[pdcmnt] + immob);
  }

  fimmb = nimm * immob * decay * rh;

  if( fimmb > availn ) { fimmb = availn; }

  return fimmb; 

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::nminxclm( const int& pdcmnt,
                             const double& soilh2o,
                             const double& soilorgc,
                             const double& soilorgn,
                             const double& availn,
                             const double& decay,
                             const double& rh,
                             const double& ksoil )
{

  double nmin;
  double tcnsoil;

  tcnsoil = cnsoil[pdcmnt];

  immob = ZERO;
  nmin = ZERO;
  
  if( soilorgc > ZERO && soilorgn > ZERO )
  {
    immob  = (availn * ksoil) / soilh2o;
    immob /= (kn2[pdcmnt] + immob);
    nmin   = ((soilorgn / soilorgc) - (nimm * immob * decay))
             * rh;

    if( nmin >= ZERO ) { nmin *= (soilorgn/soilorgc) * tcnsoil; }
    else { nmin *= (soilorgc/soilorgn) / tcnsoil; }
  }

  return nmin;

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::ntrfxclm( const int& pdcmnt,
                             const double& soilh2o,
                             const double& nh4,
                             const double& nmin,
                             const double& ksoil )
{

  double ntrf = ZERO;

  if( soilh2o > ZERO )
  {
    ntrf = (nh4 * ksoil) / soilh2o;
    ntrf /= (kn2[pdcmnt] + ntrf);
  }

  if( nmin > ZERO && ntrf > ZERO )
  {
    return relntrf * ntrfpar * ntrf * nmin;
  }
  else 
  { 
    return ZERO;
  }
  
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::resetEcds( const int& pcmnt, 
                            const double& psiplusc )
{
  if( psiplusc <= kdcut[pcmnt] )
  {
    kdc = (kd1a[pcmnt] * psiplusc) + kd1b[pcmnt];
  }
  else
  {
    kdc = (kd2a[pcmnt] * psiplusc) + kd2b[pcmnt];
  }

  if( kdc < ZERO ) { kdc = ZERO; }


  if( psiplusc <= nh4immcut[pcmnt] )
  {
    nh4imm = (nh4imm1a[pcmnt] * psiplusc) + nh4imm1b[pcmnt];
  }
  else
  {
    nh4imm = (nh4imm2a[pcmnt] * psiplusc) + nh4imm2b[pcmnt];
  }

  if( nh4imm < ZERO ) { nh4imm = ZERO; }
  
  if( psiplusc <= ntrfparcut[pcmnt] )
  {
    ntrfpar = (ntrfpar1a[pcmnt] * psiplusc) + ntrfpar1b[pcmnt];
  }
  else
  {
    ntrfpar = (ntrfpar2a[pcmnt] * psiplusc) + ntrfpar2b[pcmnt];
  }

  if( ntrfpar < ZERO ) { ntrfpar = ZERO; }


  // Determine the "decay" parameter

  decay = 0.26299 
          + (1.14757 * propftos[pcmnt])
          - (0.42956 * pow( propftos[pcmnt], 2.0 ));

  if( psiplusc <= DONparcut[pcmnt] )
  {
    DONpar = (DONpar1a[pcmnt] * psiplusc) + DONpar1b[pcmnt];
  }
  else
  {
    DONpar = (DONpar2a[pcmnt] * psiplusc) + DONpar2b[pcmnt];
  }
  
  if( DONpar < ZERO ) { DONpar = ZERO; }
	
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::resetMonthlyFluxes( void )
{
  // Reset monthly fluxes to zero
  
  // Carbon fluxes
  
  decomp = ZERO;
  rh = ZERO;
  DOMprod.carbon = ZERO;

  // Nitrogen fluxes
  
  nfix = ZERO;

  ndecomp = ZERO;
  DOMprod.nitrogen = ZERO;

  grossnmin = ZERO;
  immnh4 = ZERO;
  immob = ZERO;
  netnmin = ZERO;

  ammnvol = ZERO;

  nitrif = ZERO;
  no3prod = ZERO;
  noprod = ZERO;
  n2oprod = ZERO;
  n2prod = ZERO;
  denitrif = ZERO;
	
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::resetYrFluxes( void )
{
  // Reset annual fluxes and summary variables to zero

  // Carbon fluxes
  
  yrdecomp = ZERO;
  yrrh = ZERO;
  yrDOMprod.carbon = ZERO;

  // Nitrogen fluxes
  
  yrnfix = ZERO;

  yrndecomp = ZERO;
  yrDOMprod.nitrogen = ZERO;
  yrgmin = ZERO;
  yrimmnh4 = ZERO;
  yrimmb = ZERO;
  yrnmin = ZERO;

  yrammnvol = ZERO;

  yrnitrif = ZERO;
  yrno3prd = ZERO;
  yrnoprd = ZERO;
  yrn2oprd = ZERO;
  yrn2prd = ZERO;
  yrdenitrf = ZERO;
  
  
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::rhxclm( const double& soilorgc,
                           const double& dq10,
                           const double& moist )
{

  return kd * soilorgc * moist * dq10;

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::setDQ10( const int& pdcmnt, 
                          const double& tair, 
                          const double& tsoil,
                          const double& snowpack, 
                          const int& tsoilflg )
{
  // dq10: effect of temperature on decomposition 

  if( 1 == tsoilflg )
  {
    if( tsoil > (tair+100.0) )
    {
      dq10 = pow( rhq10[pdcmnt], tair / 10.0 );
    }
    else
    {
      dq10 = pow( rhq10[pdcmnt], tsoil / 10.0 );
    }
  }
  else
  {
    if( snowpack > ZERO ) { dq10 = 1.0; }
    else
    {
      // Use air temperature to calculate dq10
      	
      dq10 = pow( rhq10[pdcmnt], tair / 10.0 );
    }
  }

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::setNewDQ10( const int& pdcmnt,
                             const double& tair,
                             const double& tsoil,                             
                             const double& snowpack,
                             const int& tsoilflg )
{

/* **************************************************************
dq10: effect of temperature on decomposition based on

Lloyd, J., and J. A. Taylor (1994) On the temperature dependence
  of soil respiration. Functional Ecology 8, 315-323.
************************************************************** */

  double daq10;
  double t;


  if( 1 == tsoilflg )
  {
    if( tsoil > (tair+100.0) ) { t = tair; }
    else { t = tsoil; }

    daq10 = qref[pdcmnt]
            * exp( -1.0 * alpha[pdcmnt] * (t - tref[pdcmnt]) );

    dq10 = pow( daq10, (t - tref[pdcmnt])/10.0 )
            / ( 1.0 + exp( beta[pdcmnt] - t )
                + exp( t - gamma[pdcmnt] ));
  }
  else
  {
    // Assume snowpack insulates soil from air
    //   temperatures less than 0.0 degrees Celsius
    //   such that soil temperatures are 0.0 degrees
    //   Celsius or 273.15 degrees K

    if( snowpack > ZERO ) { t = tair; }
    else { t = ZERO; }

    daq10 = qref[pdcmnt]
            * exp( -1.0 * alpha[pdcmnt] * (t - tref[pdcmnt]) );

    dq10 = pow( daq10, (t - tref[pdcmnt])/10.0 )
            / ( 1.0 + exp( beta[pdcmnt] - t )
                + exp( t - gamma[pdcmnt] ));
  }
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::setNitrifStatus( const int& pdcmnt )
{
  // proportion of net N mineralization that is nitrified
  	
  double pntrf;  

  if( netnmin >= allntrf[pdcmnt] ) { pntrf = 1.000000; }
  else
  {
    if( (netnmin > initntrf[pdcmnt]) 
        && (allntrf[pdcmnt] != initntrf[pdcmnt]) )
    {
      pntrf = (netnmin - initntrf[pdcmnt])
              / (allntrf[pdcmnt] - initntrf[pdcmnt]);
    }
    else { pntrf = ZERO; }
  }

  return pntrf;

};

/* **************************************************************
************************************************************** */

/* **************************************************************
************************************************************** */

double Tmicrobe60::setRHMOIST( const int& pdcmnt,
                               const double& pcfldcap,
                               const double& vsm,
                               const int& moistlim )
{
  
/* rhxh2o: effect of moisture on decomposition */

  double rhxh2o;
  double vfc;
  
  if( 0 == moistlim )
  {
    vfc = pcfldcap * 0.01;

    rhxh2o = (vfc - moistmin[pdcmnt]) 
             * (vfc - moistmax[pdcmnt]);

    rhxh2o /= rhxh2o - pow( (vfc - moistopt[pdcmnt]), 2.0 );
  }
  else
  {
    if( vsm > 1.0 )
    {
      rhxh2o = (1.0 - moistmin[pdcmnt])
               * (1.0 - moistmax[pdcmnt]);

      rhxh2o /= rhxh2o - pow( (1.0 - moistopt[pdcmnt]), 2.0 );
    }
    else
    {
      rhxh2o = (vsm - moistmin[pdcmnt]) 
               * (vsm - moistmax[pdcmnt]);

      rhxh2o /= rhxh2o - pow( (vsm - moistopt[pdcmnt]), 2.0 );
    }
  }

  if( rhxh2o < ZERO ) { rhxh2o = ZERO; }

  return rhxh2o;
  
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::setTraceGasProduction( const int& pdcmnt,
                                        const double& pctp,
                                        double& agfertn )
{
  // Assume 2% of soil NO3 is lost as NO, N2O or N2
  //  based on WFPS (i.e., PCTP)

  const double upper = 150.0;  // upper limit
  const double opt = 60.0;  // optimum

  // rate at x = 0 as a fraction of optimum
  const double mzero = 0.0005;    

  double fluxmult;
  double ntracegas;

  double a;
  double b;
  double s;
  
  ammnvol = ZERO;

  noprod = ZERO;
  n2oprod = ZERO;
  n2prod = ZERO;

  if( agfertn < ZERO ) { agfertn = ZERO; }
  
  ntracegas = (no3prod + agfertn) * tgmpar[pdcmnt];

  if( ntracegas < ZERO ) { ntracegas = ZERO; }

  a = upper / pow( (upper - opt), 2.0 );
  s = -1.0 * log( mzero ) 
      / pow( (pow( a*upper, 0.5 ) - 1.0), 2.0 );

  if( pctp < upper )
  {
    b = pow( (pow( a*upper, 0.5 ) - 1.0), 2.0 );      
    b = pctp * (a + 1.0 / (pctp - upper)) - b;
    fluxmult = exp( s * b );
  }
  else { fluxmult = ZERO; }

  if( fluxmult > 1.0 ) { fluxmult = 1.000000; }
  
  n2oprod = ntracegas * fluxmult;
                            
  if( pctp < 60.0 )
  {
    noprod = ntracegas - n2oprod;

    // Adjust no3prod to account for the production
    //   of NO during nitrification instead of NO3

    no3prod = nitrif - noprod;
  }
  else
  {
    n2prod = ntracegas - n2oprod;
  }

 // Determine Denitrification (denitrif) from production
  //   of N2O and N2
  
  denitrif = n2oprod + n2prod;

  // Assume that a percentage of N added as fertilizer is lost
  //   as trace gases so readjust agfertn upward to account
  //   for this loss

  agfertn += (agfertn * tgmpar[pdcmnt]);

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

#ifdef CALIBRATE_TEM

void Tmicrobe60::showecd( const int& pdcmnt )
{

  printw( "\n   MICROBIAL PARAMETERS INFLUENCED BY CLIMATE\n\n" );

  printw( "          KN2 = %6.4lf\n", kn2[pdcmnt] );
  printw( "        RHQ10 = %6.2lf\n", rhq10[pdcmnt] );
  printw( "     MOISTMIN = %8.6lf\n", moistmin[pdcmnt] );
  printw( "     MOISTOPT = %8.6lf\n", moistopt[pdcmnt] );
  printw( "     MOISTMAX = %8.6lf\n", moistmax[pdcmnt] );
  printw( "       CNSOIL = %5.2lf\n", cnsoil[pdcmnt] );

};

#endif

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void Tmicrobe60::updateDynamics( const int& pdcmnt,
                                 const double& pcfldcap,
                                 const double& actlayer,
                                 const double& soilorgc,
                                 const double& soilorgn,
                                 const double& soilh2o,
                                 const double& vsm,
                                 const double& soilnh4,
                                 const double& nh4dep,
                                 const int& moistlim,
                                 const int& tillflag,
                                 const double& tillfactor,
                                 const double& ksoil )
{
  double rhmoist;

  // rhmoist: effect of moisture on decomposition

  rhmoist = setRHMOIST( pdcmnt, pcfldcap, vsm, moistlim );


  if( actlayer > MINACTLAYERZ )
  {
    decomp = rhxclm( soilorgc, dq10, rhmoist );
  }
  else { decomp = ZERO; }

  if( decomp < ZERO ) { decomp = ZERO; }


  // Adjust decomposition rate due to tillage effects
  
  if( 1 == tillflag )
  {
    decomp *= tillfactor;
  }


  // Determine production of DOC and DON
  
  DOMprod.carbon = decomp * DOCpar[pdcmnt];
                               
  if( DOMprod.carbon < ZERO ) 
  { 
    DOMprod.carbon = ZERO; 
  }
  
  
  // Determine Heterotrophic Respiration (microbe.rh)

  rh = decomp - DOMprod.carbon;
                   
  if( rh < ZERO ) { rh = ZERO; }


  // Determine amount of DON produced

  DOMprod.nitrogen = DOMprod.carbon * DONpar;


  // Determine gross N mineralization of soil organic matter

  grossnmin = gminFastxClm( soilorgc, soilorgn, rh );


  // Determine N immobilization

  if( actlayer > MINACTLAYERZ )
  {
    immnh4 = nimmFastxClm( pdcmnt,
                           nh4imm,
                           soilh2o,
                           (soilnh4+grossnmin),
                           decay, 
                           rh,
                           ksoil );
  }
  else
  {
    immnh4 = ZERO;
  }
  
  if( immnh4 < ZERO ) { immnh4 = ZERO; }


  immob = immnh4;


  // Determine Net N Mineralization (microbe.netnmin)

  if( grossnmin >= immob )
  {
    if( soilorgc > ZERO )
    {
      grossnmin *= (soilorgn / soilorgc)
                   * cnsoil[pdcmnt];

      immnh4 *= (soilorgn / soilorgc)
                * cnsoil[pdcmnt];

      immob *= (soilorgn / soilorgc)
               * cnsoil[pdcmnt];
    }
    else
    {
      grossnmin = ZERO;
      immnh4 = ZERO;
      immob = ZERO;
    }
  }
  else
  {
    if( soilorgn > ZERO )
    {
      grossnmin *= (soilorgc / soilorgn)
                   / cnsoil[pdcmnt];

      immnh4 *= (soilorgc / soilorgn)
                / cnsoil[pdcmnt];

      immob *= (soilorgc / soilorgn)
               / cnsoil[pdcmnt];
    }
    else
    {
      grossnmin = ZERO;
      immnh4 = ZERO;
      immob = ZERO;
    }
    

    if( immob > soilnh4 + nh4dep
         + grossnmin )
    {
      immob = soilnh4 + nh4dep + grossnmin;
    }
  }

  netnmin = grossnmin - immob;

  if( netnmin > soilorgn )
  {
    netnmin = soilorgn;
    
    grossnmin = netnmin + immob;
  }


  // Determine total amount of nitrogen released from soil 
  //   organic matter as a result of decomposition 
  
  ndecomp = netnmin + DOMprod.nitrogen;  

  // Determine rates of Nitrification (microbe.nitrif) and
  //  nitrate production (microbe.no3prod)

  nitrif = ZERO;
  no3prod = ZERO;

  relntrf = setNitrifStatus( pdcmnt );
  
  if( relntrf > ZERO )
  {

    nitrif = ntrfxclm( pdcmnt,
                       soilh2o,
                       soilnh4,
                       netnmin,
                       ksoil );

    if( nitrif > soilnh4 + nh4dep + netnmin - ammnvol )
    {
      nitrif = soilnh4 + nh4dep + netnmin - ammnvol;
    }
                                                                                                                           

    if( nitrif < ZERO ) 
    { 
      nitrif = ZERO; 
    }
    
    no3prod = nitrif;
  }
	
};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

double Tmicrobe60::yrkd( const int& nfeed,
                         const double& yrltrc,
                         const double& yrltrn,
                         const double& lcclnc )
{

  double yrkd;

  if( yrltrn <= 0.000001 ) 
  { 
    return  yrkd = ZERO; 
  }

  if( yrltrc < ZERO )
  {
    cout << "YRLTRC is < 0.0 in microbe.yrkd()" << endl;
    exit( -1 );
  }

  if( 0 == nfeed ) { yrkd = kdc; }
  else
  {
    yrkd = kdc * pow( (yrltrc/yrltrn), -0.784 )
           / pow( lcclnc, -0.784 );
  }

  return yrkd;
};

