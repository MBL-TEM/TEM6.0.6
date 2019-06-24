/* *************************************************************
****************************************************************
TTEM606C.CPP - Terrestrial Ecosystem Model Version 6.0
****************************************************************

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

****************************************************************
************************************************************** */

#include "ttem606c.h"

// Initialization of static members

int TTEM60::avlnflag = 0;
int TTEM60::nfeed = 0;
int TTEM60::rheqflag = 0;
int TTEM60::moistlim = 0;
int TTEM60::o3flag = 0;
int TTEM60::initbase = 0;
int TTEM60::baseline = 0;
int TTEM60::intflag = 0;

int TTEM60::maxnrun = 0;
int TTEM60::equil = 0;
int TTEM60::runsize = 0;
int TTEM60::maxyears = 0;
int TTEM60::strteq = 0;
int TTEM60::endeq = 0;
int TTEM60::startyr = 0;
int TTEM60::endyr = 0;
int TTEM60::diffyr = 0;
int TTEM60::wrtyr = 0;

double TTEM60::ctol = 1.0;
double TTEM60::ntol = 0.02;
double TTEM60::wtol = 0.01;

// Initialization of adaptive integrator variables

double TTEM60::inittol = 0.01;
int TTEM60::maxit = 20;
long TTEM60::maxitmon = 2000;

double TTEM60::a1 =   0.115740741;

double   TTEM60::a3 =   0.548927875;
double  TTEM60::a31 =   0.09375;
double  TTEM60::a32 =   0.28125;

double   TTEM60::a4 =   0.535331384;
double  TTEM60::a41 =   0.879380974;
double  TTEM60::a42 =  -3.277196177;
double  TTEM60::a43 =   3.320892126;

double   TTEM60::a5 =  -0.20;
double  TTEM60::a51 =   2.032407407;
double  TTEM60::a52 =  -8.0;
double  TTEM60::a53 =   7.173489279;
double  TTEM60::a54 =  -0.2058966866;

double   TTEM60::b1 =   0.118518519;
double   TTEM60::b3 =   0.518986355;
double   TTEM60::b4 =   0.50613149;
double   TTEM60::b5 =  -0.18;
double   TTEM60::b6 =   0.036363636;
double  TTEM60::b61 =  -0.296296296;
double  TTEM60::b62 =   2.0;
double  TTEM60::b63 =  -1.381676413;
double  TTEM60::b64 =   0.45297271;
double  TTEM60::b65 =  -0.275;


/* **************************************************************
************************************************************** */

TTEM60::TTEM60() : ProcessXML60(), predstr( NUMTEM ) 
{
  tol = inittol;
  syint = 1;  
  totyr = -99;
  rheqflag = 0;

#ifdef CALIBRATE_TEM
  cal43dir = "/mnt/data/Data/Ecds/Ver43/";
  soilfile = cal43dir + "tsoil43d.ecd";

  rheqflag = 0;

  scy[0] = GET_VEGC;
  scy[1] = GET_SOLC;
  scy[2] = GET_DOC;
  scy[3] = GET_LAI;
  scy[4] = GET_NPP;
  scy[5] = GET_CDCMP;
  scy[6] = GET_RH;
  scy[7] = GET_LCHDOC;
  scy[8] = GET_NECB;

  sny[0] = GET_STRN;
  sny[1] = GET_STON;
  sny[2] = GET_SOLN;
  sny[3] = GET_DON;
  sny[4] = GET_NH4;
  sny[5] = GET_NO3;
  sny[6] = GET_VNUP;
  sny[7] = GET_NDCMP;
  sny[8] = GET_LCHDON;

  swy[0] = GET_AVLW;
  swy[1] = GET_RGRW;
  swy[2] = GET_SNWPK;
  swy[3] = GET_SGRW;
  swy[4] = GET_EET;
  swy[5] = GET_RAIN;
  swy[6] = GET_SNWINF;
  swy[7] = GET_VSM;
  swy[8] = GET_PET;

  ssty[0] = GET_TSOIL;
  ssty[1] = GET_DST00;
  ssty[2] = GET_DST05;
  ssty[3] = GET_DST10;
  ssty[4] = GET_DST20;
  ssty[5] = GET_DST50;
  ssty[6] = GET_DST100;
  ssty[7] = GET_DST200;
  ssty[8] = GET_ACTLAY;
  ssty[9] = GET_THAWPCT;

  sgy[0] = GET_GNH4;
  sgy[1] = GET_GNO3;
  sgy[2] = GET_GNMIN;
  sgy[3] = GET_NTRF;
  sgy[4] = GET_DNTRF;
  sgy[5] = GET_GNLST;
  sgy[6] = GET_NOFLX;
  sgy[7] = GET_N2OFLX;
  sgy[8] = GET_N2FLX;

#endif
  
// Identify potential output variables from TEM

// Ecosystem carbon pools determined by the integrator**********

  // vegetation carbon
  predstr.at( I_VEGC ) = "VEGC";  
  
  // reactive soil organic carbon      
  predstr.at( I_SOLC ) = "SOILORGC";   
  
  // dissolved organic carbon
  predstr.at( I_DOC ) = "DOC";


// Ecosystem nitrogen pools determined by the integrator********

  // vegetation structural nitrogen
  predstr.at( I_STRN ) = "VSTRUCTN";

  // vegetation labile nitrogen
  predstr.at( I_STON ) = "VSTOREN";

  // reactive soil organic nitrogen
  predstr.at( I_SOLN ) = "SOILORGN";  

  // dissolved organic nitrogen
  predstr.at( I_DON ) = "DON";

  // soil ammonium    
  predstr.at( I_NH4 ) = "SOILNH4";   
  
  // soil nitrate
  predstr.at( I_NO3 ) = "SOILNO3";   


// Ecosystem water pools determined by the integrator***********

  // soil moisture
  predstr.at( I_SM ) = "SMOIST";       

  // groundwater pool resulting from rainfall
  predstr.at( I_RGRW ) = "RGRNDH2O";

  // groundwater pool resulting from snow melt
  predstr.at( I_SGRW ) = "SGRNDH2O";


/// Phenology variables determined by the integrator************

  // un-normalized relative phenology variable
  predstr.at( I_UNRMLF ) = "UNRMLEAF";

  // normalized relative phenology variable (0 - 1.0)
  predstr.at( I_LEAF ) = "LEAF";

  // leaf area index
  predstr.at( I_LAI ) = "LAI";    
  
  // foliar projected cover
  predstr.at( I_FPC ) = "FPC";    


// Carbon fluxes for ecosystems ********************************

  // GPP not limited by nutrient availability
  predstr.at( I_INGPP ) = "VEGINGPP";

  // gross primary production
  predstr.at( I_GPP ) = "GPP";    

  // Direct ozone effects 
  predstr.at( I_FOZONE ) = "FOZONE";
  
  // Indirect ozone effects 
  predstr.at( I_FINDOZONE ) = "FINDOZON";

 // NPP not limited by nutrient availability
  predstr.at( I_INNPP ) = "VEGINNPP";

  // net primary production
  predstr.at( I_NPP ) = "NPP";      

  // gross plant respiration
  predstr.at( I_GPR ) = "GPR";      

  // vegetation maintenance respiration
  predstr.at( I_RVMNT ) = "RVMAINT";

  // vegetation growth respiration
  predstr.at( I_RVGRW ) = "RVGRWTH";

  // aboveground vegetation respiration
  predstr.at( I_ABVGPR ) = "ABVGPR";

  // root respiration
  predstr.at( I_ROOTGPR ) = "ROOTRESP";

  // litterfall carbon
  predstr.at( I_LTRFALC ) = "LTRFALC";   

  // carbon in decomposition of organic matter
  predstr.at( I_CDCMP ) = "CDECOMP";   

  // heterotrophic respiration
  predstr.at( I_RH ) = "RH";       

  // dissolved organic carbon production
  predstr.at( I_DOCP ) = "DOCPROD";

  // DOC leaching losses
  predstr.at( I_LCHDOC ) = "LEACHDOC";   

  // erosion of particulate organic carbon
  predstr.at( I_ERDPOC ) = "ERODEPOC";


// Nitrogen fluxes for ecosystems determined by the integrator

  // Total atmospheric N deposition
  predstr.at( I_TOTNDEP ) = "TOTNDEP";

  // Atmospheric NHX deposition 
  predstr.at( I_NH4DEP ) = "NH4DEP";

  // Atmospheric NOY deposition
  predstr.at( I_NO3DEP ) = "NO3DEP";

  //Atmospheric N deposition resulting from earlier fires
  predstr.at( I_FIRENTOTDEP ) = "FIRENTOTDEP";

  predstr.at( I_FIRENH4DEP ) = "FIRENH4DEP";

  predstr.at( I_FIRENO3DEP ) = "FIRENO3DEP";

  // nitrogen fertilization
  predstr.at( I_AGFRTN ) = "AGFERTN";

  // Biological nitrogen fixation
  predstr.at( I_BNFIX ) = "BIOLNFIX";

  // Symbiotic nitrogen fixation
  predstr.at( I_SNFIX ) = "SYMNFIX";

  // Asymbiotic nitrogen fixation
  predstr.at( I_ANFIX ) = "ASYMNFIX";

  // VEGNUP not limited by carbon availability
  predstr.at( I_INNUP ) = "VEGINNUP";

  // VNH4UP not limited by carbon availability
  predstr.at( I_INNH4UP ) = "VINNH4UP";

  // VNO3UP not limited by carbon availability
  predstr.at( I_INNO3UP ) = "VINNO3UP";

  // nitrogen uptake by vegetation
  predstr.at( I_VNUP ) = "VEGNUP";

  // ammonium uptake by vegetation
  predstr.at( I_VNH4UP ) = "VEGNH4UP";

  // nitrate uptake by vegetation
  predstr.at( I_VNO3UP ) = "VEGNO3UP";

  // vegetation nitrogen uptake for structural components
  predstr.at( I_VSUP ) = "VEGSUP";

  // vegetation nitrogen uptake for labile components
  predstr.at( I_VLUP ) = "VEGLUP";

  // nitrogen mobilization by vegetation
  predstr.at( I_VNMBL ) = "VNMOBIL";

  // nitrogen resorption by vegetation
  predstr.at( I_VNRSRB ) = "VNRESORB";

  // litterfall nitrogen from vegetation
  predstr.at( I_LTRFALN ) = "LTRFALN";

  // nitrogen in decomposition of organic matter
  predstr.at( I_NDCMP ) = "NDECOMP";   

  // dissolved organic nitrogen production
  predstr.at( I_DONP ) = "DONPROD";

  // gross nitrogen mineralization
  predstr.at( I_GMIN ) = "GROSNMIN";

  // ammonium immobilization
  predstr.at( I_NH4IMM ) = "NH4IMMOB";

  // nitrate immobilization
//  predstr.at( I_NO3IMM ) = "NO3IMMOB";

  // total nitrogen immobilization
  predstr.at( I_NIMM ) = "NIMMOBIL";

  // net nitrogen mineralization
  predstr.at( I_NMIN ) = "NETNMIN";

  // abiotic NH4 immobilization
  predstr.at( I_AIMMNH4 ) = "AIMMNH4";

  // abiotic NO3 immobilization
  predstr.at( I_AIMMNO3 ) = "AIMMNO3";

  // ammonia volatilization
  predstr.at( I_AMMN ) = "AMMNVOL";

  // nitrification
  predstr.at( I_NTRF ) = "NITRIF";     
  
  // Nitrate production
  predstr.at( I_NO3P ) = "NO3PROD";    
  
  // Microbial nitric oxide production
  predstr.at( I_NOP ) = "NOPROD";      
  
  // Microbial nitrous oxide production
  predstr.at( I_N2OP ) = "N2OPROD";    
  
  // microbial dinitrogen production
  predstr.at( I_N2P ) = "N2PROD";      
  
  // Denitrification
  predstr.at( I_DNTRF ) = "DENITRIF";  

  // Soil ammonia flux
  predstr.at( I_NH3FLX ) = "NH3FLUX";
  
  // Soil nitric oxide flux
  predstr.at( I_NOFLX ) = "NOFLUX";
  
  // Soil nitrous oxide flux
  predstr.at( I_N2OFLX ) = "N2OFLUX";
  
  // Soil dinitrogen flux
  predstr.at( I_N2FLX ) = "N2FLUX";
  
  // Ammonium leaching losses
  predstr.at( I_LCHNH4 ) = "LEACHNH4";  

  // Nitrate leaching losses
  predstr.at( I_LCHNO3 ) = "LEACHNO3";  
  
  // Dissolved organic nitrogen leaching losses
  predstr.at( I_LCHDON ) = "LEACHDON";  

  // Erosion of particulate organic nitrogen
  predstr.at( I_ERDPON ) = "ERODEPON";


// Water fluxes determined by the integrator********************

  // Irrigation
  predstr.at( I_AGIRRIG ) = "IRRIGATE"; 

  // Initial estimated evapotranspiration
  predstr.at( I_INEET ) = "INEET";

  // estimated evapotranspiration
  predstr.at( I_EET ) = "EET";

  // percolation of rainwater through soil profile
  predstr.at( I_RPERC ) = "RPERC";

  // percolation of snowmelt through soil profile
  predstr.at( I_SPERC ) = "SPERC";

  // runoff of rainwater
  predstr.at( I_RRUN ) = "RRUN";
  
  // runoff of snowmelt
  predstr.at( I_SRUN ) = "SRUN";        


// Other ecosystem carbon pools ********************************

  // nonreactive soil organic carbon      
  predstr.at(I_NSOLC ) = "NONSOLC";   

  // total soil organic carbon      
  predstr.at( I_TSOLC ) = "TOTSOLC";   

  // total carbon pool found in ecosystem excluding products
  predstr.at( I_TOTEC ) = "TOTEC";

  // total carbon
  predstr.at( I_TOTC ) = "TOTALC";     

// Other ecosystem nitrogen pools ******************************

  // total nitrogen stored in vegetation
  predstr.at( I_VEGN ) = "VEGN";

  // nonreactive soil organic nitrogen
  predstr.at( I_NSOLN ) = "NONSOLN";  

  // total soil organic nitrogen
  predstr.at( I_TSOLN ) = "TOTSOLN";  

  // soil available nitrogen
  predstr.at( I_AVLN ) = "AVAILN";


// Other ecosystem water pools ******************************

  predstr.at( I_SNWPCK ) = "SNOWPACK";  // snowpack

  // available soil moisture
  predstr.at( I_AVLW ) = "AVAILW";

  // volumetric soil moisture
  predstr.at( I_VSM ) = "VSM";      

  // soil moisture expressed as percent total porosity
  predstr.at( I_PCTP ) = "PCTP";



// Other carbon fluxes for ecosystems **************************

  // forage carbon
  predstr.at( I_FORAGEC ) = "FORAGEC";
   
  // manure carbon
  predstr.at( I_MANUREC ) = "MANUREC";

  // animal respiration
  predstr.at( I_ANIMALR ) = "ANIMALR";
  
  // soil respiration
  predstr.at( I_RSOIL ) = "RSOIL";  

  // net ecosystem production
  predstr.at( I_NEP ) = "NEP";     

  // net carbon exchange of ecosystem with atmosphere
  predstr.at( I_NCE ) = "NCE";

  // net ecosystem carbon balance
  predstr.at( I_NECB ) = "NECB";


// Other nitrogen fluxes for ecosystems ************************

  // forage nitrogen
  predstr.at( I_FORAGEN ) = "FORAGEN";
   
  // manure nitrogen
  predstr.at( I_MANUREN ) = "MANUREN";

  // urine
  predstr.at( I_URINE ) = "URINE";
  
  // total nitrogen inputs into ecosystem
  predstr.at( I_NINP ) = "NINPUT";

  // Total nitrogen losses from ecosystems
  predstr.at( I_NLST ) = "NLOST";

  // net terrestrial nitrogen balance
  predstr.at( I_NENB ) = "NENB";


// Other water fluxes ******************************************

  // potential evapotranspiration
  predstr.at( I_PET ) = "PET";

  // infiltration into the soil of water from snowmelt
  predstr.at( I_SNWINF ) = "SNOWINF";

  // water yield
  predstr.at( I_WYLD ) = "H2OYIELD";    


// Carbon stocks in products ***********************************

  // carbon in agricultural products
  predstr.at( I_AGPRDC ) = "AGPRODC";

  // carbon pool of products that decompose in 10 years
  predstr.at( I_PROD10C ) = "PROD10C";

  // carbon pool of products that decompose in 100 years
  predstr.at( I_PROD100C ) = "PROD100C";

  // carbon in all product pools
  predstr.at( I_TOTPRDC ) = "TOTPRODC";


// Carbon stocks in crop residue and stubble********************

  // carbon in crop residue
  predstr.at( I_RESIDC ) = "RESIDC";

  // stubble carbon
  predstr.at( I_AGSTUBC ) = "CRPSTUBC";   


// Nitrogen stocks in products *********************************

  // nitrogen in agricultural products
  predstr.at( I_AGPRDN ) = "AGPRODN";

  // nitrogen pool of products that decompose in 10 years
  predstr.at( I_PROD10N ) = "PROD10N";

  // nitrogen pool of products that decompose in 100 years
  predstr.at( I_PROD100N ) = "PROD100N";

  // nitrogen in all product pools
  predstr.at( I_TOTPRDN ) = "TOTPRODN";


// Nitrogen stocks in crop residue and stubble******************

  // nitrogen in crop residue
  predstr.at( I_RESIDN ) = "RESIDN";

  // stubble nitrogen
  predstr.at( I_AGSTUBN ) = "CRPSTUBN";


// Carbon fluxes associated with agricultural conversion *******

  // carbon loss from the ecosystem during conversion
  predstr.at( I_CNVRTC ) = "CONVERTC";

  // carbon loss from vegetation during conversion
  predstr.at( I_VCNVRTC ) = "VCONVRTC";

  // carbon loss from soils during conversion
  predstr.at( I_SCNVRTC ) = "SCONVRTC";

  // carbon associated with slash left after conversion
  predstr.at( I_SLASHC ) = "SLASHC";

  // carbon flux from ecosystem (NEP - CONVERTC)
  predstr.at( I_CFLX ) = "CFLUX";


// Nitrogen fluxes associated with agricultural conversion *****

  // nitrogen loss from the ecosystem during conversion
  predstr.at( I_CNVRTN ) = "CONVERTN";

  // nitrogen loss from vegetation during conversion
  predstr.at( I_VCNVRTN ) = "VCONVRTN";

  // nitrogen loss from soils during conversion
  predstr.at( I_SCNVRTN ) = "SCONVRTN";

  // nitrogen associated with slash left after conversion
  predstr.at( I_SLASHN ) = "SLASHN";

  // Total organic N mineralized and retained in ecosystem
  //   after disturbance
  predstr.at( I_NTOTRTNT ) = "NTOTRETENT";

  predstr.at( I_NH4RTNT ) = "NH4RETENT";

  predstr.at( I_NO3RTNT ) = "NO3RETENT";

  // Vegetation N mineralized and retained in ecosystem
  //   after disturbance
  predstr.at( I_VNTOTRTNT ) = "VNTOTRETENT";

  predstr.at( I_VNH4RTNT ) = "VNH4RETENT";

  predstr.at( I_VNO3RTNT ) = "VNO3RETENT";

  // Soil organic N mineralized and retained in ecosystem
  //   after disturbance
  predstr.at( I_SNTOTRTNT ) = "SNTOTRETENT";

  predstr.at( I_SNH4RTNT ) = "SNH4RETENT";

  predstr.at( I_SNO3RTNT ) = "SNO3RETENT";

// Carbon and nitrogen fluxes to/from products *****************

  // carbon loss to formation of agricultural products
  predstr.at( I_AGFPRDC ) = "AGFPRODC";

  // nitrogen loss to formation of agricultural products
  predstr.at( I_AGFPRDN ) = "AGFPRODN";

  // carbon loss to crop residue
  predstr.at( I_FRESIDC ) = "FRESIDC";

  // nitrogen loss to crop residue
  predstr.at( I_FRESIDN ) = "FRESIDN";

  // carbon loss to resulting from decomposition of agricultural
  //   products
  predstr.at( I_AGPRDFC ) = "AGPRODFC";

  // nitrogen loss resulting from decomposition of agricultural
  //   products
  predstr.at( I_AGPRDFN ) = "AGPRODFN";

  // carbon loss from crop residue
  predstr.at( I_RESIDFC ) = "RESIDFC";

  // nitrogen loss from crop residue
  predstr.at( I_RESIDFN ) = "RESIDFN";

  // carbon loss to formation of products that decompose in
  //  10 years
  predstr.at( I_PRDF10C ) = "PRDF10C";

  // nitrogen loss to formation of products that decompose in
  //   10 years
  predstr.at( I_PRDF10N ) = "PRDF10N";

  // carbon loss resulting from decomposition of PROD10C
  predstr.at( I_PRD10FC ) = "PRD10FC";

  // nitrogen loss resulting from decomposition of PROD10N
  predstr.at( I_PRD10FN ) = "PRD10FN";

  // carbon loss to formation of products that decompose in
  //  100 years
  predstr.at( I_PRDF100C ) = "PRDF100C";

  // nitrogen loss to formation of products that decompose in
  //   100 years
  predstr.at( I_PRDF100N ) = "PRDF100N";

  // carbon loss resulting from decomposition of PROD100C
  predstr.at( I_PRD100FC ) = "PRD100FC";

  // nitrogen loss resulting from decomposition of PROD100N
  predstr.at( I_PRD100FN ) = "PRD100FN";

  // carbon loss to the formation of all products
  predstr.at( I_TOTFPRDC ) = "TOTFPRDC";

  // nitrogen loss to the formation of all products
  predstr.at( I_TOTFPRDN ) = "TOTFPRDN";

  // carbon loss resulting from decomposition of all products
  predstr.at( I_TOTPRDFC ) = "TOTPRDFC";

  // nitrogen loss resulting from decomposition of all products
  predstr.at( I_TOTPRDFN ) = "TOTPRDFN";


// Agro-Ecosystem carbon and nitrogen pools *********************

  // crop carbon
  predstr.at( I_CROPC ) = "CROPC";       

  // carbon in natural vegetation
  predstr.at( I_NATVEGC ) = "NATVEGC";

  // crop nitrogen
  predstr.at( I_CROPN ) = "CROPN";       

  // nitrogen in natural vegetation
  predstr.at( I_NATVEGN ) = "NATVEGN";

  // crop structural N
  predstr.at( I_CSTRN ) = "CROPSTRN";    

  // structural N in natural vegetation
  predstr.at( I_NATSTRN ) = "NATSTRN";

  // crop labile N
  predstr.at( I_CSTON ) = "CROPSTON";    

  // labile N stored in natural vegetation
  predstr.at( I_NATSTON ) = "NATSTON";


// Crop phenology **********************************************

  // unnormalized leaf in crops
  predstr.at( I_CROPULF ) = "CRPUNMLF";

  // unnormalized leaf in natural vegetation
  predstr.at( I_NATULF ) = "NATUNMLF";

  // leaf of crops
  predstr.at ( I_CROPLEAF ) = "CROPLEAF";

  // leaf of natural vegetation
  predstr.at( I_NATLEAF ) = "NATLEAF";

  // leaf area index (LAI) of crops
  predstr.at( I_CROPLAI ) = "CROPLAI";

  // leaf area index (LAI) of natural vegetation
  predstr.at( I_NATLAI ) = "NATLAI";

  // foliar projected cover (FPC) of crops
  predstr.at( I_CROPFPC ) = "CROPFPC";

  // foliar projected cover (FPC) of natural vegetation
  predstr.at( I_NATFPC ) = "NATFPC";


// Additional carbon fluxes for agro-ecosystems *****************

  // GPP of crops not limited by nutrient availability
  predstr.at( I_AGINGPP ) = "CRPINGPP";

  // GPP of natural vegetation not limited by 
  //   nutrient availability
  predstr.at( I_NATINGPP ) = "NATINGPP";

  // gross primary production (GPP) of crops
  predstr.at( I_AGGPP ) = "CROPGPP";

  // gross primary production of natural vegetation
  predstr.at( I_NATGPP ) = "NATGPP";

  // NPP of crops not limited by nutrient availability
  predstr.at( I_AGINNPP ) = "CRPINNPP";

  // NPP of natural vegetation not limited by 
  //   nutrient availability
  predstr.at( I_NATINNPP ) = "NATINNPP";

  // net primary production (NPP) of crops
  predstr.at( I_AGNPP ) = "CROPNPP";

  // net primary production (NPP) of natural vegetation
  predstr.at( I_NATNPP ) = "NATNPP";

  // gross plant respiration of crops
  predstr.at( I_AGGPR ) = "CROPGPR";

  // gross plant respiration of natural vegetation
  predstr.at( I_NATGPR ) = "NATGPR";

  // maintenance respiration of crop plants
  predstr.at( I_AGRVMNT ) = "CRPRMNT";

  // maintenance respiration of natural vegetation
  predstr.at( I_NATRVMNT ) = "NATRVMNT";

  // growth respiration of crop plants
  predstr.at( I_AGRVGRW ) = "CRPRGRW";

  // growth respiration of natural vegetation
  predstr.at( I_NATRVGRW ) = "NATRGRW";

  // litterfall carbon from crops
  predstr.at( I_AGLTRC ) = "CROPLTRC";

  // litterfall carbon from natural vegetation
  predstr.at( I_NATLTRC ) = "NATLTRC";

  // Additional nitrogen fluxes for agro-ecosystems ************

  // symbiotic nitrogen fixation with crops
  predstr.at( I_AGSNFX ) = "CRPSNFIX";

  // symbiotic nitrogen fixation with natural vegetation
  predstr.at( I_NATSNFX ) = "NATSNFIX";

  // nitrogen uptake by crops not limited by carbon availability
  predstr.at( I_AGINNUP ) = "CRPINNUP";

  // nitrogen uptake by natural vegetation not limited by carbon
  //   availability
  predstr.at( I_NATINNUP ) = "NATINNUP";

  // ammonium uptake by crops not limited by carbon availability
  predstr.at( I_AINNH4UP ) = "CINNH4UP";

  // ammonium uptake vy natural vegetation not limited by carbon
  //  availability
  predstr.at( I_NINNH4UP ) = "NINNH4UP";

  // nitrate uptake by crops not limited by carbon availability
  predstr.at( I_AINNO3UP ) = "CINNO3UP";

  // nitrate uptake by natural vegetation not limited by carbon
  //   availability
  predstr.at( I_NINNO3UP ) = "NINNO3UP";

  // nitrogen uptake by crops
  predstr.at( I_AGVNUP ) = "CROPNUP";

  // nitrogen uptake by natural vegetation
  predstr.at( I_NATVNUP ) = "NATVNUP";

  // ammonium uptake by crops
  predstr.at( I_AGVNH4UP ) = "CRPNH4UP";

  // ammonium uptake by natural vegetation
  predstr.at( I_NVNH4UP ) = "NVNH4UP";

  // nitrate uptake by crops
  predstr.at( I_AGVNO3UP ) = "CRPNO3UP";

  // nitrate uptake by natural vegetation
  predstr.at( I_NVNO3UP ) = "NVNO3UP";

  // nitrogen uptake for structural components of crops
  predstr.at( I_AGVSUP ) = "CROPSUP";

  // nitrogen uptake for structural components of natural
  //  vegetation
  predstr.at( I_NATVSUP ) = "NATVSUP";

  // nitrogen uptake for labile components of crops
  predstr.at( I_AGVLUP ) = "CROPLUP";

  // nitrogen uptake for labile components of natural vegetation
  predstr.at( I_NATVLUP ) = "NATVLUP";

  // nitrogen mobilization by crops
  predstr.at( I_AGVNMBL ) = "CRPNMOBL";

  // nitrogen mobilization by natural vegetation
  predstr.at( I_NATVNMBL ) = "NATVNMBL";

  // nitrogen resorption by crops
  predstr.at( I_AGVNRSRB ) = "CRPNRSRB";

  // nitrogen resorption by natural vegetation
  predstr.at( I_NVNRSRB ) = "NVNRSRB";

  // litterfall nitrogen from crops
  predstr.at( I_AGLTRN ) = "CROPLTRN";

  //litterfall nitrogen from natural vegetation
  predstr.at( I_NATLTRN ) = "NATLTRN";

// Soil thermal variables **************************************

  // Soil temperature for 0 - 20 cm
  predstr.at( I_TSOIL ) = "TSOIL";
  
  // Soil temperature at the ground surface
  predstr.at( I_DST0 ) = "DST0";
  
  // Soil temperature at 5 cm depth
  predstr.at( I_DST5 ) = "DST5";
  
  // Soil temperature at 10 cm depth
  predstr.at( I_DST10 ) = "DST10";
  
  // Soil temperature at 20 cm depth
  predstr.at( I_DST20 ) = "DST20";
  
  // Soil temperature at 50 cm depth
  predstr.at( I_DST50 ) = "DST50";
  
  // Soil temperature at 100 cm depth
  predstr.at( I_DST100 ) = "DST100";
  
  // Soil temperature at 200 cm depth
  predstr.at( I_DST200 ) = "DST200";
  
  predstr.at( I_FRONTD ) = "FRONTD";
  
  predstr.at( I_THAWBE ) = "THAWBE";
  
  predstr.at( I_THAWEND ) = "THAWEND";

// Percentage of month with thawed ground **********************

  predstr.at( I_THAWPCT ) = "THAWPCT";

// Percentage of month with thawed ground **********************

  predstr.at( I_ACTLAYER ) = "ACTLAYER";


  dbugflg = 0;

};

/* **************************************************************
************************* Functions *****************************
************************************************************** */


/* *************************************************************
************************************************************* */

