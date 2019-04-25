/* **************************************************************
*****************************************************************
TVEG606CNOFERT.H -  Vegetation characteristics used in the 
  Terrestrial Ecosystem Model (TEM).  Nitrogen fertilizers are
  never assumed to be applied to croplands.
  
Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>  

****************************************************************
************************************************************* */

#ifndef TVEG606_H
#define TVEG606_H

#include "protocol605.hpp"

#include<cstdio>

  using std::printf;

#include<ncurses.h>

#include<iostream>

  using std::cout;
  using std::cin;
  using std::ios;
  using std::cerr;
  using std::endl;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<cstdlib>

  using std::exit;
  using std::atof;
  using std::atoi;

#include<cmath>

  using std::exp;
  using std::pow;
    
#include<string>
  
  using std::string;


// Tveg60 also uses the global constants CYCLE and NUMVEG
#include "temconsts606.hpp"

// Tveg60 uses Biomass Class
#include "bioms423.hpp"   

// Tveg60 uses InorgN60 Class
#include "inorgn60.hpp"   

// Tveg60 uses VolatileOrganicCarbon60 class
#include "voc60.hpp"      

class Tveg60 
{

  public:

     Tveg60();

/* **************************************************************
		 Public Functions
************************************************************** */

     // Limit parameter topt to a biome-specific range of 
     //   air temperatures
     
     void boundTOPT( const int& pcmnt );

     void resetEcds( const int& pcmnt, const double& psiplusc );

     void resetMonthlyFluxes( void );

     void resetNEWTOPT( const int& pcmnt, 
                        const double& tair, 
                        const double& unnrmleaf );

     void resetYrFluxes( void );

     double setGV( const double& eet,
                   const double& pet,
                   const int& moistlim );

     void setNewRESPQ10( const int& pdcmnt, const double& tair );

     void setTEMP( const int& pdcmnt, const double& tair );

     void setThawPercent( const double& pprevdst10,
                          const double& pdst10,
                          const double& pnextdst10 );

     #ifdef CALIBRATE_TEM
       void   showecd( const int& pdcmnt );
     
       void   showleaf( const int& pdcmnt );
     #endif

     void   updateC2N( const int& pdcmnt,
                       const double& yreet,
                       const double& yrpet,
                       const double& currentco2,
                       const double& initco2 );

     void updateDynamics( const int& pdcmnt,
                          const double& co2,
                          const double& aot40,
                          const InorgN60& ndep,
                          const InorgN60& extraNH4,
                          const double& par,
                          const double& pet,
                          const double& prevmaxpet,
                          const double& eet,
                          const double& prevmaxeet,
                          const double& vegc,
                          const double& structn,
                          const double& labilen,
                          const double& soilh2o,
                          const double& soilnh4,
                          const double& soilno3,
                          const int& moistlim,
                          const int& nfeed,
                          const int& o3flag,
                          const int& agstate,
                          const int& agperennial,
                          const int& year,
                          const int& fertflag,
                          const double& ksoil,
                          const double& netnmin,
                          const double& ammnvol,
                          const double& nitrif,
                          const double& no3prod,
                          double& agfertn );

     void updateFoliage( const int& pdcmnt,
						 const double& vegc,
						 const double& eet_mature );



     // "Get" and "Set" private variables and parameters
     
     // abvgrndResp ********************************************

     inline double getABVGPR( void ) { return abvgrndResp; };

     inline void setABVGPR( const double& pabvgrndResp ) 
     { 
       abvgrndResp = pabvgrndResp; 
     };

     // adjc2n *************************************************

     inline double getADJC2N( void ) { return adjc2n; } 

     inline void setADJC2N( const double& padjc2n ) 
     { 
       adjc2n = padjc2n; 
     };


     // aleaf **************************************************
     
     inline double getALEAF( const int& pcmnt ) 
     { 
       return aleaf[pcmnt]; 
     };

     inline void setALEAF( const double& paleaf, 
                           const int& pcmnt ) 
     { 
       aleaf[pcmnt] = paleaf; 
     };

 
     // alpha *****************************************************

     inline double getALPHA( const int& pcmnt )
     {
       return alpha[pcmnt];
     };

     inline void setALPHA( const double& palpha, const int& pcmnt )
     {
       alpha[pcmnt] = palpha;
     };


     // beta *****************************************************

     inline double getBETA( const int& pcmnt )
     {
       return beta[pcmnt];
     };

     inline void setBETA( const double& pbeta, const int& pcmnt )
     {
       beta[pcmnt] = pbeta;
     };


     // bleaf **************************************************
     
     inline double getBLEAF( const int& pcmnt ) 
     { 
       return bleaf[pcmnt]; 
     };

     inline void setBLEAF( const double& pbleaf, 
                           const int& pcmnt ) 
     { 
       bleaf[pcmnt] = pbleaf; 
     };

 
     // c2n ****************************************************
     
     inline double getC2N( void ) { return c2n; };
     
     inline void setC2N( const double& pc2n ) { c2n = pc2n; };


     // c2na ***************************************************
     
     inline double getC2NA( const int& pcmnt ) 
     {
       return c2na[pcmnt]; 
     };
     
     inline void setC2NA( const double& pc2na, 
                          const int& pcmnt ) 
     { 
       c2na[pcmnt] = pc2na; 
     };


     // c2nb ***************************************************
     
     inline double getC2NB( const int& pcmnt ) 
     { 
       return c2nb[pcmnt]; 
     };
     
     inline void setC2NB( const double& pc2nb, 
                          const int& pcmnt ) 
     { 
       c2nb[pcmnt] = pc2nb; 
     };


     // c2nmin *************************************************
     
     inline double getC2NMIN( const int& pcmnt ) 
     { 
       return c2nmin[pcmnt]; 
     };
     
     inline void setC2NMIN( const double& pc2nmin, 
                            const int& pcmnt ) 
     { 
       c2nmin[pcmnt] = pc2nmin; 
     };


     // cfall **************************************************
     
     inline double getCFALL( const int& pcmnt ) 
     { 
       return cfall[pcmnt]; 
     };

     inline void setCFALL( const double& pcfall, 
                           const int& pcmnt ) 
     { 
       cfall[pcmnt] = pcfall; 
     };


     // cleaf **************************************************
     
     inline double getCLEAF( const int& pcmnt ) 
     { 
       return cleaf[pcmnt]; 
     };

     inline void setCLEAF( const double& pcleaf, 
                           const int& pcmnt ) 
     { 
       cleaf[pcmnt] = pcleaf; 
     };

 
     // cmax ***************************************************
     
     inline double getCMAX( void ) { return cmax; };

     inline void setCMAX( const double& pcmax ) 
     { 
       cmax = pcmax; 
     };


     // cmaxcut ************************************************
     
     inline double getCMAXCUT( const int& pcmnt ) 
     { 
       return cmaxcut[pcmnt]; 
     };

     inline void setCMAXCUT( const double& pcmaxcut, 
                             const int& pcmnt ) 
     { 
       cmaxcut[pcmnt] = pcmaxcut; 
     };


     // cmax1a *************************************************
     
     inline double getCMAX1A( const int& pcmnt ) 
     { 
       return cmax1a[pcmnt]; 
     };

     inline void setCMAX1A( const double& pcmax1a, 
                            const int& pcmnt ) 
     { 
       cmax1a[pcmnt] = pcmax1a; 
     };


