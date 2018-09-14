/* **************************************************************
*****************************************************************
TMCRB606B.H - object describing characteristics of soil microbes
	     used in the Terrestrial Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>   
                      
*****************************************************************
************************************************************** */

// Tmicrobe60 uses the global constants CYCLE, NUMMSAC and NUMVEG

#ifndef TMCRB606_H
#define TMCRB606_H

#include "protocol605.hpp"

#include<cstdio>

  using std::printf;

#include<iostream>

  using std::cin;
  using std::cout;
  using std::ios;
  using std::cerr;
  using std::endl;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<cstdlib>

  using std::exit;
  using std::atof;
  using std:: atoi;

#include<cmath>

  using std::exp;
  using std::log;
  using std::pow;

#include<vector>

  using std::vector;
    
#include<string>
  
  using std::string;

#ifdef CALIBRATE_TEM
  #include<ncurses.h>
#endif

#include "temconsts606.hpp"
#include "bioms423.hpp"


class Tmicrobe60 
{

   public:

     Tmicrobe60();

/* **************************************************************
		 Public Functions
************************************************************** */

     void resetEcds( const int& pcmnt, const double& psiplusc );
      
     void resetMonthlyFluxes( void );

     void resetYrFluxes( void );

     void setDQ10( const int& pdcmnt, 
                   const double& tair, 
                   const double& tsoil,
                   const double& snowpack, 
                   const int& tsoilflg );

     void setNewDQ10( const int& pdcmnt, 
                      const double& tair, 
                      const double& tsoil,
                      const double& snowpack, 
                      const int& tsoilflg );

     double setNitrifStatus( const int& dcmnt );

     double setRHMOIST( const int& pdcmnt,
                        const double& pcfldcap,
                        const double& vsm,
                        const int& moistlim );

     void setTraceGasProduction( const int& pdcmnt,
                                 const double& pctp,
                                 double& agfertn );

     void showecd( const int& pdcmnt );

     void updateDynamics( const int& pcmnt,
                          const double& pcfldcap,
                          const double& actlayer,
                          const double& soilorgc,
                          const double& soilorgn,
                          const double& soilh2o,
                          const double& vsm,
                          const double& nh4,
                          const double& nh4dep,
                          const int& moistlim,
                          const int& tillflag,
                          const double& tillfactor,
                          const double& ksoil );
     
     double yrkd( const int& nfeed,
                  const double& yrltrc,
                  const double& yrltrn,
                  const double& lcclnc );


     // "Get" and "Set" private variables and parameters
     
     // alpha *****************************************************

     inline double getALPHA( const int& pcmnt )
     {
       return alpha[pcmnt];
     };

     inline void setALPHA( const double& palpha, const int& pcmnt )
     {
       alpha[pcmnt] = palpha;
     };


     // allntrf ************************************************
     
     inline double getALLNTRF( const int& pcmnt ) 
     { 
       return allntrf[pcmnt]; 
     }

     inline void setALLNTRF( const double& pallntrf, 
                             const int& pcmnt ) 
     { 
       allntrf[pcmnt] = pallntrf; 
     }


     // ammnpar ************************************************
     
     inline double getAMMNPAR( const int& pcmnt ) 
     { 
       return ammnpar[pcmnt]; 
     }

     inline void setAMMNPAR( const double& pammnpar, 
                             const int& pcmnt ) 
     { 
       ammnpar[pcmnt] = pammnpar; 
     }

     
     // ammnvol ************************************************
     
     inline double getAMMNVOL( void ) { return ammnvol; }

     inline void setAMMNVOL( const double& pammnvol ) 
     { 
       ammnvol = pammnvol; 
     }


     // beta *****************************************************

     inline double getBETA( const int& pcmnt )
     {
       return beta[pcmnt];
     };

     inline void setBETA( const double& pbeta, const int& pcmnt )
     {
       beta[pcmnt] = pbeta;
     };


     // cnsoil *************************************************
     
     inline double getCNSOIL( const int& pcmnt ) 
     { 
       return cnsoil[pcmnt]; 
     }

