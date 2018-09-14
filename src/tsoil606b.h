/* **************************************************************
*****************************************************************
TSOIL606B.H - object describing characteristics of soil used by
	          the Terrestrial Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

****************************************************************
************************************************************* */

#ifndef TSOIL606_H
#define TSOIL606_H

// Tsoil60 also uses the global constants CYCLE, MAXRTIME, MISSING,
//   NUMVEG and MAXFNAME
#include "temconsts606.hpp"

#include "tprocessXML606.h"

#include "bioms423.hpp"      // Tsoil60 uses Biomass class
#include "inorgn60.hpp"      // Tsoil60 used InorgN60 class
#include "qsoiltemp606b.h"   // Tsoil60 inherits Soilthermal60 class


class Tsoil60 : public ProcessXML60 
{

  public:
    
     Tsoil60( void );

/* **************************************************************
		 Public Functions
************************************************************** */

     void getecd ( ofstream& rflog1 );

     void getecd ( const string& ecd );
     
     double getThawedReactiveSOMProp( const int& pdcmnt );

     void lake( const double& tair,
                const double& prec,
                double& rain,
                double& snowfall,
                const double& pet,
                double& eet );

     void resetEcds( const int& pcmnt );
     
     void resetMonthlyFluxes( void );
     
     void resetYrFluxes( void );

     void setDOMleaching( const int& pdcmnt,
                          const double& soilc,
                          const double& soiln,
                          const double& soilh2o,
                          const double& rain,
                          const double& eet );

     void setKH2O( const double& vsm,
                   const int& moistlim );

     void setTraceGasFluxes( const double& nh3vol,
                             const double& noprd,
                             const double& n2oprd,
                             const double& n2prd  );

     void showecd( void );

     double snowmelt( const double& elev,
                      const double& tair,
                      const double& prevtair,
                      const double& snowpack );

     void updateActiveLayerRootZ( void );
     
     void updateHydrology( const double& elev,
                           const double& tair,
                           const double& prevtair,
                           const double& prev2tair,
                           const double& rain,
                           const double& pet,
                           const double& avlh2o,
                           const double& rgrndh2o,
                           const double& sgrndh2o,
                           const int& irrgflag,
                           double& irrigate,
                           const int& pdm );

     void updateLeachingLosses( const int& pdcmnt,
                                const double& doc,
                                const double& don,
                                const double& soilno3, 
                                const double& soilh2o );
                                    
     void updateRootZ( const int& pdcmnt );

     void xtext( const int& pdcmnt, 
                 const double& pctsilt, 
                 const double& pctclay );


     // "Get" and "Set" private variables and parameters
     
     // abioticNimmob ******************************************
     
     inline double getABIMMOB( void ) { return abioticNimmob; }

     inline void setABIMMOB( const double& pabimmob )
     {
       abioticNimmob = pabimmob;
     }

     // activeLayer ********************************************
      
     inline double getACTLAYER( void ) { return activeLayer; }

     inline void setACTLAYER( const double& pactlayer ) 
     { 
       activeLayer = pactlayer; 
     }


     // availn.nh4 *********************************************
     
     inline double getNH4( void ) { return availn.nh4; }


     // availn.no3 *********************************************
     
     inline double getNO3( void ) { return availn.no3; }


     // availn.total *******************************************
     
     inline double getAVLN( void ) { return availn.total; }

     inline void setAVLN( const double& pavln ) 
     { 
       availn.total = pavln; 
     }


     // avlh2o *************************************************
     
     inline double getAVLH2O( void ) { return avlh2o; }

     inline void setAVLH2O( const double& pavlh2o ) 
     { 
       avlh2o = pavlh2o; 
     }

     // awcapmm ************************************************
     
     inline double getAWCAPMM( void ) { return awcapmm; }

     inline void setAWCAPMM( const double& pawcapmm ) 
     { 
       awcapmm = pawcapmm; 
     }


     // DOM.carbon *********************************************
     
     inline double getDOC( void ) { return DOM.carbon; }
     
     
     // DOM.nitrogen *******************************************
     
     inline double getDON( void ) { return DOM.nitrogen; }
    

     // drainage ***********************************************
     
     inline double getDRAINAGE( void ) { return drainage; }

     inline void setDRAINAGE( const double& pdrainage ) 
     { 
       drainage = pdrainage; 
     }


     // dst10 **************************************************
     
     inline double getDST10( void ) { return dst10; }

     inline void setDST10( const double& pdst10 ) 
     { 
       dst10 = pdst10; 
     }
    
    
     // eet ****************************************************
     
     inline double getEET( void ) { return eet; }

     inline void setEET( const double& peet ) 
     { 
       eet = peet; 
     }


     // eetmx **************************************************
     
     inline double getEETMX( void ) { return eetmx; }

     inline void setEETMX( const double& peetmx ) 
     { 
       eetmx = peetmx; 
     }


     // erodePOM.carbon ****************************************
     
     inline double getERODEPOC( void ) 
     { 
       return erodePOM.carbon; 
     }

     inline void setERODEPOC( const double& perodepoc ) 
     { 
       erodePOM.carbon = perodepoc; 
     }


     // erodePOM.nitrogen **************************************
     
     inline double getERODEPON( void ) 
     { 
       return erodePOM.nitrogen; 
     }

     inline void setERODEPON( const double& perodepon ) 
     { 
       erodePOM.nitrogen = perodepon; 
     }


     // evaporation **************************************
     
     inline double getEVAPORATION( void ) 
     { 
       return evaporation; 
     }

     inline void setEVAPORATION( const double& pevap ) 
     { 
       evaporation = pevap; 
     }


     // fldcap *************************************************
     
     inline double getFLDCAP( void ) { return fldcap; }


     // fldcapa ************************************************
     
