/* *************************************************************
TELVDAT605.H - object to read and write the structure of 
               elevation data from/to files used by the Water 
               Balance Model

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

****************************************************************
************************************************************* */

#ifndef TELVDAT605_H
#define TELVDAT605_H

class Elevdata60 
{
   
  public:
          
     Elevdata60( void );

/* *************************************************************
                      Public Functions
************************************************************* */

     // read data structure.
     int get( ifstream& infile );
     
     int getdel( FILE* infile );

     //write data structure.
     void out( ofstream& ofile, 
               const double& col, 
               const double& row, 
               const string& varname, 
               const long& carea, 
               const double& elev, 
               const string& region );
     
     void outdel( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const long& carea, 
                  const double& elev, 
                  const string& region );

          
/* *************************************************************
                     Public Variables
************************************************************* */

     // column or longitude of grid cell (degrees)
     double col;          
     
     // row or latitude of grid cell (degrees)
     double row;          
     
     // "ELEV"
     string varname;
     
     // area covered by grid cell (sq. km)    
     long carea;          
     
     // elevation of grid cell (m)
     double elev;        
     
     // name of region containing grid cell
     string region;   


  private:

/* *************************************************************
                      Private Variables
************************************************************* */

     int elvend;
     long curpos;
     long lagpos;

};

#endif