     inline void setCNSOIL( const double& pcnsoil, 
                            const int& pcmnt ) 
     { 
       cnsoil[pcmnt] = pcnsoil; 
     }


     // decay **************************************************
     
     inline double getDECAY( void ) { return decay; }


     // decomp *************************************************
     
     inline double getDECOMP( void ) { return decomp; }

     inline void setDECOMP( const double& pdecomp ) 
     { 
       decomp = pdecomp; 
     }

     // denitrif ***********************************************
     
     inline double getDENITRIF( void ) { return denitrif; }

     inline void setDENITRIF( const double& pdenitrif ) 
     { 
       denitrif = pdenitrif; 
     }


     // DOCpar *************************************************
     
     inline double getDOCPAR( const int& pcmnt ) 
     { 
       return DOCpar[pcmnt]; 
     }

     inline void setDOCPAR( const double& pdocpar, 
                            const int& pcmnt ) 
     { 
       DOCpar[pcmnt] = pdocpar; 
     }


     // DOMprod.carbon *****************************************
     
     inline double getDOCPROD( void ) { return DOMprod.carbon; }

     inline void setDOCPROD( const double& pdocprod ) 
     { 
       DOMprod.carbon = pdocprod; 
     }

     // DONpar *************************************************
     
     inline double getDONPAR( void ) { return DONpar; }
     
     inline void setDONPAR( const double& pdonpar ) 
     { 
       DONpar = pdonpar; 
     }
     
     
     // DONparcut **********************************************
     
     inline double getDONPARCUT( const int& pcmnt ) 
     { 
       return DONparcut[pcmnt]; 
     }

     inline void setDONPARCUT( const double& pdonparcut, 
                               const int& pcmnt ) 
     { 
       DONparcut[pcmnt] = pdonparcut; 
     }


     // DONpar1a ***********************************************
     
     inline double getDONPAR1A( const int& pcmnt ) 
     { 
       return DONpar1a[pcmnt]; 
     }

     inline void setDONPAR1A( const double& pdonpar1a, 
                              const int& pcmnt ) 
     { 
       DONpar1a[pcmnt] = pdonpar1a; 
     }


     // DONpar1b ***********************************************
     
     inline double getDONPAR1B( const int& pcmnt ) 
     { 
       return DONpar1b[pcmnt]; 
     }

     inline void setDONPAR1B( const double& pdonpar1b, 
                              const int& pcmnt ) 
     { 
       DONpar1b[pcmnt] = pdonpar1b; 
     }


     // DONpar2a ***********************************************
     
     inline double getDONPAR2A( const int& pcmnt ) 
     { 
       return DONpar2a[pcmnt]; 
     }

     inline void setDONPAR2A( const double& pdonpar2a, 
                              const int& pcmnt ) 
     { 
       DONpar2a[pcmnt] = pdonpar2a; 
     }


     // DONpar2b ***********************************************
     
     inline double getDONPAR2B( const int& pcmnt ) 
     { 
       return DONpar2b[pcmnt]; 
     }

     inline void setDONPAR2B( const double& pdonpar2b, 
                              const int& pcmnt ) 
     { 
       DONpar2b[pcmnt] = pdonpar2b; 
     }


     // DOMprod.nitrogen ***************************************
     
     inline double getDONPROD( void ) 
     { 
       return DOMprod.nitrogen; 
     }

     inline void setDONPROD( const double& pdonprod ) 
     { 
       DOMprod.nitrogen = pdonprod; 
     }

     // DQ10 ***************************************
     
     inline double getDQ10( void ) 
     { 
       return dq10; 
     }


     // gamma *****************************************************

     inline double getGAMMA( const int& pcmnt )
     {
       return gamma[pcmnt];
     };

     inline void setGAMMA( const double& pgamma, const int& pcmnt )
     {
       gamma[pcmnt] = pgamma;
     };


     // grossnmin **********************************************
     
     inline double getGROSSNMIN( void ) { return grossnmin; }

     inline void setGROSSNMIN( const double& pgnmin ) 
     { 
       grossnmin = pgnmin; 
     }

