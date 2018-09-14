/* *************************************************************
****************************************************************
QSOILTEMP606B.H - Soil temperature model developed by Qianlai
                  Zhuang for the Terrestrial Ecosystem Model.
                  Model based on Goodrich one-dimensional
                  soil thermal model (Goodrich 1976, 1978a, 
                  1978b; Romanovsky et al. 1997)
****************************************************************

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>    


References:

Goodrich LE (1976) A numerical model for assessing the influence
  of snow cover on the ground thermal regime.  PhD thesis, 
  410 pp., McGill University, Montreal, Quebec.
  
Goodrich LE (1978a) Some results of a numerical study of ground 
  thermal regimes. pp. 29-34. IN: Proceedings of the 3rd 
  International Conference on Permafrost, Vol. 1, Nat. Res.
  Counc. of Canada, Ottawa.
  
Goodrich LE (1978b) Efficient numerical technique for one-
  dimensional thermal problems with phase change. International
  Journal of Heat and Mass Transfer 21, 615-621.
  
Liston, G. E. and R. A. Pielke (2000) A climate version of the 
  regional atmospheric modeling system.  Theoretical and 
  Applied Climatology 66, 29-47.
    
Romanovsky VE, Osterkamp TE, Duxbury NS (1997) An evaluation of
  three numerical models used in simulation of the active layer
  and permafrost temperature regimes.  Cold Reg. Scie. Technol.
  26, 195-203.
  
Sturm, M., J. Holmgren, M. Konig and K. Morris (1997) The
  thermal conductivity of seasonal snow.  Journal of Glaciology
  43(143), 26-41.
  
Sturm, M., J. Holmgren and G. E. Liston (1995) A seasonal snow
  cover classification system for local to global applications.
  Journal of Climate 8(5), 1261-1283.
    
Zhuang Q, Romanovsky VE, McGuire AD (2001) Incorporation of a 
  permafrost model into a large-scale ecosystem model: Evaluation
  of temporal and spatial scaling issues in simulating soil
  thermal dynamics. Journal of Geophysical Research 106(D24),
  33,648-33,670.

Zhuang Q, McGuire AD, O'Neill KP, Harden JW, Romanovsky VE, Yarie J
  (2002) Modeling the soil thermal and carbon dynamics of a fire
  chronosequence in interior Alaska. Journal of Geophysical Research,
  108, D1, 8147, doi:10.1029/2001JD001244.

Zhuang Q, McGuire AD, Melillo JM, Clein JS, Dargaville RJ,
  Kicklighter DW, Myneni RB, Dong J, Romanovsky VE, Harden J,
  Hobbie JE (2003) Carbon cycling in extratropical terrestrial
  ecosystems of the Northern Hemisphere during the 20th century:
  a modeling analysis of the influences of soil thermal dynamics,
  Tellus 55B: 751-776.

******************************************************************
*************************************************************** */


#ifndef QSOILTEMP606_H
#define QSOILTEMP606_H  

#include "tprocessXML606.h"

typedef long int integer;
typedef char *address;
typedef short int shortint;
typedef double doubledouble;
typedef long int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;

// Maximum number of nodes in the snowpack 
 
#ifndef MAXSNODES_CONST
#define MAXSNODES_CONST
  const int MAXSNODES = 9;
#endif

// Maximum number of soil layers with different thermal 
//   characteristics

const int MAXSLAYERS = 6;

// Maximum number of nodes in snowpack and soil combined

#ifndef MAXNODES_CONST
#define MAXNODES_CONST
  const int MAXNODES = 210;
#endif 

// Maximum number of nodes considered in the output of the soil
//  temperature profile

const int MAXDFST = 30;

// Maximum number of materials for which soil thermal properties 
//   are considered

const int MAXMAT = 5;

// Maximum number of soil depths with "raw" temperature data

const int MAXSPDATA = 25;

// Maximum number of data points per month 

const int MXTSDATA = 3;

// Maximum number of time steps per month of the interpolated
//   fitted data (assumes 0.5 day time steps)

const int MXTSFITTED = 120; // 2x 0.5-day time steps in a month

// Seconds per day

const double SECSPERDAY = 86400.0;

const double PI = 3.1415926536;

const double ADJUST = 0.0001;  

const doubledouble TEN = 10.0; 
const long THOUSANDX100 = 100000;


// Absolute values less than ZEROTOL are considered "zero"

const double ZEROTOL = 0.00001;

struct STMsoilwater 
{
  double layer1;  // moss/litter layer water 
  double layer2;  // organic layer water
  double layer3;

};


struct  STMmonth 
{
  double beginning;
  double middle;
  double end;

};


class Soilthermal60 : public ProcessXML60 
{

  public:

    Soilthermal60();

/* **************************************************************
		 Public Functions
************************************************************** */

     void   getsnowecd( ofstream& rflog1 );
     void   getsnowecd( const string& ecd );
     void   getsoillecd( ofstream& rflog1 );
     void   getsoillecd( const string& ecd );
     void   getsoiltecd( ofstream& rflog1 );
     void   getsoiltecd( const string& ecd );

     void initSoilThermalRegime( const double& tstart );

     double InterpolatST( const double& dst1, 
                          const double& dst2,
                          const double& dst3,
                          const double& dst4, 
                          const double& dst5, 
                          const double& dst6,  
                          double x );

