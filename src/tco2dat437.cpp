/* *************************************************************
TCO2DAT437.CPP - object to read and write the structure of 
                   transient atmospheric CO2 data from/to files 
                   used by the Terrestrial Ecosystem Model (TEM)

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
  

#include "tco2dat437.h"


CO2data43::CO2data43( void )
{

  co2end = 1;
  lagpos = -99;
  curpos = 0;

};

/* *************************************************************
                    Public Functions
************************************************************* */

int CO2data43::get( ifstream& infile )
{

  lagpos = infile.tellg();

  infile >> year >> mco2;

  infile.seekg( 0, ios::cur );
  
  curpos = infile.tellg();

  if( curpos < (lagpos + 5) ) { co2end = -1; }

  return co2end;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int CO2data43::getdel( FILE* infile )
{

  co2end = fscanf( infile, "%f,%lf", &year, &mco2 );

  return co2end;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void CO2data43::out( ofstream& ofile, 
                     float& year, 
                     double& mco2 )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 1 );

  ofile << year << ' ';
  ofile << setprecision( 4 ) << mco2;
  ofile << endl;


};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void CO2data43::outdel( ofstream& ofile, 
                        float& year, 
                        double& mco2 )
{

  ofile.setf( ios::fixed,ios::floatfield );
  ofile.setf( ios::showpoint );
  ofile.precision( 1 );

  ofile << year << ",";
  ofile << setprecision( 4 ) << mco2;
  ofile << endl;

};