     // cmax1b *************************************************
     
     inline double getCMAX1B( const int& pcmnt ) 
     { 
       return cmax1b[pcmnt]; 
     };

     inline void setCMAX1B( const double& pcmax1b, 
                            const int& pcmnt ) 
     { 
       cmax1b[pcmnt] = pcmax1b; 
     };


     // cmax2a *************************************************
     
     inline double getCMAX2A( const int& pcmnt ) 
     { 
       return cmax2a[pcmnt]; 
     };

     inline void setCMAX2A( const double& pcmax2a, 
                            const int& pcmnt ) 
     { 
       cmax2a[pcmnt] = pcmax2a; 
     };


     // cmax2b *************************************************
     
     inline double getCMAX2B( const int& pcmnt ) 
     { 
       return cmax2b[pcmnt]; 
     };

     inline void setCMAX2B( const double& pcmax2b, 
                            const int& pcmnt ) 
     { 
       cmax2b[pcmnt] = pcmax2b; 
     };


     // cneven *************************************************
     
     inline double getCNEVEN( void ) { return cneven; };

     inline void setCNEVEN( const double& pcneven ) 
     { 
       cneven = pcneven; 
     };


     // cnmin **************************************************
     
     inline double getCNMIN( const int& pcmnt ) 
     { 
       return cnmin[pcmnt]; 
     };

     inline void setCNMIN( const double& pcnmin, 
                           const int& pcmnt ) 
     { 
       cnmin[pcmnt] = pcnmin; 
     };


     // cov ****************************************************
     
     inline double getCOV( const int& pcmnt ) 
     { 
       return cov[pcmnt]; 
     };

     inline void setCOV( const double& pcov, const int& pcmnt ) 
     { 
       cov[pcmnt] = pcov; 
     };


     // currentveg *********************************************
     
     inline int getCURRENTVEG( void ) { return currentveg; };

     inline void setCURRENTVEG( const int& ptveg ) 
     { 
       currentveg = ptveg; 
     };
     
     
     // dc2n ***************************************************
     
     inline double getDC2N( void ) { return dc2n; };

     inline void setDC2N( const double& pdc2n ) 
     { 
       dc2n = pdc2n; 
     };
     
     
     // findozone **********************************************
     
     inline double getFINDOZONE( void ) { return findozone; };

     inline void setFINDOZONE( const double& pfindozone ) 
     { 
       findozone = pfindozone; 
     };

     // foliage *************************************************
     
     inline double getFOLIAGE( void ) { return foliage; };


     // fozone *************************************************
     
     inline double getFOZONE( void ) { return fozone; };

     inline void setFOZONE( const double& pfozone ) 
     { 
       fozone = pfozone; 
     };

     // fpc ****************************************************
     
     inline double getFPC( void ) { return fpc; };

     inline void setFPC( const double& pfpc ) 
     { 
       fpc = pfpc; 
     };

     // fpcmax *************************************************
     
     inline double getFPCMAX( const int& pcmnt ) 
     { 
       return fpcmax[pcmnt]; 
     };

     inline void setFPCMAX( const double& pfpcmx, 
                            const int& pcmnt ) 
     { 
       fpcmax[pcmnt] = pfpcmx; 
     };


     // fprevozone *********************************************
     
     inline double getFPREVOZONE( void ) { return fprevozone; };

     inline void setFPREVOZONE( const double& pfprevozone ) 
     { 
       fprevozone = pfprevozone; 
     };


     // gamma *****************************************************

     inline double getGAMMA( const int& pcmnt )
     {
       return gamma[pcmnt];
     };

     inline void setGAMMA( const double& pgamma, const int& pcmnt )
     {
       gamma[pcmnt] = pgamma;
     };


     // gpp ****************************************************
     
     inline double getGPP( void ) { return gpp; };

     inline void setGPP( const double& pgpp ) 
     { 
       gpp = pgpp; 
     };

     // gpr ****************************************************
     
     inline double getGPR( void ) { return gpr; };

     inline void setGPR( const double& pgpr ) 
     { 
       gpr = pgpr; 
     };

     // gva ****************************************************
     
     inline double getGVA( const int& pcmnt ) 
     { 
       return gva[pcmnt]; 
     };

     inline void setGVA( const double& pgva, 
                         const int& pcmnt ) 
     { 
       gva[pcmnt] = pgva; 
     };


     // ingpp **************************************************
     
     inline double getINGPP( void ) { return ingpp; };

     inline void setINGPP( const double& pingpp ) 
     { 
       ingpp = pingpp; 
     };

     // initcneven *********************************************
     
     inline double getINITCNEVEN( const int& pcmnt ) 
     { 
       return initcneven[pcmnt]; 
     };

     inline void setINITCNEVEN( const double& pincneven, 
                                const int& pcmnt ) 
     { 
       initcneven[pcmnt] = pincneven; 
     };


     // initleafmx *********************************************
     
     inline double getINITLEAFMX( const int& pcmnt ) 
     { 
      return initleafmx[pcmnt]; 
     };

     inline void setINITLEAFMX( const double& pinleafmx, 
                                const int& pcmnt ) 
     { 
       initleafmx[pcmnt] = pinleafmx; 
     };


     // innpp **************************************************
     
     inline double getINNPP( void ) { return innpp; };

     inline void setINNPP( const double& pinnpp ) 
     { 
       innpp = pinnpp; 
     };

     // inuptake.nh4 *******************************************
     
     inline double getINH4UPTAKE( void ) 
     { 
       return inuptake.nh4; 
     };

    inline void setINH4UPTAKE( const double& pinnh4up ) 
     { 
       inuptake.nh4 = pinnh4up; 
     };

     
     // inuptake.no3 *******************************************
     
     inline double getINO3UPTAKE( void ) 
     { 
       return inuptake.no3; 
     };

    inline void setINO3UPTAKE( const double& pinno3up ) 
     { 
       inuptake.no3 = pinno3up; 
     };

     
     // inuptake.total *****************************************
     
     inline double getINUPTAKE( void ) 
     { 
       return inuptake.total; 
     };

    inline void setINUPTAKE( const double& pinuptake ) 
     { 
       inuptake.total = pinuptake; 
     };


     // kc *****************************************************
     
     inline double getKC( const int& pcmnt ) 
     { 
       return kc[pcmnt]; 
     };

     inline void setKC( const double& pkc, const int& pcmnt ) 
     { 
       kc[pcmnt] = pkc; 
     };


     // ki *****************************************************
     
     inline double getKI( const int& pcmnt ) 
     { 
       return ki[pcmnt]; 
     };

     inline void setKI( const double& pki, const int& pcmnt ) 
     { 
       ki[pcmnt] = pki; 
     };


     // kn1 ****************************************************
     
     inline double getKN1( const int& pcmnt ) 
     { 
       return kn1[pcmnt]; 
     };

     inline void setKN1( const double& pkn1, const int& pcmnt ) 
     { 
       kn1[pcmnt] = pkn1; 
     };


     // kra ****************************************************
     
     inline double getKRA( const int& pcmnt ) 
     { 
       return kra[pcmnt]; 
     };

     inline void setKRA( const double& pkra, const int& pcmnt ) 
     { 
       kra[pcmnt] = pkra; 
     };