     void resetYr( void );

    
    int    setMonthlySoilConditions( const double& prevtair,
                                     const double& tair,
                                     const double& nexttair,
                                     const double& prevspack,
                                     const double& snowpack,
                                     const double& nextspack,
                                     const int& cmnt,
                                     const int& outmon,
                                     ofstream& rflog1 );
            
    double   setSnowDensity( const int& cmnt, 
                             const double& prec,
                             const int& outmon );

    int setInitSnowPackGrid( const double& prevspack, 
                             const double& spack,  
                             const double& sdensity );
                           
    void   showsnowecd( int& pdcmnt );
    void   showsoillecd( int& pdcmnt );
    void   showsoiltecd( int& pdcmnt );
    void   updateyrCDM( double tair[CYCLE] );


     // "Get" and "Set" functions for private variables and 
     //   parameters
     
     
     // activeLayer ********************************************
      
     inline double getACTLAYER( void ) { return activeLayer; };

     inline void setACTLAYER( const double& pactlayer ) 
     { 
       activeLayer = pactlayer; 
     };


    // cdsnow **************************************************

     inline double getCDSNOW( const int& pcmnt ) 
     { 
       return cdsnow[pcmnt]; 
     };

     inline void setCDSNOW( const double& pcdsnow, 
                            const int& pcmnt ) 
     { 
       cdsnow[pcmnt] = pcdsnow; 
     };


    // dst0 ****************************************************
      
     inline double getDST0( void ) { return dst0; };

     inline void setDST0( const double& pdst0 )
     {
       dst0 = pdst0;
     };

    // dst5 ****************************************************
      
     inline double getDST5( void ) { return dst5; };

     inline void setDST5( const double& pdst5 )
     {
       dst5 = pdst5;
     };

    // dst10 ***************************************************
      
     inline double getDST10( void ) { return dst10; };

     inline void setDST10( const double& pdst10 )
     {
       dst10 = pdst10;
     };

    // dst20 ***************************************************
      
     inline double getDST20( void ) { return dst20; };

     inline void setDST20( const double& pdst20 )
     {
       dst20 = pdst20;
     };

    // dst50 ***************************************************
      
     inline double getDST50( void ) { return dst50; };

     inline void setDST50( const double& pdst50 )
     {
       dst50 = pdst50;
     };

    // dst100 **************************************************
      
     inline double getDST100( void ) { return dst100; };

     inline void setDST100( const double& pdst100 )
     {
       dst100 = pdst100;
     };

    // dst200 **************************************************
      
     inline double getDST200( void ) { return dst200; };

     inline void setDST200( const double& pdst200 )
     {
       dst100 = pdst200;
     };

    // dx9 *****************************************************

     inline double getDX9( const int& pnode ) 
     { 
       return dx9[pnode]; 
     };

     inline void setDX9( const double& pdx9, 
                        const int& pnode ) 
     { 
       dx9[pnode] = pdx9; 
     };


    // frontd **************************************************
      
     inline double getFRONTD( void ) { return frontd; };

     inline void setFRONTD( const double& pfrontd )
     {
       frontd = pfrontd;
     };

    // frontd2 *************************************************
      
     inline double getFRONTD2( void ) { return frontd2; };

     inline void setFRONTD2( const double& pfrontd2 )
     {
       frontd2 = pfrontd2;
     };

    // gflux ***************************************************

     inline double getGFLUX( const int& pcmnt ) 
     { 
       return gflux[pcmnt]; 
     };

     inline void setGFLUX( const double& pgflux, 
                           const int& pcmnt ) 
     { 
       gflux[pcmnt] = pgflux; 
     };


    // initcondf *************************************************

     inline double getINITCONDF( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initCONDF[pcmnt][pslayr]; 
     };

     inline void setINITCONDF( const double& pinitcondf, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initCONDF[pcmnt][pslayr] = pinitcondf; 
     };


    // initcondt *************************************************

     inline double getINITCONDT( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initCONDT[pcmnt][pslayr]; 
     };

     inline void setINITCONDT( const double& pinitcondt, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initCONDT[pcmnt][pslayr] = pinitcondt; 
     };


    // initdense *************************************************

     inline double getINITDENSE( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initDENSE[pcmnt][pslayr]; 
     };

     inline void setINITDENSE( const double& pinitdense, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initDENSE[pcmnt][pslayr] = pinitdense; 
     };


    // initdtday ***********************************************

     inline double getINITDTDAY( const int& pcmnt ) 
     { 
       return initDTDAY[pcmnt]; 
     };

     inline void setINITDTDAY( const double& pinitdtday, 
                               const int& pcmnt ) 
     { 
       initDTDAY[pcmnt] = pinitdtday; 
     };


    // initdxa *************************************************

     inline double getINITDXA( const int& pcmnt,
                               const int& pslayr ) 
     { 
       return initDXA[pcmnt][pslayr]; 
     };

     inline void setINITDXA( const double& pinitdxa, 
                             const int& pcmnt,
                             const int& pslayr ) 
     { 
       initDXA[pcmnt][pslayr] = pinitdxa; 
     };


    // initdxb *************************************************

     inline double getINITDXB( const int& pcmnt,
                               const int& pslayr ) 
     { 
       return initDXB[pcmnt][pslayr]; 
     };

     inline void setINITDXB( const double& pinitdxb, 
                             const int& pcmnt,
                             const int& pslayr ) 
     { 
       initDXB[pcmnt][pslayr] = pinitdxb; 
     };


