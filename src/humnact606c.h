/* *************************************************************
****************************************************************
HUMNACT606C.H - describes human disturbances to natural ecosystems

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

****************************************************************
************************************************************* */

#ifndef HUMNACT606_H
#define HUMNACT606_H

const double GDDMIN = 5.00000;
const double GDDSEED = 300.0;
const double GDDHARVST = 2000.0;

#include "temconsts606.hpp"
#include "bioms423.hpp"  // Humnact60 uses Biomass class
#include "tveg606c.h"     // Humanact60 uses Tveg60 class

//class Humanact60 : public ProcessXML60
class Humanact60
{

  public:

     Humanact60();

/* **************************************************************
		 Public Functions
************************************************************** */

     void conversion( const int& pdcmnt,
                      const double& vegc, 
                      const double& vstrn,
                      const double& vston, 
                      const double& solc, 
                      const double& soiln );

     void createWoodProducts( const int& outyr,
                              const double& vegc, 
                              const double& vstrn,
                              const double& vston );
                      
     void decayProducts( void );

     void frostDamage( const double& vegc, 
                       const double& vstrn,
                       const double& vston );
         
     void grazing( const double& vegc, const double& strn );

     void harvest( const int& pdm,
                   const double& vegc, 
                   const double& vstrn,
                   const double& vston );
                       
     void resetMonthlyDisturbFluxes( void );

     void resetMonthlyFluxes( void );
         
     void resetPROD( void );

     void resetYrFluxes( void );
     
     void setAgricFlags( ofstream& rflog1 );

     void setFireNDEP( void );

     void setNoCrops( const int& pdm );
     
     void setNoGrazing( void );

     void setNoWoodProducts( const int& pdyr );
     
     void updateCropResidue( void );
     
     void updateCropResidueFluxes( void );
     
     void updateProducts( void );
     
     void updateTotalProductFormation( void );


     // "Get" and "Set" private variables

     // animalresp *********************************************

     inline double getANIMALRESP( void ) { return animalresp; }

     inline void setANIMALRESP( const double& panimalresp )
     {
       animalresp = panimalresp; }


     // c2n ****************************************************
     
     inline double getC2N( void ) { return c2n; }

     inline void setC2N( const double& pc2n ) { c2n = pc2n; }

     
     // cflux **************************************************
     
     inline double getCFLUX( void ) { return cflux; }
     
     inline void setCFLUX( const double& pcflx ) 
     { 
       cflux = pcflx; 
     }

     
     // convrtflx.carbon ***************************************
     
     inline double getCONVRTFLXC( void ) 
     { 
       return convrtflx.carbon; 
     }

     inline void setCONVRTFLXC( const double& pcnvrtflxc ) 
     { 
       convrtflx.carbon = pcnvrtflxc; 
     }


     // convrtflx.nitrogen *************************************
     
     inline double getCONVRTFLXN( void ) 
     { 
       return convrtflx.nitrogen; 
     }

     inline void setCONVRTFLXN( const double& pcnvrtflxn ) 
     { 
       convrtflx.nitrogen = pcnvrtflxn; 
     }


     // cropprod.carbon ****************************************
     
     inline double getCROPPRODC( void ) 
     { 
       return cropprod.carbon; 
     }

     inline void setCROPPRODC( const double& pcrpprdc ) 
     { 
       cropprod.carbon = pcrpprdc; 
     }


     // cropprod.nitrogen **************************************
     
     inline double getCROPPRODN( void ) 
     { 
       return cropprod.nitrogen; 
     }

     inline void setCROPPRODN( const double& pcrpprdn ) 
     { 
       cropprod.nitrogen = pcrpprdn; 
     }


     // cropprveetmx *******************************************
     
     inline double getCROPPRVEETMX( void ) 
     { 
       return cropprveetmx; 
     }

     inline void setCROPPRVEETMX( const double& pcrpprveetmx ) 
     { 
       cropprveetmx = pcrpprveetmx; 
     }


     // cropprvleafmx ******************************************
     
     inline double getCROPPRVLEAFMX( void ) 
     { 
       return cropprvleafmx; 
     }

     inline void setCROPPRVLEAFMX( const double& pcrpprvleafmx ) 
     { 
       cropprvleafmx = pcrpprvleafmx; 
     }


     // cropprvpetmx *******************************************
     
     inline double getCROPPRVPETMX( void ) 
     { 
       return cropprvpetmx; 
     }

     inline void setCROPPRVPETMX( const double& pcrpprvpetmx ) 
     { 
       cropprvpetmx = pcrpprvpetmx; 
     }


     // cropResidue.carbon *************************************
     
     inline double getCROPRESIDUEC( void ) 
     { 
       return cropResidue.carbon; 
     }

     inline void setCROPRESIDUEC( const double& pcrpresiduec ) 
     { 
       cropResidue.carbon = pcrpresiduec; 
     }


     // cropResidue.nitrogen ***********************************
     
     inline double getCROPRESIDUEN( void ) 
     { 
       return cropResidue.nitrogen; 
     }

     inline void setCROPRESIDUEN( const double& pcrpresiduen ) 
     { 
       cropResidue.nitrogen = pcrpresiduen; 
     }


     // cropResidueFlux.carbon *********************************
     
     inline double getCROPRESIDUEFLXC( void ) 
     { 
       return cropResidueFlux.carbon; 
     }



     // cropResidueFlux.nitrogen *******************************
     
     inline double getCROPRESIDUEFLXN( void ) 
     { 
       return cropResidueFlux.nitrogen; 
     }


     // cropseedC **********************************************
     
     inline double getCROPSEEDC( const int& pcmnt ) 
     { 
       return cropseedC[pcmnt]; 
     }

     inline void setCROPSEEDC( const double& pcropseedc,
                               const int& pcmnt ) 
     { 
       cropseedC[pcmnt] = pcropseedc; 
     }

 
     // cropseedSTON *******************************************
     
     inline double getCROPSEEDSTON( const int& pcmnt ) 
     { 
       return cropseedSTON[pcmnt]; 
     }

     inline void setCROPSEEDSTON( const double& pcropseedston,
                                  const int& pcmnt ) 
     { 
       cropseedSTON[pcmnt] = pcropseedston; 
     }

 
     // cropseedSTRN *******************************************
     
     inline double getCROPSEEDSTRN( const int& pcmnt ) 
     { 
       return cropseedSTRN[pcmnt]; 
     }

     inline void setCROPSEEDSTRN( const double& pcropseedstrn,
                                  const int& pcmnt ) 
     { 
       cropseedSTRN[pcmnt] = pcropseedstrn; 
     }

 
     // croptopt ***********************************************
     
     inline double getCROPTOPT( void ) { return croptopt; }

     inline void setCROPTOPT( const double& pcrptopt ) 
     { 
       croptopt = pcrptopt; 
     }


     // firendep ***********************************************
     