     // krb ****************************************************
     
     inline double getKRB( const int& pcmnt ) 
     { 
       return krb[pcmnt]; 
     };

     inline void setKRB( const double& pkrb, const int& pcmnt ) 
     { 
       krb[pcmnt] = pkrb; 
     };


     // kleaf **************************************************
     
     inline double getKLEAFC( const int& pcmnt ) 
     { 
       return kleafc[pcmnt]; 
     };

     inline void setKLEAFC( const double& pkleafc, 
                            const int& pcmnt ) 
     { 
       kleafc[pcmnt] = pkleafc; 
     };


     // kvnh4 ****************************************************
     
     inline double getKVNH4( const int& pcmnt ) 
     { 
       return kvnh4[pcmnt]; 
     };

     inline void setKVNH4( const double& pkvnh4, 
                           const int& pcmnt ) 
     { 
       kvnh4[pcmnt] = pkvnh4; 
     };


     // kvno3 ****************************************************
     
     inline double getKVNO3( const int& pcmnt ) 
     { 
       return kvno3[pcmnt]; 
     };

     inline void setKVNO3( const double& pkvno3, 
                           const int& pcmnt ) 
     { 
       kvno3[pcmnt] = pkvno3; 
     };


     // labile.nitrogen ****************************************
     
     inline double getLABILEN( void ) 
     { 
       return labile.nitrogen; 
     };


     // labncon ************************************************
     
     inline double getLABNCON( const int& pcmnt ) 
     { 
       return labncon[pcmnt]; 
     };

     inline void setLABNCON( const double& plabncon, 
                             const int& pcmnt ) 
     { 
       labncon[pcmnt] = plabncon; 
     };


     // lai ****************************************************
     
     inline double getLAI( void ) { return lai; };

     inline void setLAI( const double& plai ) 
     { 
       lai = plai; 
     };

     // lcclnc *************************************************
     
     inline double getLCCLNC( const int& pcmnt ) 
     { 
       return lcclnc[pcmnt]; 
     }

     inline void setLCCLNC( const double& plcclnc, 
                            const int& pcmnt ) 
     { 
       lcclnc[pcmnt] = plcclnc; 
     }


     // leaf ***************************************************
     
     inline double getLEAF( void ) { return leaf; };
     

     inline void setLEAF( const double& pleaf ) 
     { 
       leaf = pleaf; 
     };

     // leafmxc ************************************************
     
     inline double getLEAFMXC( const int& pcmnt ) 
     { 
       return leafmxc[pcmnt]; 
     };

     inline void setLEAFMXC( const double& pleafmxc, 
                             const int& pcmnt ) 
     { 
       leafmxc[pcmnt] = pleafmxc; 
     };


     // ltrfal.carbon ******************************************  
     
     inline double getLTRFALC( void ) { return ltrfal.carbon; };

     inline void setLTRFALC( const double& pltrfalc ) 
     { 
       ltrfal.carbon = pltrfalc; 
     };
     
     // ltrfal.nitrogen ****************************************
     
     inline double getLTRFALN( void ) 
     { 
       return ltrfal.nitrogen; 
     };

     inline void setLTRFALN( const double& pltrfaln ) 
     { 
       ltrfal.nitrogen = pltrfaln; 
     };
     

     // luptake ************************************************
     
     inline double getLUPTAKE( void ) { return luptake; };

     inline void setLUPTAKE( const double& pluptake ) 
     { 
       luptake = pluptake; 
     };
     
     // minleaf ************************************************
     
     inline double getMINLEAF( const int& pcmnt ) 
     { 
       return minleaf[pcmnt]; 
     };

     inline void setMINLEAF( const double& pminleaf, 
                             const int& pcmnt ) 
     { 
       minleaf[pcmnt] = pminleaf; 
     };

 
     // newleafmx **********************************************
     
     inline double getNEWLEAFMX( void ) { return newleafmx; };

     inline void setNEWLEAFMX( const double& pnewleafmx ) 
     { 
       newleafmx = pnewleafmx; 
     };


     // newtopt ************************************************
     
     inline double getNEWTOPT( void ) { return newtopt; };

     inline void setNEWTOPT( const double& pnewtopt ) 
     { 
       newtopt = pnewtopt; 
     };


     // nfall **************************************************
     
     inline double getNFALL( const int& pcmnt ) 
     { 
       return nfall[pcmnt]; 
     };

     inline void setNFALL( const double& pnfall, 
                           const int& pcmnt ) 
     { 
       nfall[pcmnt] = pnfall; 
     };


     // nfix ***************************************************
     
     inline double getNFIX( void ) { return nfix; };

     inline void setNFIX( const double& pnfix ) 
     { 
       nfix = pnfix; 
     };


     // nfixadjust ***********************************************
     
     inline double getNFIXADJUST( const int& pcmnt )
     {
       return nfixadjust[pcmnt];
     };
     
     inline void setNFIXADJUST( const double& pnfixadj,
                                const int& pcmnt )
     {
       nfixadjust[pcmnt] = pnfixadj;
     };
     
     
     // nfixpara ***********************************************
     
     inline double getNFIXPARA( const int& pcmnt ) 
     { 
       return nfixpara[pcmnt]; 
     };

     inline void setNFIXPARA( const double& pnfixpara, 
                              const int& pcmnt ) 
     { 
       nfixpara[pcmnt] = pnfixpara; 
     };


     // nfixparb ***********************************************
     
     inline double getNFIXPARB( const int& pcmnt ) 
     { 
       return nfixparb[pcmnt]; 
     };

     inline void setNFIXPARB( const double& pnfixparb, 
                              const int& pcmnt ) 
     { 
       nfixparb[pcmnt] = pnfixparb; 
     };
 
 
     // nmobil *************************************************
     
     inline double getNMOBIL( void ) { return nmobil; };

     inline void setNMOBIL( const double& pnmobil ) 
     { 
       nmobil = pnmobil; 
     };

     // npp ****************************************************
     
     inline double getNPP( void ) { return npp; };

     inline void setNPP( const double& pnpp ) 
     { 
       npp = pnpp; 
     };

     // nresorb ************************************************
     
     inline double getNRESORB( void ) { return nresorb; };

     inline void setNRESORB( const double& pnresorb ) 
     { 
       nresorb = pnresorb; 
     };

     // nupnh4 *************************************************
     
     inline double getNUPNH4( void ) { return nupnh4; };

     inline void setNUPNH4( const double& pnupnh4 ) 
     { 
       nupnh4 = pnupnh4; 
     };


     // nupnh4cut **********************************************
     
     inline double getNUPNH4CUT( const int& pcmnt ) 
     { 
       return nupnh4cut[pcmnt]; 
     };

     inline void setNUPNH4CUT( const double& pnupnh4cut, 
                               const int& pcmnt ) 
     { 
       nupnh4cut[pcmnt] = pnupnh4cut; 
     };


     // nupnh41a ***********************************************
     
     inline double getNUPNH41A( const int& pcmnt ) 
     { 
       return nupnh41a[pcmnt]; 
     };

     inline void setNUPNH41A( const double& pnupnh41a, 
                              const int& pcmnt ) 
     { 
       nupnh41a[pcmnt] = pnupnh41a; 
     };


     // nupnh41b ***********************************************
     