     inline double getFLDCAPA( void ) { return fldcapa; }

     inline void setFLDCAPA( const double& pfldcapa ) 
     { 
       fldcapa = pfldcapa; 
     }


     // fldcapb ************************************************
     
     inline double getFLDCAPB( void ) { return fldcapb; }

     inline void setFLDCAPB( const double& pfldcapb ) 
     { 
       fldcapb = pfldcapb; 
     }


     // h2oyld *************************************************
     
     inline double getH2OYLD( void ) { return h2oyld; }

     inline void setH2OYLD( const double& ph2oyld ) 
     { 
       h2oyld = ph2oyld; 
     }

     
     // ineet **************************************************
     
     inline double getINEET( void ) { return ineet; }

     inline void setINEET( const double& pineet ) 
     { 
       ineet = pineet; 
     }


     // kh2o ***************************************************
     
     inline double getKH2O( void ) { return kh2o; }


     // lchDOMpar **********************************************
     
     inline double getLCHDOMPAR( const int& pcmnt ) 
     { 
       return lchDOMpar[pcmnt]; 
     }
     
     inline void setLCHDOMPAR( const double& plchdompar, 
                               const int& pcmnt ) 
     { 
       lchDOMpar[pcmnt] = plchdompar; 
     }


     // lchNO3par **********************************************
     
     inline double getLCHNO3PAR( void ) { return lchNO3par; }

     inline void setLCHNO3PAR( const double& plchno3par ) 
     { 
       lchNO3par = plchno3par; 
     }


     // lchNO3parcut *******************************************
     
     inline double getLCHNO3PARCUT( const int& pcmnt ) 
     { 
       return lchNO3parcut[pcmnt]; 
     }
     
     inline void setLCHNO3PARCUT( const double& plchno3parcut, 
                                  const int& pcmnt ) 
     { 
       lchNO3parcut[pcmnt] = plchno3parcut; 
     }

     // lchNO3par1a ********************************************
     
     inline double getLCHNO3PAR1A( const int& pcmnt ) 
     { 
       return lchNO3par1a[pcmnt]; 
     }
     
     inline void setLCHNO3PAR1A( const double& plchno3par1a, 
                                 const int& pcmnt ) 
     { 
       lchNO3par1a[pcmnt] = plchno3par1a; 
     }

     // lchNO3par1b ********************************************

     inline double getLCHNO3PAR1B( const int& pcmnt ) 
     { 
       return lchNO3par1b[pcmnt]; 
     }
     
     inline void setLCHNO3PAR1B( const double& plchno3par1b, 
                                 const int& pcmnt ) 
     { 
       lchNO3par1b[pcmnt] = plchno3par1b; 
     }

     // lchNO3par2a ********************************************

     inline double getLCHNO3PAR2A( const int& pcmnt ) 
     { 
       return lchNO3par2a[pcmnt]; 
     }
     
     inline void setLCHNO3PAR2A( const double& plchno3par2a, 
                                 const int& pcmnt ) 
     { 
       lchNO3par2a[pcmnt] = plchno3par2a; 
     }

     // lchNO3par2b ********************************************

     inline double getLCHNO3PAR2B( const int& pcmnt ) 
     { 
       return lchNO3par2b[pcmnt]; 
     }
     
     inline void setLCHNO3PAR2B( const double& plchno3par2b, 
                                 const int& pcmnt ) 
     { 
       lchNO3par2b[pcmnt] = plchno3par2b; 
     }

     
     // leachDOM.carbon ****************************************

     inline double getLEACHDOC( void ) 
     { 
       return leachDOM.carbon; 
     }

     inline void setLEACHDOC( const double& pleachdoc )
     { 
       leachDOM.carbon = pleachdoc; 
     }


     // leachDOM.nitrogen **************************************
     
     inline double getLEACHDON( void ) 
     { 
       return leachDOM.nitrogen; 
     }

     inline void setLEACHDON( const double& pleachdon ) 
     { 
       leachDOM.nitrogen = pleachdon; 
     }


     // leachNH4 ***********************************************
     
     inline double getLEACHNH4( void ) { return leachNH4; }

     inline void setLEACHNH4( const double& pleachnh4 ) 
     { 
       leachNH4 = pleachnh4; 
     }

     // leachNO3 ***********************************************
     
     inline double getLEACHNO3( void ) { return leachNO3; }

     inline void setLEACHNO3( const double& pleachno3 ) 
     { 
       leachNO3 = pleachno3; 
     }


     // minrootz ***********************************************
     
     inline double getMINROOTZ( const int& pcmnt ) 
     { 
       return minrootz[pcmnt]; 
     }

     inline void setMINROOTZ( const double& pminrootz,
                              const int& pcmnt ) 
     { 
       minrootz[pcmnt] = pminrootz; 
     }


     // moist **************************************************
     
     inline double getMOIST( void ) { return moist; }

     inline void setMOIST( const double& psh2o ) 
     { 
       moist = psh2o; 
     }


     // n2flux *************************************************
     
     inline double getN2FLUX( void ) { return n2flux; }

     inline void setN2FLUX( const double& pn2flux ) 
     { 
       n2flux = pn2flux; 
     }


     // n2oflux ************************************************
     
     inline double getN2OFLUX( void ) { return n2oflux; }

     inline void setN2OFLUX( const double& pn2oflux ) 
     { 
       n2oflux = pn2oflux; 
     }

     // nextdst10 **********************************************
     
     inline double getNEXTDST10( void ) { return nextdst10; }

     inline void setNEXTDST10( const double& pnextdst10 ) 
     { 
       nextdst10 = pnextdst10; 
     }


     // nh3flux ************************************************
     
     inline double getNH3FLUX( void ) { return nh3flux; }

     inline void setNH3FLUX( const double& pnh3flx ) 
     { 
       nh3flux = pnh3flx; 
     }