int TTEM60::adapt( const int& numeq, 
                   double pstate[], 
                   const double& ptol, 
                   const int& pdm )
{

  int i;
  double ipart;
  double fpart;
  double time = ZERO;
  double dt = 1.0;
  int mflag = 0;
  long nintmon = 0;
  double oldstate[NUMEQ];

  blackhol = 0;
  while( time != 1.0 )
  {
    test = REJECT;
    if( 1 == syint )
    {
      while( test != ACCEPT )
      {
	rkf( numeq, pstate, dt, pdm );

	test = boundcon( dum4, error, ptol );

        #ifdef CALIBRATE_TEM
	  if( test != ACCEPT )
          {
            // Display ODE errors to DOS screen

            pcdisplayODEerr( test, pstate );
          }
        #endif
	
	if( dt <= pow( 0.5, maxit ) )
        {
	  test = ACCEPT;
	  mflag = 1;
        
          if( 0 == nintmon )
          {
            for( i = 0; i < numeq; ++i ) 
            { 
              oldstate[i] = pstate[i]; 
            }
          }
	
	  ++nintmon;
	}

        if( ACCEPT == test )
        {
          for( i = 0; i < numeq; ++i ) { pstate[i] = dum4[i]; }
        
          time += dt;

          #ifdef CALIBRATE_TEM
            // Display time updates to the DOS screen

            pcdisplayDT( time, dt );
          #endif

          fpart = modf( (0.01 + (time/(2.0*dt))), &ipart );
        
          if( fpart < 0.1 && dt < 1.0 ) { dt *= 2.0; }
        }
        else { dt *= 0.500; }

        if( nintmon == maxitmon )
        {
          time = 1.0;
          blackhol = 1;
        
          for( i = 0; i < numeq; ++i ) 
          { 
            pstate[i] = oldstate[i]; 
          }
        }
      }
    }    /* end rkf integrator */
  }      /* end time while */

  return mflag;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::askODE( ofstream& rflog1 )
{


/* **************************************************************
	      Parameters for Adaptive Integrator
************************************************************** */
  #ifdef CALIBRATE_TEM
    nocbreak();
    echo();
    printw( "\nEnter the proportional tolerance for the integrator: " );
    refresh();

    scanw( "%f", &inittol );

    printw( "\nEnter the maximum number of iterations in the integrator: " );
    refresh();

    scanw( "%d", &maxit );

    printw( "\nEnter the maximum number of times in a month that the\n" );
    printw( "integrator can reach the maximum number of iterations: " );
    refresh();

    scanw( "%ld", &maxitmon );

  #else
    cout << endl;
    cout << "Enter the proportional tolerance for the integrator:";
    cout << endl;

    cin >> inittol;

    rflog1 << endl;
    rflog1 << "Enter the proportional tolerance for the integrator: ";
    rflog1 << inittol << endl;

    cout << endl;
    cout << "Enter the maximum number of iterations in the integrator:";
    cout << endl;

    cin >> maxit;

    rflog1 << endl;
    rflog1 << "Enter the maximum number of iterations in the integrator: ";
    rflog1 << maxit << endl;

    cout << endl;
    cout << "Enter the maximum number of times in a month that the";
    cout << endl;
    cout << "integrator can reach the maximum number of iterations:";
    cout << endl;

    cin >> maxitmon;

    rflog1 << endl;
    rflog1 << "Enter the maximum number of times in a month that the" << endl;
    rflog1 << "integrator can reach the maximum number of iterations: ";
    rflog1 << maxitmon << endl;
  #endif
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::asphaltDynamics( const int& pdm, double pstate[] )
{

  soil.setPCTP( ZERO );

  soil.setVSM( ZERO );

  // Phenology

  veg.setUNNORMLEAF( ZERO );

  veg.setLEAF( ZERO );

  veg.setLAI( ZERO );

  veg.setFPC( ZERO );

  // Carbon fluxes in ecosystems

  veg.setINGPP( ZERO );

  veg.setGPP( ZERO );

  veg.setFOZONE( ZERO );

  veg.setFINDOZONE( ZERO );

  veg.setINNPP( ZERO );

  veg.setNPP( ZERO );

  veg.setGPR( ZERO );

  veg.setRMAINT( ZERO );

  veg.setRGRWTH( ZERO );

  veg.setABVGPR( ZERO );

  veg.setROOTRESP( ZERO );

  veg.setLTRFALC( ZERO );

  microbe.setDECOMP( ZERO );
  
  microbe.setRH( ZERO );
  
  microbe.setDOCPROD( ZERO );

  soil.setLEACHDOC( ZERO );

  soil.setERODEPOC( ZERO );


  // Nitrogen fluxes in ecosystems

  ag.fertn = ZERO;

  bnfix = ZERO;

  microbe.setNFIX( ZERO );

  veg.setNFIX( ZERO );
  
  microbe.setNFIX( ZERO );

  veg.setINUPTAKE( ZERO );
  veg.setINH4UPTAKE( ZERO );
  veg.setINO3UPTAKE( ZERO );

  veg.setNUPTAKE( ZERO );
  veg.setNH4UPTAKE( ZERO );
  veg.setNO3UPTAKE( ZERO );

  veg.setSUPTAKE( ZERO );
  veg.setLUPTAKE( ZERO );
  veg.setNMOBIL( ZERO );
  veg.setNRESORB( ZERO );

  veg.setLTRFALN( ZERO );

  microbe.setNDECOMP( ZERO );

  microbe.setDONPROD( ZERO );

  microbe.setGROSSNMIN( ZERO );

  microbe.setIMMNH4( ZERO );

  microbe.setIMMOB( ZERO );

  microbe.setNETNMIN( ZERO );

  soil.setLEACHDON( ZERO );

  soil.setERODEPON( ZERO );

  soil.setLEACHNH4( atms.getNH4DEP() 
                    + ag.getNH4RETENT()
                    + ag.getFIRENH4DEP() );


  soil.setLEACHNO3( atms.getNO3DEP() 
                    + ag.getNO3RETENT() 
                    + ag.getFIRENO3DEP() );

  microbe.setAMMNVOL( ZERO );

  microbe.setNITRIF( ZERO );
  microbe.setNO3PROD( ZERO );
  microbe.setNOPROD( ZERO );
  microbe.setN2OPROD( ZERO );
  microbe.setN2PROD( ZERO );

  microbe.setDENITRIF( ZERO );


  soil.setNH3FLUX( ZERO );

  soil.setNOFLUX( ZERO );
  soil.setN2OFLUX( ZERO );
  soil.setN2FLUX( ZERO );

  // Water fluxes

  ag.irrigate = ZERO;
  
  soil.setINEET( ZERO );

  if( atms.getPET() < (0.5 * atms.getRAIN()) )
  {
    soil.setEET( atms.getPET() );
  }
  else
  {
    soil.setEET( 0.5 * atms.getRAIN() );
  }


  soil.setRPERC( atms.getRAIN() - soil.getEET() );
  soil.setSPERC( soil.getSNOWINF() );

  soil.setRRUN( soil.getRPERC() );
  soil.setSRUN( soil.getSPERC() );

};

/* *************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

int TTEM60::boundcon( double ptstate[],
                      double err[],
                      const double& ptol )
{

  int test = ACCEPT;

// Check carbon and nitrogen state variables

  if( err[I_VEGC] > fabs( ptol * ptstate[I_VEGC] ) )
  {
    return test = temkey( I_VEGC )+1;
  }

  if( err[I_SOLC] > fabs( ptol * ptstate[I_SOLC] ) )
  {
    return test = temkey( I_SOLC )+1;
  }

  if( err[I_DOC] > fabs( ptol * ptstate[I_DOC] ) )
  {
    return test = temkey( I_DOC )+1;
  }

  if( 1 == nfeed
      && err[I_STRN] > fabs( ptol * ptstate[I_STRN] ) )
  {
    return test = temkey( I_STRN )+1;
  }

  if( 1 == nfeed
      && err[I_STON] > fabs( ptol * ptstate[I_STON] ) )
  {
    return test = temkey( I_STON )+1;
  }

  if( 1 == nfeed
      && err[I_SOLN] > fabs( ptol * ptstate[I_SOLN] ) )
  {
    return test = temkey( I_SOLN )+1;
  }

  if( 1 == nfeed
      && err[I_DON] > fabs( ptol * ptstate[I_DON] ) )
  {
    return test = temkey( I_DON )+1;
  }

  if( 1 == nfeed
      && err[I_NH4] > fabs( ptol * ptstate[I_NH4] ) )
  {
    return test = temkey( I_NH4 )+1;
  }

  if( 1 == nfeed
      && err[I_NO3] > fabs( ptol * ptstate[I_NO3] ) )
  {
    return test = temkey( I_NO3 )+1;
  }

  if( err[I_GPP] > fabs( ptol * ptstate[I_GPP] ) )
  {
    return test = temkey( I_GPP )+1;
  }

  if( err[I_NPP] > fabs( ptol * ptstate[I_NPP] ) )
  {
    return test = temkey( I_NPP )+1;
  }

  if( err[I_RVMNT] > fabs( ptol * ptstate[I_RVMNT] ) )
  {
    return test = temkey( I_RVMNT )+1;
  }

  if( 1 == nfeed
      && err[I_VNH4UP] > fabs( ptol * ptstate[I_VNH4UP] ) )
  {
    return test = temkey( I_VNH4UP )+1;
  }

  if( 1 == nfeed
      && err[I_VNO3UP] > fabs( ptol * ptstate[I_VNO3UP] ) )
  {
    return test = temkey( I_VNO3UP )+1;
  }

  if( 1 == nfeed
      && err[I_VSUP] > fabs( ptol * ptstate[I_VSUP] ) )
  {
    return test = temkey( I_VSUP )+1;
  }

  if( 1 == nfeed
      && err[I_VNMBL] > fabs( ptol * ptstate[I_VNMBL] ) )
  {
    return test = temkey( I_VNMBL )+1;
  }


  // Check water state variables

  if( err[I_SM]  > fabs( ptol * ptstate[I_SM] ) )
  {
    return test = temkey( I_SM )+1;
  }

  if( err[I_RGRW]  > fabs( ptol * ptstate[I_RGRW] ) )
  {
    return test = temkey( I_RGRW )+1;
  }

  if( err[I_SGRW]  > fabs( ptol * ptstate[I_SGRW] ) )
  {
    return test = temkey( I_SGRW )+1;
  }

  if( err[I_RPERC]  > fabs( ptol * ptstate[I_RPERC] ) )
  {
    return test = temkey( I_RPERC )+1;
  }

  if( err[I_EET]  > fabs( ptol * ptstate[I_EET] ) )
  {
    return test = temkey( I_EET )+1;
  }


  return test;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::cropDynamics( const int& pdm, double pstate[] )
{
  double avlNH4;
  double avlNO3;

  InorgN60 extraN;

//  int irrgflag = 1;

  double newpctp;
  double newsh2o;
  double newvsm;

  int perennial = 0;

  double propReact;
 
 
  soil.updateHydrology( elev,
                        atms.getTAIR(),
                        atms.getPREVTAIR(),
                        atms.getPREV2TAIR(),
                        atms.getRAIN(),
                        atms.getPET(),
                        pstate[I_SM],
                        pstate[I_RGRW],
                        pstate[I_SGRW],
                        ag.irrgflag,
                        ag.irrigate,
                        pdm );
                          

  
  // Assume no agricultural N fertilization (ag.fertn) and no
  //  nutrients resulting from agricultural conversion

  ag.fertn = ZERO;
  microbe.setAMMNVOL( ZERO );


  // Determine biological N fixation and partition it between
  //   symbiotic N fixation (veg.nfix) and nonsymbiotic N
  //   fixation (microbe.nfix)

  if( soil.getEET() > 0.1 )
  {
    bnfix = veg.getNFIXPARA( ag.cmnt ) * soil.getEET()
            + veg.getNFIXPARB( ag.cmnt );
  }
  else { bnfix = ZERO; }

  microbe.setNFIX( (bnfix * microbe.getNFIXPAR( ag.cmnt )) ) ;
  
  if( microbe.getNFIX() < ZERO ) 
  { 
    microbe.setNFIX( ZERO ); 
  }

  veg.setNFIX( (bnfix - microbe.getNFIX()) );

  if( veg.getNFIX() < ZERO ) { veg.setNFIX( ZERO ); }
  

  // Reduce EET if vegetation is not mature
  
  soil.setEVAPORATION( soil.getEET() 
                       * (1.0 - veg.getPROPTRANS( ag.cmnt)) );
					   
  veg.updateFoliage( ag.cmnt, pstate[I_VEGC], soil.getEET() );                       

  soil.setEET( veg.getTRANSPIRATION() + soil.getEVAPORATION() );


  // Assume wetlands are wetter by the wfpsoff for determining
  //   moisture effects on vegetation and microbes

  newpctp = soil.getPCTP() + soil.getWFPSOFF();
  
  newsh2o = (newpctp * soil.getTOTPOR() * soil.getROOTZ()) 
		    / (100.0 * soil.getACTLAYER()); 

  newvsm = newsh2o / (soil.getROOTZ() * 1000.0);


  soil.setKH2O( newvsm, moistlim );

  // Get proportion of unfrozen organic matter in rooting zone
  
  propReact = soil.getThawedReactiveSOMProp( veg.cmnt );
  
  avlNH4 = pstate[I_NH4] * soil.getACTLAYER() / soil.getROOTZ();
  avlNO3 = pstate[I_NO3] * soil.getACTLAYER() / soil.getROOTZ();
  
  // Note: Microbes are assumed to be acting on "old" carbon
  //   (i.e. natural vegetation - veg.cmnt) rather than 
  //   "new" carbon associated with crops (i.e. ag.cmnt)

  microbe.updateDynamics( veg.cmnt,
                          soil.getPCTFLDCAP(),
                          soil.getACTLAYER(),
                          (pstate[I_SOLC] * propReact),
                          (pstate[I_SOLN] * propReact),
                          newsh2o,
                          newvsm,
                          avlNH4,
                          (atms.getNH4DEP()+ ag.getNH4RETENT() + ag.getFIRENH4DEP()),
                          moistlim,
                          ag.tillflag,
                          ag.getTILLFACTOR( veg.cmnt ),
                          soil.getKH2O() );

  if( ag.getGROWDD() >= GDDSEED )
  {
    if( ag.getCROPPRVPETMX() < atms.getPET() )
    {
      ag.setCROPPRVPETMX( atms.getPET() );
    }

    if( atms.getPRVPETMX() < ag.getCROPPRVPETMX() )
    {
      atms.setPRVPETMX( ag.getCROPPRVPETMX() );
    }


    if( 0 == moistlim )
    {
      if( ag.getCROPPRVEETMX() < atms.getPET() )
      {
        ag.setCROPPRVEETMX( atms.getPET() );
      }
    }
    else
    {
      if( ag.getCROPPRVEETMX() < soil.getEET() )
      {
        ag.setCROPPRVEETMX( soil.getEET() );
      }
    }

    if( soil.getPRVEETMX() < ag.getCROPPRVEETMX() )
    {
      soil.setPRVEETMX( ag.getCROPPRVEETMX() );
    }

    extraN.total = ag.getNTOTRETENT() + ag.getFIRENTOTDEP();
    extraN.nh4 = ag.getNH4RETENT() + ag.getFIRENH4DEP();
    extraN.no3 = ag.getNO3RETENT() + ag.getFIRENO3DEP();

    veg.updateDynamics( ag.cmnt,
                        atms.getCO2(),
                        atms.getAOT40(),
                        atms.getNDEP(),
                        extraN,
                        atms.getPAR(),
                        atms.getPET(),
                        atms.getPRVPETMX(),
                        soil.getEET(),
                        soil.getPRVEETMX(),
                        pstate[I_VEGC],
                        pstate[I_STRN],
                        pstate[I_STON],
                        newsh2o,
                        avlNH4,
                        avlNO3,
                        moistlim,
                        nfeed,
                        o3flag,
                        ag.state,
                        perennial,
                        totyr,
                        ag.fertflag,
                        soil.getKH2O(),
                        microbe.getNETNMIN(),
                        microbe.getAMMNVOL(),
                        microbe.getNITRIF(),
                        microbe.getNO3PROD(),
                        ag.fertn ); 
  }                    
  else
  {
    // No crop plants exist - set all monthly fluxes to zero
    
    veg.resetMonthlyFluxes();
  }


  // Determine carbon and nitrogen leaching losses
  
  soil.updateLeachingLosses( veg.cmnt,
                             (pstate[I_DOC] * propReact), 
                             (pstate[I_DON] * propReact), 
                             avlNO3, 
                             (pstate[I_SM] * soil.getACTLAYER() / soil.getROOTZ()) );
  

  if ( soil.getLEACHDOC() > (pstate[I_DOC]  
       + microbe.getDOCPROD()) )
  {
    soil.setLEACHDOC( (pstate[I_DOC] + microbe.getDOCPROD()) );
  }

  if ( soil.getLEACHDON() > (pstate[I_DON] 
         + microbe.getDONPROD()) )
  {
    soil.setLEACHDON( (pstate[I_DON] + microbe.getDONPROD()) );
  }

  
  // Determine loss of POC through erosion
  
  soil.setERODEPOC( ZERO );


  // Determine loss of PON through erosion
  
  soil.setERODEPON( ZERO );
  
  
  // Determine trace gas production based on microbe.no3prod,
  //   ag.fertn and water-filled pore space

  microbe.setTraceGasProduction( veg.cmnt, 
                                 newpctp, 
                                 ag.fertn );


  // Limit ecosystem N losses to total NO3 available

  if( soil.getLCHNO3PAR() > ZERO )
  {    
    if ( soil.getLEACHNO3() > (avlNO3 + atms.getNO3DEP()
         + microbe.getNO3PROD() + ag.fertn - microbe.getDENITRIF() 
         - veg.getNO3UPTAKE()) )
    {
      if ( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
           + ag.fertn - microbe.getDENITRIF() 
           - veg.getNO3UPTAKE()) > ZERO )
      {    
        soil.setLEACHNO3( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()
                           + ag.fertn
                           - microbe.getDENITRIF()
                           - veg.getNO3UPTAKE()) );
      }
      else
      {
        soil.setLEACHNO3( ZERO );

        if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
            + ag.fertn - veg.getNO3UPTAKE()) > ZERO )
        {
          microbe.setDENITRIF( (avlNO3
                               + atms.getNO3DEP()
                               + microbe.getNO3PROD()
                               + ag.fertn
                               - veg.getNO3UPTAKE()) );
        }
        else
        {
          microbe.setDENITRIF( ZERO );
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( ZERO );

          veg.setNO3UPTAKE( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()
                             + ag.fertn) );
        }
      }
    }
  }
  else     
  {
    // If no leaching losses, limit ecosystem N losses to 
    //   total NO3 available for denitrification
    
    if( microbe.getDENITRIF() > (avlNO3 + atms.getNO3DEP() 
         + ag.fertn + microbe.getNO3PROD() - veg.getNO3UPTAKE()) )
    {

      if( (avlNO3 + atms.getNO3DEP() + ag.fertn 
          + microbe.getNO3PROD() - veg.getNO3UPTAKE()) > ZERO )
      {
        microbe.setDENITRIF( (avlNO3
                             + atms.getNO3DEP()
                             + ag.fertn
                             + microbe.getNO3PROD()
                             - veg.getNO3UPTAKE()) );
      }
      else
      {
        microbe.setDENITRIF( ZERO );
        microbe.setN2PROD( ZERO );
        microbe.setN2OPROD( ZERO );

        veg.setNO3UPTAKE( (avlNO3
                           + atms.getNO3DEP()
                           + ag.fertn
                           + microbe.getNO3PROD()) );
      }

                                 
      if( microbe.getN2OPROD() > ZERO )
      {
        microbe.setN2PROD( microbe.getDENITRIF() - microbe.getN2OPROD() );
      
        if( microbe.getN2PROD() < ZERO )
        {
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( microbe.getDENITRIF() );
        }
      }
      else { microbe.setN2PROD( microbe.getDENITRIF() ); }           
    }    
  }


  // Determine trace gas fluxes based on ammonia volatilization
  //   (microbe.ammnvol), NO production (microbe.noprod),
  //   N2O production (microbe.n2oprod) and N2 production
  //   (microbe.n2prod)

  soil.setTraceGasFluxes( microbe.getAMMNVOL(),
                          microbe.getNOPROD(),
                          microbe.getN2OPROD(),
                          microbe.getN2PROD() );


  if( 0 == avlnflag )
  {
    // Do not allow changes in available nitrogen in soil
    //   (used during calibration process)

    // Equilibrate Ammonium (NH4) pool

    microbe.setAMMNVOL( (atms.getNH4DEP()
                        + microbe.getGROSSNMIN()
                        - microbe.getIMMNH4()
                        - veg.getNH4UPTAKE()
                        - microbe.getNITRIF()) );

    soil.setNH3FLUX( microbe.getAMMNVOL() );
    
    
    // Equilibrate nitrate (NO3) pool

    soil.setLEACHNO3( (atms.getNO3DEP()
                      + microbe.getNO3PROD()
                      - microbe.getDENITRIF()
                      - veg.getNO3UPTAKE()) );

    // Equilibrate DON pool

    soil.setLEACHDON( microbe.getDONPROD() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::delta( const int& pdm,
                    double pstate[],
                    double pdstate[] )
{
//  double tmprootz;

  switch( ag.state )
  {
    case 1:  cropDynamics( pdm, pstate ); break;
    case 2:  pastureDynamics( pdm, pstate ); break;
    case 3:  if( ASPHALT == ag.cmnt )
             { 
               asphaltDynamics( pdm, pstate ); 
             }
             else if( LAWN == ag.cmnt )
             {
               lawnDynamics( pdm, pstate );
             }
             else
             {
               natvegDynamics( pdm, pstate );
             }
             break;
    case 5:  if( ASPHALT == ag.cmnt )
             { 
               asphaltDynamics( pdm, pstate ); 
             }
             else if( LAWN == ag.cmnt )
             {
               lawnDynamics( pdm, pstate );
             }
             else
             {
               natvegDynamics( pdm, pstate );
             }
             break;
    default: if( BAREGRND == veg.cmnt )
             { 
               asphaltDynamics( pdm, pstate ); 
             }
             else if( LAKES == veg.cmnt )
             {
               lakeDynamics( pdm, pstate );
             }

             else 
             {  
               natvegDynamics( pdm, pstate );
             }
  }         


  // Describe monthly changes to carbon pools and fluxes for ODE 
  //   state variables (i.e., pdstate)

  // Carbon pools in ecosystems

  pdstate[I_VEGC] = veg.getGPP() 
                    - veg.getGPR() 
                    - veg.getLTRFALC();

  pdstate[I_SOLC] = veg.getLTRFALC()
                    + ag.getSLASHC()
                    - ag.getSCONVRTFLXC()
                    - microbe.getRH()
                    - microbe.getDOCPROD()
                    - soil.getERODEPOC();

  pdstate[I_DOC] = microbe.getDOCPROD()
                   - soil.getLEACHDOC();


  // Nitrogen pools in ecosystems

  pdstate[I_STRN] = veg.getSUPTAKE()
                    - veg.getLTRFALN()
                    - veg.getNRESORB()
                    + veg.getNMOBIL()
                    + veg.getNFIX();

  pdstate[I_STON] = veg.getLUPTAKE() 
                    + veg.getNRESORB() 
                    - veg.getNMOBIL();

  pdstate[I_SOLN] = veg.getLTRFALN()
                    + ag.getSLASHN()
                    - ag.getSCONVRTFLXN()
                    - ag.getSNTOTRETENT()
                    - microbe.getNETNMIN()
                    - microbe.getDONPROD()
                    - soil.getERODEPON()
                    + microbe.getNFIX();

  pdstate[I_DON] = microbe.getDONPROD()
                   - soil.getLEACHDON();

  if( BAREGRND == veg.cmnt
      || LAKES == veg.cmnt
      || (ASPHALT == ag.cmnt 
      && (3 == ag.state 
      || 5 == ag.state)) )
  { 
    pdstate[I_NH4] = ZERO;

    pdstate[I_NO3] = ZERO;

    pdstate[I_SM] = ZERO;
 
    pdstate[I_RGRW] = ZERO;

    pdstate[I_SGRW] = ZERO;
  }
  else
  {
    pdstate[I_NH4] = atms.getNH4DEP()
	  	     + ag.getNH4RETENT()
                     + ag.getFIRENH4DEP()
                     + microbe.getGROSSNMIN()
                     - microbe.getIMMNH4()
                     - veg.getNH4UPTAKE()
                     - microbe.getAMMNVOL()
                     - microbe.getNITRIF();

    pdstate[I_NO3] = atms.getNO3DEP()
                     + ag.fertn
                     + ag.getNO3RETENT()
                     + ag.getFIRENO3DEP()
                      + microbe.getNO3PROD()
                     - microbe.getDENITRIF()
                     - veg.getNO3UPTAKE()
                     - soil.getLEACHNO3();

    pdstate[I_SM] = soil.getSNOWINF()
                    + atms.getRAIN()
                    + ag.irrigate
                    - soil.getEET()
                    - soil.getRPERC()
                    - soil.getSPERC();
 
    pdstate[I_RGRW] = soil.getRPERC() - soil.getRRUN();

    pdstate[I_SGRW] = soil.getSPERC() - soil.getSRUN();
  }


  // Phenology

  pdstate[I_UNRMLF] = veg.getUNNORMLEAF();

  pdstate[I_LEAF] = veg.getLEAF();

  pdstate[I_LAI] = veg.getLAI();

  pdstate[I_FPC] = veg.getFPC();

  // Carbon fluxes in ecosystems

  pdstate[I_INGPP] = veg.getINGPP();

  pdstate[I_GPP] = veg.getGPP();

  pdstate[I_FOZONE] = veg.getFOZONE();

  pdstate[I_FINDOZONE] = veg.getFINDOZONE();

  pdstate[I_INNPP] = veg.getINNPP();

  pdstate[I_NPP] = veg.getNPP();

  pdstate[I_GPR] = veg.getGPR();

  pdstate[I_RVMNT] = veg.getRMAINT();

  pdstate[I_RVGRW] = veg.getRGRWTH();

  pdstate[I_ABVGPR] = veg.getABVGPR();

  pdstate[I_ROOTGPR] = veg.getROOTRESP();

  pdstate[I_LTRFALC] = veg.getLTRFALC();

  pdstate[I_CDCMP] = microbe.getDECOMP();
  
  pdstate[I_RH] = microbe.getRH();
  
  pdstate[I_DOCP] = microbe.getDOCPROD();

  pdstate[I_LCHDOC] = soil.getLEACHDOC();

  pdstate[I_ERDPOC] = soil.getERODEPOC();


  // Nitrogen fluxes in ecosystems

  pdstate[I_AGFRTN] = ag.fertn;

  pdstate[I_BNFIX] = bnfix;

  pdstate[I_SNFIX] = veg.getNFIX();

  pdstate[I_ANFIX] = microbe.getNFIX();

  pdstate[I_INNUP] = veg.getINUPTAKE();
  pdstate[I_INNH4UP] = veg.getINH4UPTAKE();
  pdstate[I_INNO3UP] = veg.getINO3UPTAKE();

  pdstate[I_VNUP] = veg.getNUPTAKE();
  pdstate[I_VNH4UP] = veg.getNH4UPTAKE();
  pdstate[I_VNO3UP] = veg.getNO3UPTAKE();

  pdstate[I_VSUP] = veg.getSUPTAKE();
  pdstate[I_VLUP] = veg.getLUPTAKE();
  pdstate[I_VNMBL] = veg.getNMOBIL();
  pdstate[I_VNRSRB] = veg.getNRESORB();

  pdstate[I_LTRFALN] = veg.getLTRFALN();

  pdstate[I_NDCMP] = microbe.getNDECOMP();

  pdstate[I_DONP] = microbe.getDONPROD();

  pdstate[I_GMIN] = microbe.getGROSSNMIN();

  pdstate[I_NH4IMM] = microbe.getIMMNH4();

  pdstate[I_NIMM] = microbe.getIMMOB();

  pdstate[I_NMIN] = microbe.getNETNMIN();

  pdstate[I_AIMMNH4] = soil.getABIMMOB();

  pdstate[I_AMMN] = microbe.getAMMNVOL();

  pdstate[I_AIMMNO3] = ZERO;

  pdstate[I_NTRF] = microbe.getNITRIF();
  pdstate[I_NO3P] = microbe.getNO3PROD();
  pdstate[I_NOP] = microbe.getNOPROD();
  pdstate[I_N2OP] = microbe.getN2OPROD();
  pdstate[I_N2P] = microbe.getN2PROD();

  pdstate[I_DNTRF] = microbe.getDENITRIF();


  pdstate[I_NH3FLX] = soil.getNH3FLUX();

  pdstate[I_NOFLX] = soil.getNOFLUX();
  pdstate[I_N2OFLX] = soil.getN2OFLUX();
  pdstate[I_N2FLX] = soil.getN2FLUX();
  pdstate[I_LCHNH4] = soil.getLEACHNH4();
  pdstate[I_LCHNO3] = soil.getLEACHNO3();
  pdstate[I_LCHDON] = soil.getLEACHDON();

  pdstate[I_ERDPON] = soil.getERODEPON();

  // Water fluxes

  pdstate[I_AGIRRIG] = ag.irrigate;
  
  pdstate[I_INEET] = soil.getINEET();
  pdstate[I_EET] = soil.getEET();
  pdstate[I_RPERC] = soil.getRPERC();
  pdstate[I_SPERC] = soil.getSPERC();
  pdstate[I_RRUN] = soil.getRRUN();
  pdstate[I_SRUN] = soil.getSRUN();



};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::displayOptionalCflx( const scykey& s )
{
  switch( s )
  {
    case GET_VEGC:    printw( "   VEGC " ); break;
    case GET_LEAF:    printw( "   LEAF " ); break;
    case GET_LAI:     printw( "    LAI " ); break;
    case GET_FPC:     printw( "    FPC " ); break;
    case GET_SOLC:    printw( "   SOLC " ); break;
    case GET_DOC:     printw( "    DOC " ); break;
    case GET_NSOLC:   printw( "  NSOLC " ); break;
    case GET_TSOLC:   printw( "  TSOLC " ); break;

    case GET_INGPP:    printw( "  INGPP " ); break;
    case GET_GPP:      printw( "   GPP  " ); break;
    case GET_INNPP:    printw( "  INNPP " ); break;
    case GET_NPP:      printw( "   NPP  " ); break;
    case GET_GPR:      printw( "    RA  " ); break;
    case GET_RVMNT:    printw( "  RVMNT " ); break;
    case GET_RVGRW:    printw( "  RVGRW " ); break;
    case GET_LTRFALC:  printw( "LTRFALC " ); break;
    case GET_AGSTUBC:  printw( "AGSTUBC " ); break;
    case GET_CDCMP:    printw( "  CDCMP " ); break;
    case GET_RH:       printw( "    RH  " ); break;
    case GET_RSOIL:    printw( "  RSOIL " ); break;
    case GET_LCHDOC:   printw( " LCHDOC " ); break;
    case GET_NEP:      printw( "   NEP  " ); break;
    case GET_NECB:     printw( "  NECB  " ); break;

    case GET_D40:      printw( " AOT40  " ); break;
    case GET_FOZONE:   printw( " FOZONE " ); break;

    case GET_CNVRTC:   printw( " CNVRTC " ); break;
    case GET_VCNVRTC:  printw( "VCNVRTC " ); break;
    case GET_SCNVRTC:  printw( "SCNVRTC " ); break;
    case GET_SLASHC:   printw( " SLASHC " ); break;
    case GET_CFLX:     printw( "  CFLUX " ); break;
    case GET_NCE:      printw( "   NCE  " ); break;

    case GET_AGPRDC:   printw( " AGPRODC " ); break;
    case GET_PROD10C:  printw( " PROD10C " ); break;
    case GET_PROD100C: printw( "PROD100C " ); break;
    case GET_RESIDC:   printw( "  RESIDC " ); break;

    case GET_AGFPRDC:  printw( " AGFPRDC " ); break;
    case GET_PRDF10C:  printw( " PRDF10C " ); break;
    case GET_PRDF100C: printw( "PRDF100C " ); break;
    case GET_FRESIDC:  printw( " FRESIDC " ); break;
    case GET_AGPRDFC:  printw( " AGPRDFC " ); break;
    case GET_PRD10FC:  printw( " PRD10FC " ); break;
    case GET_PRD100FC: printw( "PRD100FC " ); break;
    case GET_TOTPRDFC: printw( "TOTPRDFC " ); break;
    case GET_RESIDFC:  printw( " RESIDFC " ); break;
  }

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::displayOptionalNflx( const snykey& s )
{
  switch( s )
  {
    case GET_STRN:    printw( "   STRN " ); break;
    case GET_STON:    printw( "   STON " ); break;
    case GET_SOLN:    printw( "   SOLN " ); break;
    case GET_DON:     printw( "    DON " ); break;
    case GET_NSOLN:   printw( "  NSOLN " ); break;
    case GET_TSOLN:   printw( "  TSOLN " ); break;
    case GET_NH4:     printw( "    NH4 " ); break;
    case GET_NO3:     printw( "    NO3 " ); break;

    case GET_NINP:     printw( " NINPUT " ); break;
    case GET_TNDEP:    printw( "TOTNDEP " ); break;
    case GET_NH4DEP:   printw( " NH4DEP " ); break;
    case GET_NO3DEP:   printw( " NO3DEP " ); break;
    case GET_AGFRTN:   printw( "AGFERTN " ); break;
    case GET_BNFIX:    printw( "  BNFIX " ); break;
    case GET_SNFIX:    printw( "  SNFIX " ); break;
    case GET_ANFIX:    printw( "  ANFIX " ); break;
    case GET_INNUP:    printw( "  INNUP " ); break;
    case GET_INNH4UP:  printw( "INNH4UP " ); break;
    case GET_INNO3UP:  printw( "INNO3UP " ); break;
    case GET_VNUP:     printw( " UPTAKE " ); break;
    case GET_VNH4UP:   printw( "  NH4UP " ); break;
    case GET_VNO3UP:   printw( "  NO3UP " ); break;
    case GET_VSUP:     printw( " SUPTAK " ); break;
    case GET_VLUP:     printw( " LUPTAK " ); break;
    case GET_VNMBL:    printw( " NMOBIL " ); break;
    case GET_VNRSRB:   printw( " NRTRAN " ); break;
    case GET_LTRFALN:  printw( "LTRFALN " ); break;
    case GET_AGSTUBN:  printw( "AGSTUBN " ); break;
    case GET_NDCMP:    printw( "  NDCMP " ); break;
    case GET_DONP:     printw( "   DONP" ); break;
    case GET_GMIN:     printw( "GRSNMIN " ); break;
    case GET_NH4IMM:   printw( " NH4IMM " ); break;
    case GET_NO3IMM:   printw( " NO3IMM " ); break;
    case GET_NIMM:     printw( " NIMMOB " ); break;
    case GET_NMIN:     printw( "NETNMIN " ); break;
    case GET_LCHNO3:   printw( " LCHNO3" ); break;
    case GET_LCHDON:   printw( " LCHDON" ); break;
    case GET_NLST:     printw( "  NLOST " ); break;
    case GET_NENB:     printw( "  NENB  " ); break;

    case GET_CNVRTN:   printw( " CNVRTN " ); break;
    case GET_VCNVRTN:  printw( "VCNVRTN " ); break;
    case GET_SCNVRTN:  printw( "SCNVRTN " ); break;
    case GET_SLASHN:   printw( " SLASHN " ); break;
    case GET_NRETNT:   printw( " NRETNT " ); break;
    case GET_NVRTNT:   printw( " NVRTNT " ); break;
    case GET_NSRTNT:   printw( " NSRTNT " ); break;

    case GET_AGPRDN:   printw( " AGPRODN " ); break;
    case GET_PROD10N:  printw( " PROD10N " ); break;
    case GET_PROD100N: printw( "PROD100N " ); break;
    case GET_RESIDN:   printw( "  RESIDN " ); break;

    case GET_AGFPRDN:  printw( " AGFPRDN " ); break;
    case GET_PRDF10N:  printw( " PRDF10N " ); break;
    case GET_PRDF100N: printw( "PRDF100N " ); break;
    case GET_FRESIDN:  printw( " FRESIDN " ); break;
    case GET_AGPRDFN:  printw( " AGPRDFN " ); break;
    case GET_PRD10FN:  printw( " PRD10FN " ); break;
    case GET_PRD100FN: printw( "PRD100FN " ); break;
    case GET_TOTPRDFN: printw( "TOTPRDFN " ); break;
    case GET_RESIDFN:  printw( " RESIDFN " ); break;

    case GET_FIRENDEP: printw( "FIRENDEP " ); break;
    
    case GET_L2SN:     printw( "   LCON  " ); break;
  }

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::displayOptionalSoilTemp( const sstykey& s )
{
  switch( s )
  {
    case GET_TSOIL:  printw( " TSOIL " ); break;
    case GET_DST00:  printw( " DST00 " ); break;
    case GET_DST05:  printw( " DST05 " ); break;
    case GET_DST10:  printw( " DST10 " ); break;
    case GET_DST20:  printw( " DST20 " ); break;
    case GET_DST50:  printw( " DST50 " ); break;
    case GET_DST100: printw( " DST100" ); break;
    case GET_DST200: printw( " DST200" ); break;
    case GET_FRONTD:   printw( " FRONTD" ); break;
    case GET_ACTLAY:   printw( " ACTLAY" ); break;
    case GET_THAWPCT:  printw( "THAWPCT" ); break;
    case GET_THWBEG1:  printw( "THWBEG1" ); break;
    case GET_THWEND1:  printw( "THWEND1" ); break;
    case GET_THWBEG2:  printw( "THWBEG2" ); break;
    case GET_THWEND2:  printw( "THWEND2" ); break;
  }

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::displayOptionalTraceGas( const sgykey& s )
{
  switch( s )
  {
    case GET_GNH4:    printw( "   NH4 " ); break;
    case GET_GNO3:    printw( "   NO3 " ); break;
    case GET_NTRF:    printw( " NITRF " ); break;
    case GET_DNTRF:   printw( " DNITRF" ); break;
    case GET_AIMMNH4: printw( "AIMMNH4" ); break;
    case GET_AMMN:    printw( "AMMNVOL" ); break;
    case GET_AIMMNO3: printw( "AIMMNO3" ); break;
    case GET_NO3P:    printw( " NO3PRD" ); break;
    case GET_NOP:     printw( "  NOPRD" ); break;
    case GET_N2OP:    printw( " N2OPRD" ); break;
    case GET_N2P:     printw( "  N2PRD" ); break;
    case GET_GNLST:   printw( "  NLOST" ); break;
    case GET_NH3FLX:  printw( " NH3FLX" ); break;
    case GET_NOFLX:   printw( "  NOFLX" ); break;
    case GET_N2OFLX:  printw( " N2OFLX" ); break;
    case GET_N2FLX:   printw( "  N2FLX" ); break;
    case GET_GNMIN:   printw( "NETNMIN" ); break;
  }

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::displayOptionalWflx( const swykey& s )
{
  switch( s )
  {
    case GET_SH2O:    printw( " SMOIST" ); break;
    case GET_PCTP:    printw( "  PCTP " ); break;
    case GET_VSM:     printw( "  VSM  " ); break;
    case GET_AVLW:    printw( "  AVLW " ); break;
    case GET_RGRW:    printw( "  RGRW " ); break;
    case GET_SNWPK:   printw( " SNWPK " ); break;
    case GET_SGRW:    printw( "  SGRW " ); break;

    case GET_RAIN:    printw( "  RAIN " ); break;
    case GET_SNWFAL:  printw( " SNWFAL" ); break;
    case GET_SNWINF:  printw( " SNWINF" ); break;
    case GET_AGIRRIG: printw( " IRRIG " ); break;
    case GET_PET:     printw( "  PET  " ); break;
    case GET_INEET:   printw( "  INEET" ); break;
    case GET_EET:     printw( "  EET  " ); break;
    case GET_RPERC:   printw( "  RPERC" ); break;
    case GET_SPERC:   printw( "  SPERC" ); break;
    case GET_RRUN:    printw( "  RRUN " ); break;
    case GET_SRUN:    printw( "  SRUN " ); break;
    case GET_WYLD:    printw( "  WYLD " ); break;
  }

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int TTEM60::ecdqc( const int& dcmnt )
{

  int qc = ACCEPT;

  if( vegca[dcmnt] <= MISSING ) { return qc = 101; }
  if( vegcb[dcmnt] <= MISSING ) { return qc = 102; }

  if( strna[dcmnt] <= MISSING ) { return qc = 103; }
  if( strnb[dcmnt] <= MISSING ) { return qc = 104; }

  if( stona[dcmnt] <= MISSING ) { return qc = 105; }
  if( stonb[dcmnt] <= MISSING ) { return qc = 106; }

  if( solca[dcmnt] <= MISSING ) { return qc = 107; }
  if( solcb[dcmnt] <= MISSING ) { return qc = 108; }

  if( solna[dcmnt] <= MISSING ) { return qc = 109; }
  if( solnb[dcmnt] <= MISSING ) { return qc = 110; }

  if( doccut[dcmnt] <= -0.1 ) { return qc = 111; }
  if( doc1a[dcmnt] <= MISSING ) { return qc = 112; }
  if( doc1b[dcmnt] <= MISSING ) { return qc = 113; }
  if( doc2a[dcmnt] <= MISSING ) { return qc = 114; }
  if( doc2b[dcmnt] <= MISSING ) { return qc = 115; }

  if( doncut[dcmnt] <= -0.1 ) { return qc = 116; }
  if( don1a[dcmnt] <= MISSING ) { return qc = 117; }
  if( don1b[dcmnt] <= MISSING ) { return qc = 118; }
  if( don2a[dcmnt] <= MISSING ) { return qc = 119; }
  if( don2b[dcmnt] <= MISSING ) { return qc = 120; }

  if( nh4a[dcmnt] <= MISSING ) { return qc = 121; }
  if( nh4b[dcmnt] <= MISSING ) { return qc = 122; }

  if( no3cut[dcmnt] <= -0.1 ) { return qc = 123; }
  if( no31a[dcmnt] <= MISSING ) { return qc = 124; }
  if( no31b[dcmnt] <= MISSING ) { return qc = 125; }
  if( no32a[dcmnt] <= MISSING ) { return qc = 126; }
  if( no32b[dcmnt] <= MISSING ) { return qc = 127; }

  if( veg.getUNLEAF12( dcmnt ) <= -0.1 ) { return qc = 128; }
  if( veg.getINITLEAFMX( dcmnt ) <= -0.1 ) { return qc = 129; }

  if( veg.getCMAXCUT( dcmnt ) <= -0.1 ) { return qc = 130; }
  if( veg.getCMAX1A( dcmnt ) <= MISSING ) { return qc = 131; }
  if( veg.getCMAX1B( dcmnt ) <= MISSING ) { return qc = 132; }
  if( veg.getCMAX2A( dcmnt ) <= MISSING ) { return qc = 133; }
  if( veg.getCMAX2B( dcmnt ) <= MISSING ) { return qc = 134; }
  if( veg.getCFALL( dcmnt ) <= -0.1 ) { return qc = 135; }

  if( veg.getRMMAX( dcmnt ) <= -0.1 ) { return qc = 136; }

  if( veg.getRROOT( dcmnt ) <= -0.1 ) { return qc = 138; }

  if( microbe.getKDCUT( dcmnt ) <= -0.1 ) { return qc = 139; }
  if( microbe.getKD1A( dcmnt ) <= -99.99 ) { return qc = 140; }
  if( microbe.getKD1B( dcmnt ) <= -99.99 ) { return qc = 141; }
  if( microbe.getKD2A( dcmnt ) <= -99.99 ) { return qc = 142; }
  if( microbe.getKD2B( dcmnt ) <= -99.99 ) { return qc = 143; }

  if( microbe.getPROPFTOS( dcmnt ) <= -0.1 ) { return qc = 144; }

  if( soil.getPROPREACTA( dcmnt ) <= -99.99 ) 
  { 
    return qc = 145; 
  }

  if( soil.getPROPREACTB( dcmnt ) <= -99.99 ) 
  { 
    return qc = 146; 
  }

  if( soil.getNSOLPAR( dcmnt ) <= -0.1 ) 
  { 
    return qc = 147; 
  }
  
  if( microbe.getDOCPAR( dcmnt ) <= -0.1 ) { return qc = 148; }
  if( soil.getLCHDOMPAR( dcmnt ) <= -0.1 ) { return qc = 149; }

  if( veg.getNFIXADJUST( dcmnt ) <= -0.1 ) { return qc = 150; }
  if( veg.getNFIXPARA( dcmnt ) <= -99.99 ) { return qc = 151; }
  if( veg.getNFIXPARB( dcmnt ) <= -99.99 ) { return qc = 152; }

  if( veg.getNUPNH4CUT( dcmnt ) <= -0.1 ) { return qc = 153; }
  if( veg.getNUPNH41A( dcmnt ) <= MISSING ) { return qc = 154; }
  if( veg.getNUPNH41B( dcmnt ) <= MISSING ) { return qc = 155; }
  if( veg.getNUPNH42A( dcmnt ) <= MISSING ) { return qc = 156; }
  if( veg.getNUPNH42B( dcmnt ) <= MISSING ) { return qc = 157; }

  if( veg.getNUPNO3CUT( dcmnt ) <= -0.1 ) { return qc = 158; }
  if( veg.getNUPNO31A( dcmnt ) <= MISSING ) { return qc = 159; }
  if( veg.getNUPNO31B( dcmnt ) <= MISSING ) { return qc = 160; }
  if( veg.getNUPNO32A( dcmnt ) <= MISSING ) { return qc = 161; }
  if( veg.getNUPNO32B( dcmnt ) <= MISSING ) { return qc = 162; }

  if( veg.getNFALL( dcmnt ) <= -0.1 ) { return qc = 163; }
  if( veg.getLCCLNC( dcmnt ) <= -0.1 ) { return qc = 164; }

  if( microbe.getNFIXPAR( dcmnt ) <= -0.1 ) { return qc = 165; }

  if( microbe.getNH4IMMCUT( dcmnt ) <= -0.1 ) { return qc = 166; }
  if( microbe.getNH4IMM1A( dcmnt ) <= MISSING ) { return qc = 167; }
  if( microbe.getNH4IMM1B( dcmnt ) <= MISSING ) { return qc = 168; }
  if( microbe.getNH4IMM2A( dcmnt ) <= MISSING ) { return qc = 169; }
  if( microbe.getNH4IMM2B( dcmnt ) <= MISSING ) { return qc = 170; }

  if( microbe.getAMMNPAR( dcmnt ) <= -0.1 ) { return qc = 171; }

  if( microbe.getNTRFPARCUT( dcmnt ) <= -0.1 ) { return qc = 172; }
  if( microbe.getNTRFPAR1A( dcmnt ) <= MISSING ) { return qc = 173; }
  if( microbe.getNTRFPAR1B( dcmnt ) <= MISSING ) { return qc = 174; }
  if( microbe.getNTRFPAR2A( dcmnt ) <= MISSING ) { return qc = 175; }
  if( microbe.getNTRFPAR2B( dcmnt ) <= MISSING ) { return qc = 176; }
  
  if( microbe.getINITNTRF( dcmnt ) <= MISSING ) { return qc = 177; }
  if( microbe.getALLNTRF( dcmnt ) <= MISSING ) { return qc = 178; }
  if( microbe.getTGMPAR( dcmnt ) <= -0.1 ) { return qc = 179; }

  if( soil.getLCHNO3PARCUT( dcmnt ) <= -0.1 ) { return qc = 180; }
  if( soil.getLCHNO3PAR1A( dcmnt ) <= MISSING ) { return qc = 181; }
  if( soil.getLCHNO3PAR1B( dcmnt ) <= MISSING ) { return qc = 182; }
  if( soil.getLCHNO3PAR2A( dcmnt ) <= MISSING ) { return qc = 183; }
  if( soil.getLCHNO3PAR2B( dcmnt ) <= MISSING ) { return qc = 184; }

  if( microbe.getDONPARCUT( dcmnt ) <= -0.1 ) { return qc = 185; }
  if( microbe.getDONPAR1A( dcmnt ) <= MISSING ) { return qc = 186; }
  if( microbe.getDONPAR1B( dcmnt ) <= MISSING ) { return qc = 187; }
  if( microbe.getDONPAR2A( dcmnt ) <= MISSING ) { return qc = 188; }
  if( microbe.getDONPAR2B( dcmnt ) <= MISSING ) { return qc = 189; }

  if( veg.getINITCNEVEN( dcmnt ) <= -0.1 ) { return qc = 190; }
  if( veg.getCNMIN( dcmnt ) <= -0.1 ) { return qc = 191; }
  if( veg.getC2NA( dcmnt ) <= MISSING ) { return qc = 192; }
  if( veg.getC2NB( dcmnt ) <= MISSING ) { return qc = 193; }
  if( veg.getC2NMIN( dcmnt ) <= -0.1 ) { return qc = 194; }

  if( microbe.getCNSOIL( dcmnt ) <= -0.1 ) { return qc = 195; }

  if( veg.getO3PARA( dcmnt ) <= -99.99 ) { return qc = 196; }
  if( veg.getO3PARB( dcmnt ) <= -99.99 ) { return qc = 197; }
  if( veg.getO3PARC( dcmnt ) <= -99.99 ) { return qc = 198; }

  if( veg.getKC( dcmnt ) <= -0.1 ) { return qc = 200; }
  if( veg.getKI( dcmnt ) <= -0.1 ) { return qc = 201; }
  if( veg.getGVA( dcmnt ) <= -0.1 ) { return qc = 202; }
  if( veg.getTMIN( dcmnt ) <= -99.99 ) { return qc = 203; }
  if( veg.getTOPTMIN( dcmnt ) <= -99.99 ) { return qc = 204; }
  if( veg.getTOPTMAX( dcmnt ) <= -99.99 ) { return qc = 205; }
  if( veg.getTMAX( dcmnt ) <= -99.99 ) { return qc = 206; }
  if( veg.getTREF( dcmnt ) <= -99.99 ) { return qc = 207; }
  if( veg.getQREF( dcmnt ) <= -99.99 ) { return qc = 208; }
  if( veg.getALPHA( dcmnt ) <= MISSING ) { return qc = 209; }
  if( veg.getBETA( dcmnt ) <= MISSING ) { return qc = 210; }
  if( veg.getGAMMA( dcmnt ) <= MISSING ) { return qc = 211; }
  if( veg.getKVNH4( dcmnt ) <= MISSING ) { return qc = 212; }
  if( veg.getKVNO3( dcmnt ) <= MISSING ) { return qc = 213; }
  if( veg.getLABNCON( dcmnt ) <= -0.1 ) { return qc = 214; }
  if( veg.getLEAFMXC( dcmnt ) <= -0.1 ) { return qc = 215; }
  if( veg.getKLEAFC( dcmnt ) <= MISSING ) { return qc = 216; }
  if( veg.getSLA( dcmnt ) <= -0.1 ) { return qc = 217; }
  if( veg.getCOV( dcmnt ) <= MISSING ) { return qc = 218; }
  if( veg.getFPCMAX( dcmnt ) <= -0.1 ) { return qc = 219; }
  if( veg.getPROPTRANS( dcmnt ) <= -0.1 ) { return qc = 220; }

  if( veg.getMINLEAF( dcmnt ) <= -0.1 ) { return qc = 221; }
  if( veg.getALEAF( dcmnt ) <= MISSING ) { return qc = 222; }
  if( veg.getBLEAF( dcmnt ) <= MISSING ) { return qc = 223; }
  if( veg.getCLEAF( dcmnt ) <= MISSING ) { return qc = 224; }

  if( microbe.getTREF( dcmnt ) <= -99.99 ) { return qc = 225; }
  if( microbe.getQREF( dcmnt ) <= -99.99 ) { return qc = 226; }
  if( microbe.getALPHA( dcmnt ) <= MISSING ) { return qc = 227; }
  if( microbe.getBETA( dcmnt ) <= MISSING ) { return qc = 228; }
  if( microbe.getGAMMA( dcmnt ) <= MISSING ) { return qc = 229; }
  if( microbe.getKN2( dcmnt ) <= -0.1 ) { return qc = 230; }
  if( microbe.getMOISTMIN( dcmnt ) <= -0.1 ) { return qc = 231; }
  if( microbe.getMOISTOPT( dcmnt ) <= -0.1 ) { return qc = 232; }
  if( microbe.getMOISTMAX( dcmnt ) <= -0.1 ) { return qc = 233; }

  if( soil.getROOTZA( dcmnt ) <= MISSING ) { return qc = 234; }
  if( soil.getROOTZB( dcmnt ) <= MISSING ) { return qc = 235; }
  if( soil.getROOTZC( dcmnt ) <= MISSING ) { return qc = 236; }
  if( soil.getMINROOTZ( dcmnt ) <= -0.1 ) { return qc = 237; }

  if( ag.getNVRETCONV( dcmnt ) <= -0.1 ) { return qc = 238; }
  if( ag.getNSRETCONV( dcmnt ) <= -0.1 ) { return qc = 239; }
  if( ag.getTILLFACTOR( dcmnt ) <= -0.1 ) { return qc = 240; }
  if( ag.getHARVSTC( dcmnt ) <= -0.1 ) { return qc = 241; }
  if( ag.getHARVSTN( dcmnt ) <= -0.1 ) { return qc = 242; }
  if( ag.getRESIDUEC( dcmnt ) <= -0.1 ) { return qc = 243; }
  if( ag.getRESIDUEN( dcmnt ) <= -0.1 ) { return qc = 244; }
  if( ag.getCROPSEEDC( dcmnt ) <= -0.1 ) { return qc = 245; }
  if( ag.getCROPSEEDSTRN( dcmnt ) <= -0.1 ) { return qc = 246; }
  if( ag.getCROPSEEDSTON( dcmnt ) <= -0.1 ) { return qc = 247; }

  return qc;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TTEM60::ECDsetODEstate( const int& pdcmnt,
                             const double& psiplusc )
{
  // Initialize the NUMEQ state variables used in the 
  //   ODE integrator from ECD and DAT files 
    
  y[I_VEGC] = vegca[pdcmnt] * psiplusc + vegcb[pdcmnt];
  
  if( y[I_VEGC] < ZERO ) { y[I_VEGC] = ZERO; }


  y[I_SOLC] = solca[pdcmnt] * psiplusc + solcb[pdcmnt];
  
  if( y[I_SOLC] < ZERO ) { y[I_SOLC] = ZERO; }

  if( psiplusc <= doccut[pdcmnt] )
  { 
    y[I_DOC]  = doc1a[pdcmnt] * psiplusc + doc1b[pdcmnt];
  }
  else
  { 
    y[I_DOC]  = doc2a[pdcmnt] * psiplusc + doc2b[pdcmnt];
  }
      
  if( y[I_DOC] < ZERO ) { y[I_DOC] = ZERO; }
        

  y[I_STRN] = strna[pdcmnt] * psiplusc + strnb[pdcmnt];
  
  if( y[I_STRN] < ZERO ) { y[I_STRN] = ZERO; }
    

  y[I_STON] = stona[pdcmnt] * psiplusc + stonb[pdcmnt];

  if( y[I_STON] < ZERO ) { y[I_STON] = ZERO; }
    

  y[I_SOLN] = solna[pdcmnt] * psiplusc + solnb[pdcmnt];
    
  if( y[I_SOLN] < ZERO ) { y[I_SOLN] = ZERO; }
  

  if( psiplusc <= doncut[pdcmnt] )
  { 
    y[I_DON]  = don1a[pdcmnt] * psiplusc + don1b[pdcmnt];
  }
  else
  { 
    y[I_DON]  = don2a[pdcmnt] * psiplusc + don2b[pdcmnt];
  }
      
  if( y[I_DON] < ZERO )
  {
    y[I_DON] = ZERO;
  }
    

  y[I_NH4] = nh4a[pdcmnt] * psiplusc + nh4b[pdcmnt];
  
  if( y[I_NH4] < ZERO ) { y[I_NH4] = ZERO; }
   

  if( psiplusc <= no3cut[pdcmnt] )
  { 
    y[I_NO3] = no31a[pdcmnt] * psiplusc + no31b[pdcmnt];
  }
  else
  { 
    y[I_NO3] = no32a[pdcmnt] * psiplusc + no32b[pdcmnt];
  }
    
  if( y[I_NO3] < ZERO ) { y[I_NO3] = ZERO; }
    
  y[I_SM] = soil.getAWCAPMM() + soil.getWILTPT();

  y[I_RGRW] = ZERO;

  y[I_SGRW] =  ZERO;


  // Initialize all phenology and flux states to zero

  resetODEflux();


  // Reinitialize phenology state variables
  
  y[I_UNRMLF] = veg.getUNLEAF12( pdcmnt );

  y[I_LEAF] = veg.getINITLEAFMX( pdcmnt );  
  
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TTEM60::getCropSpecificECD( const int& dv, 
                                 const string& agecd )
{
  string agversion;
  string agsitename;
  string agdeveloper;
  string agsitecol;
  string agsiterow;
  string agupdated;

  string agdescription;

  int dlayer;

  string kstring;
  char tmpstring[80];


  fecd.open( agecd.c_str(), ios::in );

  if( !fecd )
  {
    cerr << endl << "Cannot open " << agecd;
    cerr << " for ag siteECD input" << endl;
    
    exit( -1 );
  }

  // Get site-specific parameters

  ag.cmnt = getXMLCommunityNode( fecd,
                                 kstring,
                                 agsitename,
                                 kstring,
                                 kstring,
                                 agdeveloper,
                                 agversion,
                                 kstring );

  getXMLNode( fecd, "siteECD" );
 
  vegca[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegca",
                                          ag.cmnt );

  vegcb[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegcb",
                                          ag.cmnt );

  strna[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "strna",
                                          ag.cmnt );

  strnb[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "strnb",
                                          ag.cmnt );

  stona[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "stona",
                                          ag.cmnt );

  stonb[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "stonb",
                                          ag.cmnt );

  solca[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "solca",
                                          ag.cmnt );

  solcb[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "solcb",
                                          ag.cmnt );

  solna[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "solna",
                                          ag.cmnt );

  solnb[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "solnb",
                                          ag.cmnt );

  doccut[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "doccut",
                                           ag.cmnt );

  doc1a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "doc1a",
                                          ag.cmnt );

  doc1b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "doc1b",
                                          ag.cmnt );

  doc2a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "doc2a",
                                          ag.cmnt );

  doc2b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "doc2b",
                                          ag.cmnt );

  doncut[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "doncut",
                                           ag.cmnt );

  don1a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "don1a",
                                          ag.cmnt );

  don1b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "don1b",
                                          ag.cmnt );

  don2a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "don2a",
                                          ag.cmnt );

  don2b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "don2b",
                                          ag.cmnt );

  nh4a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                         "siteECD",
                                         "nh4a",
                                         ag.cmnt );

  nh4b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                         "siteECD",
                                         "nh4b",
                                         ag.cmnt );


  no3cut[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "no3cut",
                                           ag.cmnt );

  no31a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "no31a",
                                          ag.cmnt );

  no31b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "no31b",
                                          ag.cmnt );

  no32a[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "no32a",
                                          ag.cmnt );

  no32b[ag.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "no32b",
                                          ag.cmnt );

  veg.setUNLEAF12( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "unleaf12",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setINITLEAFMX( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "initleafmx",
                                             ag.cmnt ),
                     ag.cmnt );


  veg.setCMAXCUT( getXMLcmntArrayDouble( fecd,
                                         "siteECD",
                                         "vegcmaxcut",
                                         ag.cmnt ),
                  ag.cmnt );

  veg.setCMAX1A( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax1a",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setCMAX1B( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax1b",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setCMAX2A( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax2a",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setCMAX2B( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax2b",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setCFALL( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegcfall",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setRMMAX( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegrmmax",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setRROOT( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegrroot",
                                       ag.cmnt ),
                ag.cmnt );


  microbe.setKDCUT( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "microbekdcut",
                                           ag.cmnt ),
                    ag.cmnt );

  microbe.setKD1A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd1a",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setKD1B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd1b",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setKD2A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd2a",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setKD2B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd2b",
                                          ag.cmnt ),
                   ag.cmnt );


  microbe.setPROPFTOS( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbepropftos",
                                              ag.cmnt ),
                       ag.cmnt );

  soil.setPROPREACTA( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "soilpropReactA",
                                             ag.cmnt ),
                      ag.cmnt );

  soil.setPROPREACTB( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "soilpropReactB",
                                             ag.cmnt ),
                      ag.cmnt );

  soil.setNSOLPAR( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "soilnonOMpar",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setDOCPAR( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "microbeDOCpar",
                                            ag.cmnt ),
                     ag.cmnt );

  soil.setLCHDOMPAR( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "soillchDOMpar",
                                            ag.cmnt ),
                     ag.cmnt );

  veg.setNFIXPARA( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnfixpara",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNFIXPARB( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnfixparb",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNH4CUT( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "vegnupnh4cut",
                                           ag.cmnt ),
                    ag.cmnt );

  veg.setNUPNH41A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh41a",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNH41B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh41b",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNH42A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh42a",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNH42B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh42b",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNO3CUT( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "vegnupno3cut",
                                           ag.cmnt ),
                    ag.cmnt );

  veg.setNUPNO31A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno31a",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNO31B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno31b",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNO32A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno32a",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNUPNO32B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno32b",
                                          ag.cmnt ),
                   ag.cmnt );

  veg.setNFALL( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegnfall",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setLCCLNC( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "veglcclnc",
                                        ag.cmnt ),
                 ag.cmnt );

  microbe.setNFIXPAR( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "microbenfixpar",
                                             ag.cmnt ),
                      ag.cmnt );

  microbe.setNH4IMMCUT( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbenh4immcut",
                                               ag.cmnt ),
                        ag.cmnt );

  microbe.setNH4IMM1A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm1a",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setNH4IMM1B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm1b",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setNH4IMM2A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm2a",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setNH4IMM2B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm2b",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setAMMNPAR( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "microbeammnpar",
                                             ag.cmnt ),
                      ag.cmnt );

  microbe.setNTRFPARCUT( getXMLcmntArrayDouble( fecd,
                                                "siteECD",
                                                "microbentrfparcut",
                                                ag.cmnt ),
                         ag.cmnt );

  microbe.setNTRFPAR1A( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar1a",
                                               ag.cmnt ),
                        ag.cmnt );

  microbe.setNTRFPAR1B( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar1b",
                                               ag.cmnt ),
                        ag.cmnt );

  microbe.setNTRFPAR2A( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar2a",
                                               ag.cmnt ),
                        ag.cmnt );

  microbe.setNTRFPAR2B( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar2b",
                                               ag.cmnt ),
                        ag.cmnt );

  microbe.setINITNTRF( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeinitntrf",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setALLNTRF( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "microbeallntrf",
                                             ag.cmnt ),
                      ag.cmnt );

  microbe.setTGMPAR( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "microbetgmpar",
                                            ag.cmnt ),
                     ag.cmnt );

  soil.setLCHNO3PARCUT( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "soillchNO3parcut",
                                               ag.cmnt ),
                        ag.cmnt );

  soil.setLCHNO3PAR1A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par1a",
                                              ag.cmnt ),
                       ag.cmnt );

  soil.setLCHNO3PAR1B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par1b",
                                              ag.cmnt ),
                       ag.cmnt );

  soil.setLCHNO3PAR2A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par2a",
                                              ag.cmnt ), 
                       ag.cmnt );

  soil.setLCHNO3PAR2B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par2b",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setDONPARCUT( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbeDONparcut",
                                               ag.cmnt ),
                        ag.cmnt );

  microbe.setDONPAR1A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar1a",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setDONPAR1B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar1b",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setDONPAR2A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar2a",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setDONPAR2B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar2b",
                                              ag.cmnt ),
                       ag.cmnt );
                                                       
  veg.setINITCNEVEN( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "veginitcneven",
                                            ag.cmnt ),
                     ag.cmnt );

  veg.setCNMIN( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegcnmin",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setC2NA( getXMLcmntArrayDouble( fecd,
                                      "siteECD",
                                      "vegc2na",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setC2NB( getXMLcmntArrayDouble( fecd,
                                      "siteECD",
                                      "vegc2nb",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setC2NMIN( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegc2nmin",
                                        ag.cmnt ),
                 ag.cmnt );

  microbe.setCNSOIL( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "microbecnsoil",
                                            ag.cmnt ),
                     ag.cmnt );

  veg.setO3PARA( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "o3para",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setO3PARB( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "o3parb",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setO3PARC( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "o3parc",
                                        ag.cmnt ),
                 ag.cmnt );

  endXMLNode( fecd, "siteECD" );


  // Get vegetation-specific parameters for vegetation dynamics

  getXMLNode( fecd, "vegECD" );

  veg.setKC( getXMLcmntArrayDouble( fecd,
                                    "vegECD",
                                    "kc",
                                    ag.cmnt ),
             ag.cmnt );

  veg.setKI( getXMLcmntArrayDouble( fecd,
                                    "vegECD",
                                    "ki",
                                    ag.cmnt ),
             ag.cmnt );

  veg.setGVA( getXMLcmntArrayDouble( fecd,
                                     "vegECD",
                                     "gva",
                                     ag.cmnt ),
              ag.cmnt );

  veg.setTMIN( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "tmin",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setTOPTMIN( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "toptmin",
                                         ag.cmnt ),
                  ag.cmnt );

  veg.setTOPTMAX( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "toptmax",
                                         ag.cmnt ),
                  ag.cmnt );

  veg.setTMAX( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "tmax",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setTREF( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "tref",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setQREF( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "qref",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setALPHA( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "alpha",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setBETA( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "beta",
                                      ag.cmnt ),
               ag.cmnt );

  veg.setGAMMA( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "gamma",
                                       ag.cmnt ),
                ag.cmnt );


  veg.setKVNH4( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "kvnh4",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setKVNO3( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "kvno3",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setLABNCON( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "labncon",
                                         ag.cmnt ),
                  ag.cmnt );

  veg.setLEAFMXC( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "leafmxc",
                                         ag.cmnt ),
                  ag.cmnt );

  veg.setKLEAFC( getXMLcmntArrayDouble( fecd,
                                        "vegECD",
                                        "kleafc",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setSLA( getXMLcmntArrayDouble( fecd,
                                     "vegECD",
                                     "sla",
                                     ag.cmnt ),
              ag.cmnt );

  veg.setCOV( getXMLcmntArrayDouble( fecd,
                                     "vegECD",
                                     "cov",
                                     ag.cmnt ),
              ag.cmnt );

  veg.setFPCMAX( getXMLcmntArrayDouble( fecd,
                                        "vegECD",
                                        "fpcmax",
                                        ag.cmnt ),
                 ag.cmnt );

  veg.setPROPTRANS( getXMLcmntArrayDouble( fecd,
                                           "vegECD",
                                           "proptrans",
                                           ag.cmnt ),
                    ag.cmnt );

  endXMLNode( fecd, "vegECD" );


  // Get vegetation-specific parameters for phenology

  getXMLNode( fecd, "leafECD" );


  veg.setMINLEAF( getXMLcmntArrayDouble( fecd,
                                         "leafECD",
                                         "minleaf",
                                         ag.cmnt ),
                  ag.cmnt );

  veg.setALEAF( getXMLcmntArrayDouble( fecd,
                                       "leafECD",
                                       "aleaf",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setBLEAF( getXMLcmntArrayDouble( fecd,
                                       "leafECD",
                                       "bleaf",
                                       ag.cmnt ),
                ag.cmnt );

  veg.setCLEAF( getXMLcmntArrayDouble( fecd,
                                       "leafECD",
                                       "cleaf",
                                       ag.cmnt ),
                ag.cmnt );

  endXMLNode( fecd, "leafECD" );


  // Get vegetation-specific parameters for microbe dynamics

  getXMLNode( fecd, "microbeECD" );

  microbe.setTREF( getXMLcmntArrayDouble( fecd,
                                          "microbeECD",
                                          "tref",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setQREF( getXMLcmntArrayDouble( fecd,
                                          "microbeECD",
                                          "qref",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setALPHA( getXMLcmntArrayDouble( fecd,
                                           "microbeECD",
                                           "alpha",
                                           ag.cmnt ),
                    ag.cmnt );

  microbe.setBETA( getXMLcmntArrayDouble( fecd,
                                          "microbeECD",
                                          "beta",
                                          ag.cmnt ),
                   ag.cmnt );

  microbe.setGAMMA( getXMLcmntArrayDouble( fecd,
                                           "microbeECD",
                                           "gamma",
                                           ag.cmnt ),
                    ag.cmnt );


  microbe.setKN2( getXMLcmntArrayDouble( fecd,
                                         "microbeECD",
                                         "kn2", 
                                         ag.cmnt),
                  ag.cmnt );

  microbe.setMOISTMIN( getXMLcmntArrayDouble( fecd,
                                              "microbeECD",
                                              "moistmin",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setMOISTOPT( getXMLcmntArrayDouble( fecd,
                                              "microbeECD",
                                              "moistopt",
                                              ag.cmnt ),
                       ag.cmnt );

  microbe.setMOISTMAX( getXMLcmntArrayDouble( fecd,
                                              "microbeECD",
                                              "moistmax",
                                              ag.cmnt ),
                       ag.cmnt );

    endXMLNode( fecd, "microbeECD" );


  // Get vegetation-specific parameters for rooting depth

  getXMLNode( fecd, "rootzECD" );
 
  soil.setROOTZA( getXMLcmntArrayDouble( fecd,
                                         "rootzECD",
                                         "rootza",
                                         ag.cmnt ),
                  ag.cmnt );

  soil.setROOTZB( getXMLcmntArrayDouble( fecd,
                                         "rootzECD",
                                         "rootzb",
                                         ag.cmnt ),
                  ag.cmnt );

  soil.setROOTZC( getXMLcmntArrayDouble( fecd,
                                         "rootzECD",
                                         "rootzc",
                                         ag.cmnt ),
                  ag.cmnt );

  soil.setMINROOTZ( getXMLcmntArrayDouble( fecd,
                                           "rootzECD",
                                           "minrootz",
                                           ag.cmnt ),
                    ag.cmnt );

    endXMLNode( fecd, "rootzECD" );


  // Get vegetation-specific parameters for the snowpack

  getXMLNode( fecd, "snowPackECD" );

  soil.stm.setVEGWINDSP( getXMLcmntArrayInt( fecd, 
                                             "snowPackECD", 
                                             "vegWindSp", 
                                             ag.cmnt ),
                         ag.cmnt ); 
    
  soil.stm.setGFLUX( getXMLcmntArrayDouble( fecd, 
                                            "snowPackECD", 
                                            "gflux",  
                                            ag.cmnt ),
                     ag.cmnt );

  soil.stm.setCDSNOW( getXMLcmntArrayDouble( fecd, 
                                             "snowPackECD", 
                                             "cdsnow",  
                                             ag.cmnt ),
                      ag.cmnt );

  soil.stm.setINITDTDAY( getXMLcmntArrayDouble( fecd, 
                                                "snowPackECD", 
                                                "DTDAY",  
                                                ag.cmnt ),
                         ag.cmnt );

  endXMLNode( fecd, "snowPackECD" );


  // Get vegetation-specific parameters for the soil layers

  getXMLNode( fecd, "soilLayerECD" );

  for( dlayer = 0; dlayer < MAXSLAYERS; ++dlayer )
  {
    sprintf( tmpstring, "%s%d", "THICK", (dlayer+1) );	
    soil.stm.setINITTHICK( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  ag.cmnt ),
                           ag.cmnt,
                           dlayer ); 

    sprintf( tmpstring, "%s%d", "DXA", (dlayer+1) );	
    soil.stm.setINITDXA( getXMLcmntArrayDouble( fecd, 
                                                "soilLayerECD", 
                                                tmpstring,  
                                                ag.cmnt ),
                         ag.cmnt,
                         dlayer );

    sprintf( tmpstring, "%s%d", "DXB", (dlayer+1) );	
    soil.stm.setINITDXB( getXMLcmntArrayDouble( fecd, 
                                                "soilLayerECD", 
                                                tmpstring,  
                                                ag.cmnt ),
                         ag.cmnt,
                         dlayer );

    sprintf( tmpstring, "%s%d", "MAT", (dlayer+1) );	
    soil.stm.setVEGMAT( getXMLcmntArrayLong( fecd, 
                                             "soilLayerECD", 
                                             tmpstring,  
                                             ag.cmnt ),
                        ag.cmnt,
                        dlayer ); 

    sprintf( tmpstring, "%s%d", "DENSE", (dlayer+1) );	
    soil.stm.setINITDENSE( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  ag.cmnt ),
                           ag.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "WATER", (dlayer+1) );	
    soil.stm.setINITWATER( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  ag.cmnt ),
                           ag.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "vcond", (dlayer+1) );	
    soil.stm.setVCOND( getXMLcmntArrayDouble( fecd, 
                                              "soilLayerECD", 
                                              tmpstring,  
                                              ag.cmnt ),
                       ag.cmnt,
                       dlayer );

    sprintf( tmpstring, "%s%d", "vsph", (dlayer+1) );	
    soil.stm.setVSPH( getXMLcmntArrayDouble( fecd, 
                                             "soilLayerECD", 
                                             tmpstring,  
                                             ag.cmnt ),
                      ag.cmnt,
                      dlayer ); 

    sprintf( tmpstring, "%s%d", "cond", (dlayer+1) );	
    soil.stm.setINITCONDT( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  ag.cmnt ),
                           ag.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "spht", (dlayer+1) );	
    soil.stm.setINITSPHT( getXMLcmntArrayDouble( fecd, 
                                                 "soilLayerECD", 
                                                 tmpstring,  
                                                 ag.cmnt ),
                          ag.cmnt,
                          dlayer );

    sprintf( tmpstring, "%s%d", "condf", (dlayer+1) );	
    soil.stm.setINITCONDF( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  ag.cmnt ),
                           ag.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "sphf", (dlayer+1) );	
    soil.stm.setINITSPHF( getXMLcmntArrayDouble( fecd, 
                                                 "soilLayerECD", 
                                                 tmpstring,  
                                                 ag.cmnt ),
                          ag.cmnt,
                          dlayer );
  }
 
  endXMLNode( fecd, "soilLayerECD" );


  // Get vegetation-specific parameters for disturbance

  getXMLNode( fecd, "agECD" );

  ag.setNVRETCONV( getXMLcmntArrayDouble( fecd,
                                          "agECD",
                                          "nvretconv",
                                          ag.cmnt ),
                   ag.cmnt );

  ag.setNSRETCONV( getXMLcmntArrayDouble( fecd,
                                          "agECD",
                                          "nsretconv",
                                          ag.cmnt ),
                   ag.cmnt );

  ag.setTILLFACTOR( getXMLcmntArrayDouble( fecd,
                                           "agECD",
                                           "tillfactor",
                                           ag.cmnt ),
                    ag.cmnt );

  ag.setHARVSTC( getXMLcmntArrayDouble( fecd,
                                        "agECD",
                                        "harvstC",
                                        ag.cmnt ),
                 ag.cmnt );

  ag.setHARVSTN( getXMLcmntArrayDouble( fecd,
                                        "agECD",
                                        "harvstN",
                                        ag.cmnt ),
                 ag.cmnt );

  ag.setRESIDUEC( getXMLcmntArrayDouble( fecd,
                                         "agECD",
                                         "residueC",
                                         ag.cmnt ),
                  ag.cmnt );

  ag.setRESIDUEN( getXMLcmntArrayDouble( fecd,
                                         "agECD",
                                         "residueN",
                                         ag.cmnt ),
                  ag.cmnt );

  ag.setCROPSEEDC( getXMLcmntArrayDouble( fecd,
                                          "agECD",
                                          "cropseedC",
                                          ag.cmnt ),
                   ag.cmnt );

  ag.setCROPSEEDSTRN( getXMLcmntArrayDouble( fecd,
                                             "agECD",
                                             "cropseedSTRN",
                                             ag.cmnt ),
                      ag.cmnt );

  ag.setCROPSEEDSTON( getXMLcmntArrayDouble( fecd,
                                             "agECD",
                                             "cropseedSTON",
                                             ag.cmnt ),
                      ag.cmnt );

  endXMLNode( fecd, "agECD" );

  fecd.close();

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TTEM60::getenviron( const int& pdyr,
                         const int& pdm,
                         ofstream& rflog1 )
{
  double nextsnowinf;
  double lastyrdst10;
  double diffdst10;

  // Determine monthly potential evapotranspiration

  atms.petjh( atms.getNIRR(), atms.getTAIR(), pdm );



  // Determine contribution of snowmelt to soil moisture

  soil.setSNOWINF( soil.snowmelt( elev, 
                                  atms.getTAIR(), 
                                  atms.getPREVTAIR(), 
                                  soil.getPREVSPACK() ) );

  // Determine new snow pack
  
  soil.setSNOWPACK( (soil.getPREVSPACK() 
                     + atms.getSNOWFALL() 
                     - soil.getSNOWINF()) );


  if( soil.getSNOWPACK() < ZERO )
  {
    soil.setSNOWPACK( ZERO );
  }

  soil.setACTLAYER( soil.getROOTZ() );


  if( 1 == soil.stmflg
      && ag.cmnt != BAREGRND
      && ag.cmnt != ASPHALT
      && ag.cmnt != LAKES )
  {
    if ( 0 == pdyr && 0 == pdm ) 
    { 
      soil.stm.setKSWITCH( 0 ); 
    
      soil.stm.initSoilThermalRegime( atms.getAVETAIR() );
    }
    else { soil.stm.setKSWITCH( 1 ); }

    

    nextsnowinf = soil.snowmelt( elev,
                                 soil.stm.getNEXTTAIR(),
                                 atms.getTAIR(),
                                 soil.getSNOWPACK() );

    soil.stm.setNEXTSPACK( (soil.getSNOWPACK() 
                            + soil.stm.getNEXTSNOWFALL()
                            - nextsnowinf) );

    soil.stm.setSnowDensity( veg.cmnt, atms.getPREC(), pdm );

    // Obtain dst10 and tsoil value from last year
    
    lastyrdst10 = soil.getDST10();



    soil.stm.setMonthlySoilConditions( atms.getPREVTAIR(),
                                       atms.getTAIR(),
                                       soil.stm.getNEXTTAIR(),
                                       soil.getPREVSPACK(),
                                       soil.getSNOWPACK(),
                                       soil.stm.getNEXTSPACK(),
                                       veg.cmnt,
                                       pdm,
                                       rflog1 );


    // Determine year-to-year different in dst10 for 
    //   particular month
    
    diffdst10 = soil.getDST10() - lastyrdst10;
    
    // Impose active layer restrictions on rooting depth for 
    //   those areas underlain by permafrost 

    if( soil.stm.getTHAWEND1() > soil.getROOTZ() )
    {
      if( (soil.getROOTZ() - soil.stm.getTHAWBEGIN1()) < MINACTLAYERZ )
      {
        soil.setACTLAYER( MINACTLAYERZ ); 
      }
      else
      {
        soil.setACTLAYER( (soil.getROOTZ() - soil.stm.getTHAWBEGIN1()) );
      }
    }
    else
    {
      if( (soil.stm.getTHAWEND1() - soil.stm.getTHAWBEGIN1()) < MINACTLAYERZ )
      {
        soil.setACTLAYER( MINACTLAYERZ ); 
      }
      else
      {
      	if( soil.stm.getTHAWEND2() > soil.getROOTZ()
      	    && soil.stm.getTHAWBEGIN2() > soil.getROOTZ() )
        {
          soil.setACTLAYER( (soil.stm.getTHAWEND1() - soil.stm.getTHAWBEGIN1()) );
        }
      	
      	else if( soil.stm.getTHAWEND2() > soil.getROOTZ()
      	    && soil.stm.getTHAWBEGIN2() < soil.getROOTZ() )
        {
          soil.setACTLAYER( ((soil.stm.getTHAWEND1() - soil.stm.getTHAWBEGIN1()) 
                            + (soil.getROOTZ() - soil.stm.getTHAWBEGIN2())) );
        } 
      	
      	else
        {
          soil.setACTLAYER( ((soil.stm.getTHAWEND1() - soil.stm.getTHAWBEGIN1()) 
                            + (soil.stm.getTHAWEND2() - soil.stm.getTHAWBEGIN2())) );
        }
        
      }
    }

    // Update soil characteristics based on dynamic 
    //   active layer depth
              
    soil.updateActiveLayerRootZ();


    soil.setTSOIL( soil.stm.getTSOIL() );

    if( soil.stm.getDST10() > (atms.getTAIR() + 100.0) )
    {
      soil.setDST10( atms.getTAIR() );
    }
    else
    {  
      soil.setDST10( soil.stm.getDST10() );
    }
        
    // Determine the amount of soil (0 - 10 cm depth) that is 
    //   thawed

    veg.setThawPercent( soil.getPREVDST10(),
                        soil.getDST10(),
                        (soil.getNEXTDST10() + diffdst10) );
  }
  else 
  { 
    soil.stm.setDST0( atms.getTAIR() );
    soil.stm.setDST5( atms.getTAIR() );
    soil.setDST10( atms.getTAIR() );
    soil.stm.setDST20( atms.getTAIR() );
    soil.stm.setDST50( atms.getTAIR() );
    soil.stm.setDST100( atms.getTAIR() );
    soil.stm.setDST200( atms.getTAIR() );
    soil.setTSOIL( atms.getTAIR() );

    veg.setThawPercent( 1.0000000 ); 
  }
  
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

double TTEM60::getOptionalCflx( const int& optflx )
{

  double outflux;

  switch( optflx )
  {
    case GET_VEGC:    outflux = y[I_VEGC]; break;
    case GET_LEAF:    outflux = y[I_LEAF]; break;
    case GET_LAI:     outflux = veg.getLAI(); break;
    case GET_FPC:     outflux = y[I_FPC]; break;
    case GET_SOLC:    outflux = y[I_SOLC]; break;
    case GET_DOC:     outflux = y[I_DOC]; break;
    case GET_NSOLC:   outflux = soil.getNSOLC(); break;
    case GET_TSOLC:   outflux = soil.getTSOLC(); break;

    case GET_INGPP:    outflux = y[I_INGPP]; break;
    case GET_GPP:      outflux = y[I_GPP]; break;
    case GET_INNPP:    outflux = y[I_INNPP]; break;
    case GET_NPP:      outflux = y[I_NPP]; break;
    case GET_GPR:      outflux = y[I_GPR]; break;
    case GET_RVMNT:    outflux = y[I_RVMNT]; break;
    case GET_RVGRW:    outflux = y[I_RVGRW]; break;
    case GET_LTRFALC:  outflux = y[I_LTRFALC]; break;
    case GET_CDCMP:    outflux = y[I_CDCMP]; break;
    case GET_RH:       outflux = y[I_RH]; break;
    case GET_RSOIL:    outflux = rsoil; break;
    case GET_LCHDOC:   outflux = y[I_LCHDOC]; break;
    case GET_NEP:      outflux = nep; break;
    case GET_NECB:     outflux = necb; break;

    case GET_D40:      outflux = atms.getAOT40(); break;
    case GET_FOZONE:   outflux = y[I_FOZONE]; break;

    case GET_CNVRTC:   outflux = ag.getCONVRTFLXC();  break;
    case GET_VCNVRTC:  outflux = ag.getVCONVRTFLXC();  break;
    case GET_SCNVRTC:  outflux = ag.getSCONVRTFLXC();  break;
    case GET_SLASHC:   outflux = ag.getSLASHC();  break;
    case GET_CFLX:     outflux = ag.getCFLUX();  break;
    case GET_NCE:      outflux = nce;  break;

    case GET_AGSTUBC:  outflux = ag.getSTUBBLEC(); break;
    case GET_RESIDC:   outflux = ag.getCROPRESIDUEC();  break;

    case GET_AGPRDC:   outflux = ag.getPROD1C();  break;
    case GET_PROD10C:  outflux = ag.getPROD10C();  break;
    case GET_PROD100C: outflux = ag.getPROD100C();  break;

    case GET_FRESIDC:  outflux = ag.getFORMCROPRESIDUEC();  break;

    case GET_AGFPRDC:  outflux = ag.getCROPPRODC();  break;
    case GET_PRDF10C:  outflux = ag.getFORMPROD10C();  break;
    case GET_PRDF100C: outflux = ag.getFORMPROD100C();  break;
    case GET_AGPRDFC:  outflux = ag.getPROD1DECAYC();  break;
    case GET_PRD10FC:  outflux = ag.getPROD10DECAYC();  break;
    case GET_PRD100FC: outflux = ag.getPROD100DECAYC();  break;
    case GET_TOTPRDFC: outflux = ag.getTOTPRODDECAYC();  break;
    case GET_RESIDFC:  outflux = ag.getCROPRESIDUEFLXC();  break;

    default:           outflux = MISSING;
  }

  return outflux;

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

double TTEM60::getOptionalNflx( const int& optflx )
{

  double outflux;

  switch( optflx )
  {
    case GET_STRN:    outflux = y[I_STRN]; break;
    case GET_STON:    outflux = y[I_STON]; break;
    case GET_SOLN:    outflux = y[I_SOLN]; break;
    case GET_DON:     outflux = y[I_DON]; break;
    case GET_NSOLN:   outflux = soil.getNSOLN(); break;
    case GET_TSOLN:   outflux = soil.getTSOLN(); break;
    case GET_NH4:     outflux = y[I_NH4]; break;
    case GET_NO3:     outflux = y[I_NO3]; break;

    case GET_NINP:     outflux = soil.getNINPUT(); break;
    case GET_TNDEP:    outflux = atms.getTOTNDEP(); break;
    case GET_NH4DEP:   outflux = atms.getNH4DEP(); break;
    case GET_NO3DEP:   outflux = atms.getNO3DEP(); break;
    case GET_AGFRTN:   outflux = y[I_AGFRTN]; break;
    case GET_BNFIX:    outflux = y[I_BNFIX]; break;
    case GET_SNFIX:    outflux = y[I_SNFIX]; break;
    case GET_ANFIX:    outflux = y[I_ANFIX]; break;
    case GET_INNUP:    outflux = y[I_INNUP]; break;
    case GET_INNH4UP:  outflux = y[I_INNH4UP]; break;
    case GET_INNO3UP:  outflux = y[I_INNO3UP]; break;
    case GET_VNUP:     outflux = y[I_VNUP]; break;
    case GET_VNH4UP:   outflux = y[I_VNH4UP]; break;
    case GET_VNO3UP:   outflux = y[I_VNO3UP]; break;
    case GET_VSUP:     outflux = y[I_VSUP]; break;
    case GET_VLUP:     outflux = y[I_VLUP]; break;
    case GET_VNMBL:    outflux = y[I_VNMBL]; break;
    case GET_VNRSRB:   outflux = y[I_VNRSRB]; break;
    case GET_LTRFALN:  outflux = y[I_LTRFALN]; break;
    case GET_AGSTUBN:  outflux = ag.getSTUBBLEN(); break;
    case GET_NDCMP:    outflux = y[I_NDCMP]; break;
    case GET_DONP:     outflux = y[I_DONP]; break;
    case GET_GMIN:     outflux = y[I_GMIN]; break;
    case GET_NH4IMM:   outflux = y[I_NH4IMM]; break;
    case GET_NIMM:     outflux = y[I_NIMM]; break;
    case GET_NMIN:     outflux = y[I_NMIN]; break;
    case GET_LCHNO3:   outflux = y[I_LCHNO3]; break;
    case GET_LCHDON:   outflux = y[I_LCHDON]; break;
    case GET_NLST:     outflux = soil.getNLOST(); break;
    case GET_NENB:     outflux = nenb; break;

    case GET_CNVRTN:   outflux = ag.getCONVRTFLXN();  break;
    case GET_VCNVRTN:  outflux = ag.getVCONVRTFLXN();  break;
    case GET_SCNVRTN:  outflux = ag.getSCONVRTFLXN();  break;
    case GET_SLASHN:   outflux = ag.getSLASHN();  break;
    case GET_NRETNT:   outflux = ag.getNRETENT();  break;
    case GET_NVRTNT:   outflux = ag.getNVRETENT();  break;
    case GET_NSRTNT:   outflux = ag.getNSRETENT();  break;

    case GET_AGPRDN:   outflux = ag.getPROD1N();  break;
    case GET_PROD10N:  outflux = ag.getPROD10N();  break;
    case GET_PROD100N: outflux = ag.getPROD100N();  break;
    case GET_RESIDN:   outflux = ag.getCROPRESIDUEN();  break;

    case GET_AGFPRDN:  outflux = ag.getCROPPRODN();  break;
    case GET_PRDF10N:  outflux = ag.getFORMPROD10N();  break;
    case GET_PRDF100N: outflux = ag.getFORMPROD100N();  break;
    case GET_FRESIDN:  outflux = ag.getFORMCROPRESIDUEN();  break;
    case GET_AGPRDFN:  outflux = ag.getPROD1DECAYN();  break;
    case GET_PRD10FN:  outflux = ag.getPROD10DECAYN();  break;
    case GET_PRD100FN: outflux = ag.getPROD100DECAYN();  break;
    case GET_TOTPRDFN: outflux = ag.getTOTPRODDECAYN();  break;
    case GET_RESIDFN:  outflux = ag.getCROPRESIDUEFLXN();  break;

    case GET_FIRENDEP: outflux = ag.getFIRENDEP();  break;
    
    case GET_L2SN:     if ( y[I_VEGC] != ZERO )
                       {
                         outflux = y[I_STON]/y[I_STRN];
                       }
                       else { outflux = MISSING; } break;
    default:           outflux = MISSING;
  }

  return outflux;

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

double TTEM60::getOptionalSoilTemp( const int& optflx )
{

  double stair;

  switch( optflx )
  {
    case GET_TSOIL:  stair = soil.stm.getTSOIL(); break;
    case GET_DST00:  stair = soil.stm.getDST0(); break;
    case GET_DST05:  stair = soil.stm.getDST5(); break;
    case GET_DST10:  stair = soil.stm.getDST10(); break;
    case GET_DST20:  stair = soil.stm.getDST20(); break;
    case GET_DST50:  stair = soil.stm.getDST50(); break;
    case GET_DST100: stair = soil.stm.getDST100(); break;
    case GET_DST200: stair = soil.stm.getDST200(); break;
    case GET_FRONTD:   stair = soil.stm.getFRONTD() * 1000.0; break;
    case GET_ACTLAY:   stair = soil.getACTLAYER() * 1000.0; break;
    case GET_THAWPCT:  stair = veg.getTHAWPCT() * 100.0; break;
    case GET_THWBEG1:  stair = soil.stm.getTHAWBEGIN1() * 1000.0; break;
    case GET_THWEND1:  stair = soil.stm.getTHAWEND1() * 1000.0; break;
    case GET_THWBEG2:  stair = soil.stm.getTHAWBEGIN2() * 1000.0; break;
    case GET_THWEND2:  stair = soil.stm.getTHAWEND2() * 1000.0; break;
    default:           stair = MISSING;
  }

  return stair;

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

double TTEM60::getOptionalTraceGas( const int& optflx )
{

  double outflux;

  switch( optflx )
  {
    case GET_GNH4:    outflux = y[I_NH4] * 1000.0; break;
    case GET_GNO3:    outflux = y[I_NO3] * 1000.0; break;
    case GET_NTRF:    outflux = y[I_NTRF] * 1000.0; break;
    case GET_DNTRF:   outflux = y[I_DNTRF] * 1000.0; break;
    case GET_AIMMNH4: outflux = y[I_AIMMNH4] * 1000.0; break;
    case GET_AMMN:    outflux = y[I_AMMN] * 1000.0; break;
    case GET_AIMMNO3: outflux = y[I_AIMMNO3] * 1000.0; break;
    case GET_NO3P:    outflux = y[I_NO3P] * 1000.0; break;
    case GET_NOP:     outflux = y[I_NOP] * 1000.0; break;
    case GET_N2OP:    outflux = y[I_N2OP] * 1000.0; break;
    case GET_N2P:     outflux = y[I_N2P] * 1000.0; break;
    case GET_GNLST:   outflux = soil.getNLOST() * 1000.0; break;
    case GET_NH3FLX:  outflux = y[I_NH3FLX] * 1000.0; break;
    case GET_NOFLX:   outflux = y[I_NOFLX] * 1000.0; break;
    case GET_N2OFLX:  outflux = y[I_N2OFLX] * 1000.0; break;
    case GET_N2FLX:   outflux = y[I_N2FLX] * 1000.0; break;
    case GET_GNMIN:   outflux = y[I_NMIN] * 1000.0; break;
    default:          outflux = MISSING;
  }

  return outflux;

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

double TTEM60::getOptionalWflx( const int& optflx )
{

  double outflux;

  switch( optflx )
  {
    case GET_SH2O:    outflux = y[I_SM]; break;
    
    case GET_PCTP:    outflux = (y[I_SM]
                                * soil.getACTLAYER() / soil.getROOTZ())
                                / soil.getTOTPOR(); 
                      break;
    
    case GET_VSM:     outflux = 100.0*y[I_SM]
                                / (soil.getROOTZ()*1000.0); 
                      break;

    case GET_AVLW:    outflux = soil.getAVLH2O(); break;
    case GET_RGRW:    outflux = y[I_RGRW]; break;
    case GET_SNWPK:   outflux = soil.getSNOWPACK(); break;
    case GET_SGRW:    outflux = y[I_SGRW]; break;
    case GET_RAIN:    outflux = atms.getRAIN(); break;
    case GET_SNWFAL:  outflux = atms.getSNOWFALL(); break;
    case GET_SNWINF:  outflux = soil.getSNOWINF(); break;
    case GET_AGIRRIG: outflux = y[I_AGIRRIG]; break;
    case GET_PET:     outflux = atms.getPET(); break;
    case GET_INEET:   outflux = y[I_INEET]; break;
    case GET_EET:     outflux = y[I_EET]; break;
    case GET_RPERC:   outflux = y[I_RPERC]; break;
    case GET_SPERC:   outflux = y[I_SPERC]; break;
    case GET_RRUN:    outflux = y[I_RRUN]; break;
    case GET_SRUN:    outflux = y[I_SRUN]; break;
    case GET_WYLD:    outflux = soil.getH2OYLD(); break;
    default:          outflux = MISSING;
  }

  return outflux;

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::getVegSpecificECD( const int& numcmnt, 
                                ofstream& rflog1 )
{

  int dv;
  string ecd;

  cout << "Enter name of the site (.ECD) data file with the";
  cout << " parameter values  for cmnt" << endl;

  rflog1 << "Enter name of the site (.ECD) data file with the";
  rflog1 << " parameter values cmnt" << endl;

  for( dv = 0; dv < numcmnt; ++dv )
  {
    cout << (dv+1) << ": ";
    cin >> ecd;

    rflog1 << (dv+1) << ": " << ecd << endl;

    getVegSpecificECD( dv, ecd );
  }

  rflog1 << endl;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TTEM60::getVegSpecificECD( const int& dv, 
                                const string&  ecd )
{
  int dlayer;

  ifstream fecd;

  string kstring;

  char tmpstring[80];

  fecd.open( ecd.c_str(), ios::in );

  if( !fecd )
  {
    cerr << endl;
    cerr << "Cannot open " << ecd << " for site ECD input";
    cerr << endl;
    
    exit( -1 );
  }

  veg.cmnt = getXMLCommunityNode( fecd,
                                  kstring,
                                  kstring,
                                  kstring,
                                  kstring,
                                  kstring,
                                  kstring,
                                  kstring );

  getXMLNode( fecd, "siteECD" );
 
  vegca[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "vegca",
                                           veg.cmnt );

  vegcb[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "vegcb",
                                           veg.cmnt );

  strna[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "strna",
                                           veg.cmnt );

  strnb[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "strnb",
                                           veg.cmnt );

  stona[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "stona",
                                           veg.cmnt );

  stonb[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "stonb",
                                           veg.cmnt );

  solca[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "solca",
                                           veg.cmnt );

  solcb[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "solcb",
                                           veg.cmnt );

  solna[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "solna",
                                           veg.cmnt );

  solnb[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "solnb",
                                           veg.cmnt );

  doccut[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "doccut",
                                            veg.cmnt );

  doc1a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "doc1a",
                                           veg.cmnt );

  doc1b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "doc1b",
                                           veg.cmnt );

  doc2a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "doc2a",
                                           veg.cmnt );

  doc2b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "doc2b",
                                           veg.cmnt );

  doncut[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "doncut",
                                            veg.cmnt );

  don1a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "don1a",
                                           veg.cmnt );

  don1b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "don1b",
                                           veg.cmnt );

  don2a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "don2a",
                                           veg.cmnt );

  don2b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "don2b",
                                           veg.cmnt );

  nh4a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "nh4a",
                                          veg.cmnt );

  nh4b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "nh4b",
                                          veg.cmnt );


  no3cut[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "no3cut",
                                            veg.cmnt );

  no31a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "no31a",
                                           veg.cmnt );

  no31b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "no31b",
                                           veg.cmnt );

  no32a[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "no32a",
                                           veg.cmnt );

  no32b[veg.cmnt] = getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "no32b",
                                           veg.cmnt );

  veg.setUNLEAF12( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "unleaf12",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setINITLEAFMX( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "initleafmx",
                                            veg.cmnt ),
                     veg.cmnt );

  veg.setCMAXCUT( getXMLcmntArrayDouble( fecd,
                                         "siteECD",
                                         "vegcmaxcut",
                                         veg.cmnt ),
                  veg.cmnt );

  veg.setCMAX1A( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                            "vegcmax1a",
                                            veg.cmnt ),
                 veg.cmnt );

  veg.setCMAX1B( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax1b",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setCMAX2A( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax2a",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setCMAX2B( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegcmax2b",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setCFALL( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegcfall",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setRMMAX( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegrmmax",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setRROOT( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegrroot",
                                       veg.cmnt ),
                veg.cmnt );

  microbe.setKDCUT( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "microbekdcut",
                                           veg.cmnt ),
                    veg.cmnt );

  microbe.setKD1A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd1a",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setKD1B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd1b",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setKD2A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd2a",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setKD2B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "microbekd2b",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setPROPFTOS( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbepropftos",
                                              veg.cmnt ),
                       veg.cmnt );

  soil.setPROPREACTA( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "soilpropReactA",
                                             veg.cmnt ),
                      veg.cmnt );

  soil.setPROPREACTB( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "soilpropReactB",
                                             veg.cmnt ),
                      veg.cmnt );

  soil.setNSOLPAR( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "soilnonOMpar",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setDOCPAR( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "microbeDOCpar",
                                            veg.cmnt ),
                     veg.cmnt );

  soil.setLCHDOMPAR( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "soillchDOMpar",
                                            veg.cmnt ),
                     veg.cmnt );

  veg.setNFIXPARA( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnfixpara",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNFIXPARB( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnfixparb",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNFIXADJUST( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "vegnfixadj",
                                            veg.cmnt ),
                     veg.cmnt );

  veg.setNUPNH4CUT( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "vegnupnh4cut",
                                           veg.cmnt ),
                    veg.cmnt );

  veg.setNUPNH41A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh41a",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNH41B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh41b",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNH42A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh42a",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNH42B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupnh42b",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNO3CUT( getXMLcmntArrayDouble( fecd,
                                           "siteECD",
                                           "vegnupno3cut",
                                           veg.cmnt ),
                    veg.cmnt );

  veg.setNUPNO31A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno31a",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNO31B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno31b",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNO32A( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno32a",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNUPNO32B( getXMLcmntArrayDouble( fecd,
                                          "siteECD",
                                          "vegnupno32b",
                                          veg.cmnt ),
                   veg.cmnt );

  veg.setNFALL( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegnfall",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setLCCLNC( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "veglcclnc",
                                        veg.cmnt ),
                 veg.cmnt );

  microbe.setNFIXPAR( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "microbenfixpar",
                                             veg.cmnt ),
                      veg.cmnt );

  microbe.setNH4IMMCUT( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbenh4immcut",
                                               veg.cmnt ),
                        veg.cmnt );

  microbe.setNH4IMM1A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm1a",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setNH4IMM1B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm1b",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setNH4IMM2A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm2a",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setNH4IMM2B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbenh4imm2b",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setAMMNPAR( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "microbeammnpar",
                                             veg.cmnt ),
                      veg.cmnt );

  microbe.setNTRFPARCUT( getXMLcmntArrayDouble( fecd,
                                                "siteECD",
                                                "microbentrfparcut",
                                                veg.cmnt ),
                         veg.cmnt );

  microbe.setNTRFPAR1A( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar1a",
                                               veg.cmnt ),
                        veg.cmnt );

  microbe.setNTRFPAR1B( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar1b",
                                               veg.cmnt ),
                        veg.cmnt );

  microbe.setNTRFPAR2A( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar2a",
                                               veg.cmnt ),
                        veg.cmnt );

  microbe.setNTRFPAR2B( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbentrfpar2b",
                                               veg.cmnt ), 
                        veg.cmnt );

  microbe.setINITNTRF( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeinitntrf",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setALLNTRF( getXMLcmntArrayDouble( fecd,
                                             "siteECD",
                                             "microbeallntrf",
                                             veg.cmnt ),
                      veg.cmnt );

  microbe.setTGMPAR( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "microbetgmpar",
                                            veg.cmnt ),
                     veg.cmnt );

  soil.setLCHNO3PARCUT( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "soillchNO3parcut",
                                               veg.cmnt ),
                        veg.cmnt );

  soil.setLCHNO3PAR1A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par1a",
                                              veg.cmnt ),
                       veg.cmnt );

  soil.setLCHNO3PAR1B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par1b",
                                              veg.cmnt ),
                       veg.cmnt );

  soil.setLCHNO3PAR2A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par2a",
                                              veg.cmnt ),
                       veg.cmnt );

  soil.setLCHNO3PAR2B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "soillchNO3par2b",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setDONPARCUT( getXMLcmntArrayDouble( fecd,
                                               "siteECD",
                                               "microbeDONparcut",
                                               veg.cmnt ),
                        veg.cmnt );

  microbe.setDONPAR1A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar1a",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setDONPAR1B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar1b",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setDONPAR2A( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar2a",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setDONPAR2B( getXMLcmntArrayDouble( fecd,
                                              "siteECD",
                                              "microbeDONpar2b",
                                              veg.cmnt ),
                       veg.cmnt );

  veg.setINITCNEVEN( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "veginitcneven",
                                            veg.cmnt ),
                     veg.cmnt );

  veg.setCNMIN( getXMLcmntArrayDouble( fecd,
                                       "siteECD",
                                       "vegcnmin",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setC2NA( getXMLcmntArrayDouble( fecd,
                                      "siteECD",
                                      "vegc2na",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setC2NB( getXMLcmntArrayDouble( fecd,
                                      "siteECD",
                                      "vegc2nb",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setC2NMIN( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "vegc2nmin",
                                        veg.cmnt ),
                 veg.cmnt );

  microbe.setCNSOIL( getXMLcmntArrayDouble( fecd,
                                            "siteECD",
                                            "microbecnsoil",
                                            veg.cmnt ),
                     veg.cmnt );

  veg.setO3PARA( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "o3para",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setO3PARB( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "o3parb",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setO3PARC( getXMLcmntArrayDouble( fecd,
                                        "siteECD",
                                        "o3parc",
                                        veg.cmnt ),
                 veg.cmnt );

  endXMLNode( fecd, "siteECD" );


  // Get vegetation-specific parameters for vegetation dynamics

  getXMLNode( fecd, "vegECD" );

  veg.setKC( getXMLcmntArrayDouble( fecd,
                                    "vegECD",
                                    "kc",
                                    veg.cmnt ),
             veg.cmnt );

  veg.setKI( getXMLcmntArrayDouble( fecd,
                                    "vegECD",
                                    "ki",
                                    veg.cmnt ),
             veg.cmnt );

  veg.setGVA( getXMLcmntArrayDouble( fecd,
                                     "vegECD",
                                     "gva",
                                     veg.cmnt ),
              veg.cmnt );

  veg.setTMIN( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "tmin",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setTOPTMIN( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "toptmin",
                                         veg.cmnt ),
                  veg.cmnt );

  veg.setTOPTMAX( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "toptmax",
                                         veg.cmnt ),
                  veg.cmnt );

  veg.setTMAX( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "tmax",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setTREF( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "tref",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setQREF( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "qref",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setALPHA( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "alpha",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setBETA( getXMLcmntArrayDouble( fecd,
                                      "vegECD",
                                      "beta",
                                      veg.cmnt ),
               veg.cmnt );

  veg.setGAMMA( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "gamma",
                                       veg.cmnt ),
                veg.cmnt );


  veg.setKVNH4( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "kvnh4",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setKVNO3( getXMLcmntArrayDouble( fecd,
                                       "vegECD",
                                       "kvno3",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setLABNCON( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "labncon",
                                         veg.cmnt ),
                  veg.cmnt );

  veg.setLEAFMXC( getXMLcmntArrayDouble( fecd,
                                         "vegECD",
                                         "leafmxc",
                                         veg.cmnt ),
                  veg.cmnt );

  veg.setKLEAFC( getXMLcmntArrayDouble( fecd,
                                        "vegECD",
                                        "kleafc",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setSLA( getXMLcmntArrayDouble( fecd,
                                     "vegECD",
                                     "sla",
                                     veg.cmnt ),
              veg.cmnt );

  veg.setCOV( getXMLcmntArrayDouble( fecd,
                                     "vegECD",
                                     "cov",
                                     veg.cmnt ),
              veg.cmnt );

  veg.setFPCMAX( getXMLcmntArrayDouble( fecd,
                                        "vegECD",
                                        "fpcmax",
                                        veg.cmnt ),
                 veg.cmnt );

  veg.setPROPTRANS( getXMLcmntArrayDouble( fecd,
                                           "vegECD",
                                           "proptrans",
                                           veg.cmnt ),
                    veg.cmnt );

  endXMLNode( fecd, "vegECD" );


  // Get vegetation-specific parameters for phenology

  getXMLNode( fecd, "leafECD" );


  veg.setMINLEAF( getXMLcmntArrayDouble( fecd,
                                         "leafECD",
                                         "minleaf",
                                         veg.cmnt ),
                  veg.cmnt );

  veg.setALEAF( getXMLcmntArrayDouble( fecd,
                                       "leafECD",
                                       "aleaf",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setBLEAF( getXMLcmntArrayDouble( fecd,
                                       "leafECD",
                                       "bleaf",
                                       veg.cmnt ),
                veg.cmnt );

  veg.setCLEAF( getXMLcmntArrayDouble( fecd,
                                       "leafECD",
                                       "cleaf",
                                       veg.cmnt ),
                veg.cmnt );

  endXMLNode( fecd, "leafECD" );


  // Get vegetation-specific parameters for microbe dynamics

  getXMLNode( fecd, "microbeECD" );

  microbe.setTREF( getXMLcmntArrayDouble( fecd,
                                          "microbeECD",
                                          "tref",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setQREF( getXMLcmntArrayDouble( fecd,
                                          "microbeECD",
                                          "qref",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setALPHA( getXMLcmntArrayDouble( fecd,
                                           "microbeECD",
                                           "alpha",
                                           veg.cmnt ),
                    veg.cmnt );

  microbe.setBETA( getXMLcmntArrayDouble( fecd,
                                          "microbeECD",
                                          "beta",
                                          veg.cmnt ),
                   veg.cmnt );

  microbe.setGAMMA( getXMLcmntArrayDouble( fecd,
                                           "microbeECD",
                                           "gamma",
                                           veg.cmnt ),
                    veg.cmnt );


  microbe.setKN2( getXMLcmntArrayDouble( fecd,
                                         "microbeECD",
                                         "kn2", 
                                         veg.cmnt),
                  veg.cmnt );

  microbe.setMOISTMIN( getXMLcmntArrayDouble( fecd,
                                              "microbeECD",
                                              "moistmin",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setMOISTOPT( getXMLcmntArrayDouble( fecd,
                                              "microbeECD",
                                              "moistopt",
                                              veg.cmnt ),
                       veg.cmnt );

  microbe.setMOISTMAX( getXMLcmntArrayDouble( fecd,
                                              "microbeECD",
                                              "moistmax",
                                              veg.cmnt ),
                       veg.cmnt );

  endXMLNode( fecd, "microbeECD" );


  // Get vegetation-specific parameters for rooting depth

  getXMLNode( fecd, "rootzECD" );
 
  soil.setROOTZA( getXMLcmntArrayDouble( fecd,
                                         "rootzECD",
                                         "rootza",
                                         veg.cmnt ),
                  veg.cmnt );

  soil.setROOTZB( getXMLcmntArrayDouble( fecd,
                                         "rootzECD",
                                         "rootzb",
                                         veg.cmnt ),
                  veg.cmnt );

  soil.setROOTZC( getXMLcmntArrayDouble( fecd,
                                         "rootzECD",
                                         "rootzc",
                                         veg.cmnt ),
                  veg.cmnt );

  soil.setMINROOTZ( getXMLcmntArrayDouble( fecd,
                                           "rootzECD",
                                           "minrootz",
                                           veg.cmnt ),
                    veg.cmnt );

  endXMLNode( fecd, "rootzECD" );


  // Get vegetation-specific parameters for the snowpack

  getXMLNode( fecd, "snowPackECD" );

  soil.stm.setVEGWINDSP( getXMLcmntArrayInt( fecd, 
                                             "snowPackECD", 
                                             "vegWindSp", 
                                             veg.cmnt ),
                         veg.cmnt ); 
    
  soil.stm.setGFLUX( getXMLcmntArrayDouble( fecd, 
                                            "snowPackECD", 
                                            "gflux",  
                                            veg.cmnt ),
                     veg.cmnt );

  soil.stm.setCDSNOW( getXMLcmntArrayDouble( fecd, 
                                             "snowPackECD", 
                                             "cdsnow",  
                                             veg.cmnt ),
                      veg.cmnt );

  soil.stm.setINITDTDAY( getXMLcmntArrayDouble( fecd, 
                                                "snowPackECD", 
                                                "DTDAY",  
                                                veg.cmnt ),
                         veg.cmnt );

  endXMLNode( fecd, "snowPackECD" );


  // Get vegetation-specific parameters for the soil layers

  getXMLNode( fecd, "soilLayerECD" );

  for( dlayer = 0; dlayer < MAXSLAYERS; ++dlayer )
  {
    sprintf( tmpstring, "%s%d", "THICK", (dlayer+1) );	
    soil.stm.setINITTHICK( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  veg.cmnt ),
                           veg.cmnt,
                           dlayer ); 

    sprintf( tmpstring, "%s%d", "DXA", (dlayer+1) );	
    soil.stm.setINITDXA( getXMLcmntArrayDouble( fecd, 
                                                "soilLayerECD", 
                                                tmpstring,  
                                                veg.cmnt ),
                         veg.cmnt,
                         dlayer );

    sprintf( tmpstring, "%s%d", "DXB", (dlayer+1) );	
    soil.stm.setINITDXB( getXMLcmntArrayDouble( fecd, 
                                                "soilLayerECD", 
                                                tmpstring,  
                                                veg.cmnt ),
                         veg.cmnt,
                         dlayer );

    sprintf( tmpstring, "%s%d", "MAT", (dlayer+1) );	
    soil.stm.setVEGMAT( getXMLcmntArrayLong( fecd, 
                                             "soilLayerECD", 
                                             tmpstring,  
                                             veg.cmnt ),
                        veg.cmnt,
                        dlayer ); 

    sprintf( tmpstring, "%s%d", "DENSE", (dlayer+1) );	
    soil.stm.setINITDENSE( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  veg.cmnt ),
                           veg.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "WATER", (dlayer+1) );	
    soil.stm.setINITWATER( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  veg.cmnt ),
                           veg.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "vcond", (dlayer+1) );	
    soil.stm.setVCOND( getXMLcmntArrayDouble( fecd, 
                                              "soilLayerECD", 
                                              tmpstring,  
                                              veg.cmnt ),
                       veg.cmnt,
                       dlayer );

    sprintf( tmpstring, "%s%d", "vsph", (dlayer+1) );	
    soil.stm.setVSPH( getXMLcmntArrayDouble( fecd, 
                                             "soilLayerECD", 
                                             tmpstring,  
                                             veg.cmnt ),
                      veg.cmnt,
                      dlayer ); 

    sprintf( tmpstring, "%s%d", "cond", (dlayer+1) );	
    soil.stm.setINITCONDT( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  veg.cmnt ),
                           veg.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "spht", (dlayer+1) );	
    soil.stm.setINITSPHT( getXMLcmntArrayDouble( fecd, 
                                                 "soilLayerECD", 
                                                 tmpstring,  
                                                 veg.cmnt ),
                          veg.cmnt,
                          dlayer );

    sprintf( tmpstring, "%s%d", "condf", (dlayer+1) );	
    soil.stm.setINITCONDF( getXMLcmntArrayDouble( fecd, 
                                                  "soilLayerECD", 
                                                  tmpstring,  
                                                  veg.cmnt ),
                           veg.cmnt,
                           dlayer );

    sprintf( tmpstring, "%s%d", "sphf", (dlayer+1) );	
    soil.stm.setINITSPHF( getXMLcmntArrayDouble( fecd, 
                                                 "soilLayerECD", 
                                                 tmpstring,  
                                                 veg.cmnt ),
                          veg.cmnt,
                          dlayer );
  }
 
  endXMLNode( fecd, "soilLayerECD" );

  // Get vegetation-specific parameters for disturbance

  getXMLNode( fecd, "agECD" );

  ag.setNVRETCONV( getXMLcmntArrayDouble( fecd,
                                          "agECD",
                                          "nvretconv",
                                          veg.cmnt ),
                   veg.cmnt );

  ag.setNSRETCONV( getXMLcmntArrayDouble( fecd,
                                          "agECD",
                                          "nsretconv",
                                          veg.cmnt ),
                   veg.cmnt );

  ag.setTILLFACTOR( getXMLcmntArrayDouble( fecd,
                                           "agECD",
                                           "tillfactor",
                                           veg.cmnt ),
                    veg.cmnt );

  ag.setHARVSTC( getXMLcmntArrayDouble( fecd,
                                        "agECD",
                                        "harvstC",
                                        veg.cmnt ),
                 veg.cmnt );

  ag.setHARVSTN( getXMLcmntArrayDouble( fecd,
                                        "agECD",
                                        "harvstN",
                                        veg.cmnt ),
                 veg.cmnt );

  ag.setRESIDUEC( getXMLcmntArrayDouble( fecd,
                                         "agECD",
                                         "residueC",
                                         veg.cmnt ),
                  veg.cmnt );

  ag.setRESIDUEN( getXMLcmntArrayDouble( fecd,
                                         "agECD",
                                         "residueN",
                                         veg.cmnt ),
                  veg.cmnt );

  ag.setCROPSEEDC( getXMLcmntArrayDouble( fecd,
                                          "agECD",
                                          "cropseedC",
                                          veg.cmnt ),
                   veg.cmnt );

  ag.setCROPSEEDSTRN( getXMLcmntArrayDouble( fecd,
                                             "agECD",
                                             "cropseedSTRN",
                                             veg.cmnt ),
                      veg.cmnt );

  ag.setCROPSEEDSTON( getXMLcmntArrayDouble( fecd,
                                             "agECD",
                                             "cropseedSTON",
                                             veg.cmnt ),
                      veg.cmnt );

  endXMLNode( fecd, "agECD" );

  fecd.close();

};

/* *************************************************************
************************************************************** */


/* **************************************************************
************************************************************** */

void TTEM60::initrun( ofstream& rflog1 )
{
  
  avlnflag = nfeed = rheqflag = 0;

/* **************************************************************
 *                   Run Model with Soil Thermal Model?
 ************************************************************* */

  #ifdef CALIBRATE_TEM
    printw( "Do you want to run the SOIL THERMAL MODEL (STM)?");
    refresh();

    cbreak();
    noecho();

    if( 'Y' == toupper( getch() ) )
    {
      soil.stmflg = 1;
      printw( "Y\n" );
      refresh();
    }
    else
    {
      soil.stmflg = 0;
      printw( "N\n" );
      refresh();
    }
  #else
    cout << "Do you want to run the SOIL THERMAL MODEL (STM)";
    cout << " to determine soil temperatures?" << endl;
    cout << "  Enter 0 for No" << endl;
    cout << "  Enter 1 for Yes" << endl;

    cin >> soil.stmflg;

    rflog1 << "Do you want to run the SOIL THERMAL MODEL (STM)";
    rflog1 << " to determine soil temperatures?" << endl;
    rflog1 << "  Enter 0 for No" << endl;
    rflog1 << "  Enter 1 for Yes" << endl;
    rflog1 << " telmnt[0].tem.soil.stmflg = ";
    rflog1 << soil.stmflg << endl << endl;
  #endif

/* **************************************************************
 *                   Run Model with Nitrogen Limitation?
 * ************************************************************** */


  #ifdef CALIBRATE_TEM
    printw( "Do you want to start calibration allowing available N to fluctuate? ");
    refresh();
    
    cbreak();
    noecho();

    if( 'Y' == toupper( getch() ) )
    {
      avlnflag = 1;
      printw( "Y\n" );
      refresh();
    }
    else
    {
      avlnflag = 0;
      printw( "N\n" );
      refresh();
    }
  #else
    cout << endl;
    cout << "Do you want to allow available N to fluctuate?";
    cout << endl;
    cout << "  Enter 0 for No" << endl;
    cout << "  Enter 1 for Yes: " << endl;

    cin >> avlnflag;
  
    rflog1 << endl << "Do you want to allow available N to fluctuate?";
    rflog1 << endl;
    rflog1 << "  Enter 0 for No" << endl;
    rflog1 << "  Enter 1 for Yes: " << endl;
    rflog1 << "avlnflag = " << avlnflag << endl << endl;
  #endif
  
  baseline = initbase = 0;
  
  #ifdef CALIBRATE_TEM
    printw( "\nDo you want to start calibration with N feedback on GPP? " );
    refresh();
    
    if( 'Y' == toupper( getch() ) )
    {
      nfeed = 1;
      printw( "Y\n" );
      refresh();   
   }
    else
    {
       nfeed = 0;
       printw( "N\n" );
       refresh();
    }
  #else
    cout << endl << "Do you want nitrogen feedback on GPP?" << endl;
    cout << "  Enter 0 for No" << endl;
    cout << "  Enter 1 for Yes:" << endl;
   
    cin >> nfeed;

    rflog1 << endl << "Do you want nitrogen feedback on GPP?";
    rflog1 << endl;
    rflog1 << "  Enter 0 for No" << endl;
    rflog1 << "  Enter 1 for Yes: " << endl;
    rflog1 << "nfeed = " << nfeed << endl << endl;

    if( 1 == nfeed )
    {
      cout << endl;
      cout << "Do you want to solve for baseline soil nitrogen?";
      cout << endl;
      cout << "  Enter 0 for No" << endl;
      cout << "  Enter 1 for Yes:" << endl;

      cin >> initbase;

      baseline = initbase;

      rflog1 << endl;
      rflog1 << "Do you want to solve for baseline soil nitrogen?";
      rflog1 << endl;
      rflog1 << "  Enter 0 for No" << endl;
      rflog1 << "  Enter 1 for Yes: " << endl;
      rflog1 << "baseline = " << baseline << endl << endl;
    }
  #endif
  
/* **************************************************************
			 Run Model with Moisture Limitation?
************************************************************** */

  moistlim = 0;
  
  #ifdef CALIBRATE_TEM
    printw( "Do you want to start calibration with moisture limitation? " );
    refresh();

    cbreak();
    noecho();
    if( 'Y' == toupper( getch() ) )
    {
      moistlim = 1;
      printw( "Y\n" );
      refresh();
    }
    else
    {
      moistlim = 0;
      printw( "N\n" );
      refresh();
    }
  #else
    cout << endl;
    cout << "Do you want to run the model with moisture limitation?";
    cout << endl;
    cout << "  Enter 0 for No" << endl;
    cout << "  Enter 1 for Yes:" << endl;

    cin >> moistlim;

    rflog1 << endl;
    rflog1 << "Do you want to run the model with moisture limitation?";
    rflog1 << endl;
    rflog1 << "  Enter 0 for No" << endl;
    rflog1 << "  Enter 1 for Yes: " << endl;
    rflog1 << "moistlim = " << moistlim << endl << endl;
  #endif
  
/****************************************************************
			 Run Model with Ozone?
************************************************************** */

  o3flag = 0;
  
  #ifdef CALIBRATE_TEM
    printw( "\nDo you want to start calibration with ozone? " );
    refresh();
 
    cbreak();
    noecho();
    if( 'Y' == toupper(getch()) )
    {
      o3flag = 1;
      printw( "Y\n" );
      refresh();
    }
    else
    {
      o3flag = 0;
      printw( "N\n" );
      refresh();
    }  
  #else
    cout << endl;
    cout << "Do you want to run the model with ozone?";
    cout << endl;
    cout << "  Enter 0 for No" << endl;
    cout <<  "  Enter 1 for Yes:" << endl;

    cin >> o3flag;

    rflog1 << endl;
    rflog1 << "Do you want to run the model with ozone?" << endl;
    rflog1 << "  Enter 0 for No" << endl;
    rflog1 << "  Enter 1 for Yes: " << endl;
    rflog1 << "o3flag = " << o3flag << endl << endl;
  #endif

/* ***************************************************************
	       Details for Steady State Conditions
************************************************************** */

  #ifdef CALIBRATE_TEM
    double co2level;
    double dc2n;

    equil = 0;
    adapttol = 0;
    intbomb = 0;
    tolbomb = 0;

    printw( "Do you want the model to stop at steady state conditions? " );
    refresh();
    
    if( 'Y' == toupper( getch() ) )
    {
      equil = 1;
      
      printw( "Y\n\n" );
      refresh;

      printw( "How many years do you want to wait before checking equilibrium conditions? " );
      refresh();

      nocbreak();
      echo();
      scanw( "%d", &strteq );

      if( 0 == nfeed )
      {
        cbreak();
        noecho();        
        printw( "Do you want decomposition to come into equilibrium?" );
        refresh();

        if( 'Y' == toupper(getch()) )
        {
	  rheqflag = 1;
	  printw( "Y\n" );
          refresh();
        }
        else 
        { 
          printw( "N\n" );
          refresh(); 
        }
      }

      printw( "\nEnter the absolute tolerance for the water cycle? " );
      refresh();

      nocbreak();
      echo();
      scanw( "%d", &wtol );

      printw( "\nEnter the absolute tolerance for the carbon cycle? " );
      refresh();

      scanw( "%d", &ctol );

      if( 1 == nfeed )
      {
        rheqflag = 1;
        
        printw( "\nEnter the absolute tolerance for the nitrogen cycle? " );
        refresh();

        scanw( "%d", &ntol );
      }

      printw( "\nDo you want to have the integrator tolerance adjusted automatically? " );
      refresh();
      
      cbreak();
      noecho();
      if( 'Y' == toupper( getch() ) )
      {
        printw( "Y\n" );
        refresh();

        adapttol = 1;
        
        
        askODE( rflog1 );
        
        printw( "\nEnter the maximum number of years for the model to run: " );
        refresh();

        nocbreak();
        echo();
        scanw( "%d", &maxyears );

        printw( "\nEnter the maximum number of attempts to reach a solution: " );
        refresh();

        scanw( "%d", &maxnrun );
      }
      else 
      { 
        printw( "N\n" );
        refresh(); 
      }
    }
    else 
    { 
      printw( "N\n\n" ); 
      refresh();
    }

    if ( 0 == adapttol ) { askODE( rflog1 ); }

    printw( "\nEnter the level of carbon dioxide in ppmv: " );
    refresh();

    nocbreak();
    echo();
    scanw( "%lf", &co2level );
    
    atms.setCO2LEVEL( co2level );

    printw( "\n\n\nEnter the factor for changing C:N per ppmv of enhanced CO2:\n" );
    printw( "               (Enter 0.0 for no change)\n" );
    refresh();
    
    scanw( "%lf", &dc2n );
    
    veg.setDC2N( dc2n );
    
    printw( "\n" );
    refresh();
  #else
    maxyears = 0;
    maxnrun = 0;

    cout << endl;
    cout << "How many years do you want to wait before checking equilibrium conditions? ";
    cout << endl;

    cin >> strteq;

    rflog1 << endl;
    rflog1 << "How many years do you want to wait before checking";
    rflog1 << " equilibrium conditions? ";
    rflog1 << endl;
    rflog1 << "strteq = " << strteq << endl << endl;

    cout << endl;
    cout << "Enter the maximum number of years for the model to run:";
    cout << endl;

    cin >> maxyears;

    rflog1 << endl;
    rflog1 << "Enter the maximum number of years for the model to run: ";
    rflog1 << endl;
    rflog1 << "maxyears = " << maxyears << endl << endl;

    runsize = maxyears;

    cout << endl;
    cout << "Enter the maximum number of attempts to reach a solution:";
    cout << endl;

    cin >> maxnrun;

    rflog1 << endl;
    rflog1 << "Enter the maximum number of attempts to reach a solution: ";
    rflog1 << endl;
    rflog1 << "maxnrun = " << maxnrun << endl << endl;

    if( 0 == nfeed )
    {
      cout << endl;
      cout << "Do you want decomposition to come into equilibrium?";
      cout << endl;
      cout << "  Enter 0 for No" << endl;
      cout << "  Enter 1 for Yes:" << endl;

      cin >> rheqflag;

      rflog1 << endl;
      rflog1 << "Do you want decomposition to come into equilibrium? ";
      rflog1 << endl;
      rflog1 << "  Enter 0 for No" << endl;
      rflog1 << "  Enter 1 for Yes: " << endl;
      rflog1 << "rheqflag = " << rheqflag << endl << endl;
    }
   
    wtol = 1000.0;

    cout << endl;
    cout << "What absolute tolerance do you want to use for";
    cout << " checking equilibrium" << endl;
    cout << "of the water cycle?" << endl;

    cin >> wtol;

    rflog1 << endl;
    rflog1 << "What absolute tolerance do you want to use for";
    rflog1 << " checking equilibrium";
    rflog1 << endl;
    rflog1 << "of the water cycle? wtol = " << wtol;
    rflog1 << endl << endl;

    ctol = 1000.0;

    cout << endl;
    cout << "What absolute tolerance do you want to use for";
    cout << " checking equilibrium" << endl;
    cout << "of the carbon cycle?" << endl;

    cin >> ctol;

    rflog1 << endl;
    rflog1 << "What absolute tolerance do you want to use for";
    rflog1 << " checking equilibrium";
    rflog1 << endl;
    rflog1 << "of the carbon cycle?" << endl;
    rflog1 << "ctol = " << ctol << endl << endl;

    ntol = 1000.0;

    if( 1 == nfeed )
    {
      rheqflag = 1;

      cout << endl;
      cout << "What absolute tolerance do you want to use for";
      cout << " checking equilibrium" << endl;
      cout << "of the nitrogen cycle?" << endl;

      cin >> ntol;

      rflog1 << endl;
      rflog1 << "What absolute tolerance do you want to use for";
      rflog1 << " checking equilibrium";
      rflog1 << endl;
      rflog1 << "of the nitrogen cycle?" << endl;
      rflog1 << "ntol = " << ntol << endl << endl;
    }

    if( 0 == equil )
    {

      cout << endl << endl;
      cout << "What year do you want to start collecting output data?";
      cout << endl;

      cin >> startyr;

      rflog1 << endl << endl;
      rflog1 << "What year do you want to start collecting output data? ";
      rflog1 << "startyr = " << startyr << endl;

      cout << endl << endl;
      cout << "What year do you want to stop collecting output data?";
      cout << endl;

      cin >> endyr;

      rflog1 << endl << endl;
      rflog1 << "What year do you want to stop collecting output data? ";
      rflog1 << "endyr = " << endyr << endl;

      cout << endl;
      cout << "How often (x years) should data be collected";
      cout << " after the initial year? ";
      cout << endl;

      cin >> diffyr;

      rflog1 << "How often (x years) should data be collected";
      rflog1 << " after the initial year? ";
      rflog1 << "diffyr = " << diffyr << endl;
    }
  #endif

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */
void TTEM60::lakeDynamics( const int& pdm, double pstate[] )
{

  soil.setPCTP( ZERO );

  soil.setVSM( ZERO );
  // Phenology
  
  veg.setUNNORMLEAF( ZERO );
  
  veg.setLEAF( ZERO );
  
  veg.setLAI( ZERO );
  
  veg.setFPC( ZERO );
  
  // Carbon fluxes in ecosystems
  
  veg.setINGPP( ZERO );
  
  veg.setGPP( ZERO );
  
  veg.setFOZONE( ZERO );
  
  veg.setFINDOZONE( ZERO );
  
  veg.setINNPP( ZERO );
  
  veg.setNPP( ZERO );
  
  veg.setGPR( ZERO );
  
  veg.setRMAINT( ZERO );
  
  veg.setRGRWTH( ZERO );
  
  veg.setABVGPR( ZERO );
  
  veg.setROOTRESP( ZERO );
  
  veg.setLTRFALC( ZERO );

  microbe.setDECOMP( ZERO );
  
  microbe.setRH( ZERO );

  microbe.setDOCPROD( ZERO );

  soil.setLEACHDOC( ZERO );

  soil.setERODEPOC( ZERO );


  // Nitrogen fluxes in ecosystems

  ag.fertn = ZERO;

  bnfix = ZERO;

  microbe.setNFIX( ZERO );

  veg.setNFIX( ZERO );

  microbe.setNFIX( ZERO );

  veg.setINUPTAKE( ZERO );
  veg.setINH4UPTAKE( ZERO );
  veg.setINO3UPTAKE( ZERO );

  veg.setNUPTAKE( ZERO );
  veg.setNH4UPTAKE( ZERO );
  veg.setNO3UPTAKE( ZERO );

  veg.setSUPTAKE( ZERO );
  veg.setLUPTAKE( ZERO );
  veg.setNMOBIL( ZERO );
  veg.setNRESORB( ZERO );

  veg.setLTRFALN( ZERO );

  microbe.setNDECOMP( ZERO );

  microbe.setDONPROD( ZERO );

  microbe.setGROSSNMIN( ZERO );

  microbe.setIMMNH4( ZERO );

  microbe.setIMMOB( ZERO );

  microbe.setNETNMIN( ZERO );

  soil.setABIMMOB( ZERO );

  soil.setLEACHDON( ZERO );

  soil.setERODEPON( ZERO );

  soil.setLEACHNH4( atms.getNH4DEP() );

  soil.setLEACHNO3( atms.getNO3DEP() );

  microbe.setAMMNVOL( ZERO );

  microbe.setNITRIF( ZERO );
  microbe.setNO3PROD( ZERO );
  microbe.setNOPROD( ZERO );
  microbe.setN2OPROD( ZERO );
  microbe.setN2PROD( ZERO );

  microbe.setDENITRIF( ZERO );

  soil.setNH3FLUX( ZERO );

  soil.setNOFLUX( ZERO );
  soil.setN2OFLUX( ZERO );
  soil.setN2FLUX( ZERO );

  // Water fluxes

  ag.irrigate = ZERO;

  if( atms.getRAIN() > atms.getPET() )
  {
    soil.setINEET( atms.getPET() );
    soil.setEET( soil.getINEET() );
  }
  else
  {
    soil.setINEET( atms.getRAIN() );
    soil.setEET( soil.getINEET() );
  }

  soil.setRPERC( atms.getRAIN() - soil.getEET() );
  soil.setSPERC( soil.getSNOWINF() );

  soil.setRRUN( soil.getRPERC() );
  soil.setSRUN( soil.getSPERC() );

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TTEM60::lawnDynamics( const int& pdm, double pstate[] )
{
  int fertflag = 0;
  int irrgflag = 0;
  int perennial = 1;
  int tillflag = 0;

  double avlNH4;
  double avlNO3;

  InorgN60 extraN;

  double newpctp;
  double newsh2o;
  double newvsm;

  double propReact;
  
  soil.updateHydrology( elev,
                        atms.getTAIR(),
                        atms.getPREVTAIR(),
                        atms.getPREV2TAIR(),
                        atms.getRAIN(),
                        atms.getPET(),
                        pstate[I_SM],
                        pstate[I_RGRW],
                        pstate[I_SGRW],
                        irrgflag,
                        ag.irrigate,
                        pdm );

                                      
  // Assume no agricultural N fertilization (ag.fertn) and no
  //  nutrients resulting from agricultural conversion

  ag.fertn = ZERO;
  microbe.setAMMNVOL( ZERO );


  // Determine biological N fixation and partition it between
  //   symbiotic N fixation (veg.nfix) and nonsymbiotic N
  //   fixation (microbe.nfix)

  if( soil.getEET() > 0.1 )
  {
    bnfix = veg.getNFIXPARA( ag.cmnt ) * soil.getEET()
            + veg.getNFIXPARB( ag.cmnt );
  }
  else { bnfix = ZERO; }

  microbe.setNFIX( (bnfix * microbe.getNFIXPAR( veg.cmnt )) );
  
  if( microbe.getNFIX() < ZERO ) { microbe.setNFIX( ZERO ); }

  veg.setNFIX( (bnfix - microbe.getNFIX()) );

  if( veg.getNFIX() < ZERO ) { veg.setNFIX( ZERO ); }
  

  // Reduce EET if vegetation is not mature
  
  soil.setEVAPORATION( soil.getEET() 
                       * (1.0 - veg.getPROPTRANS( ag.cmnt)) );
					   
  veg.updateFoliage( ag.cmnt, pstate[I_VEGC], soil.getEET() );                       

  soil.setEET( veg.getTRANSPIRATION() + soil.getEVAPORATION() );


  // Assume wetlands are wetter by the wfpsoff for determining
  //   moisture effects on vegetation and microbes

  newpctp = soil.getPCTP() + soil.getWFPSOFF();
  
  newsh2o = (newpctp * soil.getTOTPOR() * soil.getROOTZ()) 
		    / (100.0 * soil.getACTLAYER()); 

  newvsm = newsh2o / (soil.getROOTZ() * 1000.0);


  soil.setKH2O( newvsm, moistlim );

  // Get proportion of unfrozen organic matter in rooting zone
  
  propReact = soil.getThawedReactiveSOMProp( veg.cmnt );

  avlNH4 = pstate[I_NH4] * soil.getACTLAYER() / soil.getROOTZ();
  avlNO3 = pstate[I_NO3] * soil.getACTLAYER() / soil.getROOTZ();

  microbe.updateDynamics( veg.cmnt,
                          soil.getPCTFLDCAP(),
                          soil.getACTLAYER(),
                          (pstate[I_SOLC] * propReact),
                          (pstate[I_SOLN] * propReact),
                          newsh2o,
                          newvsm,
                          avlNH4,
                          (atms.getNH4DEP()+ ag.getNH4RETENT() + ag.getFIRENH4DEP()),
                          moistlim,
                          tillflag,
                          ag.getTILLFACTOR( veg.cmnt ),
                          soil.getKH2O() );

  if( disturbflag > 1 && pdm == (disturbmonth-1) )
  {
    // Set monthly vegetation fluxes to zero
    	
    veg.resetMonthlyFluxes();  	
  } 
  else
  {
    extraN.total = ag.getNTOTRETENT() + ag.getFIRENTOTDEP();
    extraN.nh4 = ag.getNH4RETENT() + ag.getFIRENH4DEP();
    extraN.no3 = ag.getNO3RETENT() + ag.getFIRENO3DEP();

    veg.updateDynamics( ag.cmnt,
                        atms.getCO2(),
                        atms.getAOT40(),
                        atms.getNDEP(),
                        extraN,
                        atms.getPAR(),
                        atms.getPET(),
                        atms.getPRVPETMX(),
                        soil.getEET(),
                        soil.getPRVEETMX(),
                        pstate[I_VEGC],
                        pstate[I_STRN],
                        pstate[I_STON],
                        newsh2o,
                        avlNH4,
                        avlNO3,
                        moistlim,
                        nfeed,
                        o3flag,
                        ag.state,
                        perennial,
                        totyr,
                        fertflag,
                        soil.getKH2O(),
                        microbe.getNETNMIN(),
                        microbe.getAMMNVOL(),
                        microbe.getNITRIF(),
                        microbe.getNO3PROD(),
                        ag.fertn );
  }                    

  // Determine carbon and nitrogen leaching losses
  
  soil.updateLeachingLosses( veg.cmnt,
                             (pstate[I_DOC] * propReact), 
                             (pstate[I_DON] * propReact), 
                             avlNO3, 
                             (pstate[I_SM] * soil.getACTLAYER() / soil.getROOTZ()) );
  

  if ( soil.getLEACHDOC() > (pstate[I_DOC]  
       + microbe.getDOCPROD()) )
  {
    soil.setLEACHDOC( (pstate[I_DOC] + microbe.getDOCPROD()) );
  }

  if ( soil.getLEACHDON() > (pstate[I_DON] 
         + microbe.getDONPROD()) )
  {
    soil.setLEACHDON( (pstate[I_DON] + microbe.getDONPROD()) );
  }

  
  // Determine loss of POC through erosion
  
  soil.setERODEPOC( ZERO );


  // Determine loss of PON through erosion
  
  soil.setERODEPON( ZERO );

               
  // Determine trace gas production based on microbe.no3prod,
  //   ag.fertn and water-filled pore space

  microbe.setTraceGasProduction( veg.cmnt,
                                 newpctp, 
                                 ag.fertn );
  
  
  if( soil.getLCHNO3PAR() > ZERO )
  {
    // Limit ecosystem N losses to total NO3 available for 
    //   leaching after denitrification has been substracted
    
    if ( soil.getLEACHNO3() > (avlNO3 + atms.getNO3DEP()
         + microbe.getNO3PROD() - microbe.getDENITRIF() 
         - veg.getNO3UPTAKE()) )
    {
      if ( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
           - microbe.getDENITRIF() - veg.getNO3UPTAKE()) > ZERO )
      {    
        soil.setLEACHNO3( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()
                           - microbe.getDENITRIF()
                           - veg.getNO3UPTAKE()) );
      }
      else
      {
        soil.setLEACHNO3( ZERO );

        if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
            - veg.getNO3UPTAKE()) > ZERO )
        {
          microbe.setDENITRIF( (avlNO3
                               + atms.getNO3DEP()
                               + microbe.getNO3PROD()
                               - veg.getNO3UPTAKE()) );
        }
        else
        {
          microbe.setDENITRIF( ZERO );
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( ZERO );

          veg.setNO3UPTAKE( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()) );
        }
      }
    }
  }
  else     
  {
    // If no leaching losses, limit ecosystem N losses to 
    //   total NO3 available for denitrification
    
    if( microbe.getDENITRIF() > (avlNO3 + atms.getNO3DEP() 
         + microbe.getNO3PROD() - veg.getNO3UPTAKE()) )
    {

      if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
          - veg.getNO3UPTAKE()) > ZERO )
      {
        microbe.setDENITRIF( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()
                             - veg.getNO3UPTAKE()) );
      }
      else
      {
        microbe.setDENITRIF( ZERO );
        microbe.setN2PROD( ZERO );
        microbe.setN2OPROD( ZERO );

        veg.setNO3UPTAKE( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()) );
      }

                                 
      if( microbe.getN2OPROD() > ZERO )
      {
        microbe.setN2PROD( microbe.getDENITRIF() - microbe.getN2OPROD() );
      
        if( microbe.getN2PROD() < ZERO )
        {
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( microbe.getDENITRIF() );
        }
      }
      else { microbe.setN2PROD( microbe.getDENITRIF() ); }           
    }    
  }


  // Determine trace gas fluxes based on ammonia volatilization
  //   (microbe.ammnvol), NO production (microbe.noprod),
  //   N2O production (microbe.n2oprod) and N2 production
  //   (microbe.n2prod)

  soil.setTraceGasFluxes( microbe.getAMMNVOL(),
                          microbe.getNOPROD(),
                          microbe.getN2OPROD(),
                          microbe.getN2PROD() );

  if( 0 == avlnflag )
  {
    // Do not allow changes in available nitrogen in soil
    //   (used during calibration process)

    // Equilibrate Ammonium (NH4) pool

    microbe.setAMMNVOL( (atms.getNH4DEP()
                        + microbe.getGROSSNMIN()
                        - microbe.getIMMNH4()
                        - veg.getNH4UPTAKE()
                        - microbe.getNITRIF()) );

    soil.setNH3FLUX( microbe.getAMMNVOL() );
    
    
    // Equilibrate nitrate (NO3) pool

    soil.setLEACHNO3( (atms.getNO3DEP()
                       + microbe.getNO3PROD()
                       - microbe.getDENITRIF()
                       - veg.getNO3UPTAKE()) );

    // Equilibrate DON pool

    soil.setLEACHDON( microbe.getDONPROD() );
  }

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TTEM60::massbal( double y[NUMEQ], 
                      double prevy[MAXSTATE] )
{
  if( (y[I_SM] - prevy[I_SM]) != (soil.getSNOWINF() + atms.getRAIN() 
      + y[I_AGIRRIG] - y[I_RPERC] - y[I_EET] - y[I_SPERC]) )
  {
    y[I_SPERC] = soil.getSNOWINF() 
                 + atms.getRAIN() 
                 + y[I_AGIRRIG] 
                 - y[I_RPERC] 
                 - y[I_EET]
                 - y[I_SM] 
                 + prevy[I_SM];
  }

  if( y[I_SPERC] < ZERO ) { y[I_SPERC] = ZERO; }


  if( (y[I_RGRW] - prevy[I_RGRW]) != (y[I_RPERC] - y[I_RRUN]) )
  {
    y[I_RRUN] = y[I_RPERC] - y[I_RGRW] + prevy[I_RGRW];
  }

  if( y[I_RRUN] < ZERO ) { y[I_RRUN] = ZERO; }


  if( (y[I_SGRW] - prevy[I_SGRW]) != (y[I_SPERC] - y[I_SRUN]) )
  {
    y[I_SRUN] = y[I_SPERC] - y[I_SGRW] + prevy[I_SGRW];
  }

  if( y[I_SRUN] < ZERO ) { y[I_SRUN] = ZERO; }


 
/************************* Carbon Cycle Balances **************************/

  if( y[I_INNPP] < y[I_NPP] ) { y[I_INNPP] = y[I_NPP]; }

  if( y[I_INGPP] < y[I_GPP] ) { y[I_INGPP] = y[I_GPP]; }

  if( y[I_GPR] != y[I_GPP] - y[I_NPP] )
  {
    y[I_GPR] = y[I_GPP] - y[I_NPP];
  }

  if( y[I_GPR] != y[I_RVMNT] + y[I_RVGRW] )
  {
    y[I_RVGRW] = y[I_GPR] - y[I_RVMNT];
  }


  if( y[I_VEGC] - prevy[I_VEGC]
      != y[I_NPP] - y[I_LTRFALC] )
  {
    y[I_LTRFALC] = y[I_NPP]- y[I_VEGC] + prevy[I_VEGC];
  }


  y[I_ERDPOC] = ZERO; 

  if( y[I_SOLC] - prevy[I_SOLC] != y[I_LTRFALC] + ag.getSLASHC() 
       - ag.getSCONVRTFLXC() - y[I_CDCMP] - y[I_ERDPOC] )
  {
    y[I_CDCMP] = y[I_LTRFALC] 
                 + ag.getSLASHC() 
                 - ag.getSCONVRTFLXC()
                 - y[I_ERDPOC] 
                 - y[I_SOLC] 
                 + prevy[I_SOLC];
  }

  if( y[I_DOCP] < ZERO ) { y[I_DOCP] = ZERO; }

  if( y[I_LCHDOC] < ZERO ) { y[I_LCHDOC] = ZERO; }

  if( y[I_DOC] - prevy[I_DOC] != y[I_DOCP] - y[I_LCHDOC] )
  {
    if( y[I_DOCP] - y[I_DOC] + prevy[I_DOC] > ZERO ) 
    {
      y[I_LCHDOC] = y[I_DOCP] - y[I_DOC] + prevy[I_DOC];
    }
    else
    {
      y[I_DOCP] = y[I_DOC] - prevy[I_DOC] + y[I_LCHDOC];
    }    
  }
  

  if( y[I_CDCMP] != y[I_RH] + y[I_DOCP] )
  {
    y[I_RH] = y[I_CDCMP] - y[I_DOCP];
  }
   


  /*********************Nitrogen Cycle Balances**********************/

  if( y[I_VNH4UP] < ZERO ) { y[I_VNH4UP] = ZERO; }
  if( y[I_VNO3UP] < ZERO ) { y[I_VNO3UP] = ZERO; }

  if( y[I_VNUP] != y[I_VNH4UP] + y[I_VNO3UP] )
  {
    y[I_VNUP] = y[I_VNH4UP] + y[I_VNO3UP];
  }

  if( y[I_VNUP] < ZERO ) { y[I_VNUP] = ZERO; }

  if( y[I_INNUP] < y[I_VNUP] ) { y[I_INNUP] = y[I_VNUP]; }

  if( y[I_VSUP] < ZERO ) { y[I_VSUP] = ZERO; }

  if( y[I_VSUP] > y[I_VNUP] ) { y[I_VSUP] = y[I_VNUP]; }

  if( y[I_VLUP] != y[I_VNUP] - y[I_VSUP] )
  {
    y[I_VLUP] = y[I_VNUP] - y[I_VSUP];
  }

  if( 1 == dbug )
  {
    cout << "y[I_VNUP]= " << y[I_VNUP] << " y[I_VSUP]= " << y[I_VSUP] << " y[I_VLUP]= " << y[I_VLUP] << endl;
  }

  // DWK modified the following conditions for checking the mass
  //   balance on STON on 0020401

  if( y[I_STON] - prevy[I_STON]
       != y[I_VLUP] + y[I_VNRSRB] - y[I_VNMBL] )
  {
    y[I_VNRSRB] = y[I_STON] 
                  - prevy[I_STON] 
                  + y[I_VNMBL]
                  - y[I_VLUP];
  }

  if( y[I_BNFIX] < ZERO ) { y[I_BNFIX] = ZERO; }
  if ( y[I_SNFIX] < ZERO ) { y[I_SNFIX] = ZERO; }
  
  if( y[I_BNFIX] != y[I_SNFIX] + y[I_ANFIX] )
  {
    y[I_ANFIX] = y[I_BNFIX] - y[I_SNFIX];
  }    
  
  if( y[I_ANFIX] < ZERO ) { y[I_ANFIX] = ZERO; }

  if( 1 == dbug )
  {
    cout << "y[I_LTRFALN]= " << y[I_LTRFALN] << endl;
    cout << "y[I_VSUP]= " << y[I_VSUP] << endl;
    cout << "y[I_VNMBL]= " << y[I_VNMBL] << endl;
    cout << "y[I_SNFIX]= " << y[I_SNFIX] << endl;
    cout << "y[I_VNRSRB]= " << y[I_VNRSRB] << endl; 
    cout << "y[I_STRN]= " << y[I_STRN] << endl;
    cout << "prevy[I_STRN]= " << prevy[I_STRN] << endl;

  }

  if( y[I_STRN] - prevy[I_STRN] != y[I_VSUP] - y[I_LTRFALN]
       - y[I_VNRSRB] + y[I_VNMBL] + y[I_SNFIX] )
  {
    y[I_LTRFALN] = y[I_VSUP] 
                - y[I_VNRSRB] 
                + y[I_VNMBL]
                + y[I_SNFIX] 
                - y[I_STRN] 
                + prevy[I_STRN];
  }

  y[I_ERDPON] = ZERO;

  if( 1 == dbug )
  {
    cout << "Second y[I_LTRFALN]= " << y[I_LTRFALN] << endl;
    cout << "y[I_SOLN]= " << y[I_SOLN] << endl;
    cout << "prevy[I_SOLN]= " << prevy[I_SOLN] << endl;
    
  }

  if( y[I_SOLN] - prevy[I_SOLN] != y[I_LTRFALN] 
      + ag.getSLASHN() + y[I_ANFIX] 
      - ag.getSCONVRTFLXN() - ag.getSNTOTRETENT() 
      - y[I_NDCMP] - y[I_ERDPON] )
  {
    y[I_NDCMP] = y[I_LTRFALN] 
                 + ag.getSLASHN() 
                 - ag.getSCONVRTFLXN()
                 - ag.getSNTOTRETENT() 
                 + y[I_ANFIX] 
                 - y[I_ERDPON]
                 - y[I_SOLN]  
                 + prevy[I_SOLN];
  }
  
  if( y[I_DONP] < ZERO ) { y[I_DONP] = ZERO; }

  if( y[I_LCHDON] < ZERO ) { y[I_LCHDON] = ZERO; }

  if( y[I_DON] - prevy[I_DON] != y[I_DONP] - y[I_LCHDON] )
  {
    if( y[I_DONP] - y[I_DON] + prevy[I_DON] > ZERO ) 
    {
      y[I_LCHDON] = y[I_DONP] - y[I_DON] + prevy[I_DON];
    }
    else
    {
      y[I_DONP] = y[I_DON] - prevy[I_DON] + y[I_LCHDON];
    }    
  }
 
   if( 1 == dbug )
  {
    cout << "Before y[I_NCMP]= " << y[I_NDCMP] << " y[I_NMIN]= " << y[I_NMIN] << " y[I_DONP]= " << y[I_DONP] << endl;   
  }

  if( y[I_NDCMP] != y[I_NMIN] + y[I_DONP] )
  {
    y[I_NMIN] = y[I_NDCMP] - y[I_DONP];
  }

  if( 1 == dbug )
  {
    cout << "y[I_NMIN]= " << y[I_NMIN] << " y[I_GMIN]= " << y[I_GMIN] << " y[I_NH4IMM]= " << y[I_NH4IMM] << endl;
  }
  if( y[I_NMIN] != y[I_GMIN] - y[I_NH4IMM] )
  {
    if ( y[I_NMIN] < ZERO )
    {
      y[I_NH4IMM] = y[I_GMIN] - y[I_NMIN];
      
      if( y[I_NH4IMM] > y[I_NH4] + y[I_GMIN] + atms.getNH4DEP() 
                        + ag.getNH4RETENT() 
                        + ag.getFIRENH4DEP() )
      {
        y[I_NH4IMM] = y[I_NH4] 
                      + y[I_GMIN] 
                      + atms.getNH4DEP()
                      + ag.getNH4RETENT()
                      + ag.getFIRENH4DEP();
      }
    }

    y[I_GMIN] = y[I_NMIN] + y[I_NH4IMM];
    y[I_NIMM] = y[I_NH4IMM];
    
    if( 1 == dbug )
    {
      cout << "After y[I_NMIN]= " << y[I_NMIN] << " y[I_GMIN]= " << y[I_GMIN] << " y[I_NH4IMM]= " << y[I_NH4IMM] << endl;
    }
  }

  if( y[I_AGFRTN] < ZERO ) { y[I_AGFRTN] = ZERO; }


  if( y[I_NTRF] < ZERO ) { y[I_NTRF] = ZERO; }

  if( y[I_NH4] - prevy[I_NH4]
      != atms.getNH4DEP() + ag.getNH4RETENT() 
         + ag.getFIRENH4DEP() + y[I_GMIN] 
         - y[I_NH4IMM] - y[I_VNH4UP] - y[I_AMMN] - y[I_NTRF] )
  {
    y[I_AIMMNH4] =  atms.getNH4DEP() 
                    + ag.getNH4RETENT()
                    + ag.getFIRENH4DEP()
                    + y[I_GMIN] 
                    - y[I_NH4IMM]
                    - y[I_VNH4UP] 
                    - y[I_AMMN] 
                    - y[I_NTRF]
                    - y[I_NH4] 
                    + prevy[I_NH4];
  }

  if( y[I_NOP] < ZERO ) {  y[I_NOP] = ZERO; }

  if( y[I_NO3P] < ZERO ) {  y[I_NO3P] = ZERO; }

  if( y[I_NTRF] != y[I_NO3P] + y[I_NOP] )
  {
    y[I_NO3P] = y[I_NTRF] - y[I_NOP];

    if( y[I_NO3P] < ZERO )
    {
      y[I_NO3P] = ZERO;
      y[I_NOP] = y[I_NTRF];
    }
  }

  if( y[I_N2OP] < ZERO ) {  y[I_N2OP] = ZERO; }
  if( y[I_N2P] < ZERO ) {  y[I_N2P] = ZERO; }

  if( y[I_LCHNO3] < ZERO ) { y[I_LCHNO3] = ZERO; }

  if( y[I_NO3] - prevy[I_NO3]
       != atms.getNO3DEP() + y[I_AGFRTN] + ag.getNO3RETENT() 
           + ag.getFIRENO3DEP() + y[I_NO3P] 
          - y[I_DNTRF] - y[I_VNO3UP] -  y[I_LCHNO3] )
  {
    if( soil.getLCHNO3PAR() > ZERO )
    {	
      if( atms.getNO3DEP() + y[I_AGFRTN] + ag.getNO3RETENT() 
          +  + ag.getFIRENO3DEP() + y[I_NO3P] 
          - y[I_DNTRF] - y[I_VNO3UP] - y[I_LCHNO3] 
          - y[I_NO3] + prevy[I_NO3] > ZERO )
      {
        y[I_LCHNO3] =  atms.getNO3DEP() 
                       + y[I_AGFRTN] 
                       + ag.getNO3RETENT() 
                       + ag.getFIRENO3DEP() 
                       + y[I_NO3P] 
                       - y[I_DNTRF] 
                       - y[I_VNO3UP] 
                       - y[I_NO3] 
                       + prevy[I_NO3];
      }
      else
      {
        y[I_AIMMNO3] =  atms.getNO3DEP() 
                        + y[I_AGFRTN] 
                        + ag.getNO3RETENT() 
                        + ag.getFIRENO3DEP() 
                        + y[I_NO3P] 
                        - y[I_VNO3UP] 
                        - y[I_DNTRF] 
                        - y[I_LCHNO3] 
                        - y[I_NO3] 
                        + prevy[I_NO3];
      }
    }
    else
    {
      if( atms.getNO3DEP() + y[I_AGFRTN] + ag.getNO3RETENT() 
           + ag.getFIRENO3DEP() + y[I_NO3P] 
          - y[I_DNTRF] - y[I_VNO3UP] - y[I_LCHNO3] 
          - y[I_NO3] + prevy[I_NO3] > ZERO )
      {
        y[I_DNTRF] = atms.getNO3DEP() 
                     + y[I_AGFRTN] 
                     + ag.getNO3RETENT() 
                     + ag.getFIRENO3DEP() 
                     + y[I_NO3P] 
                     - y[I_VNO3UP] 
                     - y[I_LCHNO3] 
                     - y[I_NO3] 
                     + prevy[I_NO3];      
      }
      else
      {
        y[I_AIMMNO3] =  atms.getNO3DEP() 
                        + y[I_AGFRTN] 
                        + ag.getNO3RETENT() 
                        + ag.getFIRENO3DEP() 
                        + y[I_NO3P] 
                        - y[I_VNO3UP] 
                        - y[I_LCHNO3] 
                        - y[I_DNTRF] 
                        - y[I_NO3] 
                        + prevy[I_NO3];
      }
    }
  }
  
  if( y[I_NH3FLX] < ZERO ) {  y[I_NH3FLX] = ZERO; }

  if( y[I_DNTRF] != y[I_N2OP] + y[I_N2P] )
  {
    y[I_N2P] = y[I_DNTRF] - y[I_N2OP];
 
    if( y[I_N2P] < ZERO )
    {
      y[I_N2P] = ZERO;
      y[I_N2OP] = y[I_DNTRF];
    }
  }   

  if( y[I_NOFLX] != y[I_NOP] ) { y[I_NOFLX] = y[I_NOP]; }  

  if( y[I_N2OFLX] != y[I_N2OP] ) { y[I_N2OFLX] = y[I_N2OP]; }  
   
  if( y[I_N2FLX] != y[I_N2P] ) { y[I_N2FLX] = y[I_N2P]; }  
  
};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