     // immnh4 *************************************************
     
     inline double getIMMNH4( void ) { return immnh4; }

     inline void setIMMNH4( const double& pimmnh4 ) 
     { 
       immnh4 = pimmnh4; 
     }

     // immob **************************************************
     
     inline double getIMMOB( void ) { return immob; }

     inline void setIMMOB( const double& pimmob ) 
     { 
       immob = pimmob; 
     }

     // initntrf ***********************************************
     
     inline double getINITNTRF( const int& pcmnt ) 
     { 
       return initntrf[pcmnt]; 
     }

     inline void setINITNTRF( const double& pinntrf, 
                              const int& pcmnt ) 
     { 
       initntrf[pcmnt] = pinntrf; 
     }


     // kd *****************************************************
     
     inline double getKD( void ) { return kd; }

     inline void setKD( const double& pkd ) { kd = pkd; }


     // kdcut **************************************************
     
     inline double getKDCUT( const int& pcmnt ) 
     { 
       return kdcut[pcmnt]; 
     }

     inline void setKDCUT( const double& pkdcut, 
                           const int& pcmnt ) 
     { 
       kdcut[pcmnt] = pkdcut; 
     }


     // kd1a ***************************************************
     
     inline double getKD1A( const int& pcmnt ) 
     { 
       return kd1a[pcmnt]; 
     }

     inline void setKD1A( const double& pkd1a, 
                          const int& pcmnt ) 
     { 
       kd1a[pcmnt] = pkd1a; 
     }


     // kd1b ***************************************************
     
     inline double getKD1B( const int& pcmnt ) 
     { 
       return kd1b[pcmnt]; 
     }

     inline void setKD1B( const double& pkd1b, 
                          const int& pcmnt ) 
     { 
       kd1b[pcmnt] = pkd1b; 
     }


     // kd2a ***************************************************
     
     inline double getKD2A( const int& pcmnt ) 
     { 
       return kd2a[pcmnt]; 
     }

     inline void setKD2A( const double& pkd2a, 
                          const int& pcmnt ) 
     { 
       kd2a[pcmnt] = pkd2a; 
     }


     // kd2b ***************************************************
     
     inline double getKD2B( const int& pcmnt ) 
     { 
       return kd2b[pcmnt]; 
     }

     inline void setKD2B( const double& pkd2b, 
                          const int& pcmnt ) 
     { 
       kd2b[pcmnt] = pkd2b; 
     }


     // kdc ****************************************************
     
     inline double getKDC( void ) { return kdc; }

     inline void setKDC( const double& pkdc ) { kdc = pkdc; }


     // kn2 ****************************************************
     
     inline double getKN2( const int& pcmnt ) 
     { 
       return kn2[pcmnt]; 
     }

     inline void setKN2( const double& pkn2, 
                         const int& pcmnt ) 
     { 
       kn2[pcmnt] = pkn2; 
     }


     // moistmax ***********************************************
     
     inline double getMOISTMAX( const int& pcmnt ) 
     { 
       return moistmax[pcmnt]; 
     }

     inline void setMOISTMAX( const double& pmoistmax, 
                              const int& pcmnt ) 
     { 
       moistmax[pcmnt] = pmoistmax; 
     }


     // moistmin ***********************************************
     
     inline double getMOISTMIN( const int& pcmnt ) 
     { 
       return moistmin[pcmnt]; 
     }

     inline void setMOISTMIN( const double& pmoistmin, 
                              const int& pcmnt ) 
     { 
       moistmin[pcmnt] = pmoistmin; 
     }


     // moistopt ***********************************************
     
     inline double getMOISTOPT( const int& pcmnt ) 
     { 
       return moistopt[pcmnt]; 
     }

     inline void setMOISTOPT( const double& pmoistopt, 
                              const int& pcmnt ) 
     { 
       moistopt[pcmnt] = pmoistopt; 
     }


     // n2oprod ************************************************
     
     inline double getN2OPROD( void ) { return n2oprod; }

     inline void setN2OPROD( const double& pn2oprod ) 
     { 
       n2oprod = pn2oprod; 
     }