     inline double getFIRENH4DEP( void ) 
     { 
       return firendep.nh4; 
     }

     inline void setFIRENH4DEP( const double& pfirendep ) 
     { 
       firendep.nh4 = pfirendep; 
     }


    // firendep ***********************************************

    inline double getFIRENO3DEP( void )
    {
      return firendep.no3;
    }

    inline void setFIRENO3DEP( const double& pfirendep )
    {
      firendep.no3 = pfirendep;
    }

    // firendep ***********************************************

    inline double getFIRENTOTDEP( void )
    {
      return firendep.total;
    }

    inline void setFIRENTOTDEP( const double& pfirendep )
    {
      firendep.total = pfirendep;
    }

     // forage.carbon *********************************

     inline double getFORAGEC( void )
     {
       return forage.carbon;
     }

     inline void setFORAGEC( const double& pforagec )
     {
       forage.carbon = pforagec;
     }

     // forage.nitrogen *********************************

     inline double getFORAGEN( void )
     {
       return forage.nitrogen;
     }

     inline void setFORAGEN( const double& pforagen )
     {
       forage.nitrogen = pforagen;
     }


     // formCropResidue.carbon *********************************
     
     inline double getFORMCROPRESIDUEC( void ) 
     { 
       return formCropResidue.carbon; 
     }

     inline void setFORMCROPRESIDUEC( const double& pfrmcrpresiduec ) 
     { 
       formCropResidue.carbon = pfrmcrpresiduec; 
     }


     // formCropResidue.nitrogen *******************************
     
     inline double getFORMCROPRESIDUEN( void ) 
     { 
       return formCropResidue.nitrogen; 
     }

     inline void setFORMCROPRESIDUEN( const double& pfrmcrpresiduen ) 
     { 
       formCropResidue.nitrogen = pfrmcrpresiduen; 
     }


     // formPROD10.carbon **************************************
     
     inline double getFORMPROD10C( void ) 
     { 
       return formPROD10.carbon; 
     }

     inline void setFORMPROD10C( const double& pfrmprod10c ) 
     { 
       formPROD10.carbon = pfrmprod10c; 
     }


     // formPROD10.nitrogen ************************************
     
     inline double getFORMPROD10N( void ) 
     { 
       return formPROD10.nitrogen; 
     }

     inline void setFORMPROD10N( const double& pfrmprod10n ) 
     { 
       formPROD10.nitrogen = pfrmprod10n; 
     }


     // formPROD100.carbon *************************************
     
     inline double getFORMPROD100C( void ) 
     { 
       return formPROD100.carbon; 
     }

     inline void setFORMPROD100C( const double& pfrmprod100c ) 
     { 
       formPROD100.carbon = pfrmprod100c; 
     }


     // formPROD100.nitrogen ***********************************
     
     inline double getFORMPROD100N( void ) 
     { 
       return formPROD100.nitrogen; 
     }

     inline void setFORMPROD100N( const double& pfrmprod100n ) 
     { 
       formPROD100.nitrogen = pfrmprod100n; 
     }


     // formTOTPROD.carbon *************************************
     
     inline double getFORMTOTPRODC( void ) 
     { 
       return formTOTPROD.carbon; 
     }

     inline void setFORMTOTPRODC( const double& pfrmtotprodc ) 
     { 
       formTOTPROD.carbon = pfrmtotprodc; 
     }


     // formTOTPROD.nitrogen ***********************************
     
     inline double getFORMTOTPRODN( void ) 
     { 
       return formTOTPROD.nitrogen; 
     }

     inline void setFORMTOTPRODN( const double& pfrmtotprodn ) 
     { 
       formTOTPROD.nitrogen = pfrmtotprodn; 
     }


     // FRI ****************************************************
     
     inline int getFRI( void ) { return FRI; }

     inline void setFRI( const int& pfri ) { FRI = pfri; }


     // growdd *************************************************
     
     inline double getGROWDD( void ) { return growdd; }

     inline void setGROWDD( const double& pgrowdd ) 
     { 
       growdd = pgrowdd; 
     }


     // harvstC *********************************************
     
     inline double getHARVSTC( const int& pcmnt ) 
     { 
       return harvstC[pcmnt]; 
     }

     inline void setHARVSTC( const double& pharvstC, 
                             const int& pcmnt ) 
     { 
       harvstC[pcmnt] = pharvstC; 
     }


     // harvstN *********************************************
     
     inline double getHARVSTN( const int& pcmnt ) 
     { 
       return harvstN[pcmnt]; 
     }

     inline void setHARVSTN( const double& pharvstN, 
                                const int& pcmnt ) 
     { 
       harvstN[pcmnt] = pharvstN; 
     }


     // initPROD1.carbon ***************************************
     
     inline double getINITPROD1C( const int& pdm ) 
     { 
       return initPROD1[pdm].carbon; 
     }

     inline void setINITPROD1C( const double& pinprod1c,
                                const int& pdm ) 
     { 
       initPROD1[pdm].carbon = pinprod1c; 
     }


     // initPROD1.nitrogen *************************************
     
     inline double getINITPROD1N( const int& pdm ) 
     { 
       return initPROD1[pdm].nitrogen; 
     }

     inline void setINITPROD1N( const double& pinprod1n,
                                const int& pdm ) 
     { 
       initPROD1[pdm].nitrogen = pinprod1n; 
     }


     // initPROD10[].carbon ************************************
     
     inline double getINITPROD10C( const int& i ) 
     { 
       return initPROD10[i].carbon; 
     }

     inline void setINITPROD10C( const double& pinprod10c, 
                                 const int& i ) 
     { 
       initPROD10[i].carbon = pinprod10c; 
     }


     // initPROD10[].nitrogen **********************************
     
     inline double getINITPROD10N( const int& i ) 
     { 
       return initPROD10[i].nitrogen; 
     }

     inline void setINITPROD10N( const double& pinprod10n, 
                                 const int& i ) 
     { 
       initPROD10[i].nitrogen = pinprod10n; 
     }


     // initPROD100[].carbon ***********************************
      
     inline double getINITPROD100C( const int& i ) 
     { 
       return initPROD100[i].carbon; 
     }

     inline void setINITPROD100C( const double& pinprod100c, 
                                  const int& i ) 
     { 
       initPROD100[i].carbon = pinprod100c; 
     }


     // initPROD100[].nitrogen *********************************
     
     inline double getINITPROD100N( const int& i ) 
     { 
       return initPROD100[i].nitrogen; 
     }

     inline void setINITPROD100N( const double& pinprod100n, 
                                  const int& i ) 
     { 
       initPROD100[i].nitrogen = pinprod100n; 
     }


     // kd *****************************************************
     
     inline double getKD( void ) { return kd; }

     inline void setKD( const double& pkd ) { kd = pkd; }


     //manure.carbon *********************************

     inline double getMANUREC( void )
     {
       return manure.carbon;
     }

