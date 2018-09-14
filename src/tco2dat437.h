/* **************************************************************
TCO2DAT437.H - object to read and write the structure of 
                  transient CO2 data from/to files used by the
	          Terrestrial Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

************************************************************** */

#ifndef TCO2DAT437_H
#define TCO2DAT437_H

class CO2data43 
{
   
  public:
      
     CO2data43( void );
     
/* **************************************************************
		    Public Functions
************************************************************** */
     
     int get( ifstream& ifile );
     int getdel( FILE* infile );
     void out( ofstream& ofile, float& year, double& bco2 );
     void outdel( ofstream& ofile, float& year, double& bco2 );

/* **************************************************************
		     Public Variables
************************************************************** */
	  
     float year;

     // atmospheric CO2 concentration in July (ppmv)
     double mco2;        


  private:

/* **************************************************************
		      Private Variables
************************************************************** */

     int co2end;
     long curpos;
     long lagpos;


};

#endif