    // initsphf *************************************************

     inline double getINITSPHF( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initSPHF[pcmnt][pslayr]; 
     };

     inline void setINITSPHF( const double& pinitsphf, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initSPHF[pcmnt][pslayr] = pinitsphf; 
     };


    // initspht *************************************************

     inline double getINITSPHT( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initSPHT[pcmnt][pslayr]; 
     };

     inline void setINITSPHT( const double& pinitspht, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initSPHT[pcmnt][pslayr] = pinitspht; 
     };


    // initthick *************************************************

     inline double getINITTHICK( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initTHICK[pcmnt][pslayr]; 
     };

     inline void setINITTHICK( const double& pinitthick, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initTHICK[pcmnt][pslayr] = pinitthick; 
     };


    // initwater *************************************************

     inline double getINITWATER( const int& pcmnt,
                                 const int& pslayr ) 
     { 
       return initWATER[pcmnt][pslayr]; 
     };

     inline void setINITWATER( const double& pinitwater, 
                               const int& pcmnt,
                               const int& pslayr ) 
     { 
       initWATER[pcmnt][pslayr] = pinitwater; 
     };


    // is9 *****************************************************
      
     inline int getIS9( void ) { return is9; };

     inline void setIS9( const int& pis9 ) 
     { 
       is9 = pis9; 
     };


    // ism19 *****************************************************
      
     inline int getISM19( void ) { return ism19; };

     inline void setISM19( const int& pism19 ) 
     { 
       ism19 = pism19; 
     };


     // kswitch ************************************************
     
     inline void setKSWITCH( const int& pkswitch ) 
     { 
       kswitch = pkswitch; 
     };


     // nextsnowfall *******************************************
      
     inline double getNEXTSNOWFALL( void ) 
     { 
       return nextsnowfall; 
     };

     inline void setNEXTSNOWFALL( const double& pnextsnwfal ) 
     { 
       nextsnowfall = pnextsnwfal; 
     };


     // nextspack **********************************************
      
     inline double getNEXTSPACK( void ) 
     { 
       return nextspack; 
     };

     inline void setNEXTSPACK( const double& pnextspack ) 
     { 
       nextspack = pnextspack; 
     };


     // nexttair ********************************************
      
     inline double getNEXTTAIR( void ) { return nexttair; }

     inline void setNEXTTAIR( const double& pnexttair ) 
     { 
       nexttair = pnexttair; 
     };


     // prevspack **********************************************
     
     inline double getPREVSPACK( void ) { return prevspack; }

     inline void setPREVSPACK( const double& pprvspack ) 
     { 
       prevspack = pprvspack; 
     };


    // smass9 **************************************************
      
     inline double getSMASS9( void ) { return smass9; };

     inline void setSMASS9( const double& psmass9 ) 
     { 
       smass9 = psmass9; 
     };


    // t9 ******************************************************

     inline double getT9( const int& pnode ) 
     { 
       return t9[pnode]; 
     };

     inline void setT9( const double& pt9, 
                        const int& pnode ) 
     { 
       t9[pnode] = pt9; 
     };


    // thawbegin1 **********************************************
      
     inline double getTHAWBEGIN1( void ) { return thawbegin1; };

     inline void setTHAWBEGIN1( const double& pthawbegin1 )
     {
       thawbegin1 = pthawbegin1;
     };

    // thawbegin2 **********************************************
      
     inline double getTHAWBEGIN2( void ) { return thawbegin2; };

     inline void setTHAWBEGIN2( const double& pthawbegin2 )
     {
       thawbegin2 = pthawbegin2;
     };

    // thawend1 ************************************************
      
     inline double getTHAWEND1( void ) { return thawend1; };

     inline void setTHAWEND1( const double& pthawend1 )
     {
       thawend1 = pthawend1;
     };

    // thawend2 ************************************************
      
     inline double getTHAWEND2( void ) { return thawend2; };

     inline void setTHAWEND2( const double& pthawend2 )
     {
       thawend2 = pthawend2;
     };

    // tsoil ***************************************************
      
     inline double getTSOIL( void ) { return tsoil; };

     inline void setTSOIL( const double& ptsoil )
     {
       tsoil = ptsoil;
     };


    // vcond ***************************************************

     inline double getVCOND( const int& pcmnt,
                             const int& pslayr ) 
     { 
       return vcond[pcmnt][pslayr]; 
     };

     inline void setVCOND( const double& pvcond, 
                           const int& pcmnt,
                           const int& pslayr ) 
     { 
       vcond[pcmnt][pslayr] = pvcond; 
     };


    // vegmat **************************************************

     inline integer getVEGMAT( const int& pcmnt,
                               const int& pslayr ) 
     { 
       return vegMAT[pcmnt][pslayr]; 
     };

     inline void setVEGMAT( const integer& pvegmat, 
                            const int& pcmnt,
                            const int& pslayr ) 
     { 
       vegMAT[pcmnt][pslayr] = pvegmat; 
     };


    // vegwindsp ***********************************************

     inline integer getVEGWINDSP( const int& pcmnt ) 
     { 
       return vegWindSp[pcmnt]; 
     };

     inline void setVEGWINDSP( const integer& pvegwindsp, 
                               const int& pcmnt ) 
     { 
       vegWindSp[pcmnt] = pvegwindsp; 
     };