int TTEM60::monthlyTransient( const int& pdyr,
                              const int& pdm,
                              const double& ptol,
                              ofstream& pflog1 )
{
  endeq = 0;
  initFlag = 1;

  // Reset to appropriate rooting depth and texture-dependent 
  //   vegetation parameters for each cohort during each month
  //   (Note: microbe and soil parameters are the same between
  //   disturbed [ag.cmnt] and natural [veg.cmnt] land cover 

  if( (0 == ag.state || 6 == ag.state) 
      || (ag.state != 0 && ag.state !=6 
      && disturbflag > 0 && pdm < (disturbmonth-1)) )
  {
    soil.updateRootZ( veg.cmnt );

    veg.resetEcds( veg.cmnt, soil.getPSIPLUSC() );
  }
  else
  {
    soil.updateRootZ( ag.cmnt );
    
    veg.resetEcds( ag.cmnt, soil.getPSIPLUSC() );
  }
 

  // Reset texture-dependent parameters for microbes 
  //   and soil in current cohort

  microbe.resetEcds( veg.cmnt, soil.getPSIPLUSC() );

  soil.resetEcds( veg.cmnt );



  // Update monthly carbon, nitrogen and water dynamics of
  //   terrestrial ecosystem

  stepmonth( pdyr, pdm, intflag, ptol, pflog1 );


  // Update annual agricultural product pools and fluxes

  if( totyr == startyr ) { wrtyr = 0;}

  if( (CYCLE-1) == pdm )
  {
    if( (totyr > startyr) ) { ++wrtyr; }
  }

  return wrtyr;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::natvegDynamics( const int& pdm, double pstate[] )
{
  int agstate = 0;
  int fertflag = 0;
  int perennial = 1;
  int tillflag = 0;
  int irrgflag = 0;

  double avlNH4;
  double avlNO3;

  InorgN60 extraN;

  double newpctp;
  double newsh2o;
  double newvsm;
  
  double propReact;
  
  soil.updateHydrology( elev,
                        atms.getTAIR(),
                        atms.getPREVTAIR(),
                        atms.getPREV2TAIR(),
                        atms.getRAIN(),
                        atms.getPET(),
                        pstate[I_SM],
                        pstate[I_RGRW],
                        pstate[I_SGRW],
                        irrgflag,
                        ag.irrigate,
                        pdm );
						
                                      
  // Assume no agricultural N fertilization (ag.fertn) and no
  //  nutrients resulting from agricultural conversion

  ag.fertn = ZERO;
  microbe.setAMMNVOL( ZERO );


  // Determine biological N fixation and partition it between
  //   symbiotic N fixation (veg.nfix) and nonsymbiotic N
  //   fixation (microbe.nfix)

  if( soil.getEET() > 0.1 )
  {
    bnfix = veg.getNFIXPARA( veg.cmnt ) * soil.getEET()
            + veg.getNFIXPARB( veg.cmnt );
  }
  else { bnfix = ZERO; }

  microbe.setNFIX( (bnfix * microbe.getNFIXPAR( veg.cmnt )) );
  
  if( microbe.getNFIX() < ZERO ) { microbe.setNFIX( ZERO ); }

  veg.setNFIX( (bnfix - microbe.getNFIX()) );

  if( veg.getNFIX() < ZERO ) { veg.setNFIX( ZERO ); }
  

  // Reduce EET if vegetation is not mature
  
  soil.setEVAPORATION( soil.getEET() 
                       * (1.0 - veg.getPROPTRANS( veg.cmnt)) );
					   
  veg.updateFoliage( veg.cmnt, pstate[I_VEGC], soil.getEET() );                       

  soil.setEET( veg.getTRANSPIRATION() + soil.getEVAPORATION() );


  // Assume wetlands are wetter by the wfpsoff for determining
  //   moisture effects on vegetation and microbes

  newpctp = soil.getPCTP() + soil.getWFPSOFF();
  
  newsh2o = (newpctp * soil.getTOTPOR() * soil.getROOTZ()) 
		    / (100.0 * soil.getACTLAYER()); 

  newvsm = newsh2o / (soil.getROOTZ() * 1000.0);

  
  soil.setKH2O( newvsm, moistlim );


  // Get proportion of unfrozen organic matter in rooting zone
  
  propReact = soil.getThawedReactiveSOMProp( veg.cmnt );

  avlNH4 = pstate[I_NH4] * soil.getACTLAYER() / soil.getROOTZ();
  avlNO3 = pstate[I_NO3] * soil.getACTLAYER() / soil.getROOTZ();

  microbe.updateDynamics( veg.cmnt,
                          soil.getPCTFLDCAP(),
                          soil.getACTLAYER(),
                          (pstate[I_SOLC] * propReact),
                          (pstate[I_SOLN] * propReact),
                          newsh2o,
                          newvsm,
                          avlNH4,
                          (atms.getNH4DEP()+ ag.getNH4RETENT() + ag.getFIRENH4DEP()),
                          moistlim,
                          tillflag,
                          ag.getTILLFACTOR( veg.cmnt ),
                          soil.getKH2O() );

  if( disturbflag > 1 && pdm == (disturbmonth-1) )
  {
    // Set monthly vegetation fluxes to zero
    	
    veg.resetMonthlyFluxes();  	
  } 
  else
  {
    extraN.total = ag.getNTOTRETENT() + ag.getFIRENTOTDEP();
    extraN.nh4 = ag.getNH4RETENT() + ag.getFIRENH4DEP();
    extraN.no3 = ag.getNO3RETENT() + ag.getFIRENO3DEP();

    veg.updateDynamics( veg.cmnt,
                        atms.getCO2(),
                        atms.getAOT40(),
                        atms.getNDEP(),
                        extraN,
                        atms.getPAR(),
                        atms.getPET(),
                        atms.getPRVPETMX(),
                        soil.getEET(),
                        soil.getPRVEETMX(),
                        pstate[I_VEGC],
                        pstate[I_STRN],
                        pstate[I_STON],
                        newsh2o,
                        avlNH4,
                        avlNO3,
                        moistlim,
                        nfeed,
                        o3flag,
                        agstate,
                        perennial,
                        totyr,
                        fertflag,
                        soil.getKH2O(),
                        microbe.getNETNMIN(),
                        microbe.getAMMNVOL(),
                        microbe.getNITRIF(),
                        microbe.getNO3PROD(),
                        ag.fertn );
  }                    

  // Determine carbon and nitrogen leaching losses
  
  soil.updateLeachingLosses( veg.cmnt,
                             (pstate[I_DOC] * propReact), 
                             (pstate[I_DON] * propReact), 
                             avlNO3, 
                             (pstate[I_SM] * soil.getACTLAYER() / soil.getROOTZ()) );
  

  if ( soil.getLEACHDOC() > (pstate[I_DOC]  
       + microbe.getDOCPROD()) )
  {
    soil.setLEACHDOC( (pstate[I_DOC] + microbe.getDOCPROD()) );
  }

  if ( soil.getLEACHDON() > (pstate[I_DON] 
         + microbe.getDONPROD()) )
  {
    soil.setLEACHDON( (pstate[I_DON] + microbe.getDONPROD()) );
  }

  
  // Determine loss of POC through erosion
  
  soil.setERODEPOC( ZERO );


  // Determine loss of PON through erosion
  
  soil.setERODEPON( ZERO );

               
  // Determine trace gas production based on microbe.no3prod,
  //   ag.fertn and water-filled pore space

  microbe.setTraceGasProduction( veg.cmnt,
                                 newpctp, 
                                 ag.fertn );

 
  if( soil.getLCHNO3PAR() > ZERO )
  {
    // Limit ecosystem N losses to total NO3 available for 
    //   leaching after denitrification has been substracted
    
    if ( soil.getLEACHNO3() > (avlNO3 + atms.getNO3DEP()
         + microbe.getNO3PROD() - microbe.getDENITRIF() 
         - veg.getNO3UPTAKE()) )
    {
      if ( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
           - microbe.getDENITRIF() - veg.getNO3UPTAKE()) > ZERO )
      {    
        soil.setLEACHNO3( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()
                           - microbe.getDENITRIF()
                           - veg.getNO3UPTAKE()) );
      }
      else
      {
        soil.setLEACHNO3( ZERO );

        if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
            - veg.getNO3UPTAKE()) > ZERO )
        {
          microbe.setDENITRIF( (avlNO3
                               + atms.getNO3DEP()
                               + microbe.getNO3PROD()
                               - veg.getNO3UPTAKE()) );
        }
        else
        {
          microbe.setDENITRIF( ZERO );
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( ZERO );

          veg.setNO3UPTAKE( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()) );
        }
      }
    }
  }
  else     
  {
    // If no leaching losses, limit ecosystem N losses to 
    //   total NO3 available for denitrification
    
    if( microbe.getDENITRIF() > (avlNO3 + atms.getNO3DEP() 
         + microbe.getNO3PROD() - veg.getNO3UPTAKE()) )
    {
      if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
          - veg.getNO3UPTAKE()) > ZERO )
      {
        microbe.setDENITRIF( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()
                             - veg.getNO3UPTAKE()) );
      }
      else
      {
        microbe.setDENITRIF( ZERO );
        microbe.setN2PROD( ZERO );
        microbe.setN2OPROD( ZERO );

        veg.setNO3UPTAKE( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()) );
      }

                                 
      if( microbe.getN2OPROD() > ZERO )
      {
        microbe.setN2PROD( microbe.getDENITRIF() - microbe.getN2OPROD() );
      
        if( microbe.getN2PROD() < ZERO )
        {
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( microbe.getDENITRIF() );
        }
      }
      else { microbe.setN2PROD( microbe.getDENITRIF() ); }           
    }    
  }


  // Determine trace gas fluxes based on ammonia volatilization
  //   (microbe.ammnvol), NO production (microbe.noprod),
  //   N2O production (microbe.n2oprod) and N2 production
  //   (microbe.n2prod)

  soil.setTraceGasFluxes( microbe.getAMMNVOL(),
                          microbe.getNOPROD(),
                          microbe.getN2OPROD(),
                          microbe.getN2PROD() );


  if( 0 == avlnflag )
  {
    // Do not allow changes in available nitrogen in soil
    //   (used during calibration process)

    // Equilibrate Ammonium (NH4) pool

    microbe.setAMMNVOL( (atms.getNH4DEP()
                        + microbe.getGROSSNMIN()
                        - microbe.getIMMNH4()
                        - veg.getNH4UPTAKE()
                        - microbe.getNITRIF()) );

    soil.setNH3FLUX( microbe.getAMMNVOL() );
    
    
    // Equilibrate nitrate (NO3) pool

    soil.setLEACHNO3( (atms.getNO3DEP()
                       + microbe.getNO3PROD()
                       - microbe.getDENITRIF()
                       - veg.getNO3UPTAKE()) );

    // Equilibrate DON pool

    soil.setLEACHDON( microbe.getDONPROD() );
  }

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TTEM60::pastureDynamics( const int& pdm, double pstate[] )
{
  int fertflag = 0;
  int irrgflag = 0;
  int perennial = 1;
  int tillflag = 0;

  double avlNH4;
  double avlNO3;

  InorgN60 extraN;

  double newpctp;
  double newsh2o;
  double newvsm;

  double propReact;
  
  soil.updateHydrology( elev,
                        atms.getTAIR(),
                        atms.getPREVTAIR(),
                        atms.getPREV2TAIR(),
                        atms.getRAIN(),
                        atms.getPET(),
                        pstate[I_SM],
                        pstate[I_RGRW],
                        pstate[I_SGRW],
                        irrgflag,
                        ag.irrigate,
                        pdm );

                                      
  // Assume no agricultural N fertilization (ag.fertn) and no
  //  nutrients resulting from agricultural conversion

  ag.fertn = ZERO;
  microbe.setAMMNVOL( ZERO );


  // Determine biological N fixation and partition it between
  //   symbiotic N fixation (veg.nfix) and nonsymbiotic N
  //   fixation (microbe.nfix)

  if( soil.getEET() > 0.1 )
  {
    bnfix = veg.getNFIXPARA( ag.cmnt ) * soil.getEET()
            + veg.getNFIXPARB( ag.cmnt );
  }
  else { bnfix = ZERO; }

  microbe.setNFIX( (bnfix * microbe.getNFIXPAR( veg.cmnt )) );
  
  if( microbe.getNFIX() < ZERO ) { microbe.setNFIX( ZERO ); }

  veg.setNFIX( (bnfix - microbe.getNFIX()) );

  if( veg.getNFIX() < ZERO ) { veg.setNFIX( ZERO ); }
  

  // Reduce EET if vegetation is not mature
  
  soil.setEVAPORATION( soil.getEET() 
                       * (1.0 - veg.getPROPTRANS( ag.cmnt)) );
					   
  veg.updateFoliage( ag.cmnt, pstate[I_VEGC], soil.getEET() );                       

  soil.setEET( veg.getTRANSPIRATION() + soil.getEVAPORATION() );


  // Assume wetlands are wetter by the wfpsoff for determining
  //   moisture effects on vegetation and microbes

  newpctp = soil.getPCTP() + soil.getWFPSOFF();
  
  newsh2o = (newpctp * soil.getTOTPOR() * soil.getROOTZ()) 
		    / (100.0 * soil.getACTLAYER()); 

  newvsm = newsh2o / (soil.getROOTZ() * 1000.0);


  soil.setKH2O( newvsm, moistlim );

  // Get proportion of unfrozen organic matter in rooting zone
  
  propReact = soil.getThawedReactiveSOMProp( veg.cmnt );

  avlNH4 = pstate[I_NH4] * soil.getACTLAYER() / soil.getROOTZ();
  avlNO3 = pstate[I_NO3] * soil.getACTLAYER() / soil.getROOTZ();

  microbe.updateDynamics( veg.cmnt,
                          soil.getPCTFLDCAP(),
                          soil.getACTLAYER(),
                          (pstate[I_SOLC] * propReact),
                          (pstate[I_SOLN] * propReact),
                          newsh2o,
                          newvsm,
                          avlNH4,
                          (atms.getNH4DEP()+ ag.getNH4RETENT() + ag.getFIRENH4DEP()),
                          moistlim,
                          tillflag,
                          ag.getTILLFACTOR( veg.cmnt ),
                          soil.getKH2O() );

  if( disturbflag > 1 && pdm == (disturbmonth-1) )
  {
    // Set monthly vegetation fluxes to zero
    	
    veg.resetMonthlyFluxes();  	
  } 
  else
  {
    extraN.total = ag.getNTOTRETENT() + ag.getFIRENTOTDEP();
    extraN.nh4 = ag.getNH4RETENT() + ag.getFIRENH4DEP();
    extraN.no3 = ag.getNO3RETENT() + ag.getFIRENO3DEP();

    veg.updateDynamics( ag.cmnt,
                        atms.getCO2(),
                        atms.getAOT40(),
                        atms.getNDEP(),
                        extraN,
                        atms.getPAR(),
                        atms.getPET(),
                        atms.getPRVPETMX(),
                        soil.getEET(),
                        soil.getPRVEETMX(),
                        pstate[I_VEGC],
                        pstate[I_STRN],
                        pstate[I_STON],
                        newsh2o,
                        avlNH4,
                        avlNO3,
                        moistlim,
                        nfeed,
                        o3flag,
                        ag.state,
                        perennial,
                        totyr,
                        fertflag,
                        soil.getKH2O(),
                        microbe.getNETNMIN(),
                        microbe.getAMMNVOL(),
                        microbe.getNITRIF(),
                        microbe.getNO3PROD(),
                        ag.fertn );
  }                    

  // Determine carbon and nitrogen leaching losses
  
  soil.updateLeachingLosses( veg.cmnt,
                             (pstate[I_DOC] * propReact), 
                             (pstate[I_DON] * propReact), 
                             avlNO3, 
                             (pstate[I_SM] * soil.getACTLAYER() / soil.getROOTZ()) );
  

  if ( soil.getLEACHDOC() > (pstate[I_DOC]  
       + microbe.getDOCPROD()) )
  {
    soil.setLEACHDOC( (pstate[I_DOC] + microbe.getDOCPROD()) );
  }

  if ( soil.getLEACHDON() > (pstate[I_DON] 
         + microbe.getDONPROD()) )
  {
    soil.setLEACHDON( (pstate[I_DON] + microbe.getDONPROD()) );
  }

  
  // Determine loss of POC through erosion
  
  soil.setERODEPOC( ZERO );


  // Determine loss of PON through erosion
  
  soil.setERODEPON( ZERO );

               
  // Determine trace gas production based on microbe.no3prod,
  //   ag.fertn and water-filled pore space

  microbe.setTraceGasProduction( veg.cmnt,
                                 newpctp, 
                                 ag.fertn );
  
  
  if( soil.getLCHNO3PAR() > ZERO )
  {
    // Limit ecosystem N losses to total NO3 available for 
    //   leaching after denitrification has been substracted
    
    if ( soil.getLEACHNO3() > (avlNO3 + atms.getNO3DEP()
         + microbe.getNO3PROD() - microbe.getDENITRIF() 
         - veg.getNO3UPTAKE()) )
    {
      if ( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
           - microbe.getDENITRIF() - veg.getNO3UPTAKE()) > ZERO )
      {    
        soil.setLEACHNO3( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()
                           - microbe.getDENITRIF()
                           - veg.getNO3UPTAKE()) );
      }
      else
      {
        soil.setLEACHNO3( ZERO );

        if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
            - veg.getNO3UPTAKE()) > ZERO )
        {
          microbe.setDENITRIF( (avlNO3
                               + atms.getNO3DEP()
                               + microbe.getNO3PROD()
                               - veg.getNO3UPTAKE()) );
        }
        else
        {
          microbe.setDENITRIF( ZERO );
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( ZERO );

          veg.setNO3UPTAKE( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()) );
        }
      }
    }
  }
  else     
  {
    // If no leaching losses, limit ecosystem N losses to 
    //   total NO3 available for denitrification
    
    if( microbe.getDENITRIF() > (avlNO3 + atms.getNO3DEP() 
         + microbe.getNO3PROD() - veg.getNO3UPTAKE()) )
    {

      if( (avlNO3 + atms.getNO3DEP() + microbe.getNO3PROD() 
          - veg.getNO3UPTAKE()) > ZERO )
      {
        microbe.setDENITRIF( (avlNO3
                             + atms.getNO3DEP()
                             + microbe.getNO3PROD()
                             - veg.getNO3UPTAKE()) );
      }
      else
      {
        microbe.setDENITRIF( ZERO );
        microbe.setN2PROD( ZERO );
        microbe.setN2OPROD( ZERO );

        veg.setNO3UPTAKE( (avlNO3
                           + atms.getNO3DEP()
                           + microbe.getNO3PROD()) );
      }

                                 
      if( microbe.getN2OPROD() > ZERO )
      {
        microbe.setN2PROD( microbe.getDENITRIF() - microbe.getN2OPROD() );
      
        if( microbe.getN2PROD() < ZERO )
        {
          microbe.setN2PROD( ZERO );
          microbe.setN2OPROD( microbe.getDENITRIF() );
        }
      }
      else { microbe.setN2PROD( microbe.getDENITRIF() ); }           
    }    
  }


  // Determine trace gas fluxes based on ammonia volatilization
  //   (microbe.ammnvol), NO production (microbe.noprod),
  //   N2O production (microbe.n2oprod) and N2 production
  //   (microbe.n2prod)

  soil.setTraceGasFluxes( microbe.getAMMNVOL(),
                          microbe.getNOPROD(),
                          microbe.getN2OPROD(),
                          microbe.getN2PROD() );

  if( 0 == avlnflag )
  {
    // Do not allow changes in available nitrogen in soil
    //   (used during calibration process)

    // Equilibrate Ammonium (NH4) pool

    microbe.setAMMNVOL( (atms.getNH4DEP()
                        + microbe.getGROSSNMIN()
                        - microbe.getIMMNH4()
                        - veg.getNH4UPTAKE()
                        - microbe.getNITRIF()) );

    soil.setNH3FLUX( microbe.getAMMNVOL() );
    
    
    // Equilibrate nitrate (NO3) pool

    soil.setLEACHNO3( (atms.getNO3DEP()
                       + microbe.getNO3PROD()
                       - microbe.getDENITRIF()
                       - veg.getNO3UPTAKE()) );

    // Equilibrate DON pool

    soil.setLEACHDON( microbe.getDONPROD() );
  }

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::pcdisplayDT( const double& tottime,
                          const double& deltat )
{
  move( 15,1 );
  printw( "TIME = %10.8lf   DT = %10.8lf    ",
          tottime,
          deltat );

  refresh();

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::pcdisplayMonth( const int& dyr, const int& pdm )
{
  int iopt;

  char limitC[2];

  double outCflux[CSY];
  double outGflux[GSY];
  double outNflux[NSY];
  double outStair[STSY];
  double outWflux[WSY];

  if ( 0 == topwind )
  {
    clear();
    move( 1,1 );
    printw( " TIME  " );
    
    switch( calwind )
    {
      case 1: for( iopt = 0; iopt < WSY; ++iopt )
               {
                 move( 1, (12+(9*iopt)) );
                 displayOptionalWflx( swy[iopt] );
               }
               break;

      case 2:  for( iopt = 0; iopt < CSY; ++iopt )
               {
                 move( 1, (11+(9*iopt)) );
                 displayOptionalCflx( scy[iopt] );
               }
               break;

      case 3:  for( iopt = 0; iopt < NSY; ++iopt )
               {
                 move( 1, (8+(9*iopt)) );
                 displayOptionalNflx( sny[iopt] );
               }
               break;

      case 4:  for( iopt = 0; iopt < STSY; ++iopt )
               {
                 move( 1, (9+(7*iopt)) );
                 displayOptionalSoilTemp( ssty[iopt] );
               }
               break;

      case 5:  for( iopt = 0; iopt < GSY; ++iopt )
               {
                 move( 1, (9+(8*iopt)) );
                 displayOptionalTraceGas( sgy[iopt] );
               }
               break;

    }

    topwind = 1;
  }

  refresh();

 // Assign values of optional variables to outflux? for later 
  //   screen display

  // Carbon fluxes and pools

  outCflux[0] = getOptionalCflx( scy[0] );

  outCflux[1] = getOptionalCflx( scy[1] );

  outCflux[2] = getOptionalCflx( scy[2] );

  outCflux[3] = getOptionalCflx( scy[3] );

  outCflux[4] = getOptionalCflx( scy[4] );

  outCflux[5] = getOptionalCflx( scy[5] );

  outCflux[6] = getOptionalCflx( scy[6] );

  outCflux[7] = getOptionalCflx( scy[7] );

  outCflux[8] = getOptionalCflx( scy[8] );


  // Nitrogen fluxes and pools

  outNflux[0] = getOptionalNflx( sny[0] );

  outNflux[1] = getOptionalNflx( sny[1] );

  outNflux[2] = getOptionalNflx( sny[2] );

  outNflux[3] = getOptionalNflx( sny[3] );

  outNflux[4] = getOptionalNflx( sny[4] );

  outNflux[5] = getOptionalNflx( sny[5] );

  outNflux[6] = getOptionalNflx( sny[6] );

  outNflux[7] = getOptionalNflx( sny[7] );

  outNflux[8] = getOptionalNflx( sny[8] );


  // Water fluxes and pools

  outWflux[0] = getOptionalWflx( swy[0] );

  outWflux[1] = getOptionalWflx( swy[1] );

  outWflux[2] = getOptionalWflx( swy[2] );

  outWflux[3] = getOptionalWflx( swy[3] );

  outWflux[4] = getOptionalWflx( swy[4] );

  outWflux[5] = getOptionalWflx( swy[5] );

  outWflux[6] = getOptionalWflx( swy[6] );

  outWflux[7] = getOptionalWflx( swy[7] );

  outWflux[8] = getOptionalWflx( swy[8] );


  // Soil Temperatures

  outStair[0] = getOptionalSoilTemp( ssty[0] );

  outStair[1] = getOptionalSoilTemp( ssty[1] );

  outStair[2] = getOptionalSoilTemp( ssty[2] );

  outStair[3] = getOptionalSoilTemp( ssty[3] );

  outStair[4] = getOptionalSoilTemp( ssty[4] );

  outStair[5] = getOptionalSoilTemp( ssty[5] );

  outStair[6] = getOptionalSoilTemp( ssty[6] );

  outStair[7] = getOptionalSoilTemp( ssty[7] );

  outStair[8] = getOptionalSoilTemp( ssty[8] );

  outStair[9] = getOptionalSoilTemp( ssty[9] );



  // Trace Gas Fluxes

  outGflux[0] = getOptionalTraceGas( sgy[0] );

  outGflux[1] = getOptionalTraceGas( sgy[1] );

  outGflux[2] = getOptionalTraceGas( sgy[2] );

  outGflux[3] = getOptionalTraceGas( sgy[3] );

  outGflux[4] = getOptionalTraceGas( sgy[4] );

  outGflux[5] = getOptionalTraceGas( sgy[5] );

  outGflux[6] = getOptionalTraceGas( sgy[6] );

  outGflux[7] = getOptionalTraceGas( sgy[7] );

  outGflux[8] = getOptionalTraceGas( sgy[8] );

  move( (pdm+2), 1 );

  // Display monthly values for selected C and N pools and fluxes

  switch( calwind )
  {
    case 1: printw( "%4d-%2d %9.2lf %8.2lf %8.2lf %8.2lf %8.1lf %8.1lf %8.1lf %8.1lf %8.2lf",
                    dyr,
                    (pdm+1),
                    outWflux[0],
                    outWflux[1],
                    outWflux[2],
                    outWflux[3],
                    outWflux[4],
                    outWflux[5],
                    outWflux[6],
                    outWflux[7],
                    outWflux[8] );
            break;
            
    case 2: // Productivity is nitrogen limited

            if ( (y[I_INNPP] > y[I_NPP])
                 && (y[I_INNUP] == y[I_VNUP]) )
            {
              strcpy( limitC, "N" );
            }

            // Productivity is either carbon or nitrogen limited

            if ( (y[I_INNPP] == y[I_NPP])
                 && (y[I_INNUP] == y[I_VNUP]) )
            {
              strcpy( limitC, "E" );
            }

            // Productivity is carbon limited (climate)

            if ( (y[I_INNPP] == y[I_NPP])
                 && (y[I_INNUP] > y[I_VNUP]) )
            {
              strcpy( limitC, "C" );
            }

            // Productivity is limited by both carbon and nitrogen

            if ( (y[I_INNPP] > y[I_NPP])
                 && (y[I_INNUP] > y[I_VNUP]) )
            {
              strcpy( limitC, "B" );
            }

            // Unknown limits on productivity

            if ( y[I_INNPP] < y[I_NPP]
                 || y[I_INNUP] < y[I_VNUP] )
            {
              strcpy( limitC, "?" );
            }

            printw( "%3d-%2d %s %8.2lf %8.2lf %8.2lf %8.3lf %8.3lf %8.3lf %8.3lf %8.3lf %8.3lf ",
                    dyr,
                    (pdm+1),
                    limitC,
                    outCflux[0],
                    outCflux[1],
                    outCflux[2],
                    outCflux[3],
                    outCflux[4],
                    outCflux[5],
                    outCflux[6],
                    outCflux[7],
                    outCflux[8] );

            break;
    
    case 3: printw( "%3d-%2d %8.2lf %8.3lf %8.2lf %8.4lf %8.4lf %8.4lf %8.4lf %8.4lf %8.4lf",
                    dyr,
                    (pdm+1),
                    outNflux[0],
                    outNflux[1],
                    outNflux[2],
                    outNflux[3],
                    outNflux[4],
                    outNflux[5],
                    outNflux[6],
                    outNflux[7],
                    outNflux[8] );
            break;

    case 4: printw( "%4d-%2d %6.1lf %6.1lf %6.1lf %6.1lf %6.1lf %6.1lf %6.1lf %6.1lf %7.1lf %7.1lf",
                    dyr,
                    (pdm+1),
                    outStair[0],
                    outStair[1],
                    outStair[2],
                    outStair[3],
                    outStair[4],
                    outStair[5],
                    outStair[6],
                    outStair[7],
                    outStair[8],
                    outStair[9] );
            break;
    case 5: printw("%4d-%2d %7.1lf %7.1lf %7.1lf %7.1lf %7.1lf %7.1lf %7.1lf %7.1lf %7.1lf",
                    dyr,
                    (pdm+1),
                    outGflux[0],
                    outGflux[1],
                    outGflux[2],
                    outGflux[3],
                    outGflux[4],
                    outGflux[5],
                    outGflux[6],
                    outGflux[7],
                    outGflux[8] );
            break;

  }

  refresh();

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

#ifdef CALIBRATE_TEM

void TTEM60::pcdisplayODEerr( const int& test, double pstate[] )
{
  int errtest;

  move( 15,40 );
  printw( "                                                                                         " );
  move( 15,40 );

  if ( test != ACCEPT )
  {
    errtest = test - 1;
    switch( errtest )
    {
      case   I_VEGC: printw( "   VEGC = %8.2lf  Error = %11.8lf  ",
                             pstate[I_VEGC],
                             error[I_VEGC] );
                     break;

      case   I_SOLC: printw( "  SOILC = %8.2lf  Error = %11.8lf  ",
                             pstate[I_SOLC],
                             error[I_SOLC] );
                     break;

      case   I_STRN: printw( "   STRN = %8.2lf  Error = %11.8lf  ",
                             pstate[I_STRN],
                             error[I_STRN] );
                     break;

      case   I_STON: printw( "LABILEN = %8.3lf  Error = %11.8lf  ",
                             pstate[I_STON],
                             error[I_STON] );
                     break;

      case   I_SOLN: printw( "  SOILN = %8.2lf  Error = %11.8lf  ",
                             pstate[I_SOLN],
                             error[I_SOLN] );
                     break;

      case   I_NH4: printw( "    NH4 = %8.5lf  Error = %11.8lf  ",
                             pstate[I_NH4],
                             error[I_NH4] );
                     break;

      case   I_NO3: printw( "    NO3 = %8.5lf  Error = %11.8lf  ",
                             pstate[I_NO3],
                             error[I_NO3] );

      case  I_INGPP: printw( "INITGPP = %8.1lf  Error = %11.8lf  ",
                             pstate[I_INGPP],
                             error[I_INGPP] );
                     break;

      case    I_GPP: printw( "    GPP = %8.1lf  Error = %11.8lf  ",
                             pstate[I_GPP],
                             error[I_GPP] );
                     break;

      case  I_INNPP: printw( "INITNPP = %8.1lf  Error = %11.8lf  ",
                             pstate[I_INNPP],
                             error[I_INNPP] );
                     break;

      case    I_NPP: printw( "    NPP = %8.1lf  Error = %11.8lf  ",
                             pstate[I_NPP],
                             error[I_NPP] );
                     break;

      case    I_GPR: printw( "     RA = %8.1lf  Error = %11.8lf  ",
                             pstate[I_GPR],
                             error[I_GPR] );
                     break;

      case  I_RVMNT: printw( "     RM = %8.1lf  Error = %11.8lf  ",
                             pstate[I_RVMNT],
                             error[I_RVMNT] );
                     break;

      case  I_RVGRW: printw( "     RG = %8.1lf  Error = %11.8lf  ",
                             pstate[I_RVGRW],
                             error[I_RVGRW] );
                     break;

      case  I_LTRFALC: printw( "LTRFALC = %8.1lf  Error = %11.8lf  ",
                             pstate[I_LTRFALC],
                             error[I_LTRFALC] );
                     break;

      case     I_RH: printw( "     RH = %8.1lf  Error = %11.8lf  ",
                             pstate[I_RH],
                             error[I_RH] );
                     break;

      case I_LCHDOC: printw( " LCHDOC = %8.1lf  Error = %11.8lf  ",
                             pstate[I_LCHDOC],
                             error[I_LCHDOC] );
                     break;


      case I_AGFRTN: printw( "AGFERTN = %8.3lf  Error = %11.8lf  ",
                              pstate[I_AGFRTN],
                              error[I_AGFRTN] );
                     break;

      case  I_SNFIX: printw( "  SNFIX = %8.3lf  Error = %11.8lf  ",
                             pstate[I_SNFIX],
                             error[I_SNFIX] );
                     break;

      case  I_ANFIX: printw( "  ANFIX = %8.3lf  Error = %11.8lf  ",
                             pstate[I_ANFIX],
                             error[I_ANFIX] );
                     break;

      case  I_INNUP: printw( "INUPTAK = %8.3lf  Error = %11.8lf  ",
                             pstate[I_INNUP],
                             error[I_INNUP] );
                     break;

      case I_INNH4UP: printw( "INNH4UP = %8.3lf  Error = %11.8lf  ",
                              pstate[I_INNH4UP],
                              error[I_INNH4UP] );
                      break;

      case I_INNO3UP: printw( "INNO3UP = %8.3lf  Error = %11.8lf  ",
                              pstate[I_INNO3UP],
                              error[I_INNO3UP] );
                      break;

      case   I_VNUP: printw( "NUPTAKE = %8.3lf  Error = %11.8lf  ",
                             pstate[I_VNH4UP],
                             error[I_VNH4UP] );
                     break;

      case I_VNH4UP: printw( "  NH4UP = %8.3lf  Error = %11.8lf  ",
                             pstate[I_VNH4UP],
                             error[I_VNH4UP] );
                     break;

      case I_VNO3UP: printw( "  NO3UP = %8.3lf  Error = %11.8lf  ",
                             pstate[I_VNO3UP],
                             error[I_VNO3UP] );
                     break;

      case   I_VSUP: printw( "SUPTAKE = %8.3lf  Error = %11.8lf  ",
                             pstate[I_VSUP],
                             error[I_VSUP] );
                     break;

      case   I_VLUP: printw( "LUPTAKE = %8.3lf  Error = %11.8lf  ",
                             pstate[I_VLUP],
                             error[I_VLUP] );
                     break;

      case  I_VNMBL: printw( " NMOBIL = %8.3lf  Error = %11.8lf  ",
                             pstate[I_VNMBL],
                             error[I_VNMBL] );
                     break;

      case   I_LTRFALN: printw( "LTRFALN = %8.3lf  Error = %11.8lf  ",
                             pstate[I_LTRFALN],
                             error[I_LTRFALN] );
                     break;

      case   I_GMIN: printw( "   GMIN = %8.3lf  Error = %11.8lf  ",
                             pstate[I_GMIN],
                             error[I_GMIN] );
                     break;

      case   I_NIMM: printw( "MCRONUP = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NIMM],
                             error[I_NIMM] );
                     break;

      case   I_NMIN: printw( "   NMIN = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NMIN],
                             error[I_NMIN] );
                     break;

      case   I_AMMN: printw( "AMMNVOL = %8.3lf  Error = %11.8lf  ",
                             pstate[I_AMMN],
                             error[I_AMMN] );
                     break;

      case   I_NTRF: printw( " NITRIF = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NTRF],
                             error[I_NTRF] );
                     break;

      case   I_NO3P: printw( " NO3PRD = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NO3P],
                             error[I_NO3P] );
                     break;

      case   I_NOP: printw( "  NOPRD = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NOP],
                             error[I_NOP] );
                     break;

      case   I_N2OP: printw( " N2OPRD = %8.3lf  Error = %11.8lf  ",
                             pstate[I_N2OP],
                             error[I_N2OP] );
                     break;

      case    I_N2P: printw( "  N2PRD = %8.3lf  Error = %11.8lf  ",
                             pstate[I_N2P],
                             error[I_N2P] );
                     break;

      case  I_DNTRF: printw( "DNITRIF = %8.3lf  Error = %11.8lf  ",
                             pstate[I_DNTRF],
                             error[I_DNTRF] );
                     break;

      case I_NH3FLX: printw( " NH3FLX = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NH3FLX],
                             error[I_NH3FLX] );
                     break;

      case  I_NOFLX: printw( "  NOFLX = %8.3lf  Error = %11.8lf  ",
                             pstate[I_NOFLX],
                             error[I_NOFLX] );
                     break;

      case I_N2OFLX: printw( " N2OFLX = %8.3lf  Error = %11.8lf  ",
                             pstate[I_N2OFLX],
                             error[I_N2OFLX] );
                     break;

      case  I_N2FLX: printw( "  N2FLX = %8.3lf  Error = %11.8lf  ",
                             pstate[I_N2FLX],
                             error[I_N2FLX] );
                     break;

      case I_LCHNO3: printw( " LCHNO3 = %8.1lf  Error = %11.8lf  ",
                             pstate[I_LCHNO3],
                             error[I_LCHNO3] );
                     break;

      case I_LCHDON: printw( " LCHDON = %8.1lf  Error = %11.8lf  ",
                             pstate[I_LCHDON],
                             error[I_LCHDON] );
                     break;

      case I_UNRMLF: printw( " UNLEAF = %8.3lf  Error = %11.8lf  ",
                             pstate[I_UNRMLF],
                             error[I_UNRMLF] );
                     break;

      case   I_LEAF: printw( "   LEAF = %8.3lf  Error = %11.8lf  ",
                             pstate[I_LEAF],
                             error[I_LEAF] );
                     break;

      case   I_RGRW: printw( " RGRNDW = %8.2lf  Error = %11.8lf  ",
                             pstate[I_RGRW],
                             error[I_RGRW] );
                     break;

      case   I_SGRW: printw( " SGRNDW = %8.2lf  Error = %11.8lf  ",
                             pstate[I_SGRW],
                             error[I_SGRW] );
                     break;

      case     I_SM: printw( " SMOIST = %8.5lf  Error = %11.8lf  ",
                             pstate[I_SM],
                             error[I_SM] );
                     break;

      case  I_RPERC: printw( "  RPERC = %8.3lf  Error = %11.8lf  ",
                             pstate[I_RPERC],
                             error[I_RPERC] );
                     break;

      case   I_RRUN: printw( "   RRUN = %8.1lf  Error = %11.8lf  ",
                             pstate[I_RRUN],
                             error[I_RRUN] );
                     break;

      case  I_SPERC: printw( "  SPERC = %8.1lf  Error = %11.8lf  ",
                             pstate[I_SPERC],
                             error[I_SPERC] );
                     break;

      case   I_SRUN: printw( "   SRUN = %8.1lf  Error = %11.8lf  ",
                             pstate[I_SRUN],
                             error[I_SRUN] );
                     break;

      case    I_EET: printw( "    EET = %8.3lf  Error = %11.8lf  ",
                             pstate[I_EET],
                             error[I_EET] );
                     break;
    }
  }

  refresh();

};

#endif

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************** */

void TTEM60::resetMonthlyELMNTFluxes( void )
{

  // Reset all monthly fluxes to zero

  atms.resetMonthlyFluxes();
  
  veg.resetMonthlyFluxes();
  
  microbe.resetMonthlyFluxes();
  
  soil.resetMonthlyFluxes();
  
  ag.resetMonthlyFluxes();
  
  // Carbon fluxes 

  rsoil = ZERO;
  nep = ZERO;
  nce = ZERO;
  necb = ZERO;

  // Nitrogen fluxes 

  bnfix = ZERO;
  nenb = ZERO;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TTEM60::resetODEflux( void )
{
  int i;

  for( i = MAXSTATE; i < NUMEQ; ++i ) { y[i] = ZERO; }

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TTEM60::resetYrFluxes( void )
{

  atms.resetYrFluxes();
  
  veg.resetYrFluxes();
  
  microbe.resetYrFluxes();
  
  soil.resetYrFluxes();
  
  ag.resetYrFluxes();
  
  yrtotalc = ZERO;

  // Annual carbon fluxes

  yrrsoil = ZERO;
  yrnep = ZERO;
  yrnce = ZERO;
  yrnecb = ZERO;

  // Annual nitrogen fluxes
 
  yrbnfix = ZERO;
  yrnenb = ZERO;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TTEM60::rkf( const int& numeq, 
                  double pstate[], 
                  double& pdt, 
                  const int& pdm )
{

  int i;
  double ptdt = ZERO;

  for( i = 0; i < numeq; ++i )
  {
    dum4[i] = dum5[i] = pstate[i];
    yprime[i] = rk45[i] = error[i] = ZERO;
  }

  ptdt = pdt * 0.25;

  delta( pdm, dum4, f11 );

  step( numeq, yprime, f11, yprime, a1 );

  step( numeq, rk45, f11, rk45, b1 );

  step( numeq, dum4, f11, ydum, ptdt );

  delta( pdm, ydum, f2 );
  
  for( i = 0; i < numeq; ++i ) 
  {
    f13[i] = a31*f11[i] + a32*f2[i];
  }
  
  step( numeq, dum4, f13, ydum, pdt );

  delta( pdm, ydum, f3 );

  step( numeq, yprime, f3, yprime, a3 );

  step( numeq, rk45, f3, rk45, b3 );
  
  for( i = 0; i < numeq; ++i )
  {
    f14[i] = a41*f11[i] + a42*f2[i] + a43*f3[i];
  }
  
  step( numeq, dum4, f14, ydum, pdt );

  delta( pdm, ydum, f4 );

  step( numeq, yprime, f4, yprime, a4 );

  step( numeq, rk45, f4, rk45, b4 );
  
  for( i = 0; i < numeq; ++i )
  {
    f15[i] = a51*f11[i] + a52*f2[i] + a53*f3[i] + a54*f4[i];
  }
  
  step( numeq, dum4, f15, ydum, pdt );

  delta( pdm, ydum, f5 );

  step( numeq, yprime, f5, yprime, a5 );

  step( numeq, rk45, f5, rk45, b5 );
  
  for( i = 0; i < numeq; ++i )
  {
    f16[i] = b61*f11[i] + b62*f2[i] + b63*f3[i] + b64*f4[i] + b65*f5[i];
  }
  
  step( numeq, dum4, f16, ydum, pdt );

  delta( pdm, ydum, f6 );

  step( numeq, rk45, f6, rk45, b6 );

  step( numeq, dum4, yprime, dum4, pdt );

  step( numeq, dum5, rk45, dum5, pdt );
  
  for ( i = 0; i < numeq; ++i )
  {
    error[i] = fabs( dum4[i] - dum5[i] );
  }

};

/***************************************************************
 ***************************************************************/


/* *************************************************************
************************************************************** */

void TTEM60::setELMNTecd( const int& pdcmnt,
                          const double& psiplusc )
{
  // Initialize TEM parameters dependent upon a grid cell's
  //   soil texture

  veg.resetEcds( pdcmnt, psiplusc );
  
  microbe.resetEcds( pdcmnt, psiplusc );
  	 
  soil.resetEcds( pdcmnt );  
  
};

/* *************************************************************
************************************************************** */

/* *************************************************************
************************************************************** */

void TTEM60::setEquilC2N( const int& pdcmnt, const double& co2 )
{

  double yrpet = 1.0;
  double yreet = 1.0;

  // Determine vegetation C/N parameter as a function of
  //   vegetation type, annual PET, and annual EET (annual EET
  //   initially equal to yrpet)

  veg.updateC2N( pdcmnt,
                 yreet,
                 yrpet,
                 co2,
                 atms.getINITCO2() );

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TTEM60::setEquilEvap( const double& nirr,
                           const double& tair,
                           const int& pdm )
{

  // Determine initial values for atms.prvpetmx, atms.prveetmx,
  //   and veg.topt

  atms.petjh( nirr, tair, pdm );

  if( 0 == pdm )
  {
    atms.setPRVPETMX( atms.getPET() );
    soil.setPRVEETMX( atms.getPET() );
    veg.setTOPT( tair );
  }
  else
  {
    if( atms.getPET() > atms.getPRVPETMX() )
    {
      atms.setPRVPETMX( atms.getPET() );
      soil.setPRVEETMX( atms.getPET() );
      veg.setTOPT( tair );
    }
  }
  

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************* */

void TTEM60::setPrevState( void )
{
  for( int i = 0; i < MAXSTATE; ++i ) { prevy[i] = y[i]; }

};

/* *************************************************************
************************************************************* */


/***************************************************************
 ***************************************************************/

void TTEM60::step( const int& numeq, 
                   double pstate[], 
                   double pdstate[], 
                   double ptstate[],
	           double& pdt )
{

  for( int i = 0; i < numeq; ++i )
  {
    ptstate[i] = pstate[i] + (pdt * pdstate[i]);
  }

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

int TTEM60::stepmonth( const int& pdyr,
                       const int& pdm,
                       int& intflag,
                       const double& ptol,
                       ofstream& rflog1 )
{

  double clippingC;
  double clippingN;

  int mintflag;

  // Reset all monthly fluxes to zero
  
  resetMonthlyELMNTFluxes();


  // Reset ODE state variables representing monthly
  //   fluxes to zero
  
  resetODEflux();


  // If 12 months have passed since disturbance, reset
  //   all immediate fluxes associated with disturbance 
  //   (i.e., slash, convrtflx, nretent) to zero
  
  if( CYCLE == distmnthcnt )
  {
    distmnthcnt = 0;
    ag.resetMonthlyDisturbFluxes();
  } 

  // Count the number of months since disturbance
  
  if( distmnthcnt > 0 ) { ++distmnthcnt; }


  // If (FRI times 12 months have passed since a fire
  //   disturbance, reset ag.firendep to zero
  
  if( (ag.getFRI() * 12) == firemnthcnt )
  {
    firemnthcnt = 0;
    ag.setFIRENTOTDEP( ZERO );
    ag.setFIRENH4DEP( ZERO );
    ag.setFIRENO3DEP( ZERO );
  }

  // Count the number of months since a fire disturbance
  
  if( firemnthcnt > 0 ) { ++firemnthcnt; };
  
  if( (0 == ag.state || 6 == ag.state) && 2 == distmnthcnt )
  {
     // Establish natural vegetation the month
     //   following disturbance if cohort is not
     //   in agriculture

      prevy[I_VEGC] = y[I_VEGC] = ag.getNATSEEDC();
      prevy[I_STRN] = y[I_STRN] = ag.getNATSEEDSTRN();
      prevy[I_STON] = y[I_STON] = ag.getNATSEEDSTON();  
  }

  if( 0 == pdm )
  {
    if( 0 == pdyr )
    {
      microbe.setKD( microbe.getKDC() );
      ag.setKD( microbe.getKD() );
      ag.setNATSOIL( y[I_SOLC] );
    }
    else
    {
      if( (0 == ag.state || 6 == ag.state)
          && (0 == ag.prvstate || 6 == ag.prvstate) )
      {
        microbe.setKD( microbe.yrkd( nfeed,
                                     veg.getYRLTRFALC(),
                                     veg.getYRLTRFALN(),
                                     veg.getLCCLNC( veg.cmnt ) ) );
        ag.setKD( microbe.getKD() );
        ag.setNATSOIL( y[I_SOLC] );
      }
      else
      {
        if( y[I_SOLC] < ag.getNATSOIL() )
        {
          microbe.setKD( (ag.getKD() 
                         * y[I_SOLC] 
                         / ag.getNATSOIL()) );
        }
        else { microbe.setKD( ag.getKD() ); }
      }
    }


    // Reset annual fluxes to zero

    resetYrFluxes();
  }


  // Implement disturbance effects

  if( disturbflag > 0 && pdm == (disturbmonth-1) )
  {
    distmnthcnt = 1;

    // Save proportion of vegetation for "seed" for regrowth
    // after disturbance

    ag.setNATSEEDC( (y[I_VEGC] * ag.getVRESPAR()) );
    ag.setNATSEEDSTRN( (y[I_STRN] * ag.getVRESPAR()) );
    ag.setNATSEEDSTON( (y[I_STON] * ag.getVRESPAR()) );


    // Create potential 10-year and 100-year products 
    //   from human disturbance

    ag.createWoodProducts( pdyr,
                           y[I_VEGC],
                           y[I_STRN],
                           y[I_STON] );

      
    // Determine carbon and nitrogen lost during the first year
    //   after disturbance
      
    ag.conversion( veg.cmnt,
                   y[I_VEGC],
                   y[I_STRN],
                   y[I_STON],
                   y[I_SOLC],
                   y[I_SOLN] );

    prevy[I_VEGC] = y[I_VEGC] = ZERO;
    prevy[I_STRN] = y[I_STRN] = ZERO;
    prevy[I_STON] = y[I_STON] = ZERO;


    if( 3 == disturbflag )   // fire disturbance = 3
    {
       ag.setFIRENTOTDEP( ZERO );
       ag.setFIRENH4DEP( ZERO );
       ag.setFIRENO3DEP( ZERO );
       firemnthcnt = 1;
    }
      
	  
    if( 1 == disturbflag )
    {
      if( 1 == ag.state 
          || 2 == ag.state
          || 3 == ag.state
          || 4 == ag.state
          || 5 == ag.state )
      {
        // Update soil characteristics for rooting depth that
        //   is appropriate to disturbed community type

        soil.updateRootZ( ag.cmnt );


        // Update soil texture-dependent vegetation parameters
        //   for crops

        veg.resetEcds( ag.cmnt, soil.getPSIPLUSC() );

        // Update other adaptive parameters

        atms.setYRPET( 1.0 );
        soil.setYREET( 1.0 );
      
        veg.updateC2N( ag.cmnt,
                       soil.getYREET(),
                       atms.getYRPET(),
                       atms.getPREVCO2(),
                       atms.getINITCO2() );

        veg.setPRVLEAFMX( ag.getCROPPRVLEAFMX() );
     
        veg.setTOPT( ag.getCROPTOPT() );
      
        atms.setPRVPETMX( ag.getCROPPRVPETMX() );
      
        soil.setPRVEETMX( ag.getCROPPRVEETMX() );
      
        ag.setPRVCROPNPP( ZERO );
      }      
    }
  }


  // Revert to natural vegetation after cropland abandonment

  if( (0 == ag.state || 6 == ag.state) 
      && (ag.prvstate != 0 && ag.prvstate !=6) )
  {
    // Update soil characteristics to rooting depth that is 
    //   appropriate to natural vegetation

    soil.updateRootZ( veg.cmnt );


    // Establish natural vegetation

    prevy[I_VEGC] = y[I_VEGC] = ag.getNATSEEDC();
    prevy[I_STRN] = y[I_STRN] = ag.getNATSEEDSTRN();
    prevy[I_STON] = y[I_STON] = ag.getNATSEEDSTON();

    // Update soil texture-dependent vegetation parameters
    //   for natural vegetation

    veg.resetEcds( veg.cmnt, soil.getPSIPLUSC() );


    // Update other adaptive parameters

    atms.setYRPET( ag.getNATYRPET() );
    soil.setYREET( ag.getNATYREET() );

    veg.updateC2N( veg.cmnt,
                   soil.getYREET(),
                   atms.getYRPET(),
                   atms.getPREVCO2(),
                   atms.getINITCO2() );

    veg.setPRVLEAFMX( ag.getNATPRVLEAFMX() );
    veg.setTOPT( ag.getNATTOPT() );
    atms.setPRVPETMX( ag.getNATPRVPETMX() );
    soil.setPRVEETMX( ag.getNATPRVEETMX() );
    ag.setPRVCROPNPP( ZERO );
  }
  

  // set ozone efect from previous month for initial month

  if( 0 == pdyr && 0 == pdm ) { veg.setFPREVOZONE( 1.0 ); }


  // Get environmental conditions for month "dm"

  getenviron( pdyr, pdm, rflog1 );


  // Determine effect of air temperature on GPP (i.e. temp)
  //   and GPR (i.e. respq10)
  
  if( 0 == ag.state || 6 == ag.state )
  {
    veg.setTEMP( veg.cmnt, atms.getTAIR() );
    veg.setNewRESPQ10( veg.cmnt, atms.getTAIR() );
  }
  else
  {
	veg.setTEMP( ag.cmnt, atms.getTAIR() );
	veg.setNewRESPQ10( ag.cmnt, atms.getTAIR() );
  }

  // Determine effect of temperature on decomposition 
  //   (i.e. dq10)

  microbe.setNewDQ10( veg.cmnt,
    		      atms.getTAIR(),
		      soil.getTSOIL(),
		      soil.getSNOWPACK(),
                      soil.stmflg );

  // Update growing degree days

  if( atms.getTAIR() >= GDDMIN )
  {
    if( 1 == ag.state )
    {
      ag.setGROWDD( ag.getGROWDD() 
                    + ((atms.getTAIR() - GDDMIN) 
                    * atms.getNDAYS( pdm )) );
    }
    else
    {
      ag.setGROWDD( ZERO );
    }
  }
  else
  {
    // If "cold snap" (i.e. TAIR < GDDMIN) hits after crops 
    //   begin to grow, crops are assumed to die and resulting
    //   detritus is added to soil organic carbon and nitrogen
  	
    if( 1 == ag.state && ag.getGROWDD() > GDDSEED  )
    {       	
      ag.frostDamage( y[I_VEGC], y[I_STRN], y[I_STON] );
      y[I_VEGC] = ZERO;
      prevy[I_VEGC] = ZERO;
      y[I_STRN] = ZERO;
      prevy[I_STRN] = ZERO;
      y[I_STON] = ZERO;
      prevy[I_STON] = ZERO;
      y[I_SOLC] += ag.getSTUBBLEC();
      prevy[I_SOLC] = y[I_SOLC];
      y[I_SOLN] += ag.getSTUBBLEN();
      prevy[I_SOLN] = y[I_SOLN];
    }

    ag.setGROWDD( ZERO );
  }


  // Run TEM for a monthly time step

  mintflag = adapt( NUMEQ, y, ptol, pdm );


  if( 1 == dbug ) 
  { 
    cout << "Updated " << totyr << " " << (pdm+1) << " " << endl;
    cout << "GROSNMIN = " << microbe.getGROSSNMIN() << " " << y[I_GMIN] << endl;
  }

  if( 1 == mintflag ) { intflag = 1; }

  if ( blackhol != 0 )
  {
    if( 0 == initFlag ) { qualcon[0] = 10; }
    else { qualcon[pdyr] += 10; }
  }


  // Check mass balance

  massbal( y, prevy );

  if( 1 == dbug )
  {
    cout << "MassBal " << pdyr << " " << (pdm+1) << endl;
    cout << "GROSNMIN = " << microbe.getGROSSNMIN() << " " << y[I_GMIN] << endl;
    if( 11 == pdm) { exit( 0 ); }
  }

  // Determine veg.plant.nitrogen
  
  veg.setVEGN( (y[I_STRN] + y[I_STON]) );
  
  // Determine soil.availn.total
  
  soil.setAVLN( (y[I_NH4] + y[I_NO3]) );

  // Determine water yield (soil.h2oyld)

  soil.setH2OYLD( (y[I_RRUN] + y[I_SRUN]) );


  // Determine total monthly N inputs to ecosystem

  soil.setNINPUT( (ag.getFIRENTOTDEP() 
                   + atms.getTOTNDEP()
                   + y[I_AGFRTN] 
                   + y[I_BNFIX]) );


  // Determine monthly Soil Respiration (rsoil)

  rsoil = y[I_RH] + y[I_ROOTGPR];


  // Determine Net Ecosystem Production (nep)

  nep = y[I_NPP] - y[I_RH];


  // Determine fluxes from crop residues

  ag.updateCropResidueFluxes();


  // Determine fluxes from decay of products

  ag.decayProducts();


  // Reset growing degree days to zero if crops were
  // harvested this month

  if( 1 == ag.state && ag.getGROWDD() >= GDDHARVST )
  {
    ag.harvest( pdm, y[I_VEGC], y[I_STRN], y[I_STON] );
    y[I_VEGC] = ZERO;
    y[I_STRN] = ZERO;
    y[I_STON] = ZERO;
    y[I_SOLC] += ag.getSTUBBLEC();
    y[I_SOLN] += ag.getSTUBBLEN();

    ag.setGROWDD( ZERO );
  }
  else { ag.setNoCrops( pdm ); }


  // Determine crop residue
  
  ag.updateCropResidue();


  // Determine standing stock of products

  ag.updateProducts();

  ag.updateTotalProductFormation();

//  cout << nep << " " << endl;


  // Graze veg biomass every month if cohort is in pasture

  if( 2 == ag.state )
  {
   ag.grazing(  y[I_VEGC], y[I_STRN] );
    y[I_VEGC] -= ag.getFORAGEC();
    y[I_STRN] -= ag.getFORAGEN();
    y[I_SOLC] += ag.getMANUREC();
    y[I_SOLN] += ag.getMANUREN();
    y[I_NH4] += ag.getURINE();
  }
  else { ag.setNoGrazing(); }


  if( (3 == ag.state || 5 == ag.state)
      && LAWN == ag.cmnt )
  {
    // Mow lawn during growing season, assume 10% of vegetation 
    //   biomass are clipped each month 

    if( y[I_NPP] > ZERO )
    {
      clippingC = 0.1 * y[I_VEGC];
      clippingN = 0.1 * y[I_STRN];
      y[I_VEGC] -= clippingC;
      y[I_STRN] -= clippingN;
      y[I_SOLC] += clippingC;
      y[I_SOLN] += clippingN;
    }
  } 

  // Determine CFLUX from ecosystem from NEP plus
  //   fluxes from burning associated with agricultural
  //   conversion or

  ag.setCFLUX( (nep
                - ag.getCONVRTFLXC()
                - ag.getCROPRESIDUEFLXC()
                - ag.getANIMALRESP()) );

  // Determine Net Carbon Exchange (NCE) with atmosphere
  //   (CFLUX plus decay of agricultural and wood products)
  
  nce = ag.getCFLUX() - ag.getTOTPRODDECAYC();


  // Determine Net Ecosystem Carbon Balance (NECB)
  
  necb = nce - y[I_LCHDOC];


  // Determine carbon storage in ecosystem

  ag.setTOTEC( (y[I_VEGC]
             + y[I_SOLC]
             + soil.getNSOLC()
             + y[I_DOC]) );


  // Determine total carbon in ecosystems plus
  //   agricultural and wood products
                 
  totalc = ag.getTOTEC() + ag.getTOTPRODC(); 
 

  // Add nitrogen released from products back into nitrate pool

  y[I_NO3] +=  ag.getTOTPRODDECAYN();


  // Determine total loss of nitrogen from ecosystem
    
  soil.setNLOST( (y[I_NH3FLX]
                  + y[I_NOFLX]
                  + y[I_N2OFLX]
                  + y[I_N2FLX]
                  + y[I_LCHNO3]
                  + y[I_LCHDON]
                  + y[I_ERDPON]
                  + ag.getCONVRTFLXN()
                  + ag.getCROPRESIDUEFLXN()) );

  // Determine net ecosystem nitrogen balance (NENB) 
      
  nenb = soil.getNINPUT() - soil.getNLOST();


  // Update ANNUAL carbon, nitrogen and water pools and fluxes 
  //   from integrator results

  updateYearSummary();


  #ifdef CALIBRATE_TEM
    // Display monthly results to DOS screen
    pcdisplayMonth( pdyr, pdm );
  #endif


  if( 1 == ag.state && ag.getPRVCROPNPP() < y[I_NPP] )
  {
     ag.setPRVCROPNPP( y[I_NPP] );
  }
  else { ag.setPRVCROPNPP( ZERO ); }

  if( 1 == ag.state && ag.getPRVCROPNPP() > y[I_NPP] )
  {
    y[I_UNRMLF] = ZERO;
  }

  // Reset growing degree days to zero if crops were
  // harvested this month

  if( 1 == ag.state && ag.getGROWDD() >= GDDHARVST )
  {
    ag.setGROWDD( ZERO );
  }

  if( atms.getTAIR() < GDDMIN ) { ag.setGROWDD( ZERO ); }


  if( pdyr > 0 || pdm > 0 )
  {
    veg.setFPREVOZONE( (1.0 - 0.5 * (1.0 - y[I_FOZONE])) );
  }

  if( y[I_NPP] <= ZERO ) { veg.setFPREVOZONE( 1.0 ); }


  // Update atms.prevco2 for next month

  atms.setPREVCO2( atms.getCO2() );
  
  // Update atms.prevtair and atms.prev2tair for next month

  atms.setPREV2TAIR( atms.getPREVTAIR() );
  atms.setPREVTAIR( atms.getTAIR() );

  // Update previous snowpack and previous soil temperature
  // at 10 cm for next month

  soil.setPREVSPACK( soil.getSNOWPACK() );
  soil.setPREVDST10( soil.getDST10() );

  // Update previous unnormalized relative leaf area for
  //   next month
  
  veg.setPREVUNRMLEAF( y[I_UNRMLF] );
  
  // Update ag.prevPROD1, ag.prevPROD10 and ag.prevPROD100
  // for next month

  ag.setPREVPROD1C( ag.getPROD1C() );
  ag.setPREVPROD1N( ag.getPROD1N() );

  ag.setPREVPROD10C( ag.getPROD10C() );
  ag.setPREVPROD10N( ag.getPROD10N() );

  ag.setPREVPROD100C( ag.getPROD100C() );
  ag.setPREVPROD100N( ag.getPROD100N() );

  // Update ag.prevCropResidue for next month

  ag.setPREVCROPRESIDUEC( ag.getCROPRESIDUEC() );
  ag.setPREVCROPRESIDUEN( ag.getCROPRESIDUEN() );

  //  Update maximum EET, maximum PET, GPP optimum temperature
  //    (veg.topt), and maximum leaf cover (veg.prvleafmx) for
  //    the current year

  if( 0 == pdm )
  {
    soil.setEETMX( y[I_EET] );
    atms.setPETMX( atms.getPET() );
    veg.setNEWTOPT( atms.getTAIR() );
    veg.setNEWLEAFMX( y[I_UNRMLF] );
  }
  else
  {
    if( y[I_EET] > soil.getEETMX() )
    {
      soil.setEETMX( y[I_EET] );
    }

    if( atms.getPET() > atms.getPETMX() )
    {
      atms.setPETMX( atms.getPET() );
    }

    if( 0 == ag.state || 6 == ag.state )
    {
      veg.resetNEWTOPT( veg.cmnt, 
                        atms.getTAIR(), 
                        y[I_UNRMLF] );
    }
    else 
    {
      veg.resetNEWTOPT( ag.cmnt, 
                        atms.getTAIR(), 
                        y[I_UNRMLF] );
    }    
  }


  // Save state of all the ODE state variables 
  //   representing pools to allow checking
  //   of mass balance
  
  setPrevState();


  // Update annual parameters for next year
  
  if( (CYCLE-1) == pdm )
  {
    soil.setPRVEETMX( soil.getEETMX() );
    atms.setPRVPETMX( atms.getPETMX() );
    veg.setTOPT( veg.getNEWTOPT() );
    veg.setPRVLEAFMX( veg.getNEWLEAFMX() );

    // Update optimum temperature parameters for GPP

    if( 0 == ag.state || 6 == ag.state )
    {
      veg.boundTOPT( veg.cmnt );
      
    // Update adaptive parameters

      ag.setNATYRPET( atms.getYRPET() );
      ag.setNATYREET( soil.getYREET() );
      ag.setNATPRVPETMX( atms.getPRVPETMX() );
      ag.setNATPRVEETMX( soil.getPRVEETMX() );
      ag.setNATTOPT( veg.getTOPT() );
      ag.setNATPRVLEAFMX( veg.getPRVLEAFMX() );

      // Determine vegetation C/N parameter as a function
      // of vegetation type, annual PET, annual EET,
      // CO2 concentration

      veg.updateC2N( veg.cmnt,
                     soil.getYREET(),
                     atms.getYRPET(),
                     atms.getPREVCO2(),
                     atms.getINITCO2() );


    }
    else
    {
      veg.boundTOPT( ag.cmnt );

      ag.setCROPPRVPETMX( atms.getPRVPETMX() );
      ag.setCROPPRVEETMX( soil.getPRVEETMX() );
      ag.setCROPTOPT( veg.getTOPT() );
      ag.setCROPPRVLEAFMX( veg.getPRVLEAFMX() );

     // Determine vegetation C/N parameter as a function of
     //   vegetation type, annual PET, annual EET, CO2
     //   concentration

      veg.updateC2N( ag.cmnt,
                     soil.getYREET(),
                     atms.getYRPET(),
                     atms.getPREVCO2(),
                     atms.getINITCO2() );

    }

    // Update next year ag.prvstate with current year ag.state

    ag.prvstate = ag.state;

    veg.setYRVEGC( veg.getYRVEGC() / 12.0 );
    soil.setYRORGC( soil.getYRORGC() / 12.0 );
    soil.setYRNONORGC( soil.getYRNONORGC() / 12.0 );
    soil.setYRTOTORGC( soil.getYRTOTORGC() / 12.0 );
    soil.setYRDOC( soil.getYRDOC() / 12.0 );

    yrtotalc /= 12.0;

    veg.setYRVEGN( veg.getYRVEGN() / 12.0 );
    veg.setYRSTRUCTN( veg.getYRSTRUCTN() / 12.0 );

    if( veg.getYRSTRUCTN() != ZERO )
    {
      veg.setYRC2N( veg.getYRVEGC() / veg.getYRSTRUCTN() );
    }

    veg.setYRSTOREN( veg.getYRSTOREN() / 12.0 );

    soil.setYRORGN( soil.getYRORGN() / 12.0 );

    if( soil.getYRORGN() != ZERO )
    {
      soil.setYRC2N( soil.getYRORGC() / soil.getYRORGN() );
    }

    soil.setYRNONORGN( soil.getYRNONORGN() / 12.0 );
    soil.setYRTOTORGN( soil.getYRTOTORGN() / 12.0 );

    soil.setYRDON( soil.getYRDON() / 12.0 );

    soil.setYRAVLN( soil.getYRAVLN() / 12.0 );
    soil.setYRAVLNH4( soil.getYRAVLNH4() / 12.0 );
    soil.setYRAVLNO3( soil.getYRAVLNO3() / 12.0 );

    soil.setYRAVLH2O( soil.getYRAVLH2O() / 12.0 );
    soil.setYRSMOIST( soil.getYRSMOIST() / 12.0 );
    soil.setYRVSM( soil.getYRVSM() / 12.0 );
    soil.setYRPCTP( soil.getYRPCTP() / 12.0 );
    soil.setYRSNOWPACK( soil.getYRSNOWPACK() / 12.0 );
    soil.setYRRGRNDH2O( soil.getYRRGRNDH2O() / 12.0 );
    soil.setYRSGRNDH2O( soil.getYRSGRNDH2O() / 12.0 );

    veg.setYRUNLEAF( veg.getYRUNLEAF() / 12.0 );
    veg.setYRLEAF( veg.getYRLEAF() / 12.0 );
    veg.setYRLAI( veg.getYRLAI() / 12.0 );
    veg.setYRFPC( veg.getYRFPC() / 12.0 );

    soil.setYRTSOIL( soil.getYRTSOIL() / 12.0 );
    soil.stm.setYRDST0( soil.stm.getYRDST0() / 12.0 );
    soil.stm.setYRDST5( soil.stm.getYRDST5() / 12.0 );
    soil.setYRDST10( soil.getYRDST10() / 12.0 );
    soil.stm.setYRDST20( soil.stm.getYRDST20() / 12.0 );
    soil.stm.setYRDST50( soil.stm.getYRDST50() / 12.0 );
    soil.stm.setYRDST100( soil.stm.getYRDST100() / 12.0 );
    soil.stm.setYRDST200( soil.stm.getYRDST200() / 12.0 );
    soil.stm.setYRFRONTD( soil.stm.getYRFRONTD() / 12.0 );
    soil.stm.setYRFRONTD2( soil.stm.getYRFRONTD2() / 12.0 );
    soil.stm.setYRTHAWBEGIN1( soil.stm.getYRTHAWBEGIN1() / 12.0 );
    soil.stm.setYRTHAWBEGIN2( soil.stm.getYRTHAWBEGIN2() / 12.0 );
    soil.stm.setYRTHAWEND1( soil.stm.getYRTHAWEND1() / 12.0 );
    soil.stm.setYRTHAWEND2( soil.stm.getYRTHAWEND2() / 12.0 );
    veg.setYRTHAWPCT( veg.getYRTHAWPCT() / 12.0 );

      
    if( 0 == initFlag )
    {
      soil.setNSOLC( ((y[I_SOLC] 
                     / (1.0 - soil.getNSOLPAR( veg.cmnt )))
                     - y[I_SOLC]) );
      
      soil.setNSOLN( ((y[I_SOLN] 
                     / (1.0 - soil.getNSOLPAR( veg.cmnt )))
                     - y[I_SOLN]) );
    }

    soil.setTSOLC( (y[I_SOLC] + soil.getNSOLC() + y[I_DOC]) );

    soil.setTSOLN( (y[I_SOLN] + soil.getNSOLN() + y[I_DON]) );

                        
    if( endeq > 0 ) 
    { 
      ++endeq; 
    }
  }

  return endeq;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int TTEM60::testEquilibrium( void )
{

  if( 0 == nfeed && 0 == rheqflag
      && wtol >= fabs( atms.getYRRAIN() + atms.getYRSNOWFALL()
      - soil.getYREET() - soil.getYRRRUN() - soil.getYRSRUN() )
      && (ctol >= fabs( veg.getYRNPP() - veg.getYRLTRFALC() )) )
  {
    return 1;
  }

  if( 0 == nfeed && 1 == rheqflag
      && wtol >= fabs( atms.getYRRAIN() 
                       + atms.getYRSNOWFALL()
                       - soil.getYREET() 
                       - soil.getYRRRUN() 
                       - soil.getYRSRUN() )
                        
      && (ctol >= fabs( yrnecb ))
      && (ctol >= fabs( veg.getYRNPP() - veg.getYRLTRFALC() ))
      && (ctol >= fabs( veg.getYRLTRFALC() - microbe.getYRDECOMP() )) 
       
      && (ctol >= fabs( microbe.getYRDECOMP() 
                        - microbe.getYRRH() 
                        - microbe.getYRDOCPRD() )) )
  {
    return 1;
  }

  if( 1 == nfeed && 1 == rheqflag
      && wtol >= fabs( atms.getYRRAIN() 
                       + atms.getYRSNOWFALL()
                       - soil.getYREET() 
                       - soil.getYRRRUN() 
                       - soil.getYRSRUN() )
              
      && (ntol >= fabs( yrnenb - soil.getYRABNIMMOB() ))

      && (ntol >= fabs( veg.getYRNUP() 
                        + veg.getYRNFIX() 
                        - veg.getYRLTRFALN() ))
                         
      && (ntol >= fabs( veg.getYRLTRFALN() 
                        + microbe.getYRNFIX() 
                        - microbe.getYRNDECOMP() ))
                         
      && (ntol >= fabs( microbe.getYRNDECOMP() 
                        - microbe.getYRNMIN() 
                        - microbe.getYRDONPRD() ))
        
      && (ntol >= fabs( atms.getYRNH4DEP() 
                        + microbe.getYRNMIN() 
                        - soil.getYRABNIMMOB() 
                        - veg.getYRNH4UP()
                        - microbe.getYRNITRIF() 
                        - microbe.getYRAMMNVOL() ))
                          
      && (ntol >= fabs( microbe.getYRNITRIF() 
                        - microbe.getYRNO3PRD() 
                        - microbe.getYRNOPRD() ))
                           
      && (ntol >= fabs( microbe.getYRNO3PRD() 
                        + atms.getYRNO3DEP() 
                        - veg.getYRNO3UP() 
                        - soil.getYRLCHNO3()
                        - microbe.getYRDENITRF() ))
                         
      && (ntol >= fabs( microbe.getYRDENITRF() 
                        - microbe.getYRN2OPRD() 
                        - microbe.getYRN2PRD() ))
                         
      && (ntol >= fabs( microbe.getYRDONPRD() 
                        - soil.getYRLCHDON() ))

      && (ntol >= fabs( microbe.getYRAMMNVOL() - soil.getYRNH3FLX() ))
      && (ntol >= fabs( microbe.getYRNOPRD() - soil.getYRNOFLX() ))
      && (ntol >= fabs( microbe.getYRN2OPRD() - soil.getYRN2OFLX() ))
      && (ntol >= fabs( microbe.getYRN2PRD() - soil.getYRN2FLX() ))

      && (ctol >= fabs( yrnecb ))
      && (ctol >= fabs( veg.getYRNPP() - veg.getYRLTRFALC() ))
      && (ctol >= fabs( veg.getYRLTRFALC() - microbe.getYRDECOMP() )) 
       
      && (ctol >= fabs( microbe.getYRDECOMP() 
                        - microbe.getYRRH() 
                        - microbe.getYRDOCPRD() )) )
  {
    return 1;
  }

  return 0;

};

/* *************************************************************
************************************************************** */


/* *************************************************************
************************************************************** */

void TTEM60::updateYearSummary( void )
{

  // Update sum of annual carbon storage in ecosystems

  veg.updateYRVEGC( y[I_VEGC] );
  soil.updateYRORGC( y[I_SOLC] );
  soil.updateYRDOC( y[I_DOC] );

  soil.updateYRNONORGC( soil.getNSOLC() );
  soil.updateYRTOTORGC( soil.getTSOLC() );
  updateYRTOTALC( totalc );

  // Update sum of annual nitrogen storage in ecosystems

  veg.updateYRSTRUCTN( y[I_STRN] );
  veg.updateYRSTOREN( y[I_STON] );
  soil.updateYRORGN( y[I_SOLN] );
  soil.updateYRDON( y[I_DON] );
  soil.updateYRAVLNH4( y[I_NH4] );
  soil.updateYRAVLNO3( y[I_NO3] );

  veg.updateYRVEGN( veg.getVEGN() );
  soil.updateYRNONORGN( soil.getNSOLN() );
  soil.updateYRTOTORGN( soil.getTSOLN() );
  soil.updateYRAVLN( soil.getAVLN() );

  // Update sum of annual water storage in ecosystems

  if( soil.getROOTZ() < MINACTLAYERZ )
  {
    soil.updateYRAVLH2O( ZERO );
    soil.updateYRSMOIST( ZERO );
    soil.updateYRVSM( ZERO );
    soil.updateYRPCTP( ZERO );
  }
  else
  {
    soil.updateYRAVLH2O( (y[I_SM] * soil.getACTLAYER() 
                          / soil.getROOTZ())
                         - soil.getWILTPT() );
                   
    soil.updateYRSMOIST( y[I_SM] );
  
    soil.updateYRVSM( y[I_SM] / (soil.getROOTZ() * 1000.0) );
  
    soil.updateYRPCTP( 100.0 * (y[I_SM] * soil.getACTLAYER() 
                        / soil.getROOTZ())
                        / soil.getTOTPOR() );
  }

  soil.updateYRSNOWPACK( soil.getSNOWPACK() );
  soil.updateYRRGRNDH2O( y[I_RGRW] );
  soil.updateYRSGRNDH2O( y[I_SGRW] );

  // Update sum of annual phenology in natural ecosystems

  veg.updateYRUNLEAF( y[I_UNRMLF] );
  veg.updateYRLEAF( y[I_LEAF] );
  veg.updateYRLAI( y[I_LAI] );
  veg.updateYRFPC( y[I_FPC] );

  // Update sum of annual carbon fluxes in ecosystems

  veg.updateYRINGPP( y[I_INGPP] );
  veg.updateYRGPP( y[I_GPP] );
  veg.updateYRINNPP( y[I_INNPP] );
  veg.updateYRNPP( y[I_NPP] );
  veg.updateYRGPR( y[I_GPR] );
  veg.updateYRRMAINT( y[I_RVMNT] );
  veg.updateYRRGROWTH( y[I_RVGRW] );
  veg.updateYRABVGRNDRESP( y[I_ABVGPR] );
  veg.updateYRROOTRESP( y[I_ROOTGPR] );

  veg.updateYRLTRFALC( y[I_LTRFALC] );
  microbe.updateYRDECOMP( y[I_CDCMP] );
  microbe.updateYRRH( y[I_RH] );

  microbe.updateYRDOCPRD( y[I_DOCP] );
  soil.updateYRLCHDOC( y[I_LCHDOC] );
  soil.updateYRERODEPOC( y[I_ERDPOC] );

  updateYRRSOIL( rsoil );
  updateYRNEP( nep );
  updateYRNCE( nce );
  updateYRNECB( necb );


 // Update sum of annual nitrogen fluxes in ecosystems

  ag.updateYRFERTN( y[I_AGFRTN] );

  updateYRBNFIX( y[I_BNFIX] );
  veg.updateYRNFIX( y[I_SNFIX] );
  microbe.updateYRNFIX( y[I_ANFIX] );

  veg.updateYRINNUP( y[I_INNUP] );
  veg.updateYRINNH4UP( y[I_INNH4UP] );
  veg.updateYRINNO3UP( y[I_INNO3UP] );

  veg.updateYRNUP( y[I_VNUP] );
  veg.updateYRNH4UP( y[I_VNH4UP] );
  veg.updateYRNO3UP( y[I_VNO3UP] );

  veg.updateYRSUP( y[I_VSUP] );
  veg.updateYRLUP( y[I_VLUP] );
  veg.updateYRNMOBIL( y[I_VNMBL] );
  veg.updateYRNRSORB( y[I_VNRSRB] );

  veg.updateYRLTRFALN( y[I_LTRFALN] );

  microbe.updateYRNDECOMP( y[I_NDCMP] );
  microbe.updateYRDONPRD( y[I_DONP] );

  microbe.updateYRGMIN( y[I_GMIN] );
  microbe.updateYRIMMNH4( y[I_NH4IMM] );
  microbe.updateYRIMMB( y[I_NIMM] );
  microbe.updateYRNMIN( y[I_NMIN] );

  soil.updateYRABNIMMOB( y[I_AIMMNH4] );

  microbe.updateYRAMMNVOL( y[I_AMMN] );

  microbe.updateYRNITRIF( y[I_NTRF] );
  microbe.updateYRNO3PRD( y[I_NO3P] );
  microbe.updateYRNOPRD( y[I_NOP] );
  microbe.updateYRN2OPRD( y[I_N2OP] );
  microbe.updateYRN2PRD( y[I_N2P] );
  microbe.updateYRDENITRF( y[I_DNTRF] );

  soil.updateYRNH3FLX( y[I_NH3FLX] );
  soil.updateYRNOFLX( y[I_NOFLX] );
  soil.updateYRN2OFLX( y[I_N2OFLX] );
  soil.updateYRN2FLX( y[I_N2FLX] );

  soil.updateYRLCHNO3( y[I_LCHNO3] );
  soil.updateYRLCHDON( y[I_LCHDON] );
  soil.updateYRERODEPON( y[I_ERDPON] );

  atms.updateYRTOTNDEP( atms.getTOTNDEP() );
  atms.updateYRNH4DEP( atms.getNH4DEP() );
  atms.updateYRNO3DEP( atms.getNO3DEP() );

  soil.updateYRNINPUT( soil.getNINPUT() );
  soil.updateYRNLOST( soil.getNLOST() );
  updateYRNENB( nenb );


   // Update sum of annual water fluxes in ecosystems

  ag.updateYRIRRIG( y[I_AGIRRIG] );
  soil.updateYRINEET( y[I_INEET] );
  soil.updateYREET( y[I_EET] );
  soil.updateYRRPERC( y[I_RPERC] );
  soil.updateYRSPERC( y[I_SPERC] );
  soil.updateYRRRUN( y[I_RRUN] );
  soil.updateYRSRUN( y[I_SRUN] );

  atms.updateYRRAIN( atms.getRAIN() );
  atms.updateYRSNOWFALL( atms.getSNOWFALL() );
  atms.updateYRPET( atms.getPET() );
  soil.updateYRSNOWINF( soil.getSNOWINF() );
  soil.updateYRH2OYIELD( soil.getH2OYLD() );


  ag.updateYRSTUBC( ag.getSTUBBLEC() );
  ag.updateYRSTUBN( ag.getSTUBBLEN() );

 // Update sum of annual carbon and nitrogen fluxes from
 //   agricultural conversion

  ag.updateYRCONVRTC( ag.getCONVRTFLXC() );
  ag.updateYRVCONVRTC( ag.getVCONVRTFLXC() );
  ag.updateYRSCONVRTC( ag.getSCONVRTFLXC() );
  ag.updateYRSLASHC( ag.getSLASHC() );
  ag.updateYRCFLUX( ag.getCFLUX() );
  
  ag.updateYRCONVRTN( ag.getCONVRTFLXN() );
  ag.updateYRVCONVRTN( ag.getVCONVRTFLXN() );
  ag.updateYRSCONVRTN( ag.getSCONVRTFLXN() );
  ag.updateYRSLASHN( ag.getSLASHN() );

  ag.updateYRNRENT( ag.getNRETENT() );
  ag.updateYRNVRENT( ag.getNVRETENT() );
  ag.updateYRNSRENT( ag.getNSRETENT() );
  
 // Update sum of annual carbon and nitrogen fluxes from
 //   products

  ag.updateYRFORMPROD1C( ag.getCROPPRODC() );
  ag.updateYRFORMPROD1N( ag.getCROPPRODN() );

  ag.updateYRFORMRESIDUEC( ag.getFORMCROPRESIDUEC() );
  ag.updateYRFORMRESIDUEN( ag.getFORMCROPRESIDUEN() );

  ag.updateYRDECAYPROD1C( ag.getPROD1DECAYC() );
  ag.updateYRDECAYPROD1N( ag.getPROD1DECAYN() );

  ag.updateYRFLUXRESIDUEC( ag.getCROPRESIDUEFLXC() );
  ag.updateYRFLUXRESIDUEN( ag.getCROPRESIDUEFLXN() );

  ag.updateYRFORMPROD10C( ag.getFORMPROD10C() );
  ag.updateYRFORMPROD10N( ag.getFORMPROD10N() );

  ag.updateYRDECAYPROD10C( ag.getPROD10DECAYC() );
  ag.updateYRDECAYPROD10N( ag.getPROD10DECAYN() );

  ag.updateYRFORMPROD100C( ag.getFORMPROD100C() );
  ag.updateYRFORMPROD100N( ag.getFORMPROD100N() );

  ag.updateYRDECAYPROD100C( ag.getPROD100DECAYC() );
  ag.updateYRDECAYPROD100N( ag.getPROD100DECAYN() );

  ag.updateYRFORMTOTPRODC( ag.getFORMTOTPRODC() );
  ag.updateYRFORMTOTPRODN( ag.getFORMTOTPRODN() );

  ag.updateYRDECAYTOTPRODC( ag.getTOTPRODDECAYC() );
  ag.updateYRDECAYTOTPRODN( ag.getTOTPRODDECAYN() );

  // Update sum of soil thermal dynamic variables

  soil.updateYRTSOIL( soil.getTSOIL() );
  soil.stm.updateYRDST0( soil.stm.getDST0() );
  soil.stm.updateYRDST5( soil.stm.getDST5() );
  soil.updateYRDST10( soil.getDST10() );
  soil.stm.updateYRDST20( soil.stm.getDST20() );
  soil.stm.updateYRDST50( soil.stm.getDST50() );
  soil.stm.updateYRDST100( soil.stm.getDST100() );
  soil.stm.updateYRDST200( soil.stm.getDST200() );
  soil.stm.updateYRFRONTD( soil.stm.getFRONTD() );
  soil.stm.updateYRFRONTD2( soil.stm.getFRONTD2() );
  soil.stm.updateYRTHAWBEGIN1( soil.stm.getTHAWBEGIN1() );
  soil.stm.updateYRTHAWBEGIN2( soil.stm.getTHAWBEGIN2() );
  soil.stm.updateYRTHAWEND1( soil.stm.getTHAWEND1() );
  soil.stm.updateYRTHAWEND2( soil.stm.getTHAWEND2() );
  veg.updateYRTHAWPCT( veg.getTHAWPCT() );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void TTEM60::writesitecd( ofstream& fout, const int& pcmnt )
{
  int dlayer;

  fout << "<?xml version = \"1.0\"?>" << endl << endl;

  fout << "<community type = \"" << pcmnt << "\"" << endl;
  fout << "  description = \"" << description << "\">" << endl;
  fout << "  site = \"" << sitename << "\"" << endl;
  fout << "  longitude = \"" << sitecol << "\"" << endl;
  fout << "  latitude = \"" << siterow << "\"" << endl;
  fout << "  developedBy = \"" << developer << "\"" << endl;
  fout << "  version = \"" << version << "\"" << endl;
  fout << "  updated = \"" << updated << "\">" << endl;
  fout << endl;

  fout << "  <siteECD>" << endl;
  fout << "    <vegca>" << vegca[pcmnt] << "</vegca>" << endl;
  fout << "    <vegcb>" << vegcb[pcmnt] << "</vegcb>" << endl;
  fout << "    <strna>" << strna[pcmnt] << "</strna>" << endl;
  fout << "    <strnb>" << strnb[pcmnt] << "</strnb>" << endl;
  fout << "    <stona>" << stona[pcmnt] << "</stona>" << endl;
  fout << "    <stonb>" << stonb[pcmnt] << "</stonb>" << endl;
  fout << "    <solca>" << solca[pcmnt] << "</solca>" << endl;
  fout << "    <solcb>" << solcb[pcmnt] << "</solcb>" << endl;
  fout << "    <solna>" << solna[pcmnt] << "</solna>" << endl;
  fout << "    <solnb>" << solnb[pcmnt] << "</solnb>" << endl;
  fout << "    <doccut>" << doccut[pcmnt] << "</doccut>" << endl;
  fout << "    <doc1a>" << doc1a[pcmnt] << "</doc1a>" << endl;
  fout << "    <doc1b>" << doc1b[pcmnt] << "</doc1b>" << endl;
  fout << "    <doc2a>" << doc2a[pcmnt] << "</doc2a>" << endl;
  fout << "    <doc2b>" << doc2b[pcmnt] << "</doc2b>" << endl;
  fout << "    <doncut>" << doncut[pcmnt] << "</doncut>" << endl;
  fout << "    <don1a>" << don1a[pcmnt] << "</don1a>" << endl;
  fout << "    <don1b>" << don1b[pcmnt] << "</don1b>" << endl;
  fout << "    <don2a>" << don2a[pcmnt] << "</don2a>" << endl;
  fout << "    <don2b>" << don2b[pcmnt] << "</don2b>" << endl;
  fout << "    <nh4a>" << nh4a[pcmnt] << "</nh4a>" << endl;
  fout << "    <nh4b>" << nh4b[pcmnt] << "</nh4b>" << endl;
  fout << "    <no3cut>" << no3cut[pcmnt] << "</no3cut>" << endl;
  fout << "    <no31a>" << no31a[pcmnt] << "</no31a>" << endl;
  fout << "    <no31b>" << no31b[pcmnt] << "</no31b>" << endl;
  fout << "    <no32a>" << no32a[pcmnt] << "</no32a>" << endl;
  fout << "    <no32b>" << no32b[pcmnt] << "</no32b>" << endl;
  fout << endl;
  fout << "    <unleaf12>" << veg.getUNLEAF12( pcmnt );
  fout << "</unleaf12>" << endl;
  fout << "    <initleafmx>" << veg.getINITLEAFMX( pcmnt );
  fout << "</initleafmx>" << endl;
  fout << endl;
  fout << "    <vegcmaxcut>" << veg.getCMAXCUT( pcmnt );
  fout << "</vegcmaxcut>" << endl;
  fout << "    <vegcmax1a>" << veg.getCMAX1A( pcmnt );
  fout << "</vegcmax1a>" << endl;
  fout << "    <vegcmax1b>" << veg.getCMAX1B( pcmnt );
  fout << "</vegcmax1b>" << endl;
  fout << "    <vegcmax2a>" << veg.getCMAX2A( pcmnt );
  fout << "</vegcmax2a>" << endl;
  fout << "    <vegcmax2b>" << veg.getCMAX2B( pcmnt );
  fout << "</vegcmax2b>" << endl;
  fout << "    <vegcfall>" << veg.getCFALL( pcmnt );
  fout << "</vegcfall>" << endl;
  fout << "    <vegrmmax>" << veg.getRMMAX( pcmnt );
  fout << "</vegrmmax>" << endl;
  fout << "    <vegrroot>" << veg.getRROOT( pcmnt );
  fout << "</vegrroot>" << endl;
  fout << "    <microbekdcut>" << microbe.getKDCUT( pcmnt );
  fout << "</microbekdcut>" << endl;
  fout << "    <microbekd1a>" << microbe.getKD1A( pcmnt );
  fout << "</microbekd1a>" << endl;
  fout << "    <microbekd1b>" << microbe.getKD1B( pcmnt );
  fout << "</microbekd1b>" << endl;
  fout << "    <microbekd2a>" << microbe.getKD2A( pcmnt );
  fout << "</microbek2da>" << endl;
  fout << "    <microbekd2b>" << microbe.getKD2B( pcmnt );
  fout << "</microbekd2b>" << endl;
  fout << "    <microbepropftos>" << microbe.getPROPFTOS( pcmnt );
  fout << "</microbepropftos>" << endl;
  fout << "    <soilnonOMpar>" << soil.getNSOLPAR( pcmnt );
  fout << "</soilnonOMpar>" << endl;
  fout << "    <microbeDOCpar>" << microbe.getDOCPAR( pcmnt );
  fout << "</microbeDOCpar>" << endl;
  fout << "    <soillchDOMpar>" << soil.getLCHDOMPAR( pcmnt );
  fout << "  </soillchDOMpar>" << endl;  
  fout << endl;
  fout << "    <vegnfixpara>" << veg.getNFIXPARA( pcmnt );
  fout << "</vegnfixpara>" << endl;
  fout << "    <vegnfixparb>" << veg.getNFIXPARB( pcmnt );
  fout << "</vegnfixparb>" << endl;
  fout << "    <vegnfixadj>" << veg.getNFIXADJUST( pcmnt );
  fout << "</vegnfixadj>" << endl;
  fout << "    <vegnupnh4cut>" << veg.getNUPNH4CUT( pcmnt );
  fout << "</vegnupnh4cut>" << endl;
  fout << "    <vegnupnh41a>" << veg.getNUPNH41A( pcmnt );
  fout << "</vegnupnh41a>" << endl;
  fout << "    <vegnupnh41b>" << veg.getNUPNH41B( pcmnt );
  fout << "</vegnupnh41b>" << endl;
  fout << "    <vegnupnh42a>" << veg.getNUPNH42A( pcmnt );
  fout << "</vegnupnh42a>" << endl;
  fout << "    <vegnupnh42b>" << veg.getNUPNH42B( pcmnt );
  fout << "</vegnupnh42b>" << endl;
  fout << "    <vegnupno3cut>" << veg.getNUPNO3CUT( pcmnt );
  fout << "</vegnupno3cut>" << endl;
  fout << "    <vegnupno31a>" << veg.getNUPNO31A( pcmnt );
  fout << "</vegnupno31a>" << endl;
  fout << "    <vegnupno31b>" << veg.getNUPNO31B( pcmnt );
  fout << "</vegnupno31b>" << endl;
  fout << "    <vegnupno32a>" << veg.getNUPNO32A( pcmnt );
  fout << "</vegnupno32a>" << endl;
  fout << "    <vegnupno32b>" << veg.getNUPNO32B( pcmnt );
  fout << "</vegnupno32b>" << endl;
  fout << "    <vegnfall>" << veg.getNFALL( pcmnt );
  fout << "</vegnfall>" << endl;
  fout << "    <veglcclnc>" << veg.getLCCLNC( pcmnt );
  fout << "</veglcclnc>" << endl;
  fout << "    <microbenfixpar>" << microbe.getNFIXPAR( pcmnt );
  fout << "</microbenfixpar>" << endl;
  fout << "    <microbenh4immcut>" << microbe.getNH4IMMCUT( pcmnt );
  fout << "</microbenh4immcut>" << endl;
  fout << "    <microbenh4imm1a>" << microbe.getNH4IMM1A( pcmnt );
  fout << "</microbenh4imm1a>" << endl;
  fout << "    <microbenh4imm1b>" << microbe.getNH4IMM1B( pcmnt );
  fout << "</microbenh4imm1b>" << endl;
  fout << "    <microbenh4imm2a>" << microbe.getNH4IMM2A( pcmnt );
  fout << "</microbenh4imm2a>" << endl;
  fout << "    <microbenh4imm2b>" << microbe.getNH4IMM2B( pcmnt );
  fout << "</microbenh4imm2b>" << endl;
  fout << "    <microbeammnpar>" << microbe.getAMMNPAR( pcmnt );
  fout << "</microbeammnpar>" << endl;
  fout << "    <microbentrfparcut>" << microbe.getNTRFPARCUT( pcmnt );
  fout << "</microbentrfparcut>" << endl;
  fout << "    <microbentrfpar1a>" << microbe.getNTRFPAR1A( pcmnt );
  fout << "</microbentrfpar1a>" << endl;
  fout << "    <microbentrfpar1b>" << microbe.getNTRFPAR1B( pcmnt );
  fout << "</microbentrfpar1b>" << endl;
  fout << "    <microbentrfpar2a>" << microbe.getNTRFPAR2A( pcmnt );
  fout << "</microbentrfpar2a>" << endl;
  fout << "    <microbentrfpar2b>" << microbe.getNTRFPAR2B( pcmnt );
  fout << "</microbentrfpar2b>" << endl;
  fout << "    <microbeinitntrf>" << microbe.getINITNTRF( pcmnt );
  fout << "</microbeinitntrf>" << endl;
  fout << "    <microbeallntrf>" << microbe.getALLNTRF( pcmnt );
  fout << "</microbeallntrf>" << endl;
  fout << "    <soillchNO3parcut>" << soil.getLCHNO3PARCUT( pcmnt );
  fout << "</soillchNO3parcut>" << endl;
  fout << "    <soillchNO3par1a>" << soil.getLCHNO3PAR1A( pcmnt );
  fout << "</soillchNO3par1a>" << endl;
  fout << "    <soillchNO3par1b>" << soil.getLCHNO3PAR1B( pcmnt );
  fout << "</soillchNO3par1b>" << endl;
  fout << "    <soillchNO3par2a>" << soil.getLCHNO3PAR2A( pcmnt );
  fout << "</soillchNO3par2a>" << endl;
  fout << "    <soillchNO3par2b>" << soil.getLCHNO3PAR2B( pcmnt );
  fout << "</soillchNO3par2b>" << endl;
  fout << "    <microbeDONparcut>" << microbe.getDONPARCUT( pcmnt );
  fout << "</microbeDONparcut>" << endl;
  fout << "    <microbeDONpar1a>" << microbe.getDONPAR1A( pcmnt );
  fout << "</microbeDONpar1a>" << endl;
  fout << "    <microbeDONpar1b>" << microbe.getDONPAR1B( pcmnt );
  fout << "</microbeDONpar1b>" << endl;
  fout << "    <microbeDONpar2a>" << microbe.getDONPAR2A( pcmnt );
  fout << "</microbeDONpar2a>" << endl;
  fout << "    <microbeDONpar2b>" << microbe.getDONPAR2B( pcmnt );
  fout << "</microbeDONpar2b>" << endl;
  fout << "    <veginitcneven>" << veg.getINITCNEVEN( pcmnt );
  fout << "</veginitcneven>" << endl;
  fout << "    <vegcnmin>" << veg.getCNMIN( pcmnt );
  fout << "</vegcnmin>" << endl;
  fout << "    <vegc2na>" << veg.getC2NA( pcmnt );
  fout << "</vegc2na>" << endl;
  fout << "    <vegc2nb>" << veg.getC2NB( pcmnt );
  fout << "</vegc2nb>" << endl;
  fout << "    <vegc2nmin>" << veg.getC2NMIN( pcmnt );
  fout << "</vegc2nmin>" << endl;
  fout << "    <microbecnsoil>" << microbe.getCNSOIL( pcmnt );
  fout << "</microbecnsoil>" << endl;
  fout << endl;
  fout << "    <o3para>" << veg.getO3PARA( pcmnt );
  fout << "</o3para>" << endl;
  fout << "    <o3parb>" << veg.getO3PARB( pcmnt );
  fout << "</o3parb>" << endl;
  fout << "    <o3parc>" << veg.getO3PARC( pcmnt );
  fout << "</o3parc>" << endl;
  fout << "  </siteECD>" << endl;
  fout << endl;

  fout << "  <vegECD>" << endl; 
  fout << "    <kc>" << veg.getKC( pcmnt );
  fout << "</kc>" << endl;
  fout << "    <ki>" << veg.getKI( pcmnt );
  fout << "</ki>" << endl;
  fout << "    <gva>" << veg.getGVA( pcmnt );
  fout << "</gva>" << endl;
  fout << "    <tmin>" << veg.getTMIN( pcmnt );
  fout << "</tmin>" << endl;
  fout << "    <toptmin>" << veg.getTOPTMIN( pcmnt );
  fout << "</toptmin>" << endl;
  fout << "    <toptmax>" << veg.getTOPTMAX( pcmnt );
  fout << "</toptmax>" << endl;
  fout << "    <tmax>" << veg.getTMAX( pcmnt );
  fout << "</tmax>" << endl;
  fout << "    <tref>" << veg.getTREF( pcmnt );
  fout << "</tref>" << endl;
  fout << "    <qref>" << veg.getQREF( pcmnt );
  fout << "</qref>" << endl;
  fout << "    <alpha>" << veg.getALPHA( pcmnt );
  fout << "</alpha>" << endl;
  fout << "    <beta>" << veg.getBETA( pcmnt );
  fout << "</beta>" << endl;
  fout << "    <gamma>" << veg.getGAMMA( pcmnt );
  fout << "</gamma>" << endl;
  fout << "    <kvnh4>" << veg.getKVNH4( pcmnt );
  fout << "</kvnh4>" << endl;
  fout << "    <kvno3>" << veg.getKVNO3( pcmnt );
  fout << "</kvno3>" << endl;
  fout << "    <labncon>" << veg.getLABNCON( pcmnt );
  fout << "</labncon>" << endl;
  fout << "    <leafmxc>" << veg.getLEAFMXC( pcmnt );
  fout << "</leafmxc>" << endl;
  fout << "    <kleafc>" << veg.getKLEAFC( pcmnt );
  fout << "</kleafc>" << endl;
  fout << "    <sla>" << veg.getSLA( pcmnt );
  fout << "</sla>" << endl;
  fout << "    <cov>" << veg.getCOV( pcmnt );
  fout << "</cov>" << endl;
  fout << "    <fpcmax>" << veg.getFPCMAX( pcmnt );
  fout << "</fpcmax>" << endl;
  fout << "    <proptrans>" << veg.getPROPTRANS( pcmnt );
  fout << "</proptrans>" << endl;
  fout << "  </vegECD>" << endl;
  fout << endl;

  fout << "  <leafECD>" << endl;
  fout << "    <minleaf>" << veg.getMINLEAF( pcmnt );
  fout << "</minleaf>" << endl;
  fout << "    <aleaf>" << veg.getALEAF( pcmnt );
  fout << "</aleaf>" << endl;
  fout << "    <bleaf>" << veg.getBLEAF( pcmnt );
  fout << "</bleaf>" << endl;
  fout << "    <cleaf>" << veg.getCLEAF( pcmnt );
  fout << "</cleaf>" << endl;
  fout << "  </leafECD>" << endl;
  fout << endl;

  fout << "  <microbeECD>" << endl;
  fout << "    <tref>" << microbe.getTREF( pcmnt );
  fout << "</tref>" << endl;
  fout << "    <qref>" << microbe.getQREF( pcmnt );
  fout << "</qref>" << endl;
  fout << "    <alpha>" << microbe.getALPHA( pcmnt );
  fout << "</alpha>" << endl;
  fout << "    <beta>" << microbe.getBETA( pcmnt );
  fout << "</beta>" << endl;
  fout << "    <gamma>" << microbe.getGAMMA( pcmnt );
  fout << "</gamma>" << endl;
  fout << "    <kn2>" << microbe.getKN2( pcmnt );
  fout << "</kn2>" << endl;
  fout << "    <moistmin>" << microbe.getMOISTMIN( pcmnt );
  fout << "</moistmin>" << endl;
  fout << "    <moistopt>" << microbe.getMOISTOPT( pcmnt );
  fout << "</moistopt>" << endl;
  fout << "    <moistmax>" << microbe.getMOISTMAX( pcmnt );
  fout << "</moistmax>" << endl;
  fout << "  </microbeECD>" << endl;
  fout << endl;

  fout << "  <rootzECD>" << endl;
  fout << "    <rootza>" << soil.getROOTZA( pcmnt );
  fout << "</rootza>" << endl;
  fout << "    <rootzb>" << soil.getROOTZB( pcmnt );
  fout << "</rootzb>" << endl;
  fout << "    <rootzc>" << soil.getROOTZC( pcmnt );
  fout << "</rootzc>" << endl;
  fout << "    <minrootz>" << soil.getMINROOTZ( pcmnt );
  fout << "</minrootz>" << endl;
  fout << "  </rootzECD>" << endl;
  fout << endl;

  fout << "  <snowPackECD>" << endl;
  fout << "    <vegWindSp>" << soil.stm.getVEGWINDSP( pcmnt );
  fout << "</vegWindSp>" << endl;
  fout << "    <gflux>" << soil.stm.getGFLUX( pcmnt );
  fout << "</gflux>" << endl;
  fout << "    <cdsnow>" << soil.stm.getCDSNOW( pcmnt );
  fout << "</cdsnow>" << endl;
  fout << "    <DTDAY>" << soil.stm.getINITDTDAY( pcmnt );
  fout << "</DTDAY>" << endl;
  fout << "  </snowPackECD>" << endl;
  fout << endl;

  fout << "  <soilLayerECD>" << endl;

  for( dlayer = 0; dlayer < MAXSLAYERS; ++dlayer )
  {
    fout << "    <THICK" << (dlayer+1) << ">"; 
    fout << soil.stm.getINITTHICK( pcmnt, dlayer );
    fout << "</THICK" << (dlayer+1) << ">" << endl;
    fout << "    <DXA" << (dlayer+1) << ">"; 
    fout << soil.stm.getINITDXA( pcmnt, dlayer );
    fout << "</DXA" << (dlayer+1) << ">" << endl;
    fout << "    <DXB" << (dlayer+1) << ">";  
    fout << soil.stm.getINITDXB( pcmnt, dlayer );
    fout << "</DXB" << (dlayer+1) << ">" << endl;
    fout << "    <MAT" << (dlayer+1) << ">";  
    fout << soil.stm.getVEGMAT( pcmnt, dlayer );
    fout << "</MAT" << (dlayer+1) << ">" << endl;
    fout << "    <DENSE" << (dlayer+1) << ">";  
    fout << soil.stm.getINITDENSE( pcmnt, dlayer );
    fout << "</DENSE" << (dlayer+1) << ">" << endl;
    fout << "    <WATER" << (dlayer+1) << ">";  
    fout << soil.stm.getINITWATER( pcmnt, dlayer );
    fout << "</WATER" << (dlayer+1) << ">" << endl;
    fout << "    <vcond" << (dlayer+1) << ">";  
    fout << soil.stm.getVCOND( pcmnt, dlayer );
    fout << "</vcond" << (dlayer+1) << ">" << endl;
    fout << "    <vsph" << (dlayer+1) << ">";  
    fout << soil.stm.getVSPH( pcmnt, dlayer );
    fout << "    <cond" << (dlayer+1) << ">";  
    fout << soil.stm.getINITCONDT( pcmnt, dlayer );
    fout << "</cond" << (dlayer+1) << ">" << endl;
    fout << "    <spht" << (dlayer+1) << ">";  
    fout << soil.stm.getINITSPHT( pcmnt, dlayer );
    fout << "</spht" << (dlayer+1) << ">" << endl;
    fout << "    <condf" << (dlayer+1) << ">";  
    fout << soil.stm.getINITCONDF( pcmnt, dlayer );
    fout << "</condf" << (dlayer+1) << ">" << endl;
    fout << "    <sphf" << (dlayer+1) << ">";  
    fout << soil.stm.getINITSPHF( pcmnt,dlayer );
    fout << "</sphf" << (dlayer+1) << ">" << endl;
    fout << endl;
  }  

  fout << "  </soilLayerECD>" << endl;
  fout << endl;

  fout << "  <agECD>" << endl;
  fout << "    <nvretconv>" << ag.getNVRETCONV( pcmnt );
  fout << "</nvretconv>" << endl;
  fout << "    <nsretconv>" << ag.getNSRETCONV( pcmnt );
  fout << "</nsretconv>" << endl;
  fout << "    <tillfactor>" << ag.getTILLFACTOR( pcmnt );
  fout << "</tillfactor>" << endl;
  fout << "    <harvstC>" << ag.getHARVSTC( pcmnt );
  fout << "</harvstC>" << endl;
  fout << "    <harvstN>" << ag.getHARVSTN( pcmnt );
  fout << "</harvstN>" << endl;
  fout << "    <residueC>" << ag.getRESIDUEC( pcmnt );
  fout << "</residueC>" << endl;
  fout << "    <residueN>" << ag.getRESIDUEN( pcmnt );
  fout << "</residueN>" << endl;
  fout << "    <cropseedC>" << ag.getCROPSEEDC( pcmnt );
  fout << "</cropseedC>" << endl;
  fout << "    <cropseedSTRN>" << ag.getCROPSEEDSTRN( pcmnt );
  fout << "</cropseedSTRN>" << endl;
  fout << "    <cropseedSTON>" << ag.getCROPSEEDSTON( pcmnt );
  fout << "</cropseedSTON>" << endl;
  fout << "  </agECD>" << endl;
  fout << "</community>" << endl;
  
};








