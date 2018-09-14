/* *************************************************************
TCLMDAT606.CPP - object to read and write the structure of the
                climate data from files used by the Terrestrial
                Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

****************************************************************
************************************************************* */

#include<cstdio>

  using std::fscanf;
  using std::FILE;

#include<iostream>

  using std::ios;
  using std::endl;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<iomanip>

  using std::setprecision;

#include<string>

  using std::string;
  

#include "tclmdat606.h"

Clmdata60::Clmdata60( void )
{

  clmend = 1;
  lagpos = -99;
  curpos = 0;

};

/* *************************************************************
************************************************************* */

int Clmdata60::get( ifstream& ifile )
{

  int dm;
  
  lagpos = ifile.tellg();

  ifile >> col;
  ifile >> row;
  ifile >> varname;
  ifile >> carea;
  ifile >> year;

  ifile >> total;
  ifile >> max;
  ifile >> ave;
  ifile >> min;

  for( dm = 0; dm < (CYCLE+1); ++dm ) { ifile >> mon[dm]; }

  ifile >> region;

  ifile.seekg( 0, ios::cur );
  
  curpos = ifile.tellg();

  if( curpos < (lagpos + 10) ) { clmend = -1; }

  return clmend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Clmdata60::getdel( FILE* ifile )
{

  char tempvarname[40];
  char tempregion[80];

  clmend = fscanf( ifile, 
                   "%lf,%lf, %s ,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf, %s",
                   &col, 
                   &row, 
                   tempvarname, 
                   &carea, 
                   &year, 
                   &total, 
                   &max, 
                   &ave, 
                   &min,
                   mon+0, 
                   mon+1, 
                   mon+2, 
                   mon+3, 
                   mon+4, 
                   mon+5,
                   mon+6, 
                   mon+7, 
                   mon+8, 
                   mon+9, 
                   mon+10, 
                   mon+11,
                   mon+12, 
                   tempregion );

  varname = tempvarname;
  region = tempregion;

  return clmend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Clmdata60::out( ofstream& ofile, 
                     const double& col, 
                     const double& row, 
                     const string& varname,
                     const int& carea, 
                     const int& year, 
                     double mon[CYCLE+1], 
                     const string& region )
{

  int dm;
  double predtotl;
  double predmax;
  double predave;
  double predmin;

  predtotl = 0.0;
  predmax   = -900000.0;
  predmin   =  900000.0;

  for( dm = 0; dm < CYCLE; ++dm ) 
  {
    if( mon[dm] > predmax ) { predmax = mon[dm]; }
    
    if( mon[dm] < predmin ) { predmin = mon[dm]; }
    
    predtotl += mon[dm];
  }

  predave = predtotl / (double) CYCLE;
  
  if(predtotl <= (MISSING*CYCLE)) { predtotl = MISSING; }

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ' ';
  ofile << setprecision( 4 ) << row << ' ';
  ofile << varname << ' ';
  ofile << setprecision( 0 ) << carea << ' ';
  ofile << setprecision( 0 ) << year << ' ';

  ofile << setprecision( 1 ) << predtotl << ' ';
  ofile << setprecision( 1 ) << predmax << ' ';
  ofile << setprecision( 2 ) << predave << ' ';
  ofile << setprecision( 1 ) << predmin << ' ';

  for( dm = 0; dm < (CYCLE+1); ++dm )  
  { 
    ofile << setprecision( 1 ) << mon[dm] << ' '; 
  }

  ofile << region << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Clmdata60::outdel( ofstream& ofile, 
                        const double& col, 
                        const double& row, 
                        const string& varname,
                        const int& carea, 
                        const int& year, 
                        double mon[CYCLE+1], 
                        const string& region )
{

  int dm;
  double predtotl;
  double predmax;
  double predave;
  double predmin;

  predtotl = 0.0;
  predmax   = -900000.0;
  predmin   =  900000.0;

  for( dm = 0; dm < CYCLE; ++dm ) 
  {
    if( mon[dm] > predmax ) { predmax = mon[dm]; }
    
    if( mon[dm] < predmin ) { predmin = mon[dm]; }
    
    predtotl += mon[dm];
  }

  predave = predtotl / (double) CYCLE;
  
  if( predtotl <= (MISSING*CYCLE) ) { predtotl = MISSING; }

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ",";
  ofile << setprecision( 4 ) << row << ", ";
  ofile << varname << " ,";
  ofile << setprecision( 0 ) << carea << ",";
  ofile << setprecision( 0 ) << year << ",";
  ofile << setprecision( 1 ) << predtotl << ",";
  ofile << setprecision( 1 ) << predmax << ",";
  ofile << setprecision( 2 ) << predave << ",";
  ofile << setprecision( 1 ) << predmin << ",";

  for( dm = 0; dm < (CYCLE+1); ++dm )  
  { 
    ofile << setprecision( 1 ) << mon[dm] << ","; 
  }

  ofile << " " << region;
  ofile << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Clmdata60::pctout( ofstream& ofile, 
                        const double& col, 
                        const double& row, 
                        const string& varname,
                        const int& carea, 
                        const int& year, 
                        double mon[CYCLE+1], 
                        const string& region )
{

  int dm;
  double predtotl;
  double predmax;
  double predave;
  double predmin;

  predtotl = 0.0;
  predmax   = -900000.0;
  predmin   =  900000.0;

  for( dm = 0; dm < CYCLE; ++dm ) 
  {
    if( mon[dm] > predmax ) { predmax = mon[dm]; }
    
    if( mon[dm] < predmin ) { predmin = mon[dm]; }
    
    predtotl += mon[dm];
  }

  predave = predtotl / (double) CYCLE;
  
  if( predtotl <= (MISSING*CYCLE) ) { predtotl = MISSING; }

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ' ';
  ofile << setprecision( 4 ) << row << ' ';
  ofile << varname << ' ';
  ofile << setprecision( 0 ) << carea << ' ';
  ofile << setprecision( 0 ) << year << ' ';

  ofile << setprecision( 2 ) << predtotl << ' ';
  ofile << setprecision( 2 ) << predmax << ' ';
  ofile << setprecision( 2 ) << predave << ' ';
  ofile << setprecision( 2 ) << predmin << ' ';

  for( dm = 0; dm < (CYCLE+1); ++dm )  
  { 
    ofile << setprecision( 2 ) << mon[dm] << ' '; 
  }

  ofile << region;
  ofile << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Clmdata60::poutdel( ofstream& ofile, 
                         const double& col, 
                         const double& row, 
                         const string& varname,
                         const int& carea, 
                         const int& year, 
                         double mon[CYCLE+1], 
                         const string& region )
{

  int dm;
  double predtotl;
  double predmax;
  double predave;
  double predmin;

  predtotl = 0.0;
  predmax   = -900000.0;
  predmin   =  900000.0;

  for( dm = 0; dm < CYCLE; ++dm ) 
  {
    if( mon[dm] > predmax ) { predmax = mon[dm]; }
    
    if( mon[dm] < predmin ) { predmin = mon[dm]; }
    
    predtotl += mon[dm];
  }

  predave = predtotl / (double) CYCLE;
  
  if( predtotl <= (MISSING*CYCLE) ) { predtotl = MISSING; }

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ",";
  ofile << setprecision( 4 ) << row << ", ";
  ofile << varname << " ,";
  ofile << setprecision( 0 ) << carea << ",";
  ofile << setprecision( 0 ) << year << ",";

  ofile << setprecision( 2 ) << predtotl << ",";
  ofile << setprecision( 2 ) << predmax << ",";
  ofile << setprecision( 2 ) << predave << ",";
  ofile << setprecision( 2 ) << predmin << ",";

  for( dm = 0; dm < (CYCLE+1); ++dm ) 
  { 
    ofile << setprecision( 2 ) << mon[dm] << ","; 
  }

  ofile << " " << region;
  ofile << endl;

};