    // vsph ***************************************************

     inline double getVSPH( const int& pcmnt,
                            const int& pslayr ) 
     { 
       return vsph[pcmnt][pslayr]; 
     };

     inline void setVSPH( const double& pvsph, 
                          const int& pcmnt,
                          const int& pslayr ) 
     { 
       vsph[pcmnt][pslayr] = pvsph; 
     };


    // water9 **************************************************

     inline double getWATER9( const int& pnode ) 
     { 
       return water9[pnode]; 
     };

     inline void setWATER9( const double& pwater9, 
                            const int& pnode ) 
     { 
       water9[pnode] = pwater9; 
     };


    // weight9 *************************************************

     inline double getWEIGHT9( const int& pnode ) 
     { 
       return weight9[pnode]; 
     };

     inline void setWEIGHT9( const double& pweight9, 
                             const int& pnode ) 
     { 
       weight9[pnode] = pweight9; 
     };


    // x9 ******************************************************

     inline double getX9( const int& pnode ) 
     { 
       return x9[pnode]; 
     };

     inline void setX9( const double& px9, 
                        const int& pnode ) 
     { 
       x9[pnode] = px9; 
     };
    

    // xfa9 ****************************************************

     inline double getXFA9( const int& pnode ) 
     { 
       return xfa9[pnode]; 
     };

     inline void setXFA9( const double& pxfa9, 
                          const int& pnode ) 
     { 
       xfa9[pnode] = pxfa9; 
     };


    // xfa9 ****************************************************

     inline double getXFB9( const int& pnode ) 
     { 
       return xfb9[pnode]; 
     };

     inline void setXFB9( const double& pxfb9, 
                          const int& pnode ) 
     { 
       xfb9[pnode] = pxfb9; 
     };

     // yrdst0 **********************************************
     
     inline double getYRDST0( void ) { return yrdst0; }

     inline void setYRDST0( const double& pyrdst0 ) 
     { 
       yrdst0 = pyrdst0; 
     };

     inline void updateYRDST0( const double& pdst0 ) 
     { 
       yrdst0 += pdst0; 
     };

     // yrdst5 **********************************************
     
     inline double getYRDST5( void ) { return yrdst5; }

     inline void setYRDST5( const double& pyrdst5 ) 
     { 
       yrdst5 = pyrdst5; 
     };

     inline void updateYRDST5( const double& pdst5 ) 
     { 
       yrdst5 += pdst5; 
     };
      
     // yrdst10 **********************************************
     
     inline double getYRDST10( void ) { return yrdst10; }

     inline void setYRDST10( const double& pyrdst10 ) 
     { 
       yrdst10 = pyrdst10; 
     };

     inline void updateYRDST10( const double& pdst10 ) 
     { 
       yrdst10 += pdst10; 
     };

     // yrdst20 **********************************************
     
     inline double getYRDST20( void ) { return yrdst20; }

     inline void setYRDST20( const double& pyrdst20 ) 
     { 
       yrdst20 = pyrdst20; 
     };

     inline void updateYRDST20( const double& pdst20 ) 
     { 
       yrdst20 += pdst20; 
     };

     // yrdst50 **********************************************
     
     inline double getYRDST50( void ) { return yrdst50; }

     inline void setYRDST50( const double& pyrdst50 ) 
     { 
       yrdst50 = pyrdst50; 
     };

     inline void updateYRDST50( const double& pdst50 ) 
     { 
       yrdst50 += pdst50; 
     };

     // yrdst100 **********************************************
     
     inline double getYRDST100( void ) { return yrdst100; }

     inline void setYRDST100( const double& pyrdst100 ) 
     { 
       yrdst100 = pyrdst100; 
     };

     inline void updateYRDST100( const double& pdst100 ) 
     { 
       yrdst100 += pdst100; 
     };

     // yrdst200 **********************************************
     
     inline double getYRDST200( void ) { return yrdst200; }

     inline void setYRDST200( const double& pyrdst200 ) 
     { 
       yrdst200 = pyrdst200; 
     };

     inline void updateYRDST200( const double& pdst200 ) 
     { 
       yrdst200 += pdst200; 
     };

     // yrfrontd **********************************************
     
     inline double getYRFRONTD( void ) { return yrfrontd; }

     inline void setYRFRONTD( const double& pyrfrontd ) 
     { 
       yrfrontd = pyrfrontd; 
     };

     inline void updateYRFRONTD( const double& pfrontd ) 
     { 
       yrfrontd += pfrontd; 
     };

     // yrfrontd2 **********************************************
     
     inline double getYRFRONTD2( void ) { return yrfrontd2; }

     inline void setYRFRONTD2( const double& pyrfrontd2 ) 
     { 
       yrfrontd2 = pyrfrontd2; 
     };

     inline void updateYRFRONTD2( const double& pfrontd2 ) 
     { 
       yrfrontd2 += pfrontd2; 
     };

     // yrthawbegin1 *******************************************
     
     inline double getYRTHAWBEGIN1( void ) { return yrthawbegin1; }

     inline void setYRTHAWBEGIN1( const double& pyrthawbegin1 ) 
     { 
       yrthawbegin1 = pyrthawbegin1; 
     };

     inline void updateYRTHAWBEGIN1( const double& pthawbegin1 ) 
     { 
       yrthawbegin1 += pthawbegin1; 
     };

