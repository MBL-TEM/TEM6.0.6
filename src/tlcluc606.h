/* *************************************************************
****************************************************************
TLCLUC606.H - determines both potential and "actual" land
               cover, and identifies land uses within a grid
               cell

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
                                                                
****************************************************************
************************************************************* */

#ifndef TLCLUC606_H
#define TLCLUC606_H

const int MXFRF = 2000;

// TEMlcluc60 uses the MaxCohortdata60 class
#include "tmaxcohortdat605.h" 

// TEMlcluc60 uses the LULCdata60 class
#include "lulcdat605.h"    

// TEMlcluc60 inherits the Biome60 class
#include "tbiome606.h"    

class TEMlcluc60 : public Biome60
{

  public:

     TEMlcluc60();

 /* ************************************************************
		 Public Functions
************************************************************* */

     int getCohort( FILE* flulc );
     
     int getNumberOfCohorts( FILE* fnchrts );

     void initCohorts( ofstream& rflog1 );
     
     void initMaxCohorts( ofstream& rflog1 );

     void setLCLUCFlags( ofstream& rflog1, const int& requil );


/* *************************************************************
		 Public Variables
************************************************************* */

     int agcmnt;

     MaxCohortdata60 cohorts;

     int currentveg;
     
     int endyr;
    
     FILE* ifnumcohrts;

     FILE* iflulc;

     string ilulcend;
     string ilulcfname;

     string imxcohrtend;
     string imxcohrtfname;
     
     int lastyr;

     Lulcdata60 lulc;

     int maxtype;

     int potveg;
 
     int startyr;
     
     // portion of carea in a particular cohort, km^2
     long subarea;

     int tlulcflag;

};

#endif