     inline void setMANUREC( const double& pmanurec )
     {
       manure.carbon = pmanurec;
     }

     // manure.nitrogen *********************************

     inline double getMANUREN( void )
     {
       return manure.nitrogen;
     }

     inline void setMANUREN( const double& pmanuren )
     {
       manure.nitrogen = pmanuren;
     }


     // natprveetmx ********************************************
     
     inline double getNATPRVEETMX( void ) 
     { 
       return natprveetmx; 
     }

     inline void setNATPRVEETMX( const double& pnatprveetmx ) 
     { 
       natprveetmx = pnatprveetmx; 
     }


     // natprvleafmx *******************************************
     
     inline double getNATPRVLEAFMX( void ) 
     { 
       return natprvleafmx; 
     }

     inline void setNATPRVLEAFMX( const double& pnatprvleafmx ) 
     { 
       natprvleafmx = pnatprvleafmx; 
     }


     // natprvpetmx ********************************************
     
     inline double getNATPRVPETMX( void ) 
     { 
       return natprvpetmx; 
     }

     inline void setNATPRVPETMX( const double& pnatprvpetmx ) 
     { 
       natprvpetmx = pnatprvpetmx; 
     }


     // natseedC ***********************************************
     
     inline double getNATSEEDC( void ) { return natseedC; }

     inline void setNATSEEDC( const double& pnatseedc ) 
     { 
       natseedC = pnatseedc; 
     }


     // natseedSTRN ********************************************
     
     inline double getNATSEEDSTRN( void ) 
     { 
       return natseedSTRN; 
     }

     inline void setNATSEEDSTRN( const double& pnatseedstrn ) 
     { 
       natseedSTRN = pnatseedstrn; 
     }


     // natseedSTON ********************************************
     
     inline double getNATSEEDSTON( void ) 
     { 
       return natseedSTON; 
     }

     inline void setNATSEEDSTON( const double& pnatseedston ) 
     { 
       natseedSTON = pnatseedston; 
     }


     // natsoil ************************************************
     
     inline double getNATSOIL( void ) { return natsoil; }

     inline void setNATSOIL( const double& pnatsoil ) 
     { 
       natsoil = pnatsoil; 
     }


     // nattopt ************************************************
     
     inline double getNATTOPT( void ) { return nattopt; }

     inline void setNATTOPT( const double& pnattopt ) 
     { 
       nattopt = pnattopt; 
     }


     // natyreet ***********************************************

     inline double getNATYREET( void ) { return natyreet; }

     inline void setNATYREET( const double& pnatyreet ) 
     { 
       natyreet = pnatyreet; 
     }


     // natyrpet ***********************************************

     inline double getNATYRPET( void ) { return natyrpet; }

     inline void setNATYRPET( const double& pnatyrpet ) 
     { 
       natyrpet = pnatyrpet; 
     }

     
     // nretent ************************************************

     inline InorgN60 getNRETENT( void ) { return nretent; }

     
     // nretent.nh4 ********************************************

     inline double getNH4RETENT( void ) { return nretent.nh4; }

     inline void setNH4RETENT( const double& pnretent ) 
     { 
       nretent.nh4 = pnretent; 
     }

     // nretent.no3 *********************************************

     inline double getNO3RETENT( void ) { return nretent.no3; }

     inline void setNO3RETENT( const double& pnretent )
     {
       nretent.no3 = pnretent;
     }


     // nretent.total ******************************************

     inline double getNTOTRETENT( void ) { return nretent.total; }

     inline void setNTOTRETENT( const double& pnretent )
     {
       nretent.total = pnretent;
     }


     // nsretconv **********************************************
     
     inline double getNSRETCONV( const int& pcmnt ) 
     { 
       return nsretconv[pcmnt]; 
     }

     inline void setNSRETCONV( const double& pnsretconv, 
                               const int& pcmnt ) 
     { 
       nsretconv[pcmnt] = pnsretconv; 
     }


     // nsretent ***********************************************

     inline InorgN60 getNSRETENT( void ) { return nsretent; }

     
     // nsretent.nh4 *******************************************

     inline double getSNH4RETENT( void ) { return nsretent.nh4; }

     inline void setSNH4RETENT( const double& pnsretent ) 
     { 
       nsretent.nh4 = pnsretent; 
     }

     // nsretent.no3 *******************************************

     inline double getSNO3RETENT( void ) { return nsretent.no3; }

     inline void setSNO3RETENT( const double& pnsretent )
     {
       nsretent.no3 = pnsretent;
     }

     // nsretent.total *****************************************

     inline double getSNTOTRETENT( void ) { return nsretent.total; }

     inline void setSNTOTRETENT( const double& pnsretent )
     {
       nsretent.total = pnsretent;
     }
 
     // nvretconv **********************************************
     
     inline double getNVRETCONV( const int& pcmnt ) 
     { 
       return nvretconv[pcmnt]; 
     }

     inline void setNVRETCONV( const double& pnvretconv, 
                               const int& pcmnt ) 
     { 
       nvretconv[pcmnt] = pnvretconv; 
     }


     // nvretent ***********************************************

     inline InorgN60 getNVRETENT( void ) { return nvretent; }


     // nvretent.nh4 *******************************************
     
     inline double getVNH4RETENT( void ) { return nvretent.nh4; }

     inline void setVNH4RETENT( const double& pnvretent ) 
     { 
       nvretent.nh4 = pnvretent; 
     }


     // nvretent.no3 *******************************************

     inline double getVNO3RETENT( void ) { return nvretent.no3; }

     inline void setVNO3RETENT( const double& pnvretent )
     {
       nvretent.no3 = pnvretent;
     }

     // nvretent.total *****************************************

     inline double getVNTOTRETENT( void ) { return nvretent.total; }

     inline void setVNTOTRETENT( const double& pnvretent )
     {
       nvretent.total = pnvretent;
     }

     // prevCropResidue.carbon *********************************
     
     inline double getPREVCROPRESIDUEC( void ) 
     { 
       return prevCropResidue.carbon; 
     }

     inline void setPREVCROPRESIDUEC( const double& pcrpresc ) 
     { 
       prevCropResidue.carbon = pcrpresc; 
     }


     // prevCropResidue.nitrogen *******************************
     
     inline double getPREVCROPRESIDUEN( void ) 
     { 
       return prevCropResidue.nitrogen; 
     }

     inline void setPREVCROPRESIDUEN( const double& pcrpresn ) 
     { 
       prevCropResidue.nitrogen = pcrpresn; 
     }


     // prevPROD1.carbon ***************************************
     
     inline double getPREVPROD1C( void ) 
     { 
       return prevPROD1.carbon; 
     }

     inline void setPREVPROD1C( const double& pprod1c ) 
     { 
       prevPROD1.carbon = pprod1c; 
     }


     // prev.PROD1.nitrogen ************************************
     
     inline double getPREVPROD1N( void ) 
     { 
       return prevPROD1.nitrogen; 
     }