     // yrthawbegin2 *******************************************
     
     inline double getYRTHAWBEGIN2( void ) { return yrthawbegin2; }

     inline void setYRTHAWBEGIN2( const double& pyrthawbegin2 ) 
     { 
       yrthawbegin2 = pyrthawbegin2; 
     };

     inline void updateYRTHAWBEGIN2( const double& pthawbegin2 ) 
     { 
       yrthawbegin2 += pthawbegin2; 
     };

     // yrthawend1 *******************************************
     
     inline double getYRTHAWEND1( void ) { return yrthawend1; }

     inline void setYRTHAWEND1( const double& pyrthawend1 ) 
     { 
       yrthawend1 = pyrthawend1; 
     };

     inline void updateYRTHAWEND1( const double& pthawend1 ) 
     { 
       yrthawend1 += pthawend1; 
     };

     // yrthawend2 *******************************************
     
     inline double getYRTHAWEND2( void ) { return yrthawend2; }

     inline void setYRTHAWEND2( const double& pyrthawend2 ) 
     { 
       yrthawend2 = pyrthawend2; 
     };

     inline void updateYRTHAWEND2( const double& pthawend2 ) 
     { 
       yrthawend2 += pthawend2; 
     };

     // yrtsoil *******************************************
     
     inline double getYRTSOIL( void ) { return yrtsoil; }

     inline void setYRTSOIL( const double& pyrtsoil ) 
     { 
       yrtsoil = pyrtsoil; 
     };

     inline void updateYRTSOIL( const double& ptsoil ) 
     { 
       yrtsoil += ptsoil; 
     };
 

  private:

     enum interpIndex { SPACEINDX, TIMEINDX };

/* **************************************************************
		 Private Functions
************************************************************** */

    inline integer abs( integer x ) 
                   {
                     if ( x >= 0 ) { return x; }
                     else { return -(x); }
                   };

    int crankNicholsonBackward( integer *i1 );


    int crankNicholsonForward( integer *i1 );


    void createMorePhasePlanes( integer& itzero,
                                integer& ibzero,
                                double& r1, 
                                double& topold,
                                double& topnew );


    void createSinglePhasePlane(  const integer& cmnt,
                                  const integer& itzero, 
                                  double& r1, 
                                  double& topold, 
                                  const double& topnew );
    
    
    inline doubledouble dabs( doubledouble x ) 
                        { 
                          if ( x >= 0 ) { return x; }
                          else { return -(x); }
                        };

    inline doubledouble dmax( doubledouble a, doubledouble b ) 
                        { 
                          if ( a >= b ) { return a; }
                          else { return b; } 
                        };
    inline doubledouble dmin( doubledouble a, doubledouble b ) 
                        { 
                          if ( a <= b ) { return a; }
                          else { return b; } 
                        };


    int gaussianEliminBackward( integer *i1, 
                                const integer& cmnt );


    int gaussianEliminForward( integer *i1 );


    void initMonthlySoilConditions( const int& outmon,
                                    const double& prevtair,
                                    const double& tair,
                                    const double& nexttair, 
                                    const double& prevspack, 
                                    const double& snowpack, 
                                    const double& nextspack,
                                    const int& cmnt,
                                    ofstream& rflog1 );

 
    int initSoilTemp( const int& cmnt, ofstream& rflog1 );


    int interpolate( double x[], 
                     double y[], 
                     integer *nmax,
  	             double xx[], 
  	             double yy[], 
  	             integer *nnmax, 
                     const int& spaceTimeIndex,
  	             ofstream& rflog1 );


    int interpolateAirHeat( double fitted[MXTSFITTED],
                            ofstream& rflog1 );

        // interpolateSnow(), formerly part of SNOFAL(), 
        //   interpolates the change in snow cover during each 
        //   time step from monthly changes in snow pack
        
    int interpolateSnow( const integer& maxTimeSteps,
                         const double& snowDensity ); 


    inline integer max( integer a, integer b )
                   {
                     if ( a >= b ) { return a; }
                     else { return b; }
                   };

    inline integer min( integer a, integer b )
                   {
                     if ( a <= b ) { return a; }
                     else { return b; }
                   };

    int resetNodeHeat( void );

    void resetTimeStep( const integer& cmnt, 
                        const int& outmon,
                        ofstream& rflog1 );
    
    int resetXFA( const double& thresholdFreezeT,  
                  const double& latentHeat );

    int setAirFreezeThawIndex( void );


        // setFullSnowNode(), formerly part of SNOFAL(),
        //   determines the maximum mass of snow that a "full"
        //   snow node can hold (NOTE: During simulations, the
        //   mass of a "full" snow node remains constant whereas 
        //   the thickness and density of snow within the node 
        //   are allowed to vary

    double setFullSnowNode( const double& timeStepSecs ); 


    int setHeatSources( integer *mmax, 
                        integer kint[2], 
                        double heat[MXTSFITTED][2],
                        double source[MXTSFITTED], 
                        ofstream& kflog1 );

    int setInitSnowPackGrid( const double& initSnowPack );


    int setLowerBoundaryConditions( double *tber );


    int setMonthlySoilTemp( void );

    int setSnowCharSturm( double *ta, 
                          double *sph, 
                          double *cnd );


    int setSoilProfileGrid( const int& cmnt, 
                            ofstream& rflog1 );  