     inline double getNUPNH41B( const int& pcmnt ) 
     { 
       return nupnh41b[pcmnt]; 
     };

     inline void setNUPNH41B( const double& pnupnh41b, 
                              const int& pcmnt ) 
     { 
       nupnh41b[pcmnt] = pnupnh41b; 
     };


     // nupnh42a ***********************************************
     
     inline double getNUPNH42A( const int& pcmnt ) 
     { 
       return nupnh42a[pcmnt]; 
     };

     inline void setNUPNH42A( const double& pnupnh42a, 
                              const int& pcmnt ) 
     { 
       nupnh42a[pcmnt] = pnupnh42a; 
     };


     // nupnh42b ***********************************************
     
     inline double getNUPNH42B( const int& pcmnt ) 
     { 
       return nupnh42b[pcmnt]; 
     };

     inline void setNUPNH42B( const double& pnupnh42b, 
                              const int& pcmnt ) 
     { 
       nupnh42b[pcmnt] = pnupnh42b; 
     };


     // nupno3 *************************************************
     
     inline double getNUPNO3( void ) { return nupno3; };

     inline void setNUPNO3( const double& pnupno3 ) 
     { 
       nupno3 = pnupno3; 
     };


     // nupno3cut **********************************************
     
     inline double getNUPNO3CUT( const int& pcmnt ) 
     { 
       return nupno3cut[pcmnt]; 
     };

     inline void setNUPNO3CUT( const double& pnupno3cut, 
                               const int& pcmnt ) 
     { 
       nupno3cut[pcmnt] = pnupno3cut; 
     };


     // nupno31a ***********************************************
     
     inline double getNUPNO31A( const int& pcmnt ) 
     { 
       return nupno31a[pcmnt]; 
     };

     inline void setNUPNO31A( const double& pnupno31a, 
                              const int& pcmnt ) 
     { 
       nupno31a[pcmnt] = pnupno31a; 
     };
  
  
     // nupno31b ***********************************************
     
     inline double getNUPNO31B( const int& pcmnt ) 
     { 
       return nupno31b[pcmnt]; 
     };

     inline void setNUPNO31B( const double& pnupno31b, 
                              const int& pcmnt ) 
     { 
       nupno31b[pcmnt] = pnupno31b; 
     };


     // nupno32a ***********************************************
     
     inline double getNUPNO32A( const int& pcmnt ) 
     { 
       return nupno32a[pcmnt]; 
     };

     inline void setNUPNO32A( const double& pnupno32a, 
                              const int& pcmnt ) 
     { 
       nupno32a[pcmnt] = pnupno32a; 
     };


     // nupno32b ***********************************************
     
     inline double getNUPNO32B( const int& pcmnt ) 
     { 
       return nupno32b[pcmnt]; 
     };

     inline void setNUPNO32B( const double& pnupno32b, 
                              const int& pcmnt ) 
     { 
       nupno32b[pcmnt] = pnupno32b; 
     };


     // nuptake.nh4 ********************************************
     
     inline double getNH4UPTAKE( void ) { return nuptake.nh4; };

     inline void setNH4UPTAKE( const double& pnh4uptake ) 
     { 
       nuptake.nh4 = pnh4uptake; 
     };
     
     // nuptake.no3 ********************************************
     
     inline double getNO3UPTAKE( void ) { return nuptake.no3; };

     inline void setNO3UPTAKE( const double& pno3uptake  ) 
     { 
       nuptake.no3 = pno3uptake; 
     };

     // nuptake.total ******************************************
     
     inline double getNUPTAKE( void ) { return nuptake.total; };

     inline void setNUPTAKE( const double& pnuptake ) 
     { 
       nuptake.total = pnuptake; 
     };
     

     // o3para *************************************************
     
     inline double getO3PARA( const int& pcmnt ) 
     { 
       return o3para[pcmnt]; 
     };

     inline void setO3PARA( const double& po3para, 
                            const int& pcmnt ) 
     { 
       o3para[pcmnt] = po3para; 
     };


     // o3parb *************************************************
     
     inline double getO3PARB( const int& pcmnt ) 
     { 
       return o3parb[pcmnt]; 
     };

     inline void setO3PARB( const double& po3parb, 
                            const int& pcmnt ) 
     { 
       o3parb[pcmnt] = po3parb; 
     };


     // o3parc *************************************************
     
     inline double getO3PARC( const int& pcmnt ) 
     { 
       return o3parc[pcmnt]; 
     };

     inline void setO3PARC( const double& po3parc, 
                            const int& pcmnt ) 
     { 
       o3parc[pcmnt] = po3parc; 
     };


     // potveg *************************************************
     
     inline int getPOTVEG( void ) { return potveg; };

     inline void setPOTVEG( const int& ptveg ) 
     { 
       potveg = ptveg; 
     };


     // prevunrmleaf *******************************************
     
     inline double getPREVUNRMLEAF( void ) 
     { 
       return prevunrmleaf; 
     };

     inline void setPREVUNRMLEAF( const double& pprevunrmleaf ) 
     { 
       prevunrmleaf = pprevunrmleaf; 
     };


     // proptrans ************************************************
     
     inline double getPROPTRANS( const int& pcmnt ) 
     { 
       return proptrans[pcmnt]; 
     };

     inline void setPROPTRANS( const double& pproptrans, 
                               const int& pcmnt ) 
     { 
       proptrans[pcmnt] = pproptrans; 
     };


     // prvleafmx **********************************************
     
     inline double getPRVLEAFMX( void ) { return prvleafmx; };

     inline void setPRVLEAFMX( const double& pprvleafmx ) 
     { 
       prvleafmx = pprvleafmx; 
     };


     // qref *****************************************************

     inline double getQREF( const int& pcmnt )
     {
       return qref[pcmnt];
     };

     inline void setQREF( const double& pqref, const int& pcmnt )
     {
       qref[pcmnt] = pqref;
     };

     // rg *****************************************************
     
     inline double getRGRWTH( void ) { return rg; };

     inline void setRGRWTH( const double& prg ) 
     { 
       rg = prg; 
     };

     // rm *****************************************************
     
     inline double getRMAINT( void ) { return rm; };

     inline void setRMAINT( const double& prm ) 
     { 
       rm = prm; 
     };

     // rmmax ****************************************************

     inline double getRMMAX( const int& pcmnt )
     {
       return rmmax[pcmnt];
     };

     inline void setRMMAX( const double& prmmax, const int& pcmnt )
     {
       rmmax[pcmnt] = prmmax;
     };


     // rootResp ***********************************************
     
     inline double getROOTRESP( void ) { return rootResp; };

     inline void setROOTRESP( const double& prootResp ) 
     { 
       rootResp = prootResp; 
     };

     // rroot **************************************************
     
     inline double getRROOT( const int& pcmnt ) 
     { 
       return rroot[pcmnt]; 
     };

     inline void setRROOT( const double& prroot, 
                           const int& pcmnt ) 
     { 
       rroot[pcmnt] = prroot; 
     };


     // sla ****************************************************
     
     inline double getSLA( const int& pcmnt ) 
     { 
       return sla[pcmnt]; 
     };

     inline void setSLA( const double& psla, const int& pcmnt ) 
     { 
       sla[pcmnt] = psla; 
     };


     // strctrl.nitrogen ***************************************
          
