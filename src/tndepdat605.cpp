/* *************************************************************
TNDEPDAT605.CPP - object to read and write the structure of the
                N deposition data from files used by the 
                Terrestrial Ecosystem Model (TEM)

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
  

#include "tndepdat605.h"

Ndepdata60::Ndepdata60( void )
{

  ndepend = 1;
  lagpos = -99;
  curpos = 0;

};

/* **************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

int Ndepdata60::get( ifstream& ifile )
{

  lagpos = ifile.tellg();

  ifile >> col;
  ifile >> row;
  ifile >> varname;
  ifile >> carea;
  ifile >> year;

  ifile >> nhx;
  ifile >> noy;
  ifile >> totndep;

  ifile >> region;

  ifile.seekg( 0, ios::cur );
  
  curpos = ifile.tellg();

  if(curpos < (lagpos + 10)) { ndepend = -1; }

  return ndepend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Ndepdata60::getdel( FILE* ifile )
{
  char tmpvarname[40];
  char tmpregion[80];
  
  ndepend = fscanf( ifile, 
                    "%lf,%lf, %s ,%d,%d,%lf,%lf,%lf,%s",
                    &col, 
                    &row, 
                    tmpvarname, 
                    &carea, 
                    &year, 
                    &nhx, 
                    &noy, 
                    &totndep, 
                    tmpregion );

  varname = tmpvarname;
  region = tmpregion;
  
  return ndepend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Ndepdata60::out( ofstream& ofile, 
                      const double& col, 
                      const double& row, 
                      const string& varname, 
                      const long& carea, 
                      const int& year, 
                      const double& nhx, 
                      const double& noy, 
                      const double& totndep, 
                      const string& region )

{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ' ';
  ofile << row << ' ';
  ofile << varname << ' ';
  ofile << setprecision( 0 ) << carea << ' ';
  ofile << year << ' ';

  ofile << setprecision( 5 ) << nhx << ' ';
  ofile << setprecision( 5 ) << noy << ' ';
  ofile << setprecision( 5 ) << totndep << ' ';

  ofile << region << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Ndepdata60::outdel( ofstream& ofile, 
                         const double& col, 
                         const double& row, 
                         const string& varname, 
                         const long& carea, 
                         const int& year, 
                         const double& nhx, 
                         const double& noy, 
                         const double& totndep, 
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
  ofile << setprecision( 5 ) << nhx << ",";
  ofile << setprecision( 5 ) << noy << ",";
  ofile << setprecision( 5 ) << totndep << ",";

  ofile << " " << region;
  ofile << endl;

};