     inline void setPREVPROD1N( const double& pprod1n ) 
     { 
       prevPROD1.nitrogen = pprod1n; 
     }


     // prevPROD10.carbon **************************************
     
     inline double getPREVPROD10C( void ) 
     { 
       return prevPROD10.carbon; 
     }

     inline void setPREVPROD10C( const double& pprod10c ) 
     { 
       prevPROD10.carbon = pprod10c; 
     }


     // prevPROD10.nitrogen ************************************
     
     inline double getPREVPROD10N( void ) 
     { 
       return prevPROD10.nitrogen; 
     }

     inline void setPREVPROD10N( const double& pprod10n ) 
     { 
       prevPROD10.nitrogen = pprod10n; 
     }


     // prevPROD100.carbon *************************************
     
     inline double getPREVPROD100C( void ) 
     { 
       return prevPROD100.carbon; 
     }

     inline void setPREVPROD100C( const double& pprod100c ) 
     { 
       prevPROD100.carbon = pprod100c; 
     }


     // prevPROD100.nitrogen ***********************************
     
     inline double getPREVPROD100N( void ) 
     { 
       return prevPROD100.nitrogen; 
     }

     inline void setPREVPROD100N( const double& pprod100n ) 
     { 
       prevPROD100.nitrogen = pprod100n; 
     }


     // PROD1.carbon *******************************************
     
     inline double getPROD1C( void ) { return PROD1.carbon; }


     // PROD1.nitrogen *****************************************
     
     inline double getPROD1N( void ) { return PROD1.nitrogen; }


     // PROD10.carbon ******************************************
     
     inline double getPROD10C( void ) { return PROD10.carbon; }


     // PROD10.nitrogen ****************************************
     
     inline double getPROD10N( void ) 
     { 
       return PROD10.nitrogen; 
     }


     // PROD100.carbon *****************************************
     
     inline double getPROD100C( void ) 
     { 
       return PROD100.carbon; 
     }


     // PROD100.nitrogen ***************************************
     
     inline double getPROD100N( void ) 
     { 
       return PROD100.nitrogen; 
     }


     // PROD1decay.carbon **************************************
     
     inline double getPROD1DECAYC( void ) 
     { 
       return PROD1decay.carbon; 
     }


     // PROD1decay.nitrogen ************************************
     
     inline double getPROD1DECAYN( void ) 
     { 
       return PROD1decay.nitrogen; 
     }


     // PROD10decay.carbon *************************************
     
     inline double getPROD10DECAYC( void ) 
     { 
       return PROD10decay.carbon; 
     }


     // PROD10decay.nitrogen ***********************************
     
     inline double getPROD10DECAYN( void ) 
     { 
       return PROD10decay.nitrogen; 
     }


     // PROD100decay.carbon ************************************
     
     inline double getPROD100DECAYC( void ) 
     { 
       return PROD100decay.carbon; 
     }


     // PROD100decay.nitrogen **********************************
     
     inline double getPROD100DECAYN( void ) 
     { 
       return PROD100decay.nitrogen; 
     }


     // prod10par **********************************************
     
     inline double getPROD10PAR( void ) { return prod10par; }

     inline void setPROD10PAR( const double& pprod10par ) 
     { 
       prod10par = pprod10par; 
     }


     // prod100par *********************************************
     
     inline double getPROD100PAR( void ) { return prod100par; }

     inline void setPROD100PAR( const double& pprod100par ) 
     { 
       prod100par = pprod100par; 
     }


     // productYear ********************************************
     
     inline int getPRODUCTYEAR( void ) { return productYear; }

     inline void setPRODUCTYEAR( const int& pprodyr ) 
     { 
       productYear = pprodyr; 
     }


     // prvcropnpp *********************************************
     
     inline double getPRVCROPNPP( void ) { return prvcropnpp; }

     inline void setPRVCROPNPP( const double& pprvcropnpp ) 
     { 
       prvcropnpp = pprvcropnpp; 
     }


     // residueC ***********************************************
     
     inline double getRESIDUEC( const int& pcmnt ) 
     { 
       return residueC[pcmnt]; 
     }

     inline void setRESIDUEC( const double& presidueC, 
                              const int& pcmnt ) 
     { 
       residueC[pcmnt] = presidueC; 
     }


     // residueN ***********************************************
     
     inline double getRESIDUEN( const int& pcmnt ) 
     { 
       return residueN[pcmnt]; 
     }

     inline void setRESIDUEN( const double& presidueN, 
                              const int& pcmnt ) 
     { 
       residueN[pcmnt] = presidueN; 
     }


     // sconvert ***********************************************
     
     inline double getSCONVERT( void ) { return sconvert; }

     inline void setSCONVERT( const double& pscnvrt ) 
     { 
       sconvert = pscnvrt; 
     }


     // sconvrtflx.carbon **************************************
     
     inline double getSCONVRTFLXC( void ) 
     { 
       return sconvrtflx.carbon; 
     }

     inline void setSCONVRTFLXC( const double& pscnvrtflxc ) 
     { 
       sconvrtflx.carbon = pscnvrtflxc; 
     }


     // sconvrtflx.nitrogen ************************************
     
     inline double getSCONVRTFLXN( void ) 
     { 
       return sconvrtflx.nitrogen; 
     }

     inline void setSCONVRTFLXN( const double& pscnvrtflxn ) 
     { 
       sconvrtflx.nitrogen = pscnvrtflxn; 
     }


     // slash.carbon *******************************************
     
     inline double getSLASHC( void ) { return slash.carbon; }

     inline void setSLASHC( const double& pslashc ) 
     { 
       slash.carbon = pslashc; 
     }


     // slash.nitrogen *****************************************

     inline double getSLASHN( void ) { return slash.nitrogen; }

     inline void setSLASHN( const double& pslashn ) 
     { 
       slash.nitrogen = pslashn; 
     }


     // slashpar ***********************************************
     
     inline double getSLASHPAR( void ) { return slashpar; }

     inline void setSLASHPAR( const double& pslashpar ) 
     { 
       slashpar = pslashpar; 
     }


     // stubble.carbon *****************************************
     
     inline double getSTUBBLEC( void ) 
     { 
       return stubble.carbon; 
     }

     inline void setSTUBBLEC( const double& pstubc ) 
     { 
       stubble.carbon = pstubc; 
     }


     // stubble.nitrogen ***************************************
     
     inline double getSTUBBLEN( void ) 
     { 
       return stubble.nitrogen; 
     }

     inline void setSTUBBLEN( const double& pstubn ) 
     { 
       stubble.nitrogen = pstubn; 
     }


     // tillfactor *********************************************
     
     inline double getTILLFACTOR( const int& pcmnt ) 
     { 
       return tillfactor[pcmnt]; 
     }

     inline void setTILLFACTOR( const double& ptillfact, 
                                const int& pcmnt ) 
     { 
       tillfactor[pcmnt] = ptillfact; 
     }