    int setUpperBoundaryConditions( double taer[MXTSFITTED], 
                                    ofstream& rflog1 ); 

    void updateActiveLayer( void );


    int updateMultiplePhasePlaneTemps( integer *itzero, 
                                       integer *ibzero,
                                       const integer& cmnt,
                                       ofstream& rflog1 );


    int updatePhasePlane( integer *dnode, 
                          double *rlw, 
                          double *cu, 
                          double *rsu, 
                          double *cd, 
                          double *rsd, 
                          double *tt, 
                          double *td, 
                          double *dxx, 
                          double *gold, 
                          double *g, 
                          double *t1, 
                          double *t2, 
                          ofstream& rflog1 );


    int updateSinglePhasePlaneTemps( integer *dnode, 
                                     const integer& cmnt, 
                                     ofstream& rflog1 );


    int updateSnowPackGrid( const double& acum, 
                            double *snoden, 
                            double *weight, 
                            double *comp, 
                            double *fcmelt, 
                            double *tdrive );


    int updateSoilProfileHeat( const int& m, 
                               integer *kint, 
                               double *source );


    int updateSoilThermalProperties( integer *mat, 
                                     double *ta, 
	                             double *sph, 
                                     double *cnd, 
                                     ofstream& rflog1 );


    int updateTimeStep( const int& m,
                        const integer& cmnt,
                        double& r1, 
                        const integer& imaxp,
                        ofstream& rflog1 );


/* **************************************************************
		 Private Variables
************************************************************** */

    // Width ( m ) of the active layer
    double activeLayer;

    // Variable used to calculate snow thermal conductivity 
    double calcu_cdsnow; 

    // Monthly soil temperature ( degrees C ) at the surface
    double dst0;

    // Monthly soil temperature ( degrees C ) at 5 cm
    double dst5;

    // Monthly soil temperature ( degrees C ) at 10 cm
    double dst10;

    // Monthly soil temperature ( degrees C ) at 20 cm
    double dst20;     

    // Monthly soil temperature ( degrees C ) at 50 cm
    double dst50;     

    // Monthly soil temperature ( degrees C ) at 100 cm
    double dst100;    

    // Monthly soil temperature ( degrees C ) at 200 cm
    double dst200;    

    // Initial or previous thickness of each node ( m ) in the
    //   snowpack and soil
    double dx9[MAXNODES+1];

    // Monthly depth ( m ) of the node containing the upper 
    //   phase change plane (frozen front from ground surface)
    double frontd;

    double frontd2;

    // Initial or previous index of node representing the 
    //   surface of the snowpack    
    int is9;

    // Debugging flag
    int kdbgflg;

    // Flag to indicate that the soil thermal model needs to
    //  be initialized:
    //  kswitch = 0 during initialization
    //  kswitch = 1 when soil thermal model has already been 
    //              initialized
    int kswitch; 

    double nextdst10; // Next month's dst10

    double nextsnowfall;     // Next month's snowfall
    
    double nextspack;        // Next month's snowpack

    double nexttair;         // Next month's air temperature

    double prevdst10; // Previous month's dst10
    
    double prevspack;        // Previous month's snowpack

    // Initial or previous mass of snowpack ( kg m^-2 )
    double smass9;

    // Monthly snow density ( g cm^-3 )
    double snow_dens;
    
    // Initial or previous temperature at each node  
    double t9[MAXNODES+1];

    // Monthly depth ( m ) of thawed soil just below 
    //   the upper phase change plane associated with
    //   the freezing front from top of soil profile
    double thawbegin1;

    // Monthly depth ( m ) of thawed soil just below 
    //   lower phase change plane associated with 
    //   frozen soil lens in middle of profile
    //   (if it exists)
    double thawbegin2;

    // Monthly depth ( m ) of phase change plane 
    //   associated with frozen soil lens in middle
    //   of profile (if it exists)
    double thawend1;

    // Monthly depth ( m ) of the node just above the lower 
    //   phase change plane represented by permafrost 
    //   (if it exists)
    double thawend2;

    // Mean monthly soil temperature ( degrees C ) of the top 
    //   20 cm of the soil profile
    double tsoil;      

    // Initial or previous water content at each node
    double water9[MAXNODES+1];
    
    // Initial or previous mass of snow within each node 
    //   of the snowpack
    double weight9[MAXSNODES];

    // Initial or previous depth of the top of each node
    double x9[MAXNODES+1];   

    // Initial or previous depth of phase change plane from the 
    //   top of the node that contains the phase change plane 
    double xfa9[MAXNODES+1];

    // Initial or previous heighth of the phase change plane 
    //   above the bottom of the node that contains the phase 
    //   change plane
    double xfb9[MAXNODES+1];



    // Interpolated air temperatures for the beginning, 
    //   middle and end of a month   
    STMmonth airheat;  

    // The term "CAPi" in Figure 5.2 of Goodrich [1976] and 
    //   Figure 1 in Figure 1 of Goodrich [1978b] for each
    //   node in the snowpack and soil
    double capx[MAXNODES+1];

    // Cooling degree month ( degrees C )
    //   see p.1274 in Sturm et al. (1995)
    double CDM; 

    // Maximum Mass ( g m^-2? )of snow in a "filled" snow node 
    double comp;
     
    // Frozen thermal conductivity ( W m^-1 K^-1 ) for each
    //   material type  
    double condf[MAXMAT];
    
