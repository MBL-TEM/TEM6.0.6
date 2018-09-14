/* *************************************************************
TMAXCOHORTDAT605.CPP - object to read and write the structure 
                          of maximum number of cohort grid cell 
                          data from/to files used by the 
                          Terrestrial Ecosystem Model

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
  using std::cout;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<iomanip>

  using std::setprecision;

#include<string>

  using std::string;

#include "tmaxcohortdat605.h" 

/* *************************************************************
************************************************************* */

MaxCohortdata60::MaxCohortdata60( void )
{

  chrtend = 1;
  lagpos = -99;
  curpos = 0;

};

/* *************************************************************
************************************************************* */

int MaxCohortdata60::get( ifstream& infile )
{

  lagpos = infile.tellg();

  infile >> col;
  infile >> row;
  infile >> varname;
  infile >> carea;
  infile >> year;
  infile >> total;
  infile >> natchrts;
  infile >> region;

  infile.seekg( 0, ios::cur );
  
  curpos = infile.tellg();

  if( curpos < (lagpos + 10) ) { chrtend = -1; }

  return chrtend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int MaxCohortdata60::getdel( FILE* infile )
{
  char tmpvarname[40];
  char tmpregion[80];
  
//  cout << "infile = " << infile << endl;

  chrtend = fscanf( infile,"%lf,%lf, %s ,%ld,%d,%d,%d, %s",
                   &col, 
                   &row, 
                   tmpvarname, 
                   &carea,
                   &year, 
                   &total,
                   &natchrts, 
                   tmpregion );

  varname = tmpvarname;
  region = tmpregion;
  
  return chrtend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void MaxCohortdata60::out( ofstream& ofile, 
                           const double& col, 
                           const double& row, 
                           const string& varname, 
                           const long& carea,
                           const int& year,  
                           const int& total,
                           const int& natchrts, 
                           const string& region )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ' ';
  ofile << row << ' ';
  ofile << varname << ' ';
  ofile << setprecision( 0 ) << carea << ' ';
  ofile << setprecision( 0 ) << year << ' ';
  ofile << setprecision( 0 ) << total << ' ';
  ofile << setprecision( 0 ) << natchrts << ' ';
  ofile << region;
  ofile << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void MaxCohortdata60::outdel( ofstream& ofile, 
                              const double& col, 
                              const double& row, 
                              const string& varname, 
                              const long& carea,  
                              const int& year,
                              const int& total,
                              const int& natchrts, 
                              const string& region )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ",";
  ofile << row << ", ";
  ofile << varname << " ,";
  ofile << setprecision( 0 ) << carea << ",";
  ofile << setprecision( 0 ) << year << ",";
  ofile << setprecision( 0 ) << total << ",";
  ofile << setprecision( 0 ) << natchrts << ", ";
  ofile << region;
  ofile << endl;

};