     // totec **************************************************
     
     inline double getTOTEC( void ) { return totec; }

     inline void setTOTEC( const double& ptotec ) 
     { 
       totec = ptotec; 
     }


     // TOTPROD.carbon *****************************************
     
     inline double getTOTPRODC( void ) 
     { 
       return TOTPROD.carbon; 
     }


     // TOTPROD.nitrogen ***************************************
     
     inline double getTOTPRODN( void ) 
     { 
       return TOTPROD.nitrogen; 
     }


     // TOTPRODdecay.carbon ************************************
     
     inline double getTOTPRODDECAYC( void ) 
     { 
       return TOTPRODdecay.carbon; 
     }


     // TOTPRODdecay.nitrogen **********************************
     
     inline double getTOTPRODDECAYN( void ) 
     { 
       return TOTPRODdecay.nitrogen; 
     }


     // urine **************************************************

     inline double getURINE( void )
     {
       return urine;
     }

     inline void setURINE( const double& purine )
     {
       urine = purine;
     }


     // vconvert ***********************************************
     
     inline double getVCONVERT( void ) { return vconvert; }

     inline void setVCONVERT( const double& pvcnvrt ) 
     { 
       vconvert = pvcnvrt; 
     }


     // vconvrtflx.carbon **************************************
     
     inline double getVCONVRTFLXC( void ) 
     { 
       return vconvrtflx.carbon; 
     }

     inline void setVCONVRTFLXC( const double& pvcnvrtflxc ) 
     { 
       vconvrtflx.carbon = pvcnvrtflxc; 
     }


     // vconvrtflx.nitrogen ************************************
     
     inline double getVCONVRTFLXN( void ) 
     { 
       return vconvrtflx.nitrogen; 
     }

     inline void setVCONVRTFLXN( const double& pvcnvrtflxn ) 
     { 
       vconvrtflx.nitrogen = pvcnvrtflxn; 
     }


     // vrespar ************************************************
     
     inline double getVRESPAR( void ) { return vrespar; }

     inline void setVRESPAR( const double& pvrespar ) 
     { 
       vrespar = pvrespar; 
     }

     // yrcflux ************************************************
     
     inline double getYRCFLUX( void ) { return yrcflux; }

     inline void setYRCFLUX( const double& pyrcflux ) 
     { 
       yrcflux = pyrcflux; 
     }

     inline void updateYRCFLUX( const double& pcflux ) 
     { 
       yrcflux += pcflux; 
     }

     // yrconvrtC ************************************************
     
     inline double getYRCONVRTC( void ) { return yrconvrtC; }

     inline void setYRCONVRTC( const double& pyrconvrtC ) 
     { 
       yrconvrtC = pyrconvrtC; 
     }

     inline void updateYRCONVRTC( const double& pconvrtC ) 
     { 
       yrconvrtC += pconvrtC; 
     }

     // yrconvrtN **********************************************
     
     inline double getYRCONVRTN( void ) { return yrconvrtN; }

     inline void setYRCONVRTN( const double& pyrconvrtN ) 
     { 
       yrconvrtN = pyrconvrtN; 
     }

     inline void updateYRCONVRTN( const double& pconvrtN ) 
     { 
       yrconvrtN += pconvrtN; 
     }

     // yrdecayPROD1C ******************************************
     
     inline double getYRDECAYPROD1C( void ) { return yrdecayPROD1C; }

     inline void setYRDECAYPROD1C( const double& pyrdecayPROD1C ) 
     { 
       yrdecayPROD1C = pyrdecayPROD1C; 
     }

     inline void updateYRDECAYPROD1C( const double& pdecayPROD1C ) 
     { 
       yrdecayPROD1C += pdecayPROD1C; 
     }

     // yrdecayPROD10C ******************************************
     
     inline double getYRDECAYPROD10C( void ) { return yrdecayPROD10C; }

     inline void setYRDECAYPROD10C( const double& pyrdecayPROD10C ) 
     { 
       yrdecayPROD10C = pyrdecayPROD10C; 
     }

     inline void updateYRDECAYPROD10C( const double& pdecayPROD10C ) 
     { 
       yrdecayPROD10C += pdecayPROD10C; 
     }

     // yrdecayPROD100C ******************************************
     
     inline double getYRDECAYPROD100C( void ) { return yrdecayPROD100C; }

     inline void setYRDECAYPROD100C( const double& pyrdecayPROD100C ) 
     { 
       yrdecayPROD100C = pyrdecayPROD100C; 
     }

     inline void updateYRDECAYPROD100C( const double& pdecayPROD100C ) 
     { 
       yrdecayPROD100C += pdecayPROD100C; 
     }

     // yrdecayPROD1N ******************************************
     
     inline double getYRDECAYPROD1N( void ) { return yrdecayPROD1N; }

     inline void setYRDECAYPROD1N( const double& pyrdecayPROD1N ) 
     { 
       yrdecayPROD1N = pyrdecayPROD1N; 
     }

     inline void updateYRDECAYPROD1N( const double& pdecayPROD1N ) 
     { 
       yrdecayPROD1N += pdecayPROD1N; 
     }

     // yrdecayPROD10N ******************************************
     
     inline double getYRDECAYPROD10N( void ) { return yrdecayPROD10N; }

     inline void setYRDECAYPROD10N( const double& pyrdecayPROD10N ) 
     { 
       yrdecayPROD10N = pyrdecayPROD10N; 
     }

     inline void updateYRDECAYPROD10N( const double& pdecayPROD10N ) 
     { 
       yrdecayPROD10N += pdecayPROD10N; 
     }

     // yrdecayPROD100N ******************************************
     
     inline double getYRDECAYPROD100N( void ) { return yrdecayPROD100N; }

     inline void setYRDECAYPROD100N( const double& pyrdecayPROD100N ) 
     { 
       yrdecayPROD100N = pyrdecayPROD100N; 
     }

     inline void updateYRDECAYPROD100N( const double& pdecayPROD100N ) 
     { 
       yrdecayPROD100N += pdecayPROD100N; 
     }

     // yrdecayTOTPRODC ******************************************
     
     inline double getYRDECAYTOTPRODC( void ) { return yrdecayTOTPRODC; }

     inline void setYRDECAYTOTPRODC( const double& pyrdecayTOTPRODC ) 
     { 
       yrdecayTOTPRODC = pyrdecayTOTPRODC; 
     }

     inline void updateYRDECAYTOTPRODC( const double& pdecayTOTPRODC ) 
     { 
       yrdecayTOTPRODC += pdecayTOTPRODC; 
     }

     // yrdecayTOTPRODN ******************************************
     
     inline double getYRDECAYTOTPRODN( void ) { return yrdecayTOTPRODN; }

     inline void setYRDECAYTOTPRODN( const double& pyrdecayTOTPRODN ) 
     { 
       yrdecayTOTPRODN = pyrdecayTOTPRODN; 
     }

