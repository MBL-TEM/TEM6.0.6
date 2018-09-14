/* **************************************************************
XTEM606C.CXX - Extrapolation version of the Terrestrial Ecosystem 
               Model (TEM) Version 6.0.6c 
*****************************************************************

BY DOWNLOADING THE TERRESTRIAL ECOSYSTEM MODEL (TEM) PROGRAM YOU 
AGREE TO THE FOLLOWING TERMS OF USE:

Copyright © 2018.  The Marine Biological Laboratory (“MBL”). All 
Rights Reserved.  

Permission to use, copy, modify, and distribute this software, 
including all object code and source code, and any accompanying
documentation (together the “Software Model”) for educational and 
not-for-profit research purposes, without fee and without a signed
licensing agreement, is hereby granted, provided that the above 
copyright notice, this paragraph and the following three paragraphs
appear in all copies, modifications, and distributions. For the 
avoidance of doubt, educational and not-for-profit research purposes
excludes any service or part of selling a service that uses the 
Software Model. To obtain a commercial license for the Software 
Model, contact the Technology Commercialization team at the 
Polsky Center for Entrepreneurship and Innovation, University of 
Chicago, 1452 East 53rd Street, 2nd floor, Chicago, IL 60615.

Created by David W. Kicklighter, A. David McGuire, James W. Raich, 
Yude Pan, Xiangming Xiao, Qianlai Zhuang, Hanqin Tian, Benjamin
Felzer, Timothy W. Cronin, and Jerry Melillo at The Marine 
Biological Laboratory.

The Software Model is copyrighted by MBL. The Software Model is 
supplied "as is", without any accompanying services from MBL. MBL 
does not warrant that the operation of the Software Model will be 
uninterrupted or error-free. The end-user understands that the 
Software Model was developed for research purposes and is advised 
not to rely exclusively on the Software Model for any reason.

IN NO EVENT SHALL MBL BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, 
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
PROFITS, ARISING OUT OF THE USE OF THE SOFTWARE MODEL, EVEN IF MBL 
HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. MBL SPECIFICALLY
DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE SOFTWARE MODEL PROVIDED HEREUNDER IS PROVIDED "AS IS".  MBL HAS 
NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
ENHANCEMENTS, OR MODIFICATIONS.

*****************************************************************
************************************************************** */

#define ANSI_CPP

//#define BORLAND_CPP

#include<cstdio>

  using std::fopen;
  using std::fclose;
  using std::printf;
  using std::sprintf;
  using std::fscanf;
  using std::FILE;

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

  using std::setiosflags;
  using std::setw;
  using std::setprecision;

#include<cstdlib>

  using std::exit;
  
#include<cmath>

#include<vector>

  using std::vector;
  
#include<cctype>

  using std::toupper;

#include<cstring>
  
#include<string>
  
  using std::string;
  
#include<sstream>

  using std::ostringstream;

#ifdef ANSI_CPP

  #include<ctime>

  using std::time_t;
  using std::ctime;

#endif

#ifdef BORLAND_CPP

  #include<time>

  using std::time_t;
  using std::ctime;

#endif


#include "temconsts606.hpp"   // Global constants
#include "tclmdat606.h"       // Clmdata60 class
#include "tco2dat437.h"       // CO2data43 class
#include "tndepdat605.h"      // Ndepdata60 class
#include "elmnt605.h"         // Elmnt60 Class
#include "latdat602.h"        // Latdata60 class
#include "telm606c.h"         // TEMelmnt60 Class

int askpred( const vector<string>& pvarname, 
             const int& posspred, 
             const vector<string>& predmap );

void initCLM( void );
void initializeCLMGridCell( void );
void initializeLCLUCGridCell( void );
void initializeTEMGridCell( void );
void initLCLUC( void );
void initTEM( void );
void setClmPred( void );
void setGridParameters( void );
void setInTEMState( void );
void setOutTEMState( void );
void setRunMode( void );          
void setRunTime( void );
void setTEMPred( void );
long skipRecords( void );
void updateTCLMGridCell( const int& pdyr );
void updateTLCLUCGridCell( const int& pdyr );
void updateTTEMGridCell( const int& pdyr );


ofstream flog1;

Elmnt60 elmnt;
TEMelmnt60 telmnt[MAXGRID];

int equil;
int RTIME;

long mxnumgrid;

int spinflag;
int spinoutfg;
int spinoutyrs;
int numspin;
int spintime;
int totsptime;
int transtime;

int temflag;
int istateflag;
int istateyear;
int ostateflag;
int ostateyear;

vector<string> clmpredmap( NUMATMS );
vector<string> tempredmap( NUMTEM );
    
int fatalerr;
int end1;
int icount;
int glob_count;

Latdata60 latdat;

Clmdata60 girrdat[MAXRTIME];
Clmdata60 cldsdat[MAXRTIME];
Clmdata60 nirrdat[MAXRTIME];
Clmdata60 pardat[MAXRTIME];
Clmdata60 tairdat[MAXRTIME];
Clmdata60 precdat[MAXRTIME];

CO2data43 co2dat[MAXRTIME+1];
Clmdata60 grdco2dat[MAXRTIME];
Clmdata60 o3dat[MAXRTIME];
Ndepdata60 ndepdat[MAXRTIME];

MaxCohortdata60 mxcohrtdat[MAXRTIME];
Lulcdata60 lulcdat[MAXRTIME][MAXCHRTS];  

FILE* flonlat;
  
FILE* ifgirr;
FILE* ifnirr;
FILE* ifpar;
FILE* ifclds;
FILE* iftair;
FILE* ifprec;
ifstream ifco2;
FILE* ifgrdco2;
FILE* ifo3;
FILE* ifndep;

FILE* ifnumchrts;
FILE* iflulc;

FILE* fstxt;
FILE* felev;

ifstream ifstate;  // Use TEMstate from a specified year
ofstream ofstate;  // Save TEMstate for a specified year
ofstream fclmpred[NUMATMS];
ofstream ftempred[NUMTEM];

int assignCO2 = 0;

/* *************************************************************
**********************START MAIN PROGRAM************************
************************************************************* */

int main()
{

  int dyr;
  int i;
 
  long grdcnt;


  // Run model in steady state mode or dynamic mode? 

  setRunMode();


  // Determine time frame of simulation
  
  setRunTime();

  
  // Specify number of grid cells in the study region and determine 
  // if spatially explicit data is referenced by column and row
  // or by longitude and latitude
  
  setGridParameters();


  // Initialize climate module

  initCLM();


  // Initialize land cover module

  initLCLUC();
  

  // Initialize TEM 

  initTEM();  


  telmnt[0].col = MISSING;
  telmnt[0].row = MISSING;
  telmnt[0].tem.totyr = -99;

  cout << endl;
  flog1 << endl << endl;

  elmnt.show( flog1, 
              telmnt[0].col, 
              telmnt[0].row,
              telmnt[0].tem.totyr, 
              telmnt[0].tem.inittol );


  // Extrapolate TEM across region

  grdcnt = 0;

  while( grdcnt < mxnumgrid && 0 == fatalerr )   // Grid cell loop
  {
    
//*********************************************************** */


    // Load grid cell climate data into one node of CLM linked list

    dyr = 0;
    updateTCLMGridCell( dyr );


    // Determine number of land use/land cover cohorts in a 
    //   grid cell and load land cover data into cohorts of 
    //   LULC linked list

    updateTLCLUCGridCell( dyr );

    // Initialize TEM to equilibrium conditions for all cohorts
    // using the baseline climate if starting from calibration data 
    // (i.e. istateflag == 0) or read in initial conditions from 
    // temstate file

    initializeTEMGridCell();

    // Begin simulation of transient climate and terrestrial 
    //   ecosystem response

    if( 0 == equil )
    {

      for( dyr = 1; dyr < RTIME; ++dyr )
      {

        // Run climate module or read climate data from file to update
        // climate for grid cell during year "dyr"

        updateTCLMGridCell( dyr );


        // Run land cover module or read in land cover data from file 
        // to update land cover characteristics for grid cell during year "dyr" 

        updateTLCLUCGridCell( dyr ); 


        // Run TEM for grid cell during year "dyr"
    
        updateTTEMGridCell( dyr );
      }
    }
   
    elmnt.show( flog1, 
                telmnt[0].col, 
                telmnt[0].row,
                telmnt[0].tem.totyr, 
                telmnt[0].tem.tol );

    ++grdcnt;
  }
  

  if( 0 == fatalerr )
  {
    cout << "Extrapolation successfully completed - Congratulations!" << endl;
    flog1 << "Extrapolation successfully completed - Congratulations!" << endl;
  }
  else
  {
    if( elmnt.grdcnt != -99 && elmnt.count <= elmnt.grdcnt )
    {
      cout << "FATAL ERROR! Program Terminated" << endl;
    }
    flog1 << "FATAL ERROR! Program Terminated" << endl;
  }

  // Finished processing all elements - close open files

  if( 0 == telmnt[0].lonlatflag ) { fclose( flonlat ); }

  if( 1 == telmnt[0].clm.predflag )
  {
    for( i = 0; i < telmnt[0].natmspred; ++i ) 
    { 
      fclmpred[i].close(); 
    }
  }

  
  if( 1 == telmnt[0].clm.cldflag ) { fclose( ifclds ); }
  else { fclose( ifnirr ); }

  if( 0 == telmnt[0].clm.sradflag ) { fclose( ifgirr ); }

  if( 1 == telmnt[0].clm.parflag ) { fclose( ifpar ); }

  fclose( iftair );
  fclose( ifprec );
  
  ifco2.close();
  
  fclose( ifo3 );
  fclose( ifndep );
  
  if( 1 == temflag )
  {
    fclose( ifnumchrts );
    fclose( iflulc ); 
    
    fclose( fstxt );
    fclose( felev );
    
    for( i = 0; i < telmnt[0].ntempred; ++i ) 
    { 
      ftempred[i].close(); 
    }
    
    if( istateflag != 0 ) { ifstate.close(); }
    if( ostateflag != 0 ) { ofstate.close(); }
  }

  cout << "Closed all files!" << endl << endl;
  flog1 << "Closed all files!" << endl << endl;

  flog1.close();

  return 0;

};

/* *************************************************************
******************** End of Main ******************************* 
************************************************************* */

/* *************************************************************
************************************************************* */

