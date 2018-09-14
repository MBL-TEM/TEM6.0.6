/* *************************************************************
TSOLDAT606.H - object to read and write the structure of soil
               texture data from/to files used by the  
               Terrestrial Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

************************************************************* */

#ifndef TSOLDAT606_H
#define TSOLDAT606_H

class Soildata60
{
  
  public:
	 
     Soildata60( void );

/* *************************************************************
		    Public Functions
************************************************************* */
     
     int get( ifstream& infile );
     
     int getdel( FILE* infile );
     
     void out( ofstream& ofile, 
               const double& col, 
               const double& row, 
               const string& varname, 
               const long& carea, 
               const double& pctsand, 
               const double& pctsilt, 
               const double& pctclay,  
               const string& region );
     
     void outdel( ofstream& ofile, 
                  const double& col, 
                  const double& row, 
                  const string& varname, 
                  const long& carea, 
                  const double& pctsand, 
                  const double& pctsilt, 
                  const double& pctclay,  
                  const string& region );

/* *************************************************************
		     Public Variables
************************************************************* */

     // column or longitude of grid cell (degrees)	 
     double col;           
     
     // row or latitude of grid cell (degrees)
     double row;           
     
     // "TEXTURE"
     string varname;
     
     // area covered by grid cell (sq. km)     
     long carea;
     
     // percent sand of grid cell's soil texture           
     double pctsand;      
     
     // percent silt of grid cell's soil texture
     double pctsilt;      
     
     // percent clay of grid cell's soil texture
     double pctclay;      
     
     // name of region containing grid cell      
     string region;    


  private:

/* *************************************************************
		      Private Variables
************************************************************* */

     int soilend;
     long curpos;
     long lagpos;

};

#endif