     // ninput *************************************************
     
     inline double getNINPUT( void ) { return ninput; }

     inline void setNINPUT( const double& pninput ) 
     { 
       ninput = pninput; 
     }


     // nlost **************************************************
     
     inline double getNLOST( void ) { return nlost; }

     inline void setNLOST( const double& pnlst ) 
     { 
       nlost = pnlst; 
     }


     // noflux *************************************************
     
     inline double getNOFLUX( void ) { return noflux; }

     inline void setNOFLUX( const double& pnoflux ) 
     { 
       noflux = pnoflux; 
     }

     // nonReactiveOMpar ***************************************
     
     inline double getNSOLPAR( const int& pcmnt ) 
     { 
       return nonReactiveOMpar[pcmnt]; 
     }
     
     inline void setNSOLPAR( const double& pnsolcpar, 
                             const int& pcmnt ) 
     { 
       nonReactiveOMpar[pcmnt] = pnsolcpar; 
     }


     // nonReactiveOrg.carbon **********************************
     
     inline double getNSOLC( void ) 
     { 
       return nonReactiveOrg.carbon; 
     }

     inline void setNSOLC( const double& pnsolc ) 
     { 
       nonReactiveOrg.carbon = pnsolc; 
     }


     // nonReactiveOrg.nitrogen ********************************

     inline double getNSOLN( void ) 
     { 
       return nonReactiveOrg.nitrogen; 
     }

     inline void setNSOLN( const double& pnsoln ) 
     { 
       nonReactiveOrg.nitrogen = pnsoln; 
     }


     // pctclay ************************************************
     
     inline double getPCTCLAY( void ) { return pctclay; }

     inline void setPCTCLAY( const double& ppctclay ) 
     { 
       pctclay = ppctclay; 
     }


     // pcfldcap ***********************************************
     
     inline double getPCTFLDCAP( void ) { return pcfldcap; }

     inline void setPCTFLDCAP( const double& ppctfldcap ) 
     { 
       pcfldcap = ppctfldcap; 
     }

     
     // pctp ***************************************************
     
     inline double getPCTP( void ) { return pctp; }

     inline void setPCTP( const double& ppctp ) 
     { 
       pctp = ppctp; 
     }


     // pctpora ************************************************
     
     inline double getPCTPORA( void ) { return pctpora; }

     inline void setPCTPORA( const double& ppctpora ) 
     { 
       pctpora = ppctpora; 
     }


     // pctporb ************************************************
     
     inline double getPCTPORB( void ) { return pctporb; }

     inline void setPCTPORB( const double& ppctporb ) 
     { 
       pctporb = ppctporb; 
     }


     // pctsand ************************************************
     
     inline double getPCTSAND( void ) { return pctsand; }

     inline void setPCTSAND( const double& ppctsand ) 
     { 
       pctsand = ppctsand; 
     }


     // pctsilt ************************************************
     
     inline double getPCTSILT( void ) { return pctsilt; }

     inline void setPCTSILT( const double& ppctsilt ) 
     { 
       pctsilt = ppctsilt; 
     }


     // prevdst10 **********************************************
     
     inline double getPREVDST10( void ) { return prevdst10; }

     inline void setPREVDST10( const double& pprevdst10 ) 
     { 
       prevdst10 = pprevdst10; 
     }


     // prevspack **********************************************
     
     inline double getPREVSPACK( void ) { return prevspack; }

     inline void setPREVSPACK( const double& pprvspack ) 
     { 
       prevspack = pprvspack; 
     }


     // propReactA *************************************************
     
     inline double getPROPREACTA( const int& pcmnt ) 
     { 
       return propReactA[pcmnt]; 
     }

     inline void setPROPREACTA( const double& ppropreacta,
                                const int& pcmnt ) 
     { 
       propReactA[pcmnt] = ppropreacta; 
     }


     // propReactB *************************************************
     
     inline double getPROPREACTB( const int& pcmnt ) 
     { 
       return propReactB[pcmnt]; 
     }

     inline void setPROPREACTB( const double& ppropreactb,
                                const int& pcmnt ) 
     { 
       propReactB[pcmnt] = ppropreactb; 
     }


     // prveetmx ***********************************************
     
     inline double getPRVEETMX( void ) { return prveetmx; }

     inline void setPRVEETMX( const double& pprveetmx ) 
     { 
       prveetmx = pprveetmx; 
     }


     // psiplusc ***********************************************
     
     inline double getPSIPLUSC( void ) { return psiplusc; }

     inline void setPSIPLUSC( const double& ppsiplusc ) 
     { 
       psiplusc = ppsiplusc; 
     }


     // rootz **************************************************
     
     inline double getROOTZ( void ) { return rootz; }

     inline void setROOTZ( const double& prootz ) 
     { 
       rootz = prootz; 
     }


     // rootza *************************************************
     
     inline double getROOTZA( const int& pcmnt ) 
     { 
       return rootza[pcmnt]; 
     }

     inline void setROOTZA( const double& prootza,
                            const int& pcmnt ) 
     { 
       rootza[pcmnt] = prootza; 
     }


     // rootzb *************************************************
     
     inline double getROOTZB( const int& pcmnt ) 
     { 
       return rootzb[pcmnt]; 
     }

     inline void setROOTZB( const double& prootzb,
                            const int& pcmnt ) 
     { 
       rootzb[pcmnt] = prootzb; 
     }


     // rootzc *************************************************
     
     inline double getROOTZC( const int& pcmnt ) 
     { 
       return rootzc[pcmnt]; 
     }

     inline void setROOTZC( const double& prootzc,
                            const int& pcmnt ) 
     { 
       rootzc[pcmnt] = prootzc; 
     }


     // rperc **************************************************
     