     // n2prod *************************************************
     
     inline double getN2PROD( void ) { return n2prod; }

     inline void setN2PROD( const double& pn2prod ) 
     { 
       n2prod = pn2prod; 
     }

     // ndecomp ************************************************
     
     inline double getNDECOMP( void ) { return ndecomp; }

     inline void setNDECOMP( const double& pndecomp ) 
     { 
       ndecomp = pndecomp; 
     }

     // netnmin ************************************************
     
     inline double getNETNMIN( void ) { return netnmin; }

     inline void setNETNMIN( const double& pnetnmin ) 
     { 
       netnmin = pnetnmin; 
     }


     // nfix ***************************************************
     
     inline double getNFIX( void ) { return nfix; }

     inline void setNFIX( const double& pnfix ) 
     { 
       nfix = pnfix; 
     }


     // nfixpar ************************************************
     
     inline double getNFIXPAR( const int& pcmnt ) 
     { 
       return nfixpar[pcmnt]; 
     }

     inline void setNFIXPAR( const double& pnfixpar, 
                             const int& pcmnt ) 
     { 
       nfixpar[pcmnt] = pnfixpar; 
     }


     // nh4imm *************************************************
     
     inline double getNH4IMM( void ) { return nh4imm; }

     inline void setNH4IMM( const double& pnh4imm ) 
     { 
       nh4imm = pnh4imm; 
     }


     // nh4immcut **********************************************
     
     inline double getNH4IMMCUT( const int& pcmnt ) 
     { 
       return nh4immcut[pcmnt]; 
     }

     inline void setNH4IMMCUT( const double& pnh4immcut, 
                               const int& pcmnt ) 
     { 
       nh4immcut[pcmnt] = pnh4immcut; 
     }


     // nh4imm1a ***********************************************
     
     inline double getNH4IMM1A( const int& pcmnt ) 
     { 
       return nh4imm1a[pcmnt]; 
     }

     inline void setNH4IMM1A( const double& pnh4imm1a, 
                              const int& pcmnt ) 
     { 
       nh4imm1a[pcmnt] = pnh4imm1a; 
     }


     // nh4imm1b ***********************************************
     
     inline double getNH4IMM1B( const int& pcmnt ) 
     { 
       return nh4imm1b[pcmnt]; 
     }

     inline void setNH4IMM1B( const double& pnh4imm1b, 
                              const int& pcmnt ) 
     { 
       nh4imm1b[pcmnt] = pnh4imm1b; 
     }


     // nh4imm2a ***********************************************
     
     inline double getNH4IMM2A( const int& pcmnt ) 
     { 
       return nh4imm2a[pcmnt]; 
     }

     inline void setNH4IMM2A( const double& pnh4imm2a, 
                              const int& pcmnt ) 
     { 
       nh4imm2a[pcmnt] = pnh4imm2a; 
     }


     // nh4imm2b ***********************************************
     
     inline double getNH4IMM2B( const int& pcmnt ) 
     { 
       return nh4imm2b[pcmnt]; 
     }

     inline void setNH4IMM2B( const double& pnh4imm2b, 
                              const int& pcmnt ) 
     { 
       nh4imm2b[pcmnt] = pnh4imm2b; 
     }


     // nimm ***************************************************
     
     inline double getNIMM( void ) { return nimm; }


     // nitrif *************************************************
     
     inline double getNITRIF( void ) { return nitrif; }

     inline void setNITRIF( const double& pnitrif ) 
     { 
       nitrif = pnitrif; 
     }


     // noprod *************************************************
     
     inline double getNOPROD( void ) { return noprod; }

     inline void setNOPROD( const double& pnoprod ) 
     { 
       noprod = pnoprod; 
     }


     // no3prod ************************************************
     
     inline double getNO3PROD( void ) { return no3prod; }

     inline void setNO3PROD( const double& pno3prod ) 
     { 
       no3prod = pno3prod; 
     }


     // ntrfpar ************************************************
     
     inline double getNTRFPAR( void ) { return ntrfpar; }

