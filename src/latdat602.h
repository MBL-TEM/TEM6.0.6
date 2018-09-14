/* **************************************************************
LATDAT602.H - object to read and write the structure of latitude
               and longitude data from/to files

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

************************************************************** */

#ifndef LATDAT602_H
#define LATDAT602_H

class Latdata60
{

  public:

     Latdata60( void );

/* **************************************************************
                      Public Functions
************************************************************** */

// read data structure.
     int get( ifstream& infile );
     
     int getdel( FILE* infile );

//write data structure.

     void out( ofstream& ofile, 
               const double& col, 
               const double& row, 
               const string& varname, 
               const double& lat, 
               const double& lon, 
               const string& contnent );

     void outdel( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const double& lat, 
                  const double& lon, 
                  const string& contnent );


/* **************************************************************
                     Public Variables
************************************************************** */

     double col;        // column of grid cell
     double row;        // row or of grid cell
     string varname;    // "LATITUDE?"
     double lat;        // latitude of grid cell (degrees)
     double lon;        // longitude of grid cell (degrees)
     string contnent;   // name of continent containing grid cell


  private:

/* **************************************************************
                      Private Variables
************************************************************** */

     int latend;
     long curpos;
     long lagpos;

};

#endif