     inline double getRPERC( void ) { return rperc; }

     inline void setRPERC( const double& prperc ) 
     { 
       rperc = prperc; 
     }

     // rrun ***************************************************
     
     inline double getRRUN( void ) { return rrun; }
 
     inline void setRRUN( const double& prrun ) 
     { 
       rrun = prrun; 
     }

     // snowinf ************************************************
     
     inline double getSNOWINF( void ) { return snowinf; }

     inline void setSNOWINF( const double& psnwinf ) 
     { 
       snowinf = psnwinf; 
     }


     // snowpack ***********************************************
     
     inline double getSNOWPACK( void ) { return snowpack; }

     inline void setSNOWPACK( const double& psnwpck ) 
     { 
       snowpack = psnwpck; 
     }


     // sperc **************************************************
     
     inline double getSPERC( void ) { return sperc; }

     inline void setSPERC( const double& psperc ) 
     { 
       sperc = psperc; 
     }


     // srun ***************************************************
     
     inline double getSRUN( void ) { return srun; }

     inline void setSRUN( const double& psrun ) 
     { 
       srun = psrun; 
     }

     // surfrun ************************************************
     
     inline double getSURFRUN( void ) { return surfrun; }

     inline void setSURFRUN( const double& psurfrun ) 
     { 
       surfrun = psurfrun; 
     }


     // totpor *************************************************
     
     inline double getTOTPOR( void ) { return totpor; }

     inline void setTOTPOR( const double& ptotpor ) 
     { 
       totpor = ptotpor; 
     }


     // tsoil **************************************************
     
     inline double getTSOIL( void ) { return tsoil; };

     inline void setTSOIL( const double& ptsoil ) 
     { 
       tsoil = ptsoil; 
     }


     // totalOrg.carbon ****************************************
     
     inline double getTSOLC( void ) { return totalOrg.carbon; }

     inline void setTSOLC( const double& ptsolc ) 
     { 
       totalOrg.carbon = ptsolc; 
     }


     // totalOrg.nitrogen **************************************
     
     inline double getTSOLN( void ) 
     { 
       return totalOrg.nitrogen; 
     }

     inline void setTSOLN( const double& ptsoln ) 
     { 
       totalOrg.nitrogen = ptsoln; 
     }


     // vsm *************************************************
     
     inline double getVSM( void ) { return vsm; }
     
     inline void setVSM( const double& pvsm ) 
     { 
       vsm = pvsm; 
     }


     // wfpsoff *************************************************
     
     inline double getWFPSOFF( void ) 
     { 
       return wfpsoff; 
     }

     inline void setWFPSOFF( const double& pwfpsoff ) 
     { 
       wfpsoff = pwfpsoff; 
     }


     // wiltpt *************************************************
     
     inline double getWILTPT( void ) { return wiltpt; }
     
     inline void setWILTPT( const double& pwiltpt ) 
     { 
       wiltpt = pwiltpt; 
     }


     // wiltpta ************************************************
     
     inline double getWILTPTA( void ) { return wiltpta; }

     inline void setWILTPTA( const double& pwiltpta ) 
     { 
       wiltpta = pwiltpta; 
     }


     // wiltptb ************************************************
     
     inline double getWILTPTB( void ) { return wiltptb; }

     inline void setWILTPTB( const double& pwiltptb ) 
     { 
       wiltptb = pwiltptb; 
     }



     // wsoil **************************************************
     
     inline int getWSOIL( void ) { return wsoil; }

     inline void setWSOIL( const int& pwsoil ) 
     { 
       wsoil = pwsoil; 
     }

     // yrabNimmob *********************************************
     
     inline double getYRABNIMMOB( void ) { return yrabNimmob; }

     inline void setYRABNIMMOB( const double& pyrabNimmob ) 
     { 
       yrabNimmob = pyrabNimmob; 
     }

     inline void updateYRABNIMMOB( const double& pabNimmob ) 
     { 
       yrabNimmob += pabNimmob; 
     }
     
     // yravlh2o ************************************************
     
     inline double getYRAVLH2O( void ) { return yravlh2o; }

     inline void setYRAVLH2O( const double& pyravlh2o ) 
     { 
       yravlh2o = pyravlh2o; 
     }

     inline void updateYRAVLH2O( const double& pavlh2o ) 
     { 
       yravlh2o += pavlh2o; 
     }

     // yravln ************************************************
     
     inline double getYRAVLN( void ) { return yravln.total; }

     inline void setYRAVLN( const double& pyravln ) 
     { 
       yravln.total = pyravln; 
     }

     inline void updateYRAVLN( const double& pavln ) 
     { 
       yravln.total += pavln; 
     }

     // yravlnh4 ************************************************
     
     inline double getYRAVLNH4( void ) { return yravln.nh4; }

     inline void setYRAVLNH4( const double& pyravlnh4 ) 
     { 
       yravln.nh4 = pyravlnh4; 
     }

     inline void updateYRAVLNH4( const double& pavlnh4 ) 
     { 
       yravln.nh4 += pavlnh4; 
     }

     // yravlno3 ************************************************
     
     inline double getYRAVLNO3( void ) { return yravln.no3; }

     inline void setYRAVLNO3( const double& pyravlno3 ) 
     { 
       yravln.no3 = pyravlno3; 
     }

     inline void updateYRAVLNO3( const double& pavlno3 ) 
     { 
       yravln.no3 += pavlno3; 
     }
 
     // yrc2n ************************************************
     
     inline double getYRC2N( void ) { return yrc2n; }

     inline void setYRC2N( const double& pyrc2n ) 
     { 
       yrc2n = pyrc2n; 
     }

     inline void updateYRC2N( const double& pc2n ) 
     { 
       yrc2n += pc2n; 
     }

     // yrDOM.carbon *******************************************
     