     inline double getSTRUCTN( void ) 
     { 
       return strctrl.nitrogen; 
     };


     // subtype ************************************************
          
     inline int getSUBTYPE( void ) { return subtype; };

     inline void setSUBTYPE( const int& psubtype ) 
     { 
       subtype = psubtype; 
     };


     // suptake ************************************************
          
     inline double getSUPTAKE( void ) { return suptake; };

     inline void setSUPTAKE( const double& psuptake ) 
     { 
       suptake = psuptake; 
     };
     

     // thawpercent ********************************************
     
     inline double getTHAWPCT( void ) { return thawpercent; };

     inline void setThawPercent( const double& pthawpct ) 
     { 
       thawpercent = pthawpct; 
     };


     // tmax ***************************************************
     
     inline double getTMAX( const int& pcmnt ) 
     { 
       return tmax[pcmnt]; 
     };

     inline void setTMAX( const double& ptmax, 
                          const int& pcmnt ) 
     { 
       tmax[pcmnt] = ptmax; 
     };


     // tmin ***************************************************
     
     inline double getTMIN( const int& pcmnt ) 
     { 
       return tmin[pcmnt]; 
     };

     inline void setTMIN( const double& ptmin, 
                          const int& pcmnt ) 
     { 
       tmin[pcmnt] = ptmin; 
     };


     // topt ***************************************************
     
     inline double getTOPT( void ) { return topt; };

     inline void setTOPT( const double& ptopt ) 
     { 
       topt = ptopt; 
     };


     // toptmax ************************************************
     
     inline double getTOPTMAX( const int& pcmnt ) 
     { 
       return toptmax[pcmnt]; 
     };

     inline void setTOPTMAX( const double& ptoptmax, 
                             const int& pcmnt ) 
     { 
       toptmax[pcmnt] = ptoptmax; 
     };


     // toptmin ************************************************
     
     inline double getTOPTMIN( const int& pcmnt ) 
     { 
       return toptmin[pcmnt]; 
     };

     inline void setTOPTMIN( const double& ptoptmin, 
                             const int& pcmnt ) 
     { 
       toptmin[pcmnt] = ptoptmin; 
     };


     // transpiration *****************************************
      
     inline double getTRANSPIRATION( void ) 
  	 { 
	     return transpiration; 
	   };

     inline void setTRANSPIRATION( const double& ptrans ) 
     { 
       transpiration = ptrans; 
     };


     // tref *****************************************************

     inline double getTREF( const int& pcmnt )
     {
       return tref[pcmnt];
     };

     inline void setTREF( const double& ptref, const int& pcmnt )
     {
       tref[pcmnt] = ptref;
     };


     // unleaf12 ***********************************************
     
     inline double getUNLEAF12( const int& pcmnt ) 
     { 
       return unleaf12[pcmnt]; 
     };

     inline void setUNLEAF12( const double& punleaf12, 
                              const int& pcmnt ) 
     { 
       unleaf12[pcmnt] = punleaf12; 
     };


     // unnormleaf *********************************************
     
     inline double getUNNORMLEAF( void ) { return unnormleaf; };

     inline void setUNNORMLEAF( const double& punnormleaf ) 
     { 
       unnormleaf = punnormleaf; 
     };

     // plant.carbon *******************************************
     
     inline double getVEGC( void ) { return plant.carbon; };


     // plant.nitrogen *****************************************
      
     inline double getVEGN( void ) { return plant.nitrogen; };

     inline void setVEGN( const double& pvegn ) 
     { 
       plant.nitrogen = pvegn; 
     };

     // yrabvgrndResp ******************************************
     
     inline double getYRABVGRNDRESP( void ) { return yrabvgrndResp; };

     inline void setYRABVGRNDRESP( const double& pyrabvgrndResp ) 
     { 
       yrabvgrndResp = pyrabvgrndResp; 
     };

     inline void updateYRABVGRNDRESP( const double& pabvgrndResp ) 
     { 
       yrabvgrndResp += pabvgrndResp; 
     };

     // yrc2n **************************************************
     
     inline double getYRC2N( void ) { return yrc2n; };

     inline void setYRC2N( const double& pyrc2n ) 
     { 
       yrc2n = pyrc2n; 
     };

     inline void updateYRC2N( const double& pc2n ) 
     { 
       yrc2n += pc2n; 
     };
 
     // yrcarbon ***********************************************
      
     inline double getYRVEGC( void ) { return yrcarbon; };

     inline void setYRVEGC( const double& pyrcarbon ) 
     { 
       yrcarbon = pyrcarbon; 
     };
 
    inline void updateYRVEGC( const double& pvegc ) 
     { 
       yrcarbon += pvegc; 
     };

     // yrfpc ***********************************************
      
     inline double getYRFPC( void ) { return yrfpc; };

     inline void setYRFPC( const double& pyrfpc ) 
     { 
       yrfpc = pyrfpc; 
     };
 
    inline void updateYRFPC( const double& pfpc ) 
     { 
       yrfpc += pfpc; 
     };

     // yrgpp ***********************************************
      
     inline double getYRGPP( void ) { return yrgpp; };

     inline void setYRGPP( const double& pyrgpp ) 
     { 
       yrgpp = pyrgpp; 
     };
 
    inline void updateYRGPP( const double& pgpp ) 
     { 
       yrgpp += pgpp; 
     };

     // yrgpr ***********************************************
      
     inline double getYRGPR( void ) { return yrgpr; };

     inline void setYRGPR( const double& pyrgpr ) 
     { 
       yrgpr = pyrgpr; 
     };
 
    inline void updateYRGPR( const double& pgpr ) 
     { 
       yrgpr += pgpr; 
     };

     // yringpp ***********************************************
      
     inline double getYRINGPP( void ) { return yringpp; };

     inline void setYRINGPP( const double& pyringpp ) 
     { 
       yringpp = pyringpp; 
     };
 
    inline void updateYRINGPP( const double& pingpp ) 
     { 
       yringpp += pingpp; 
     };

     // yrinnfix ***********************************************
      
     inline double getYRINNFIX( void ) { return yrinnfix; };

     inline void setYRINNFIX( const double& pyrinnfix ) 
     { 
       yrinnfix = pyrinnfix; 
     };
 
    inline void updateYRINNFIX( const double& pinnfix ) 
     { 
       yrinnfix += pinnfix; 
     };

     // yrinnpp ***********************************************
      
     inline double getYRINNPP( void ) { return yrinnpp; };

     inline void setYRINNPP( const double& pyrinnpp ) 
     { 
       yrinnpp = pyrinnpp; 
     };
 
    inline void updateYRINNPP( const double& pinnpp ) 
     { 
       yrinnpp += pinnpp; 
     };

     // yrinnup.nh4 ********************************************
     
     inline double getYRINNH4UP( void ) { return yrinnup.nh4; };

     inline void setYRINNH4UP( const double& pyrinnh4up ) 
     { 
       yrinnup.nh4 = pyrinnh4up; 
     };

     inline void updateYRINNH4UP( const double& pinnh4up ) 
     { 
       yrinnup.nh4 += pinnh4up; 
     };
     
     // yrinnup.no3 ********************************************
     
     inline double getYRINNO3UP( void ) { return yrinnup.no3; };

     inline void setYRINNO3UP( const double& pyrinno3up  ) 
     { 
       yrinnup.no3 = pyrinno3up; 
     };

