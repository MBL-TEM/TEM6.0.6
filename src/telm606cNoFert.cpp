/* **************************************************************
*****************************************************************
TELM606CNOFERT.CPP - Runs TEM for a single grid cell.  Nitrogen
  fertilizers are never assumed to be applied to cropands.

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

****************************************************************
************************************************************* */

#include<cstdio>

  using std::fscanf;
  using std::FILE;
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

#include<iomanip>

  using std::setprecision;

#include<cstdlib>

  using std::exit;
  using std::atof;
  using std::atoi;

#include<cmath>

  using std::exp;
  using std::fabs;
  using std::pow;

#include<vector>

  using std::vector;
      
#include<cstring>

#include<string>
  
  using std::string;


#include "telm606cNoFert.h"

/* *************************************************************
************************************************************* */

TEMelmnt60::TEMelmnt60()
{

  col = MISSING;
  row = MISSING;
  carea = -999;
  subarea = -999;
  fatalerr = 0;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::atmswritemiss( ofstream fout[NUMATMS],
                                const vector<string>& predname,
                                const int& pdyr,
                                const int& natmspred,
                                const double value )
{

  int i;
  int dm;
  Clmdata60 atmspred;

  for( i = 0; i < natmspred; ++i )
  {
    for( dm = 0; dm <= CYCLE; ++dm )
    {
      atmspred.mon[dm] = value;
    }

	 atmspred.outdel( fout[i],
                          col,
                          row,
                          predname[i],
                          carea,
	                  atmstotyr[pdyr],
                          atmspred.mon,
                          region );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::atmswritepred( ofstream fout[NUMATMS],
                                const vector<string>& predname,
                                const int& natmspred )
{

  int i;
  int dm;
  Clmdata60 atmspred;

  // Covert cal/cm2/day to W/m2 (4.186 Joules / calorie)

  const double  cal2Watts = 0.4845;


  for( i = 0; i < natmspred; ++i )
  {
    if( predname.at( i ) == clm.predstr.at( clm.I_GIRR ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = climate[clm.I_GIRR][dm] * cal2Watts;
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_NIRR ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = climate[clm.I_NIRR][dm] * cal2Watts;
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_PAR ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = climate[clm.I_PAR][dm] * cal2Watts;
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_CLDS ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm ) 
      { 
        atmspred.mon[dm] = climate[clm.I_CLDS][dm]; 
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_TAIR ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm ) 
      { 
      	atmspred.mon[dm] = climate[clm.I_TAIR][dm]; 
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_PREC ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm ) 
      { 
      	atmspred.mon[dm] = climate[clm.I_PREC][dm]; 
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_RAIN ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm ) 
      { 
      	atmspred.mon[dm] = climate[clm.I_RAIN][dm]; 
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_SNWFAL ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm ) 
      { 
      	atmspred.mon[dm] = climate[clm.I_SNWFAL][dm]; 
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_AOT40 ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm ) 
      { 
      	atmspred.mon[dm] = climate[clm.I_AOT40][dm]; 
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_TNDEP ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = climate[clm.I_TNDEP][dm] * 1000.0;
      }
    }

    else if( predname.at( i ) == clm.predstr.at( clm.I_NH4DEP ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = climate[clm.I_NH4DEP][dm] * 1000.0;
      }
    }
    else if( predname.at( i ) == clm.predstr.at( clm.I_NO3DEP ) )
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = climate[clm.I_NO3DEP][dm] * 1000.0;
      }
    }
    else
    {
      for( dm = 0; dm <= CYCLE; ++dm )
      {
        atmspred.mon[dm] = MISSING;
      }
    }

    atmspred.outdel( fout[i],
                     col,
                     row,
                     predname[i],
                     carea,
                     year,
                     atmspred.mon,
                     region );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int TEMelmnt60::coregerr( ofstream& rflog1,
                          const string& varname1,
                          const double& col1,
                          const double& row1,
                          const string& varname2,
                          const double& col2,
                          const double& row2 )
{

  int fatalerr = 0;

  if( col1 != col2 || row1 != row2 )
  {
    fatalerr = 1;

    cout << "ERROR:  " << varname1 << " data and ";
    cout << varname2 << "data are not coregistered." << endl;
    cout << "COL = " << col1 << " and ROW = " << row1;
    cout << " in " << varname1 << " data" << endl;
    cout << "COL = " << col2 << " and ROW = " << row2;
    cout << " in " << varname2 << " data" << endl;

    rflog1 << "ERROR:  " << varname1 << " data and ";
    rflog1 << varname2 << "data are not coregistered." << endl;
    rflog1 << "COL = " << col1 << " and ROW = " << row1;
    rflog1 << " in " << varname1 << " data" << endl;
    rflog1 << "COL = " << col2 << " and ROW = " << row2;
    rflog1 << " in " << varname2 << " data" << endl;
  }

  return fatalerr;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

int TEMelmnt60::equilibrateTEM( const int& pichrt, 
                                const double& ptol, 
                                ofstream& rflog1 )
{
  // Run TEM until steady state conditions occur (equilibrium)

  int dyr = 0;
  int dm;

  // Initialize standing stocks of carbon and nitrogen from 
  //   calibration ("ECD") data and fluxes for integrator

  tem.ECDsetODEstate( tem.veg.cmnt, tem.soil.getPSIPLUSC() );

   
  // Set previous value of TEM ODE state variables to the 
  //   current values of TEM ODE state variables for initial
  //   conditions
 
  tem.setPrevState();


  // Initialize all disturbance fluxes to zero

  tem.ag.resetMonthlyDisturbFluxes();

  tem.ag.setFIRENTOTDEP( ZERO );
  tem.ag.setFIRENH4DEP( ZERO );
  tem.ag.setFIRENO3DEP( ZERO );


  // Initialize all agricultural and wood product pools to 
  //   zero

  tem.ag.resetPROD();


  tem.totyr = 0;
  tem.endeq = 0;
  tem.intflag = 0;
  tem.initFlag = 0;


  // Determine CDM for long-term mean climate data for 
  //   soil thermal calculations (STM)

  tem.soil.stm.updateyrCDM( climate[clm.I_TAIR] ); 


  // Initialize tem.atms.prevtair for water balance (WBM) and 
  //   soil thermal (STM) calculations
  
  tem.atms.setPREVTAIR( climate[clm.I_TAIR][CYCLE-1] );


  // Initialize tem.atms.prev2tair for water balance  
  //   calculations (WBM)

  tem.atms.setPREV2TAIR( climate[clm.I_TAIR][CYCLE-2] );

  
  // Initialize tem.atms.prevtair for water balance (WBM) and 
  //   soil thermal (STM) calculations
  
  tem.soil.setPREVSPACK( ZERO );
  
  
  // Initialize tem.soil.prevdst10 for GPP calculations
  
  tem.soil.setPREVDST10( ZERO );
  
  
  // Initialize tem.veg.prvleafmx and tem.veg.prevunrmleaf
  //   for phenology calculations
  
  tem.veg.setPRVLEAFMX( tem.veg.getINITLEAFMX( tem.veg.cmnt ) );
  
  tem.veg.setPREVUNRMLEAF( tem.veg.getUNLEAF12( tem.veg.cmnt ) );


  while( (dyr < tem.runsize) && (tem.endeq < 2) )
  {
    for( dm = 0; dm < CYCLE; ++dm )
    {
      // Assign telmnt[0].climate to TEM.atms
      
      tem.atms.setGIRR( climate[clm.I_GIRR][dm] );
      tem.atms.setCLDS( climate[clm.I_CLDS][dm] );
      tem.atms.setNIRR( climate[clm.I_NIRR][dm] );
      tem.atms.setPAR(  climate[clm.I_PAR][dm] );
      tem.atms.setTAIR( climate[clm.I_TAIR][dm] );
      tem.atms.setRAIN( climate[clm.I_RAIN][dm] );
      tem.atms.setSNOWFALL( climate[clm.I_SNWFAL][dm] );
      tem.atms.setCO2( climate[clm.I_CO2][dm] );
      tem.atms.setAOT40( climate[clm.I_AOT40][dm] );
      tem.atms.setTOTNDEP( climate[clm.I_TNDEP][dm] );
      tem.atms.setNH4DEP( climate[clm.I_NH4DEP][dm] );
      tem.atms.setNO3DEP( climate[clm.I_NO3DEP][dm] );

      tem.soil.stm.setNEXTTAIR( climate[clm.I_TAIR][dm+1] );
      tem.soil.stm.setNEXTSNOWFALL( climate[clm.I_SNWFAL][dm+1] );

      tem.soil.setNEXTDST10( cohort[pichrt].dst10[dm+1] );
      
      tem.endeq = tem.stepmonth( dyr, 
                                 dm, 
                                 tem.intflag, 
                                 ptol, 
                                 rflog1 );
     
 
      // Update telmnt[0].cohort.dst10 for future use 
      
      cohort[pichrt].dst10[dm] = tem.soil.getDST10();
      
      
      // Save TEM output to telmnt[0].output
      
      outputTEMmonth( dm );
    }

    ++dyr;
    ++tem.totyr;


// Check to see if steady state conditions have been reached.

    if( dyr >= tem.strteq && 0 == tem.endeq )
    {
      tem.endeq = tem.testEquilibrium();
    }
  }

  if( tem.totyr >= tem.runsize && tem.endeq < 2 ) 
  { 
    tem.nattempt += 1; 
    tem.initFlag = 0;
  }
  else { tem.initFlag = 1; }

  return tem.nattempt;

};
/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::getTEMCohortState( const int& pichrt, 
                                    const int& pdm )
{
  int dnode;
  int i;
  int kdm;

  tem.veg.setPOTVEG( cohort[pichrt].potveg );

  tem.veg.setCURRENTVEG( cohort[pichrt].currentveg );

  tem.veg.setSUBTYPE( cohort[pichrt].subtype );

  tem.veg.cmnt = cohort[pichrt].cmnt;

  for( i = 0; i < MAXSTATE; ++i )
  {
    tem.setY( cohort[pichrt].y[i], i );
    tem.setPREVY( cohort[pichrt].prevy[i], i );
  }

  tem.ag.cmnt = cohort[pichrt].agcmnt;

  tem.ag.setGROWDD( cohort[pichrt].aggrowdd );

  tem.ag.setKD( cohort[pichrt].agkd );

  tem.ag.prvstate = cohort[pichrt].agprvstate;

  tem.ag.state = cohort[pichrt].agstate;

  tem.veg.setC2N( cohort[pichrt].c2n );
  
  tem.veg.setCNEVEN( cohort[pichrt].cneven );

  tem.ag.setCONVRTFLXC( cohort[pichrt].convrtflx.carbon );
  tem.ag.setCONVRTFLXN( cohort[pichrt].convrtflx.nitrogen );

  tem.ag.setCROPPRVEETMX( cohort[pichrt].cropprveetmx );

  tem.ag.setCROPPRVLEAFMX( cohort[pichrt].cropprvleafmx );

  tem.ag.setCROPPRVPETMX( cohort[pichrt].cropprvpetmx );

  tem.ag.setCROPRESIDUEC( cohort[pichrt].cropResidue.carbon );
  tem.ag.setCROPRESIDUEN( cohort[pichrt].cropResidue.nitrogen );

  tem.ag.setCROPTOPT( cohort[pichrt].croptopt );

  tem.distmnthcnt = cohort[pichrt].distmnthcnt;
  
  tem.disturbflag = cohort[pichrt].disturbflag;

  tem.disturbmonth = cohort[pichrt].disturbmonth;
  
  if( (CYCLE-1) == pdm )
  {
    tem.soil.setNEXTDST10( cohort[pichrt].dst10[0] );
  }
  else 
  {
    tem.soil.setNEXTDST10( cohort[pichrt].dst10[pdm+1] );
  }

  tem.soil.setEETMX( cohort[pichrt].eetmx );

  tem.ag.fertflag = cohort[pichrt].fertflag;                              

  tem.firemnthcnt = cohort[pichrt].firemnthcnt; 
  
  tem.ag.setFIRENTOTDEP( cohort[pichrt].firendep.total );
  tem.ag.setFIRENH4DEP( cohort[pichrt].firendep.nh4 );
  tem.ag.setFIRENO3DEP( cohort[pichrt].firendep.no3 );
  
  tem.ag.setFORMPROD10C( cohort[pichrt].formPROD10.carbon );
  tem.ag.setFORMPROD10N( cohort[pichrt].formPROD10.nitrogen );

  tem.ag.setFORMPROD100C( cohort[pichrt].formPROD100.carbon );
  tem.ag.setFORMPROD100N( cohort[pichrt].formPROD100.nitrogen );

  tem.veg.setFPREVOZONE( cohort[pichrt].fprevozone );

  tem.ag.setFRI( cohort[pichrt].FRI );

  for( kdm = 0; kdm < CYCLE; ++kdm )
  {
    tem.ag.setINITPROD1C( cohort[pichrt].initPROD1[kdm].carbon,
                          kdm );
                          
    tem.ag.setINITPROD1N( cohort[pichrt].initPROD1[kdm].nitrogen,
                          kdm ); 
  }
  
  for( i = 0; i < 10; ++i )
  {
    tem.ag.setINITPROD10C( cohort[pichrt].initPROD10[i].carbon, i );
    tem.ag.setINITPROD10N( cohort[pichrt].initPROD10[i].nitrogen, i );
  }
    
  for( i = 0; i < 100; ++i )
  {
    tem.ag.setINITPROD100C( cohort[pichrt].initPROD100[i].carbon, i );
    tem.ag.setINITPROD100N( cohort[pichrt].initPROD100[i].nitrogen, i );
  }

  tem.ag.irrgflag = cohort[pichrt].irrgflag;                              
  
  tem.microbe.setKD( cohort[pichrt].kd );

  tem.ag.setNATPRVEETMX( cohort[pichrt].natprveetmx );

  tem.ag.setNATPRVLEAFMX( cohort[pichrt].natprvleafmx );

  tem.ag.setNATPRVPETMX( cohort[pichrt].natprvpetmx );

  tem.ag.setNATSEEDC( cohort[pichrt].natseedC );

  tem.ag.setNATSEEDSTRN( cohort[pichrt].natseedSTRN );

  tem.ag.setNATSEEDSTON( cohort[pichrt].natseedSTON );

  tem.ag.setNATSOIL( cohort[pichrt].natsoil );

  tem.ag.setNATTOPT( cohort[pichrt].nattopt );

  tem.ag.setNATYREET( cohort[pichrt].natyreet );

  tem.ag.setNATYRPET( cohort[pichrt].natyrpet );

  tem.veg.setNEWLEAFMX( cohort[pichrt].newleafmx );

  tem.veg.setNEWTOPT( cohort[pichrt].newtopt );

  tem.soil.setNSOLC( cohort[pichrt].nonsolc );

  tem.soil.setNSOLN( cohort[pichrt].nonsoln );

  tem.ag.setNTOTRETENT( cohort[pichrt].nretent.total );
  tem.ag.setNH4RETENT( cohort[pichrt].nretent.nh4 );
  tem.ag.setNO3RETENT( cohort[pichrt].nretent.no3 );

  tem.ag.setSNTOTRETENT( cohort[pichrt].nsretent.total );
  tem.ag.setSNH4RETENT( cohort[pichrt].nsretent.nh4 );
  tem.ag.setSNO3RETENT( cohort[pichrt].nsretent.no3 );

  tem.ag.setVNTOTRETENT( cohort[pichrt].nvretent.total );
  tem.ag.setVNH4RETENT( cohort[pichrt].nvretent.nh4 );
  tem.ag.setVNO3RETENT( cohort[pichrt].nvretent.no3 );

  tem.atms.setPETMX( cohort[pichrt].petmx );

  tem.atms.setPREV2TAIR( cohort[pichrt].prev2tair );

  tem.atms.setPREVCO2( cohort[pichrt].prevco2 );

  tem.ag.setPREVCROPRESIDUEC( cohort[pichrt].prevCropResidue.carbon );
  tem.ag.setPREVCROPRESIDUEN( cohort[pichrt].prevCropResidue.nitrogen );

  tem.soil.setPREVDST10( cohort[pichrt].prevdst10 );

  tem.ag.setPREVPROD1C( cohort[pichrt].prevPROD1.carbon );
  tem.ag.setPREVPROD1N( cohort[pichrt].prevPROD1.nitrogen );

  tem.ag.setPREVPROD10C( cohort[pichrt].prevPROD10.carbon );
  tem.ag.setPREVPROD10N( cohort[pichrt].prevPROD10.nitrogen );

  tem.ag.setPREVPROD100C( cohort[pichrt].prevPROD100.carbon );
  tem.ag.setPREVPROD100N( cohort[pichrt].prevPROD100.nitrogen );

  tem.soil.setPREVSPACK( cohort[pichrt].prevspack );

  tem.atms.setPREVTAIR( cohort[pichrt].prevtair );

  tem.veg.setPREVUNRMLEAF( cohort[pichrt].prevunrmleaf );

  tem.ag.setPROD10PAR( cohort[pichrt].prod10par ); 

  tem.ag.setPROD100PAR( cohort[pichrt].prod100par ); 

  tem.ag.setPRODUCTYEAR( cohort[pichrt].productYear );
 
  tem.ag.setPRVCROPNPP( cohort[pichrt].prvcropnpp );

  tem.soil.setPRVEETMX( cohort[pichrt].prveetmx );

  tem.veg.setPRVLEAFMX( cohort[pichrt].prvleafmx );

  tem.atms.setPRVPETMX( cohort[pichrt].prvpetmx );

  tem.ag.setSCONVERT( cohort[pichrt].sconvert ); 
  
  tem.ag.setSCONVRTFLXC( cohort[pichrt].sconvrtflx.carbon );
  tem.ag.setSCONVRTFLXN( cohort[pichrt].sconvrtflx.nitrogen );

  tem.ag.setSLASHC( cohort[pichrt].slash.carbon );
  tem.ag.setSLASHN( cohort[pichrt].slash.nitrogen );

  tem.ag.setSLASHPAR( cohort[pichrt].slashpar ); 

  tem.soil.stm.setDST0( cohort[pichrt].STMdst0 );

  tem.soil.stm.setDST5( cohort[pichrt].STMdst5 );

  tem.soil.setDST10( cohort[pichrt].STMdst10 );

  tem.soil.stm.setDST20( cohort[pichrt].STMdst20 );

  tem.soil.stm.setDST50( cohort[pichrt].STMdst50 );

  tem.soil.stm.setDST100( cohort[pichrt].STMdst100 );

  tem.soil.stm.setDST200( cohort[pichrt].STMdst200 );

  tem.soil.stm.setFRONTD( cohort[pichrt].STMfrontd );

  tem.soil.stm.setFRONTD2( cohort[pichrt].STMfrontd2 );

  tem.soil.stm.setIS9( cohort[pichrt].STMis9 );
  
  tem.soil.stm.setSMASS9( cohort[pichrt].STMsmass9 );

  tem.soil.stm.setTHAWBEGIN1( cohort[pichrt].STMthawbegin1 );

  tem.soil.stm.setTHAWBEGIN2( cohort[pichrt].STMthawbegin2 );

  tem.soil.stm.setTHAWEND1( cohort[pichrt].STMthawend1 );

  tem.soil.stm.setTHAWEND2( cohort[pichrt].STMthawend2 );

  tem.soil.setTSOIL( cohort[pichrt].STMtsoil );

 
  for( dnode = 0; dnode < MAXNODES; ++dnode )
  {
    tem.soil.stm.setDX9( cohort[pichrt].STMdx9[dnode], dnode ); 
     
    tem.soil.stm.setT9( cohort[pichrt].STMt9[dnode], dnode );  
    
    tem.soil.stm.setWATER9( cohort[pichrt].STMwater9[dnode], 
                            dnode );  
    
    tem.soil.stm.setX9( cohort[pichrt].STMx9[dnode], dnode );  

    tem.soil.stm.setXFA9( cohort[pichrt].STMxfa9[dnode], 
                          dnode );  

    tem.soil.stm.setXFB9( cohort[pichrt].STMxfb9[dnode], 
                          dnode );  
  }

  for( dnode = 0; dnode < MAXSNODES; ++dnode )
  {
    tem.soil.stm.setWEIGHT9( cohort[pichrt].STMweight9[dnode], 
                            dnode );  
  }
  
  tem.ag.tillflag = cohort[pichrt].tillflag;                           

  tem.veg.setTOPT( cohort[pichrt].topt );

  tem.ag.setVCONVERT( cohort[pichrt].vconvert ); 

  tem.ag.setVCONVRTFLXC( cohort[pichrt].vconvrtflx.carbon );
  tem.ag.setVCONVRTFLXN( cohort[pichrt].vconvrtflx.nitrogen );

  tem.ag.setVRESPAR( cohort[pichrt].vrespar ); 

  tem.soil.setWFPSOFF( cohort[pichrt].wfpsoff );
  
  tem.ag.setYRSTUBC( cohort[pichrt].yragstubC );
  
  tem.ag.setYRSTUBN( cohort[pichrt].yragstubN );

  tem.microbe.setYRAMMNVOL( cohort[pichrt].yrammonvol );
  
  tem.ag.setYRCFLUX( cohort[pichrt].yrcflux );
  
  tem.ag.setYRCONVRTC( cohort[pichrt].yrconvrtC );
  
  tem.ag.setYRCONVRTN( cohort[pichrt].yrconvrtN );
  
  tem.ag.setYRDECAYPROD1C( cohort[pichrt].yrdecayPROD1C );
  
  tem.ag.setYRDECAYPROD10C( cohort[pichrt].yrdecayPROD10C );
  
  tem.ag.setYRDECAYPROD100C( cohort[pichrt].yrdecayPROD100C );

  tem.ag.setYRDECAYPROD1N( cohort[pichrt].yrdecayPROD1N );
  
  tem.ag.setYRDECAYPROD10N( cohort[pichrt].yrdecayPROD10N );
  
  tem.ag.setYRDECAYPROD100N( cohort[pichrt].yrdecayPROD100N );
  
  tem.ag.setYRDECAYTOTPRODC( cohort[pichrt].yrdecayTOTPRODC );

  tem.ag.setYRDECAYTOTPRODN( cohort[pichrt].yrdecayTOTPRODN );
 
  tem.microbe.setYRDECOMP( cohort[pichrt].yrdecompC );

  tem.microbe.setYRNDECOMP( cohort[pichrt].yrdecompN );
  
  tem.microbe.setYRDENITRF( cohort[pichrt].yrdenitrif );

  tem.soil.setYRLCHDOC( cohort[pichrt].yrDOCleach );
  
  tem.microbe.setYRDOCPRD( cohort[pichrt].yrDOCprod );

  tem.soil.setYRLCHDON( cohort[pichrt].yrDONleach );
  
  tem.microbe.setYRDONPRD( cohort[pichrt].yrDONprod );
  
  tem.soil.setYREET( cohort[pichrt].yreet );
  
  tem.ag.setYRFERTN( cohort[pichrt].yrfertn );
  
  tem.ag.setYRFLUXRESIDUEC( cohort[pichrt].yrfluxResidueC );
  
  tem.ag.setYRFLUXRESIDUEN( cohort[pichrt].yrfluxResidueN );

  tem.ag.setYRFORMPROD1C( cohort[pichrt].yrformPROD1C );
  
  tem.ag.setYRFORMPROD10C( cohort[pichrt].yrformPROD10C );
  
  tem.ag.setYRFORMPROD100C( cohort[pichrt].yrformPROD100C );

  tem.ag.setYRFORMPROD1N( cohort[pichrt].yrformPROD1N );
  
  tem.ag.setYRFORMPROD10N( cohort[pichrt].yrformPROD10N );
  
  tem.ag.setYRFORMPROD100N( cohort[pichrt].yrformPROD100N );
  
  tem.ag.setYRFORMRESIDUEC( cohort[pichrt].yrformResidueC );
  
  tem.ag.setYRFORMRESIDUEN( cohort[pichrt].yrformResidueN );

  tem.ag.setYRFORMTOTPRODC( cohort[pichrt].yrformTOTPRODC );

  tem.ag.setYRFORMTOTPRODN( cohort[pichrt].yrformTOTPRODN );

  tem.veg.setYRFPC( cohort[pichrt].yrfpc );

  tem.microbe.setYRGMIN( cohort[pichrt].yrgmin );
  
  tem.veg.setYRGPP( cohort[pichrt].yrgpp );
  
  tem.veg.setYRGPR( cohort[pichrt].yrgpr );
  
  tem.soil.setYRH2OYIELD( cohort[pichrt].yrh2oyld );
  
  tem.microbe.setYRIMMB( cohort[pichrt].yrimmob );

  tem.soil.setYRABNIMMOB( cohort[pichrt].yrimmobabN );

  tem.microbe.setYRIMMNH4( cohort[pichrt].yrimmobNH4 );
  
  tem.soil.setYRINEET( cohort[pichrt].yrineet );
  
  tem.veg.setYRINGPP( cohort[pichrt].yringpp );
  
  tem.veg.setYRINNPP( cohort[pichrt].yrinnpp );
  
  tem.veg.setYRINNUP( cohort[pichrt].yrinnup );

  tem.veg.setYRINNH4UP( cohort[pichrt].yrinnupNH4 );

  tem.veg.setYRINNO3UP( cohort[pichrt].yrinnupNO3 );
  
  tem.ag.setYRIRRIG( cohort[pichrt].yrirrig );
  
  tem.veg.setYRLAI( cohort[pichrt].yrlai );
    
  tem.veg.setYRLEAF( cohort[pichrt].yrleaf );

  tem.veg.setYRLTRFALC( cohort[pichrt].yrltrfalc );

  tem.veg.setYRLTRFALN( cohort[pichrt].yrltrfaln );  	
  
  tem.soil.setYRN2FLX( cohort[pichrt].yrN2flx );
   
  tem.soil.setYRN2OFLX( cohort[pichrt].yrN2Oflx );

  tem.soil.setYRNH3FLX( cohort[pichrt].yrNH3flx );

  tem.soil.setYRNOFLX( cohort[pichrt].yrNOflx );
   
  tem.microbe.setYRN2PRD( cohort[pichrt].yrN2prd );
   
  tem.microbe.setYRN2OPRD( cohort[pichrt].yrN2Oprd );
 
  tem.setYRNCE( cohort[pichrt].yrnce );

  tem.atms.setYRTOTNDEP( cohort[pichrt].yrndep );
  
  tem.atms.setYRNH4DEP( cohort[pichrt].yrndepNH4 );
  
  tem.atms.setYRNO3DEP( cohort[pichrt].yrndepNO3 );
  
  tem.setYRNECB( cohort[pichrt].yrnecb );  

  tem.setYRNENB( cohort[pichrt].yrnenb );  

  tem.setYRNEP( cohort[pichrt].yrnep );
  
  tem.setYRBNFIX( cohort[pichrt].yrNfixBiol );

  tem.microbe.setYRNFIX( cohort[pichrt].yrNfixAsymb );

  tem.veg.setYRNFIX( cohort[pichrt].yrNfixSymb );
  
  tem.soil.setYRLCHNH4( cohort[pichrt].yrNH4leach );

  tem.soil.setYRNINPUT( cohort[pichrt].yrninput );

  tem.microbe.setYRNITRIF( cohort[pichrt].yrnitrif );
  
  tem.soil.setYRNLOST( cohort[pichrt].yrnlost );
  
  tem.microbe.setYRNMIN( cohort[pichrt].yrnmin );
    
  tem.microbe.setYRNOPRD( cohort[pichrt].yrNOprd );
  
  tem.soil.setYRLCHNO3( cohort[pichrt].yrNO3leach );

  tem.microbe.setYRNO3PRD( cohort[pichrt].yrNO3prd );
  
  tem.veg.setYRNPP( cohort[pichrt].yrnpp );
  
  tem.ag.setYRNRENT( cohort[pichrt].yrnrent ); 
  
  tem.ag.setYRNSRENT( cohort[pichrt].yrnsrent );
  
  tem.veg.setYRNUP( cohort[pichrt].yrnup );

  tem.veg.setYRNH4UP( cohort[pichrt].yrnupNH4 );

  tem.veg.setYRNO3UP( cohort[pichrt].yrnupNO3 );

  tem.ag.setYRNVRENT( cohort[pichrt].yrnvrent );
  
  tem.atms.setYRPET( cohort[pichrt].yrpet );
  
  tem.soil.setYRERODEPOC( cohort[pichrt].yrPOCerode );

  tem.soil.setYRERODEPON( cohort[pichrt].yrPONerode );
  
  tem.soil.setYRRGRNDH2O( cohort[pichrt].yrrgrndh2o ); 
  
  tem.microbe.setYRRH( cohort[pichrt].yrrh );
    
  tem.atms.setYRRAIN( cohort[pichrt].yrrain );
  
  tem.soil.setYRRPERC( cohort[pichrt].yrrperc );
  
  tem.soil.setYRRRUN( cohort[pichrt].yrrrun );

  tem.ag.setYRSCONVRTC( cohort[pichrt].yrsconvrtC );

  tem.ag.setYRCONVRTN( cohort[pichrt].yrsconvrtN );
  
  tem.soil.setYRSGRNDH2O( cohort[pichrt].yrsgrndh2o );

  tem.ag.setYRSLASHC( cohort[pichrt].yrslashC );

  tem.ag.setYRSLASHN( cohort[pichrt].yrslashN );
  
  tem.atms.setYRSNOWFALL( cohort[pichrt].yrsnowfall );

  tem.soil.setYRSNOWINF( cohort[pichrt].yrsnowinf );

  tem.soil.setYRSNOWPACK( cohort[pichrt].yrsnowpack );
  
  tem.soil.setYRAVLH2O( cohort[pichrt].yrsoilavlH2O );
  
  tem.soil.setYRAVLN( cohort[pichrt].yrsoilavlN );

  tem.soil.setYRAVLNH4( cohort[pichrt].yrsoilavlNH4 );

  tem.soil.setYRAVLNO3( cohort[pichrt].yrsoilavlNO3 );
  
  tem.soil.setYRDOC( cohort[pichrt].yrsoilDOC );
  
  tem.soil.setYRDON( cohort[pichrt].yrsoilDON );
  
  tem.soil.setYRSMOIST( cohort[pichrt].yrsoilmoist );
  
  tem.soil.setYRNONORGC( cohort[pichrt].yrsoilnonorgC );
  
  tem.soil.setYRNONORGN( cohort[pichrt].yrsoilnonorgN );
  
  tem.soil.setYRORGC( cohort[pichrt].yrsoilorgC );
  
  tem.soil.setYRORGN( cohort[pichrt].yrsoilorgN );

  tem.soil.setYRPCTP( cohort[pichrt].yrsoilpctp );
  
  tem.setYRRSOIL( cohort[pichrt].yrsoilResp );
  
  tem.soil.setYRTOTORGC( cohort[pichrt].yrsoiltotorgC );

  tem.soil.setYRTOTORGN( cohort[pichrt].yrsoiltotorgN );
  
  tem.soil.setYRVSM( cohort[pichrt].yrsoilvsm );

  tem.soil.setYRSPERC( cohort[pichrt].yrsperc );
  
  tem.soil.setSRUN( cohort[pichrt].yrsrun );

  tem.soil.stm.setYRDST0( cohort[pichrt].yrSTMdst0 );

  tem.soil.stm.setYRDST5( cohort[pichrt].yrSTMdst5 );

  tem.soil.setYRDST10( cohort[pichrt].yrSTMdst10 );

  tem.soil.stm.setYRDST20( cohort[pichrt].yrSTMdst20 );

  tem.soil.stm.setYRDST50( cohort[pichrt].yrSTMdst50 );

  tem.soil.stm.setYRDST100( cohort[pichrt].yrSTMdst100 );

  tem.soil.stm.setYRDST200( cohort[pichrt].yrSTMdst200 );

  tem.soil.stm.setYRFRONTD( cohort[pichrt].yrSTMfrontd );

  tem.soil.stm.setYRFRONTD2( cohort[pichrt].yrSTMfrontd2 );

  tem.soil.stm.setYRTHAWBEGIN1( cohort[pichrt].yrSTMthawbegin1 );

  tem.soil.stm.setYRTHAWBEGIN2( cohort[pichrt].yrSTMthawbegin2 );

  tem.soil.stm.setYRTHAWEND1( cohort[pichrt].yrSTMthawend1 );

  tem.soil.stm.setYRTHAWEND2( cohort[pichrt].yrSTMthawend2 );

  tem.soil.setYRTSOIL( cohort[pichrt].yrSTMtsoil );
     
  tem.veg.setYRTHAWPCT( cohort[pichrt].yrthawpct );
  
  tem.setYRTOTALC( cohort[pichrt].yrtotalC );
  
  tem.veg.setYRUNLEAF( cohort[pichrt].yrunleaf );

  tem.ag.setYRVCONVRTC( cohort[pichrt].yrvconvrtC );
  
  tem.ag.setYRCONVRTN( cohort[pichrt].yrvconvrtN );

  tem.veg.setYRABVGRNDRESP( cohort[pichrt].yrvegabvgrndResp );
  
  tem.veg.setYRVEGC( cohort[pichrt].yrvegC );
    
  tem.veg.setYRLUP( cohort[pichrt].yrveglup );

  tem.veg.setYRVEGN( cohort[pichrt].yrvegN );

  tem.veg.setYRNMOBIL( cohort[pichrt].yrvegnmobil );

  tem.veg.setYRNRSORB( cohort[pichrt].yrvegnrsorb );

  tem.veg.setYRRGROWTH( cohort[pichrt].yrvegrgrowth );

  tem.veg.setYRRMAINT( cohort[pichrt].yrvegrmaint );

  tem.veg.setYRROOTRESP( cohort[pichrt].yrvegrootResp );
  
  tem.veg.setYRSTOREN( cohort[pichrt].yrvegstoN );
  
  tem.veg.setYRSTRUCTN( cohort[pichrt].yrvegstrN );

  tem.veg.setYRSUP( cohort[pichrt].yrvegsup );
	
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TEMelmnt60::initializeCohortTEMState( const int& pichrt )
{
  int dm;
  int dnode;
  int i;

  for( i = 0; i < MAXSTATE; ++i )
  {
    cohort[pichrt].y[i] = ZERO;
    cohort[pichrt].prevy[i] = ZERO;
  }

  cohort[pichrt].aggrowdd = ZERO;

  cohort[pichrt].agkd = ZERO;

  cohort[pichrt].c2n = ZERO;

  cohort[pichrt].cneven = ZERO;
  
  cohort[pichrt].convrtflx.carbon = ZERO;
  cohort[pichrt].convrtflx.nitrogen = ZERO;

  cohort[pichrt].cropprveetmx = ZERO;

  cohort[pichrt].cropprvleafmx = ZERO;

  cohort[pichrt].cropprvpetmx = ZERO;

  cohort[pichrt].cropResidue.carbon = ZERO;
  cohort[pichrt].cropResidue.nitrogen = ZERO;

  cohort[pichrt].croptopt = ZERO;

  cohort[pichrt].distmnthcnt = 0;

  
  for( dm = 0; dm < CYCLE; ++dm )
  {
    cohort[pichrt].dst10[dm] = ZERO;
  }
 
  cohort[pichrt].eetmx = ZERO;

  cohort[pichrt].firemnthcnt = 0;
  
  cohort[pichrt].firendep.total = ZERO;
  cohort[pichrt].firendep.nh4 = ZERO;
  cohort[pichrt].firendep.no3 = ZERO;
                           
  cohort[pichrt].formPROD10.carbon = ZERO;
  cohort[pichrt].formPROD10.nitrogen = ZERO;
  
  cohort[pichrt].formPROD100.carbon = ZERO;
  cohort[pichrt].formPROD100.nitrogen = ZERO;
  
  cohort[pichrt].fprevozone = ZERO;

  for( dm = 0; dm < CYCLE; ++dm )
  {
    cohort[pichrt].initPROD1[dm].carbon = ZERO;
    cohort[pichrt].initPROD1[dm].nitrogen = ZERO;
  }
    
  for( i = 0; i < 10; ++i )
  {
    cohort[pichrt].initPROD10[i].carbon = ZERO; 
    cohort[pichrt].initPROD10[i].nitrogen = ZERO;
  }
    
  for( i = 0; i < 100; ++i )
  {
    cohort[pichrt].initPROD100[i].carbon = ZERO;
    cohort[pichrt].initPROD100[i].nitrogen = ZERO;
  }                            
 
  cohort[pichrt].kd = ZERO;

  cohort[pichrt].natprveetmx = ZERO;

  cohort[pichrt].natprvleafmx = ZERO;

  cohort[pichrt].natprvpetmx = ZERO;

  cohort[pichrt].natseedC = ZERO;

  cohort[pichrt].natseedSTRN = ZERO;

  cohort[pichrt].natseedSTON = ZERO;

  cohort[pichrt].natsoil = ZERO;

  cohort[pichrt].nattopt = ZERO;

  cohort[pichrt].natyreet = ZERO;

  cohort[pichrt].natyrpet= ZERO;

  cohort[pichrt].newleafmx = ZERO;

  cohort[pichrt].newtopt = ZERO;

  cohort[pichrt].nonsolc = ZERO;

  cohort[pichrt].nonsoln = ZERO;

  cohort[pichrt].nretent.total = ZERO;
  cohort[pichrt].nretent.nh4 = ZERO;
  cohort[pichrt].nretent.no3 = ZERO;

  cohort[pichrt].nsretent.total = ZERO;
  cohort[pichrt].nsretent.nh4 = ZERO;
  cohort[pichrt].nsretent.no3 = ZERO;

  cohort[pichrt].nvretent.total = ZERO;
  cohort[pichrt].nvretent.nh4 = ZERO;
  cohort[pichrt].nvretent.no3 = ZERO;

  cohort[pichrt].petmx = ZERO;

  cohort[pichrt].prev2tair = ZERO;

  cohort[pichrt].prevco2 = ZERO;

  cohort[pichrt].prevCropResidue.carbon = ZERO;
  cohort[pichrt].prevCropResidue.nitrogen = ZERO;
  
  cohort[pichrt].prevdst10 = ZERO;

  cohort[pichrt].prevPROD1.carbon = ZERO; 
  cohort[pichrt].prevPROD1.nitrogen = ZERO;
  
  cohort[pichrt].prevPROD10.carbon = ZERO; 
  cohort[pichrt].prevPROD10.nitrogen = ZERO;
  
  cohort[pichrt].prevPROD100.carbon = ZERO;
  cohort[pichrt].prevPROD100.nitrogen = ZERO;

  cohort[pichrt].prevspack = ZERO;

  cohort[pichrt].prevtair = ZERO;
  
  cohort[pichrt].prevunrmleaf = ZERO;

  cohort[pichrt].productYear = 0;
   
  cohort[pichrt].prvcropnpp = ZERO;

  cohort[pichrt].prveetmx = ZERO;

  cohort[pichrt].prvleafmx = ZERO;

  cohort[pichrt].prvpetmx = ZERO;

  cohort[pichrt].qc = 0;

  cohort[pichrt].sconvrtflx.carbon = ZERO;
  cohort[pichrt].sconvrtflx.nitrogen = ZERO;

  cohort[pichrt].slash.carbon = ZERO;
  cohort[pichrt].slash.nitrogen = ZERO;                       

  cohort[pichrt].STMdst0 = ZERO;

  cohort[pichrt].STMdst5 = ZERO;

  cohort[pichrt].STMdst10 = ZERO;

  cohort[pichrt].STMdst20 = ZERO;

  cohort[pichrt].STMdst50 = ZERO;

  cohort[pichrt].STMdst100 = ZERO;

  cohort[pichrt].STMdst200 = ZERO;

  cohort[pichrt].STMfrontd = ZERO;

  cohort[pichrt].STMfrontd2 = ZERO;

  cohort[pichrt].STMis9 = 0;
  
  cohort[pichrt].STMsmass9 = ZERO;
 
  cohort[pichrt].STMthawbegin1 = ZERO;

  cohort[pichrt].STMthawbegin2 = ZERO;

  cohort[pichrt].STMthawend1 = ZERO;

  cohort[pichrt].STMthawend2 = ZERO;

  cohort[pichrt].STMtsoil = ZERO;
 
  for( dnode = 0; dnode < MAXNODES; ++dnode )
  {
    cohort[pichrt].STMdx9[dnode] = ZERO; 
     
    cohort[pichrt].STMt9[dnode] = ZERO;  
    
    cohort[pichrt].STMwater9[dnode] = ZERO;  
    
    cohort[pichrt].STMx9[dnode] = ZERO;  

    cohort[pichrt].STMxfa9[dnode] = ZERO;  

    cohort[pichrt].STMxfb9[dnode] = ZERO;  
  }

  for( dnode = 0; dnode < MAXSNODES; ++dnode )
  {
    cohort[pichrt].STMweight9[dnode] = MISSING;  
  }


  cohort[pichrt].topt = ZERO;

  cohort[pichrt].tqc = 0;

  cohort[pichrt].vconvrtflx.carbon = ZERO;
  cohort[pichrt].vconvrtflx.nitrogen = ZERO; 

  cohort[pichrt].yragstubC = ZERO;
  
  cohort[pichrt].yragstubN = ZERO;

  cohort[pichrt].yrammonvol = ZERO;
  
  cohort[pichrt].yrcflux = ZERO;
  
  cohort[pichrt].yrconvrtC = ZERO;
  
  cohort[pichrt].yrconvrtN = ZERO;
  
  cohort[pichrt].yrdecayPROD1C = ZERO;
  
  cohort[pichrt].yrdecayPROD10C = ZERO;
  
  cohort[pichrt].yrdecayPROD100C = ZERO;

  cohort[pichrt].yrdecayPROD1N = ZERO;
  
  cohort[pichrt].yrdecayPROD10N = ZERO;
  
  cohort[pichrt].yrdecayPROD100N = ZERO;
  
  cohort[pichrt].yrdecayTOTPRODC = ZERO;

  cohort[pichrt].yrdecayTOTPRODN = ZERO;
 
  cohort[pichrt].yrdecompC = ZERO;

  cohort[pichrt].yrdecompN = ZERO;
  
  cohort[pichrt].yrdenitrif = ZERO;

  cohort[pichrt].yrDOCleach = ZERO;
  
  cohort[pichrt].yrDOCprod = ZERO;

  cohort[pichrt].yrDONleach = ZERO;
  
  cohort[pichrt].yrDONprod = ZERO;
  
  cohort[pichrt].yreet = ZERO;
  
  cohort[pichrt].yrfertn = ZERO;
  
  cohort[pichrt].yrfluxResidueC = ZERO;
  
  cohort[pichrt].yrfluxResidueN = ZERO;

  cohort[pichrt].yrformPROD1C = ZERO;
  
  cohort[pichrt].yrformPROD10C = ZERO;
  
  cohort[pichrt].yrformPROD100C = ZERO;

  cohort[pichrt].yrformPROD1N = ZERO;
  
  cohort[pichrt].yrformPROD10N = ZERO;
  
  cohort[pichrt].yrformPROD100N = ZERO;
  
  cohort[pichrt].yrformResidueC = ZERO;
  
  cohort[pichrt].yrformResidueN = ZERO;

  cohort[pichrt].yrformTOTPRODC = ZERO;

  cohort[pichrt].yrformTOTPRODN = ZERO;

  cohort[pichrt].yrfpc = ZERO;

  cohort[pichrt].yrgmin = ZERO;
  
  cohort[pichrt].yrgpp = ZERO;
  
  cohort[pichrt].yrgpr = ZERO;
  
  cohort[pichrt].yrh2oyld = ZERO;
  
  cohort[pichrt].yrimmob = ZERO;

  cohort[pichrt].yrimmobabN = ZERO;

  cohort[pichrt].yrimmobNH4 = ZERO;
  
  cohort[pichrt].yrineet = ZERO;
  
  cohort[pichrt].yringpp = ZERO;
  
  cohort[pichrt].yrinnpp = ZERO;
  
  cohort[pichrt].yrinnup = ZERO;

  cohort[pichrt].yrinnupNH4 = ZERO;

  cohort[pichrt].yrinnupNO3 = ZERO;
  
  cohort[pichrt].yrirrig = ZERO;
  
  cohort[pichrt].yrlai = ZERO;
    
  cohort[pichrt].yrleaf = ZERO;

  cohort[pichrt].yrltrfalc = ZERO;

  cohort[pichrt].yrltrfaln = ZERO;	
  
  cohort[pichrt].yrN2flx = ZERO;
   
  cohort[pichrt].yrN2Oflx = ZERO;

  cohort[pichrt].yrNH3flx = ZERO;

  cohort[pichrt].yrNOflx = ZERO;
   
  cohort[pichrt].yrN2prd = ZERO;
   
  cohort[pichrt].yrN2Oprd = ZERO;
 
  cohort[pichrt].yrnce = ZERO;

  cohort[pichrt].yrndep = ZERO;
  
  cohort[pichrt].yrndepNH4 = ZERO;
  
  cohort[pichrt].yrndepNO3 = ZERO;
  
  cohort[pichrt].yrnecb = ZERO; 

  cohort[pichrt].yrnenb = ZERO;  

  cohort[pichrt].yrnep = ZERO;
  
  cohort[pichrt].yrNfixBiol = ZERO;

  cohort[pichrt].yrNfixAsymb = ZERO;

  cohort[pichrt].yrNfixSymb = ZERO;
  
  cohort[pichrt].yrNH4leach = ZERO;

  cohort[pichrt].yrninput = ZERO;

  cohort[pichrt].yrnitrif = ZERO;
  
  cohort[pichrt].yrnlost = ZERO;
  
  cohort[pichrt].yrnmin = ZERO;
    
  cohort[pichrt].yrNOprd = ZERO;
  
  cohort[pichrt].yrNO3leach = ZERO;

  cohort[pichrt].yrNO3prd = ZERO;
  
  cohort[pichrt].yrnpp = ZERO;
  
  cohort[pichrt].yrnrent.total = ZERO; 
  cohort[pichrt].yrnrent.nh4 = ZERO;
  cohort[pichrt].yrnrent.no3 = ZERO;
  
  cohort[pichrt].yrnsrent.total = ZERO;
  cohort[pichrt].yrnsrent.nh4 = ZERO;
  cohort[pichrt].yrnsrent.no3 = ZERO;
  
  cohort[pichrt].yrnup = ZERO;

  cohort[pichrt].yrnupNH4 = ZERO;

  cohort[pichrt].yrnupNO3 = ZERO;

  cohort[pichrt].yrnvrent.total = ZERO;
  cohort[pichrt].yrnvrent.nh4 = ZERO;
  cohort[pichrt].yrnvrent.no3 = ZERO;
  
  cohort[pichrt].yrpet = ZERO;
  
  cohort[pichrt].yrPOCerode = ZERO;

  cohort[pichrt].yrPONerode = ZERO;
  
  cohort[pichrt].yrrgrndh2o = ZERO; 
  
  cohort[pichrt].yrrh = ZERO;
    
  cohort[pichrt].yrrain = ZERO;
  
  cohort[pichrt].yrrperc = ZERO;
  
  cohort[pichrt].yrrrun = ZERO;

  cohort[pichrt].yrsconvrtC = ZERO;

  cohort[pichrt].yrsconvrtN = ZERO;
  
  cohort[pichrt].yrsgrndh2o = ZERO;

  cohort[pichrt].yrslashC = ZERO;

  cohort[pichrt].yrslashN = ZERO;
  
  cohort[pichrt].yrsnowfall = ZERO;

  cohort[pichrt].yrsnowinf = ZERO;

  cohort[pichrt].yrsnowpack = ZERO;
  
  cohort[pichrt].yrsoilavlH2O = ZERO;
  
  cohort[pichrt].yrsoilavlN = ZERO;

  cohort[pichrt].yrsoilavlNH4 = ZERO;

  cohort[pichrt].yrsoilavlNO3 = ZERO;
  
  cohort[pichrt].yrsoilDOC = ZERO;
  
  cohort[pichrt].yrsoilDON = ZERO;
  
  cohort[pichrt].yrsoilmoist = ZERO;
  
  cohort[pichrt].yrsoilnonorgC = ZERO;
  
  cohort[pichrt].yrsoilnonorgN = ZERO;
  
  cohort[pichrt].yrsoilorgC = ZERO;
  
  cohort[pichrt].yrsoilorgN = ZERO;

  cohort[pichrt].yrsoilpctp = ZERO;
  
  cohort[pichrt].yrsoilResp = ZERO;
  
  cohort[pichrt].yrsoiltotorgC = ZERO;

  cohort[pichrt].yrsoiltotorgN = ZERO;
  
  cohort[pichrt].yrsoilvsm = ZERO;

  cohort[pichrt].yrsperc = ZERO;
  
  cohort[pichrt].yrsrun = ZERO;

  cohort[pichrt].yrSTMdst0 = ZERO;

  cohort[pichrt].yrSTMdst5 = ZERO;

  cohort[pichrt].yrSTMdst10 = ZERO;

  cohort[pichrt].yrSTMdst20 = ZERO;

  cohort[pichrt].yrSTMdst50 = ZERO;

  cohort[pichrt].yrSTMdst100 = ZERO;

  cohort[pichrt].yrSTMdst200 = ZERO;

  cohort[pichrt].yrSTMfrontd = ZERO;

  cohort[pichrt].yrSTMfrontd2 = ZERO;

  cohort[pichrt].yrSTMthawbegin1 = ZERO;

  cohort[pichrt].yrSTMthawbegin2 = ZERO;

  cohort[pichrt].yrSTMthawend1 = ZERO;

  cohort[pichrt].yrSTMthawend2 = ZERO;

  cohort[pichrt].yrSTMtsoil = ZERO;
     
  cohort[pichrt].yrthawpct = ZERO;
  
  cohort[pichrt].yrtotalC = ZERO;
  
  cohort[pichrt].yrunleaf = ZERO;

  cohort[pichrt].yrvconvrtC = ZERO;
  
  cohort[pichrt].yrvconvrtN = ZERO;

  cohort[pichrt].yrvegabvgrndResp = ZERO;
  
  cohort[pichrt].yrvegC = ZERO;
    
  cohort[pichrt].yrveglup = ZERO;

  cohort[pichrt].yrvegN = ZERO;

  cohort[pichrt].yrvegnmobil = ZERO;

  cohort[pichrt].yrvegnrsorb = ZERO;

  cohort[pichrt].yrvegrgrowth = ZERO;

  cohort[pichrt].yrvegrmaint = ZERO;

  cohort[pichrt].yrvegrootResp = ZERO;
  
  cohort[pichrt].yrvegstoN = ZERO;
  
  cohort[pichrt].yrvegstrN = ZERO;

  cohort[pichrt].yrvegsup = ZERO;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TEMelmnt60::outputTEMmonth( const int& pdm )
{

  // Ecosystem carbon pools determined in integrator

  output[tem.I_VEGC][pdm] = tem.getY( tem.I_VEGC );

  output[tem.I_SOLC][pdm] = tem.getY( tem.I_SOLC );

  output[tem.I_DOC][pdm] = tem.getY( tem.I_DOC );
                                         
  // Ecosystem nitrogen pools determined in integrator

  output[tem.I_STRN][pdm] = tem.getY( tem.I_STRN );

  output[tem.I_STON][pdm] = tem.getY( tem.I_STON );

  output[tem.I_SOLN][pdm] = tem.getY( tem.I_SOLN );
      
  output[tem.I_DON][pdm] = tem.getY( tem.I_DON );

  output[tem.I_NH4][pdm] = tem.getY( tem.I_NH4 );

  output[tem.I_NO3][pdm] = tem.getY( tem.I_NO3 );
  
  // Ecosystem water pools determined in integrator

  output[tem.I_AVLW][pdm] = (tem.getY( tem.I_SM ) 
                            * tem.soil.getACTLAYER() / tem.soil.getROOTZ())
                            - tem.soil.getWILTPT();

  if( output[tem.I_AVLW][pdm] < ZERO )
  {
    output[tem.I_AVLW][pdm] = ZERO;
  }

  output[tem.I_SM][pdm] = tem.getY( tem.I_SM );

  output[tem.I_VSM][pdm] = tem.getY( tem.I_SM )
                           / (tem.soil.getROOTZ() * 1000.0);

  output[tem.I_PCTP][pdm] = (tem.getY( tem.I_SM )
                            * tem.soil.getACTLAYER() / tem.soil.getROOTZ())
                            / tem.soil.getTOTPOR();

  output[tem.I_RGRW][pdm] = tem.getY( tem.I_RGRW );

  output[tem.I_SGRW][pdm] = tem.getY(tem.I_SGRW );

  // Monthly phenology determined in integrator

  output[tem.I_UNRMLF][pdm] = tem.getY( tem.I_UNRMLF );

  output[tem.I_LEAF][pdm] = tem.getY( tem.I_LEAF );

  output[tem.I_LAI][pdm] = tem.getY( tem.I_LAI );

  output[tem.I_FPC][pdm] = tem.getY( tem.I_FPC );

  // Monthly carbon fluxes in ecosystems determined in integrator

  output[tem.I_INGPP][pdm] = tem.getY( tem.I_INGPP );

  output[tem.I_GPP][pdm] = tem.getY( tem.I_GPP );

  output[tem.I_FOZONE][pdm] = tem.getY( tem.I_FOZONE );

  output[tem.I_FINDOZONE][pdm] = tem.getY( tem.I_FINDOZONE );

  output[tem.I_INNPP][pdm] = tem.getY( tem.I_INNPP );

  output[tem.I_NPP][pdm] = tem.getY( tem.I_NPP );

  output[tem.I_GPR][pdm] = tem.getY( tem.I_GPR );

  output[tem.I_RVMNT][pdm] = tem.getY( tem.I_RVMNT );

  output[tem.I_RVGRW][pdm] = tem.getY( tem.I_RVGRW );

  output[tem.I_ABVGPR][pdm] = tem.getY( tem.I_ABVGPR );

  output[tem.I_ROOTGPR][pdm] = tem.getY( tem.I_ROOTGPR );

  output[tem.I_LTRFALC][pdm] = tem.getY( tem.I_LTRFALC );

  output[tem.I_CDCMP][pdm] = tem.getY( tem.I_CDCMP );

  output[tem.I_RH][pdm] = tem.getY( tem.I_RH );

  output[tem.I_DOCP][pdm] = tem.getY( tem.I_DOCP );

  output[tem.I_LCHDOC][pdm] = tem.getY( tem.I_LCHDOC );

  // Monthly nitrogen fluxes in ecosystems determined in 
  //   integrator

  output[tem.I_AGFRTN][pdm] = tem.getY( tem.I_AGFRTN );

  output[tem.I_BNFIX][pdm] = tem.getY( tem.I_BNFIX );

  output[tem.I_SNFIX][pdm] = tem.getY( tem.I_SNFIX );

  output[tem.I_ANFIX][pdm] = tem.getY( tem.I_ANFIX );

  output[tem.I_INNUP][pdm] = tem.getY( tem.I_INNUP );

  output[tem.I_INNH4UP][pdm] = tem.getY( tem.I_INNH4UP );

  output[tem.I_INNO3UP][pdm] = tem.getY( tem.I_INNO3UP );

  output[tem.I_VNUP][pdm] = tem.getY( tem.I_VNUP );

  output[tem.I_VNH4UP][pdm] = tem.getY( tem.I_VNH4UP );

  output[tem.I_VNO3UP][pdm] = tem.getY( tem.I_VNO3UP );

  output[tem.I_VSUP][pdm] = tem.getY( tem.I_VSUP );

  output[tem.I_VLUP][pdm] = tem.getY( tem.I_VLUP );

  output[tem.I_VNMBL][pdm] = tem.getY( tem.I_VNMBL );

  output[tem.I_VNRSRB][pdm] = tem.getY( tem.I_VNRSRB );

  output[tem.I_LTRFALN][pdm] = tem.getY( tem.I_LTRFALN );

  output[tem.I_NDCMP][pdm] = tem.getY( tem.I_NDCMP );

  output[tem.I_DONP][pdm] = tem.getY( tem.I_DONP );

  output[tem.I_GMIN][pdm] = tem.getY( tem.I_GMIN );

  output[tem.I_NH4IMM][pdm] = tem.getY( tem.I_NH4IMM );

  output[tem.I_NIMM][pdm] = tem.getY( tem.I_NIMM );

  output[tem.I_NMIN][pdm] = tem.getY( tem.I_NMIN );

  output[tem.I_AIMMNH4][pdm] = tem.getY( tem.I_AIMMNH4 );

  output[tem.I_AIMMNO3][pdm] = tem.getY( tem.I_AIMMNO3 );

  output[tem.I_AMMN][pdm] = tem.getY( tem.I_AMMN );

  output[tem.I_NTRF][pdm] = tem.getY( tem.I_NTRF );

  output[tem.I_NO3P][pdm] = tem.getY( tem.I_NO3P );

  output[tem.I_NOP][pdm] = tem.getY( tem.I_NOP );

  output[tem.I_N2OP][pdm] = tem.getY( tem.I_N2OP );

  output[tem.I_N2P][pdm] = tem.getY( tem.I_N2P );

  output[tem.I_DNTRF][pdm] = tem.getY( tem.I_DNTRF );

  output[tem.I_NH3FLX][pdm] = tem.getY( tem.I_NH3FLX );

  output[tem.I_NOFLX][pdm] = tem.getY( tem.I_NOFLX );

  output[tem.I_N2OFLX][pdm] = tem.getY( tem.I_N2OFLX );

  output[tem.I_N2FLX][pdm] = tem.getY( tem.I_N2FLX );

  output[tem.I_LCHNH4][pdm] = tem.getY( tem.I_LCHNH4 );

  output[tem.I_LCHNO3][pdm] = tem.getY( tem.I_LCHNO3 );

  output[tem.I_LCHDON][pdm] = tem.getY( tem.I_LCHDON );

  // Monthly water fluxes in ecosystems

  output[tem.I_AGIRRIG][pdm] = tem.getY( tem.I_AGIRRIG );

  output[tem.I_INEET][pdm] = tem.getY( tem.I_INEET );

  output[tem.I_EET][pdm] = tem.getY( tem.I_EET );

  output[tem.I_RPERC][pdm] = tem.getY( tem.I_RPERC );

  output[tem.I_SPERC][pdm] = tem.getY( tem.I_SPERC );

  output[tem.I_RRUN][pdm] = tem.getY( tem.I_RRUN );

  output[tem.I_SRUN][pdm] = tem.getY( tem.I_SRUN );

  // Other ecosystem carbon pools

  output[tem.I_NSOLC][pdm] = tem.soil.getNSOLC();

  output[tem.I_TSOLC][pdm] = tem.soil.getTSOLC();

  output[tem.I_TOTEC][pdm] = tem.ag.getTOTEC();

  output[tem.I_TOTC][pdm] = tem.getTOTALC();

  // Other ecosystem nitrogen pools

  output[tem.I_VEGN][pdm] = tem.veg.getVEGN();

  output[tem.I_NSOLN][pdm] = tem.soil.getNSOLN();

  output[tem.I_TSOLN][pdm] = tem.soil.getTSOLN();

  output[tem.I_AVLN][pdm] = tem.soil.getAVLN();

  // Other ecosystem water pools
  
  output[tem.I_SNWPCK][pdm] = tem.soil.getSNOWPACK();

  // Other monthly carbon fluxes in ecosystems

  output[tem.I_FORAGEC][pdm] = tem.ag.getFORAGEC();

  output[tem.I_MANUREC][pdm] = tem.ag.getMANUREC();

  output[tem.I_ANIMALR][pdm] = tem.ag.getANIMALRESP();

  output[tem.I_RSOIL][pdm] = tem.getRSOIL();

  output[tem.I_NEP][pdm] = tem.getNEP();

  output[tem.I_NCE][pdm] = tem.getNCE();

  output[tem.I_NECB][pdm] = tem.getNECB();

  // Other monthly nitrogen fluxes in ecosystems

  output[tem.I_TOTNDEP][pdm] = tem.atms.getTOTNDEP();

  output[tem.I_NH4DEP][pdm] = tem.atms.getNH4DEP();

  output[tem.I_NO3DEP][pdm] = tem.atms.getNO3DEP();

  output[tem.I_FIRENTOTDEP][pdm] = tem.ag.getFIRENTOTDEP();

  output[tem.I_FIRENH4DEP][pdm] = tem.ag.getFIRENH4DEP();

  output[tem.I_FIRENO3DEP][pdm] = tem.ag.getFIRENO3DEP();

  output[tem.I_FORAGEN][pdm] = tem.ag.getFORAGEN();

  output[tem.I_MANUREN][pdm] = tem.ag.getMANUREN();

  output[tem.I_URINE][pdm] = tem.ag.getURINE();

  output[tem.I_NINP][pdm] = tem.soil.getNINPUT();

  output[tem.I_NLST][pdm] = tem.soil.getNLOST();

  output[tem.I_NENB][pdm] = tem.getNENB();

  // Other monthly water fluxes in ecosystems

  output[tem.I_PET][pdm] = tem.atms.getPET();

  output[tem.I_SNWINF][pdm] = tem.soil.getSNOWINF();

  output[tem.I_WYLD][pdm] = tem.soil.getH2OYLD();

  // Carbon in Human product pools

  output[tem.I_AGPRDC][pdm] = tem.ag.getPROD1C();

  output[tem.I_PROD10C][pdm] = tem.ag.getPROD10C();

  output[tem.I_PROD100C][pdm] = tem.ag.getPROD100C();

  output[tem.I_TOTPRDC][pdm] = tem.ag.getTOTPRODC();

  // Carbon in crop residue pool

  output[tem.I_RESIDC][pdm] = tem.ag.getCROPRESIDUEC();

  output[tem.I_AGSTUBC][pdm] = tem.ag.getSTUBBLEC();

  // Nitrogen in Human product pools

  output[tem.I_AGPRDN][pdm] = tem.ag.getPROD1N();

  output[tem.I_PROD10N][pdm] = tem.ag.getPROD10N();

  output[tem.I_PROD100N][pdm] = tem.ag.getPROD100N();

  output[tem.I_TOTPRDN][pdm] = tem.ag.getTOTPRODN();

  // Nitrogen in crop residue pool

  output[tem.I_RESIDN][pdm] = tem.ag.getCROPRESIDUEN();

  output[tem.I_AGSTUBN][pdm] = tem.ag.getSTUBBLEN();

  // Monthly carbon fluxes associated with
  //  agricultural conversion

  output[tem.I_CNVRTC][pdm] = tem.ag.getCONVRTFLXC();

  output[tem.I_VCNVRTC][pdm] = tem.ag.getVCONVRTFLXC();

  output[tem.I_SCNVRTC][pdm] = tem.ag.getSCONVRTFLXC();

  output[tem.I_SLASHC][pdm] = tem.ag.getSLASHC();

  output[tem.I_CFLX][pdm] = tem.ag.getCFLUX();

  // Monthly nitrogen fluxes associated with
  //  agricultural conversion

  output[tem.I_CNVRTN][pdm] = tem.ag.getCONVRTFLXN();

  output[tem.I_VCNVRTN][pdm] = tem.ag.getVCONVRTFLXN();

  output[tem.I_SCNVRTN][pdm] = tem.ag.getSCONVRTFLXN();

  output[tem.I_SLASHN][pdm] = tem.ag.getSLASHN();

  output[tem.I_NTOTRTNT][pdm] = tem.ag.getNTOTRETENT();

  output[tem.I_NH4RTNT][pdm] = tem.ag.getNH4RETENT();

  output[tem.I_NO3RTNT][pdm] = tem.ag.getNO3RETENT();

  output[tem.I_VNTOTRTNT][pdm] = tem.ag.getVNTOTRETENT();

  output[tem.I_VNH4RTNT][pdm] = tem.ag.getVNH4RETENT();

  output[tem.I_VNO3RTNT][pdm] = tem.ag.getVNO3RETENT();

  output[tem.I_SNTOTRTNT][pdm] = tem.ag.getSNTOTRETENT();

 output[tem.I_SNH4RTNT][pdm] = tem.ag.getSNH4RETENT();

 output[tem.I_SNO3RTNT][pdm] = tem.ag.getSNO3RETENT();

  // Monthly carbon and nitrogen fluxes from agricultural
  //   ecosystems

  output[tem.I_AGFPRDC][pdm] = tem.ag.getCROPPRODC();
  output[tem.I_AGFPRDN][pdm] = tem.ag.getCROPPRODN();

  output[tem.I_FRESIDC][pdm] = tem.ag.getFORMCROPRESIDUEC();
  output[tem.I_FRESIDN][pdm] = tem.ag.getFORMCROPRESIDUEN();

  output[tem.I_AGPRDFC][pdm] = tem.ag.getPROD1DECAYC();
  output[tem.I_AGPRDFN][pdm] = tem.ag.getPROD1DECAYN();

  output[tem.I_RESIDFC][pdm] = tem.ag.getCROPRESIDUEFLXC();
  output[tem.I_RESIDFN][pdm] = tem.ag.getCROPRESIDUEFLXN();


  // Monthly carbon and nitrogen fluxes from products

  output[tem.I_PRDF10C][pdm] = tem.ag.getFORMPROD10C();
  output[tem.I_PRDF10N][pdm] = tem.ag.getFORMPROD10N();

  output[tem.I_PRD10FC][pdm] = tem.ag.getPROD10DECAYC();
  output[tem.I_PRD10FN][pdm] = tem.ag.getPROD10DECAYN();

  output[tem.I_PRDF100C][pdm] = tem.ag.getFORMPROD100C();
  output[tem.I_PRDF100N][pdm] = tem.ag.getFORMPROD100N();

  output[tem.I_PRD100FC][pdm] = tem.ag.getPROD100DECAYC();
  output[tem.I_PRD100FN][pdm] = tem.ag.getPROD100DECAYN();

  output[tem.I_TOTFPRDC][pdm] = tem.ag.getFORMTOTPRODC();
  output[tem.I_TOTFPRDN][pdm] = tem.ag.getFORMTOTPRODN();

  output[tem.I_TOTPRDFC][pdm] = tem.ag.getTOTPRODDECAYC();
  output[tem.I_TOTPRDFN][pdm] = tem.ag.getTOTPRODDECAYN();

  //  Output agricultural area-specific vs natural area-specific
  //    results
  
  if( 1 == tem.ag.state )
  {
    output[tem.I_CROPC][pdm] = tem.getY( I_VEGC );
    output[tem.I_NATVEGC][pdm] = ZERO;

    output[tem.I_CROPN][pdm] = tem.veg.getVEGN();
    output[tem.I_NATVEGN][pdm] = ZERO;

    output[tem.I_CSTRN][pdm] = tem.getY( I_STRN );
    output[tem.I_NATSTRN][pdm] = ZERO;

    output[tem.I_CSTON][pdm] = tem.getY( I_STON );
    output[tem.I_NATSTON][pdm] = ZERO;

    output[tem.I_CROPULF][pdm] = tem.getY( I_UNRMLF );
    output[tem.I_NATULF][pdm] = ZERO;

    output[tem.I_CROPLEAF][pdm] = tem.getY( I_LEAF );
    output[tem.I_NATLEAF][pdm] = ZERO;

    output[tem.I_CROPLAI][pdm] = tem.getY( I_LAI );
    output[tem.I_NATLAI][pdm] = ZERO;

    output[tem.I_CROPFPC][pdm] = tem.getY( I_FPC );
    output[tem.I_NATFPC][pdm] = ZERO;

    output[tem.I_AGINGPP][pdm] = tem.getY( I_INGPP );
    output[tem.I_NATINGPP][pdm] = ZERO;

    output[tem.I_AGGPP][pdm] = tem.getY( I_GPP );
    output[tem.I_NATGPP][pdm] = ZERO;

    output[tem.I_AGINNPP][pdm] = tem.getY( I_INNPP );
    output[tem.I_NATINNPP][pdm] = ZERO;

    output[tem.I_AGNPP][pdm] = tem.getY( I_NPP );
    output[tem.I_NATNPP][pdm] = ZERO;

    output[tem.I_AGGPR][pdm] = tem.getY( I_GPR );
    output[tem.I_NATGPR][pdm] = ZERO;

    output[tem.I_AGRVMNT][pdm] = tem.getY( I_RVMNT );
    output[tem.I_NATRVMNT][pdm] = ZERO;

    output[tem.I_AGRVGRW][pdm] = tem.getY( I_RVGRW );
    output[tem.I_NATRVGRW][pdm] = ZERO;

    output[tem.I_AGLTRC][pdm] = tem.getY( I_LTRFALC );
    output[tem.I_NATLTRC][pdm] = ZERO;

    output[tem.I_AGSNFX][pdm] = tem.getY( I_SNFIX );
    output[tem.I_NATSNFX][pdm] = ZERO;

    output[tem.I_AGINNUP][pdm] = tem.getY( I_INNUP );
    output[tem.I_NATINNUP][pdm] = ZERO;

    output[tem.I_AINNH4UP][pdm] = tem.getY( I_INNH4UP );
    output[tem.I_NINNH4UP][pdm] = ZERO;

    output[tem.I_AINNO3UP][pdm] = tem.getY( I_INNO3UP );
    output[tem.I_NINNO3UP][pdm] = ZERO;

    output[tem.I_AGVNUP][pdm] = tem.getY( I_VNUP );
    output[tem.I_NATVNUP][pdm] = ZERO;

    output[tem.I_AGVNH4UP][pdm] = tem.getY( I_VNH4UP );
    output[tem.I_NVNH4UP][pdm] = ZERO;

    output[tem.I_AGVNO3UP][pdm] = tem.getY( I_VNO3UP );
    output[tem.I_NVNO3UP][pdm] = ZERO;

    output[tem.I_AGVSUP][pdm] = tem.getY( I_VSUP );
    output[tem.I_NATVSUP][pdm] = ZERO;

    output[tem.I_AGVLUP][pdm] = tem.getY( I_VLUP );
    output[tem.I_NATVLUP][pdm] = ZERO;

    output[tem.I_AGVNMBL][pdm] = tem.getY( I_VNMBL );
    output[tem.I_NATVNMBL][pdm] = ZERO;

    output[tem.I_AGVNRSRB][pdm] = tem.getY( I_VNRSRB );
    output[tem.I_NVNRSRB][pdm] = ZERO;

    output[tem.I_AGLTRN][pdm] = tem.getY( I_LTRFALN );
    output[tem.I_NATLTRN][pdm] = ZERO;
  }
  else 
  {
    output[tem.I_CROPC][pdm] = ZERO;
    output[tem.I_NATVEGC][pdm] = tem.getY( I_VEGC );

    output[tem.I_CROPN][pdm] = ZERO;
    output[tem.I_NATVEGN][pdm] = tem.veg.getVEGN();

    output[tem.I_CSTRN][pdm] = ZERO;
    output[tem.I_NATSTRN][pdm] = tem.getY( I_STRN );

    output[tem.I_CSTON][pdm] = ZERO;
    output[tem.I_NATSTON][pdm] = tem.getY( I_STON );

    output[tem.I_CROPULF][pdm] = ZERO;
    output[tem.I_NATULF][pdm] = tem.getY( I_UNRMLF );

    output[tem.I_CROPLEAF][pdm] = ZERO;
    output[tem.I_NATLEAF][pdm] = tem.getY( I_LEAF );

    output[tem.I_CROPLAI][pdm] = ZERO;
    output[tem.I_NATLAI][pdm] = tem.getY( I_LAI );

    output[tem.I_CROPFPC][pdm] = ZERO;
    output[tem.I_NATFPC][pdm] = tem.getY( I_FPC );

    output[tem.I_AGINGPP][pdm] = ZERO;
    output[tem.I_NATINGPP][pdm] = tem.getY( I_INGPP );

    output[tem.I_AGGPP][pdm] = ZERO;
    output[tem.I_NATGPP][pdm] = tem.getY( I_GPP );

    output[tem.I_AGINNPP][pdm] = ZERO;
    output[tem.I_NATINNPP][pdm] = tem.getY( I_INNPP );

    output[tem.I_AGNPP][pdm] = ZERO;
    output[tem.I_NATNPP][pdm] = tem.getY( I_NPP );

    output[tem.I_AGGPR][pdm] = ZERO;
    output[tem.I_NATGPR][pdm] = tem.getY( I_GPR );

    output[tem.I_AGRVMNT][pdm] = ZERO;
    output[tem.I_NATRVMNT][pdm] = tem.getY( I_RVMNT );

    output[tem.I_AGRVGRW][pdm] = ZERO;
    output[tem.I_NATRVGRW][pdm] = tem.getY( I_RVGRW );

    output[tem.I_AGLTRC][pdm] = ZERO;
    output[tem.I_NATLTRC][pdm] = tem.getY( I_LTRFALC );

    output[tem.I_AGSNFX][pdm] = ZERO;
    output[tem.I_NATSNFX][pdm] = tem.getY( I_SNFIX );

    output[tem.I_AGINNUP][pdm] = ZERO;
    output[tem.I_NATINNUP][pdm] = tem.getY( I_INNUP );

    output[tem.I_AINNH4UP][pdm] = ZERO;
    output[tem.I_NINNH4UP][pdm] = tem.getY( I_INNH4UP );

    output[tem.I_AINNO3UP][pdm] = ZERO;
    output[tem.I_NINNO3UP][pdm] = tem.getY( I_INNO3UP );

    output[tem.I_AGVNUP][pdm] = ZERO;
    output[tem.I_NATVNUP][pdm] = tem.getY( I_VNUP );

    output[tem.I_AGVNH4UP][pdm] = ZERO;
    output[tem.I_NVNH4UP][pdm] = tem.getY( I_VNH4UP );

    output[tem.I_AGVNO3UP][pdm] = ZERO;
    output[tem.I_NVNO3UP][pdm] = tem.getY( I_VNO3UP );

    output[tem.I_AGVSUP][pdm] = ZERO;
    output[tem.I_NATVSUP][pdm] = tem.getY( I_VSUP );

    output[tem.I_AGVLUP][pdm] = ZERO;
    output[tem.I_NATVLUP][pdm] = tem.getY( I_VLUP );

    output[tem.I_AGVNMBL][pdm] = ZERO;
    output[tem.I_NATVNMBL][pdm] = tem.getY( I_VNMBL );

    output[tem.I_AGVNRSRB][pdm] = ZERO;
    output[tem.I_NVNRSRB][pdm] = tem.getY( I_VNRSRB );

    output[tem.I_AGLTRN][pdm] = ZERO;
    output[tem.I_NATLTRN][pdm] = tem.getY( I_LTRFALN );
  }
  

  // Monthly soil thermal dynamics

  output[tem.I_TSOIL][pdm] = tem.soil.getTSOIL();

  output[tem.I_DST0][pdm] = tem.soil.stm.getDST0();

  output[tem.I_DST5][pdm] = tem.soil.stm.getDST5();

  output[tem.I_DST10][pdm] = tem.soil.getDST10();

  output[tem.I_DST20][pdm] = tem.soil.stm.getDST20();

  output[tem.I_DST50][pdm] = tem.soil.stm.getDST50();

  output[tem.I_DST100][pdm] = tem.soil.stm.getDST100();

  output[tem.I_DST200][pdm] = tem.soil.stm.getDST200();

  output[tem.I_FRONTD][pdm] = tem.soil.stm.getFRONTD();

  output[tem.I_THAWBE][pdm] = tem.soil.stm.getTHAWBEGIN1();

  output[tem.I_THAWEND][pdm] = tem.soil.stm.getTHAWEND1();

  output[tem.I_THAWPCT][pdm] = tem.veg.getTHAWPCT();

  output[tem.I_ACTLAYER][pdm] = tem.soil.getACTLAYER();

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::readBinaryCohortState( ifstream& ifstate,
                                        const int& pichrt )
{
  
  int ichrt;

  float tstcol;
  
  float tstrow;
  
  ifstate.read( (char *)(&tstcol), sizeof( tstcol ) );
  ifstate.read( (char *)(&tstrow), sizeof( tstrow ) );

  if( (tstcol != col) || (tstrow != row) )
  {
    cout << "TEMSTATE is not co-registered with other data sets!" << endl;
    cout << "TEMSTATE Lon = " << tstcol << " Lat = " << tstrow << endl;
    cout << "Other Lon = " << col << " Lat = " << row << endl;

    exit( -1 );
  }

  ifstate.read( (char *)(&ichrt), sizeof( ichrt ) ); 
  ifstate.read( (char *)(&cohort[pichrt]), sizeof( ElmntCohort60 ) );

  if( ifstate.fail() )
  {
  	cout << "Problem with reading in TEMSTATE at " << endl;
    cout << "Lon = " << tstcol << " Lat = " << tstrow;
    cout << " Cohort = " << ichrt << endl;
  
    exit( -1 );
  }
  	 	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::readCohortState( ifstream& ifstate, 
                                  const int& pichrt )
{
  int i;
  int dm;
  int dnode;
  double dumdouble;
//  float dumflt;
  int dumint;
  long dumlong;
 
  float tstcol;
  float tstrow;
 
  ifstate >> tstcol;    // Longitude of element
  ifstate >> tstrow;    // Latitude of element

  ifstate.seekg( 0, ios::cur );

  if( (tstcol != col) || (tstrow != row) )
  {
    cout << "TEMSTATE is not co-registered with other data sets!" << endl;
    cout << "TEMSTATE Lon = " << tstcol << " Lat = " << tstrow << endl;
    cout << "Other Lon = " << col << " Lat = " << row << endl;

    exit( -1 );
  }
  
  ifstate >> dumint;   // ichrt+1
  
  ifstate >> dumint;   // cohort[pichrt].srcCohort;
  ifstate >> dumint;   // cohort[pichrt].standage;
  ifstate >> dumlong;  // cohort[pichrt].chrtarea;
  ifstate >> dumint;   // cohort[pichrt].potveg;
  ifstate >> dumint;   // cohort[pichrt].currentveg;
  ifstate >> dumint;   // cohort[pichrt].subtype;
  ifstate >> dumint;   // cohort[pichrt].cmnt;

 	
  for( i = 0; i < MAXSTATE; ++i )
  {
    ifstate >> cohort[pichrt].y[i];
    ifstate >> cohort[pichrt].prevy[i];
  }

  ifstate >> dumint;   // cohort[pichrt].agcmnt;

  ifstate >> cohort[pichrt].aggrowdd;

  ifstate >> cohort[pichrt].agkd;

  ifstate >> dumint;   // cohort[pichrt].agprvstate;

  ifstate >> dumint;   // cohort[pichrt].agstate;

  ifstate >> cohort[pichrt].c2n;
  
  ifstate >> cohort[pichrt].cneven;

  ifstate >> cohort[pichrt].convrtflx.carbon;
  ifstate >> cohort[pichrt].convrtflx.nitrogen;

  ifstate >> cohort[pichrt].cropprveetmx;

  ifstate >> cohort[pichrt].cropprvleafmx;

  ifstate >> cohort[pichrt].cropprvpetmx;

  ifstate >> cohort[pichrt].cropResidue.carbon;
  ifstate >> cohort[pichrt].cropResidue.nitrogen;

  ifstate >> cohort[pichrt].croptopt;

  ifstate >> cohort[pichrt].distmnthcnt;

  ifstate >> dumint;   // cohort[pichrt].disturbflag;
  
  ifstate >> dumint;   // cohort[pichrt].disturbmonth;
  
  for( dm = 0; dm < CYCLE; ++dm )
  {  
    ifstate >> cohort[pichrt].dst10[dm];
  }

  ifstate >> cohort[pichrt].eetmx;

  ifstate >> dumint;   // cohort[pichrt].fertflag;                              

  ifstate >> cohort[pichrt].firemnthcnt;
  
  ifstate >> cohort[pichrt].firendep.total;
  ifstate >> cohort[pichrt].firendep.nh4;
  ifstate >> cohort[pichrt].firendep.no3;
  
  ifstate >> cohort[pichrt].formPROD10.carbon;
  ifstate >> cohort[pichrt].formPROD10.nitrogen;

  ifstate >> cohort[pichrt].formPROD100.carbon;
  ifstate >> cohort[pichrt].formPROD100.nitrogen;

  ifstate >> cohort[pichrt].fprevozone;

  ifstate >> dumint;   // cohort[pichrt].FRI;

  for( dm = 0; dm < CYCLE; ++dm )
  {  
    ifstate >> cohort[pichrt].initPROD1[dm].carbon;
    ifstate >> cohort[pichrt].initPROD1[dm].nitrogen;
  }

  for( i = 0; i < 10; ++i )
  {
    ifstate >> cohort[pichrt].initPROD10[i].carbon;
    ifstate >> cohort[pichrt].initPROD10[i].nitrogen;
  }
    
  for( i = 0; i < 100; ++i )
  {
    ifstate >> cohort[pichrt].initPROD100[i].carbon;
    ifstate >> cohort[pichrt].initPROD100[i].nitrogen;
  }

  ifstate >> dumint;   // cohort[pichrt].irrgflag;                              
  
  ifstate >> cohort[pichrt].kd;

  ifstate >> cohort[pichrt].natprveetmx;

  ifstate >> cohort[pichrt].natprvleafmx;

  ifstate >> cohort[pichrt].natprvpetmx;

  ifstate >> cohort[pichrt].natseedC;

  ifstate >> cohort[pichrt].natseedSTRN;

  ifstate >> cohort[pichrt].natseedSTON;

  ifstate >> cohort[pichrt].natsoil;

  ifstate >> cohort[pichrt].nattopt;

  ifstate >> cohort[pichrt].natyreet;

  ifstate >> cohort[pichrt].natyrpet;

  ifstate >> cohort[pichrt].newleafmx;

  ifstate >> cohort[pichrt].newtopt;

  ifstate >> cohort[pichrt].nonsolc;

  ifstate >> cohort[pichrt].nonsoln;

  ifstate >> cohort[pichrt].nretent.total;
  ifstate >> cohort[pichrt].nretent.nh4;
  ifstate >> cohort[pichrt].nretent.no3;

  ifstate >> cohort[pichrt].nsretent.total;
  ifstate >> cohort[pichrt].nsretent.nh4;
  ifstate >> cohort[pichrt].nsretent.no3;

  ifstate >> cohort[pichrt].nvretent.total;
  ifstate >> cohort[pichrt].nvretent.nh4;
  ifstate >> cohort[pichrt].nvretent.no3;

  ifstate >> cohort[pichrt].petmx;

  ifstate >> cohort[pichrt].prev2tair;

  ifstate >> cohort[pichrt].prevco2;

  ifstate >> cohort[pichrt].prevCropResidue.carbon;
  ifstate >> cohort[pichrt].prevCropResidue.nitrogen;

  ifstate >> cohort[pichrt].prevdst10;

  ifstate >> cohort[pichrt].prevPROD1.carbon;
  ifstate >> cohort[pichrt].prevPROD1.nitrogen;

  ifstate >> cohort[pichrt].prevPROD10.carbon;
  ifstate >> cohort[pichrt].prevPROD10.nitrogen;

  ifstate >> cohort[pichrt].prevPROD100.carbon;
  ifstate >> cohort[pichrt].prevPROD100.nitrogen;

  ifstate >> cohort[pichrt].prevspack;

  ifstate >> cohort[pichrt].prevtair;

  ifstate >> cohort[pichrt].prevunrmleaf;
  
  ifstate >> dumdouble;  // cohort[pichrt].prod10par; 

  ifstate >> dumdouble;  // cohort[pichrt].prod100par; 

  ifstate >> cohort[pichrt].productYear;

  ifstate >> cohort[pichrt].prvcropnpp;

  ifstate >> cohort[pichrt].prveetmx;

  ifstate >> cohort[pichrt].prvleafmx;

  ifstate >> cohort[pichrt].prvpetmx;

  ifstate >> cohort[pichrt].qc;

  ifstate >> dumdouble;  // cohort[pichrt].sconvert; 
  
  ifstate >> cohort[pichrt].sconvrtflx.carbon;
  ifstate >> cohort[pichrt].sconvrtflx.nitrogen;

  ifstate >> cohort[pichrt].slash.carbon;
  ifstate >> cohort[pichrt].slash.nitrogen;

  ifstate >> dumdouble;  // cohort[pichrt].slashpar; 

  ifstate >> cohort[pichrt].STMdst0;

  ifstate >> cohort[pichrt].STMdst5;

  ifstate >> cohort[pichrt].STMdst10;

  ifstate >> cohort[pichrt].STMdst20;

  ifstate >> cohort[pichrt].STMdst50;

  ifstate >> cohort[pichrt].STMdst100;

  ifstate >> cohort[pichrt].STMdst200;

  ifstate >> cohort[pichrt].STMfrontd;

  ifstate >> cohort[pichrt].STMfrontd2;

  ifstate >> cohort[pichrt].STMis9;
  
  ifstate >> cohort[pichrt].STMsmass9;
  
  ifstate >> cohort[pichrt].STMthawbegin1;

  ifstate >> cohort[pichrt].STMthawbegin2;

  ifstate >> cohort[pichrt].STMthawend1;

  ifstate >> cohort[pichrt].STMthawend2;

  ifstate >> cohort[pichrt].STMtsoil;


  for( dnode = 0; dnode < MAXNODES; ++dnode )
  {
    ifstate >> cohort[pichrt].STMdx9[dnode]; 
    ifstate >> cohort[pichrt].STMt9[dnode];  
    ifstate >> cohort[pichrt].STMwater9[dnode];  
    ifstate >> cohort[pichrt].STMx9[dnode];  
    ifstate >> cohort[pichrt].STMxfa9[dnode];  
    ifstate >> cohort[pichrt].STMxfb9[dnode];  
  }

  for( dnode = 0; dnode < MAXSNODES; ++dnode )
  {
    ifstate >> cohort[pichrt].STMweight9[dnode];  
  }
  
  ifstate >> dumint;    // cohort[pichrt].tillflag;                           

  ifstate >> cohort[pichrt].topt;

  ifstate >> cohort[pichrt].tqc;

  ifstate >> dumdouble; // cohort[pichrt].vconvert; 

  ifstate >> cohort[pichrt].vconvrtflx.carbon;
  ifstate >> cohort[pichrt].vconvrtflx.nitrogen;

  ifstate >> dumdouble; // cohort[pichrt].vrespar; 

  ifstate >> dumdouble; // cohort[pichrt].wfpsoff;
  
  ifstate >> cohort[pichrt].yragstubC;
  
  ifstate >> cohort[pichrt].yragstubN;

  ifstate >> cohort[pichrt].yrammonvol;
  
  ifstate >> cohort[pichrt].yrcflux;
  
  ifstate >> cohort[pichrt].yrconvrtC;
  
  ifstate >> cohort[pichrt].yrconvrtN;
  
  ifstate >> cohort[pichrt].yrdecayPROD1C;
  
  ifstate >> cohort[pichrt].yrdecayPROD10C;
  
  ifstate >> cohort[pichrt].yrdecayPROD100C;

  ifstate >> cohort[pichrt].yrdecayPROD1N;
  
  ifstate >> cohort[pichrt].yrdecayPROD10N;
  
  ifstate >> cohort[pichrt].yrdecayPROD100N;
  
  ifstate >> cohort[pichrt].yrdecayTOTPRODC;

  ifstate >> cohort[pichrt].yrdecayTOTPRODN;
 
  ifstate >> cohort[pichrt].yrdecompC;

  ifstate >> cohort[pichrt].yrdecompN;
  
  ifstate >> cohort[pichrt].yrdenitrif;

  ifstate >> cohort[pichrt].yrDOCleach;
  
  ifstate >> cohort[pichrt].yrDOCprod;

  ifstate >> cohort[pichrt].yrDONleach;
  
  ifstate >> cohort[pichrt].yrDONprod;
  
  ifstate >> cohort[pichrt].yreet;
  
  ifstate >> cohort[pichrt].yrfertn;
  
  ifstate >> cohort[pichrt].yrfluxResidueC;
  
  ifstate >> cohort[pichrt].yrfluxResidueN;

  ifstate >> cohort[pichrt].yrformPROD1C;
  
  ifstate >> cohort[pichrt].yrformPROD10C;
  
  ifstate >> cohort[pichrt].yrformPROD100C;

  ifstate >> cohort[pichrt].yrformPROD1N;
  
  ifstate >> cohort[pichrt].yrformPROD10N;
  
  ifstate >> cohort[pichrt].yrformPROD100N;
  
  ifstate >> cohort[pichrt].yrformResidueC;
  
  ifstate >> cohort[pichrt].yrformResidueN;

  ifstate >> cohort[pichrt].yrformTOTPRODC;

  ifstate >> cohort[pichrt].yrformTOTPRODN;

  ifstate >> cohort[pichrt].yrfpc;

  ifstate >> cohort[pichrt].yrgmin;
  
  ifstate >> cohort[pichrt].yrgpp;
  
  ifstate >> cohort[pichrt].yrgpr;
  
  ifstate >> cohort[pichrt].yrh2oyld;
  
  ifstate >> cohort[pichrt].yrimmob;

  ifstate >> cohort[pichrt].yrimmobabN;

  ifstate >> cohort[pichrt].yrimmobNH4;
  
  ifstate >> cohort[pichrt].yrineet;
  
  ifstate >> cohort[pichrt].yringpp;
  
  ifstate >> cohort[pichrt].yrinnpp;
  
  ifstate >> cohort[pichrt].yrinnup;

  ifstate >> cohort[pichrt].yrinnupNH4;

  ifstate >> cohort[pichrt].yrinnupNO3;
  
  ifstate >> cohort[pichrt].yrirrig;
  
  ifstate >> cohort[pichrt].yrlai;
    
  ifstate >> cohort[pichrt].yrleaf;

  ifstate >> cohort[pichrt].yrltrfalc;

  ifstate >> cohort[pichrt].yrltrfaln;  	
  
  ifstate >> cohort[pichrt].yrN2flx;
   
  ifstate >> cohort[pichrt].yrN2Oflx;

  ifstate >> cohort[pichrt].yrNH3flx;

  ifstate >> cohort[pichrt].yrNOflx;
   
  ifstate >> cohort[pichrt].yrN2prd;
   
  ifstate >> cohort[pichrt].yrN2Oprd;
 
  ifstate >> cohort[pichrt].yrnce;

  ifstate >> cohort[pichrt].yrndep;
  
  ifstate >> cohort[pichrt].yrndepNH4;
  
  ifstate >> cohort[pichrt].yrndepNO3;
  
  ifstate >> cohort[pichrt].yrnecb;  

  ifstate >> cohort[pichrt].yrnenb;  

  ifstate >> cohort[pichrt].yrnep;
  
  ifstate >> cohort[pichrt].yrNfixBiol;

  ifstate >> cohort[pichrt].yrNfixAsymb;

  ifstate >> cohort[pichrt].yrNfixSymb;
  
  ifstate >> cohort[pichrt].yrNH4leach;

  ifstate >> cohort[pichrt].yrninput;

  ifstate >> cohort[pichrt].yrnitrif;
  
  ifstate >> cohort[pichrt].yrnlost;
  
  ifstate >> cohort[pichrt].yrnmin;
    
  ifstate >> cohort[pichrt].yrNOprd;
  
  ifstate >> cohort[pichrt].yrNO3leach;

  ifstate >> cohort[pichrt].yrNO3prd;
  
  ifstate >> cohort[pichrt].yrnpp;
  
  ifstate >> cohort[pichrt].yrnrent.total; 
  ifstate >> cohort[pichrt].yrnrent.nh4;
  ifstate >> cohort[pichrt].yrnrent.no3;
  
  ifstate >> cohort[pichrt].yrnsrent.total;
  ifstate >> cohort[pichrt].yrnsrent.nh4;
  ifstate >> cohort[pichrt].yrnsrent.no3;
  
  ifstate >> cohort[pichrt].yrnup;

  ifstate >> cohort[pichrt].yrnupNH4;

  ifstate >> cohort[pichrt].yrnupNO3;

  ifstate >> cohort[pichrt].yrnvrent.total;
  ifstate >> cohort[pichrt].yrnvrent.nh4;
  ifstate >> cohort[pichrt].yrnvrent.no3;
  
  ifstate >> cohort[pichrt].yrpet;
  
  ifstate >> cohort[pichrt].yrPOCerode;

  ifstate >> cohort[pichrt].yrPONerode;
  
  ifstate >> cohort[pichrt].yrrgrndh2o; 
  
  ifstate >> cohort[pichrt].yrrh;
    
  ifstate >> cohort[pichrt].yrrain;
  
  ifstate >> cohort[pichrt].yrrperc;
  
  ifstate >> cohort[pichrt].yrrrun;

  ifstate >> cohort[pichrt].yrsconvrtC;

  ifstate >> cohort[pichrt].yrsconvrtN;
  
  ifstate >> cohort[pichrt].yrsgrndh2o;

  ifstate >> cohort[pichrt].yrslashC;

  ifstate >> cohort[pichrt].yrslashN;
  
  ifstate >> cohort[pichrt].yrsnowfall;

  ifstate >> cohort[pichrt].yrsnowinf;

  ifstate >> cohort[pichrt].yrsnowpack;
  
  ifstate >> cohort[pichrt].yrsoilavlH2O;
  
  ifstate >> cohort[pichrt].yrsoilavlN;

  ifstate >> cohort[pichrt].yrsoilavlNH4;

  ifstate >> cohort[pichrt].yrsoilavlNO3;
  
  ifstate >> cohort[pichrt].yrsoilDOC;
  
  ifstate >> cohort[pichrt].yrsoilDON;
  
  ifstate >> cohort[pichrt].yrsoilmoist;
  
  ifstate >> cohort[pichrt].yrsoilnonorgC;
  
  ifstate >> cohort[pichrt].yrsoilnonorgN;
  
  ifstate >> cohort[pichrt].yrsoilorgC;
  
  ifstate >> cohort[pichrt].yrsoilorgN;

  ifstate >> cohort[pichrt].yrsoilpctp;
  
  ifstate >> cohort[pichrt].yrsoilResp;
  
  ifstate >> cohort[pichrt].yrsoiltotorgC;

  ifstate >> cohort[pichrt].yrsoiltotorgN;
  
  ifstate >> cohort[pichrt].yrsoilvsm;

  ifstate >> cohort[pichrt].yrsperc;
  
  ifstate >> cohort[pichrt].yrsrun;

  ifstate >> cohort[pichrt].yrSTMdst0;

  ifstate >> cohort[pichrt].yrSTMdst5;

  ifstate >> cohort[pichrt].yrSTMdst10;

  ifstate >> cohort[pichrt].yrSTMdst20;

  ifstate >> cohort[pichrt].yrSTMdst50;

  ifstate >> cohort[pichrt].yrSTMdst100;

  ifstate >> cohort[pichrt].yrSTMdst200;

  ifstate >> cohort[pichrt].yrSTMfrontd;

  ifstate >> cohort[pichrt].yrSTMfrontd2;

  ifstate >> cohort[pichrt].yrSTMthawbegin1;

  ifstate >> cohort[pichrt].yrSTMthawbegin2;

  ifstate >> cohort[pichrt].yrSTMthawend1;

  ifstate >> cohort[pichrt].yrSTMthawend2;

  ifstate >> cohort[pichrt].yrSTMtsoil;
     
  ifstate >> cohort[pichrt].yrthawpct;
  
  ifstate >> cohort[pichrt].yrtotalC;
  
  ifstate >> cohort[pichrt].yrunleaf;

  ifstate >> cohort[pichrt].yrvconvrtC;
  
  ifstate >> cohort[pichrt].yrvconvrtN;

  ifstate >> cohort[pichrt].yrvegabvgrndResp;
  
  ifstate >> cohort[pichrt].yrvegC;
    
  ifstate >> cohort[pichrt].yrveglup;

  ifstate >> cohort[pichrt].yrvegN;

  ifstate >> cohort[pichrt].yrvegnmobil;

  ifstate >> cohort[pichrt].yrvegnrsorb;

  ifstate >> cohort[pichrt].yrvegrgrowth;

  ifstate >> cohort[pichrt].yrvegrmaint;

  ifstate >> cohort[pichrt].yrvegrootResp;
  
  ifstate >> cohort[pichrt].yrvegstoN;
  
  ifstate >> cohort[pichrt].yrvegstrN;

  ifstate >> cohort[pichrt].yrvegsup;


  ifstate.seekg( 0, ios::cur );
    	
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */
     
void TEMelmnt60::saveTEMCohortState( const int& pichrt )
{
  int dm;
  int dnode;
  int i;
  
  cohort[pichrt].potveg = tem.veg.getPOTVEG();

  cohort[pichrt].currentveg = tem.veg.getCURRENTVEG();

  cohort[pichrt].subtype = tem.veg.getSUBTYPE();

  cohort[pichrt].cmnt = tem.veg.cmnt;

  for( i = 0; i < MAXSTATE; ++i )
  {
    cohort[pichrt].y[i] = tem.getY( i );
    cohort[pichrt].prevy[i] = tem.getPREVY( i );
  }

  cohort[pichrt].agcmnt = tem.ag.cmnt;

  cohort[pichrt].aggrowdd = tem.ag.getGROWDD();

  cohort[pichrt].agkd = tem.ag.getKD();

  cohort[pichrt].agprvstate = tem.ag.prvstate;

  cohort[pichrt].agstate = tem.ag.state;

  cohort[pichrt].c2n = tem.veg.getC2N();
  
  cohort[pichrt].cneven = tem.veg.getCNEVEN();

  cohort[pichrt].convrtflx.carbon = tem.ag.getCONVRTFLXC();
  cohort[pichrt].convrtflx.nitrogen = tem.ag.getCONVRTFLXN();

  cohort[pichrt].cropprveetmx = tem.ag.getCROPPRVEETMX();

  cohort[pichrt].cropprvleafmx = tem.ag.getCROPPRVLEAFMX();

  cohort[pichrt].cropprvpetmx = tem.ag.getCROPPRVPETMX();

  cohort[pichrt].cropResidue.carbon = tem.ag.getCROPRESIDUEC();
  cohort[pichrt].cropResidue.nitrogen = tem.ag.getCROPRESIDUEN();

  cohort[pichrt].croptopt = tem.ag.getCROPTOPT();

  cohort[pichrt].distmnthcnt = tem.distmnthcnt;

  cohort[pichrt].disturbflag = tem.disturbflag;
  
  cohort[pichrt].disturbmonth = tem.disturbmonth;


  cohort[pichrt].eetmx = tem.soil.getEETMX();

  cohort[pichrt].fertflag = tem.ag.fertflag;                              

  cohort[pichrt].firemnthcnt = tem.firemnthcnt;
  
  cohort[pichrt].firendep.total = tem.ag.getFIRENTOTDEP();
  cohort[pichrt].firendep.nh4 = tem.ag.getFIRENH4DEP();
  cohort[pichrt].firendep.no3 = tem.ag.getFIRENO3DEP();
  
  cohort[pichrt].formPROD10.carbon = tem.ag.getFORMPROD10C();
  cohort[pichrt].formPROD10.nitrogen = tem.ag.getFORMPROD10N();

  cohort[pichrt].formPROD100.carbon = tem.ag.getFORMPROD100C();
  cohort[pichrt].formPROD100.nitrogen = tem.ag.getFORMPROD100N();

  cohort[pichrt].fprevozone = tem.veg.getFPREVOZONE();

  cohort[pichrt].FRI = tem.ag.getFRI();

  for( dm = 0; dm < CYCLE; ++dm )
  {  
    cohort[pichrt].initPROD1[dm].carbon = tem.ag.getINITPROD1C( dm );
    cohort[pichrt].initPROD1[dm].nitrogen = tem.ag.getINITPROD1N( dm );
  }

  for( i = 0; i < 10; ++i )
  {
    cohort[pichrt].initPROD10[i].carbon = tem.ag.getINITPROD10C( i );
    cohort[pichrt].initPROD10[i].nitrogen = tem.ag.getINITPROD10N( i );
  }
    
  for( i = 0; i < 100; ++i )
  {
    cohort[pichrt].initPROD100[i].carbon = tem.ag.getINITPROD100C( i );
    cohort[pichrt].initPROD100[i].nitrogen = tem.ag.getINITPROD100N( i );
  }

  cohort[pichrt].irrgflag = tem.ag.irrgflag;                              
  
  cohort[pichrt].kd = tem.microbe.getKD();

  cohort[pichrt].natprveetmx = tem.ag.getNATPRVEETMX();

  cohort[pichrt].natprvleafmx = tem.ag.getNATPRVLEAFMX();

  cohort[pichrt].natprvpetmx = tem.ag.getNATPRVPETMX();

  cohort[pichrt].natseedC = tem.ag.getNATSEEDC();

  cohort[pichrt].natseedSTRN = tem.ag.getNATSEEDSTRN();

  cohort[pichrt].natseedSTON = tem.ag.getNATSEEDSTON();

  cohort[pichrt].natsoil = tem.ag.getNATSOIL();

  cohort[pichrt].nattopt = tem.ag.getNATTOPT();

  cohort[pichrt].natyreet = tem.ag.getNATYREET();

  cohort[pichrt].natyrpet = tem.ag.getNATYRPET();

  cohort[pichrt].newleafmx = tem.veg.getNEWLEAFMX();

  cohort[pichrt].newtopt = tem.veg.getNEWTOPT();

  cohort[pichrt].nonsolc = tem.soil.getNSOLC();

  cohort[pichrt].nonsoln = tem.soil.getNSOLN();

  cohort[pichrt].nretent = tem.ag.getNRETENT();

  cohort[pichrt].nsretent = tem.ag.getNSRETENT();

  cohort[pichrt].nvretent = tem.ag.getNVRETENT();

  cohort[pichrt].petmx = tem.atms.getPETMX();

  cohort[pichrt].prev2tair = tem.atms.getPREV2TAIR();

  cohort[pichrt].prevco2 = tem.atms.getPREVCO2();

  cohort[pichrt].prevCropResidue.carbon = tem.ag.getPREVCROPRESIDUEC();
  cohort[pichrt].prevCropResidue.nitrogen = tem.ag.getPREVCROPRESIDUEN();

  cohort[pichrt].prevdst10 = tem.soil.getPREVDST10();

  cohort[pichrt].prevPROD1.carbon = tem.ag.getPREVPROD1C();
  cohort[pichrt].prevPROD1.nitrogen = tem.ag.getPREVPROD1N();

  cohort[pichrt].prevPROD10.carbon = tem.ag.getPREVPROD10C();
  cohort[pichrt].prevPROD10.nitrogen = tem.ag.getPREVPROD10N();

  cohort[pichrt].prevPROD100.carbon = tem.ag.getPREVPROD100C();
  cohort[pichrt].prevPROD100.nitrogen = tem.ag.getPREVPROD100N();

  cohort[pichrt].prevspack = tem.soil.getPREVSPACK();

  cohort[pichrt].prevtair = tem.atms.getPREVTAIR();

  cohort[pichrt].prevunrmleaf = tem.veg.getPREVUNRMLEAF();
  
  cohort[pichrt].prod10par = tem.ag.getPROD10PAR(); 

  cohort[pichrt].prod100par = tem.ag.getPROD100PAR(); 

  cohort[pichrt].productYear = tem.ag.getPRODUCTYEAR();
 
  cohort[pichrt].prvcropnpp = tem.ag.getPRVCROPNPP();

  cohort[pichrt].prveetmx = tem.soil.getPRVEETMX();

  cohort[pichrt].prvleafmx = tem.veg.getPRVLEAFMX();

  cohort[pichrt].prvpetmx = tem.atms.getPRVPETMX();

  cohort[pichrt].sconvert = tem.ag.getSCONVERT(); 
  
  cohort[pichrt].sconvrtflx.carbon = tem.ag.getSCONVRTFLXC();
  cohort[pichrt].sconvrtflx.nitrogen = tem.ag.getSCONVRTFLXN();

  cohort[pichrt].slash.carbon = tem.ag.getSLASHC();
  cohort[pichrt].slash.nitrogen = tem.ag.getSLASHN();

  cohort[pichrt].slashpar = tem.ag.getSLASHPAR(); 

  cohort[pichrt].STMdst0 = tem.soil.stm.getDST0();

  cohort[pichrt].STMdst5 = tem.soil.stm.getDST5();

  cohort[pichrt].STMdst10 = tem.soil.getDST10();

  cohort[pichrt].STMdst20 = tem.soil.stm.getDST20();

  cohort[pichrt].STMdst50 = tem.soil.stm.getDST50();

  cohort[pichrt].STMdst100 = tem.soil.stm.getDST100();

  cohort[pichrt].STMdst200 = tem.soil.stm.getDST200();

  cohort[pichrt].STMfrontd = tem.soil.stm.getFRONTD();

  cohort[pichrt].STMfrontd2 = tem.soil.stm.getFRONTD2();

  cohort[pichrt].STMis9 = tem.soil.stm.getIS9();
  
  cohort[pichrt].STMsmass9 = tem.soil.stm.getSMASS9();

  cohort[pichrt].STMthawbegin1 = tem.soil.stm.getTHAWBEGIN1();

  cohort[pichrt].STMthawbegin2 = tem.soil.stm.getTHAWBEGIN2();

  cohort[pichrt].STMthawend1 = tem.soil.stm.getTHAWEND1();

  cohort[pichrt].STMthawend2 = tem.soil.stm.getTHAWEND2();

  cohort[pichrt].STMtsoil =  tem.soil.getTSOIL();

  
  for( dnode = 0; dnode < MAXNODES; ++dnode )
  {
    cohort[pichrt].STMdx9[dnode] = tem.soil.stm.getDX9( dnode ); 
     
    cohort[pichrt].STMt9[dnode] = tem.soil.stm.getT9( dnode );  
    
    cohort[pichrt].STMwater9[dnode] = tem.soil.stm.getWATER9( dnode );  
    
    cohort[pichrt].STMx9[dnode] = tem.soil.stm.getX9( dnode );  

    cohort[pichrt].STMxfa9[dnode] = tem.soil.stm.getXFA9( dnode );  

    cohort[pichrt].STMxfb9[dnode] = tem.soil.stm.getXFB9( dnode );  
  }

  for( dnode = 0; dnode < MAXSNODES; ++dnode )
  {
    cohort[pichrt].STMweight9[dnode] = tem.soil.stm.getWEIGHT9( dnode );  
  }
  
  cohort[pichrt].tillflag = tem.ag.tillflag;                           

  cohort[pichrt].topt = tem.veg.getTOPT();

  cohort[pichrt].vconvert = tem.ag.getVCONVERT(); 

  cohort[pichrt].vconvrtflx.carbon = tem.ag.getVCONVRTFLXC();
  cohort[pichrt].vconvrtflx.nitrogen = tem.ag.getVCONVRTFLXN();

  cohort[pichrt].vrespar = tem.ag.getVRESPAR(); 

  cohort[pichrt].wfpsoff = tem.soil.getWFPSOFF();

  cohort[pichrt].yragstubC = tem.ag.getYRSTUBC();
  
  cohort[pichrt].yragstubN = tem.ag.getYRSTUBN();

  cohort[pichrt].yrammonvol = tem.microbe.getYRAMMNVOL();
  
  cohort[pichrt].yrcflux = tem.ag.getYRCFLUX();
  
  cohort[pichrt].yrconvrtC = tem.ag.getYRCONVRTC();
  
  cohort[pichrt].yrconvrtN = tem.ag.getYRCONVRTN();
  
  cohort[pichrt].yrdecayPROD1C = tem.ag.getYRDECAYPROD1C();
  
  cohort[pichrt].yrdecayPROD10C = tem.ag.getYRDECAYPROD10C();
  
  cohort[pichrt].yrdecayPROD100C = tem.ag.getYRDECAYPROD100C();

  cohort[pichrt].yrdecayPROD1N = tem.ag.getYRDECAYPROD1N();
  
  cohort[pichrt].yrdecayPROD10N = tem.ag.getYRDECAYPROD10N();
  
  cohort[pichrt].yrdecayPROD100N = tem.ag.getYRDECAYPROD100N();
  
  cohort[pichrt].yrdecayTOTPRODC = tem.ag.getYRDECAYTOTPRODC();

  cohort[pichrt].yrdecayTOTPRODN = tem.ag.getYRDECAYTOTPRODN();
 
  cohort[pichrt].yrdecompC = tem.microbe.getYRDECOMP();

  cohort[pichrt].yrdecompN = tem.microbe.getYRNDECOMP();
  
  cohort[pichrt].yrdenitrif = tem.microbe.getYRDENITRF();

  cohort[pichrt].yrDOCleach = tem.soil.getYRLCHDOC();
  
  cohort[pichrt].yrDOCprod = tem.microbe.getYRDOCPRD();

  cohort[pichrt].yrDONleach = tem.soil.getYRLCHDON();
  
  cohort[pichrt].yrDONprod = tem.microbe.getYRDONPRD();
  
  cohort[pichrt].yreet = tem.soil.getYREET();
  
  cohort[pichrt].yrfertn = tem.ag.getYRFERTN();
  
  cohort[pichrt].yrfluxResidueC = tem.ag.getYRFLUXRESIDUEC();
  
  cohort[pichrt].yrfluxResidueN = tem.ag.getYRFLUXRESIDUEN();

  cohort[pichrt].yrformPROD1C = tem.ag.getYRFORMPROD1C();
  
  cohort[pichrt].yrformPROD10C = tem.ag.getYRFORMPROD10C();
  
  cohort[pichrt].yrformPROD100C = tem.ag.getYRFORMPROD100C();

  cohort[pichrt].yrformPROD1N = tem.ag.getYRFORMPROD1N();
  
  cohort[pichrt].yrformPROD10N = tem.ag.getYRFORMPROD10N();
  
  cohort[pichrt].yrformPROD100N = tem.ag.getYRFORMPROD100N();
  
  cohort[pichrt].yrformResidueC = tem.ag.getYRFORMRESIDUEC();
  
  cohort[pichrt].yrformResidueN = tem.ag.getYRFORMRESIDUEN();

  cohort[pichrt].yrformTOTPRODC = tem.ag.getYRFORMTOTPRODC();

  cohort[pichrt].yrformTOTPRODN = tem.ag.getYRFORMTOTPRODN();

  cohort[pichrt].yrfpc = tem.veg.getYRFPC();

  cohort[pichrt].yrgmin = tem.microbe.getYRGMIN();
  
  cohort[pichrt].yrgpp = tem.veg.getYRGPP();
  
  cohort[pichrt].yrgpr = tem.veg.getYRGPR();
  
  cohort[pichrt].yrh2oyld = tem.soil.getYRH2OYIELD();
  
  cohort[pichrt].yrimmob = tem.microbe.getYRIMMB();

  cohort[pichrt].yrimmobabN = tem.soil.getYRABNIMMOB();

  cohort[pichrt].yrimmobNH4 = tem.microbe.getYRIMMNH4();
  
  cohort[pichrt].yrineet = tem.soil.getYRINEET();
  
  cohort[pichrt].yringpp = tem.veg.getYRINGPP();
  
  cohort[pichrt].yrinnpp = tem.veg.getYRINNPP();
  
  cohort[pichrt].yrinnup = tem.veg.getYRINNUP();

  cohort[pichrt].yrinnupNH4 = tem.veg.getYRINNH4UP();

  cohort[pichrt].yrinnupNO3 = tem.veg.getYRINNO3UP();
  
  cohort[pichrt].yrirrig = tem.ag.getYRIRRIG();
  
  cohort[pichrt].yrlai = tem.veg.getYRLAI();
    
  cohort[pichrt].yrleaf = tem.veg.getYRLEAF();

  cohort[pichrt].yrltrfalc = tem.veg.getYRLTRFALC();

  cohort[pichrt].yrltrfaln = tem.veg.getYRLTRFALN();  	
  
  cohort[pichrt].yrN2flx = tem.soil.getYRN2FLX();
   
  cohort[pichrt].yrN2Oflx = tem.soil.getYRN2OFLX();

  cohort[pichrt].yrNH3flx = tem.soil.getYRNH3FLX();

  cohort[pichrt].yrNOflx = tem.soil.getYRNOFLX();
   
  cohort[pichrt].yrN2prd = tem.microbe.getYRN2PRD();
   
  cohort[pichrt].yrN2Oprd = tem.microbe.getYRN2OPRD();
 
  cohort[pichrt].yrnce = tem.getYRNCE();

  cohort[pichrt].yrndep = tem.atms.getYRTOTNDEP();
  
  cohort[pichrt].yrndepNH4 = tem.atms.getYRNH4DEP();
  
  cohort[pichrt].yrndepNO3 = tem.atms.getYRNO3DEP();
  
  cohort[pichrt].yrnecb = tem.getYRNECB();  

  cohort[pichrt].yrnenb = tem.getYRNENB();  

  cohort[pichrt].yrnep = tem.getYRNEP();
  
  cohort[pichrt].yrNfixBiol = tem.getYRBNFIX();

  cohort[pichrt].yrNfixAsymb = tem.microbe.getYRNFIX();

  cohort[pichrt].yrNfixSymb = tem.veg.getYRNFIX();
  
  cohort[pichrt].yrNH4leach = tem.soil.getYRLCHNH4();

  cohort[pichrt].yrninput = tem.soil.getYRNINPUT();

  cohort[pichrt].yrnitrif = tem.microbe.getYRNITRIF();
  
  cohort[pichrt].yrnlost = tem.soil.getYRNLOST();
  
  cohort[pichrt].yrnmin = tem.microbe.getYRNMIN();
    
  cohort[pichrt].yrNOprd = tem.microbe.getYRNOPRD();
  
  cohort[pichrt].yrNO3leach = tem.soil.getYRLCHNO3();

  cohort[pichrt].yrNO3prd = tem.microbe.getYRNO3PRD();
  
  cohort[pichrt].yrnpp = tem.veg.getYRNPP();
  
  cohort[pichrt].yrnrent = tem.ag.getYRNRENT(); 
  
  cohort[pichrt].yrnsrent = tem.ag.getYRNSRENT();
  
  cohort[pichrt].yrnup = tem.veg.getYRNUP();

  cohort[pichrt].yrnupNH4 = tem.veg.getYRNH4UP();

  cohort[pichrt].yrnupNO3 = tem.veg.getYRNO3UP();

  cohort[pichrt].yrnvrent = tem.ag.getYRNVRENT();
  
  cohort[pichrt].yrpet = tem.atms.getYRPET();
  
  cohort[pichrt].yrPOCerode = tem.soil.getYRERODEPOC();

  cohort[pichrt].yrPONerode = tem.soil.getYRERODEPON();
  
  cohort[pichrt].yrrgrndh2o = tem.soil.getYRRGRNDH2O(); 
  
  cohort[pichrt].yrrh = tem.microbe.getYRRH();
    
   cohort[pichrt].yrrain = tem.atms.getYRRAIN();
  
  cohort[pichrt].yrrperc = tem.soil.getYRRPERC();
  
  cohort[pichrt].yrrrun = tem.soil.getYRRRUN();

  cohort[pichrt].yrsconvrtC = tem.ag.getYRSCONVRTC();

  cohort[pichrt].yrsconvrtN = tem.ag.getYRSCONVRTN();
  
  cohort[pichrt].yrsgrndh2o = tem.soil.getYRSGRNDH2O();

  cohort[pichrt].yrslashC = tem.ag.getYRSLASHC();

  cohort[pichrt].yrslashN = tem.ag.getYRSLASHN();
  
  cohort[pichrt].yrsnowfall = tem.atms.getYRSNOWFALL();

  cohort[pichrt].yrsnowinf = tem.soil.getYRSNOWINF();

  cohort[pichrt].yrsnowpack = tem.soil.getYRSNOWPACK();
  
  cohort[pichrt].yrsoilavlH2O = tem.soil.getYRAVLH2O();
  
  cohort[pichrt].yrsoilavlN = tem.soil.getYRAVLN();

  cohort[pichrt].yrsoilavlNH4 = tem.soil.getYRAVLNH4();

  cohort[pichrt].yrsoilavlNO3 = tem.soil.getYRAVLNO3();
  
  cohort[pichrt].yrsoilDOC = tem.soil.getYRDOC();
  
  cohort[pichrt].yrsoilDON = tem.soil.getYRDON();
  
  cohort[pichrt].yrsoilmoist = tem.soil.getYRSMOIST();
  
  cohort[pichrt].yrsoilnonorgC = tem.soil.getYRNONORGC();
  
  cohort[pichrt].yrsoilnonorgN = tem.soil.getYRNONORGN();
  
  cohort[pichrt].yrsoilorgC = tem.soil.getYRORGC();
  
  cohort[pichrt].yrsoilorgN = tem.soil.getYRORGN();

  cohort[pichrt].yrsoilpctp = tem.soil.getYRPCTP();
  
  cohort[pichrt].yrsoilResp = tem.getYRRSOIL();
  
  cohort[pichrt].yrsoiltotorgC = tem.soil.getYRTOTORGC();

  cohort[pichrt].yrsoiltotorgN = tem.soil.getYRTOTORGN();
  
  cohort[pichrt].yrsoilvsm = tem.soil.getYRVSM();

  cohort[pichrt].yrsperc = tem.soil.getYRSPERC();
  
  cohort[pichrt].yrsrun = tem.soil.getYRSRUN();

  cohort[pichrt].yrSTMdst0 = tem.soil.stm.getYRDST0();

  cohort[pichrt].yrSTMdst5 = tem.soil.stm.getYRDST5();

  cohort[pichrt].yrSTMdst10 = tem.soil.getYRDST10();

  cohort[pichrt].yrSTMdst20 = tem.soil.stm.getYRDST20();

  cohort[pichrt].yrSTMdst50 = tem.soil.stm.getYRDST50();

  cohort[pichrt].yrSTMdst100 = tem.soil.stm.getYRDST100();

  cohort[pichrt].yrSTMdst200 = tem.soil.stm.getYRDST200();

  cohort[pichrt].yrSTMfrontd = tem.soil.stm.getYRFRONTD();

  cohort[pichrt].yrSTMfrontd2 = tem.soil.stm.getYRFRONTD2();

  cohort[pichrt].yrSTMthawbegin1 = tem.soil.stm.getYRTHAWBEGIN1();

  cohort[pichrt].yrSTMthawbegin2 = tem.soil.stm.getYRTHAWBEGIN2();

  cohort[pichrt].yrSTMthawend1 = tem.soil.stm.getYRTHAWEND1();

  cohort[pichrt].yrSTMthawend2 = tem.soil.stm.getYRTHAWEND2();

  cohort[pichrt].yrSTMtsoil = tem.soil.getYRTSOIL();
     
  cohort[pichrt].yrthawpct = tem.veg.getYRTHAWPCT();
  
  cohort[pichrt].yrtotalC = tem.getYRTOTALC();
  
  cohort[pichrt].yrunleaf = tem.veg.getYRUNLEAF();

  cohort[pichrt].yrvconvrtC = tem.ag.getYRVCONVRTC();
  
  cohort[pichrt].yrvconvrtN = tem.ag.getYRVCONVRTN();

  cohort[pichrt].yrvegabvgrndResp = tem.veg.getYRABVGRNDRESP();
  
  cohort[pichrt].yrvegC = tem.veg.getYRVEGC();
    
  cohort[pichrt].yrveglup = tem.veg.getYRLUP();

  cohort[pichrt].yrvegN = tem.veg.getYRVEGN();

  cohort[pichrt].yrvegnmobil = tem.veg.getYRNMOBIL();

  cohort[pichrt].yrvegnrsorb = tem.veg.getYRNRSORB();

  cohort[pichrt].yrvegrgrowth = tem.veg.getYRRGROWTH();

  cohort[pichrt].yrvegrmaint = tem.veg.getYRRMAINT();

  cohort[pichrt].yrvegrootResp = tem.veg.getYRROOTRESP();
  
  cohort[pichrt].yrvegstoN = tem.veg.getYRSTOREN();
  
  cohort[pichrt].yrvegstrN = tem.veg.getYRSTRUCTN();

  cohort[pichrt].yrvegsup = tem.veg.getYRSUP();

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TEMelmnt60::setCohortTEMState( const ElmntCohort60& firstchrt,
                                    ElmntCohort60& targetchrt )
{
  int dm;
  int dnode;
  int i;
  
  for( i = 0; i < MAXSTATE; ++i )
  {
    targetchrt.y[i] = firstchrt.y[i];
    targetchrt.prevy[i] = firstchrt.prevy[i];
  }

  targetchrt.aggrowdd = firstchrt.aggrowdd;

  targetchrt.agkd = firstchrt.agkd;

  targetchrt.c2n = firstchrt.c2n;
  
  targetchrt.cneven = firstchrt.cneven;

  targetchrt.convrtflx.carbon = firstchrt.convrtflx.carbon;
  targetchrt.convrtflx.nitrogen = firstchrt.convrtflx.nitrogen;

  targetchrt.cropprveetmx = firstchrt.cropprveetmx;

  targetchrt.cropprvleafmx = firstchrt.cropprvleafmx;

  targetchrt.cropprvpetmx = firstchrt.cropprvpetmx;

  targetchrt.cropResidue.carbon = firstchrt.cropResidue.carbon;
  targetchrt.cropResidue.nitrogen = firstchrt.cropResidue.nitrogen;

  targetchrt.croptopt = firstchrt.croptopt;

  targetchrt.distmnthcnt = firstchrt.distmnthcnt;

  for( dm = 0; dm < CYCLE; ++dm )
  {  
    targetchrt.dst10[dm] = firstchrt.dst10[dm];
  }

  targetchrt.eetmx = firstchrt.eetmx;

  targetchrt.firemnthcnt = firstchrt.firemnthcnt;

  targetchrt.firendep = firstchrt.firendep;

  targetchrt.formPROD10.carbon = firstchrt.formPROD10.carbon;
  targetchrt.formPROD10.nitrogen = firstchrt.formPROD10.nitrogen;

  targetchrt.formPROD100.carbon = firstchrt.formPROD100.carbon;
  targetchrt.formPROD100.nitrogen = firstchrt.formPROD100.nitrogen;

  targetchrt.fprevozone = firstchrt.fprevozone;

  for( dm = 0; dm < CYCLE; ++dm )
  {  
    targetchrt.initPROD1[dm].carbon = firstchrt.initPROD1[dm].carbon;
    targetchrt.initPROD1[dm].nitrogen = firstchrt.initPROD1[dm].nitrogen;
  }

  for( i = 0; i < 10; ++i )
  {
    targetchrt.initPROD10[i].carbon = firstchrt.initPROD10[i].carbon;
    targetchrt.initPROD10[i].nitrogen = firstchrt.initPROD10[i].nitrogen;
  }
    
  for( i = 0; i < 100; ++i )
  {
    targetchrt.initPROD100[i].carbon = firstchrt.initPROD100[i].carbon;
    targetchrt.initPROD100[i].nitrogen = firstchrt.initPROD100[i].nitrogen;
  }

  targetchrt.kd = firstchrt.kd;

  targetchrt.natprveetmx = firstchrt.natprveetmx;

  targetchrt.natprvleafmx = firstchrt.natprvleafmx;

  targetchrt.natprvpetmx = firstchrt.natprvpetmx;

  targetchrt.natseedC = firstchrt.natseedC;

  targetchrt.natseedSTRN = firstchrt.natseedSTRN;

  targetchrt.natseedSTON = firstchrt.natseedSTON;

  targetchrt.natsoil = firstchrt.natsoil;

  targetchrt.nattopt = firstchrt.nattopt;

  targetchrt.natyreet = firstchrt.natyreet;

  targetchrt.natyrpet = firstchrt.natyrpet;

  targetchrt.newleafmx =  firstchrt.newleafmx;

  targetchrt.newtopt = firstchrt.newtopt;

  targetchrt.nonsolc = firstchrt.nonsolc;

  targetchrt.nonsoln = firstchrt.nonsoln;

  targetchrt.nretent = firstchrt.nretent;

  targetchrt.nsretent = firstchrt.nsretent;

  targetchrt.nvretent = firstchrt.nvretent;

  targetchrt.petmx = firstchrt.petmx;

  targetchrt.prev2tair = firstchrt.prev2tair;

  targetchrt.prevco2 = firstchrt.prevco2;

  targetchrt.prevCropResidue.carbon = firstchrt.prevCropResidue.carbon;
  targetchrt.prevCropResidue.nitrogen = firstchrt.prevCropResidue.nitrogen;

  targetchrt.prevdst10 = firstchrt.prevdst10;

  targetchrt.prevPROD1.carbon = firstchrt.prevPROD1.carbon;
  targetchrt.prevPROD1.nitrogen = firstchrt.prevPROD1.nitrogen;

  targetchrt.prevPROD10.carbon = firstchrt.prevPROD10.carbon;
  targetchrt.prevPROD10.nitrogen = firstchrt.prevPROD10.nitrogen;

  targetchrt.prevPROD100.carbon = firstchrt.prevPROD100.carbon;
  targetchrt.prevPROD100.nitrogen = firstchrt.prevPROD100.nitrogen;

  targetchrt.prevspack = firstchrt.prevspack;

  targetchrt.prevtair = firstchrt.prevtair;
  
  targetchrt.prevunrmleaf = firstchrt.prevunrmleaf;

  targetchrt.productYear = firstchrt.productYear;
   
  targetchrt.prvcropnpp = firstchrt.prvcropnpp;

  targetchrt.prveetmx = firstchrt.prveetmx;

  targetchrt.prvleafmx = firstchrt.prvleafmx;

  targetchrt.prvpetmx = firstchrt.prvpetmx;

  targetchrt.qc = firstchrt.qc;

  targetchrt.sconvrtflx.carbon = firstchrt.sconvrtflx.carbon;
  targetchrt.sconvrtflx.nitrogen = firstchrt.sconvrtflx.nitrogen;

  targetchrt.slash.carbon = firstchrt.slash.carbon;
  targetchrt.slash.nitrogen = firstchrt.slash.nitrogen;

  targetchrt.STMdst0 =  firstchrt.STMdst0;

  targetchrt.STMdst5 = firstchrt.STMdst5;

  targetchrt.STMdst10 = firstchrt.STMdst10;

  targetchrt.STMdst20 = firstchrt.STMdst20;

  targetchrt.STMdst50 = firstchrt.STMdst50;

  targetchrt.STMdst100 = firstchrt.STMdst100;

  targetchrt.STMdst200 =  firstchrt.STMdst200;

  targetchrt.STMfrontd = firstchrt.STMfrontd;

  targetchrt.STMfrontd2 =  firstchrt.STMfrontd2;

  targetchrt.STMis9 = firstchrt.STMis9;
  
  targetchrt.STMsmass9 = firstchrt.STMsmass9;

  targetchrt.STMthawbegin1 = firstchrt.STMthawbegin1;

  targetchrt.STMthawbegin2 = firstchrt.STMthawbegin2;

  targetchrt.STMthawend1 =  firstchrt.STMthawend1;

  targetchrt.STMthawend2 =  firstchrt.STMthawend2;

  targetchrt.STMtsoil = firstchrt.STMtsoil;

  
  for( dnode = 0; dnode < MAXNODES; ++dnode )
  {
    targetchrt.STMdx9[dnode] = firstchrt.STMdx9[dnode]; 
     
    targetchrt.STMt9[dnode] = firstchrt.STMt9[dnode];  
    
    targetchrt.STMwater9[dnode] = firstchrt.STMwater9[dnode];  
    
    targetchrt.STMx9[dnode] = firstchrt.STMx9[dnode];  

    targetchrt.STMxfa9[dnode] = firstchrt.STMxfa9[dnode];  

    targetchrt.STMxfb9[dnode] = firstchrt.STMxfb9[dnode];  
  }

  for( dnode = 0; dnode < MAXSNODES; ++dnode )
  {
    targetchrt.STMweight9[dnode] = firstchrt.STMweight9[dnode];  
  }

  targetchrt.topt = firstchrt.topt;

  targetchrt.tqc = firstchrt.tqc;

  targetchrt.vconvrtflx.carbon = firstchrt.vconvrtflx.carbon;
  targetchrt.vconvrtflx.nitrogen = firstchrt.vconvrtflx.nitrogen;
 
  targetchrt.yragstubC = firstchrt.yragstubC;
  
  targetchrt.yragstubN = firstchrt.yragstubN;

  targetchrt.yrammonvol = firstchrt.yrammonvol;
  
  targetchrt.yrcflux = firstchrt.yrcflux;
  
  targetchrt.yrconvrtC = firstchrt.yrconvrtC;
  
  targetchrt.yrconvrtN = firstchrt.yrconvrtN;
  
  targetchrt.yrdecayPROD1C = firstchrt.yrdecayPROD1C;
  
  targetchrt.yrdecayPROD10C = firstchrt.yrdecayPROD10C;
  
  targetchrt.yrdecayPROD100C = firstchrt.yrdecayPROD100C;

  targetchrt.yrdecayPROD1N = firstchrt.yrdecayPROD1N;
  
  targetchrt.yrdecayPROD10N = firstchrt.yrdecayPROD10N;
  
  targetchrt.yrdecayPROD100N = firstchrt.yrdecayPROD100N;
  
  targetchrt.yrdecayTOTPRODC = firstchrt.yrdecayTOTPRODC;

  targetchrt.yrdecayTOTPRODN = firstchrt.yrdecayTOTPRODN;
 
  targetchrt.yrdecompC = firstchrt.yrdecompC;

  targetchrt.yrdecompN = firstchrt.yrdecompN;
  
  targetchrt.yrdenitrif = firstchrt.yrdenitrif;

  targetchrt.yrDOCleach = firstchrt.yrDOCleach;
  
  targetchrt.yrDOCprod = firstchrt.yrDOCprod;

  targetchrt.yrDONleach = firstchrt.yrDONleach;
  
  targetchrt.yrDONprod = firstchrt.yrDONprod;
  
  targetchrt.yreet = firstchrt.yreet;
  
  targetchrt.yrfertn = firstchrt.yrfertn;
  
  targetchrt.yrfluxResidueC = firstchrt.yrfluxResidueC;
  
  targetchrt.yrfluxResidueN = firstchrt.yrfluxResidueN;

  targetchrt.yrformPROD1C = firstchrt.yrformPROD1C;
  
  targetchrt.yrformPROD10C = firstchrt.yrformPROD10C;
  
  targetchrt.yrformPROD100C = firstchrt.yrformPROD100C;

  targetchrt.yrformPROD1N = firstchrt.yrformPROD1N;
  
  targetchrt.yrformPROD10N = firstchrt.yrformPROD10N;
  
  targetchrt.yrformPROD100N = firstchrt.yrformPROD100N;
  
  targetchrt.yrformResidueC = firstchrt.yrformResidueC;
  
  targetchrt.yrformResidueN = firstchrt.yrformResidueN;

  targetchrt.yrformTOTPRODC = firstchrt.yrformTOTPRODC;

  targetchrt.yrformTOTPRODN = firstchrt.yrformTOTPRODN;

  targetchrt.yrfpc = firstchrt.yrfpc;

  targetchrt.yrgmin = firstchrt.yrgmin;
  
  targetchrt.yrgpp = firstchrt.yrgpp;
  
  targetchrt.yrgpr = firstchrt.yrgpr;
  
  targetchrt.yrh2oyld = firstchrt.yrh2oyld;
  
  targetchrt.yrimmob = firstchrt.yrimmob;

  targetchrt.yrimmobabN = firstchrt.yrimmobabN;

  targetchrt.yrimmobNH4 = firstchrt.yrimmobNH4;
  
  targetchrt.yrineet = firstchrt.yrineet;
  
  targetchrt.yringpp = firstchrt.yringpp;
  
  targetchrt.yrinnpp = firstchrt.yrinnpp;
  
  targetchrt.yrinnup = firstchrt.yrinnup;

  targetchrt.yrinnupNH4 = firstchrt.yrinnupNH4;

  targetchrt.yrinnupNO3 = firstchrt.yrinnupNO3;
  
  targetchrt.yrirrig = firstchrt.yrirrig;
  
  targetchrt.yrlai = firstchrt.yrlai;
    
  targetchrt.yrleaf = firstchrt.yrleaf;

  targetchrt.yrltrfalc = firstchrt.yrltrfalc;

  targetchrt.yrltrfaln = firstchrt.yrltrfaln;  	
  
  targetchrt.yrN2flx = firstchrt.yrN2flx;
   
  targetchrt.yrN2Oflx = firstchrt.yrN2Oflx;

  targetchrt.yrNH3flx = firstchrt.yrNH3flx;

  targetchrt.yrNOflx = firstchrt.yrNOflx;
   
  targetchrt.yrN2prd = firstchrt.yrN2prd;
   
  targetchrt.yrN2Oprd = firstchrt.yrN2Oprd;
 
  targetchrt.yrnce = firstchrt.yrnce;

  targetchrt.yrndep = firstchrt.yrndep;
  
  targetchrt.yrndepNH4 = firstchrt.yrndepNH4;
  
  targetchrt.yrndepNO3 = firstchrt.yrndepNO3;
  
  targetchrt.yrnecb = firstchrt.yrnecb;  

  targetchrt.yrnenb = firstchrt.yrnenb;  

  targetchrt.yrnep = firstchrt.yrnep;
  
  targetchrt.yrNfixBiol = firstchrt.yrNfixBiol;

  targetchrt.yrNfixAsymb = firstchrt.yrNfixAsymb;

  targetchrt.yrNfixSymb = firstchrt.yrNfixSymb;
  
  targetchrt.yrNH4leach = firstchrt.yrNH4leach;

  targetchrt.yrninput = firstchrt.yrninput;

  targetchrt.yrnitrif = firstchrt.yrnitrif;
  
  targetchrt.yrnlost = firstchrt.yrnlost;
  
  targetchrt.yrnmin = firstchrt.yrnmin;
    
  targetchrt.yrNOprd = firstchrt.yrNOprd;
  
  targetchrt.yrNO3leach = firstchrt.yrNO3leach;

  targetchrt.yrNO3prd = firstchrt.yrNO3prd;
  
  targetchrt.yrnpp = firstchrt.yrnpp;
  
  targetchrt.yrnrent = firstchrt.yrnrent; 
  
  targetchrt.yrnsrent = firstchrt.yrnsrent;
  
  targetchrt.yrnup = firstchrt.yrnup;

  targetchrt.yrnupNH4 = firstchrt.yrnupNH4;

  targetchrt.yrnupNO3 = firstchrt.yrnupNO3;

  targetchrt.yrnvrent = firstchrt.yrnvrent;
  
  targetchrt.yrpet = firstchrt.yrpet;
  
  targetchrt.yrPOCerode = firstchrt.yrPOCerode;

  targetchrt.yrPONerode = firstchrt.yrPONerode;
  
  targetchrt.yrrgrndh2o = firstchrt.yrrgrndh2o; 
  
  targetchrt.yrrh = firstchrt.yrrh;
    
  targetchrt.yrrain = firstchrt.yrrain;
  
  targetchrt.yrrperc = firstchrt.yrrperc;
  
  targetchrt.yrrrun = firstchrt.yrrrun;

  targetchrt.yrsconvrtC = firstchrt.yrsconvrtC;

  targetchrt.yrsconvrtN = firstchrt.yrsconvrtN;
  
  targetchrt.yrsgrndh2o = firstchrt.yrsgrndh2o;

  targetchrt.yrslashC = firstchrt.yrslashC;

  targetchrt.yrslashN = firstchrt.yrslashN;
  
  targetchrt.yrsnowfall = firstchrt.yrsnowfall;

  targetchrt.yrsnowinf = firstchrt.yrsnowinf;

  targetchrt.yrsnowpack = firstchrt.yrsnowpack;
  
  targetchrt.yrsoilavlH2O = firstchrt.yrsoilavlH2O;
  
  targetchrt.yrsoilavlN = firstchrt.yrsoilavlN;

  targetchrt.yrsoilavlNH4 = firstchrt.yrsoilavlNH4;

  targetchrt.yrsoilavlNO3 = firstchrt.yrsoilavlNO3;
  
  targetchrt.yrsoilDOC = firstchrt.yrsoilDOC;
  
  targetchrt.yrsoilDON = firstchrt.yrsoilDON;
  
  targetchrt.yrsoilmoist = firstchrt.yrsoilmoist;
  
  targetchrt.yrsoilnonorgC = firstchrt.yrsoilnonorgC;
  
  targetchrt.yrsoilnonorgN = firstchrt.yrsoilnonorgN;
  
  targetchrt.yrsoilorgC = firstchrt.yrsoilorgC;
  
  targetchrt.yrsoilorgN = firstchrt.yrsoilorgN;

  targetchrt.yrsoilpctp = firstchrt.yrsoilpctp;
  
  targetchrt.yrsoilResp = firstchrt.yrsoilResp;
  
  targetchrt.yrsoiltotorgC = firstchrt.yrsoiltotorgC;

  targetchrt.yrsoiltotorgN = firstchrt.yrsoiltotorgN;
  
  targetchrt.yrsoilvsm = firstchrt.yrsoilvsm;

  targetchrt.yrsperc = firstchrt.yrsperc;
  
  targetchrt.yrsrun = firstchrt.yrsrun;

  targetchrt.yrSTMdst0 = firstchrt.yrSTMdst0;

  targetchrt.yrSTMdst5 = firstchrt.yrSTMdst5;

  targetchrt.yrSTMdst10 = firstchrt.yrSTMdst10;

  targetchrt.yrSTMdst20 = firstchrt.yrSTMdst20;

  targetchrt.yrSTMdst50 = firstchrt.yrSTMdst50;

  targetchrt.yrSTMdst100 = firstchrt.yrSTMdst100;

  targetchrt.yrSTMdst200 = firstchrt.yrSTMdst200;

  targetchrt.yrSTMfrontd = firstchrt.yrSTMfrontd;

  targetchrt.yrSTMfrontd2 = firstchrt.yrSTMfrontd2;

  targetchrt.yrSTMthawbegin1 = firstchrt.yrSTMthawbegin1;

  targetchrt.yrSTMthawbegin2 = firstchrt.yrSTMthawbegin2;

  targetchrt.yrSTMthawend1 = firstchrt.yrSTMthawend1;

  targetchrt.yrSTMthawend2 = firstchrt.yrSTMthawend2;

  targetchrt.yrSTMtsoil = firstchrt.yrSTMtsoil;
     
  targetchrt.yrthawpct = firstchrt.yrthawpct;
  
  targetchrt.yrtotalC = firstchrt.yrtotalC;
  
  targetchrt.yrunleaf = firstchrt.yrunleaf;

  targetchrt.yrvconvrtC = firstchrt.yrvconvrtC;
  
  targetchrt.yrvconvrtN = firstchrt.yrvconvrtN;

  targetchrt.yrvegabvgrndResp = firstchrt.yrvegabvgrndResp;
  
  targetchrt.yrvegC = firstchrt.yrvegC;
    
  targetchrt.yrveglup = firstchrt.yrveglup;

  targetchrt.yrvegN = firstchrt.yrvegN;

  targetchrt.yrvegnmobil = firstchrt.yrvegnmobil;

  targetchrt.yrvegnrsorb = firstchrt.yrvegnrsorb;

  targetchrt.yrvegrgrowth = firstchrt.yrvegrgrowth;

  targetchrt.yrvegrmaint = firstchrt.yrvegrmaint;

  targetchrt.yrvegrootResp = firstchrt.yrvegrootResp;
  
  targetchrt.yrvegstoN = firstchrt.yrvegstoN;
  
  targetchrt.yrvegstrN = firstchrt.yrvegstrN;

  targetchrt.yrvegsup = firstchrt.yrvegsup;

};

/* *************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

int TEMelmnt60::setGIStopography( ofstream& rflog1,
                                  int& ftlerr,
                                  FILE* fstxt,
                                  FILE* felev )
{

  int gisend;

  Soildata60 fao;
  Elevdata60 elv;

  gisend = fao.getdel( fstxt );
 
  if( -1 == gisend )
  {
    rflog1 << "Ran out of Soil texture data" << endl << endl;
 
    exit( -1 );
  }
  
  ftlerr = coregerr( rflog1,
                     "Climate",
                     col,
                     row,
                     "TEXTURE",
                     fao.col,
                     fao.row );

  tem.soil.setPCTSILT( fao.pctsilt );
  tem.soil.setPCTCLAY( fao.pctclay );

  gisend = elv.getdel( felev );
  
  if( gisend == -1 )
  {
    rflog1 << "Ran out of Elevation data" << endl << endl;
 
    exit( -1 );
  }
  
  ftlerr = coregerr( rflog1,
                     "Climate",
                     col,
                     row,
                     "ELEV",
                     elv.col,
                     elv.row );

  tem.elev = elv.elev;

  return gisend;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TEMelmnt60::setTEMequilState( ofstream& rflog1,
                                   const int& equil,
                                   const int& totsptime,
                                   const int& pichrt )
{
  int dm;

  const int dyr = 0;


  // Set all TEM state-related variables in cohort to MISSING
  //   (i.e. start with "clean slate" in cohort)
   
  initializeCohortTEMState( pichrt );

  // Assign cohort data to TEM (i.e. transfer information from 
  //   the land cover/land use module to TEM and start with 
  //   "clean slate" for TEM cohort data)
   
  dm = 0;  
  getTEMCohortState( pichrt, dm );
  
  
  cohort[pichrt].qc = ACCEPT;
  cohort[pichrt].tqc = ACCEPT;

  tem.qualcon[dyr] = 0;

  tem.totyr = 0;

  tem.atms.setMXTAIR( mxtair );
  tem.atms.setYRPREC( yrprec );

  // Check TEM climate input for valid data 

  for( dm = 0; dm < CYCLE; ++dm )
  {                                
    tem.atms.setGIRR( climate[clm.I_GIRR][dm] );
    tem.atms.setCLDS( climate[clm.I_CLDS][dm] );
    tem.atms.setNIRR( climate[clm.I_NIRR][dm] );
    tem.atms.setPAR(  climate[clm.I_PAR][dm] );
    tem.atms.setTAIR( climate[clm.I_TAIR][dm] );
    tem.atms.setRAIN( climate[clm.I_RAIN][dm] );
    tem.atms.setSNOWFALL( climate[clm.I_SNWFAL][dm] );
    tem.atms.setCO2( climate[clm.I_CO2][dm] );
    tem.atms.setAOT40( climate[clm.I_AOT40][dm] );
    tem.atms.setTOTNDEP( climate[clm.I_TNDEP][dm] );
    tem.atms.setNH4DEP( climate[clm.I_NH4DEP][dm] );
    tem.atms.setNO3DEP( climate[clm.I_NO3DEP][dm] );
   
    cohort[pichrt].qc = temgisqc( cohort[pichrt].chrtarea,
                                  tem.soil.getPCTSILT(),
                                  tem.soil.getPCTCLAY(),
                                  tem.veg.cmnt,
                                  tem.elev,
                                  tem.atms.getNIRR(),
                                  tem.atms.getPAR(),
                                  tem.atms.getTAIR(),
                                  tem.atms.getMXTAIR(),
                                  avetair,
                                  tem.atms.getYRPREC(),
                                  tem.atms.getRAIN(),
                                  tem.atms.getSNOWFALL(),
                                  tem.atms.getCO2(),
                                  tem.atms.getAOT40(),
                                  tem.atms.getNDEP() );

    if( cohort[pichrt].qc != ACCEPT ) 
    { 
      rflog1 << "temgisqc = " << cohort[pichrt].qc;
      rflog1 << " during month " << (dm+1) << endl;
      break; 
    }
      
    // Determine initial values for tem.atms.prvpetmx, 
    //   tem.atms.prveetmx and and tem.veg.topt based on
    //   long-term mean climate

    tem.setEquilEvap( tem.atms.getNIRR(), 
                      tem.atms.getTAIR(), 
                      dm );


    // Set initial value of soil temperature at 10 cm for cohort
    //   to zero for all months (value will later be updated 
    //   monthly) for use as tem.soil.nextdst10 
     
    cohort[pichrt].dst10[dm] = avetair;
  }

  // Initialize all fluxes and disturbance-related variables to zero

  tem.ag.setNATSEEDC( ZERO );
  tem.ag.setNATSEEDSTRN( ZERO );
  tem.ag.setNATSEEDSTON( ZERO );
  tem.ag.setCROPPRVLEAFMX( ZERO );
  tem.ag.setCROPTOPT( ZERO );
  tem.ag.setCROPPRVPETMX( ZERO );
  tem.ag.setCROPPRVEETMX( ZERO );
  tem.ag.setPRVCROPNPP( ZERO );

  tem.ag.resetMonthlyDisturbFluxes();
  tem.resetMonthlyELMNTFluxes();
  tem.resetYrFluxes();
  

    
  // Check TEM parameters for specific vegetation types

  if( ACCEPT == cohort[pichrt].qc ) 
  { 
    cohort[pichrt].qc = tem.ecdqc( tem.veg.cmnt ); 

    if( cohort[pichrt].qc != ACCEPT )
    {
      // Note: If a TEM parameter is invalid, 
      //   cohort[pichrt].qc will have a value greater than 
      //   100
      	
      rflog1 << "temecdqc = " << cohort[pichrt].qc << endl;
    }
  }

  if( cohort[pichrt].qc != ACCEPT )
  {
    // If environmental conditions are too extreme for the 
    //   existence of vegetation (e.g., no precipitation or 
    //   constant freezing air temperatures), assign zero to 
    //   all TEM variables if the plant community is anything
    //   besides ice and open water; and all TEM parameters 
    //   are valid (i.e. cohort[pichrt].qc < 100 )

    if( cohort[pichrt].qc < 100
         && tem.veg.cmnt > 1 
         && (mxtair <= -1.0 || yrprec <= ZERO) )
    {
      // Set tqc flag to assign zero to all TEM variables 
      //   during simulation
      	
      cohort[pichrt].tqc = TQCZEROFLAG; 
    }
    else { cohort[pichrt].tqc = REJECT; }

    // Set missing values to telmnt[0].output

    setTEMmiss( dyr,
                equil,
                totsptime,
                pichrt  );
  }
  else // "cohort[pichrt].qc == ACCEPT"
  {

/* *************************************************************
                   Start Equilibrium Conditions
************************************************************* */

    // Determine soil properties of element based on 
    //   soil texture
    
    tem.soil.xtext( tem.veg.cmnt, 
                    tem.soil.getPCTSILT(), 
                    tem.soil.getPCTCLAY() );


    // Initialize tem.atms.prevco2

    tem.atms.setPREVCO2( climate[clm.I_CO2][CYCLE-1] );


    // Initialize TEM parameters based on element's 
    //   (i.e. grid cell) vegetation type, soil texture
    //   and atmospheric CO2 concentration
      
    tem.setELMNTecd( tem.veg.cmnt, tem.soil.getPSIPLUSC() );

    tem.setEquilC2N( tem.veg.cmnt, 
                     tem.atms.getPREVCO2() );


    // Assume potential vegetation when determining 
    //   equilibrium conditions

    tem.ag.state = 0;
    tem.ag.prvstate = 0;

    tem.ag.tillflag = 0;
    tem.ag.fertflag = 0;
    tem.ag.irrgflag = 0;

    tem.disturbflag = 0;
    tem.distmnthcnt = 0;


   // Initialize agricultural growing degree days to zero

    tem.ag.setGROWDD( ZERO );
                      

    // "While" loop to allow adaptive integrator tolerance 
    //   (i.e. tem.tol) to be reduced if chaotic behavior 
    //   occurs.  Try up to "tem.maxnrun" times to equilibrate 
    //   TEM.  If TEM does not equilibrate within "tem.runsize" 
    //   iterations, decrease tem.tol by an order of magnitude
    //   and try again
     
    tem.nattempt = 0;
    tem.tol = tem.inittol;
    tem.baseline = tem.initbase;
    tem.initFlag = 0;
        
    while( tem.nattempt < tem.maxnrun 
           && 0 == tem.initFlag )
    {               
      tem.nattempt = equilibrateTEM( pichrt, 
	                             tem.tol, 
	                             rflog1 );
	                               
      if( tem.nattempt < tem.maxnrun 
          && 0 == tem.initFlag ) 
      { 
      	tem.tol /= 10.0; 
      }
    }

    // Update summary variables for initial agricultural 
    //   state of cohort at end of equilibrium portion 
    //   of the TEM simulation

    tem.ag.setNATSEEDC( ZERO );
    tem.ag.setNATSEEDSTRN( ZERO );
    tem.ag.setNATSEEDSTON( ZERO );
    tem.ag.setCROPPRVLEAFMX( 1.0 );
    tem.ag.setCROPTOPT( tem.veg.getTOPT() );
    tem.ag.setCROPPRVPETMX( tem.atms.getPRVPETMX() );
    tem.ag.setCROPPRVEETMX( tem.soil.getPRVEETMX() );
    tem.ag.setPRVCROPNPP( ZERO );


    // Save quality control information about the simulation 
    //   conditions when the equilibrium portion ended
    //   (i.e. did the carbon and nitrogen fluxes really come 
    //         to equilibrium or was the run terminated after
    //         running chaotically for a specified maximum
    //         number of years?) 

    tem.qualcon[dyr] += (tem.nattempt + 1);
    

    // If simulation is part of a transient simulation, reset
    //   tem.totyr to represent an actual year rather than 
    //   the number of iterations required to reach equilibrum
    
    if( 0 == equil )
    {
      tem.totyr = clm.startyr - totsptime - 1;
      ttotyr[dyr] = tem.totyr;
      
      cohort[pichrt].tqc = transqc( tem.ag.cmnt,
                                    tem.maxyears, 
	                            tem.totyr, 
	                            output[tem.I_VEGC] );
    }
    else { ttotyr[dyr] = tem.totyr; }
  } // End of "cohort.qc == ACCEPT"


  // Save TEM state of cohort to telmnt[0].cohort

  saveTEMCohortState( pichrt );

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TEMelmnt60::setTEMmiss( const int& pdyr,
                             const int& equil,
                             const int& totsptime,
                             const int& pichrt )
{
  int dm;
  int i;
  
  if( 0 == equil )
  {
    ttotyr[pdyr] = clm.startyr 
                   - totsptime - 1 
                   + (pdyr * tem.diffyr);
  }
  else
  {
    ttotyr[pdyr] = -999;
  }

  tem.totyr = ttotyr[pdyr];

  if( TQCZEROFLAG == cohort[pichrt].tqc )
  {
    if( 1 == equil ) { ttotyr[pdyr] = 1; }

    // Assign zero to all TEM state variables
      
    for( i = 0; i < MAXSTATE; ++i )
    {
      tem.setY( ZERO, i );
      tem.setPREVY(ZERO, i );
    }

    for( i = MAXSTATE; i < NUMEQ; ++i )
    {
      tem.setY( ZERO, i );
    }
      
    // Assign zero to all TEM ouput variables
      
    for( i = 0; i < NUMTEM; ++i )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        output[i][dm] = ZERO;
      }
    }
  }
  else
  {
    // Assign missing values to grid cells where TEM did not 
    // converge on a solution 

    for( i = 0; i < MAXSTATE; ++i )
    {
      tem.setY( MISSING, i );
      tem.setPREVY( MISSING, i );
    }

    for( i = MAXSTATE; i < NUMEQ; ++i )
    {
      tem.setY( MISSING, i );
    }
      
    for( i = 0; i < NUMTEM; ++i )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        output[i][dm] = MISSING;
      }
    }
  }

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

int TEMelmnt60::temgisqc( const long& subarea,
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
                          const InorgN60& ndep )


{
  int qc;

  qc = ACCEPT;

  if( subarea < 1 ) { return qc = 1; }
  if( pctsilt < ZERO ) { return qc = 2; }
  if( pctclay < ZERO ) { return qc = 3; }
  if( cmnt < 1 || cmnt >= MAXCMNT ) { return qc = 4; }
  if( elev <= -999.0 ) { return qc = 5;}

  if( nirr <= -1.0 ) { return qc = 6; }
  if( par <= -1.0 ) { return qc = 7; }
  if( tair <= -99.0 ) { return qc = 8; }
  if( mxtair <= -1.0 ) { return qc = 9; }
  if( avtair <= -99.0 ) { return qc = 10; }
  if( yrprec <= ZERO ) { return qc = 11; }
  if( rain <= -1.0 ) { return qc = 12; }
  if( snowfall <= -1.0 ) { return qc = 13; }
  if( co2 <= -1.0 ) { return qc = 14; }
  if( aot40 <= -1.0 ) { return qc = 15; }
  if( ndep.nh4 <= -1.0 ) { return qc = 16; }
  if( ndep.no3 <= -1.0 ) { return qc = 17; }

  return qc;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TEMelmnt60::temwritepred( ofstream fout[NUMTEM],
                               const vector<string>& predname,
                               const int& pdyr,
                               const int& pichrt,
                               const int& ntempred )
{
  // Units conversion from grams to milligrams
  const double GRAMS2MG = 1000.0;
  
  // Units conversion from meters to millimeters
  const double METERS2MM = 1000.0;
  
  // Units conversion from proportion to percent
  const double PROP2PCT = 100.0;
  
  int i;
  int dm;
  Temdata60 tempred;


  for( i = 0; i < ntempred; ++i )
  {
    // ************** Carbon stocks in ecosystems  *************


    if( predname.at( i ) == tem.predstr.at( tem.I_VEGC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VEGC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SOLC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SOLC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DOC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DOC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NSOLC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NSOLC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TSOLC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TSOLC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTEC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTEC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTC][dm];
      }
    }


    // *************** Nitrogen stocks in ecosystems ***********

    else if( predname.at( i ) == tem.predstr.at( tem.I_STRN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_STRN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_STON ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_STON][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SOLN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SOLN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DON ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DON][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NH4 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NH4][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NO3 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NO3][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VEGN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VEGN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NSOLN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NSOLN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TSOLN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TSOLN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AVLN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AVLN][dm] * GRAMS2MG;
      }
    }

    // *****************Water stocks in ecosystems *************

    else if( predname.at( i ) == tem.predstr.at( tem.I_AVLW ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AVLW][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SM ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SM][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VSM ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VSM][dm] * PROP2PCT; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PCTP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PCTP][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SNWPCK ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SNWPCK][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RGRW ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RGRW][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SGRW ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SGRW][dm];
      }
    }


   // ******************** Phenology ***************************


    else if( predname.at( i ) == tem.predstr.at( tem.I_UNRMLF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_UNRMLF][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LEAF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LEAF][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LAI ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LAI][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FPC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FPC][dm] * PROP2PCT;
      }
    }


    // *************** Carbon fluxes in ecosystems *************


    else if( predname.at( i ) == tem.predstr.at( tem.I_INGPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_INGPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_GPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_GPP][dm];
      }
    }

    // *********************** Ozone Effects *******************

    else if( predname.at( i ) == tem.predstr.at( tem.I_FOZONE ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FOZONE][dm] * PROP2PCT;  

      }
    }
    else if( predname.at( i ) == tem.predstr.at( tem.I_FINDOZONE ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FINDOZONE][dm] * PROP2PCT;  

      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_INNPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_INNPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_GPR ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_GPR][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RVMNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RVMNT][dm];  
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RVGRW ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RVGRW][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_ABVGPR ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_ABVGPR][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_ROOTGPR ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_ROOTGPR][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LTRFALC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LTRFALC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CDCMP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CDCMP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RH ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RH][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RSOIL ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RSOIL][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FORAGEC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FORAGEC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_MANUREC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_MANUREC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_ANIMALR ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_ANIMALR][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DOCP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DOCP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LCHDOC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LCHDOC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NEP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NEP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NCE ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NCE][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LCHCO2 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LCHCO2][dm];
      }
    }

     else if( predname.at( i ) == tem.predstr.at( tem.I_NECB ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NECB][dm];
      }
    }

    // ************** Nitrogen fluxes in ecosystems ************


    else if( predname.at( i ) == tem.predstr.at( tem.I_AGFRTN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGFRTN][dm] * GRAMS2MG; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTNDEP ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTNDEP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NH4DEP ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NH4DEP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NO3DEP ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NO3DEP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FIRENTOTDEP ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FIRENTOTDEP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FIRENH4DEP ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FIRENH4DEP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FIRENO3DEP ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FIRENO3DEP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_BNFIX ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_BNFIX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SNFIX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SNFIX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_ANFIX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_ANFIX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_INNUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_INNUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_INNH4UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_INNH4UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_INNO3UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_INNO3UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNH4UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNH4UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNO3UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNO3UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VSUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VSUP][dm] * GRAMS2MG;  
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VLUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VLUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNMBL ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNMBL][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNRSRB ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNRSRB][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LTRFALN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LTRFALN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NDCMP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NDCMP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DONP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DONP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_GMIN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_GMIN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NH4IMM ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NH4IMM][dm] * GRAMS2MG;  
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NIMM ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NIMM][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NMIN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NMIN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AMMN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AMMN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NTRF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NTRF][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NO3P ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NO3P][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NOP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NOP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_N2OP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_N2OP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_N2P ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_N2P][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DNTRF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DNTRF][dm] * GRAMS2MG;  
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NH3FLX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NH3FLX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NOFLX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NOFLX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_N2OFLX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_N2OFLX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_N2FLX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_N2FLX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LCHNH4 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LCHNH4][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LCHNO3 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LCHNO3][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_LCHDON ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_LCHDON][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FORAGEN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FORAGEN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_MANUREN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_MANUREN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_URINE ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_URINE][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NINP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NINP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NLST ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NLST][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NENB ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NENB][dm];
      }
    }


    // *****************Water fluxes in ecosystems *************

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGIRRIG ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGIRRIG][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_INEET ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_INEET][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_EET ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_EET][dm];
      }
    }

   else if( predname.at( i ) == tem.predstr.at( tem.I_RPERC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RPERC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SPERC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SPERC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RRUN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RRUN][dm];
      }
    }


    else if( predname.at( i ) == tem.predstr.at( tem.I_SRUN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SRUN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PET ) )
    {
      for ( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PET][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SNWINF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SNWINF][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_WYLD ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_WYLD][dm];       
      }
    }