     inline double getYRDOC( void ) { return yrDOM.carbon; }

     inline void setYRDOC( const double& pyrDOC ) 
     { 
       yrDOM.carbon = pyrDOC; 
     }

     inline void updateYRDOC( const double& pdoc ) 
     { 
       yrDOM.carbon += pdoc; 
     }

     // yrDOM.nitrogen *******************************************
     
     inline double getYRDON( void ) { return yrDOM.nitrogen; }

     inline void setYRDON( const double& pyrDON ) 
     { 
       yrDOM.nitrogen = pyrDON; 
     }

     inline void updateYRDON( const double& pdon ) 
     { 
       yrDOM.nitrogen += pdon; 
     }

     // yrdst10 ************************************************
     
     inline double getYRDST10( void ) { return yrdst10; }

     inline void setYRDST10( const double& pyrdst10 ) 
     { 
       yrdst10 = pyrdst10; 
     }

     inline void updateYRDST10( const double& pdst10 ) 
     { 
       yrdst10 += pdst10; 
     }

     // yreet **********************************************
     
     inline double getYREET( void ) { return yreet; }

     inline void setYREET( const double& pyreet ) 
     { 
       yreet = pyreet; 
     }

     inline void updateYREET( const double& peet ) 
     { 
       yreet += peet; 
     }

     // yrerodePOM.carbon *******************************************
     
     inline double getYRERODEPOC( void ) { return yrerodePOM.carbon; }

     inline void setYRERODEPOC( const double& pyrPOC ) 
     { 
       yrerodePOM.carbon = pyrPOC; 
     }

     inline void updateYRERODEPOC( const double& ppoc ) 
     { 
       yrerodePOM.carbon += ppoc; 
     }

     // yrerodePOM.nitrogen *******************************************
     
     inline double getYRERODEPON( void ) { return yrerodePOM.nitrogen; }

     inline void setYRERODEPON( const double& pyrPON ) 
     { 
       yrerodePOM.nitrogen = pyrPON; 
     }

     inline void updateYRERODEPON( const double& ppon ) 
     { 
       yrerodePOM.nitrogen += ppon; 
     }

     // yrh2oyld **********************************************
     
     inline double getYRH2OYIELD( void ) { return yrh2oyld; }

     inline void setYRH2OYIELD( const double& pyrh2oyld ) 
     { 
       yrh2oyld = pyrh2oyld; 
     }

     inline void updateYRH2OYIELD( const double& ph2oyld ) 
     { 
       yrh2oyld += ph2oyld; 
     }

     // yrineet **********************************************
     
     inline double getYRINEET( void ) { return yrineet; }

     inline void setYRINEET( const double& pyrineet ) 
     { 
       yrineet = pyrineet; 
     }

     inline void updateYRINEET( const double& pineet ) 
     { 
       yrineet += pineet; 
     }

     // yrlchDOM.carbon *******************************************
     
     inline double getYRLCHDOC( void ) { return yrlchDOM.carbon; }

     inline void setYRLCHDOC( const double& pyrlchDOC ) 
     { 
       yrlchDOM.carbon = pyrlchDOC; 
     }

     inline void updateYRLCHDOC( const double& plchDOC ) 
     { 
       yrlchDOM.carbon += plchDOC; 
     }

     // yrlchDOM.nitrogen *******************************************
     
     inline double getYRLCHDON( void ) { return yrlchDOM.nitrogen; }

     inline void setYRLCHDON( const double& pyrlchDON ) 
     { 
       yrlchDOM.nitrogen = pyrlchDON; 
     }

     inline void updateYRLCHDON( const double& plchDON ) 
     { 
       yrlchDOM.nitrogen += plchDON; 
     }

     // yrlchNH4 ***********************************************
     
     inline double getYRLCHNH4( void ) { return yrlchNH4; }

     inline void setYRLCHNH4( const double& pyrlchNH4 ) 
     { 
       yrlchNH4 = pyrlchNH4; 
     }

     inline void updateYRLCHNH4( const double& plchNH4 ) 
     { 
       yrlchNH4 += plchNH4; 
     }

     // yrlchNO3 ***********************************************
     
     inline double getYRLCHNO3( void ) { return yrlchNO3; }

     inline void setYRLCHNO3( const double& pyrlchNO3 ) 
     { 
       yrlchNO3 = pyrlchNO3; 
     }

     inline void updateYRLCHNO3( const double& plchNO3 ) 
     { 
       yrlchNO3 += plchNO3; 
     }

     // yrn2flx ***********************************************
     
     inline double getYRN2FLX( void ) { return yrn2flx; }

     inline void setYRN2FLX( const double& pyrn2flx ) 
     { 
       yrn2flx = pyrn2flx; 
     }

     inline void updateYRN2FLX( const double& pn2flx ) 
     { 
       yrn2flx += pn2flx; 
     }

     // yrn2oflx ***********************************************
     
     inline double getYRN2OFLX( void ) { return yrn2oflx; }

     inline void setYRN2OFLX( const double& pyrn2oflx ) 
     { 
       yrn2oflx = pyrn2oflx; 
     }

     inline void updateYRN2OFLX( const double& pn2oflx ) 
     { 
       yrn2oflx += pn2oflx; 
     }

     // yrnh3flx ***********************************************
     
     inline double getYRNH3FLX( void ) { return yrnh3flx; }

     inline void setYRNH3FLX( const double& pyrnh3flx ) 
     { 
       yrnh3flx = pyrnh3flx; 
     }

     inline void updateYRNH3FLX( const double& pnh3flx ) 
     { 
       yrnh3flx += pnh3flx; 
     }

     // yrnin **************************************************
     
     inline double getYRNINPUT( void ) { return yrnin; }

     inline void setYRNINPUT( const double& pyrnin ) 
     { 
       yrnin = pyrnin; 
     }