     inline void updateYRINNO3UP( const double& pinno3up ) 
     { 
       yrinnup.no3 += pinno3up; 
     };

     // yrinnup.total ******************************************
     
     inline double getYRINNUP( void ) { return yrinnup.total; };

     inline void setYRINNUP( const double& pyrinnup ) 
     { 
       yrinnup.total = pyrinnup; 
     };

     inline void updateYRINNUP( const double& pinnup ) 
     { 
       yrinnup.total += pinnup; 
     };
     
     // yrinpr *************************************************
      
     inline double getYRINPR( void ) { return yrinpr; };

     inline void setYRINPR( const double& pyrinpr ) 
     { 
       yrinpr = pyrinpr; 
     };
 
    inline void updateYRINPR( const double& pinpr ) 
     { 
       yrinpr += pinpr; 
     };

     // yrlai *************************************************
      
     inline double getYRLAI( void ) { return yrlai; };

     inline void setYRLAI( const double& pyrlai ) 
     { 
       yrlai = pyrlai; 
     };
 
    inline void updateYRLAI( const double& plai ) 
     { 
       yrlai += plai; 
     };

     // yrleaf *************************************************
      
     inline double getYRLEAF( void ) { return yrleaf; };

     inline void setYRLEAF( const double& pyrleaf ) 
     { 
       yrleaf = pyrleaf; 
     };
 
    inline void updateYRLEAF( const double& pleaf ) 
     { 
       yrleaf += pleaf; 
     };

     // yrlnfix *************************************************
      
     inline double getYRLNFIX( void ) { return yrlnfix; };

     inline void setYRLNFIX( const double& pyrlnfix ) 
     { 
       yrlnfix = pyrlnfix; 
     };
 
    inline void updateYRLNFIX( const double& plnfix ) 
     { 
       yrlnfix += plnfix; 
     };

     // yrltrfalc *********************************************
      
     inline double getYRLTRFALC( void ) { return yrltrfalc; };

     inline void setYRLTRFALC( const double& pyrltrfalc ) 
     { 
       yrltrfalc = pyrltrfalc; 
     };
 
    inline void updateYRLTRFALC( const double& pltrfalc ) 
     { 
       yrltrfalc += pltrfalc; 
     };

     // yrltrfaln *********************************************
      
     inline double getYRLTRFALN( void ) { return yrltrfaln; };

     inline void setYRLTRFALN( const double& pyrltrfaln ) 
     { 
       yrltrfaln = pyrltrfaln; 
     };
 
    inline void updateYRLTRFALN( const double& pltrfaln ) 
     { 
       yrltrfaln += pltrfaln; 
     };

     // yrlup **************************************************
      
     inline double getYRLUP( void ) { return yrlup; };

     inline void setYRLUP( const double& pyrlup ) 
     { 
       yrlup = pyrlup; 
     };
 
    inline void updateYRLUP( const double& plup ) 
     { 
       yrlup += plup; 
     };

     // yrnfix *************************************************
      
     inline double getYRNFIX( void ) { return yrnfix; };

     inline void setYRNFIX( const double& pyrnfix ) 
     { 
       yrnfix = pyrnfix; 
     };
 
    inline void updateYRNFIX( const double& pnfix ) 
     { 
       yrnfix += pnfix; 
     };
      
     // yrnitrogen *********************************************
      
     inline double getYRVEGN( void ) { return yrnitrogen; };

     inline void setYRVEGN( const double& pyrnitrogen ) 
     { 
       yrnitrogen = pyrnitrogen; 
     };
 
    inline void updateYRVEGN( const double& pvegn ) 
     { 
       yrnitrogen += pvegn; 
     };

     // yrnmobil *********************************************
      
     inline double getYRNMOBIL( void ) { return yrnmobil; };

     inline void setYRNMOBIL( const double& pyrnmobil ) 
     { 
       yrnmobil = pyrnmobil; 
     };
 
    inline void updateYRNMOBIL( const double& pnmobil ) 
     { 
       yrnmobil += pnmobil; 
     };

     // yrnpp **************************************************
      
     inline double getYRNPP( void ) { return yrnpp; };

     inline void setYRNPP( const double& pyrnpp ) 
     { 
       yrnpp = pyrnpp; 
     };
 
    inline void updateYRNPP( const double& pnpp ) 
     { 
       yrnpp += pnpp; 
     };

     // yrnrsorb ***********************************************
      
     inline double getYRNRSORB( void ) { return yrnrsorb; };

     inline void setYRNRSORB( const double& pyrnrsorb ) 
     { 
       yrnrsorb = pyrnrsorb; 
     };
 
    inline void updateYRNRSORB( const double& pnrsorb ) 
     { 
       yrnrsorb += pnrsorb; 
     };

     // yrnup.nh4 ********************************************
     
     inline double getYRNH4UP( void ) { return yrnup.nh4; };

     inline void setYRNH4UP( const double& pyrnh4up ) 
     { 
       yrnup.nh4 = pyrnh4up; 
     };

     inline void updateYRNH4UP( const double& pnh4up ) 
     { 
       yrnup.nh4 += pnh4up; 
     };
     
     // yrnup.no3 ********************************************
     
     inline double getYRNO3UP( void ) { return yrnup.no3; };

     inline void setYRNO3UP( const double& pyrno3up  ) 
     { 
       yrnup.no3 = pyrno3up; 
     };

     inline void updateYRNO3UP( const double& pno3up ) 
     { 
       yrnup.no3 += pno3up; 
     };

     // yrnup.total ******************************************
     
     inline double getYRNUP( void ) { return yrnup.total; };

     inline void setYRNUP( const double& pyrnup ) 
     { 
       yrnup.total = pyrnup; 
     };

     inline void updateYRNUP( const double& pnup ) 
     { 
       yrnup.total += pnup; 
     };
     
     // yrprod *************************************************
      
     inline double getYRPROD( void ) { return yrprod; };

     inline void setYRPROD( const double& pyrprod ) 
     { 
       yrprod = pyrprod; 
     };
 
    inline void updateYRPROD( const double& pprod ) 
     { 
       yrprod += pprod; 
     };

     // yrrgrowth **********************************************
      
     inline double getYRRGROWTH( void ) { return yrrgrowth; };

     inline void setYRRGROWTH( const double& pyrrgrowth ) 
     { 
       yrrgrowth = pyrrgrowth; 
     };
 
    inline void updateYRRGROWTH( const double& prgrowth ) 
     { 
       yrrgrowth += prgrowth; 
     };

     // yrrmaint ***********************************************
      
     inline double getYRRMAINT( void ) { return yrrmaint; };

     inline void setYRRMAINT( const double& pyrrmaint ) 
     { 
       yrrmaint = pyrrmaint; 
     };
 
    inline void updateYRRMAINT( const double& prmaint ) 
     { 
       yrrmaint += prmaint; 
     };

     // yrrootResp *********************************************
      
     inline double getYRROOTRESP( void ) { return yrrootResp; };

     inline void setYRROOTRESP( const double& pyrrootResp ) 
     { 
       yrrootResp = pyrrootResp; 
     };
 
    inline void updateYRROOTRESP( const double& prootResp ) 
     { 
       yrrootResp += prootResp; 
     };

     // yrsnfix ************************************************
      
