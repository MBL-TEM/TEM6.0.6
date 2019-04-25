/* *************************************************************
Program :  XTRANALCHRT606C.CXX

Description:    Program analyzes results of TEM run including:
                analyzes of transient data, produces transient 
                output, preprocesses data for vegetation mosaic.
************************************************************* */

BY DOWNLOADING THIS PROGRAM YOU AGREE TO THE FOLLOWING TERMS OF USE:

Copyright © 2018.  The Marine Biological Laboratory (“MBL”). All 
Rights Reserved.  

Permission to use, copy, modify, and distribute this software, 
including all object code and source code, and any accompanying
documentation (together the “Software”) for educational and 
not-for-profit research purposes, without fee and without a signed
licensing agreement, is hereby granted, provided that the above 
copyright notice, this paragraph and the following three paragraphs
appear in all copies, modifications, and distributions. For the 
avoidance of doubt, educational and not-for-profit research purposes
excludes any service or part of selling a service that uses the 
Software. To obtain a commercial license for the Software, contact 
the Technology Commercialization team at the Polsky Center for 
Entrepreneurship and Innovation, University of Chicago, 1452 East 
53rd Street, 2nd floor, Chicago, IL 60615.

Created by David W. Kicklighter, A. David McGuire, and 
Greg Christopher at The Marine Biological Laboratory.

The Software is copyrighted by MBL. The Software is supplied 
"as is", without any accompanying services from MBL. MBL 
does not warrant that the operation of the Software will be 
uninterrupted or error-free. The end-user understands that the 
Software was developed for research purposes and is advised not 
to rely exclusively on the Software for any reason.

IN NO EVENT SHALL MBL BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, 
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
PROFITS, ARISING OUT OF THE USE OF THE SOFTWARE, EVEN IF MBL 
HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. MBL SPECIFICALLY
DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE SOFTWARE PROVIDED HEREUNDER IS PROVIDED "AS IS".  MBL HAS 
NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
ENHANCEMENTS, OR MODIFICATIONS.

*****************************************************************
************************************************************** */

#define ANSI_CPP

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


#ifdef ANSI_CPP

  #include<cstdlib>

  #include<cmath>

#endif

#ifdef BORLAND_CPP

  #include<stdlib>

  #include<math>

#endif

#include<cctype>

  using std::toupper;
  using std::tolower;

#include<cstring>

#include<string>

  using std::string;

#include<sstream>

  using std::ostringstream;


#include "temconsts606.hpp"

#include "tbiome606.h"

#include "lulcdat605.h"
#include "tclmdat606.h"
#include "tmaxcohortdat605.h"
#include "ttemdat606.h"

struct Season 
{
  int tveg;
  int standage;
  int agstate;
  long carea;
  long subarea;
  int totyr;
  double total;
  double max;
  double ave;
  double min;
  double mon[CYCLE];
  string region;
};

Biome60 veg;
Lulcdata60 vegdat[MAXCHRTS];
Clmdata60 clmdat[MAXRTIME];
MaxCohortdata60 cohorts;
Temdata60 temdat[MAXRTIME];
Season pred;

struct Stats 
{
  long totgrid;
  long totarea;
  double outtot;
  double outmax;
  double outmin;
  double simpmean;
  double areawmean;
  double sumy;
  double sumysq;
  double sumsqy;
  double standev;
  double sumtotyr;
  long rejgrid;
  long rejarea;
};

Stats summ[MAXNVEG][MAXRTIME];
Stats totsumm[MAXRTIME];

void aggregateData( const string& period, 
                    const Season& pred, 
                    const int& ichrt );

void chkunits( const int& dataflag, const string& predmap );
void loadpred( const string& period );
void sumreport( ofstream& fout );

int i;
int kend;
long reccount;
long maxrec;  
long equilyr;
double predamnt;
string period;
string pername;
string predmap;
double missdata;
int numveg;
int testveg[MAXNVEG];
int qc;
double co2conc;
string covrage;
string covragetxt;
string clmsrc;
string clmunits;
string version;
string cpuname;
string soilfname;
string vegfname;
string elevfname;
string cldifname;
string tairfname;
string precfname;
string chrtfname;
long rundate;
int outprec;


int startyr;
int lastyr;
int startoutyr;
int lastoutyr;
int transflag;

string infile;
string outfile;

FILE* fveg;
FILE* fchrt;
FILE* fin;

ofstream fout;
ofstream flog1;

int dataflg;
string totunits;
string units;

int notegrd[MAXNVEG];  
int notetgrd;


int startage;
int lastage;

int tststate;


