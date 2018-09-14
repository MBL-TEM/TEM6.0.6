/* *************************************************************
TELVDAT605.CPP - object to read and write the structure of 
                 elevation data from/to files used by the Water 
                 Balance Model

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
  

#include "telvdat605.h"



Elevdata60::Elevdata60( void )
{

  elvend = 1;
  lagpos = -99;
  curpos = 0;

};

/* *************************************************************
************************************************************* */

int Elevdata60::get( ifstream& infile )
{

  lagpos = infile.tellg();

  infile >> col;
  infile >> row;
  infile >> varname;
  infile >> carea;
  infile >> elev;
  infile >> region;

  infile.seekg( 0, ios::cur );
  
  curpos = infile.tellg();

  if( curpos < (lagpos + 10) ) { elvend = -1; }

  return elvend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Elevdata60::getdel( FILE* infile )
{
  char tmpvarname[40];
  char tmpregion[80];
  
  elvend = fscanf( infile,
                   "%lf,%lf, %s ,%ld,%lf, %s",
                   &col,
                   &row,
                   tmpvarname,
                   &carea,
                   &elev,
                   tmpregion );

  varname = tmpvarname;
  region = tmpregion;

  return elvend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Elevdata60::out( ofstream& ofile, 
                      const double& col, 
                      const double& row, 
                      const string& varname,
                      const long& carea, 
                      const double& elev, 
                      const string& region )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ' ';
  ofile << row << ' ';
  ofile << varname << ' ';
  ofile << setprecision( 0 ) << carea << ' ';
  ofile << setprecision( 1 ) << elev << ' ';
  ofile << region;
  ofile << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Elevdata60::outdel( ofstream& ofile, 
                         const double& col, 
                         const double& row, 
                         const string& varname,
                         const long& carea, 
                         const double& elev, 
                         const string& region )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ",";
  ofile << row << ", ";
  ofile << varname << " ,";
  ofile << setprecision( 0 ) << carea << ",";
  ofile << setprecision( 1 ) << elev << ", ";
  ofile << region;
  ofile << endl;

};