     inline void setNTRFPAR( const double& pntrfpar ) 
     { 
       ntrfpar = pntrfpar; 
     }


     // ntrfparcut *********************************************
     
     inline double getNTRFPARCUT( const int& pcmnt ) 
     { 
       return ntrfparcut[pcmnt]; 
     }
    
     inline void setNTRFPARCUT( const double& pntrfparcut, 
                                const int& pcmnt ) 
     { 
       ntrfparcut[pcmnt] = pntrfparcut; 
     }


     // ntrfpar1a **********************************************
     
     inline double getNTRFPAR1A( const int& pcmnt ) 
     { 
       return ntrfpar1a[pcmnt]; 
     }

     inline void setNTRFPAR1A( const double& pntrfpar1a, 
                               const int& pcmnt ) 
     { 
       ntrfpar1a[pcmnt] = pntrfpar1a; 
     }


     // ntrfpar1b **********************************************
     
     inline double getNTRFPAR1B( const int& pcmnt ) 
     { 
       return ntrfpar1b[pcmnt]; 
     }

     inline void setNTRFPAR1B( const double& pntrfpar1b, 
                               const int& pcmnt ) 
     { 
       ntrfpar1b[pcmnt] = pntrfpar1b; 
     }


     // ntrfpar2a **********************************************
     
     inline double getNTRFPAR2A( const int& pcmnt ) 
     { 
       return ntrfpar2a[pcmnt]; 
     }
     
     inline void setNTRFPAR2A( const double& pntrfpar2a, 
                               const int& pcmnt ) 
     { 
       ntrfpar2a[pcmnt] = pntrfpar2a; 
     }

     // ntrfpar2b **********************************************

     inline double getNTRFPAR2B( const int& pcmnt ) 
     { 
       return ntrfpar2b[pcmnt]; 
     }

     inline void setNTRFPAR2B( const double& pntrfpar2b, 
                               const int& pcmnt ) 
     { 
       ntrfpar2b[pcmnt] = pntrfpar2b; 
     }


     // propftos ***********************************************
     
     inline double getPROPFTOS( const int& pcmnt ) 
     { 
       return propftos[pcmnt]; 
     }

     inline void setPROPFTOS( const double& ppropftos, 
                              const int& pcmnt ) 
     { 
       propftos[pcmnt] = ppropftos; 
     }


     // qref *****************************************************

     inline double getQREF( const int& pcmnt )
     {
       return qref[pcmnt];
     };

     inline void setQREF( const double& pqref, const int& pcmnt )
     {
       qref[pcmnt] = pqref;
     };

     // rh *****************************************************
     
     inline double getRH( void ) { return rh; }

     inline void setRH( const double& prh ) 
     { 
       rh = prh; 
     }

     // tgmpar *************************************************
     
     inline double getTGMPAR( const int& pcmnt ) 
     { 
       return tgmpar[pcmnt]; 
     }

     inline void setTGMPAR( const double& ptgmpar, 
                            const int& pcmnt ) 
     { 
       tgmpar[pcmnt] = ptgmpar; 
     }
    
     // tref *****************************************************

     inline double getTREF( const int& pcmnt )
     {
       return tref[pcmnt];
     };

     inline void setTREF( const double& ptref, const int& pcmnt )
     {
       tref[pcmnt] = ptref;
     };

     // yrammnvol **********************************************
     
     inline double getYRAMMNVOL( void ) { return yrammnvol; }

     inline void setYRAMMNVOL( const double& pyrammnvol ) 
     { 
       yrammnvol = pyrammnvol; 
     }

     inline void updateYRAMMNVOL( const double& pammnvol ) 
     { 
       yrammnvol += pammnvol; 
     }

     // yrdecomp **********************************************
     
     inline double getYRDECOMP( void ) { return yrdecomp; }

     inline void setYRDECOMP( const double& pyrdecomp ) 
     { 
       yrdecomp = pyrdecomp; 
     }

     inline void updateYRDECOMP( const double& pdecomp ) 
     { 
       yrdecomp += pdecomp; 
     }

     // yrdenitrf **********************************************
     