     inline void updateYRNINPUT( const double& pnin ) 
     { 
       yrnin += pnin; 
     }

     // yrnlost **************************************************
     
     inline double getYRNLOST( void ) { return yrnlost; }

     inline void setYRNLOST( const double& pyrnlost ) 
     { 
       yrnlost = pyrnlost; 
     }

     inline void updateYRNLOST( const double& pnlost ) 
     { 
       yrnlost += pnlost; 
     }
 
     // yrnoflx ***********************************************
     
     inline double getYRNOFLX( void ) { return yrnoflx; }

     inline void setYRNOFLX( const double& pyrnoflx ) 
     { 
       yrnoflx = pyrnoflx; 
     }

     inline void updateYRNOFLX( const double& pnoflx ) 
     { 
       yrnoflx += pnoflx; 
     }

     // yrnonorgc **********************************************
     
     inline double getYRNONORGC( void ) { return yrnonorgc; }

     inline void setYRNONORGC( const double& pyrnonorgc ) 
     { 
       yrnonorgc = pyrnonorgc; 
     }

     inline void updateYRNONORGC( const double& pnonorgc ) 
     { 
       yrnonorgc += pnonorgc; 
     }

     // yrnonorgn **********************************************
     
     inline double getYRNONORGN( void ) { return yrnonorgn; }

     inline void setYRNONORGN( const double& pyrnonorgn ) 
     { 
       yrnonorgn = pyrnonorgn; 
     }

     inline void updateYRNONORGN( const double& pnonorgn ) 
     { 
       yrnonorgn += pnonorgn; 
     }

     // yrorgc **********************************************
     
     inline double getYRORGC( void ) { return yrorgc; }

     inline void setYRORGC( const double& pyrorgc ) 
     { 
       yrorgc = pyrorgc; 
     }

     inline void updateYRORGC( const double& porgc ) 
     { 
       yrorgc += porgc; 
     }

     // yrorgn **********************************************
     
     inline double getYRORGN( void ) { return yrorgn; }

     inline void setYRORGN( const double& pyrorgn ) 
     { 
       yrorgn = pyrorgn; 
     }

     inline void updateYRORGN( const double& porgn ) 
     { 
       yrorgn += porgn; 
     }

     // yrpctp **********************************************
     
     inline double getYRPCTP( void ) { return yrpctp; }

     inline void setYRPCTP( const double& pyrpctp ) 
     { 
       yrpctp = pyrpctp; 
     }

     inline void updateYRPCTP( const double& ppctp ) 
     { 
       yrpctp += ppctp; 
     }

     // yrrgrndh2o **********************************************
     
     inline double getYRRGRNDH2O( void ) { return yrrgrndh2o; }

     inline void setYRRGRNDH2O( const double& pyrrgrndh2o ) 
     { 
       yrrgrndh2o = pyrrgrndh2o; 
     }

     inline void updateYRRGRNDH2O( const double& prgrndh2o ) 
     { 
       yrrgrndh2o += prgrndh2o; 
     }

     // yrrperc **********************************************
     
     inline double getYRRPERC( void ) { return yrrperc; }

     inline void setYRRPERC( const double& pyrrperc ) 
     { 
       yrrperc = pyrrperc; 
     }

     inline void updateYRRPERC( const double& prperc ) 
     { 
       yrrperc += prperc; 
     }

     // yrrrun **********************************************
     
     inline double getYRRRUN( void ) { return yrrrun; }

     inline void setYRRRUN( const double& pyrrrun ) 
     { 
       yrrrun = pyrrrun; 
     }

     inline void updateYRRRUN( const double& prrun ) 
     { 
       yrrrun += prrun; 
     }

     // yrsgrndh2o **********************************************
     
     inline double getYRSGRNDH2O( void ) { return yrsgrndh2o; }

     inline void setYRSGRNDH2O( const double& pyrsgrndh2o ) 
     { 
       yrsgrndh2o = pyrsgrndh2o; 
     }

     inline void updateYRSGRNDH2O( const double& psgrndh2o ) 
     { 
       yrsgrndh2o += psgrndh2o; 
     }

     // yrsmoist **********************************************
     
     inline double getYRSMOIST( void ) { return yrsmoist; }

     inline void setYRSMOIST( const double& pyrsmoist ) 
     { 
       yrsmoist = pyrsmoist; 
     }

     inline void updateYRSMOIST( const double& psmoist ) 
     { 
       yrsmoist += psmoist; 
     }

     // yrsnowinf **********************************************
     
     inline double getYRSNOWINF( void ) { return yrsnowinf; }

     inline void setYRSNOWINF( const double& pyrsnowinf ) 
     { 
       yrsnowinf = pyrsnowinf; 
     }

     inline void updateYRSNOWINF( const double& psnowinf ) 
     { 
       yrsnowinf += psnowinf; 
     }

     // yrsnowpack **********************************************
     
     inline double getYRSNOWPACK( void ) { return yrsnowpack; }

     inline void setYRSNOWPACK( const double& pyrsnowpack ) 
     { 
       yrsnowpack = pyrsnowpack; 
     }

     inline void updateYRSNOWPACK( const double& psnowpack ) 
     { 
       yrsnowpack += psnowpack; 
     }

     // yrsperc **********************************************
     
     inline double getYRSPERC( void ) { return yrsperc; }

     inline void setYRSPERC( const double& pyrsperc ) 
     { 
       yrsperc = pyrsperc; 
     }

     inline void updateYRSPERC( const double& psperc ) 
     { 
       yrsperc += psperc; 
     }

     // yrsrun **********************************************
     
     inline double getYRSRUN( void ) { return yrsrun; }

     inline void setYRSRUN( const double& pyrsrun ) 
     { 
       yrsrun = pyrsrun; 
     }