// ************** Carbon stocks in products ********************


    else if( predname.at( i ) == tem.predstr.at( tem.I_AGPRDC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGPRDC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PROD10C ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PROD10C][dm];      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PROD100C ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PROD100C][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTPRDC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTPRDC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RESIDC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RESIDC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGSTUBC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGSTUBC][dm];
      }
    }

    // ************** Nitrogen stocks in products **************


    else if( predname.at( i ) == tem.predstr.at( tem.I_AGPRDN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGPRDN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PROD10N ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PROD10N][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PROD100N ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PROD100N][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTPRDN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTPRDN][dm] * GRAMS2MG; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RESIDN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RESIDN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGSTUBN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGSTUBN][dm];  
      }
    }


    // *** Carbon fluxes during agricultural conversion ********


    else if( predname.at( i ) == tem.predstr.at( tem.I_CNVRTC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CNVRTC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VCNVRTC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VCNVRTC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SCNVRTC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SCNVRTC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SLASHC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SLASHC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CFLX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CFLX][dm];
      }
    }


    // *** Nitrogen fluxes during agricultural conversion ******


    else if( predname.at( i ) == tem.predstr.at( tem.I_CNVRTN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CNVRTN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VCNVRTN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VCNVRTN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SCNVRTN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SCNVRTN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SLASHN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
      	 tempred.mon[dm] = output[tem.I_SLASHN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NTOTRTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NTOTRTNT][dm]; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NH4RTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NH4RTNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NO3RTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NO3RTNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNTOTRTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNTOTRTNT][dm]; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNH4RTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNH4RTNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_VNO3RTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_VNO3RTNT][dm];
      }
    }


    else if( predname.at( i ) == tem.predstr.at( tem.I_SNTOTRTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SNTOTRTNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SNH4RTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SNH4RTNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_SNO3RTNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_SNO3RTNT][dm];
      }
    }


    // ************** Carbon fluxes to/from products ***********

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGFPRDC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGFPRDC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRDF10C ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRDF10C][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRDF100C ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRDF100C][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTFPRDC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTFPRDC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FRESIDC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FRESIDC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGPRDFC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGPRDFC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRD10FC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRD10FC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRD100FC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRD100FC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTPRDFC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTPRDFC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RESIDFC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RESIDFC][dm];
      }
    }

    // ************** Nitrogen fluxes to/from products *********


    else if( predname.at( i ) == tem.predstr.at( tem.I_AGFPRDN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGFPRDN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRDF10N ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRDF10N][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRDF100N ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRDF100N][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTFPRDN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTFPRDN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FRESIDN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FRESIDN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGPRDFN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGPRDFN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRD10FN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRD10FN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_PRD100FN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_PRD100FN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_TOTPRDFN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TOTPRDFN][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_RESIDFN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_RESIDFN][dm];
      }
    }

    // ************** Carbon stocks in crops   *****************


    else if( predname.at( i ) == tem.predstr.at( tem.I_CROPC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CROPC][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATVEGC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATVEGC][dm];
      }
    }


    // ************** Nitrogen stocks in crops *****************


    else if( predname.at( i ) == tem.predstr.at( tem.I_CROPN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CROPN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATVEGN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATVEGN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CSTRN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CSTRN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATSTRN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATSTRN][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CSTON ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CSTON][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATSTON ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATSTON][dm];
      }
    }

    // ******************** Crop Phenology *********************


    else if( predname.at( i ) == tem.predstr.at( tem.I_CROPULF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CROPULF][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATULF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATULF][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CROPLEAF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CROPLEAF][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATLEAF ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATLEAF][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CROPLAI ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CROPLAI][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATLAI ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATLAI][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_CROPFPC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_CROPFPC][dm] * PROP2PCT;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATFPC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATFPC][dm] * PROP2PCT;
      }
    }

    // ************** Carbon fluxes in croplands ***************

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGINGPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGINGPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATINGPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATINGPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGGPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGGPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATGPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATGPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGINNPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGINNPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATINNPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATINNPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGNPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGNPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATNPP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATNPP][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGGPR ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGGPR][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATGPR ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATGPR][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGRVMNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGRVMNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATRVMNT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATRVMNT][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGRVGRW ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGRVGRW][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATRVGRW ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATRVGRW][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGLTRC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGLTRC][dm]; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATLTRC ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATLTRC][dm];
      }
    }

    // ************** Nitrogen fluxes in croplands *************


    else if( predname.at( i ) == tem.predstr.at( tem.I_AGSNFX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGSNFX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATSNFX ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATSNFX][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGINNUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGINNUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATINNUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATINNUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AINNH4UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AINNH4UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NINNH4UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NINNH4UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AINNO3UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AINNO3UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NINNO3UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NINNO3UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVNUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVNUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATVNUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATVNUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVNH4UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVNH4UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NVNH4UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NVNH4UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVNO3UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVNO3UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NVNO3UP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NVNO3UP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVSUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVSUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATVSUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATVSUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVLUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVLUP][dm] * GRAMS2MG;  
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATVLUP ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATVLUP][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVNMBL ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVNMBL][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATVNMBL ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATVNMBL][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGVNRSRB ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGVNRSRB][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NVNRSRB ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NVNRSRB][dm] * GRAMS2MG;
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_AGLTRN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_AGLTRN][dm] * GRAMS2MG; 
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_NATLTRN ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_NATLTRN][dm] * GRAMS2MG;
      }
    }

    // ************** Soil temperature data ********************


    else if( predname.at( i ) == tem.predstr.at( tem.I_TSOIL ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_TSOIL][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST0 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST0][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST5 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST5][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST10 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST10][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST20 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST20][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST50 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST50][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST100 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST100][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_DST200 ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_DST200][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_FRONTD ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_FRONTD][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_THAWBE ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_THAWBE][dm];
      }
    }

    else if( predname.at( i ) == tem.predstr.at( tem.I_THAWEND ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_THAWEND][dm];
      }
    }

   // ************** Thaw percent (i.e., f(FT)) ****************

   else if( predname.at( i ) == tem.predstr.at( tem.I_THAWPCT ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_THAWPCT][dm] * PROP2PCT;
      }
    }


    else if( predname.at( i ) == tem.predstr.at( tem.I_ACTLAYER ) )
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = output[tem.I_ACTLAYER][dm] * METERS2MM;
      }
    }

    else
    {
      for( dm = 0; dm < CYCLE; ++dm )
      {
        tempred.mon[dm] = MISSING;
      }
    }

    // Write output data to files

    if( predname.at( i ) == tem.predstr.at( tem.I_VSM ) 
        || predname.at( i ) == tem.predstr.at( tem.I_PCTP ) 
        || predname.at( i ) == tem.predstr.at( tem.I_LEAF )
        || predname.at( i ) == tem.predstr.at( tem.I_THAWPCT )  
        || predname.at( i ) == tem.predstr.at( tem.I_FOZONE ) 
        || predname.at( i ) == tem.predstr.at( tem.I_FINDOZONE ) )
    {
      tempred.poutdel( fout[i],
                       col,
                       row,
                       predname.at( i ),
                       (pichrt+1),
                       cohort[pichrt].standage,
                       tem.veg.getPOTVEG(),
                       tem.veg.getCURRENTVEG(),
                       tem.veg.getSUBTYPE(),
                       tem.veg.cmnt,
                       tem.ag.state,
                       (PROP2PCT * tem.soil.getPSIPLUSC()),
                       tem.qualcon[pdyr],
                       carea,
                       cohort[pichrt].chrtarea,
                       ttotyr[pdyr],
                       tempred.mon,
                       region );
    }
    else
    {
      tempred.outdel( fout[i],
                      col,
                      row,
                      predname.at( i ),
                      (pichrt+1),
                      cohort[pichrt].standage,
                      tem.veg.getPOTVEG(),
                      tem.veg.getCURRENTVEG(),
                      tem.veg.getSUBTYPE(),
                      tem.veg.cmnt,
                      tem.ag.state,
                      (PROP2PCT * tem.soil.getPSIPLUSC()),
                      tem.qualcon[pdyr],
                      carea,
                      cohort[pichrt].chrtarea,
                      ttotyr[pdyr],
                      tempred.mon,
                      region );
    }
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int TEMelmnt60::transqc( const int& pcmnt,
                         int& maxyears,
                         int& totyr,
                         double plantc[CYCLE] )
{

  int dm;
  int qc;
  double sumcarbon = ZERO;
  qc = ACCEPT;

  if( totyr < 0 || totyr >= maxyears ) { return qc = 30; }

  if( pcmnt != ASPHALT && pcmnt != BAREGRND && pcmnt != LAKES )  
  {
    for( dm = 0; dm < CYCLE; ++dm ) { sumcarbon += plantc[dm]; }
  
    if( sumcarbon <= 0.1 ) { return qc = TQCZEROFLAG; }
  }

  return qc;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TEMelmnt60::updateTEMmonth( ofstream& rflog1,
                                 const int& equil,
                                 const int& totsptime,
                                 const int& pdyr,
                                 const int& pdm,
                                 const int& pichrt )
{  

  tem.dbug = 0;
  tem.veg.dbug = 0;


  // Pass cohort characteristics information to TEM
  
  getTEMCohortState( pichrt, pdm );


  if( ACCEPT == cohort[pichrt].qc 
      && ACCEPT == cohort[pichrt].tqc )
  {
    // Pass monthly climate information to TEM
                           
    tem.atms.setGIRR( climate[clm.I_GIRR][pdm] );
    tem.atms.setCLDS( climate[clm.I_CLDS][pdm] );
    tem.atms.setNIRR( climate[clm.I_NIRR][pdm] );
    tem.atms.setPAR(  climate[clm.I_PAR][pdm] );
    tem.atms.setTAIR( climate[clm.I_TAIR][pdm] );
    tem.atms.setRAIN( climate[clm.I_RAIN][pdm] );
    tem.atms.setSNOWFALL( climate[clm.I_SNWFAL][pdm] );
    tem.atms.setCO2( climate[clm.I_CO2][pdm] );
    tem.atms.setAOT40( climate[clm.I_AOT40][pdm] );
    tem.atms.setTOTNDEP( climate[clm.I_TNDEP][pdm] );
    tem.atms.setNH4DEP( climate[clm.I_NH4DEP][pdm] );
    tem.atms.setNO3DEP( climate[clm.I_NO3DEP][pdm] );
    tem.atms.setMXTAIR( mxtair );
    tem.atms.setYRPREC( yrprec );

    tem.soil.stm.setNEXTTAIR( climate[clm.I_TAIR][pdm+1] );
    tem.soil.stm.setNEXTSNOWFALL( climate[clm.I_SNWFAL][pdm+1] );


    // Determine CDM for current year for soil thermal model
    
    if( 0 == pdm )
    {
      tem.soil.stm.updateyrCDM( climate[clm.I_TAIR] ); 
    }

    
    tem.baseline = 0;
    tem.wrtyr = -99;

    tem.totyr = clm.startyr 
                - totsptime - 1 
                + (pdyr * tem.diffyr);


    if( 1 == tem.ag.state &&  tem.totyr >= 1950 )
    {
      tem.ag.fertflag = 1;
    }
    else
    {
      tem.ag.fertflag = 0;
    }


    // Run the Terrestrial Ecosystem Model (TEM) under 
    //   transient conditions

    wrtyr = tem.monthlyTransient( pdyr, 
                                  pdm, 
                                  tem.tol,
                                  rflog1 );
   

    // Update telmnt[0].cohort.dst10 for future use 
      
    cohort[pichrt].dst10[pdm] = tem.soil.getDST10();
      
      
    // Save TEM output to telmnt[0].output

    outputTEMmonth( pdm );

    ttotyr[pdyr] = tem.totyr;
  } // End of qc == ACCEPT and tqc = ACCEPT
  else
  {
    if( (CYCLE-1) == pdm )
    {
      // Set missing values to telmnt[0].output

      setTEMmiss( pdyr,
                  equil,
                  totsptime,
                  pichrt );
    }
  }  

  // Save TEM state for cohort
  
  saveTEMCohortState( pichrt );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::writeBinaryCohortState( ofstream& ofstate,
                                         const int& pichrt )
{
  int ichrt = pichrt;
  
  ofstate.write( (char *)(&col), sizeof( col ) );
  ofstate.write( (char *)(&row), sizeof( row ) );
  ofstate.write( (char *)(&ichrt), sizeof( ichrt ) ); 
  ofstate.write( (char *)(&cohort[pichrt]), sizeof( ElmntCohort60 ) );
  	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TEMelmnt60::writeCohortState( ofstream& ofstate,
                                   const int& pichrt )
{
  int dm;
  int dnode;
  int i;

  ofstate << col << " ";    
  ofstate << row << " ";
  ofstate << (pichrt+1) << " ";
  
  ofstate << cohort[pichrt].srcCohort << " ";
  ofstate << cohort[pichrt].standage << " ";
  ofstate << cohort[pichrt].chrtarea << " ";
  ofstate << cohort[pichrt].potveg << " ";
  ofstate << cohort[pichrt].currentveg << " ";
  ofstate << cohort[pichrt].subtype << " ";
  ofstate << cohort[pichrt].cmnt << " ";

 	
  for( i = 0; i < MAXSTATE; ++i )
  {
    ofstate << cohort[pichrt].y[i] << " ";
    ofstate << cohort[pichrt].prevy[i] << " ";
  }

  ofstate << cohort[pichrt].agcmnt << " ";

  ofstate << cohort[pichrt].aggrowdd << " ";

  ofstate << cohort[pichrt].agkd << " ";

  ofstate << cohort[pichrt].agprvstate << " ";

  ofstate << cohort[pichrt].agstate << " ";

  ofstate << cohort[pichrt].c2n << " ";
  
  ofstate << cohort[pichrt].cneven << " ";

  ofstate << cohort[pichrt].convrtflx.carbon << " ";
  ofstate << cohort[pichrt].convrtflx.nitrogen << " ";

  ofstate << cohort[pichrt].cropprveetmx << " ";

  ofstate << cohort[pichrt].cropprvleafmx << " ";

  ofstate << cohort[pichrt].cropprvpetmx << " ";

  ofstate << cohort[pichrt].cropResidue.carbon << " ";
  ofstate << cohort[pichrt].cropResidue.nitrogen << " ";

  ofstate << cohort[pichrt].croptopt << " ";

  ofstate << cohort[pichrt].distmnthcnt << " ";

  ofstate << cohort[pichrt].disturbflag << " ";
  
  ofstate << cohort[pichrt].disturbmonth << " ";
  
  for( dm = 0; dm < CYCLE; ++dm )
  {  
    ofstate << cohort[pichrt].dst10[dm] << " ";
  }

  ofstate << cohort[pichrt].eetmx << " ";

  ofstate << cohort[pichrt].fertflag << " ";                              

  ofstate << cohort[pichrt].firemnthcnt << " ";                              

  ofstate << cohort[pichrt].firendep.total << " ";                              
  ofstate << cohort[pichrt].firendep.nh4 << " ";
  ofstate << cohort[pichrt].firendep.no3 << " ";

  ofstate << cohort[pichrt].formPROD10.carbon << " ";
  ofstate << cohort[pichrt].formPROD10.nitrogen << " ";

  ofstate << cohort[pichrt].formPROD100.carbon << " ";
  ofstate << cohort[pichrt].formPROD100.nitrogen << " ";

  ofstate << cohort[pichrt].fprevozone << " ";

  ofstate << cohort[pichrt].FRI << " ";

  for( dm = 0; dm < CYCLE; ++dm )
  {  
    ofstate << cohort[pichrt].initPROD1[dm].carbon << " ";
    ofstate << cohort[pichrt].initPROD1[dm].nitrogen << " ";
  }

  for( i = 0; i < 10; ++i )
  {
    ofstate << cohort[pichrt].initPROD10[i].carbon << " ";
    ofstate << cohort[pichrt].initPROD10[i].nitrogen << " ";
  }
    
  for( i = 0; i < 100; ++i )
  {
    ofstate << cohort[pichrt].initPROD100[i].carbon << " ";
    ofstate << cohort[pichrt].initPROD100[i].nitrogen << " ";
  }

  ofstate << cohort[pichrt].irrgflag << " ";                              
  
  ofstate << cohort[pichrt].kd << " ";

  ofstate << cohort[pichrt].natprveetmx << " ";

  ofstate << cohort[pichrt].natprvleafmx << " ";

  ofstate << cohort[pichrt].natprvpetmx << " ";

  ofstate << cohort[pichrt].natseedC << " ";

  ofstate << cohort[pichrt].natseedSTRN << " ";

  ofstate << cohort[pichrt].natseedSTON << " ";

  ofstate << cohort[pichrt].natsoil << " ";

  ofstate << cohort[pichrt].nattopt << " ";

  ofstate << cohort[pichrt].natyreet << " ";

  ofstate << cohort[pichrt].natyrpet << " ";

  ofstate << cohort[pichrt].newleafmx << " ";

  ofstate << cohort[pichrt].newtopt << " ";

  ofstate << cohort[pichrt].nonsolc << " ";

  ofstate << cohort[pichrt].nonsoln << " ";

  ofstate << cohort[pichrt].nretent.total << " ";
  ofstate << cohort[pichrt].nretent.nh4 << " ";
  ofstate << cohort[pichrt].nretent.no3 << " ";

  ofstate << cohort[pichrt].nsretent.total << " ";
  ofstate << cohort[pichrt].nsretent.nh4 << " ";
  ofstate << cohort[pichrt].nsretent.no3 << " ";

  ofstate << cohort[pichrt].nvretent.total << " ";
  ofstate << cohort[pichrt].nvretent.nh4 << " "; 
  ofstate << cohort[pichrt].nvretent.no3 << " ";

  ofstate << cohort[pichrt].petmx << " ";

  ofstate << cohort[pichrt].prev2tair << " ";

  ofstate << cohort[pichrt].prevco2 << " ";

  ofstate << cohort[pichrt].prevCropResidue.carbon << " ";
  ofstate << cohort[pichrt].prevCropResidue.nitrogen << " ";

  ofstate << cohort[pichrt].prevdst10 << " ";

  ofstate << cohort[pichrt].prevPROD1.carbon << " ";
  ofstate << cohort[pichrt].prevPROD1.nitrogen << " ";

  ofstate << cohort[pichrt].prevPROD10.carbon << " ";
  ofstate << cohort[pichrt].prevPROD10.nitrogen << " ";

  ofstate << cohort[pichrt].prevPROD100.carbon << " ";
  ofstate << cohort[pichrt].prevPROD100.nitrogen << " ";

  ofstate << cohort[pichrt].prevspack << " ";

  ofstate << cohort[pichrt].prevtair << " ";

  ofstate << cohort[pichrt].prevunrmleaf << " ";
  
  ofstate << cohort[pichrt].prod10par << " "; 

  ofstate << cohort[pichrt].prod100par << " "; 

  ofstate << cohort[pichrt].productYear << " ";

  ofstate << cohort[pichrt].prvcropnpp << " ";

  ofstate << cohort[pichrt].prveetmx << " ";

  ofstate << cohort[pichrt].prvleafmx << " ";

  ofstate << cohort[pichrt].prvpetmx << " ";

  ofstate << cohort[pichrt].qc << " ";

  ofstate << cohort[pichrt].sconvert << " "; 
  
  ofstate << cohort[pichrt].sconvrtflx.carbon << " ";
  ofstate << cohort[pichrt].sconvrtflx.nitrogen << " ";
  
  ofstate << cohort[pichrt].slash.carbon << " ";
  ofstate << cohort[pichrt].slash.nitrogen << " ";

  ofstate << cohort[pichrt].slashpar << " "; 

  ofstate << cohort[pichrt].STMdst0 << " ";

  ofstate << cohort[pichrt].STMdst5 << " ";

  ofstate << cohort[pichrt].STMdst10 << " ";

  ofstate << cohort[pichrt].STMdst20 << " ";

  ofstate << cohort[pichrt].STMdst50 << " ";

  ofstate << cohort[pichrt].STMdst100 << " ";

  ofstate << cohort[pichrt].STMdst200 << " ";

  ofstate << cohort[pichrt].STMfrontd << " ";

  ofstate << cohort[pichrt].STMfrontd2 << " ";

  ofstate << cohort[pichrt].STMis9 << " ";
  
  ofstate << cohort[pichrt].STMsmass9 << " ";

  ofstate << cohort[pichrt].STMthawbegin1 << " ";

  ofstate << cohort[pichrt].STMthawbegin2 << " ";

  ofstate << cohort[pichrt].STMthawend1 << " ";

  ofstate << cohort[pichrt].STMthawend2 << " ";

  ofstate << cohort[pichrt].STMtsoil << " ";
  
  for( dnode = 0; dnode < MAXNODES; ++dnode )
  {
    ofstate << cohort[pichrt].STMdx9[dnode] << " "; 
    ofstate << cohort[pichrt].STMt9[dnode] << " ";  
    ofstate << cohort[pichrt].STMwater9[dnode] << " ";  
    ofstate << cohort[pichrt].STMx9[dnode] << " ";  
    ofstate << cohort[pichrt].STMxfa9[dnode] << " ";  
    ofstate << cohort[pichrt].STMxfb9[dnode] << " ";  
  }

  for( dnode = 0; dnode < MAXSNODES; ++dnode )
  {
    ofstate << cohort[pichrt].STMweight9[dnode] << " ";  
  }
      
  ofstate << cohort[pichrt].tillflag << " ";                           

  ofstate << cohort[pichrt].topt << " ";

  ofstate << cohort[pichrt].tqc << " ";

  ofstate << cohort[pichrt].vconvert << " "; 

  ofstate << cohort[pichrt].vconvrtflx.carbon << " ";
  ofstate << cohort[pichrt].vconvrtflx.nitrogen << " ";

  ofstate << cohort[pichrt].vrespar << " "; 
  
  ofstate << cohort[pichrt].wfpsoff << " ";

  ofstate << cohort[pichrt].yragstubC << " ";
  
  ofstate << cohort[pichrt].yragstubN << " ";

  ofstate << cohort[pichrt].yrammonvol << " ";
  
  ofstate << cohort[pichrt].yrcflux << " ";
  
  ofstate << cohort[pichrt].yrconvrtC << " ";
  
  ofstate << cohort[pichrt].yrconvrtN << " ";
  
  ofstate << cohort[pichrt].yrdecayPROD1C << " ";
  
  ofstate << cohort[pichrt].yrdecayPROD10C << " ";
  
  ofstate << cohort[pichrt].yrdecayPROD100C << " ";

  ofstate << cohort[pichrt].yrdecayPROD1N << " ";
  
  ofstate << cohort[pichrt].yrdecayPROD10N << " ";
  
  ofstate << cohort[pichrt].yrdecayPROD100N << " ";
  
  ofstate << cohort[pichrt].yrdecayTOTPRODC << " ";

  ofstate << cohort[pichrt].yrdecayTOTPRODN << " ";
 
  ofstate << cohort[pichrt].yrdecompC << " ";

  ofstate << cohort[pichrt].yrdecompN << " ";
  
  ofstate << cohort[pichrt].yrdenitrif << " ";

  ofstate << cohort[pichrt].yrDOCleach << " ";
  
  ofstate << cohort[pichrt].yrDOCprod << " ";

  ofstate << cohort[pichrt].yrDONleach << " ";
  
  ofstate << cohort[pichrt].yrDONprod << " ";
  
  ofstate << cohort[pichrt].yreet << " ";
  
  ofstate << cohort[pichrt].yrfertn << " ";
  
  ofstate << cohort[pichrt].yrfluxResidueC << " ";
  
  ofstate << cohort[pichrt].yrfluxResidueN << " ";

  ofstate << cohort[pichrt].yrformPROD1C << " ";
  
  ofstate << cohort[pichrt].yrformPROD10C << " ";
  
  ofstate << cohort[pichrt].yrformPROD100C << " ";

  ofstate << cohort[pichrt].yrformPROD1N << " ";
  
  ofstate << cohort[pichrt].yrformPROD10N << " ";
  
  ofstate << cohort[pichrt].yrformPROD100N << " ";
  
  ofstate << cohort[pichrt].yrformResidueC << " ";
  
  ofstate << cohort[pichrt].yrformResidueN << " ";

  ofstate << cohort[pichrt].yrformTOTPRODC << " ";

  ofstate << cohort[pichrt].yrformTOTPRODN << " ";

  ofstate << cohort[pichrt].yrfpc << " ";

  ofstate << cohort[pichrt].yrgmin << " ";
  
  ofstate << cohort[pichrt].yrgpp << " ";
  
  ofstate << cohort[pichrt].yrgpr << " ";
  
  ofstate << cohort[pichrt].yrh2oyld << " ";
  
  ofstate << cohort[pichrt].yrimmob << " ";

  ofstate << cohort[pichrt].yrimmobabN << " ";

  ofstate << cohort[pichrt].yrimmobNH4 << " ";
  
  ofstate << cohort[pichrt].yrineet << " ";
  
  ofstate << cohort[pichrt].yringpp << " ";
  
  ofstate << cohort[pichrt].yrinnpp << " ";
  
  ofstate << cohort[pichrt].yrinnup << " ";

  ofstate << cohort[pichrt].yrinnupNH4 << " ";

  ofstate << cohort[pichrt].yrinnupNO3 << " ";
  
  ofstate << cohort[pichrt].yrirrig << " ";
  
  ofstate << cohort[pichrt].yrlai << " ";
    
  ofstate << cohort[pichrt].yrleaf << " ";

  ofstate << cohort[pichrt].yrltrfalc << " ";

  ofstate << cohort[pichrt].yrltrfaln << " ";  	
  
  ofstate << cohort[pichrt].yrN2flx << " ";
   
  ofstate << cohort[pichrt].yrN2Oflx << " ";

  ofstate << cohort[pichrt].yrNH3flx << " ";

  ofstate << cohort[pichrt].yrNOflx << " ";
   
  ofstate << cohort[pichrt].yrN2prd << " ";
   
  ofstate << cohort[pichrt].yrN2Oprd << " ";
 
  ofstate << cohort[pichrt].yrnce << " ";

  ofstate << cohort[pichrt].yrndep << " ";
  
  ofstate << cohort[pichrt].yrndepNH4 << " ";
  
  ofstate << cohort[pichrt].yrndepNO3 << " ";
  
  ofstate << cohort[pichrt].yrnecb << " ";  

  ofstate << cohort[pichrt].yrnenb << " ";  

  ofstate << cohort[pichrt].yrnep << " ";
  
  ofstate << cohort[pichrt].yrNfixBiol << " ";

  ofstate << cohort[pichrt].yrNfixAsymb << " ";

  ofstate << cohort[pichrt].yrNfixSymb << " ";
  
  ofstate << cohort[pichrt].yrNH4leach << " ";

  ofstate << cohort[pichrt].yrninput << " ";

  ofstate << cohort[pichrt].yrnitrif << " ";
  
  ofstate << cohort[pichrt].yrnlost << " ";
  
  ofstate << cohort[pichrt].yrnmin << " ";
    
  ofstate << cohort[pichrt].yrNOprd << " ";
  
  ofstate << cohort[pichrt].yrNO3leach << " ";

  ofstate << cohort[pichrt].yrNO3prd << " ";
  
  ofstate << cohort[pichrt].yrnpp << " ";
  
  ofstate << cohort[pichrt].yrnrent.total << " "; 

  ofstate << cohort[pichrt].yrnrent.nh4 << " ";

  ofstate << cohort[pichrt].yrnrent.no3 << " ";
  
  ofstate << cohort[pichrt].yrnsrent.total << " ";

  ofstate << cohort[pichrt].yrnsrent.nh4 << " ";

  ofstate << cohort[pichrt].yrnsrent.no3 << " ";
  
  ofstate << cohort[pichrt].yrnup << " ";

  ofstate << cohort[pichrt].yrnupNH4 << " ";

  ofstate << cohort[pichrt].yrnupNO3 << " ";

  ofstate << cohort[pichrt].yrnvrent.total << " ";

  ofstate << cohort[pichrt].yrnvrent.nh4 << " ";

  ofstate << cohort[pichrt].yrnvrent.no3 << " ";
  
  ofstate << cohort[pichrt].yrpet << " ";
  
  ofstate << cohort[pichrt].yrPOCerode << " ";

  ofstate << cohort[pichrt].yrPONerode << " ";
  
  ofstate << cohort[pichrt].yrrgrndh2o << " "; 
  
  ofstate << cohort[pichrt].yrrh << " ";
    
  ofstate << cohort[pichrt].yrrain << " ";
  
  ofstate << cohort[pichrt].yrrperc << " ";
  
  ofstate << cohort[pichrt].yrrrun << " ";

  ofstate << cohort[pichrt].yrsconvrtC << " ";

  ofstate << cohort[pichrt].yrsconvrtN << " ";
  
  ofstate << cohort[pichrt].yrsgrndh2o << " ";

  ofstate << cohort[pichrt].yrslashC << " ";

  ofstate << cohort[pichrt].yrslashN << " ";
  
  ofstate << cohort[pichrt].yrsnowfall << " ";

  ofstate << cohort[pichrt].yrsnowinf << " ";

  ofstate << cohort[pichrt].yrsnowpack << " ";
  
  ofstate << cohort[pichrt].yrsoilavlH2O << " ";
  
  ofstate << cohort[pichrt].yrsoilavlN << " ";

  ofstate << cohort[pichrt].yrsoilavlNH4 << " ";

  ofstate << cohort[pichrt].yrsoilavlNO3 << " ";
  
  ofstate << cohort[pichrt].yrsoilDOC << " ";
  
  ofstate << cohort[pichrt].yrsoilDON << " ";
  
  ofstate << cohort[pichrt].yrsoilmoist << " ";
  
  ofstate << cohort[pichrt].yrsoilnonorgC << " ";
  
  ofstate << cohort[pichrt].yrsoilnonorgN << " ";
  
  ofstate << cohort[pichrt].yrsoilorgC << " ";
  
  ofstate << cohort[pichrt].yrsoilorgN << " ";

  ofstate << cohort[pichrt].yrsoilpctp << " ";
  
  ofstate << cohort[pichrt].yrsoilResp << " ";
  
  ofstate << cohort[pichrt].yrsoiltotorgC << " ";

  ofstate << cohort[pichrt].yrsoiltotorgN << " ";
  
  ofstate << cohort[pichrt].yrsoilvsm << " ";

  ofstate << cohort[pichrt].yrsperc << " ";
  
  ofstate << cohort[pichrt].yrsrun << " ";

  ofstate << cohort[pichrt].yrSTMdst0 << " ";

  ofstate << cohort[pichrt].yrSTMdst5 << " ";

  ofstate << cohort[pichrt].yrSTMdst10 << " ";

  ofstate << cohort[pichrt].yrSTMdst20 << " ";

  ofstate << cohort[pichrt].yrSTMdst50 << " ";

  ofstate << cohort[pichrt].yrSTMdst100 << " ";

  ofstate << cohort[pichrt].yrSTMdst200 << " ";

  ofstate << cohort[pichrt].yrSTMfrontd << " ";

  ofstate << cohort[pichrt].yrSTMfrontd2 << " ";

  ofstate << cohort[pichrt].yrSTMthawbegin1 << " ";

  ofstate << cohort[pichrt].yrSTMthawbegin2 << " ";

  ofstate << cohort[pichrt].yrSTMthawend1 << " ";

  ofstate << cohort[pichrt].yrSTMthawend2 << " ";

  ofstate << cohort[pichrt].yrSTMtsoil << " ";
     
  ofstate << cohort[pichrt].yrthawpct << " ";
  
  ofstate << cohort[pichrt].yrtotalC << " ";
  
  ofstate << cohort[pichrt].yrunleaf << " ";

  ofstate << cohort[pichrt].yrvconvrtC << " ";
  
  ofstate << cohort[pichrt].yrvconvrtN << " ";

  ofstate << cohort[pichrt].yrvegabvgrndResp << " ";
  
  ofstate << cohort[pichrt].yrvegC << " ";
    
  ofstate << cohort[pichrt].yrveglup << " ";

  ofstate << cohort[pichrt].yrvegN << " ";

  ofstate << cohort[pichrt].yrvegnmobil << " ";

  ofstate << cohort[pichrt].yrvegnrsorb << " ";

  ofstate << cohort[pichrt].yrvegrgrowth << " ";

  ofstate << cohort[pichrt].yrvegrmaint << " ";

  ofstate << cohort[pichrt].yrvegrootResp << " ";
  
  ofstate << cohort[pichrt].yrvegstoN << " ";
  
  ofstate << cohort[pichrt].yrvegstrN << " ";

  ofstate << cohort[pichrt].yrvegsup;

  ofstate << endl;
  
};