     inline void updateYRDECAYTOTPRODN( const double& pdecayTOTPRODN ) 
     { 
       yrdecayTOTPRODN += pdecayTOTPRODN; 
     }

     // yrfertn ************************************************
     
     inline double getYRFERTN( void ) { return yrfertn; }

     inline void setYRFERTN( const double& pyrfertn ) 
     { 
       yrfertn += pyrfertn; 
     }

     inline void updateYRFERTN( const double& pfertn ) 
     { 
       yrfertn += pfertn; 
     }

     // yrfluxResidueC *****************************************
     
     inline double getYRFLUXRESIDUEC( void ) { return yrfluxResidueC; }

     inline void setYRFLUXRESIDUEC( const double& pyrfluxResidueC ) 
     { 
       yrfluxResidueC += pyrfluxResidueC; 
     }

     inline void updateYRFLUXRESIDUEC( const double& pfluxResidueC ) 
     { 
       yrfluxResidueC += pfluxResidueC; 
     }

     // yrfluxResidueN *****************************************
     
     inline double getYRFLUXRESIDUEN( void ) { return yrfluxResidueN; }

     inline void setYRFLUXRESIDUEN( const double& pyrfluxResidueN ) 
     { 
       yrfluxResidueN += pyrfluxResidueN; 
     }

     inline void updateYRFLUXRESIDUEN( const double& pfluxResidueN ) 
     { 
       yrfluxResidueN += pfluxResidueN; 
     }

     // yrformPROD1C *******************************************
     
     inline double getYRFORMPROD1C( void ) { return yrformPROD1C; }

     inline void setYRFORMPROD1C( const double& pyrformPROD1C ) 
     { 
       yrformPROD1C += pyrformPROD1C; 
     }

     inline void updateYRFORMPROD1C( const double& pformPROD1C ) 
     { 
       yrformPROD1C += pformPROD1C; 
     }

     // yrformPROD10C *******************************************
     
     inline double getYRFORMPROD10C( void ) { return yrformPROD10C; }

     inline void setYRFORMPROD10C( const double& pyrformPROD10C ) 
     { 
       yrformPROD10C += pyrformPROD10C; 
     }

     inline void updateYRFORMPROD10C( const double& pformPROD10C ) 
     { 
       yrformPROD10C += pformPROD10C; 
     }

     // yrformPROD100C *******************************************
     
     inline double getYRFORMPROD100C( void ) { return yrformPROD100C; }

     inline void setYRFORMPROD100C( const double& pyrformPROD100C ) 
     { 
       yrformPROD100C += pyrformPROD100C; 
     }

     inline void updateYRFORMPROD100C( const double& pformPROD100C ) 
     { 
       yrformPROD100C += pformPROD100C; 
     }

     // yrformPROD1N *******************************************
     
     inline double getYRFORMPROD1N( void ) { return yrformPROD1N; }

     inline void setYRFORMPROD1N( const double& pyrformPROD1N ) 
     { 
       yrformPROD1N += pyrformPROD1N; 
     }

     inline void updateYRFORMPROD1N( const double& pformPROD1N ) 
     { 
       yrformPROD1N += pformPROD1N; 
     }

     // yrformPROD10N *******************************************
     
     inline double getYRFORMPROD10N( void ) { return yrformPROD10N; }

     inline void setYRFORMPROD10N( const double& pyrformPROD10N ) 
     { 
       yrformPROD10N += pyrformPROD10N; 
     }

     inline void updateYRFORMPROD10N( const double& pformPROD10N ) 
     { 
       yrformPROD10N += pformPROD10N; 
     }

     // yrformPROD100N *******************************************
     
     inline double getYRFORMPROD100N( void ) { return yrformPROD100N; }

     inline void setYRFORMPROD100N( const double& pyrformPROD100N ) 
     { 
       yrformPROD100N += pyrformPROD100N; 
     }

     inline void updateYRFORMPROD100N( const double& pformPROD100N ) 
     { 
       yrformPROD100N += pformPROD100N; 
     }

     // yrformResidueC *****************************************
     
     inline double getYRFORMRESIDUEC( void ) { return yrformResidueC; }

     inline void setYRFORMRESIDUEC( const double& pyrformResidueC ) 
     { 
       yrformResidueC += pyrformResidueC; 
     }

     inline void updateYRFORMRESIDUEC( const double& pformResidueC ) 
     { 
       yrformResidueC += pformResidueC; 
     }

     // yrformResidueN *****************************************
     
     inline double getYRFORMRESIDUEN( void ) { return yrformResidueN; }

     inline void setYRFORMRESIDUEN( const double& pyrformResidueN ) 
     { 
       yrformResidueN += pyrformResidueN; 
     }

     inline void updateYRFORMRESIDUEN( const double& pformResidueN ) 
     { 
       yrformResidueN += pformResidueN; 
     }

     // yrformTOTPRODC *******************************************
     
     inline double getYRFORMTOTPRODC( void ) { return yrformTOTPRODC; }

     inline void setYRFORMTOTPRODC( const double& pyrformTOTPRODC ) 
     { 
       yrformTOTPRODC += pyrformTOTPRODC; 
     }

     inline void updateYRFORMTOTPRODC( const double& pformTOTPRODC ) 
     { 
       yrformTOTPRODC += pformTOTPRODC; 
     }

     // yrformTOTPRODN *******************************************
     
     inline double getYRFORMTOTPRODN( void ) { return yrformTOTPRODN; }

     inline void setYRFORMTOTPRODN( const double& pyrformTOTPRODN ) 
     { 
       yrformTOTPRODN += pyrformTOTPRODN; 
     }

     inline void updateYRFORMTOTPRODN( const double& pformTOTPRODN ) 
     { 
       yrformTOTPRODN += pformTOTPRODN; 
     }

     // yrirrig *******************************************
     
     inline double getYRIRRIG( void ) { return yrirrig; }

     inline void setYRIRRIG( const double& pyrirrig ) 
     { 
       yrirrig += pyrirrig; 
     }

     inline void updateYRIRRIG( const double& pirrig ) 
     { 
       yrirrig += pirrig; 
     }

     // yrnrent *******************************************
     
     inline InorgN60 getYRNRENT( void ) { return yrnrent; }

     inline void setYRNRENT( const InorgN60& pyrnrent ) 
     { 
       yrnrent.total = yrnrent.total + pyrnrent.total; 
       yrnrent.nh4 = yrnrent.nh4 + pyrnrent.nh4;
       yrnrent.no3 = yrnrent.no3 + pyrnrent.no3;
     }

     inline void updateYRNRENT( const InorgN60& pnrent ) 
     { 
       yrnrent.total = yrnrent.total + pnrent.total;
       yrnrent.nh4 = yrnrent.nh4 + pnrent.nh4;
       yrnrent.no3 = yrnrent.no3 + pnrent.no3;
 
     }
 