    // Thawed thermal conductivity ( W m^-1 K^-1 ) for each
    //   material type   
    double condt[MAXMAT];
    
    // The term "CNi" in Figure 5.2 of Goodrich [1976] and 
    //   Figure 1 in Figure 1 of Goodrich [1978b] for each
    //   node in the snowpack and soil
    double conx[MAXNODES+1];

    // Number of days per month
    double daze[CYCLE];
    
    // Dry density ( kg m^-3 ) of each node in the snowpack
    //   and soil 
    double ddry[MAXNODES+1];  
    
    // Actual time step used ( seconds )
    double dt;       
    
    // Actual time step used ( days )
    double dtday;
    
    // Amount of time ( seconds) the phase change plane existed 
    //   in the node (NOTE: will not be larger than dt)
    double dtfaz;
    
    // Thickness of each node ( m ) in the snowpack and soil 
    double dx[MAXNODES+1];    
        
    // Thickness ( m ) of the current node
    double dxx;

    // Coefficient in Crank-Nicholson finite difference method
    //   (see Equation 5.13 in Goodrich [1976] or Equations [7a]
    //   and [9a] in Goodrich [1978b])
    double e[MAXNODES+1];

    // Interpolated time ( days ) for a time step within a 
    //   particular month
    double eltim[MXTSFITTED];
    
    // Mass of snow (kg m^-3) that melts per day per degree C
    double fcmelt;
    
    // final day of time period
    double final;   
    
    // Air freezing index 
    double frza;

    // Heat at the bottom of the soil profile
    double hbot;

    // Interpolated heat from up to two heat sources during
    //   a 0.5-day time step 
    double heat[MXTSFITTED][2];
    
    // Source of heat
    double heatt[2];

    // Latent heat
    double hlat;    

    // Heat at each node in the soil profile
    double ht[MAXNODES+1];    
    
    // Previous heat at each node in the soil profile
    double htold[MAXNODES+1]; 
    
    // Heat above the surface of the snowpack or soil 
    //   (if snowpack does not exist)
    double htop;   

    // Index of node representing the ground surface 
    //   (i.e., maximum number of nodes in snowpack)
    integer ig;      
    
    // Index of node just above the ground surface
    //   (i.e., bottom node of snowpack if it exists)
    integer igm1;

    // Index of the node that would represent the bottom of the
    //   bottom node of the soil profile (i.e., the bottom of 
    //   the soil profile
    integer imax;
    
    // Index of the node that represents the top of the bottom
    //   node of of the soil profile
    integer imax1;

    // Index of node representing the surface of the
    //   snowpack if it exists
    integer is;   
    
    // Index of node just above the surface of the 
    //   snowpack (i.e. air)
    integer ism1;
    
    // Initial or previous index of node just above the surface 
    //   of the snowpack 
    integer ism19;

    integer kint[2];
    
    // Material index of each node:
    //    0 - Missing data
    //    1 - Moss/litter conductivity data read in from a file
    //    2 - Organic soil conductivity data read in from a file
    //    3 - Mineral soil conductivity data read in from a file
    //    4 - Sturm snow 
    integer mater[MAXNODES+1];
    
    // Maximum number of time steps in a month
    integer mmax;            
   
    // Period of calculation cycle (days)
    double per;     

    // Coefficient in Crank-Nicholson finite difference method
    //   (see Equation 5.13 in Goodrich [1976] or Equations 
    //   [7b] and [9b] in Goodrich [1978b])
    double s[MAXNODES+1];
    
    // Interpolated snow density ( kg m^-3 ) that occurs within 
    //   a 0.5 day time step    
    double sden[MXTSFITTED];
    
    // Heat flux from surface of snowpack or soil (if snowpack
    //   does not exist)
    double sflux;    
       
    // Mass of snowpack ( kg m^-2 )
    double smass;
        
    // Interpolated mass of snow ( kg m^-2 ) that accumulates
    //   or declines within a 0.5 day time step 
    double snow[MXTSFITTED];

    // Interpolated snow pack depth ( m ) for the beginning, 
    //   middle and end of a month
    STMmonth snowdepth; 
    
    // Water content of 3 hydrologic soil layers of the HM
    STMsoilwater soilwater; 

    // Frozen volumetric heat capacity ( MJ m^-1 K^-1 x 1000 )
    double sphf[MAXMAT];
    
    // Thawed volumetric heat capacity ( MJ m^-1 K^-1 x 1000 )
    double spht[MAXMAT];

    // Temperature (degrees C ) at each node
    double t[MAXNODES+1];   
    
    // Interpolated air temperature ( degrees C ) for a 
    //   0.5 day time step
    double taer[MXTSFITTED];
    
    // Air temperature ( degrees C ) during current 0.5-day 
    //   time step
    double tstair;
    
    // Highest air temperature ( degrees C ) for a time step 
    //   during a month
    double tairhi;
    
    // Lowest air temperature ( degrees C ) for a time step 
    //   during a month
    double tairlo;
    
    // Mean monthly temperature ( degrees C ) at each node
    //   in the snowpack or soil
    double tanee[MAXNODES+1];  
    
    // Interpolated temperature ( degrees C ) at the bottom
    //   of the soil profile for a 0.5 day time step
    double tber[MXTSFITTED];
    
    // Temperature ( degrees C ) at the bottom of the 
    //   soil profile
    double tbot;
    
