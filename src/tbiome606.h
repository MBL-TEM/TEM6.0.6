/* *************************************************************
****************************************************************
TBIOME606.H - object describing general characteristics of
             vegetation mosaic used in the Terrestrial Ecosystem
             Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
                                            
****************************************************************
************************************************************* */

#ifndef TBIOME606_H
#define TBIOME606_H

#include "temconsts606.hpp"
#include "tprocessXML606.h"


class Biome60 : public ProcessXML60
{

  public:

     Biome60( void );

 /* ************************************************************
		 Public Functions
************************************************************* */

     int   getCommunityType( const int& tveg );
     
     int   getVegMosaic( const int& tveg );
     
     double getVegSubarea( const int& tveg,
                           const int& dmsac,
                           const int& carea );
     
      int   getVegSubtype( const int& tveg, const int& dmsac );
     
     void   getvtype( ofstream& rflog1 );
     
     void   getvtype( const string& ecd );

     double getWFPSOFF( const int& tveg );

/* *************************************************************
		 Public Variables
************************************************************* */

     // vegetation community type (categorical data)
     int cmnt;

     //Description of a vegetation community type
     string cmnt_name;

     // number of community types in a vegetation mosaic
     int numtype[MAXNVEG];

     // community types of a vegetation mosaic
     int subtype[MAXNVEG][MAXNMSAC];

     // percent coverage of a community type in a vegetation
     //   mosaic
     double pcttype[MAXNVEG][MAXNMSAC];

     // Area covered by a vegetation community type
     double subarea;

     // biome type or ecozone (categorical data)
     int temveg;

     // Water-filled pore space offset
     double wfpsoff[MAXNVEG];
	 
};

#endif

