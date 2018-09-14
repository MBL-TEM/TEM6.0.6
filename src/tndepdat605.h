/* *************************************************************
TNDEPDAT605.H - object to read and write the structure of the
                annual N deposition data from files used by the 
                Terrestrial Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

************************************************************* */

#ifndef TNDEPDAT605_H
#define TNDEPDAT605_H

class Ndepdata60 
{
  
  public:
    
     Ndepdata60( void );

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
               const long& carea, 
               const int& year, 
               const double& nhx, 
               const double& noy, 
               const double& totndep, 
               const string& region );
               
     void outdel( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const long& carea, 
                  const int& year, 
                  const double& nhx, 
                  const double& noy, 
                  const double& totndep, 
                  const string& region );


/* *************************************************************
		     Public Variables
************************************************************* */
  
     // column or longitude of grid cell (degrees)
     double col;          

     // row or latitude of grid cell (degrees)
     double row;          

     // Variable name - i.e. NDEP
     string varname;    
     
     // area covered by grid cell (sq. km)
     long carea;          
     
     // date (year) of data
     int year;          
     
      // annual NHx deposition (mg N m-2 yr-1)
     double nhx;        
     
     // annual NOy deposition (mg N m-2 yr-1)
     double noy;         
     
     // annual total N deposition (mg N m-2 yr-1)
     double totndep;     
     
     // name of region containing grid cell
     string region;   


  private:

/* *************************************************************
		      Private Variables
************************************************************* */

     int ndepend;
     long curpos;
     long lagpos;

};

#endif