     inline double getYRDENITRF( void ) { return yrdenitrf; }

     inline void setYRDENITRF( const double& pyrdenitrf ) 
     { 
       yrdenitrf = pyrdenitrf; 
     }

     inline void updateYRDENITRF( const double& pdenitrf ) 
     { 
       yrdenitrf += pdenitrf; 
     }

     // yrDOMprod.carbon *****************************************
     
     inline double getYRDOCPRD( void ) { return yrDOMprod.carbon; }

     inline void setYRDOCPRD( const double& pyrdocprod ) 
     { 
       yrDOMprod.carbon = pyrdocprod; 
     }

     inline void updateYRDOCPRD( const double& pdocprod ) 
     { 
       yrDOMprod.carbon += pdocprod; 
     }
     
     // yrDOMprod.nitrogen *****************************************
     
     inline double getYRDONPRD( void ) { return yrDOMprod.nitrogen; }

     inline void setYRDONPRD( const double& pyrdonprod ) 
     { 
       yrDOMprod.nitrogen = pyrdonprod; 
     }

     inline void updateYRDONPRD( const double& pdonprod ) 
     { 
       yrDOMprod.nitrogen += pdonprod; 
     }

     // yrgmin **********************************************
     
     inline double getYRGMIN( void ) { return yrgmin; }

     inline void setYRGMIN( const double& pyrgmin ) 
     { 
       yrgmin = pyrgmin; 
     }

     inline void updateYRGMIN( const double& pgmin ) 
     { 
       yrgmin += pgmin; 
     }

     // yrimmnh4 **********************************************
     
     inline double getYRIMMNH4( void ) { return yrimmnh4; }

     inline void setYRIMMNH4( const double& pyrimmnh4 ) 
     { 
       yrimmnh4 = pyrimmnh4; 
     }

     inline void updateYRIMMNH4( const double& pimmnh4 ) 
     { 
       yrimmnh4 += pimmnh4; 
     }

    // yrimmb **********************************************
     
     inline double getYRIMMB( void ) { return yrimmb; }

     inline void setYRIMMB( const double& pyrimmb ) 
     { 
       yrimmb = pyrimmb; 
     }

     inline void updateYRIMMB( const double& pimmb ) 
     { 
       yrimmb += pimmb; 
     }

    // yrn2oprd **********************************************
     
     inline double getYRN2OPRD( void ) { return yrn2oprd; }

     inline void setYRN2OPRD( const double& pyrn2oprd ) 
     { 
       yrn2oprd = pyrn2oprd; 
     }

     inline void updateYRN2OPRD( const double& pn2oprd ) 
     { 
       yrn2oprd += pn2oprd; 
     }

    // yrn2prd **********************************************
     
     inline double getYRN2PRD( void ) { return yrn2prd; }

     inline void setYRN2PRD( const double& pyrn2prd ) 
     { 
       yrn2prd = pyrn2prd; 
     }

     inline void updateYRN2PRD( const double& pn2prd ) 
     { 
       yrn2prd += pn2prd; 
     }

     // yrndecomp **********************************************
     
     inline double getYRNDECOMP( void ) { return yrndecomp; }

     inline void setYRNDECOMP( const double& pyrndecomp ) 
     { 
       yrndecomp = pyrndecomp; 
     }

     inline void updateYRNDECOMP( const double& pndecomp ) 
     { 
       yrndecomp += pndecomp; 
     }

     // yrnmin *************************************************
     
     inline double getYRNMIN( void ) { return yrnmin; }

     inline void setYRNMIN( const double& pyrnmin ) 
     { 
       yrnmin = pyrnmin; 
     }

     inline void updateYRNMIN( const double& pnmin ) 
     { 
       yrnmin += pnmin; 
     }

     // yrnfix *************************************************
     
     inline double getYRNFIX( void ) { return yrnfix; }

     inline void setYRNFIX( const double& pyrnfix ) 
     { 
       yrnfix = pyrnfix; 
     }

     inline void updateYRNFIX( const double& pnfix ) 
     { 
       yrnfix += pnfix; 
     }