     inline void updateYRSRUN( const double& psrun ) 
     { 
       yrsrun += psrun; 
     }

     // yrtotorgc **********************************************
     
     inline double getYRTOTORGC( void ) { return yrtotorgc; }

     inline void setYRTOTORGC( const double& pyrtotorgc ) 
     { 
       yrtotorgc = pyrtotorgc; 
     }

     inline void updateYRTOTORGC( const double& ptotorgc ) 
     { 
       yrtotorgc += ptotorgc; 
     }

     // yrtotorgn **********************************************
     
     inline double getYRTOTORGN( void ) { return yrtotorgn; }

     inline void setYRTOTORGN( const double& pyrtotorgn ) 
     { 
       yrtotorgn = pyrtotorgn; 
     }

     inline void updateYRTOTORGN( const double& ptotorgn ) 
     { 
       yrtotorgn += ptotorgn; 
     }

     // yrtsoil **********************************************
     
     inline double getYRTSOIL( void ) { return yrtsoil; }

     inline void setYRTSOIL( const double& pyrtsoil ) 
     { 
       yrtsoil = pyrtsoil; 
     }

     inline void updateYRTSOIL( const double& ptsoil ) 
     { 
       yrtsoil += ptsoil; 
     }

     // yrvsm **********************************************
     
     inline double getYRVSM( void ) { return yrvsm; }

     inline void setYRVSM( const double& pyrvsm ) 
     { 
       yrvsm = pyrvsm; 
     }

     inline void updateYRVSM( const double& pvsm ) 
     { 
       yrvsm += pvsm; 
     }

     
/* *************************************************************
		 Public Variables
************************************************************* */

     // Soil thermal module
     Soilthermal60 stm;

    // Flag to indicate that soil thermal model should be run:
    //   stmflg = 0 if soil thermal model is not run
    //   stmflg = 1 if soil thermal model is run
    int stmflg; 

     
   
   
   private:
   
/* **************************************************************
		 Private Functions
************************************************************** */

     void percol( const double& rain,                  
                  const double& avlh2o );

     double rrunoff( const double& rgrndh2o );

     double srunoff( const double& elev,
                     const double& tair,
                     const double& prevtair,
                     const double& prev2tair,
		     const double& sgrndh2o );

     /* Estimated "actual" evapotransipiration (i.e. EET) as 
        described in Vorosmarty et al. (1989) Global Biogeochemical 
        Cycles 3: 241-265.  */

     double xeet( const double& rain,
                  const double& pet,
                  const double& avlh2o,
                  const int& pdm );


/* **************************************************************
		 Private Variables
************************************************************** */
     
     // Monthly abiotic immobilization
     double abioticNimmob; // (g N / (sq. meter * month))

     // Active Layer Depth in mm
     double activeLayer;
     
     // Available inorganic nitrogen (g N / sq. meter)
     InorgN60 availn;

     // Available water (mm)
     double avlh2o;  

     // Available water capacity (mm)
     double awcapmm;        

     // Dissolved organic matter (DOM)
     Biomass DOM;  // (g C or g N / sq. meter )

     // Monthly drainage (mm / month)
     double drainage;

    // Monthly soil temperature ( degrees C ) at 10 cm
    double dst10;

     // Monthly estimated actual Evapotranspiration (mm / month)
     double eet;

     // Maximum EET of current year (mm / month)
     double eetmx;

     // Erosion of particulate organic matter (POM)
     Biomass erodePOM;  // (g C or g N / (sq. meter * month)

     // Evaporation (mm)
	 double evaporation;

     // Volume of water at field capacity (mm)
     double fldcap;         

      // Water yield (mm / month)
     double h2oyld;  

     // Dissolved bicarbonate
     double HCO3;    // g C / sq. meter

     // Initial Estimated Actual Evapotranspiration (mm / month)
     double ineet;

     // Relative hydraulic conductivity through soil profile
     double kh2o;
     
     // Leaching of dissolved organic matter (DOM) from
     //   soil column
     Biomass leachDOM;  // (g C or g N / (sq. meter * month))

     // Leaching of ammonium (NH4) from soil column
     double leachNH4;   // (g N / (sq. meter * month))

     // Leaching of nitrate (NO3) from soil column
     double leachNO3;   // (g N / (sq. meter * month))

     // Mean annual volumetric soil moisture (%)
     double meanvsm;

     // Soil moisture (mm)
     double moist;   

     // N2 flux (g N / (sq. meter * month))
     double n2flux;

     // N2O flux
     double n2oflux;   // (g N / (sq. meter * month))

     double ndays[CYCLE];

     // Next month's soil temperature at 10 cm
     double nextdst10; 

     // NH3 flux
     double nh3flux;   // (g N / (sq. meter * month))

     // Total nitrogen input to soils
     double ninput;    // (g N / (sq. meter * month)) 

     // Total nitrogen lost from soils
     double nlost;     // (g N / (sq. meter * month))

     // NO flux
     double noflux;    // (g N / (sq. meter * month))

     // Nonreactive soil organic matter
     Biomass nonReactiveOrg; //  (g C or g N / sq. meter)

      // Reactive soil organic matter
     Biomass org;      //  (g C or g N / sq. meter)

     // Soil moisture as %field capacity
     double pcfc;    

     // Percent clay in soil texture
     double pctclay;        

     // Soil moisture as %total pore space
     double pctp;    

     // Percent sand in soil texture
     double pctsand;        
     
     // Percent silt in soil texture
     double pctsilt;

     // Previous month's soil temperature at 10 cm
     double prevdst10; 

     // Previous month's snow pack
     double prevspack;
     
     // Maximum EET of previous year (mm / month)
     double prveetmx;
             
     // Proportion silt and clay in soil texture
     double psiplusc;       