int main() 
{
  int allvflag;

  int dm;

  int dv;

  int dyr;

  int eqrsltsflg;

  int firstchrtyr;

  int icohort;

  int j;

  int len;

  int outflag;

  int potvflag;

  int regionflag;

  int tlulcflag;



  outprec = 1;

  cout << endl << "Enter the name of the INPUT file: " << endl;
  
  cin >> infile;
  
  fin = fopen( infile.c_str(), "r" );

  if( !fin ) 
  {
    cerr << endl << "Cannot open " << infile;
    cerr << " for data input." << endl;
    exit( -1 );
  }

  cout << "What format does the INPUT file use?" << endl;
  cout << "  Enter 0 for the climate data format:" << endl;
  cout << "  Enter 1 for the TEM output data format: " << endl;

  cin >> dataflg;

  cout << " dataflg = " << dataflg << endl;

  cout << "Enter the name of the cohort file: " << endl;
    
  cin >> chrtfname;


  if( dataflg != 1 ) 
  {
    cout << "Enter the name of the land cover file: " << endl;
    
    cin >> vegfname;
  } 


  cout << "Does the file contain transient data?" << endl;
  cout << "  Enter 0 if the file contains one year of output:"; 
  cout << endl;
  cout << "  Enter 1 if the file contains transient data: " << endl;
  
  cin >> transflag;


  cout << "Enter the number of grid cells represented in the ";
  cout << "data set: " << endl;
  
  cin >> maxrec;


  tlulcflag = 0;
  eqrsltsflg = 1;
  startyr = 0;
  lastyr = 0;
  firstchrtyr = 0;
  startoutyr = 0;
  lastoutyr = 9999;

  if( 1 == transflag ) 
  {
    cout << "Enter the first year in the input file: " << endl; 
    
    cin >> startyr;
    
    cout << "Enter the last year in the input file: " << endl; 
    
    cin >> lastyr;

    cout << "Does land cover change over time in the output: ";
    cout << endl;
    cout << "Enter 0 for no changes in land cover: " << endl;
    cout << "Enter 1 for changing land cover: " << endl;
    
    cin >> tlulcflag;
    
    if( 1 == tlulcflag )
    {
      cout << "Enter the first year of the maximum number of ";
      cout << "cohorts data: " << endl;
    
      cin >> firstchrtyr;
    }
            
    cout << "Enter the first year to report data for: " << endl; 
    
    cin >> startoutyr;
    
    cout << "Enter the last year to report data for: " << endl; 
    
    cin >> lastoutyr;


    if( 1 == dataflg )
    {
      cout << "Are equilibrium results included in ";
      cout << " the TEM output? " << endl;
      cout << "  Enter 0 if no:" << endl;
      cout << "  Enter 1 if yes: " << endl;
  
      cin >> eqrsltsflg;
    }
  } 


  cout << "What is the regional coverage?" << endl;
  cout << "  Enter 'All' for all grid cells" << endl;

  cin >> covrage;

  if( "All" == covrage 
      || "ALL" == covrage
      || "all" == covrage )
  {
    cout << "Enter region represented by all grid cells:" << endl;
    cin >> covragetxt;
  }
  else 
  { 
    covragetxt = covrage; 

    cout << "Is region defined in the TEM data or MXCOHRTS data?: ";
    cout << endl;
    cout << "Enter 0 for TEM data: " << endl;
    cout << "Enter 1 for MXCOHRTS data: " << endl;

    cin >> regionflag;
  }

  equilyr = 99999;
  switch( dataflg ) 
  {
    case 0: cout << "What is the source of the climate data?";
            cout << endl;
            
	    cin >> clmsrc;
	    
	    cout << "What are the units? " << endl;
	    
	    cin >> clmunits;
	    
	    break;

    case 1: cout << "What atmospheric CO2 concentration was ";
            cout << "used for the run? " << endl;
	    
	    cin >> co2conc;
	    
	    cout << "What version of the TEM model was used? " << endl;
	    
	    cin >> version;
	    
	    cout << "Enter the name of the computer used for ";
	    cout << "the TEM run: " << endl;
	    
	    cin >> cpuname;

	    cout << "Enter the date of the TEM run (YYMMDD): " << endl;

	    cin >> rundate;

	    cout << "Please enter the name of the file ";
	    cout << "containing the soil texture data" << endl;
	    cout << "used for TEM run: " << endl;

	    cin >> soilfname;

            len = soilfname.length();
	    for( j = 0; j < len; ++j ) 
            {
	      soilfname.at( j ) = toupper( soilfname.at( j ) );
	    }
	    
	    cout << "Please enter the name of the file ";
	    cout << "containing the vegetation data" << endl;
	    cout << "used for TEM run: " << endl;
	    
	    cin >> vegfname;
	    
	    len = vegfname.length();
	    for( j = 0; j < len;  ++j ) 
            {
              vegfname.at( j ) = toupper( vegfname.at( j ) );
	    }
	    
	    cout << "Please enter the name of the file ";
	    cout << "containing the elevation data" << endl;
	    cout << "used for TEM run: " << endl;
	    
	    cin >> elevfname;
	    
	    len = elevfname.length();
	    for( j = 0; j < len; ++j ) 
            {
	      elevfname.at( j ) = toupper( elevfname.at( j ) );
	    }
	    
	    cout << "Please enter the name of the file ";
	    cout << "containing the cloudiness" << endl;
	    cout << "or irradiance data used for TEM run: " << endl;
	    
	    cin >> cldifname;
	    
	    len = cldifname.length();
	    for( j = 0; j < len; ++j ) 
            {
	    cldifname.at( j ) = toupper( cldifname.at( j ) );
	    }
	    
	    cout << "Please enter the name of the file ";
	    cout << "containing the air temperature" << endl;
	    cout << "data used for TEM run: " << endl;
	    
	    cin >> tairfname;
	    
	    len = tairfname.length();
	    for( j = 0; j < len; ++j ) 
            {
              tairfname.at( j ) = toupper( tairfname.at( j ) );
            }
	    
	    cout << "Please enter the name of the file ";
	    cout << "containing the precipitation" << endl;
	    cout << "data used for TEM run: " << endl;
	    
	    cin >> precfname;
	    
	    len = precfname.length();
	    for( j = 0; j < len;  ++j ) 
            {
              precfname.at( j ) = toupper( precfname.at( j ) );
	    }
	    cout << endl;
	    cout << "Enter the year by which the model must ";
	    cout << "equilibrate: " << endl;
	    
	    cin >> equilyr;
	    
	    break;
  }

  missdata = -999.9;
  cout << endl << "Enter the value used for missing data: " << endl;
  
  cin >> missdata;

  cout << endl;
  cout << "Do you want statistics based on potential vegetation ";
  cout << " or current vegetation types?" << endl;
  cout << "  Enter 0 for potential vegetation:" << endl;
  cout << "  Enter 1 for Current vegetation: " << endl;

  cin >> potvflag;


  for( dv = 0; dv < MAXNVEG; ++dv ) { testveg[dv] = 0; }

  cout << endl;
  cout << "Do you want statistics for all vegetation ";
  cout << "types (except ice)?";
  cout << endl << "  Enter 1 for YES and 0 for NO: " << endl;
  
  cin >> allvflag;
  
  if( 1 == allvflag ) 
  {
    numveg = MAXNVEG;
    
    for( dv = 0; dv < numveg; ++dv ) { testveg[dv] = dv; }
  }
  else 
  {
    allvflag = 0;

    cout << endl;
    cout << "How many vegetation types do you want to ";
    cout << "determine statistics for? " << endl;
      
    cin >> numveg;

    cout << "Enter each TEMVEG for which you want statistics:"; 
    cout<< endl;
      
    for( dv = 0; dv < numveg; ++dv ) 
    {
      cout << (dv+1) << " ";
      cin >> testveg[dv];
    }
  }  

  if( 1 == dataflg )
  {
    cout << "What is the youngest stand age you want to consider? " << endl;
    cout << "  Enter 0 for all ages: " << endl;

    cin >> startage;

    cout << " startage = " << startage << endl;

    cout << "What is the oldest stand age you want to consider? " << endl;
    cout << "  Enter 5000 for all ages: " << endl;

    cin >> lastage;

    cout << " lastage = " << lastage << endl;

    cout << "What managed lands do you want to consider? " << endl;
    cout << "  Enter 99 for all managed lands including natural vegetation: " << endl;

    cin >> tststate;

    cout << " tststate = " << tststate << endl;
  }
  else
  {
    startage = 0;
    lastage = 5000;
    tststate = 99;
  }


  cout << endl;
  cout << "                     POSSIBLE TIME PERIODS" << endl;
  cout << endl;
  cout << "ann max ave min jan feb mar apr may jun jul aug sep ";
  cout << "oct nov dec" << endl;
  cout << endl << endl << "Enter time period for summary: " << endl;
  
  cin >> period;

  len = period.length();
  for( j = 0; j < len;  ++j ) 
  {
    period.at( j ) = tolower( period.at( j ) );
  }

  outflag = 1;
  while( 1 == outflag ) 
  {
    cout << endl << "Enter the name of the output file: " << endl;
    
    cin >> outfile;
    
    if( outfile == infile ) 
    {
      cout << endl;
      cout << "INPUT file and OUTPUT file cannot have the ";
      cout << "same name.  Try again!" << endl;
    }
    else { outflag = 0; }
  }

  cout << endl;

  fout.open( outfile.c_str(), ios::out );

  for( dv = 0; dv < MAXNVEG; ++dv ) 
  {
    for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
    {
      summ[dv][dyr].totgrid    = 0;
      summ[dv][dyr].totarea    = 0;
      summ[dv][dyr].outtot     = 0;
      summ[dv][dyr].outmax     = 0;
      summ[dv][dyr].outmin     = 0;
      summ[dv][dyr].simpmean   = 0;
      summ[dv][dyr].areawmean  = 0;
      summ[dv][dyr].sumy       = 0;
      summ[dv][dyr].sumysq     = 0;
      summ[dv][dyr].sumsqy     = 0;
      summ[dv][dyr].standev    = 0;
      summ[dv][dyr].sumtotyr   = 0;
      summ[dv][dyr].rejgrid    = 0;
      summ[dv][dyr].rejarea    = 0;
    }
  }

  for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
  {
    totsumm[dyr].totgrid      = 0;
    totsumm[dyr].totarea      = 0;
    totsumm[dyr].outtot       = 0;
    totsumm[dyr].outmax       = 0;
    totsumm[dyr].outmin       = 0;
    totsumm[dyr].simpmean     = 0;
    totsumm[dyr].areawmean    = 0;
    totsumm[dyr].sumy         = 0;
    totsumm[dyr].sumysq       = 0;
    totsumm[dyr].sumsqy       = 0;
    totsumm[dyr].standev      = 0;
    totsumm[dyr].sumtotyr     = 0;
    totsumm[dyr].rejgrid      = 0;
    totsumm[dyr].rejarea      = 0;
  }

  fchrt = fopen( chrtfname.c_str(), "r" );

  if( !fchrt ) 
  {
    cerr << endl << "Cannot open " << chrtfname;
    cerr << " for cohort data input." << endl;
             
    exit( -1 );
  }
  
  if( 0 == dataflg )
  {
    fveg = fopen( vegfname.c_str(), "r" );

    if( !fveg ) 
    {
      cerr << endl << "Cannot open " << vegfname;
      cerr << " for vegetation data input." << endl;
              
      exit( -1 );
    }
  }


  kend = 0;
  for( reccount = 0; reccount < maxrec; ++reccount )
  {
    for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr )
    {
      if( 0 == dataflg ) 
      {        
        if( 1 == tlulcflag || 0 == dyr )
        {
          kend = cohorts.getdel( fchrt );      

          if( -1 == kend ) 
          {
            cerr << "Ran out of cohort data after grid cell ";
            cerr << reccount << endl;
          
            exit( -1 );
          }


          for( icohort = 0; icohort < cohorts.total; ++icohort )
          {
            kend = vegdat[icohort].getdel( fveg );
          }

          if( -1 == kend )
          {
            cerr << "Ran out of vegetation data after grid cell ";
            cerr << reccount << endl;
        
            exit( -1 );
          }
        }

        kend = clmdat[dyr].getdel( fin );

        if( -1 == kend ) 
        {
          cerr << "Ran out of climate data for " << predmap;
          cerr << " after grid cell ";
          cerr << reccount << endl;
          
          exit( -1 );
        }

	predmap = clmdat[dyr].varname;
        

        pred.standage = 3000;
	pred.carea = cohorts.carea;
	pred.totyr = clmdat[dyr].year;
	pred.total = clmdat[dyr].total;
	pred.max = clmdat[dyr].max;
	pred.ave = clmdat[dyr].ave;
	pred.min = clmdat[dyr].min;

	for( dm = 0; dm < CYCLE; ++dm ) 
        { 
          pred.mon[dm] = clmdat[dyr].mon[dm];
        }

        pred.region = covrage;
 
        for(icohort = 0; icohort < cohorts.total; ++icohort )
        {
          if( 0 == potvflag )
          {
            pred.tveg = vegdat[icohort].potveg;
          }
          else
          { 
            pred.tveg = vegdat[icohort].currentveg;
          }

          if( pred.tveg <= 0 || pred.tveg >= MAXNVEG )
          {
            pred.tveg = 0;
          }

          pred.subarea = vegdat[icohort].chrtarea;

          aggregateData( period, pred, icohort ); 
        }
      }

      if( 1 == dataflg ) 
      {
        if( 0 == dyr 
            && (0 == eqrsltsflg 
            || 0 == tlulcflag) )
        {
          kend = cohorts.getdel( fchrt );
        }

        if( 1 == tlulcflag 
            && (0 == eqrsltsflg
            || (1 == eqrsltsflg && (dyr <= 1  
            || ((startyr+dyr) > (firstchrtyr+1))))) )
        { 
          kend = cohorts.getdel( fchrt );
        }

        if( -1 == kend ) 
        {
          cerr << "Ran out of cohort data after grid cell ";
          cerr << reccount << endl;
          
          exit( -1 );
        }


        for( icohort = 0; icohort < cohorts.total; ++icohort )
        {
          kend = temdat[dyr].getdel( fin );

          if( -1 == kend ) 
          {
            cerr << "Ran out of TEM output data for " << predmap;
            cerr << " after grid cell " << reccount;
            cerr << " and cohort " << (icohort+1) << endl;
            
            exit( -1 );
          }

          if( ((startyr+dyr) > firstchrtyr)
              && (temdat[dyr].col != cohorts.col
              || temdat[dyr].row != cohorts.row
              || (1 == tlulcflag 
                  && temdat[dyr].year != cohorts.year)) )
          {
            cout << "MAXCOHRT file and TEMfile are not co-registered!" << endl;
            cout << " MAXCOHRT LON = " << cohorts.col;
            cout << " LAT = " << cohorts.row;
            cout << " Year = " << cohorts.year << endl;
            cout << " TEM LON = " << temdat[dyr].col;
            cout << " LAT = " << temdat[dyr].row;
            cout << " Year = " << temdat[dyr].year << endl;

            exit( -1 );
          }
     
  	  predmap = temdat[0].varname;

          if( 0 == potvflag )
          {
            pred.tveg = temdat[dyr].potveg;
          }
          else 
          {
            pred.tveg = temdat[dyr].currentveg;
          }

          if( pred.tveg <= 0 || pred.tveg >= MAXNVEG ) 
          { 
            pred.tveg = 0; 
          }

          pred.standage = temdat[dyr].standage;
          pred.agstate = temdat[dyr].agstate;
	  pred.carea = temdat[dyr].carea;
          pred.subarea = temdat[dyr].subarea;
	  pred.totyr = temdat[dyr].year;
	  pred.total = temdat[dyr].total;
	  pred.max = temdat[dyr].max;
	  pred.ave = temdat[dyr].ave;
	  pred.min = temdat[dyr].min;
	
	  for( dm = 0; dm < CYCLE; ++dm ) 
          {
            pred.mon[dm] = temdat[dyr].mon[dm];
          }

          pred.region = temdat[0].region;


          if( ("All" == covrage 
              || "all" == covrage
              || "ALL" == covrage
              || (0 == regionflag && pred.region == covrage)
              || (1 == regionflag && cohorts.region == covrage)) 
              && ( 99 == tststate
              || pred.agstate == tststate) )
          {
            aggregateData( period, pred, icohort ); 
          }
        }
      }
    }
      
    if( 0 == (reccount+1)%1000 ) 
    {
      cout << "Processed " << (reccount+1) << endl;
    }
  }

  switch( dataflg ) 
  { 
    case 0: fclose( fveg ); break;
    case 1: fclose( fchrt); break;
  }

  fclose( fin );


  // Determine statistics for each vegetation type

  for( dv = 0; dv < MAXNVEG; ++dv ) 
  {
    for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
    {
      if( summ[dv][dyr].totarea > 0 ) 
      {
        summ[dv][dyr].areawmean = summ[dv][dyr].outtot
                                  / summ[dv][dyr].totarea;
      }

      if( summ[dv][dyr].totgrid > 0 ) 
      {                            
  	summ[dv][dyr].simpmean = summ[dv][dyr].sumy
  	                         / summ[dv][dyr].totgrid;
	
	summ[dv][dyr].sumsqy = summ[dv][dyr].sumysq 
	                       - (pow( summ[dv][dyr].sumy, 2.0 )
	                       / summ[dv][dyr].totgrid);
	
	if( summ[dv][dyr].totgrid > 1 
	    && summ[dv][dyr].sumsqy > 0 )
        {
	  summ[dv][dyr].standev = pow( summ[dv][dyr].sumsqy/(summ[dv][dyr].totgrid - 1),
	                               0.5 );
        }
      }
    }
  }


  // Determine overall statistics for region
  
  for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
  {
    if( totsumm[dyr].totarea > 0 ) 
    {
      totsumm[dyr].areawmean = totsumm[dyr].outtot / 
                               totsumm[dyr].totarea;
    }
                               
    if( totsumm[dyr].totgrid > 0 ) 
    {
      totsumm[dyr].simpmean = totsumm[dyr].sumy 
                              / totsumm[dyr].totgrid;
                              
      totsumm[dyr].sumsqy = totsumm[dyr].sumysq 
                            - (pow( totsumm[dyr].sumy, 2.0 )
                            / totsumm[dyr].totgrid);
      if( totsumm[dyr].totgrid > 1 
          && totsumm[dyr].sumsqy > 0 )
      {
        totsumm[dyr].standev = pow( totsumm[dyr].sumsqy/(totsumm[dyr].totgrid - 1),
                                    0.5 );
      }
    }
  }

  for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
  {
    for( dv = 0; dv < MAXNVEG; ++dv ) 
    {
      summ[dv][dyr].outtot /= 1000000.0;
    }
    totsumm[dyr].outtot  /= 1000000.0;
  }

  // Output summary of region's statistics
  
  sumreport( fout );

  cout << "Sum report written" << endl;  

  fout.close();

  return 0;
  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void aggregateData( const string& period, 
                    const Season& pred,
                    const int& ichrt )
{
  int dv;
 
  if( 0 == ichrt ) 
  { 
    for( dv = 0; dv < MAXNVEG; ++dv )    
    {
      notegrd[dv] = REJECT; 
    }

    notetgrd = REJECT;
  }  
 
  qc = REJECT;

  if( startage <= pred.standage
      && lastage >= pred.standage )
  { 
    for( dv = 0; dv < numveg; ++dv ) 
    {
      if( pred.tveg == testveg[dv] ) { qc = ACCEPT; }
    }
  }

  loadpred( period );

  if( (predamnt <= missdata) 
      || (qc == REJECT) ) 
  {        
    summ[pred.tveg][pred.totyr-startyr].rejarea += pred.subarea;
    totsumm[pred.totyr-startyr].rejarea += pred.subarea;
  } 
  else 
  {
    if( pred.totyr <= 0 
         || pred.totyr >= equilyr 
         || qc == REJECT ) 
    {
      summ[pred.tveg][pred.totyr-startyr].rejarea += pred.subarea;
      totsumm[pred.totyr-startyr].rejarea += pred.subarea;
    } 
    else 
    {
      notegrd[pred.tveg] = ACCEPT;

      notetgrd = ACCEPT;
      
      summ[pred.tveg][pred.totyr-startyr].totarea += pred.subarea;
    
      if( 0 == summ[pred.tveg][pred.totyr-startyr].totgrid ) 
      {
        summ[pred.tveg][pred.totyr-startyr].outmax = predamnt;
        summ[pred.tveg][pred.totyr-startyr].outmin = predamnt;
      }
    
      if( summ[pred.tveg][pred.totyr-startyr].outmax < predamnt )
      {
        summ[pred.tveg][pred.totyr-startyr].outmax = predamnt;
      }
          
      if( summ[pred.tveg][pred.totyr-startyr].outmin > predamnt )
      {
        summ[pred.tveg][pred.totyr-startyr].outmin = predamnt;
      }

      summ[pred.tveg][pred.totyr-startyr].outtot += predamnt * pred.subarea;
      if( pred.carea > 0.1 )
      {
        summ[pred.tveg][pred.totyr-startyr].sumy += (predamnt * pred.subarea / pred.carea);
        summ[pred.tveg][pred.totyr-startyr].sumysq += pow( (predamnt * pred.subarea / pred.carea), 2.0 );
      }

      summ[pred.tveg][pred.totyr-startyr].sumtotyr += pred.totyr;

      totsumm[pred.totyr-startyr].totarea += pred.subarea;

      if( 0 == totsumm[pred.totyr-startyr].totgrid ) 
      {
        totsumm[pred.totyr-startyr].outmax = predamnt;
        totsumm[pred.totyr-startyr].outmin = predamnt;
      }

      if( totsumm[pred.totyr-startyr].outmax < predamnt ) 
      {
        totsumm[pred.totyr-startyr].outmax = predamnt;
      }
          
      if( totsumm[pred.totyr-startyr].outmin > predamnt ) 
      {
        totsumm[pred.totyr-startyr].outmin = predamnt;
      }

      totsumm[pred.totyr-startyr].outtot  += predamnt 
                                             * pred.subarea;
                                             
      if( pred.carea > 0.1 )
      {
        totsumm[pred.totyr-startyr].sumy += (predamnt * pred.subarea / pred.carea);
        totsumm[pred.totyr-startyr].sumysq += pow( (predamnt * pred.subarea / pred.carea), 2.0 );
      }

      totsumm[pred.totyr-startyr].sumtotyr += pred.totyr;
    }
  }

  if( (cohorts.total-1) == ichrt )
  {
    for( dv = 0; dv < MAXNVEG; ++dv )    
    {
      if( REJECT == notegrd[dv] )
      {
        summ[dv][pred.totyr-startyr].rejgrid += 1;
      }
      else
      {
        summ[dv][pred.totyr-startyr].totgrid += 1;
      }
    }

    if( REJECT == notetgrd )
    {
      totsumm[pred.totyr-startyr].rejgrid += 1;
    }
    else
    {
      totsumm[pred.totyr-startyr].totgrid += 1;
    }    
  }

  
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void chkunits( const int& dataflag, const string& predmap ) 
{

  if( 1 == dataflag ) 
  {
    totunits = "(gX10**12)";
    units = "g_C";

    if ( "CH4FLUX" == predmap   
         || "CH4EMISS" == predmap   
         || "CH4CNSMP" == predmap )
    {
      totunits = "(gX10**9)";
      units = "mg_C";
    }

    if ( "VSTRUCTN" == predmap   
         || "SOILORGN" == predmap   
         || "VEGN" == predmap )
    {
      totunits = "(gX10**12)";
      units = "g_N";
    }

    if ( "VSTOREN" == predmap  
         || "AVAILN" == predmap
         || "NETNMIN" == predmap 
         || "NLOST" == predmap 
         || "NINPUT" == predmap
         || "VEGNUP" == predmap 
         || "LTRN" == predmap
         || "MICRONUP" == predmap
         || "VNMOBIL" == predmap
         || "VNRESORB" == predmap
         || "VEGSUP" == predmap
         || "VEGLUP" == predmap
         || "N2OFLUX" == predmap )
    {
      totunits = "(gX10**9)";
      units = "mg_N";
    }
  }

};

/* *************************************************************
************************************************************* */

/* *************************************************************
************************************************************* */

void loadpred( const string& period ) 
{
  if( "ann" == period ) 
  { 
    predamnt = pred.total;
    pername = "Annual";
  }
  if( "max" == period ) 
  {
    predamnt = pred.max;
    pername = "Maximum";
  }
  if( "ave" == period ) 
  {
    predamnt = pred.ave;
    pername = "Mean";
    outprec = 2;
  }
  if( "min" == period ) 
  {
    predamnt = pred.min;
    pername = "Minimum";
  }
  if( "jan" == period ) 
  {
    predamnt = pred.mon[0];
    pername = "January";
  }
  if( "feb" == period ) 
  {
    predamnt = pred.mon[1];
    pername = "February";
  }
  if( "mar" == period ) 
  {
    predamnt = pred.mon[2];
    pername = "March";
  }
  if( "apr" == period ) 
  {
    predamnt = pred.mon[3];
    pername = "April";
  }
  if( "may" == period ) 
  {
    predamnt = pred.mon[4];
    pername = "May";
  }
  if( "jun" == period ) 
  {
    predamnt = pred.mon[5];
    pername = "June";
  }
  if( "jul" == period ) 
  {
    predamnt = pred.mon[6];
    pername = "July";
  }
  if( "aug" == period ) 
  {
    predamnt = pred.mon[7];
    pername = "August";
  }
  if( "sep" == period ) 
  {
    predamnt = pred.mon[8];
    pername = "September";
  }
  if( "oct" == period ) 
  {
    predamnt = pred.mon[9];
    pername = "October";
  }
  if( "nov" == period ) 
  {
    predamnt = pred.mon[10];
    pername = "November";
  }
  if( "dec" == period ) 
  {
    predamnt = pred.mon[11];
    pername = "December";
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void sumreport( ofstream& fout ) 
{

  int dyr;
  int dv;
  int j;
  double sumrej[MAXRTIME];
  double totrej[MAXRTIME];

  fout.setf( ios::fixed,ios::floatfield );
  fout.setf( ios::showpoint );
  fout.precision( 1 );

  switch( dataflg ) 
  {
    case 0: fout << endl << "                         ";
            fout << pername << " ";
            fout << predmap << " for ";
            fout << covragetxt << endl;
	    fout << endl << endl;
            fout << "Information on grids selected for analysis";
            fout << endl << endl;
	    fout << "EZ NGRID TOTCELLAREA TOTFORECOZONE MXPRED MNPRED MNBYAR SIMPMN STNDEV MNTOTYR" << endl;
	    fout << "         (10**6m**2) <------------ ";
            fout << setw(20) << clmunits << " ------------>  years";
            fout << endl << endl;
	    break;
    case 1: fout << endl << "CO2 = " << co2conc << " ppmv         ";
	    fout << pername << " ";
            fout << predmap << " for ";
            fout << covragetxt << "              ";
            fout << version << endl;
	    fout << cpuname << "         (";
            fout << soilfname << ",";
            fout << vegfname << ",";
            fout << elevfname << ",";
            fout << tairfname << ",";
            fout << precfname << ",";
            fout << cldifname << ")" << endl;
	    fout << setprecision(0) << rundate << endl;
	    fout << endl << endl;
            fout << "Information on grids selected for analysis";
            fout << endl << endl;
	    fout << "EZ, YEAR, NGRID, TOTCELLAREA, TOTFORECOZONE, MXPRED, MNPRED, MNBYAR, SIMPMN, STNDEV, MNTOTYR" << endl;
	    chkunits( dataflg,predmap );
	    fout << "                 (10**6m**2)    ";
            fout << setw(10) << totunits << "   <---   ";
            fout << setw(4) << units << " per m**2 (per year)    --->  years";
            fout << endl << endl;
  }

  for( dv = 0; dv < MAXNVEG; ++dv ) 
  {
    for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
    {
      qc = REJECT;

      for( j = 0; j < numveg; ++j ) 
      {
        if( dv == testveg[j] ) { qc = ACCEPT; }
      }

      if( qc == ACCEPT ) 
      {
        if( ((dyr + startyr) >= startoutyr) 
            && ((dyr + startyr) <= lastoutyr) )
        {
          fout << setprecision(0) << setw(2) << dv << ", ";
          fout << setprecision(1) << (dyr+startyr) << ", ";
          fout << setw(5) << summ[dv][dyr].totgrid << ", ";
          fout << setw(11) << summ[dv][dyr].totarea << ", ";
          fout << setprecision(3) << setw(13) << summ[dv][dyr].outtot << ", ";
          fout << setprecision( outprec );
          fout << setw(6) << summ[dv][dyr].outmax << ", ";
          fout << setw(6) << summ[dv][dyr].outmin << ", ";
          fout << setw(6) << summ[dv][dyr].areawmean << ", ";
          fout << setw(6) << summ[dv][dyr].simpmean << ", ";
          fout << setw(6) << summ[dv][dyr].standev << ", ";
          if( summ[dv][dyr].totgrid > 0 ) 
          {
            fout << setw(6) << summ[dv][dyr].sumtotyr/summ[dv][dyr].totgrid << endl;
          }
          else 
          {
            fout << setw(6) << summ[dv][dyr].sumtotyr << endl;
          }
        }
      }
    }
  }

  fout << endl;
  for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr )
  {
    if( ((dyr + startyr) >= startoutyr) 
        && ((dyr + startyr) <= lastoutyr) )
    {
      fout << "99, " << setprecision(1) << (dyr+startyr) << ", ";
      fout << setprecision(0) << setw(5) << totsumm[dyr].totgrid << ", ";
      fout << setw(11) << totsumm[dyr].totarea << ", ";
      fout << setprecision(3) << setw(13) << totsumm[dyr].outtot << ", ";
      fout << setprecision(outprec) << setw(6) << totsumm[dyr].outmax << ", ";
      fout << setw(6) << totsumm[dyr].outmin << ", ";
      fout << setw(6) << totsumm[dyr].areawmean << ", ";
      fout << setw(6) << totsumm[dyr].simpmean << ", ";
      fout << setw(6) << totsumm[dyr].standev << ", ";

      if(totsumm[dyr].totgrid > 0)
      { 
        fout << setw(6) << totsumm[dyr].sumtotyr/totsumm[dyr].totgrid << endl;
      }
      else
      {
        fout << setw(6) << totsumm[dyr].sumtotyr << endl;
      }
    }
  }

  fout << endl << endl << endl << endl;
  fout << "Information on grids rejected for analysis" << endl << endl;
  fout << "EZ, NGRID, TOTCELLAREA" << endl;
  fout << "           (10**6m**2)" << endl << endl;

  for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
  {
    sumrej[dyr] = 0.0;
    totrej[dyr] = 0.0;
  }

  for( dv = 0; dv < MAXNVEG; ++dv ) 
  {
    if( summ[dv][0].rejarea > 0 ) 
    {
      qc = REJECT;
      for( j = 0; j < numveg; ++j ) 
      {
        if( dv == testveg[j] ) { qc = ACCEPT; }
      }
      if( qc == ACCEPT ) 
      {
        for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
        {
          if( ((dyr + startyr) >= startoutyr) 
              && ((dyr + startyr) <= lastoutyr) )
          {
            sumrej[dyr] = summ[dv][dyr].rejarea * summ[dv][dyr].areawmean * 0.000001;
            fout << setprecision(0) << setw(2) << dv << ' ';
            fout << setw(5) << summ[dv][dyr].rejgrid << ' ';
            fout << setw(11) << summ[dv][dyr].rejarea << " x ";
            fout << setprecision( outprec ) << setw(6) << summ[dv][dyr].areawmean << " = ";
            fout << setprecision( 3 ) << setw( 13 ) << sumrej[dyr] << " (+ ";
            fout << summ[dv][dyr].outtot << " = ";
            fout << (sumrej[dyr] + summ[dv][dyr].outtot) << ")" << endl;
            totrej[dyr] += sumrej[dyr];
          }
        }
      } 
      else 
      {
        for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
        {
          if( ((dyr + startyr) >= startoutyr) 
              && ((dyr + startyr) <= lastoutyr))
          {
            fout << setprecision(0) << setw(2) << dv << ' ';
            fout << setw(5) << summ[dv][dyr].rejgrid << ' ';
            fout << setw(11) << summ[dv][dyr].rejarea << endl;
          }
        }
      }
    }
  }

  for( dyr = 0; dyr < (lastyr-startyr+1); ++dyr ) 
  {
    if( totsumm[dyr].rejarea > 0 )
    {
      if( ((dyr + startyr) >= startoutyr) 
          && ((dyr + startyr) <= lastoutyr) )
      {
        fout << endl << "99 " << setprecision(0) << setw(5) << totsumm[dyr].rejgrid << ' ';
        fout << setw(11) << totsumm[dyr].rejarea << "          = ";
        fout << setprecision(3) << setw(13) << totrej[dyr] << " (+ ";
        fout << totsumm[dyr].outtot << " = ";
        fout << (totrej[dyr] + totsumm[dyr].outtot) << ")" << endl;
      }
    }
  }

};

