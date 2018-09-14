/* *************************************************************
ELMNT605.H - Contains functions to manage elements used in GIS
             (Note: Elements are usually grid cells)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
                                  
************************************************************** */

#ifndef ELMNT602_H
#define ELMNT602_H

class Elmnt60 
{
   
   public:

     Elmnt60( void );

/* **************************************************************
                 Public Functions
************************************************************** */

     void ask( ofstream& rflog1 );
     
     int coregerr( ofstream& rflog1, 
                   const string& varname1, 
                   const double& col1, 
                   const double& row1, 
                   const string& varname2, 
                   const double& col2, 
                   const double& row2 );
     
     void show( ofstream& rflog1, 
                const double& col, 
                const double& row );
     
     void show( ofstream& rflog1, 
                const double& col, 
                const double& row, 
                const long& totyr, 
                const double& tol );

/* **************************************************************
                 Public Variables
************************************************************** */
         
     // Column or longitude of element
     double col;

     // Area of element
     long carea;

     // Count of elements in a region
     long count;

     // Mean Elevation of element
     double elev;

     int end;

     long grdcnt;

     long numskip;

     // Region where element is located
     string region;

     // Row or latitude of element
     double row;

     int stopflag;

     int strtflag;

     int  totyr;


   private:

/* **************************************************************
                 Private Variables
************************************************************** */

     int endflag;
     long numgrids;
};

#endif