     // Rain runoff storage (mm / month)
     double rgrndh2o;

     // Rain percolation (excess)
     double rperc;   // (mm / month)

     // Rain Runoff (mm / month)
     double rrun;

     // Snowmelt runoff storage (mm)
     double sgrndh2o;

     // Snow melt infiltration (mm / month)
     double snowinf; 

     // Snowpack (mm)
     double snowpack;

     // Snow melt percolation (excess)
     double sperc;   // (mm / month)

     // Snow runoff
     double srun;    // (mm / month)

     // Surface runoff (mm / month)
     double surfrun;

     // Soil texture (categorical data)
     int text;              

      // Total soil organic matter
     Biomass totalOrg;   // (g C or g N / sq. meter)

     // volume of total pore space (mm)
     double totpor;         

     // Mean soil temperature (degrees C )of top 20 cm of soil 
     //   profile
     double tsoil;
     
     // Volumetric soil moisture (as %rooting depth)
     double vsm;     
 
     // Water-filled pore space offset in wetlands
	 double wfpsoff;

     // Volume of water at wilting point (mm)
     double wiltpt;         

     // wetland soil type designation (categorical data)
     int wsoil;

     // Annual sum of abioticNimmob
     double yrabNimmob;  // (g N / (sq. meter * year))

     // Annual sum of avlh2o
     double yravlh2o;

     // Annual sum of availn
     InorgN60 yravln;

     // Ratio of soil reactive organic carbon to 
     //   soil reactive organic nitrogen
     double yrc2n;

     // Annual sum of DOM
     Biomass yrDOM;   // (g C or g N / sq. meter)

     // Annual sum of dst10
     double yrdst10;

     // Annual estimated actual evapotranspiration (mm / year)
     double yreet;

     // Annual sum of erodePOM
     Biomass yrerodePOM;  // (g C or g N / sq. meter * year)

     // Annual sum of h2oyld (mm / year)
     double yrh2oyld;

     // Annual initial estimated actual evapotranspiration
     //   (mm / year)
     double yrineet;

     // Annual sum of leachDOM
     Biomass yrlchDOM;  // (g C or g N / (sq. meter * year))

     // Annual sum of leachNH4
     double yrlchNH4;   // (g N / (sq. meter * year))

     // Annual sum of leachNO3
     double yrlchNO3;   // (g N / (sq. meter * year))

     // Annual sum of n2flux
     double yrn2flx;    // (g N / (sq. meter * year))

     // Annual sum of n2oflux
     double yrn2oflx;  // (g N / (sq. meter * year))

     // Annual sum of nh3flux
     double yrnh3flx;  // (g N / (sq. meter * year))

     // Annual sum of ninput
     double yrnin;     // (g N / (sq. meter * year))

     // Annual sum of nlost
     double yrnlost;   // (g N / (sq. meter * year))

     // Annual sum of noflux
     double yrnoflx;   // (g N / (sq. meter * year))

     // Annual sum of nonReactiveOrg.carbon
     double yrnonorgc;

     // Annual sum of nonReactiveOrg.nitrogen
     double yrnonorgn;

     // Annual sum of org.carbon 
     double yrorgc;
     
     // Annual sum of org.nitrogen 
     double yrorgn;

     // Annual sum of pctp
     double yrpctp;

     // Annual sum of rgrdnh2o
     double yrrgrndh2o;

     // Annual sum of rperc
     double yrrperc;   // (mm / year)

     // Annual sum of rrun
     double yrrrun;  // (mm / year)

     // Annual sum of sgrndh2o
     double yrsgrndh2o;

     // Annual sum of moist
     double yrsmoist;

     // Annual sum of snowinf
     double yrsnowinf;      // (mm / year)

     // Annual sum of snowpack
     double yrsnowpack;

     // Annual sum of sperc
     double yrsperc; // (mm / year)

     // Annual sum of srun
     double yrsrun;  // (mm / year)

     // Annual sum of totalOrg.carbon
     double yrtotorgc;

     // Annual sum of totalOrg.nitrogen     
     double yrtotorgn;

     // Annual sum of tsoil
     double yrtsoil;

     // Annual sum of vsm
     double yrvsm;


/* *************************************************************
		 Private Parameters
************************************************************* */

     // DOM

     double DOCpar[MAXCMNT];

     double DONpar;
     double DONparcut[MAXCMNT];
     double DONpar1a[MAXCMNT];
     double DONpar1b[MAXCMNT];
     double DONpar2a[MAXCMNT];
     double DONpar2b[MAXCMNT];

     // Field capacity (%soil volume)

     double fldcapa;
     double fldcapb;
     double pcfldcap;

     // Leaching parameters

     double lchDOMpar[MAXCMNT];

     double lchNO3par;
     double lchNO3parcut[MAXCMNT];
     double lchNO3par1a[MAXCMNT];
     double lchNO3par1b[MAXCMNT];
     double lchNO3par2a[MAXCMNT];
     double lchNO3par2b[MAXCMNT];

     double maxdocCN[MAXCMNT];
     double mindocCN[MAXCMNT];


     //Proportion of total soil organic matter that is 
     //   nonreactive

     double nonReactiveOMpar[MAXCMNT];


     // Porosity of soil (%soil volume)

     double pctpor;
     double pctpora;
     double pctporb;

     //Proportion of reactive soil organic matter that is 
     //   unfrozen within rooting zone

     double propReactA[MAXCMNT];
     double propReactB[MAXCMNT];


     // Effective rooting depth (m)

     double minrootz[MAXCMNT];
     double rootz;
     double rootza[MAXCMNT];
     double rootzb[MAXCMNT];
     double rootzc[MAXCMNT];


     // Wilting point (%soil volume)

     double pcwiltpt;
     double wiltpta;
     double wiltptb;
     
};

#endif