     inline double getYRSNFIX( void ) { return yrsnfix; };

     inline void setYRSNFIX( const double& pyrsnfix ) 
     { 
       yrsnfix = pyrsnfix; 
     };
 
    inline void updateYRSNFIX( const double& psnfix ) 
     { 
       yrsnfix += psnfix; 
     };

     // yrstoren ************************************************
      
     inline double getYRSTOREN( void ) { return yrstoren; };

     inline void setYRSTOREN( const double& pyrstoren ) 
     { 
       yrstoren = pyrstoren; 
     };
 
    inline void updateYRSTOREN( const double& pstoren ) 
     { 
       yrstoren += pstoren; 
     };
 
     // yrstructn **********************************************
      
     inline double getYRSTRUCTN( void ) { return yrstructn; };

     inline void setYRSTRUCTN( const double& pyrstructn ) 
     { 
       yrstructn = pyrstructn; 
     };
 
    inline void updateYRSTRUCTN( const double& pstructn ) 
     { 
       yrstructn += pstructn; 
     };
 
     // yrsup **************************************************
      
     inline double getYRSUP( void ) { return yrsup; };

     inline void setYRSUP( const double& pyrsup ) 
     { 
       yrsup = pyrsup; 
     };
 
    inline void updateYRSUP( const double& psup ) 
     { 
       yrsup += psup; 
     };

     // yrthawpct **********************************************
      
     inline double getYRTHAWPCT( void ) { return yrthawpct; };

     inline void setYRTHAWPCT( const double& pyrthawpct ) 
     { 
       yrthawpct = pyrthawpct; 
     };
 
    inline void updateYRTHAWPCT( const double& pthawpct ) 
     { 
       yrthawpct += pthawpct; 
     };
 
     // yrunleaf ***********************************************
      
     inline double getYRUNLEAF( void ) { return yrunleaf; };

     inline void setYRUNLEAF( const double& pyrunleaf ) 
     { 
       yrunleaf = pyrunleaf; 
     };
 
    inline void updateYRUNLEAF( const double& punleaf ) 
     { 
       yrunleaf += punleaf; 
     };
     
     // yrvoc.isoprene *****************************************
      
     inline double getYRISOPRENE( void ) { return yrvoc.isoprene; };

     inline void setYRISOPRENE( const double& pyrisoprene ) 
     { 
       yrvoc.isoprene = pyrisoprene; 
     };
 
    inline void updateYRISOPRENE( const double& pisoprene ) 
     { 
       yrvoc.isoprene += pisoprene; 
     };
     
     // yrvoc.monoterpene *****************************************
      
     inline double getYRMONOTERPENE( void ) { return yrvoc.monoterpene; };

     inline void setYRMONOTERPENE( const double& pyrmonoterpene ) 
     { 
       yrvoc.monoterpene = pyrmonoterpene; 
     };
 
     inline void updateYRMONOTERPENE( const double& pmonoterpene ) 
     { 
       yrvoc.monoterpene += pmonoterpene; 
     };

     // yrvoc.other *****************************************
      
     inline double getYROTHERVOC( void ) { return yrvoc.other; };

     inline void setYROTHERVOC( const double& pyrothervoc ) 
     { 
       yrvoc.other = pyrothervoc; 
     };
 
     inline void updateYROTHERVOC( const double& pothervoc ) 
     { 
       yrvoc.other += pothervoc; 
     };

     // yrvoc.otherReactive ************************************
      
     inline double getYROTHERREACTIVEVOC( void ) { return yrvoc.otherReactive; };

     inline void setYROTHERREACTIVEVOC( const double& pyrotherReactivevoc ) 
     { 
       yrvoc.otherReactive = pyrotherReactivevoc; 
     };
 
     inline void updateYROTHERREACTIVEVOC( const double& potherReactivevoc ) 
     { 
       yrvoc.otherReactive += potherReactivevoc; 
     };

     // yrvoc.total ************************************
      
     inline double getYRVOC( void ) { return yrvoc.total; };

     inline void setYRVOC( const double& pyrvoc ) 
     { 
       yrvoc.total = pyrvoc; 
     };
 
     inline void updateYRVOC( const double& pvoc ) 
     { 
       yrvoc.total += pvoc; 
     };


/* *************************************************************
		 Public Variables
************************************************************* */


     // Index for community type
     int cmnt;

     int dbug;

     // Flag to simulate or prescribe canopy development
     int foliageFlag;

     // Flag to simulate or prescribe seasonal leaf phenology
     int leafFlag;


  private:

/* **************************************************************
		 Private Functions
************************************************************** */

     double deltaleaf( const int& pdcmnt,
                       const double& eet,
                       const double& prveetmx,
                       const double& prvleaf );

     double gppxclm( const int& pdcmnt,
                     const double& co2,
                     const double& par,
                     const double& temp,
                     const double& gv,
                     const double& leaf,
                     const double& foliage,
                     const double& thawpercent );

     double gppxio3( const double& fozone, 
                     const double& eetpet );

     double gppxo3( const int& pdcmnt,
                    const double& gpp,
                    const double& d40,
                    const double& eetpet );

     double nupnh4xclm( const int& pdcmnt,
                        const double& soilh2o,
                        const double& nh4,
                        const double& respq10,
                        const double& ksoil,
                        const double& foliage,
                        const double& fozone );

     double nupno3xclm( const int& pdcmnt,
                        const double& soilh2o,
                        const double& no3,
                        const double& respq10,
                        const double& ksoil,
                        const double& foliage,
                        const double& fozone );

     double nupxclm( const int& pdcmnt,
                     const double& soilh2o,
                     const double& availn,
                     const double& respq10,
                     const double& ksoil,
                     const double& foliage,
		     const double& fozone );

     double rmxclm( const int& pdcmnt,
                    const double& vegc,
                    const double& respq10 );

/* **************************************************************
		 Private Variables
************************************************************** */
     
     // Aboveground plant respiration
     double abvgrndResp; 

     double alleaf;

     // Index for current vegetation type
     int currentveg;

     // Multiplier of indirect ozone effects on GPP
     double findozone;

     double foliage;

     // Multiplier of direct ozone effects on GPP
     double fozone;

     // Monthly foliar projective cover
     double fpc;        

     // Previous month's value of fozone
     double fprevozone;

     // Monthly gross primary productivity (GPP)
     double gpp;        

     // Monthly gross plant respiration (rm + rg)
     double gpr;        

      // Initial monthly gross primary productivity
     double ingpp;     

     // Initial symbiotic N fixation
     double innfix;            

     // Initial net primary productivity
     double innpp;      

     // Initial C/N of biomass production
     double inprodcn;          

     // Initial N uptake by plants
     InorgN60 inuptake;   

     // Labile plant biomass
     Biomass labile;    

     // Monthly leaf area index
     double lai;        

     // monthly normalized leaf phenology
     double leaf; 

     // Number of annual iterations for determining monthly
     //   phenology
     int leafyrs;
     
     double lnfix;

     // Monthly litterfall
     Biomass ltrfal;    

     // Monthly N uptake by plants for labile N
     double luptake;    

     // Updated maximum leaf for current year 
     double newleafmx;

     // Updated optimum air temperature for current year
     double newtopt;

     // Monthly symbiotic N fixation
     double nfix;       

     // Monthly N mobilization by plants
     double nmobil;     