     // yrnsrent *******************************************
     
     inline InorgN60 getYRNSRENT( void ) { return yrnsrent; }

     inline void setYRNSRENT( const InorgN60& pyrnsrent ) 
     { 
       yrnsrent.total = yrnsrent.total + pyrnsrent.total;
       yrnsrent.nh4 = yrnsrent.nh4 + pyrnsrent.nh4;
       yrnsrent.no3 = yrnsrent.no3 + pyrnsrent.no3;
     }

     inline void updateYRNSRENT( const InorgN60& pnsrent ) 
     { 
       yrnsrent.total = yrnsrent.total + pnsrent.total;
       yrnsrent.nh4 = yrnsrent.nh4 + pnsrent.nh4;
       yrnsrent.no3 = yrnsrent.no3 + pnsrent.no3;
     }

     // yrnvrent *******************************************
     
     inline InorgN60 getYRNVRENT( void ) { return yrnvrent; }

     inline void setYRNVRENT( const InorgN60& pyrnvrent ) 
     { 
       yrnvrent.total = yrnvrent.total + pyrnvrent.total;
       yrnvrent.nh4 = yrnvrent.nh4 + pyrnvrent.nh4;
       yrnvrent.no3 = yrnvrent.no3 + pyrnvrent.no3;
      }

     inline void updateYRNVRENT( const InorgN60& pnvrent ) 
     { 
       yrnvrent.total = yrnvrent.total + pnvrent.total;
       yrnvrent.nh4 = yrnvrent.nh4 + pnvrent.nh4;
       yrnvrent.no3 = yrnvrent.no3 + pnvrent.no3;
     }

     // yrsconvrtC *********************************************
     
     inline double getYRSCONVRTC( void ) { return yrsconvrtC; }

     inline void setYRSCONVRTC( const double& pyrsconvrtC ) 
     { 
       yrsconvrtC += pyrsconvrtC; 
     }

     inline void updateYRSCONVRTC( const double& psconvrtC ) 
     { 
       yrsconvrtC += psconvrtC; 
     }

     // yrsconvrtN *********************************************
     
     inline double getYRSCONVRTN( void ) { return yrsconvrtN; }

     inline void setYRSCONVRTN( const double& pyrsconvrtN ) 
     { 
       yrsconvrtN += pyrsconvrtN; 
     }

     inline void updateYRSCONVRTN( const double& psconvrtN ) 
     { 
       yrsconvrtN += psconvrtN; 
     }

     // yrslashC ***********************************************
     
     inline double getYRSLASHC( void ) { return yrslashC; }

     inline void setYRSLASHC( const double& pyrslashC ) 
     { 
       yrslashC += pyrslashC; 
     }

     inline void updateYRSLASHC( const double& pslashC ) 
     { 
       yrslashC += pslashC; 
     }

     // yrslashN ***********************************************
     
     inline double getYRSLASHN( void ) { return yrslashN; }

     inline void setYRSLASHN( const double& pyrslashN ) 
     { 
       yrslashN += pyrslashN; 
     }

     inline void updateYRSLASHN( const double& pslashN ) 
     { 
       yrslashN += pslashN; 
     }

     // yrstubC ************************************************
     
     inline double getYRSTUBC( void ) { return yrstubC; }

     inline void setYRSTUBC( const double& pyrstubC ) 
     { 
       yrstubC += pyrstubC; 
     }

     inline void updateYRSTUBC( const double& pstubC ) 
     { 
       yrstubC += pstubC; 
     }

     // yrstubN ************************************************
     
     inline double getYRSTUBN( void ) { return yrstubN; }

     inline void setYRSTUBN( const double& pyrstubN ) 
     { 
       yrstubN += pyrstubN; 
     }

     inline void updateYRSTUBN( const double& pstubN ) 
     { 
       yrstubN += pstubN; 
     }

     // yrvconvrtC *********************************************
     
     inline double getYRVCONVRTC( void ) { return yrvconvrtC; }

     inline void setYRVCONVRTC( const double& pyrvconvrtC ) 
     { 
       yrvconvrtC += pyrvconvrtC; 
     }

     inline void updateYRVCONVRTC( const double& pvconvrtC ) 
     { 
       yrvconvrtC += pvconvrtC; 
     }

     // yrvconvrtN *********************************************
     
     inline double getYRVCONVRTN( void ) { return yrvconvrtN; }

     inline void setYRVCONVRTN( const double& pyrvconvrtN ) 
     { 
       yrvconvrtN += pyrvconvrtN; 
     }

     inline void updateYRVCONVRTN( const double& pvconvrtN ) 
     { 
       yrvconvrtN += pvconvrtN; 
     }

     

/* *************************************************************
		 Public Variables
************************************************************* */

    // Index for disturbed community type
    int cmnt;
  
    // Flag to indicate whether or not optimum
    //   fertilization of croplands occurs
    int fertflag;

    // Monthly fertilizer application 
    double fertn;

    // Flag to indicate whether or not optimum irrigation of
    //   croplands occur
    int irrgflag;

    // Monthly irrigation (mm / month)
    double irrigate;

    int lulcyear;

    int massbalflg;

    int mez;

    // Flag to indicate that element is in agriculture during
    //   previous year
    int prvstate;

    // Flag to indicate that element is in agriculture during
    //   current year
    // state = 1 - row-crop agriculture
    // state = 2 - pasture
    // state = 3 - urban area
    // state = 4 - tree plantation
    // state = 5 - suburban area
    // state = 6 - protected area
    int state;

     // Flag to indicate whether or not croplands are tilled
    int tillflag;

     // Flag to indicate whether or not simulation is conducted 
     //   with transient land use data 
    int tlulcflag;


   private:
   
/* *************************************************************
		 Private Variables
************************************************************* */

     // Monthly carbon flux to the atmosphere as a result of
     // livestock respiration
     double animalresp;

     // Monthly carbon flux to the atmosphere as a result of
     //   NEP plus agricultural conversion fluxes
     double cflux;

     // Monthly loss of carbon and nitrogen to the atmosphere as a
     //   result of agricultural conversion
     Biomass convrtflx;

     // Monthly carbon and nitrogen fluxes associated with crop 
     //   yield
     Biomass cropprod;

     // Maximum monthly estimated evapotranspiration of crops 
     //   during the previous year 
     double cropprveetmx;

     // Maximum monthly relative leaf area of crops during the
     //   previous year 
     double cropprvleafmx;

     // Maximum monthly potential evapotranspiration of crops 
     //   during the previous year 
     double cropprvpetmx;

     // Stock of crop residue left in crop fields after harvest
     Biomass cropResidue;

     // Monthly loss of carbon from burning crop residue
     Biomass cropResidueFlux;

     double croptopt;

     // Monthly reintroduction of N volatilized in fires
     //   back to the soil (as N deposition)
     InorgN60 firendep;
    