int askpred( vector<string>& pvarname, 
             const int& posspred,
             vector<string>& predmap ) 
{
  const int MAXCOLUMNS = 7;
  int count = 0;

  int numpred;
  
  int i;
  int j;
  int cnt;
  int length;
  
  cout << endl << endl;
  cout << "           POSSIBLE OUTPUT VARIABLES:";
  cout << endl << endl;

  vector<string>::const_iterator dn;
  
  for( dn = pvarname.begin(); dn != pvarname.end(); ++dn )
  {
    cout << std::setw(10) << *dn << " ";
    
    ++count;
  
    if( 0 == count%MAXCOLUMNS ) { cout << endl; }
  }

  cout << endl << endl;

  flog1 << endl << endl;
  flog1 << "           POSSIBLE OUTPUT VARIABLES:";
  flog1 << endl << endl;

  count = 0;
  
  for( dn = pvarname.begin(); dn != pvarname.end(); ++dn )
  {
    flog1 << std::setw(10) << *dn << " ";
    
    ++count;
    
    if( 0 == count%MAXCOLUMNS ) { flog1 << endl; }
  }

  flog1 << endl << endl;

  cout << endl << endl;
  cout << "How many variables are to be mapped (max ";
  cout << posspred << ") in output files?  ";

  cin >> numpred;

  cout << numpred << endl;

  flog1 << endl << endl;
  flog1 << "How many variables are to be mapped (max ";
  flog1 << posspred << ") in output files?";
  flog1 << numpred << endl << endl;

  cout << "Please enter output variable: " << endl;
  flog1 << "Please enter output variable: " << endl;

  for( i = 0; i < numpred; ++i )
  {
    cnt = i + 1;
    cout << cnt << " ";

    cin >> predmap.at( i );

    length = predmap.at( i ).length();
    
    for( j = 0; j < length; ++j ) 
    { 
      predmap.at( i ).at( j ) = toupper( predmap.at( i ).at( j ) ); 
    }
    
    flog1 << cnt << " " << predmap.at( i ) << endl;
  }

  return numpred;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void initCLM( void )
{
  double initco2;
  double co2level;
  
  // Set flags and filenames for spatially explicit cloudiness 
  //   or solar radiation data
  
  telmnt[0].clm.setCldsFlags( flog1, equil );
  telmnt[0].clm.initSolarRad( flog1 ); 


  // Set flags and filenames for spatially explicit air 
  //   temperature data

  telmnt[0].clm.setTairFlags( flog1, equil );
  telmnt[0].clm.initTair( flog1 );


  // Set flags and filenames for spatially explicit 
  //   precipitation data

  telmnt[0].clm.setPrecFlags( flog1, equil );
  telmnt[0].clm.initPrec( flog1 );
  	

  // Determine initial atmospheric CO2 concentration for 
  //   initial equilibrium portion of the simulation
  
  cout << endl << endl;
  cout << "Enter the initial concentration of carbon dioxide ";
  cout << "in ppmv: ";

  cin >> initco2;
  
  telmnt[0].clm.setINITCO2( initco2 );

  flog1 << endl << endl;
  flog1 << "Enter the initial concentration of carbon dioxide ";
  flog1 << "in ppmv: ";
  flog1 << telmnt[0].clm.getINITCO2() << endl << endl;

  cout << "Enter the final equilibrium concentration of ";
  cout << "carbon dioxide in ppmv: ";

  cin >> co2level;
  
  telmnt[0].clm.setCO2LEVEL( co2level );

  flog1 << "Enter the final equilibrium concentration of ";
  flog1 << "carbon dioxide in ppmv: ";
  flog1 << telmnt[0].clm.getCO2LEVEL() << endl << endl;
  
  
  // Set flags and filenames for global annual or monthly 
  //   spatially explicit atmospheric CO2 concentration 
  //   data for transient portion of the simulation
  
  telmnt[0].clm.setCO2Flags( flog1, equil );
  telmnt[0].clm.initCO2( flog1 );
 

  // Set flags and filenames for spatially explicit ozone data

  telmnt[0].clm.setO3Flags( flog1, equil );
  telmnt[0].clm.initO3( flog1 );

  // Set flags and filenames for spatially explicit nitrogen
  //  deposition data

  telmnt[0].clm.setNdepFlags( flog1, equil );
  telmnt[0].clm.initNdep( flog1 );

  // Identify output variables to be written out from climate 
  //   module
  
  setClmPred();

  // Initialize model for a grid cell
    
  initializeCLMGridCell();

  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void initializeCLMGridCell()
{   
  ostringstream tempfname;
  string girrname;
  string cldsname;
  string nirrname;
  string parname;
  string tairname;
  string precname;
  string co2name;
  string o3name;
  string ndepname; 

  
  // Open cloudiness or solar radiation file

  if( 0 == telmnt[0].clm.sradflag )
  {
    tempfname.str( "" );

    tempfname << telmnt[0].clm.igirrfname
              << telmnt[0].clm.igirrend;

    girrname = tempfname.str();

    ifgirr = fopen( girrname.c_str(), "r" );

    if( !ifgirr )
    {
      flog1 << endl << "Cannot open " << girrname;
      flog1 << " for GIRR data input" << endl << endl;

      exit( -1 );
    }
  }      

  if( 1 == telmnt[0].clm.cldflag )
  {
    tempfname.str( "" );

    tempfname << telmnt[0].clm.icldsfname
              << telmnt[0].clm.icldsend;

    cldsname = tempfname.str();

    ifclds = fopen( cldsname.c_str(), "r" );

    if( !ifclds )
    {
      flog1 << endl << "Cannot open " << cldsname;
      flog1 << " for CLDS data input" << endl << endl;

      exit( -1 );
    }
  }
  else
  {
    tempfname.str( "" );

    tempfname << telmnt[0].clm.inirrfname
              << telmnt[0].clm.inirrend;

    nirrname = tempfname.str();

    ifnirr = fopen( nirrname.c_str(), "r" );

    if( !ifnirr )
    {
      flog1 << endl << "Cannot open " << nirrname;
      flog1 << " for NIRR data input" << endl << endl;

      exit( -1 );
    }
  }

  if( 1 == telmnt[0].clm.parflag )
  {
    tempfname.str( "" );

    tempfname << telmnt[0].clm.iparfname
              << telmnt[0].clm.iparend;

    parname = tempfname.str();

    ifpar = fopen( parname.c_str(), "r" );

    if( !ifpar )
    {
      flog1 << endl << "Cannot open " << parname;
      flog1 << " for PAR data input" << endl << endl;

      exit( -1 );
    }
  }      


  // Open air temperature file

  tempfname.str( "" );

  tempfname << telmnt[0].clm.itairfname
            << telmnt[0].clm.itairend;

  tairname = tempfname.str();

  iftair = fopen( tairname.c_str(), "r" );

  if( !iftair )
  {
    flog1 << endl << "Cannot open " << tairname;
    flog1 << " for TAIR data input" << endl << endl;

    exit( -1 );
  }

  
  // Open precipitation file

  tempfname.str( "" );

  tempfname << telmnt[0].clm.iprecfname
            << telmnt[0].clm.iprecend;

  precname = tempfname.str();

  ifprec = fopen( precname.c_str(), "r" );

  if( !ifprec )
  {
    flog1 << endl << "Cannot open " << precname;
    flog1 << " for PREC data input" << endl << endl;

    exit( -1 );
  }

  // Open CO2 file

  if( 1 == telmnt[0].clm.tco2flag )
  {
    co2name = telmnt[0].clm.ico2fname;
    
    ifco2.open( co2name.c_str(), ios::in );

    if( !ifco2 )
    {
      flog1 << endl << "Cannot open " << co2name;
      flog1 << " for CO2 data input" << endl;

     exit( -1 );
    }
  }
  else if( 2 == telmnt[0].clm.tco2flag )
  {
    tempfname.str( "" );

    tempfname << telmnt[0].clm.ico2fname
              << telmnt[0].clm.ico2end;

    co2name = tempfname.str();

    ifgrdco2 = fopen( co2name.c_str(), "r" );
    if( !ifgrdco2 )
    {
      flog1 << endl << "Cannot open " << o3name;
      flog1 << " for CO2 data input" << endl << endl;

      exit( -1 );
    }
  }
 
  // Open ozone file

  tempfname.str( "" );

  tempfname << telmnt[0].clm.io3fname
            << telmnt[0].clm.io3end;

  o3name = tempfname.str();

  ifo3 = fopen( o3name.c_str(), "r" );
  if( !ifo3 )
  {
    flog1 << endl << "Cannot open " << o3name;
    flog1 << " for O3 data input" << endl << endl;

    exit( -1 );
  }

  // Open Atmospheric N deposition file

  tempfname.str( "" );

  tempfname << telmnt[0].clm.indepfname
            << telmnt[0].clm.independ;

  ndepname = tempfname.str();

  ifndep = fopen( ndepname.c_str(), "r" );

  if( !ifndep )
  {
    flog1 << endl << "Cannot open " << ndepname;
    flog1 << " for NDEP data input" << endl << endl;

    exit( -1 );
  } 
  
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void initializeLCLUCGridCell( void )
{
  string mxcohrtname;
  string lulcname;
  ostringstream tempfname;

  cout << "Got into initializeLCLUCGridCell" << endl;

  cout << "imxcohrtfname = " << endl;
  cout << "imxcohrtend = " << endl;

  // Open maximum cohort file

  tempfname.str( "" );

  tempfname << telmnt[0].lcluc.imxcohrtfname
            << telmnt[0].lcluc.imxcohrtend;

  mxcohrtname = tempfname.str();

  ifnumchrts = fopen( mxcohrtname.c_str(), "r" );

  if( !ifnumchrts )
  {
    flog1 << endl << "Cannot open " << mxcohrtname;
    flog1 << " for MXCOHRTS data input" << endl << endl;

    exit( -1 );
  }


  // Open land use/land cover cohort file

  tempfname.str( "" );

  tempfname << telmnt[0].lcluc.ilulcfname
            << telmnt[0].lcluc.ilulcend;

  lulcname = tempfname.str();

  iflulc = fopen( lulcname.c_str(), "r" );

  if( !iflulc )
  {
    flog1 << endl << "Cannot open " << lulcname;
    flog1 << " for LULCCHRT data input" << endl << endl;

    exit( -1 );
  }
   
};

/* *************************************************************
************************************************************* */


/* **************************************************************
************************************************************** */

void initializeTEMGridCell( void )
{
  int dm;
  const int dyr = 0;
  int ichrt;

// *************************************************************

  // Set elevation and soil texture for TEM

  telmnt[0].setGIStopography( flog1, fatalerr, fstxt, felev );

     
/* *************************************************************
		BEGIN VEGETATION MOSAIC LOOP
************************************************************* */

  for( ichrt = 0; ichrt < telmnt[0].maxcohorts; ++ichrt )
  {
    telmnt[0].initializeCohortTEMState( ichrt );

    if( istateflag > 0 )
    {
      // Read in initial TEM state determined in a previous 
      //  TEM simulation to telmnt[0].cohort

      if( 1 == istateflag )
      {
        telmnt[0].readBinaryCohortState( ifstate, ichrt );
      }
      else
      {
        telmnt[0].readCohortState( ifstate, ichrt );
      }
      	     
      dm = CYCLE - 1;
      
      telmnt[0].getTEMCohortState( ichrt, dm );

      // Determine soil properties of element based on
      //   soil texture

      telmnt[0].tem.soil.xtext( telmnt[0].tem.veg.cmnt,
                                telmnt[0].tem.soil.getPCTSILT(),
                                telmnt[0].tem.soil.getPCTCLAY() );


      // Set texture dependent parameters for TEM 

      telmnt[0].tem.setELMNTecd( telmnt[0].tem.veg.cmnt, 
                                 telmnt[0].tem.soil.getPSIPLUSC() );
    }
    else
    {     	
      telmnt[0].setTEMequilState( flog1,
                                  equil,
                                  totsptime,
                                  ichrt );

      if( telmnt[0].tem.intflag > 0 )
      {
        if( elmnt.count < elmnt.grdcnt )
        {
          cout << "Integration terminated before attaining ";
          cout << "tolerance level" << endl;
        }

        flog1 << "Integration terminated before attaining ";
        flog1 << "tolerance level" << endl;

        telmnt[0].tem.intflag = 0;
      }
           
      // Write selected TEM variables from telmnt[0].output to 
      //   outfile files
  
      if( 1 == spinoutfg || 3 == spinoutfg || 1 == equil )
      {
        telmnt[0].temwritepred( ftempred, 
                                tempredmap, 
                                dyr, 
                                ichrt,
                                telmnt[0].ntempred );
      }
    } // End of istateflag else
  } // End of cohort loop
 
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void initLCLUC( void )
{
  // Hand 0ff startyr from clm
  
  telmnt[0].lcluc.startyr = telmnt[0].clm.startyr;


  // Get community type parameterizations
  
  telmnt[0].lcluc.getvtype( flog1 );
 
  
  // Set flags land cover /land-use change data

  telmnt[0].lcluc.setLCLUCFlags( flog1, equil );


  // Set filename for spatially explicit number of cohorts data
 
  telmnt[0].lcluc.initMaxCohorts( flog1 );

  
  // Set filename for spatially explicit land use/ land cover 
  //   cohort data
  
  telmnt[0].lcluc.initCohorts( flog1 );


  initializeLCLUCGridCell();
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void initTEM( void )
{

  int numcmnt;
  string ifilename;

  double dc2n;

  cout << "Do you want to run the terrestrial ecosystem model ";
  cout << "(TEM)?" << endl;
  cout << "Enter 0 for No" << endl;
  cout << "Enter 1 for Yes: " << endl;
  
  cin >> temflag;

  flog1 << "Do you want to run the terrestrial ecosystem model ";
  flog1 << "(TEM)?" << endl;
  flog1 << "  Enter 0 for No" << endl;
  flog1 << "  Enter 1 for Yes" << endl;
  flog1 << "temflag = " << temflag << endl << endl;

  telmnt[0].ntempred = 0;

  if( 1 == temflag )
  {
    // Hand off climate startyr to TEM
    
    telmnt[0].tem.startyr = telmnt[0].clm.startyr;

    // Hand off initial CO2 data to TEM
    
    telmnt[0].tem.atms.setINITCO2( telmnt[0].clm.getINITCO2() );

    telmnt[0].tem.atms.setCO2LEVEL( telmnt[0].clm.getCO2LEVEL() );


    // Hand off tlulcflag from LCLUC module to TEM
    telmnt[0].tem.ag.tlulcflag = telmnt[0].lcluc.tlulcflag;

    telmnt[0].tem.initrun( flog1 );
    telmnt[0].tem.askODE( flog1 );


    // Get soil texture dependent parameters

    telmnt[0].tem.soil.getecd( flog1 );


    // Get parameters associated with human disturbance 
    //   activities

    if( 1 == telmnt[0].tem.ag.tlulcflag )
    {
      telmnt[0].tem.ag.setAgricFlags( flog1 );
    }

   // Get calibration site specific parameters

    cout << "Please enter the number of community types with ";
    cout << "calibration data for vegetation:";
    
    cin >> numcmnt;

    flog1 << endl << endl;
    flog1 << "Please enter the number of community types with ";
    flog1 << "calibration data for vegetation:";
    flog1 << numcmnt << endl;

    telmnt[0].tem.getVegSpecificECD( numcmnt, flog1 );

    cout << "Please enter the name of the file containing the ";
    cout << "soil texture data:";
    cout << endl;
    cout << "               (e.g., TEXTURE.GIS) " << endl;

    cin >> ifilename;

    flog1 << "Please enter the name of the file containing the ";
    flog1 << "soil texture data:";
    flog1 << endl;
    flog1 << "               (e.g., TEXTURE.GIS) " << endl;
    flog1 << ifilename << endl << endl;
    
    fstxt = fopen( ifilename.c_str(), "r" );

    if( !fstxt )
    {
      flog1 << endl << "Cannot open " << ifilename;
      flog1 << " for data input" << endl;
      
      exit( -1 );
    }

    cout << "Please enter the name of the file containing the ";
    cout << "elevation data: " << endl;
    cout << "               (e.g., ELEV.GIS) " << endl;
    
    cin >> ifilename;
    
    flog1 << "Please enter the name of the file containing the ";
    flog1 << "elevation data: " << endl;
    flog1 << "               (e.g., ELEV.GIS) " << endl;
    flog1 << ifilename << endl << endl;

    felev = fopen( ifilename.c_str(), "r" );

    if( !felev )
    {
      flog1 << "\nCannot open " << ifilename;
      flog1 << " for data input" << endl;
      
      exit( -1 );
    }

    cout << endl << endl;
    cout << "Enter the factor for changing C:N per ppmv of ";
    cout << "enhanced CO2:" << endl;
    cout << "           (Enter 0.0 for no change): " << endl;

    cin >> dc2n;
        
    telmnt[0].tem.veg.setDC2N( dc2n );

    flog1 << endl;
    flog1 << "Enter the factor for changing C:N per ppmv of ";
    flog1 << "enhanced CO2:" << endl;
    flog1 << "           (Enter 0.0 for no change): " << endl;
    flog1 << "telmnt[0].tem.veg.dc2n = ";
    flog1 << telmnt[0].tem.veg.getDC2N() << endl << endl;

    setTEMPred();
 
    // Identify file that has extant TEM State from previous 
    //   simulation

    setInTEMState();

    // Identify files to receive TEM States from particular years 
    //   in current simulation
  
    setOutTEMState();
  }
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setClmPred( void )
{

  int i;
  string clmpredfile;

  telmnt[0].totpred = 0;
  telmnt[0].natmspred = 0;

  telmnt[0].clm.predflag = 0;
  cout << endl;
  cout << "Do you wish output data from the irradiance model? ";
  cout << endl;
  cout << "  Enter 0 for no" << endl;
  cout << "  Enter 1 for yes: ";

  cin >> telmnt[0].clm.predflag;

  flog1 << endl;
  flog1 << "Do you wish output data from the irradiance model?";
  flog1 << endl;
  flog1 << "  Enter 0 for no" << endl;
  flog1 << "  Enter 1 for yes: " << endl;
  flog1 << "telmnt[0].clm.predflag = ";
  flog1 << telmnt[0].clm.predflag << endl << endl;

  if( 1 == telmnt[0].clm.predflag )
  {
    telmnt[0].natmspred = askpred( telmnt[0].clm.predstr,
                                   NUMATMS, 
                                   clmpredmap );
                                   
    telmnt[0].totpred = telmnt[0].natmspred;

    for( i = 0; i < telmnt[0].natmspred; ++i )
    {
      cout << endl;
      cout << "Enter the name of the OUTPUT file to contain ";
      cout << clmpredmap[i] << ":  ";

      cin >> clmpredfile;

      flog1 << endl;
      flog1 << "Enter the name of the OUTPUT file to contain ";
      flog1 << clmpredmap[i] << ":  " << clmpredfile << endl;

      fclmpred[i].open( clmpredfile.c_str(), ios::out );
    }
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setGridParameters( void )
{

  string ifilename;
  
  
  cout << "How many elements are in the gridded data sets?";

  cin >> mxnumgrid;

  flog1 << endl << endl;
  flog1 << "How many elements are in the gridded data sets? ";
  flog1 << mxnumgrid << endl << endl;

  cout << "How do you locate your grid cells?" << endl;
  cout << "Enter 0 for column/row:" << endl;
  cout << "Enter 1 for longitude/latitude: ";

  cin >> telmnt[0].lonlatflag;

  flog1 << "How do you locate your grid cells?" << endl;
  flog1 << "Enter 0 for column/row:" << endl;
  flog1 << "Enter 1 for longitude/latitude: ";
  flog1 << telmnt[0].lonlatflag << endl << endl;

  if( 0 == telmnt[0].lonlatflag )
  {
    cout << "Please enter the name of the file containing ";
    cout << "the latitude data: " << endl;
    cout << "               (e.g., LAT.GIS) " << endl;

    cin >> ifilename;

    flog1 << "Please enter the name of the file containing ";
    flog1 << "the latitude data: " << endl;
    flog1 << "               (e.g., LAT.GIS) " << endl;
    flog1 << ifilename << endl << endl;

    flonlat = fopen( ifilename.c_str(), "r" );

    if( !flonlat )
    {
      cerr << endl << "Cannot open " << ifilename;
      cerr << " for data input" << endl;
      
      exit( -1 );
    }
  }

 // Use all records in GIS data sets (i.e. desired coverage)?

  elmnt.ask( flog1 );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setInTEMState( void )
{

  string ifilename;
  
	
  istateflag = 0;
  istateyear = -99;
  
  cout << endl;
  cout << "Do you want to use spatially explicit data ";
  cout << "for initial conditions? " << endl;
  cout << "  Enter 0 for NO:" << endl;
  cout << "  Enter 1 if spatially explicit binary data represents the ";
  cout << "state of TEM at the end of a specific year:" << endl;
  cout << "  Enter 2 if spatially explicit ASCII data represents the ";
  cout << "state of TEM at the end of a specific year:" << endl;

  cin >> istateflag;

  flog1 << endl;
  flog1 << "Do you want to use spatially explicit data ";
  flog1 << "for intial conditions? " << endl;
  flog1 << "  Enter 0 for NO:" << endl;
  flog1 << "  Enter 1 if spatially explicit binary data represents the ";
  flog1 << "state of TEM at the end of a specific year::" << endl;
  flog1 << "  Enter 2 if spatially explicit ASCII data represents the ";
  flog1 << "state of TEM at the end of a specific year:" << endl;
  flog1 << "istateflag = " << istateflag << endl << endl;

  if( istateflag > 0 )
  {
    cout << "Please enter the name of the file containing the ";
    cout << "initial TEM state data: " << endl;
    cout << "               (e.g., TEMINIT.GIS) " << endl;

    cin >> ifilename;

    flog1 << "Please enter the name of the file containing the ";
    flog1 << "initial TEM state data: " << endl;
    flog1 << "               (e.g., TEMINIT.GIS) " << endl;
    flog1 << ifilename << endl << endl;

    if( 1 == istateflag )
    {
      ifstate.open( ifilename.c_str(), ios::in | ios::binary );
    }
    else
    {
      ifstate.open( ifilename.c_str(), ios::in );
    }
    	
    if( !ifstate )
    {
      cout << endl << "Cannot open " << ifilename;
      cout << " for data input" << endl;
      flog1 << endl << "Cannot open " << ifilename;
      flog1 << " for data input" << endl;
      
      exit( -1 );
    }

    cout << "Please enter the year that you wish to use as ";
    cout << "the initial TEM state: " << endl;

    cin >> istateyear;

    flog1 << "Please enter the year that you wish to use as ";
    flog1 << "the initial TEM state: " << endl;
    flog1 << istateyear << endl << endl;
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setOutTEMState( void )
{

  string ifilename;
  
  
  ostateflag = 0;
  ostateyear = -99;

  cout << endl;
  cout << "Do you want to save the state of TEM as a spatially ";
  cout << "explicit data set for a specified year? " << endl;
  cout << "  Enter 0 for NO:" << endl;
  cout << "  Enter 1 for saving the state of TEM at the end of ";
  cout << "a specific year as binary data:" << endl;
  cout << "  Enter 2 for saving the state of TEM at the end of ";
  cout << "a specific year as ASCII data:" << endl;

  cin >> ostateflag;

  flog1 << endl;
  flog1 << "Do you want to save the state of TEM as a spatially ";
  flog1 << "explicit data set for a specified year? " << endl;
  flog1 << "  Enter 0 for NO:" << endl;
  flog1 << "  Enter 1 for saving the state of TEM at the end of ";
  flog1 << "a specific year as binary data:" << endl;
  flog1 << "  Enter 2 for saving the state of TEM at the end of ";
  flog1 << "a specific year as ASCII data:" << endl;
  flog1 << ostateflag << endl << endl;

  if( ostateflag != 0 )
  {
    cout << "Please enter the name of the file to contain ";
    cout << "the 'state' of TEM: " << endl;
    cout << "               (e.g., TEMSTATE.GIS) " << endl;

    cin >> ifilename;

    flog1 << "Please enter the name of the file to contain ";
    flog1 << "the 'state' of TEM: " << endl;
    flog1 << "               (e.g., TEMSTATE.GIS) " << endl;
    flog1 << ifilename << endl << endl;

    if( 1 == ostateflag )
    {
      ofstate.open( ifilename.c_str(), ios::out | ios::binary );
    }
    else
    {
      ofstate.open( ifilename.c_str(), ios::out );
    }
    

    cout << "Please enter the year that you wish to save ";
    cout << "the TEM state: " << endl;

    cin >> ostateyear;

    flog1 << "Please enter the year that you wish to save ";
    flog1 << "the TEM state: " << endl;
    flog1 << ostateyear << endl << endl;
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setRunMode( void )
{

  // Assign a log file for the simulation

  flog1.open( "tem60.log" );

/* *************************************************************
  Run equilibrium simulation or transient simulation ?
************************************************************* */

  equil = 1;
  
  cout << endl;
  cout << "Do you want to run the model only for steady state ";
  cout << "conditions ? " << endl;
  cout << " Enter 0 for transient simulation" << endl;
  cout << " Enter 1 for steady state simulation" << endl;

  cin >> equil;

  flog1 << endl;
  flog1 << "Do you want to run the model only for steady state ";
  flog1 << "conditions ? " << endl;
  flog1 << " Enter 0 for transient simulation" << endl;
  flog1 << " Enter 1 for steady state simulation" << endl;
  flog1 << "equil = " << equil << endl << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setRunTime( void )
{
	
  RTIME = 1;
  
  if( 0 == equil )
  {
    cout << "What is the first year of the transient climate data?";
    cout << endl;

    cin >> telmnt[0].clm.startyr;

    flog1 << "What is the first year of the transient climate data?";
    flog1 << endl;
    flog1 << telmnt[0].clm.startyr << endl << endl;

    telmnt[0].tem.startyr = telmnt[0].clm.startyr;

    flog1 << telmnt[0].clm.startyr << endl << endl;

    // Start transient TEM run from equilibrium conditions 
    // (i.e. spinflag == 0) or with a "spin up" period to remove 
    // potential artifacts associated with changing from 
    // equilibrium conditions to transient conditions from model
    //  results

    cout << "Do you want to start the transient with a spin up period? ";
    cout << endl;
    cout << "Enter 0 for no:" << endl;
    cout << "Enter 1 for yes:" << endl;
 
    cin  >> spinflag;

    flog1 << "Do you want to start the transient with a spin up period? ";
    flog1 << endl;
    flog1 << "Enter 0 for no:" << endl;
    flog1 << "Enter 1 for yes: " << endl;
    flog1 << "spinflag = " << spinflag << endl << endl;

    totsptime = 0;
    
    if( 1 == spinflag )
    {
      // Specify conditions for initializing TEM with a transient 
      //   "spin up" period for a grid cell

      cout << "How many spins do you want in the spin up period? ";
      
      cin >> numspin;
      
      flog1 << "How many spins do you want in the spin up period? ";
      flog1 << endl;
      flog1 << "numspin = " << numspin << endl << endl;

      cout << "How many years per spin? ";
      
      cin >> spintime;
      
      flog1 << "How many years per spin? " << endl;
      flog1 << "spintime = " << spintime << endl << endl;

      totsptime = spintime * numspin;
      flog1 << "totsptime = " << totsptime << endl << endl;
      RTIME += totsptime;
    }
    
    // Specify conditions for the "non-spin up" part of the 
    //   transient TEM run

    cout << endl;
    cout << "How many years do you run for transient simulations ? ";
    cout << endl;
    
    cin >> transtime;

    flog1 << endl;
    flog1 << "How many years do you run for transient simulations ? ";
    flog1 << endl;
    flog1 << "transtime = " << transtime << endl << endl;

    RTIME += transtime;
    flog1 << "RTIME = " << RTIME << endl << endl;
  }
  else 
  { 
    totsptime = RTIME; 
    spintime = 1;
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void setTEMPred( void )
{

  int i;
  string tempredfile;

  telmnt[0].tem.predflag = 0;
  
  cout << endl;
  cout << "Do you wish spatially explicit output data from TEM?";
  cout << endl;
  cout << "  Enter 0 for no" << endl;
  cout << "  Enter 1 for yes: ";

  cin >> telmnt[0].tem.predflag;

  flog1 << endl;
  flog1 << "Do you wish spatially explicit output data from TEM?";
  flog1 << endl;
  flog1 << "  Enter 0 for no" << endl;
  flog1 << "  Enter 1 for yes: " << endl;
  flog1 << "telmnt[0].tem.predflag = " << telmnt[0].tem.predflag;
  flog1 << endl << endl;

  if( 1 == telmnt[0].tem.predflag )
  {
    telmnt[0].ntempred = askpred( telmnt[0].tem.predstr, 
                                  NUMTEM,
                                  tempredmap );
                                  
    for( i = 0; i < telmnt[0].ntempred; ++i )
    {
      cout << endl;
      cout << "Enter the name of the OUTPUT file to contain ";
      cout << tempredmap[i] << ":  ";
      
      cin >> tempredfile;
      
      flog1 << "Enter the name of the OUTPUT file to contain ";
      flog1 << tempredmap[i] << ":  " << tempredfile << endl;
      
      ftempred[i].open( tempredfile.c_str(), ios::out );
    }

    spinoutfg = 0;
    spinoutyrs = 0;
    
    cout << "Do you want to save TEM output from ";
    cout << "the spin-up period?" << endl;
    cout << "Enter 0 for no:" << endl;
    cout << "Enter 1 for all spin-up years: " << endl;
    cout << "Enter 2 for some spinup years: " << endl;
    cout << "Enter 3 to save only equilibrium results:" << endl;
      
    cin >> spinoutfg;

    flog1 << "Do you want to save TEM output from ";
    flog1 << "the spin-up period?" << endl;
    flog1 << "Enter 0 for no:" << endl;
    flog1 << "Enter 1 for all spin-up years: " << endl;
    flog1 << "Enter 2 for some spinup years: " << endl;
    flog1 << "Enter 3 to save only equilibrium results:" << endl;
    flog1 << "spinoutfg = " << spinoutfg << endl << endl;

    if( 2 == spinoutfg )
    {
      cout << "How many years of spin-up do you want to ";
      cout << "save in the TEM output?" << endl;
        
      cin >> spinoutyrs;
        
      flog1 << "How many years of spin-up do you want to ";
      flog1 << "save in the TEM output?" << endl;     
      flog1 << "spinoutyrs = " << spinoutyrs << endl << endl;
    }
  }
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

long skipRecords( void )
{

  long elmntcnt = 0;

  end1 = 1;
  fatalerr = 0;

  if( 0 == elmnt.strtflag )
  {

    for( elmntcnt = 0; elmntcnt < elmnt.numskip; ++elmntcnt )
    {       
      if( 1 == temflag )
      {
        telmnt[0].setGIStopography( flog1, 
                                    fatalerr, 
                                    fstxt, 
                                    felev );
      }      
    }
  }
  
  return elmntcnt;  // Number of grid cells skipped!

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void updateTCLMGridCell( const int& pdyr )
{

  const double Watts2cal = 1.0 / 0.4845;
  int dyr;
  int dm;
  int gisend;

  double lat = -999.9;

  string SRADname;
   
  fatalerr = 0; 

  if( 0 == pdyr )
  {
    if( 0 == telmnt[0].lonlatflag )
    {
      gisend = latdat.getdel( flonlat );

      if( -1 == gisend ) 
      {
        cout << "Ran out of LONLAT data" << endl << endl;
        flog1 << "Ran out of LONLAT data" << endl << endl;
            
        exit( -1 );
      }
    }

    if( 1 == telmnt[0].clm.tcldsflag )
    {
      if( 0 == telmnt[0].clm.sradflag )
      {
        for( dyr = 0; dyr < (transtime+1); ++dyr )
        { 
          gisend = girrdat[dyr].getdel( ifgirr );
          
          if( -1 == gisend ) 
          {
            cout << "Ran out of GIRR data" << endl << endl;
            flog1 << "Ran out of GIRR data" << endl << endl;
            
            exit( -1 );
          }
        }
      }
    

      if( 1 == telmnt[0].clm.cldflag )
      {
        for( dyr = 0; dyr < (transtime+1); ++dyr )
        { 
          gisend = cldsdat[dyr].getdel( ifclds );
          
          if( -1 == gisend ) 
          {  
            cout << "Ran out of Cloudiness data" << endl << endl;
            flog1 << "Ran out of Cloudiness data" << endl << endl;
          
            exit( -1 );
          }
        }

        telmnt[0].col = cldsdat[0].col;
        telmnt[0].row = cldsdat[0].row;
        SRADname = "CLDINESS";
      }  
      else
      {
        for( dyr = 0; dyr < (transtime+1); ++dyr )
        { 
          gisend = nirrdat[dyr].getdel( ifnirr );
          
          if( -1 == gisend )
          {  
            cout << "Ran out of NIRR data" << endl << endl;
            flog1 << "Ran out of NIRR data" << endl << endl;
  
            exit( -1 );
          }
        }

        telmnt[0].col = nirrdat[0].col;
        telmnt[0].row = nirrdat[0].row;
        SRADname = "NIRR";
      }
    
      if( 1 == telmnt[0].clm.parflag )
      {
        for( dyr = 0; dyr < (transtime+1); ++dyr )
        { 
          gisend = pardat[dyr].getdel( ifpar );
  
          if( -1 == gisend )
          { 
            cout << "Ran out of PAR data" << endl << endl;
            flog1 << "Ran out of PAR data" << endl << endl;
  
            exit( -1 );
          }
        }
      }
    }
    else  // 0 == telmnt[0].clm.tcldsflag
    { 
      if( 0 == telmnt[0].clm.sradflag )
      {
        gisend = girrdat[0].getdel( ifgirr );
  
        if( -1 == gisend ) 
        { 
          cout << "Ran out of GIRR data" << endl << endl;
          flog1 << "Ran out of GIRR data" << endl << endl;
  
          exit( -1 );
        }
      }

      if( 1 == telmnt[0].clm.cldflag )
      {
        gisend = cldsdat[0].getdel( ifclds );
  
        if( -1 == gisend ) 
        {  
          cout << "Ran out of Cloudiness data" << endl << endl;
          flog1 << "Ran out of Cloudiness data" << endl << endl;
  
          exit( -1 );
        }

        telmnt[0].col = cldsdat[0].col;
        telmnt[0].row = cldsdat[0].row;
        SRADname = "CLDINESS";
      }
      else
      {
        gisend = nirrdat[0].getdel( ifnirr );
  
        if( -1 == gisend ) 
        {  
          cout << "Ran out of NIRR data" << endl << endl;
          flog1 << "Ran out of NIRR data" << endl << endl;
  
          exit( -1 );
        }

        telmnt[0].col = nirrdat[0].col;
        telmnt[0].row = nirrdat[0].row;
        SRADname = "NIRR";
      }

      if( 1 == telmnt[0].clm.parflag )
      {
        gisend = pardat[0].getdel( ifpar );
  
        if( -1 == gisend ) 
        { 
          cout << "Ran out of PAR data" << endl << endl;
          flog1 << "Ran out of PAR data" << endl << endl;
  
          exit( -1 );
        }
      }
    }

    // Look for spatial co-registration problems between 
    //   cloudiness or net irradiance (NIRR) spatially explicit 
    //   data and gross irradiance (GIRR) spatially explicit 
    //   data 

    if( 0 == telmnt[0].clm.sradflag )
    {
      fatalerr = telmnt[0].coregerr( flog1, 
                                     SRADname,
                                     telmnt[0].col,
                                     telmnt[0].row,    
                                     "GIRR",
                                     girrdat[0].col,
                                     girrdat[0].row );
 
      if( fatalerr != 0 ) { exit( -1 ); }
    }

    // Look for spatial co-registration problems between 
    //   cloudiness or net irradiance (NIRR) spatially explicit 
    //   data and photosynthetically active radiation (PAR) 
    //   spatially explicit data 

    if( 1 == telmnt[0].clm.parflag )
    {
      fatalerr = telmnt[0].coregerr( flog1, 
                                     SRADname, 
                                     telmnt[0].col,
                                     telmnt[0].row,    
                                     "PAR",
                                     pardat[0].col,
                                     pardat[0].row );
 
      if( fatalerr != 0 ) { exit( -1 ); }
    }

    // Read in historical monthly air temperatures for grid cell

    if( 1 == telmnt[0].clm.ttairflag )
    {
      for( dyr = 0; dyr < (transtime+1); ++dyr )
      {
        gisend = tairdat[dyr].getdel( iftair );
        
        if( -1 == gisend ) 
        { 
          cout << "Ran out of Air Temperature data" << endl << endl;
          flog1 << "Ran out of Air Temperature data" << endl << endl;
          
          exit( -1 );
        }
      }
    }
    else
    {
      gisend = tairdat[0].getdel( iftair );
      
      if( -1 == gisend ) 
      { 
        cout << "Ran out of Air Temperature data" << endl << endl;
        flog1 << "Ran out of Air Temperature data" << endl << endl;
      
        exit( -1 );
      }
    }

    
    // Look for spatial co-registration problems between cloudiness and
    // air temperature spatially explicit data sets
    
    fatalerr = telmnt[0].coregerr( flog1, 
                                   SRADname, 
                                   telmnt[0].col,
                                   telmnt[0].row,    
                                   "TAIR",
                                   tairdat[0].col,
                                   tairdat[0].row );
 
    if( fatalerr != 0 ) { exit( -1 ); }

    
    // Read in historical monthly precipitation for grid cell
    
    if( 1 == telmnt[0].clm.tprecflag )
    {
      for( dyr = 0; dyr < (transtime+1); ++dyr )
      { 
        gisend = precdat[dyr].getdel( ifprec );
        
        if( -1 == gisend ) 
        { 
          cout << "Ran out of Precipitation data" << endl << endl;
          flog1 << "Ran out of Precipitation data" << endl << endl;
          
          exit( -1 );
        }
      }
    }
    else
    {
      gisend = precdat[0].getdel( ifprec );
      
      if( -1 == gisend ) 
      { 
        cout << "Ran out of Precipitation data" << endl << endl;
        flog1 << "Ran out of Precipitation data" << endl << endl;
      
        exit( -1 );
      }
    }

    
    // Look for spatial co-registration problems between cloudiness and
    // precipitation spatially explicit data sets

    fatalerr = telmnt[0].coregerr( flog1, 
                                   SRADname, 
                                   telmnt[0].col,
                                   telmnt[0].row,    
                                   "PREC",
                                   precdat[0].col,
                                   precdat[0].row );

    if( fatalerr != 0 ) { exit( -1 ); }

  
    // Read in historical annual atmospheric CO2 data for 
    //   globe
    
    if( 1 == telmnt[0].clm.tco2flag && 0 == assignCO2 )
    {
      for( dyr = 0; dyr < (transtime+2); ++dyr )
      {
        co2dat[dyr].get( ifco2 );
      }

      assignCO2 = 1;
    }

    // Read in historical monthly atmospheric CO2 data for
    //   grid cell
    
    else if( 0 == telmnt[0].clm.tco2flag
             || 2 == telmnt[0].clm.tco2flag )  
    {
      if( 2 == telmnt[0].clm.tco2flag )
      {
        for( dyr = 0; dyr < (transtime+1); ++dyr )
        { 
          gisend = grdco2dat[dyr].getdel( ifgrdco2 );
        
          if( -1 == gisend ) 
          { 
            cout << "Ran out of CO2 data" << endl << endl;
            flog1 << "Ran out of CO2 data" << endl << endl;
          
            exit( -1 );
          }
        }
      }
      else
      {
        gisend = grdco2dat[0].getdel( ifgrdco2 );
      
        if( -1 == gisend ) 
        { 
          cout << "Ran out of CO2 data" << endl << endl;
          flog1 << "Ran out of CO2 data" << endl << endl;
        
          exit( -1 );
        }
      }

      // Look for spatial co-registration problems between 
      //   cloudiness and CO2 spatially explicit data sets

      fatalerr = telmnt[0].coregerr( flog1, 
                                     SRADname, 
                                     telmnt[0].col,
                                     telmnt[0].row,    
                                     "CO2",
                                     grdco2dat[0].col,
                                     grdco2dat[0].row );

      if( fatalerr != 0 ) { exit( -1 ); }
    }
    
    // Read in historical monthly ozone data for grid cell
    
    if( 1 == telmnt[0].clm.to3flag )
    {
      for( dyr = 0; dyr < (transtime+1); ++dyr )
      { 
        gisend = o3dat[dyr].getdel( ifo3 );
        
        if( -1 == gisend ) 
        { 
          cout << "Ran out of Ozone data" << endl << endl;
          flog1 << "Ran out of Ozone data" << endl << endl;
          
          exit( -1 );
        }
      }
    }
    else
    {
      gisend = o3dat[0].getdel( ifo3 );
      
      if( -1 == gisend ) 
      { 
        cout << "Ran out of Ozone data" << endl << endl;
        flog1 << "Ran out of Ozone data" << endl << endl;
        
        exit( -1 );
      }
    }
    
    // Look for spatial co-registration problems between cloudiness and
    // ozone spatially explicit data sets

    fatalerr = telmnt[0].coregerr( flog1, 
                                   SRADname, 
                                   telmnt[0].col,
                                   telmnt[0].row,    
                                   "AOT40",
                                   o3dat[0].col,
                                   o3dat[0].row );

    if( fatalerr != 0 ) { exit( -1 ); }
  


    // Determine monthly N deposition grid cell

    if( 1 == telmnt[0].clm.tndepflag )
    {
      for( dyr = 0; dyr < (transtime+1); ++dyr )
      {
        gisend = ndepdat[dyr].getdel( ifndep );
        
        if( -1 == gisend )
        {
          cout << "Ran out of N deposition data";
          cout << endl << endl;
          flog1 << "Ran out of N deposition data";
          flog1 << endl << endl;
        
          exit( -1 );
        }

        // Check input for valid data
        
        if( ndepdat[dyr].nhx < ZERO ) 
        { 
          flog1 << "Lon = " << ndepdat[dyr].col << " ";
          flog1 << "Lat = " << ndepdat[dyr].row << " ";
          flog1 << "NH4DEP is less than zero during ";
          flog1 << ndepdat[dyr].year << endl;
          
          ndepdat[dyr].nhx = ZERO; 
        }
        
        if( ndepdat[dyr].noy < ZERO ) 
        { 
          flog1 << "Lon = " << ndepdat[dyr].col << " ";
          flog1 << "Lat = " << ndepdat[dyr].row << " ";
          flog1 << "NO3DEP is less than zero during ";
          flog1 << ndepdat[dyr].year << endl;

          ndepdat[dyr].noy = ZERO; 
        }
        
        if( ndepdat[dyr].totndep 
            != ndepdat[dyr].nhx + ndepdat[dyr].noy )
        {
          ndepdat[dyr].totndep = ndepdat[dyr].nhx 
                                 + ndepdat[dyr].noy;
        }

        // Adjust NDEP units from mg N m-2 mo-1 to 
        //   g N m-2 mo-1 for use in TEM

        ndepdat[dyr].totndep *= 0.001;
        ndepdat[dyr].nhx *= 0.001;
        ndepdat[dyr].noy *= 0.001;
      }
    }
    else
    {
      gisend = ndepdat[0].getdel( ifndep );

      if( -1 == gisend )
      {
        cout << "Ran out of N deposition data";
        cout << endl << endl;
        flog1 << "Ran out of N deposition data";
        flog1 << endl << endl;
        
        exit( -1 );
      }

      // Check input for valid data

      if( ndepdat[0].nhx < ZERO ) 
      { 
        flog1 << "Lon = " << ndepdat[0].col << " ";
        flog1 << "Lat = " << ndepdat[0].row << " ";
        flog1 << "NH4DEP is less than zero during ";
        flog1 << ndepdat[0].year << endl;
          
        ndepdat[0].nhx = ZERO; 
      }
        
      if( ndepdat[0].noy < ZERO ) 
      { 
        flog1 << "Lon = " << ndepdat[0].col << " ";
        flog1 << "Lat = " << ndepdat[0].row << " ";
        flog1 << "NO3DEP is less than zero during ";
        flog1 << ndepdat[0].year << endl;

        ndepdat[0].noy = ZERO; 
      }
        
      if( ndepdat[0].totndep 
          != ndepdat[0].nhx + ndepdat[0].noy )
      {
        ndepdat[0].totndep = ndepdat[0].nhx + ndepdat[0].noy;
      }

      // Adjust NDEP units from mg N m-2 mo-1 to 
      //   g N m-2 mo-1 for use in TEM

      ndepdat[0].totndep *= 0.001;
      ndepdat[0].nhx *= 0.001;
      ndepdat[0].noy *= 0.001;
    }

    // Look for spatial co-registration problems between cloudiness and
    // N deposition spatially explicit data sets

    fatalerr = telmnt[0].coregerr( flog1, 
                                   SRADname, 
                                   telmnt[0].col,
                                   telmnt[0].row,    
                                   "NDEP",
                                   ndepdat[0].col,
                                   ndepdat[0].row );

    if( fatalerr != 0 ) { exit( -1 ); }
  }

  if( 0 == pdyr ) { dyr = 0; }
  else if( 0 == istateflag && pdyr < (totsptime+1) )
  {
    dyr = (pdyr-1)%spintime + 1;
  }
  else
  {
    if( 0 == istateflag ) { dyr = pdyr - totsptime; }
    else{ dyr = pdyr; }
  }


  if( 0 == telmnt[0].clm.tcldsflag )
  {
    if( 0 == telmnt[0].clm.sradflag )
    {
      for( dm = 0; dm < (CYCLE+1); ++dm )
      {
        girrdat[dyr].mon[dm] = girrdat[0].mon[dm];
      }
    }

    if( 1 == telmnt[0].clm.cldflag )
    {
      for( dm = 0; dm < (CYCLE+1); ++dm )
      {
        cldsdat[dyr].mon[dm] = cldsdat[0].mon[dm];
      }
    }
    else
    {
      for( dm = 0; dm < (CYCLE+1); ++dm )
      {
        nirrdat[dyr].mon[dm] = nirrdat[0].mon[dm];
      }
    }

    if( 1 == telmnt[0].clm.parflag )
    {
      for( dm = 0; dm < (CYCLE+1); ++dm )
      {
        pardat[dyr].mon[dm] = pardat[0].mon[dm];
      }
    }
  }

  if( 0 == telmnt[0].clm.ttairflag )
  {
    tairdat[dyr].max = tairdat[0].max;
    tairdat[dyr].ave = tairdat[0].ave;

    for( dm = 0; dm < (CYCLE+1); ++dm )
    {
      tairdat[dyr].mon[dm] = tairdat[0].mon[dm];
    }
  }

  if( 0 == telmnt[0].clm.tprecflag )
  {
    precdat[dyr].total = precdat[0].total;

    for( dm = 0; dm < (CYCLE+1); ++dm )
    {
      precdat[dyr].mon[dm] = precdat[0].mon[dm];
    }
  }

  if( 0 == telmnt[0].clm.tco2flag )
  {
    for( dm = 0; dm < (CYCLE+1); ++dm )
    {
      grdco2dat[dyr].mon[dm] = grdco2dat[0].mon[dm];
    }
  }

  if( 0 == telmnt[0].clm.to3flag )
  {
    for( dm = 0; dm < (CYCLE+1); ++dm )
    {
      o3dat[dyr].mon[dm] = o3dat[0].mon[dm];
    }
  }

  if( 0 == telmnt[0].clm.tndepflag )
  {
    ndepdat[dyr].totndep = ndepdat[0].totndep;
    ndepdat[dyr].nhx = ndepdat[0].nhx;
    ndepdat[dyr].noy = ndepdat[0].noy;
  }


  // Determine maximum monthly air temperature for year for 
  //   each grid cell
    
  telmnt[0].mxtair = tairdat[dyr].max;
  telmnt[0].avetair = tairdat[dyr].ave;


  // Determine annual precipitation for each grid cell
    
  telmnt[0].yrprec = precdat[dyr].total;


  // Interpolate annual atmospheric CO2 concentrations
  //   to a monthly temporal resolution for grid cell
  //   Value in co2dat assumed to represent July atmospheric 
  //   CO2 concentrations    
  
  if( 1 == telmnt[0].clm.tco2flag )
  {    
    if( dyr > 0 )
    {
      if( pdyr < (totsptime+1) )
      {
        for( dm = 0; dm < (CYCLE+1); ++dm ) 
        { 
          telmnt[0].climate[telmnt[0].clm.I_CO2][dm] = co2dat[0].mco2; 
        }
      }
      else
      {
        for( dm = 0; dm < CYCLE; ++dm )
        {
          if( dm < 6 )
          {
            telmnt[0].climate[telmnt[0].clm.I_CO2][dm] = co2dat[dyr-1].mco2
                                                         + ((dm + 6) 
                                                         * (co2dat[dyr].mco2 
                                                         - co2dat[dyr-1].mco2)
                                                         / (double) CYCLE);
          }
          else
          {
            telmnt[0].climate[telmnt[0].clm.I_CO2][dm] = co2dat[dyr].mco2
                                                         + ((dm - 6) 
                                                         * (co2dat[dyr+1].mco2 
                                                         - co2dat[dyr].mco2)
                                                         / (double) CYCLE);
          }
        }
      }
    }
    else
    {
      for( dm = 0; dm < (CYCLE+1); ++dm )
      {
        telmnt[0].climate[telmnt[0].clm.I_CO2][dm] = telmnt[0].clm.getCO2LEVEL();
      }
    }
  
    telmnt[0].climate[telmnt[0].clm.I_CO2][CYCLE] = telmnt[0].climate[telmnt[0].clm.I_CO2][CYCLE-1];
  }

 // Assign information from files to telmnt.climate

  for( dm = 0; dm < (CYCLE+1); ++dm )
  {
    // Air temperature
    
    telmnt[0].climate[telmnt[0].clm.I_TAIR][dm] = tairdat[dyr].mon[dm];

    // Precipitation
    
    telmnt[0].climate[telmnt[0].clm.I_PREC][dm] = precdat[dyr].mon[dm];
    
    // Rain and Snowfall
    
    telmnt[0].clm.precsplt( telmnt[0].climate[telmnt[0].clm.I_PREC][dm], 
                            telmnt[0].climate[telmnt[0].clm.I_TAIR][dm],
                            telmnt[0].climate[telmnt[0].clm.I_RAIN][dm], 
                            telmnt[0].climate[telmnt[0].clm.I_SNWFAL][dm] );

    // Atmospheric CO2

    if( 0 == telmnt[0].clm.tco2flag 
        || 2 == telmnt[0].clm.tco2flag )
    {
      telmnt[0].climate[telmnt[0].clm.I_CO2][dm] = grdco2dat[dyr].mon[dm];
    }

    // AOT40 ozone index
    
    telmnt[0].climate[telmnt[0].clm.I_AOT40][dm] = o3dat[dyr].mon[dm];

    // Calculate monthly N deposition based on proportion of 
    //   annual precipitation that occurs during a particular 
    //   month

    if( precdat[dyr].total > 0.01 )
    {
      telmnt[0].climate[telmnt[0].clm.I_TNDEP][dm] = ndepdat[dyr].totndep
                                                     * precdat[dyr].mon[dm]
                                                     / precdat[dyr].total;

      telmnt[0].climate[telmnt[0].clm.I_NH4DEP][dm] = ndepdat[dyr].nhx
                                                      * precdat[dyr].mon[dm]
                                                      / precdat[dyr].total;

      telmnt[0].climate[telmnt[0].clm.I_NO3DEP][dm] = ndepdat[dyr].noy
                                                      * precdat[dyr].mon[dm]
                                                      / precdat[dyr].total;

    }
    else
    {
      telmnt[0].climate[telmnt[0].clm.I_TNDEP][dm] = ZERO;
      telmnt[0].climate[telmnt[0].clm.I_NH4DEP][dm] = ZERO;
      telmnt[0].climate[telmnt[0].clm.I_NO3DEP][dm] = ZERO;
    }
  }


//**************************************************************

    
  // Calculate GIRR during first year of simulation 
  //   (Note: use same values throughout simulation) 

  if( 1 == telmnt[0].clm.sradflag )
  {
    if( 0 == pdyr )
    {
      if( 0 == telmnt[0].lonlatflag ) { lat = latdat.lat; } 
      else { lat = telmnt[0].row; }

      telmnt[0].clm.yrsumday = ZERO;
      
      for( dm = 0; dm < CYCLE; ++dm )
      {
        telmnt[0].climate[telmnt[0].clm.I_GIRR][dm] = telmnt[0].clm.xgirr( lat, 
                                                                           dm, 
                                                                           telmnt[0].clm.yrsumday );
      }

      telmnt[0].climate[telmnt[0].clm.I_GIRR][CYCLE] = telmnt[0].climate[telmnt[0].clm.I_GIRR][0];
    }
  }
  else 
  { 
    for( dm = 0; dm < (CYCLE+1); ++dm )
    {  
      telmnt[0].climate[telmnt[0].clm.I_GIRR][dm] = girrdat[dyr].mon[dm] * Watts2cal;
    }
  }

  // Calculate NIRR, CLDINESS and PAR or retrieve from earlier calculations

  for( dm = 0; dm < (CYCLE+1); ++dm )
  {
    if( 1 == telmnt[0].clm.cldflag )
    {
      telmnt[0].climate[telmnt[0].clm.I_CLDS][dm] = cldsdat[dyr].mon[dm];

      telmnt[0].climate[telmnt[0].clm.I_NIRR][dm] = telmnt[0].clm.xnirr( telmnt[0].climate[telmnt[0].clm.I_CLDS][dm], 
	                                                                 telmnt[0].climate[telmnt[0].clm.I_GIRR][dm] );
    }
    else
    {
      telmnt[0].climate[telmnt[0].clm.I_NIRR][dm] = nirrdat[dyr].mon[dm] * Watts2cal;

      telmnt[0].climate[telmnt[0].clm.I_CLDS][dm] = telmnt[0].clm.mkclds( telmnt[0].climate[telmnt[0].clm.I_GIRR][dm], 
                                                                          telmnt[0].climate[telmnt[0].clm.I_NIRR][dm] );
    }
      
    if( 0 == telmnt[0].clm.parflag )
    {
      
      telmnt[0].climate[telmnt[0].clm.I_PAR][dm]  = telmnt[0].clm.xpar( telmnt[0].climate[telmnt[0].clm.I_CLDS][dm], 
                                                                        telmnt[0].climate[telmnt[0].clm.I_NIRR][dm] );
    }
    else
    {
      telmnt[0].climate[telmnt[0].clm.I_PAR][dm] = pardat[dyr].mon[dm] * Watts2cal;
    }
  }
    
    
  // Set year 

  telmnt[0].year = telmnt[0].clm.startyr 
                   - totsptime 
                   - 1 
                   + pdyr;

    
  // Copy TEMclm results to output variables

  if( 1 == telmnt[0].clm.predflag )
  {
    if ( (1 == spinoutfg 
         && telmnt[0].year < telmnt[0].clm.startyr)
         || (2 == spinoutfg 
         && telmnt[0].year >= (telmnt[0].clm.startyr-spinoutyrs))
         || (telmnt[0].year >= telmnt[0].clm.startyr) )
    {
      if( 1 == telmnt[0].clm.cldflag )
      {
        telmnt[0].carea = cldsdat[0].carea;
        telmnt[0].region = cldsdat[0].region;
      }
      else
      {
        telmnt[0].carea = nirrdat[0].carea;
        telmnt[0].region = nirrdat[0].region;
      }
    
      telmnt[0].atmswritepred( fclmpred, 
                               clmpredmap, 
                               telmnt[0].natmspred );
    }
  }
	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void updateTLCLUCGridCell( const int& pdyr )
{

  int dyr;
  int tstyr;
  int gisend;
  int ichrt;

  fatalerr = 0;

  if( 0 == pdyr )
  {
    // Get the total number of cohorts in the grid cell

    if( 1 == telmnt[0].lcluc.tlulcflag )
    {
      for( dyr = 0; dyr < (transtime+1); ++dyr )
      {
        gisend = mxcohrtdat[dyr].getdel( ifnumchrts );


        // Check data for spatial coregistration errors

        fatalerr = telmnt[0].coregerr( flog1,
                                       "Climate",
                                       telmnt[0].col,
                                       telmnt[0].row,
                                       "MAXCOHORTS",
                                       mxcohrtdat[dyr].col,
                                       mxcohrtdat[dyr].row );

        if( fatalerr != 0 ) { exit( -1 ); }
      }


      if( -1 == gisend ) 
      { 
        cout << "Ran out of Number of Cohorts data";
        cout << endl << endl;
        flog1 << "Ran out of Number of Cohorts data";
        flog1 << endl << endl;
        
        exit( -1 );
      } 
    }
    else // 0 == telmnt[0].lcluc.tlulcflag
    {
      gisend = mxcohrtdat[0].getdel( ifnumchrts );

      if( -1 == gisend ) 
      { 
        cout << "Ran out of Number of Cohorts data";
        cout << endl << endl;
        flog1 << "Ran out of Number of Cohorts data";
        flog1 << endl << endl;
        
        exit( -1 );
      } 

      // Check data for spatial coregistration errors
    
      fatalerr = telmnt[0].coregerr( flog1, 
                                     "Climate", 
                                     telmnt[0].col,  
                                     telmnt[0].row, 
                                     "MAXCOHORTS", 
                                     mxcohrtdat[0].col, 
                                     mxcohrtdat[0].row );

      if( fatalerr != 0 ) { exit( -1 ); }

      for( dyr = 1; dyr < (transtime+1); ++dyr )
      {
        mxcohrtdat[dyr].col = mxcohrtdat[0].col;
        mxcohrtdat[dyr].row = mxcohrtdat[0].row;
        mxcohrtdat[dyr].carea = mxcohrtdat[0].carea;
        mxcohrtdat[dyr].year = mxcohrtdat[0].year + dyr;
        mxcohrtdat[dyr].total = mxcohrtdat[0].total;
        mxcohrtdat[dyr].natchrts = mxcohrtdat[0].natchrts;
        mxcohrtdat[dyr].region = mxcohrtdat[0].region;
      }
    }
      	       
       
    // Get land use/land cover cohort data for  the grid cell 

    if( 1 == telmnt[0].lcluc.tlulcflag )
    {
      for( dyr = 0; dyr < (transtime+1); ++dyr )
      {
        for( ichrt = 0; ichrt < mxcohrtdat[dyr].total; ++ichrt )
        {
          gisend = lulcdat[dyr][ichrt].getdel( iflulc );

          if( -1 == gisend ) 
          { 
            flog1 << "Ran out of Land cover/land use data";
            flog1 << endl << endl;
            
            exit( -1 );
          }

          // Check data for spatial coregistration errors
    
          fatalerr = telmnt[0].coregerr( flog1, 
                                         "Climate", 
                                         telmnt[0].col,  
                                         telmnt[0].row, 
                                         "LULC", 
                                         lulcdat[dyr][ichrt].col, 
                                         lulcdat[dyr][ichrt].row );

          if( fatalerr != 0 ) 
          { 
            cout << "year = " << lulcdat[dyr][ichrt].year;
            cout << " icohort = " << lulcdat[dyr][ichrt].icohort;
            cout << endl;

            exit( -1 ); 
          }
        }
      }
    }
    else // 0 == telmnt[0].lcluc.tlulcflag
    {
      for( ichrt = 0; ichrt < mxcohrtdat[0].total; ++ichrt )
      {
        gisend = lulcdat[0][ichrt].getdel( iflulc );

        if( -1 == gisend ) 
        { 
          flog1 << "Ran out of Land cover/land use data";
          flog1 << endl << endl;
          
          exit( -1 );
        }

        fatalerr = telmnt[0].coregerr( flog1, 
                                       "Climate", 
                                       telmnt[0].col,  
                                       telmnt[0].row, 
                                       "LULC", 
                                       lulcdat[0][ichrt].col, 
                                       lulcdat[0][ichrt].row );

        if( fatalerr != 0 ) { exit( -1 ); }

        for( dyr = 1; dyr < (transtime+1); ++dyr )
        {
          lulcdat[dyr][ichrt].year = lulcdat[0][ichrt].year + dyr;
          lulcdat[dyr][ichrt].isrccohort = lulcdat[0][ichrt].isrccohort;

          if( (lulcdat[0][ichrt].standage + dyr) < MAXSTANDAGE )
          {
            lulcdat[dyr][ichrt].standage = lulcdat[0][ichrt].standage + dyr;
          }
          else
          {
            lulcdat[dyr][ichrt].standage = MAXSTANDAGE;
          }         

          lulcdat[dyr][ichrt].chrtarea = lulcdat[0][ichrt].chrtarea;
          lulcdat[dyr][ichrt].potveg = lulcdat[0][ichrt].potveg;
          lulcdat[dyr][ichrt].currentveg = lulcdat[0][ichrt].currentveg;
          lulcdat[dyr][ichrt].subtype = lulcdat[0][ichrt].subtype;
          lulcdat[dyr][ichrt].agstate = lulcdat[0][ichrt].agstate;
          lulcdat[dyr][ichrt].agprevstate = lulcdat[0][ichrt].agprevstate;
          lulcdat[dyr][ichrt].tillflag = lulcdat[0][ichrt].tillflag;                              
          lulcdat[dyr][ichrt].fertflag = lulcdat[0][ichrt].fertflag;                              
          lulcdat[dyr][ichrt].irrgflag = lulcdat[0][ichrt].irrgflag;                              
          lulcdat[dyr][ichrt].disturbflag = lulcdat[0][ichrt].disturbflag;                              
          lulcdat[dyr][ichrt].disturbmonth = lulcdat[0][ichrt].disturbmonth;                              
          lulcdat[dyr][ichrt].FRI = lulcdat[0][ichrt].FRI;
          lulcdat[dyr][ichrt].slashpar = lulcdat[0][ichrt].slashpar; 
          lulcdat[dyr][ichrt].vconvert = lulcdat[0][ichrt].vconvert; 
          lulcdat[dyr][ichrt].prod10par = lulcdat[0][ichrt].prod10par; 
          lulcdat[dyr][ichrt].prod100par = lulcdat[0][ichrt].prod100par; 
          lulcdat[dyr][ichrt].vrespar = lulcdat[0][ichrt].vrespar; 
          lulcdat[dyr][ichrt].sconvert = lulcdat[0][ichrt].sconvert;
          lulcdat[dyr][ichrt].region = lulcdat[0][ichrt].region;          
        }
      }
    }      
  } // end of 0 == pdyr
    

  if( 0 == pdyr ) { tstyr = 0; }
  else if( 0 == istateflag && pdyr < (totsptime+1) )
  {
    tstyr = 1;
  }
  else
  {
    if( 0 == istateflag )
    {
      tstyr = pdyr - totsptime;
    }
    else { tstyr = pdyr; }
  }

  // Check data for temporal coregistration errors in mxcohrtdat
    
  if( 1 == telmnt[0].lcluc.tlulcflag
      && pdyr >= (totsptime+1)
      && telmnt[0].year != mxcohrtdat[tstyr].year )
  { 
    cout << " Year in CLM data does not match ";
    cout << " Year in MAXCOHORTS data" << endl;
    cout << " at Lon = " << telmnt[0].col;
    cout << "  Lat = " << telmnt[0].row << endl;
    cout << "  CLM year = " << telmnt[0].year;
    cout << "  MAXCOHORTS year = " << mxcohrtdat[tstyr].year;
    cout << endl << endl;
      
    flog1 << " Year in CLM data does not match ";
    flog1 << " Year in MAXCOHORTS data" << endl << endl;
    flog1 << " at Lon = " << telmnt[0].col;
    flog1 << "  Lat = " << telmnt[0].row << endl;
    flog1 << " CLM year = " << telmnt[0].year;
    flog1 << " MAXCOHORTS year = " << mxcohrtdat[tstyr].year;
    flog1 << endl << endl;

    exit( -1 );
  }


  // Pass mxcohortdat information to telmnt[0]

  telmnt[0].maxcohorts = mxcohrtdat[tstyr].total;
  telmnt[0].natcohorts = mxcohrtdat[tstyr].natchrts;
  telmnt[0].carea = mxcohrtdat[tstyr].carea;
  telmnt[0].region = mxcohrtdat[tstyr].region;

  if( 0 == tstyr 
      || (0 == istateflag && pdyr > 1 && pdyr <= (totsptime+1)) )
  {
    telmnt[0].prvmxcohrts = mxcohrtdat[tstyr].total;
  }
  else
  {
    telmnt[0].prvmxcohrts = mxcohrtdat[tstyr-1].total;
  }

  for( ichrt = 0; ichrt < telmnt[0].maxcohorts; ++ichrt )
  {
    // Check data for temporal coregistration errors in lulcdat

    if( 1 == telmnt[0].lcluc.tlulcflag
        && pdyr >= (totsptime+1)
        && telmnt[0].year != lulcdat[tstyr][ichrt].year )
    { 
      cout << " Year in CLM data does not match ";
      cout << " Year in LCLUC data" << endl;
      cout << " at Lon = " << telmnt[0].col;
      cout << "  Lat = " << telmnt[0].row << endl;
      cout << "  CLM year = " << telmnt[0].year;
      cout << "  LCLUC year = " << lulcdat[tstyr][ichrt].year;
      cout << " for cohort " << (ichrt+1);
      cout << endl << endl;
      
      flog1 << " Year in CLM data does not match ";
      flog1 << " Year in LCLUC data" << endl << endl;
      flog1 << " at Lon = " << telmnt[0].col;
      flog1 << "  Lat = " << telmnt[0].row << endl;
      flog1 << " CLM year = " << telmnt[0].year;
      flog1 << " LCLUC year = " << lulcdat[tstyr][0].year;
      cout << " for cohort " << (ichrt+1);
      flog1 << endl << endl;

      exit( -1 );
    }


    // Pass lulcdat information to telmnt[0].cohort
    
    telmnt[0].cohort[ichrt].srcCohort = lulcdat[tstyr][ichrt].isrccohort;
    telmnt[0].cohort[ichrt].standage = lulcdat[tstyr][ichrt].standage;
    telmnt[0].cohort[ichrt].chrtarea = lulcdat[tstyr][ichrt].chrtarea;
    telmnt[0].cohort[ichrt].potveg = lulcdat[tstyr][ichrt].potveg;
    telmnt[0].cohort[ichrt].currentveg = lulcdat[tstyr][ichrt].currentveg;
    telmnt[0].cohort[ichrt].subtype = lulcdat[tstyr][ichrt].subtype;
    telmnt[0].cohort[ichrt].agstate = lulcdat[tstyr][ichrt].agstate;
    telmnt[0].cohort[ichrt].agprvstate = lulcdat[tstyr][ichrt].agprevstate;   
    telmnt[0].cohort[ichrt].tillflag = lulcdat[tstyr][ichrt].tillflag;                           
    telmnt[0].cohort[ichrt].fertflag = lulcdat[tstyr][ichrt].fertflag;                              
    telmnt[0].cohort[ichrt].irrgflag = lulcdat[tstyr][ichrt].irrgflag;                              
    telmnt[0].cohort[ichrt].disturbflag = lulcdat[tstyr][ichrt].disturbflag;                              
    telmnt[0].cohort[ichrt].disturbmonth = lulcdat[tstyr][ichrt].disturbmonth;                              

    // If cohort is in agriculture the during first year of the 
    //   historical study period, convert cohort to agriculture 
    //   during the first year of the transient spinup.  Keep
    //   cohort in agriculture throughout spinup period

    if( 1 == pdyr 
        && 0 == istateflag  
        && telmnt[0].cohort[ichrt].agstate > 0
        && telmnt[0].cohort[ichrt].agprvstate > 0 )
    {
      telmnt[0].cohort[ichrt].agprvstate = 0;
      telmnt[0].cohort[ichrt].disturbflag = 1;
      telmnt[0].cohort[ichrt].disturbmonth = 1;
    }
 
    telmnt[0].cohort[ichrt].FRI = lulcdat[tstyr][ichrt].FRI;
    telmnt[0].cohort[ichrt].slashpar = lulcdat[tstyr][ichrt].slashpar; 
    telmnt[0].cohort[ichrt].vconvert = lulcdat[tstyr][ichrt].vconvert; 
    telmnt[0].cohort[ichrt].prod10par = lulcdat[tstyr][ichrt].prod10par; 
    telmnt[0].cohort[ichrt].prod100par = lulcdat[tstyr][ichrt].prod100par; 
    telmnt[0].cohort[ichrt].vrespar = lulcdat[tstyr][ichrt].vrespar; 
    telmnt[0].cohort[ichrt].sconvert = lulcdat[tstyr][ichrt].sconvert; 
    telmnt[0].region = lulcdat[tstyr][ichrt].region;


    telmnt[0].cohort[ichrt].cmnt = telmnt[0].lcluc.getCommunityType( lulcdat[tstyr][ichrt].subtype );

    telmnt[0].cohort[ichrt].agcmnt = telmnt[0].cohort[ichrt].cmnt;
    
    if( pdyr > 0 && lulcdat[tstyr][ichrt].agstate > 0 )
    {
      telmnt[0].cohort[ichrt].agcmnt = telmnt[0].lcluc.getCommunityType( lulcdat[tstyr][ichrt].currentveg );
    }

    telmnt[0].cohort[ichrt].wfpsoff = telmnt[0].lcluc.getWFPSOFF( lulcdat[tstyr][ichrt].subtype );

  }

};

/* *************************************************************
************************************************************* */


/* **************************************************************
************************************************************** */

void updateTTEMGridCell( const int& pdyr )
{
  int dm;

  int ichrt;

  int tchrt;

/* *************************************************************
            INITIALIZE TEM STATE FOR NEW COHORTS
************************************************************* */
  
  if( telmnt[0].maxcohorts > telmnt[0].prvmxcohrts )
  {
    for ( ichrt = telmnt[0].prvmxcohrts; 
          ichrt < telmnt[0].maxcohorts; 
          ++ichrt )
    {     
      tchrt = telmnt[0].cohort[ichrt].srcCohort - 1;
      
      telmnt[0].setCohortTEMState( telmnt[0].cohort[tchrt],
                                   telmnt[0].cohort[ichrt] );
    }
  }

/* *************************************************************
                     UPDATE TEM FOR GRID CELL
************************************************************* */

    
/* *************************************************************
		BEGIN VEGETATION MOSAIC LOOP
************************************************************* */

  for( ichrt = 0; ichrt < telmnt[0].maxcohorts; ++ichrt )
  {
    // Get vegetation community type of cohort

    telmnt[0].tem.veg.cmnt = telmnt[0].cohort[ichrt].cmnt;
    
    // Determine soil characteristics for cohort
    
    telmnt[0].tem.soil.xtext( telmnt[0].tem.veg.cmnt,
                              telmnt[0].tem.soil.getPCTSILT(),
                              telmnt[0].tem.soil.getPCTCLAY() );
                              
                              
    for( dm = 0; dm < CYCLE; ++dm )
    {     
      // Run TEM
                           
      telmnt[0].updateTEMmonth( flog1,
                                equil, 
                                totsptime, 
                                pdyr, 
                                dm,
                                ichrt );
    } // end of CYCLE loop
    
    if( ostateflag > 0 && telmnt[0].tem.totyr == ostateyear )
    {
      if( 1 == ostateflag )
      {
        telmnt[0].writeBinaryCohortState( ofstate, ichrt );
      }
      else
      {
        telmnt[0].writeCohortState( ofstate, ichrt );
      }
    }

    if ( (1 == spinoutfg && telmnt[0].tem.totyr < telmnt[0].tem.startyr)
         || (2 == spinoutfg 
         && telmnt[0].tem.totyr >= (telmnt[0].tem.startyr-spinoutyrs))
         || (telmnt[0].tem.totyr >= telmnt[0].tem.startyr 
         && telmnt[0].tem.totyr <= telmnt[0].tem.endyr)
         && 0 == (telmnt[0].wrtyr%telmnt[0].tem.diffyr) )
    {

      // Output TEM transient results for specified years to files

      telmnt[0].temwritepred( ftempred, 
                              tempredmap, 
                              pdyr, 
                              ichrt,
                              telmnt[0].ntempred );
    }
  } // End of cohort loop
  
};

