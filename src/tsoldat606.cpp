/* *************************************************************
TSOLDAT606.CPP - object to read and write the structure of soil
                texture data from/to files used by the  
                the Terrestrial Ecosystem Model (TEM)

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
  

#include "tsoldat606.h"



Soildata60::Soildata60( void )
{

  soilend = 1;
  lagpos = -99;
  curpos = 0;

};

/* *************************************************************
************************************************************* */

int Soildata60::get( ifstream& infile )
{

  lagpos = infile.tellg();

  infile >> col;
  infile >> row;
  infile >> varname;
  infile >> carea;
  infile >> pctsand;
  infile >> pctsilt;
  infile >> pctclay;
  infile >> region;

  infile.seekg( 0, ios::cur );
  
  curpos = infile.tellg();

  if ( curpos < (lagpos + 10) ) { soilend = -1; }

  return soilend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Soildata60::getdel( FILE* infile )
{
  char tmpvarname[40];
  char tmpregion[80];
  
  soilend = fscanf( infile,
                    "%lf,%lf, %s ,%ld,%lf,%lf,%lf, %s ",
                    &col,
                    &row,
                    tmpvarname,
                    &carea,
                    &pctsand,
                    &pctsilt,
                    &pctclay,
                    tmpregion );
  
  varname = tmpvarname;
  region = tmpregion;
  
  return soilend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Soildata60::out( ofstream& ofile, 
                      const double& col, 
                      const double& row, 
                      const string& varname,
                      const long& carea, 
                      const double& pctsand, 
                      const double& pctsilt, 
                      const double& pctclay,
                      const string& region )
{

   ofile.setf( ios::fixed,ios::floatfield );
   ofile.setf( ios::showpoint );
   ofile.precision( 4 );

  ofile << col << ' ';
  ofile << row << ' ';
  ofile << varname << ' ';
  ofile << setprecision( 0 ) << carea << ' ';
  ofile << setprecision( 2 ) << pctsand << ' ';
  ofile << pctsilt << ' ';
  ofile << pctclay << ' ';
  ofile << region;
  ofile << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Soildata60::outdel( ofstream& ofile, 
                         const double& col, 
                         const double& row, 
                         const string& varname,
                         const long& carea, 
                         const double& pctsand, 
                         const double& pctsilt, 
                         const double& pctclay, 
                         const string& region )
{

   ofile.setf( ios::fixed,ios::floatfield );
   ofile.setf( ios::showpoint );
   ofile.precision( 4 );

  ofile << col << ",";
  ofile << row << ", ";
  ofile << varname << " ,";
  ofile << setprecision( 0 ) << carea << ",";
  ofile << setprecision( 2 ) << pctsand << ",";
  ofile << pctsilt << ",";
  ofile << pctclay << ", ";
  ofile << region;
  ofile << endl;

};