     // Monthly forage rates
     Biomass forage;

     // Monthly creation of crop residue from harvest
     Biomass formCropResidue;

     // Monthly formation of 10-year wood products
     Biomass formPROD10;

     // Monthly formation of 100-year wood products
     Biomass formPROD100;

     // Monthly formation of all "products"
     Biomass formTOTPROD;

     // Fire return interval
     int FRI;

     // Flag to indicate frost damage
     int frostflag;

     // Growing degree days ( degrees C )
     double growdd;
    
     Biomass initPROD1[CYCLE];
    
     Biomass initPROD10[10];
    
     Biomass initPROD100[100];


     // Intrinsic decomposition rate
     double kd;

     // Monthly manure inputs
     Biomass manure;

     // Maximum monthly estimated evapotranspiration of natural 
     //   vegetation during the previous year 
     double natprveetmx;

     // Maximum monthly relative leaf area of natural vegetation 
     //   during the previous year 
     double natprvleafmx;

     // Maximum monthly potential evapotranspiration of natural
     //   vegetation during the previous year 
     double natprvpetmx;

     double natsoil;

     double natseedC;

     double natseedSTRN;

     double natseedSTON;

     double nattopt;

     double natyreet;

     double natyrpet;
   
     // Total nitrogen retained by ecosystem after conversion
     InorgN60 nretent;

     // Nitrogen from soil organic matter retained after 
     //   conversion
     InorgN60 nsretent;

     // Nitrogen from vegetation biomass retained after 
     //   conversion
     InorgN60 nvretent;

     // Carbon and nitrogen stocks in agricultural products
     //   during previous month
     Biomass prevPROD1;
    
     // Carbon and nitrogen stocks in 10-year wood products
     //   during previous month
     Biomass prevPROD10;

     // Carbon and nitrogen stocks in 100-year wood products
     //   during previous month
     Biomass prevPROD100;

     // Carbon and nitrogen stocks in agricultural products
     //   during current month
     Biomass PROD1;

     // Carbon and nitrogen stocks in 10-year wood products
     //   during current month
     Biomass PROD10;

     // Carbon and nitrogen stocks in 100-year wood products
     //   during current month
     Biomass PROD100;

     // Loss of carbon and nitrogen from "decay" of agricultural
     //   products
     Biomass PROD1decay;

     // Loss of carbon and nitrogen from "decay" of 10-year wood
     //   products
     Biomass PROD10decay;

     // Loss of carbon and nitrogen from "decay" of 100-year wood
     //   products
     Biomass PROD100decay;

     int productYear;

     // Crop net primary production during previous month
     double prvcropnpp;

     // Stock of crop residue from previous month
     Biomass prevCropResidue;

     // Soil organic matter lost during conversion to agriculture
     Biomass sconvrtflx;

     // Stock of slash resulting from conversion to agriculture
     Biomass slash;

     // Stock of crop residue that is actually added to soil
     //   (i.e. residue that is not burned off after harvest)
     Biomass stubble;

     // Total carbon storage in ecosystem (i.e. VEGC + TOTSOLC,
     //   does not include carbon in agricultural and wood
     //   products
     double totec;

     // Carbon and nitrogen stocks in all agricultural and wood 
     //   products
     Biomass TOTPROD;

     // Loss of carbon and nitrogen from "decay" of all 
     //   agricultural and wood products
     Biomass TOTPRODdecay;

     // Monthly urine inputs
     double urine;

     // Vegetation biomass lost during conversion to agriculture
     Biomass vconvrtflx;

    // Annual sum of cflux
    double yrcflux;

    // Annual sum of convrtflx.carbon
    double yrconvrtC;

    // Annual sum of convrtflx.nitrogen
    double yrconvrtN;

    // Annual sum of PROD1decay.carbon
    double yrdecayPROD1C;

    // Annual sum of PROD10decay.carbon
    double yrdecayPROD10C;

    // Annual sum of PROD100decay.carbon
    double yrdecayPROD100C;

    // Annual sum of PROD1decay.nitrogen
    double yrdecayPROD1N;

    // Annual sum of PROD10decay.nitrogen
    double yrdecayPROD10N;

    // Annual sum of PROD100decay.nitrogen
    double yrdecayPROD100N;

    // Annual sum of TOTPRODdecay.carbon
    double yrdecayTOTPRODC;

    // Annual sum of TOTPRODdecay.nitrogen
    double yrdecayTOTPRODN;

    // Annual sum of fertn
    double yrfertn;

    // Annual sum of cropResidueFlux.carbon
    double yrfluxResidueC;

    // Annual sum of cropResidueFlux.nitrogen
    double yrfluxResidueN;

    // Annual sum of cropprod.carbon
    double yrformPROD1C;

    // Annual sum of formPROD10.carbon
    double yrformPROD10C;

    // Annual sum of formPROD100.carbon
    double yrformPROD100C;

    // Annual sum of cropprod.nitrogen
    double yrformPROD1N;

    // Annual sum of formPROD10.nitrogen
    double yrformPROD10N;

    // Annual sum of formPROD100.nitrogen
    double yrformPROD100N;

    // Annual sum of formCropResidue.carbon
    double yrformResidueC;

    // Annual sum of formCropResidue.nitrogen
    double yrformResidueN;

    // Annual sum of formTOTPROD.carbon
    double yrformTOTPRODC;

    // Annual sum of formTOTPROD.nitrogen
    double yrformTOTPRODN;

    // Annual sum of irrigate
    double yrirrig;

    // Annual sum of nretent
    InorgN60 yrnrent;

    // Annual sum of nsretent
    InorgN60 yrnsrent;

    // Annual sum of nvretent
    InorgN60 yrnvrent;

    // Annual sum of sconvrtflx.carbon
    double yrsconvrtC;

    // Annual sum of sconvrtflx.nitrogen
    double yrsconvrtN;

    // Annual sum of slash.carbon
    double yrslashC;

    // Annual sum of slash.nitrogen
    double yrslashN;

    // Annual sum of stubble.carbon
    double yrstubC;

    // Annual sum of stubble.nitrogen
    double yrstubN;

    // Annual sum of vconvrtflx.carbon
    double yrvconvrtC;

    // Annual sum of vconvrtflx.nitrogen
    double yrvconvrtN;
    


/* *************************************************************
                   Private Parameters
************************************************************* */

     double c2n;

     double cropseedC[MAXCMNT];
     double cropseedSTRN[MAXCMNT];
     double cropseedSTON[MAXCMNT];

     double harvstC[MAXCMNT];
     double harvstN[MAXCMNT];

     double nsretconv[MAXCMNT];
     double nvretconv[MAXCMNT];

     double prod10par;
     double prod100par;

     double residueC[MAXCMNT];
     double residueN[MAXCMNT];

     double sconvert;

     double slashpar;

     double tillfactor[MAXCMNT];

     double vconvert;

     double vrespar;

};

#endif

