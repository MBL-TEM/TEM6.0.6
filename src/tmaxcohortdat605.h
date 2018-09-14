/* *************************************************************
TMAXCOHORTDAT605.H - object to read and write the structure of 
                       maximum number of cohorts grid cell data 
                       from/to files used by the 
                       Terrestrial Ecosystem Model

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  
                                 
****************************************************************
************************************************************* */

#ifndef TMAXCOHORTDAT605_H
#define TMAXCOHORTDAT605_H

class MaxCohortdata60 
{
   
  public:
          
     MaxCohortdata60( void );

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
               const int& year,  
               const int& total,
               const int& natchrts,
               const string& region );
               
     void outdel( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const long& carea,
                  const int& year,  
                  const int& total,
                  const int& natchrts, 
                  const string& region );

          
/* *************************************************************
                     Public Variables
************************************************************* */

     // area covered by grid cell (sq. km)
     long carea;          

     // column or longitude of grid cell (degrees)
     double col;          
     
     // number of cohorts representing the 
     //   original (or potential) vegetation 
     //   in a grid cell
     int natchrts;

     // name of region containing grid cell      
     string region;   

     // row or latitude of grid cell (degrees)
     double row;               
     
     // total number of cohorts in a grid cell
     int total;    
     
     // "MAXNCHRT"
     string varname;    

     // date represented by data
     int year; 

  private:

/* *************************************************************
                      Private Variables
************************************************************* */

     int chrtend;
     long curpos;
     long lagpos;

};

#endif

