/* *************************************************************
TCLMDAT606.H - object to read and write the structure of the
                climate data from files used by the Terrestrial
                Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>    
                    
************************************************************* */

#ifndef TCLMDAT606_H
#define TCLMDAT606_H

#include "temconsts606.hpp"

class Clmdata60 
{
  
  public:
    
     Clmdata60( void );

/* *************************************************************
		      Public Functions
************************************************************* */

     // read data structure.
     
     int get( ifstream& ifile );
     int getdel( FILE* ifile );
     
     //write data structure.
     
     void out( ofstream& ofile, 
               const double& col, 
               const double& row, 
               const string& varname, 
               const int& carea, 
               const int& year, 
               double mon[CYCLE+1], 
               const string& region );
               
     void outdel( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const int& carea, 
                  const int& year, 
                  double mon[CYCLE+1], 
                  const string& region );
                  
     void pctout( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const int& carea, 
                  const int& year, 
                  double mon[CYCLE+1], 
                  const string& region );
                  
     void poutdel( ofstream& ofile, 
                   const double& col, 
                   const double& row, 
                   const string& varname, 
                   const int& carea, 
                   const int& year, 
                   double mon[CYCLE+1], 
                   const string& region );


/* *************************************************************
		     Public Variables
************************************************************* */

     // column or longitude of grid cell (degrees)	  
     double col;          

     // row or latitude of grid cell (degrees)
     double row;          
 
     // climate variable name
     string varname;     

     // area covered by grid cell (sq. km)
     int carea;          

      // date (year) of data
     long year;         

     // annual sum of monthly data for grid cell
     double total;       

      // maximum monthly value for grid cell
     double max;        

     // mean annual value for grid cell
     double ave;         

     // minimum monthly value for grid cell
     double min;         

     // monthly values for the grid cell
     double mon[CYCLE+1];  

      // name of region containing grid cell
     string region;   


  private:

/* *************************************************************
		      Private Variables
************************************************************* */

     int clmend;
     long curpos;
     long lagpos;

};

#endif
