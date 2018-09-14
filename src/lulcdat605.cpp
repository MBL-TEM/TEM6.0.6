/* *************************************************************
LULCDAT605.CPP - object to read and write the structure of 
                   land use/land cover data from/to files

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>   

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
  

#include "lulcdat605.h"


Lulcdata60::Lulcdata60( void )
{

  lulcend = 1;
  lagpos = -99;
  curpos = 0;

};

/* **************************************************************
                    Public Functions
************************************************************** */

/* *************************************************************
************************************************************* */

int Lulcdata60::get( ifstream& infile )
{

  lagpos = infile.tellg();

  infile >> col;
  infile >> row;
  infile >> varname;
  infile >> year;
  infile >> icohort;
  infile >> isrccohort;
  infile >> standage;
  infile >> chrtarea;
  infile >> potveg;
  infile >> currentveg;
  infile >> subtype;
  infile >> agstate;
  infile >> agprevstate;
  infile >> tillflag;
  infile >> fertflag;
  infile >> irrgflag;
  infile >> disturbflag;
  infile >> disturbmonth;
  infile >> FRI;
  infile >> slashpar;
  infile >> vconvert;
  infile >> prod10par;
  infile >> prod100par;
  infile >> vrespar;
  infile >> sconvert;
  infile >> region;

  infile.seekg( 0, ios::cur );
  curpos = infile.tellg();

  if( curpos < (lagpos + 10) ) { lulcend = -1; }

  return lulcend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Lulcdata60::getdel( FILE* infile )
{
  char tmpvarname[40];
  char tmpregion[80];

  lulcend = fscanf( infile, 
                    "%lf,%lf, %s ,%d,%d,%d,%d,%ld,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf, %s",
                    &col, 
                    &row, 
                    tmpvarname,
                    &year,                   
                    &icohort,
                    &isrccohort,
                    &standage, 
                    &chrtarea, 
                    &potveg,
                    &currentveg,
                    &subtype,
                    &agstate, 
                    &agprevstate, 
                    &tillflag,
                    &fertflag,
                    &irrgflag,
                    &disturbflag,
                    &disturbmonth, 
                    &FRI, 
                    &slashpar, 
                    &vconvert,
                    &prod10par, 
                    &prod100par, 
                    &vrespar, 
                    &sconvert,
                    tmpregion );

  
  varname = tmpvarname;
  region = tmpregion;
 
 
  return lulcend;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Lulcdata60::out( ofstream& ofile,  
                      const double& col, 
                      const double& row, 
                      const string& varname,
                      const int& year,
                      const int& icohort,
                      const int& isrccohort,
                      const int& standage, 
                      const long& chrtarea, 
                      const int& potveg,
                      const int& currentveg, 
                      const int& subtype,
                      const int& agstate, 
                      const int& agprevstate, 
                      const int& tillflag, 
                      const int& fertflag, 
                      const int& irrgflag, 
                      const int& disturbflag,
                      const int& disturbmonth,
                      const int& FRI, 
                      const double& slashpar, 
                      const double& vconvert,
                      const double& prod10par, 
                      const double& prod100par, 
                      const double& vrespar, 
                      const double& sconvert,
                      const string& region )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ' ';
  ofile << row << ' ';
  ofile << varname << ' ';
  ofile << year << ' ';
  ofile << icohort << ' ';
  ofile << isrccohort << ' ';
  ofile << standage << ' ';
  ofile << chrtarea << ' ';
  ofile << potveg << ' ';
  ofile << currentveg << ' ';
  ofile << subtype << ' ';
  ofile << agstate << ' ';
  ofile << agprevstate << ' ';
  ofile << tillflag << ' ';
  ofile << fertflag << ' ';
  ofile << irrgflag << ' ';
  ofile << disturbflag << ' ';
  ofile << disturbmonth << ' ';
  ofile << FRI << ' ';
  ofile << setprecision( 3 ) << slashpar << ' ';
  ofile << setprecision( 3 ) << vconvert << ' ';
  ofile << setprecision( 3 ) << prod10par << ' ';
  ofile << setprecision( 3 ) << prod100par << ' ';
  ofile << setprecision( 3 ) << vrespar << ' ';
  ofile << setprecision( 3 ) << sconvert << ' ';
  ofile << region;
  ofile << endl;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Lulcdata60::outdel( ofstream& ofile, 
                         const double& col, 
                         const double& row, 
                         const string& varname,
                         const int& year,
                         const int& icohort,
                         const int& isrccohort,
                         const int& standage, 
                         const long& chrtarea, 
                         const int& potveg,
                         const int& currentveg,
                         const int& subtype, 
                         const int& agstate, 
                         const int& agprevstate, 
                         const int& tillflag, 
                         const int& fertflag, 
                         const int& irrgflag, 
                         const int& disturbflag,
                         const int& disturbmonth,
                         const int& FRI,  
                         const double& slashpar, 
                         const double& vconvert,
                         const double& prod10par, 
                         const double& prod100par, 
                         const double& vrespar, 
                         const double& sconvert,
                         const string& region )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 4 );

  ofile << col << ",";
  ofile << row << ", ";
  ofile << varname << " ,";
  ofile << year << ",";
  ofile << icohort << ",";
  ofile << isrccohort << ",";
  ofile << standage << ",";
  ofile << chrtarea << ",";
  ofile << potveg << ",";
  ofile << currentveg << ",";
  ofile << subtype << ",";
  ofile << agstate << ",";
  ofile << agprevstate << ",";
  ofile << tillflag << ",";
  ofile << fertflag << ",";
  ofile << irrgflag << ",";
  ofile << disturbflag << ",";
  ofile << disturbmonth << ",";
  ofile << FRI << ",";
  ofile << setprecision( 3 ) << slashpar << ",";
  ofile << setprecision( 3 ) << vconvert << ",";
  ofile << setprecision( 3 ) << prod10par << ",";
  ofile << setprecision( 3 ) << prod100par << ",";
  ofile << setprecision( 3 ) << vrespar << ",";
  ofile << setprecision( 3 ) << sconvert << ", ";
  ofile << region;
  ofile << endl;

};