     // yrnitrif *************************************************
     
     inline double getYRNITRIF( void ) { return yrnitrif; }

     inline void setYRNITRIF( const double& pyrnitrif ) 
     { 
       yrnitrif = pyrnitrif; 
     }

     inline void updateYRNITRIF( const double& pnitrif ) 
     { 
       yrnitrif += pnitrif; 
     }

    // yrnoprd **********************************************
     
     inline double getYRNOPRD( void ) { return yrnoprd; }

     inline void setYRNOPRD( const double& pyrnoprd ) 
     { 
       yrnoprd = pyrnoprd; 
     }

     inline void updateYRNOPRD( const double& pnoprd ) 
     { 
       yrnoprd += pnoprd; 
     }

    // yrno3prd **********************************************
     
     inline double getYRNO3PRD( void ) { return yrno3prd; }

     inline void setYRNO3PRD( const double& pyrno3prd ) 
     { 
       yrno3prd = pyrno3prd; 
     }

     inline void updateYRNO3PRD( const double& pno3prd ) 
     { 
       yrno3prd += pno3prd; 
     }

    // yrrh **********************************************
     
     inline double getYRRH( void ) { return yrrh; }

     inline void setYRRH( const double& pyrrh ) 
     { 
       yrrh = pyrrh; 
     }

     inline void updateYRRH( const double& prh ) 
     { 
       yrrh += prh; 
     }


/* **************************************************************
		 Public Variables
************************************************************** */

     double relntrf;         // nitrif / netnmin




   private:

/* **************************************************************
		 Private Functions
************************************************************** */

     double gminFastxClm( const double& soilorgc,
                          const double& soilorgn,
                          const double& rh );

     double gminSlowxClm( const int& pdcmnt,
                          const double& soilorgc,
                          const double& soilorgn,
                          const double& rh );

     double nimmFastxClm( const int& pdcmnt,
                          const double& nimm,
                          const double& soilh2o,
                          const double& availn,
                          const double& decay,
                          const double& rh,
                          const double& ksoil );

     double nminxclm( const int& pdcmnt,
                      const double& soilh2o,
                      const double& soilorgc,
                      const double& soilorgn,
                      const double& availn,
                      const double& decay,
                      const double& rh,
                      const double& ksoil );

     double ntrfxclm( const int& pdcmnt,
                      const double& soilh2o,
                      const double& nh4,
                      const double& nmin,
                      const double& ksoil );

     double rhxclm( const double& soilorgc,
                    const double& dq10,
                    const double& moist );

   
/* **************************************************************
		 Private Variables
************************************************************** */
     
      // Ammonia Volatilization (g N / (sq. meter * month))
      double ammnvol; 

      // Decomposition (g C / (sq. meter * month))
      double decomp;
      
      // Denitrification (g N / (sq. meter * month))
      double denitrif; 

      // Dissolved Organic Matter (DOM) production
      Biomass DOMprod; // (g C or g N / (sq. meter * month))

     // Effect of temperature on decomposition
     double dq10;

     // Gross nitrogen mineralization
     double grossnmin;  // (g N / (sq. meter * month))

     // Ammonium uptake or "immobilzation" by microbes
     double immnh4;   // (g N / (sq. meter * month))

     // Total nitrogen uptake or "immobilzation" by microbes
     double immob;  // (g N / (sq. meter * month))

     // N2O production
     double n2oprod;  // (g N / (sq. meter * month))

     // N2 production
     double n2prod;  // (g N / (sq. meter * month))

     // Nitrogen in Decomposition      
     double ndecomp; // (g N / (sq. meter * month))

     // Net nitrogen mineralization
     double netnmin; // (g N / (sq. meter * month))

     // Nitrogen fixation by free-living microbes
     double nfix;    // (g N / (sq. meter * month))

     // Nitrification
     double nitrif;  // (g N / (sq. meter * month))

     // NO production
     double noprod;   // (g N / (sq. meter * month))

      // NO3 production
      double no3prod;  // (g N / (sq. meter * month))

     // Heterotrophic respiration
     double rh;  // (g C / (sq. meter * month))