     // Monthly net primary productivity (NPP)
     double npp;        

     // Monthly N resorption by plants
     double nresorb;    

     // Monthly N uptake by plants
     InorgN60 nuptake;    

     // whole plant biomass (structural + labile)
     Biomass plant;     

     // Index for potential vegetation biome type
     int potveg;

     // Unnormalized relative leaf area of previous month
     double prevunrmleaf;

     // Maximum relative leaf area of previous year
     double prvleafmx;

     // Effect of air temperature on plant respiration
     double respq10;

     // Monthly growth respiration
     double rg;         

     // Monthly maintenance respiration
     double rm;         

     // Monthly root respiration
     double rootResp;   

     // Structural plant biomass
     Biomass strctrl;   

     // Index for vegetation subtype
     int subtype;
     
     // Monthly N uptake by plants for structural N
     double suptake;    

     // Effect of air temperature on GPP
     double temp;

     // Percent of month with thawed ground
     double thawpercent; 

     // Canopy transpiration
 	   double transpiration;

     // Monthly unnormalized leaf phenology
     double unnormleaf; 

     // Monthly VOC fluxes
     VolatileOrganicCarbon60 voc;

     // Annual sum of abvgrndResp
     double yrabvgrndResp;

     // ratio of yrcarbon to yrnitrogen
     double yrc2n;            

     // Annual sum of plant.carbon
     double yrcarbon;          

     // Sum of monthly FPC
     double yrfpc;        

     // annual sum of monthly GPP
     double yrgpp;             

      // Annual GPR
     double yrgpr;            

     // Annual sum of ingpp
     double yringpp;           

     // Annual sum of innfix
     double yrinnfix;    

     // Annual sum of innpp
     double yrinnpp;           

     // Annual sum of innup
     InorgN60 yrinnup;           

     double yrinpr;

      // Sum of monthly LAI
     double yrlai;            

     // Annual sum of lnfix
     double yrlnfix;           

     // mean annual normalized leaf phenology
     double yrleaf;      

     // Annual sum of ltrfal.carbon
     double yrltrfalc;      
     
     // Annual sum of ltrfal.nitrogen      
     double yrltrfaln;            

     // Annual sum of luptake
     double yrlup;             

     // Annual sum of nfix
     double yrnfix;            

     // Annual sum of plant.nitrogen
     double yrnitrogen;        

     // Annual sum of nmobil
     double yrnmobil;          

     // Annual sum of npp
     double yrnpp;             

     // Annual sum of nresorb
     double yrnrsorb;          

     // Annual sum of nuptake
     InorgN60 yrnup;             

     double yrprod;

     // Annual sum of rg
     double yrrgrowth;

     // Annual sum of rm
     double yrrmaint;

     // Annual sum of rootResp
     double yrrootResp;

     // Annual sum of snfix
     double yrsnfix;           

     // Annual sum of labile.nitrogen
     double yrstoren;          
     
      // Annual sum of strctrl.nitrogen
     double yrstructn;       
     
     // Annual sum of suptake
     double yrsup;             

     // Annual sum of thawpercent
     double yrthawpct;

     // Annual sum of unnormleaf
     double yrunleaf;          

     // Annual sum of VOC fluxes
     VolatileOrganicCarbon60 yrvoc;


/* *************************************************************
		 Private Parameters
************************************************************* */

     // Biome-specific plant respiration parameters

     double alpha[MAXCMNT];
     double beta[MAXCMNT];
     double gamma[MAXCMNT];
     double qref[MAXCMNT];
     double tref[MAXCMNT];

     // Biome-specific vegetation C/N parameters

     double adjc2n;
     double c2n;
     double c2na[MAXCMNT];
     double c2nb[MAXCMNT];
     double c2nmin[MAXCMNT];
     double cnmin[MAXCMNT];
     double dc2n;

     double cneven;
     double initcneven[MAXCMNT];

     double cfall[MAXCMNT];  // proportion of vegetation carbon

     // Biome-specific carbon uptake parameters for function gppxclm

     double cmax;
     double cmaxcut[MAXCMNT];
     double cmax1a[MAXCMNT];
     double cmax1b[MAXCMNT];
     double cmax2a[MAXCMNT];
     double cmax2b[MAXCMNT];

     // Biome-specific respiration parameters for function rmxclm

     double kr;
     double kra[MAXCMNT];
     double krb[MAXCMNT];

     double lcclnc[MAXCMNT];

     // Biome-specific phenology parameters

     double aleaf[MAXCMNT];
     double bleaf[MAXCMNT];
     double cleaf[MAXCMNT];
     double initleafmx[MAXCMNT];
     double minleaf[MAXCMNT];
     double unleaf12[MAXCMNT];


     // Biome-specific foliage projection cover parameters

     double cov[MAXCMNT];
     double fpcmax[MAXCMNT];
     double sla[MAXCMNT];

     // Biome-specific parameter to describe the sensitivity of GPP
     //   to evapotranspiration
     
     double gva[MAXCMNT];

     // Biome-specific half saturation parameter for function 
     //   gppxclm describing the effects of solar atmospheric 
     //   carbon dioxide concentration on GPP

     double kc[MAXCMNT];

     // Biome-specific half saturation parameter for function 
     //   gppxclm describing the effects of photosybtheically 
     //   active radiation on GPP

     double ki[MAXCMNT];

     double kn1[MAXCMNT];
     double kvnh4[MAXCMNT];
     double kvno3[MAXCMNT];

     // Biome-specific allocation parameters

     double kleafc[MAXCMNT];
     double leafmxc[MAXCMNT];

     double labncon[MAXCMNT];

     double nfall[MAXCMNT];  // proportion of vegetation nitrogen

     // Biome-specific symbiotic N fixation parameters

     double nfixadjust[MAXCMNT];
     double nfixpara[MAXCMNT];
     double nfixparb[MAXCMNT];

     // Biome-specific nitrogen uptake parameters for function nupxclm

     double nmax;
     double nmaxcut[MAXCMNT];
     double nmax1a[MAXCMNT];
     double nmax1b[MAXCMNT];
     double nmax2a[MAXCMNT];
     double nmax2b[MAXCMNT];

     double nupnh4;
     double nupnh4cut[MAXCMNT];
     double nupnh41a[MAXCMNT];
     double nupnh41b[MAXCMNT];
     double nupnh42a[MAXCMNT];
     double nupnh42b[MAXCMNT];

     double nupno3;
     double nupno3cut[MAXCMNT];
     double nupno31a[MAXCMNT];
     double nupno31b[MAXCMNT];
     double nupno32a[MAXCMNT];
     double nupno32b[MAXCMNT];

     // Biome-specific ozone parameters

     double o3para[MAXCMNT];
     double o3parb[MAXCMNT];
     double o3parc[MAXCMNT];
	 
 	   // Proportion of EET that is canopy conductance
	   double proptrans[MAXCMNT];


     // Maximum maintenance respiration rate
     
     double rmmax[MAXCMNT];

     // Biome-specific proportion of gpr lost as root respiration

     double rroot[MAXCMNT];

    // Element-specific optimum temperature for GPP

     double tmax[MAXCMNT];
     double tmin[MAXCMNT];
     double topt;
     double toptmax[MAXCMNT];
     double toptmin[MAXCMNT];

};

#endif