    // Temperature ( degrees C ) of the node below the 
    //   current node
    double td;

    // Threshold temperature ( degrees C ) for phase change 
    //   of water/ice
    double tf;       

    // Previous temperature ( degrees C ) at each node in
    //   the snowpack and soil
    double thalt[MAXNODES+1];
    
    double theta;           // theta parameter
    double theta1;
    
    // Air thawing index
    double thwa;
    
    double time;    // cumulative time of calculation
    double told[MAXNODES+1];  // previous temperature at each node

    // Variable used to indicate an assumed constant 30 days 
    //   per month when calculating mmax and looking at 
    //   within month thermal and snow dynamics  
    double total;
    
    // Water content ( volumetric % ) at each node
    double water[MAXNODES+1];

    double water1; // moss/litter layer water content
    double water2; 
    double water3;

    // Actual mass ( kg m^-2 ) of snow within each node of the 
    //   snowpack
    double weight[MAXSNODES];

    // Depth ( m ) of the top of each node 
    //   (negative if in snowpack; positive if in soil)
    double x[MAXNODES+1];    
    
    
    // Depth ( m ) of the phase change plane from the top of 
    //   the node that contains the phase change plane 
    //   (NOTE: any node may contain a phase change plane;
    //   xfa[] must be less than the thickness of the node
    double xfa[MAXNODES+1];
    
    
    // Heighth ( m ) of the phase change plane above the bottom 
    //   of the node that contains the phase change plane 
    //   (NOTE: any node may contain a phase change plane;
    //   xfb must be less than the thickness of the node
    double xfb[MAXNODES+1];
    
    
    // Depth ( m ) of heat source from the top of the node that
    //   contains the heat source (NOTE: All nodes within the 
    //   soil may contain a heat source
    double xhet[MAXNODES+1];

    // Annual sum of dst0
    double yrdst0; 
      
    // Annual sum of dst5
    double yrdst5;    

    // Annual sum of dst10
    double yrdst10;

    // Annual sum of dst20
    double yrdst20;   

    // Annual sum of dst50
    double yrdst50;   

    // Annual sum of dst100
    double yrdst100;  

    // Annual sum of dst200
    double yrdst200;  

    // Annual sum of frontd
    double yrfrontd;

    // Annual sum of frontd2
    double yrfrontd2;

    // Annual sum of thawbegin1
    double yrthawbegin1;

    // Annual sum of thawbegin2
    double yrthawbegin2;

    // Annual sum of thawend1
    double yrthawend1;

    // Annual sum of thawend2
    double yrthawend2;

    // Annual sum of tsoil
    double yrtsoil;


    // ********************* Parameters ************************

    // Vegetation-specific
    double cdsnow[MAXCMNT];

    // Vegetation-specific depths of initial soil temperatures
    double DEPTH[MAXCMNT][MAXSPDATA];

    // Vegetation-specific
    double gflux[MAXCMNT];

    // Vegetation-specific Frozen thermal conductivity of each 
    //   soil layer    
    double initCONDF[MAXCMNT][MAXSLAYERS];

    // Vegetation-specific thawed thermal conductivity of 
    //   soil layer    
    double initCONDT[MAXCMNT][MAXSLAYERS];

    // Vegetation-specific dry density of soil layer ( kg m^-3 )
    double initDENSE[MAXCMNT][MAXSLAYERS];
    
    // Vegetation-specific time step as proportion of a day
    double initDTDAY[MAXCMNT];   
    
    // Vegetation-specific depth step ( m ) of heat flux from 
    //   top within soil layer
    double initDXA[MAXCMNT][MAXSLAYERS];
    
    // Vegetation-specific depth step ( m ) of heat flux from 
    //   bottom within soil layer
    double initDXB[MAXCMNT][MAXSLAYERS];
    
    // Vegetation-specific frozen volumetric heat capacity of 
    //   soil layer
    double initSPHF[MAXCMNT][MAXSLAYERS];
    
    // Vegetation-specific thawed volumetric heat capacity 
    //   of soil layer
    double initSPHT[MAXCMNT][MAXSLAYERS];

   
    // Vegetation-specific thickness ( m ) of soil layers:
    //   initTHICK[MAXCMNT][0] - moss/litter layer
    //   initTHICK[MAXCMNT][1] - upper organic soil layer
    //   initTHICK[MAXCMNT][2] - lower organic soil layer
    //   initTHICK[MAXCMNT][3] - upper mineral soil layer
    //   initTHICK[MAXCMNT][4] - lower mineral soil layer
    
    double initTHICK[MAXCMNT][MAXSLAYERS];
    
    // Vegetation-specific initial water content of each 
    //   soil layer
    double initWATER[MAXCMNT][MAXSLAYERS];

    // Vegetation-specific initial temperature data
    double TEMP[MAXCMNT][MAXSPDATA];
    
    // Vegetation-specific
    double vcond[MAXCMNT][MAXSLAYERS];
   
    // Vegetation-specific
    double VDEPTH1[MAXCMNT];
   
    // Vegetation-specific material index of each soil layer
    integer vegMAT[MAXCMNT][MAXSLAYERS];
    
    // Vegetation-specific wind speed index: 
    //   0 for low
    //   1 for high 
    integer vegWindSp[MAXCMNT];

    // Vegetation-specific
    double vsph[MAXCMNT][MAXSLAYERS]; 
    
};

#endif