     // Annual sum of ammnvol
     double yrammnvol;       // (g N / (sq. meter * year))

     // Annual sum of decomp
     double yrdecomp;     // (g C / (sq. meter * year))

     // Annual sum of denitrif
     double yrdenitrf;       // (g N / (sq. meter * year))

     // Annual sum of DOM
     Biomass yrDOMprod;     // (g C or g N / (sq. meter * year))

     // Annual sum of grossnmin
     double yrgmin;            // (g N / (sq. meter * year))

     // Annual sum of immnh4
     double yrimmnh4;        // (g N / (sq. meter * year))

     // Annual sum of immob
     double yrimmb;        // (g N / (sq. meter * year))

     // Annual sum of n2oprod
     double yrn2oprd;        // (g N / (sq. meter * year))

     // Annual sum of n2prod
     double yrn2prd;        // (g N / (sq. meter * year))

     // Annual sum of ndecomp
     double yrndecomp;      // (g N / (sq. meter * year))

     // Annual sum of netnmin
     double yrnmin;         // (g N / (sq. meter * year))

     // Annual sum of nfix
     double yrnfix;         // (g N / (sq. meter * year))

     // Annual sum of nitrif
     double yrnitrif;       // (g N / (sq. meter * year))

     // Annual sum of noprod
     double yrnoprd;         // (g N / (sq. meter * year))

     // Annual sum of no3prod
     double yrno3prd;        // (g N / (sq. meter * year))

     // Annual sum of rh
     double yrrh;       // (g C / (sq. meter * year))


/* *************************************************************
		 Private Parameters
************************************************************* */

     double alpha[MAXCMNT];

     // Ammonia volatilization

     double ammnpar[MAXCMNT];

     double beta[MAXCMNT];

     double cnsoil[MAXCMNT];

     // Parameter representing the quality of soil organic matter

     double decay;

     double DOCpar[MAXCMNT];

     double DONpar;
     double DONparcut[MAXCMNT];
     double DONpar1a[MAXCMNT];
     double DONpar1b[MAXCMNT];
     double DONpar2a[MAXCMNT];
     double DONpar2b[MAXCMNT];

     double gamma[MAXCMNT];

     // Biome-specific decomposition parameters for function rhxclm

     double kd;
     double kdcut[MAXCMNT];
     double kd1a[MAXCMNT];
     double kd1b[MAXCMNT];
     double kd2a[MAXCMNT];
     double kd2b[MAXCMNT];
     double kdc;

     double kdin[MAXNMSAC];     // kd values read in from file
     double kdsave[MAXNMSAC];   // kd values saved to a file

     // Biome-specific half saturation parameter for function
     //   nminxclm describing the effect of available nitrogen
     //   on microbial nitrogen uptake

     double kn2[MAXCMNT];

     // Biome-specific parameters describing the influence of 
     //   soil moisture on decomposition (i.e., moist)

     double moistmin[MAXCMNT];
     double moistopt[MAXCMNT];
     double moistmax[MAXCMNT];

     // Biome-specific nitrification parameters

     double ntrfpar;
     double ntrfparcut[MAXCMNT];
     double ntrfpar1a[MAXCMNT];
     double ntrfpar1b[MAXCMNT];
     double ntrfpar2a[MAXCMNT];
     double ntrfpar2b[MAXCMNT];
     
     double allntrf[MAXCMNT];
     double initntrf[MAXCMNT];


    // N fixation parameter

     double nfixpar[MAXCMNT];


     // Biome-specific microbial immobilization parameters for
     //   function nminxclm

     double nh4imm;
     double nh4immcut[MAXCMNT];
     double nh4imm1a[MAXCMNT];
     double nh4imm1b[MAXCMNT];
     double nh4imm2a[MAXCMNT];
     double nh4imm2b[MAXCMNT];

     double nimm;
     
     double propftos[MAXCMNT];

     double qref[MAXCMNT];

     double rhq10[MAXCMNT];

     double tgmpar[MAXCMNT];

     double tref[MAXCMNT];


};

#endif

