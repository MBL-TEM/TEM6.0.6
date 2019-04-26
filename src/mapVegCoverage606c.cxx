/* *************************************************************
Program: MAPVEGCOVERAGE606C.CXX

Description: Program maps percent coverage of specified 
             vegetation types and/or age classes for a 
             specified time period or data in 
             TEM LCLUC data format
************************************************************** 

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

const int MAXNLON = 720;
const int MAXNLAT = 360;

#include "temconsts606.hpp"
#include "tmaxcohortdat605.h"
#include "lulcdat605.h"

enum mapkey { GLBVIEW, AKVIEW, RUSSIAVIEW };

MaxCohortdata60 cohorts;
Lulcdata60 lulcdat;

double relarea[MAXNLON][MAXNLAT];

long dgrd;
long maxgrid;  // number of grid in the file

int startyr;
int lastyr;
int outyr;
int startage;
int lastage;

// total number of years in the output file
int numyear;        

string predmap;
int tveg;
long carea;
long tstarea;

string pername;

FILE* fin;
FILE* fchrt;
ofstream fout;
ostringstream tempfname;
string tempname;
string statpor;

string totunits;
string units;

int main()
{
  string chrtfname;

  int dyr;

  ofstream flog1;

  int ichrt;
  string ifilename;
  int ilon;
  int ilat;

  int iveg;

  int kend;

  int minlon;
  int minlat;
  
  int maxlon;
  int maxlat;

  int mapview;

  int nveg;

  string ofilename;

  long totarea;

  int totlon;

  int tststate;

  long vegarea;

  int vegtype[MAXNVEG];

  flog1.open( "vegmap.log", ios::out );

   
  cout << "Enter the name of the maximum cohort file: ";
    
  cin >> chrtfname;

  fchrt = fopen( chrtfname.c_str(), "r" );

  if ( !fchrt ) 
  {
    cerr << endl << "Cannot open " << chrtfname;
    cerr << " for maximum cohort data input." << endl;

    exit( -1 );
  }


  cout << "Please enter the name of the input file ";
  cout << "file containing the LCLUC data: " << endl;

  cin >> ifilename;
    
  fin = fopen( ifilename.c_str(), "r" );

  if( !fin ) 
  {
    cerr << endl << "Cannot open " << ifilename;
    cerr << " for LCLUC data input." << endl;

    exit( -1 );
  }


  cout << "How many grid cells are in the data set?" << endl;
  
  cin >> maxgrid;


  cout << "Enter the first year in the input files: "; 
    
  cin >> startyr;
    
  cout << "Enter the last year in the input files: "; 
    
  cin >> lastyr;

  numyear = lastyr - startyr + 1;


  cout << "What is the year you want to map? " << endl;
     
  cin >> outyr;


  cout << "How many vegetatiun types do you want to map? " << endl;

  cin >> nveg;

  cout << "Please enter each vegetation type: " << endl;
  
  for( iveg = 0; iveg < nveg; ++iveg )
  {
    cout << endl << (iveg+1) << ": ";

    cin >> vegtype[iveg];
  }    


  cout << "What is the youngest stand age you want to consider? " << endl;
  cout << "  Enter 0 for all ages: " << endl;
  
  cin >> startage;


  cout << "What is the oldest stand age you want to consider? " << endl;
  cout << "  Enter 5000 for all ages: " << endl;
  
  cin >> lastage;


  cout << "What managed lands do you want to consider? " << endl;
  cout << "  Enter 99 for all managed lands including natural vegetation: " << endl;

  cin >> tststate;

  cout << " tststate = " << tststate << endl;


  cout << "What view of the region do you want to map?" << endl;
  cout << "Enter 0 for global view (-180.0 to 180.0 longitiude):" << endl;
  cout << "Enter 1 for Alaska view (-187.5 to 130.5 longitude):" << endl;
  cout << "Enter 2 for Russia view (4.5 to 190.0 longitude):" << endl;

  cin >> mapview;


  cout << "Enter the name of the output file:" << endl;
  
  cin >> ofilename;

  fout.open( ofilename.c_str(), ios::out );


  for ( ilon = 0; ilon < MAXNLON; ++ilon )
  {
    for ( ilat = 0; ilat < MAXNLAT; ++ilat )
    {    
      relarea[ilon][ilat] = MISSING;
    }
  }


  totarea = 0;
  
  for( dgrd = 0; dgrd < maxgrid; ++dgrd )
  {  
    for( dyr = 0; dyr < numyear; ++dyr )
    {
      kend = cohorts.getdel( fchrt );
    
      if( -1 == kend ) 
      {
        cerr << "Ran out of cohort data after grid cell ";
        cerr << dgrd << endl;

        exit( -1 );
      }

      switch( mapview )
      {
        case GLBVIEW:  totlon = 720;
                       break;

        case AKVIEW:  if( cohorts.col > 0.0 )
                      {
                        cohorts.col -= 360.0;
                      }
 
                      totlon = 750;
                      break;

        case RUSSIAVIEW: if( cohorts.col < 0.0 )
                         {
                           cohorts.col += 360.0;
                         }
                         totlon = -18;
                         break;
      }
          
      ilon = (int) round( (cohorts.col * 2.0) + (totlon * 0.5) );
      ilat = (int) round( ((MAXNLAT * 0.5) - (cohorts.row * 2.0) - 1) );

      if( 0 == dgrd ) 
      {
        minlon = ilon;
        minlat = ilat;
            
        maxlon = ilon;
        maxlat = ilat;
      }
                    
      if( ilon < minlon ) { minlon = ilon; }
      if( ilat < minlat ) { minlat = ilat; }
          
      if( ilon > maxlon ) { maxlon = ilon; }
      if( ilat > maxlat ) { maxlat = ilat; }
       

      vegarea = 0;
      
      for( ichrt = 0; ichrt < cohorts.total; ++ichrt )
      {
        kend = lulcdat.getdel( fin );

        if( kend != -1 )
        {            
          if ( outyr == lulcdat.year
               && startage <= lulcdat.standage 
               && lastage >= lulcdat.standage )
          {
            for( iveg = 0; iveg < nveg; ++iveg )
            {
              if( vegtype[iveg] == lulcdat.currentveg 
                  && ( 99 == tststate
                  || lulcdat.agstate == tststate) )
              {
                vegarea += lulcdat.chrtarea;
                totarea += lulcdat.chrtarea;
              }  
            }
          } 
        }
      }

      if( outyr == lulcdat.year && cohorts.carea > 0 )
      {
        relarea[ilon][ilat] =  (double) vegarea / (double) cohorts.carea;  
      }
    }
    
    if ( 0 == dgrd%1000 )
    {
      cout << "Accumulated data for " << dgrd << " grid cells!" << endl;
    }
  }

  cout << "Total area = " << totarea << " square kilometers" << endl;
 
  if( minlon > 5 ) { minlon -= 5; }
  else{ minlon = 0;}

  if( minlat > 5 ) { minlat -= 5; }
  else{ minlat = 0;}
  
  if( maxlon < (MAXNLON - 6) ) { maxlon += 5; }
  else{ maxlon = MAXNLON - 1;}

  if( maxlat < (MAXNLAT - 6) ) { maxlat += 5; }
  else{ maxlat = MAXNLAT - 1;}

  cout << "Creating gridded file for ARC/INFO" << endl;
  
  fout << "ncols " << (maxlon - minlon) << endl;
  fout << "nrows " << (maxlat - minlat) << endl;

  switch( mapview )
  {
       case GLBVIEW: fout << "xllcorner " << (-180.0 + (0.5 * minlon)) << endl;
                     break;

        case AKVIEW: fout << "xllcorner " << (-172.5 + (0.5 * minlon)) << endl;
                     break;

    case RUSSIAVIEW: fout << "xllcorner " << (4.5 + (0.5 * minlon)) << endl;
                     break;
  }
  
  fout << "yllcorner " << (90.0 - (0.5 * maxlat)) << endl;
  fout << "cellsize 0.5" << endl;
  fout << "nodata_value " << MISSING << endl;
    
  for( ilat = minlat; ilat < maxlat; ++ilat )
  {
    for( ilon = minlon; ilon < maxlon; ++ilon )
    {
      fout << relarea[ilon][ilat] << " ";
    }
    
    fout << endl;
  }


// Close files

  fclose( fchrt );
  fclose( fin );
  fout.close();
  
  flog1.close();
  
  return 0;
  
};


