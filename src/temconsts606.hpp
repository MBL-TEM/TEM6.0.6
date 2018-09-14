#ifndef ACCEPT_CONST
#define ACCEPT_CONST
  const int ACCEPT = 0;
#endif

#ifndef ASPHALT_CONST
#define ASPHALT_CONST
  const int ASPHALT = 17;
#endif

#ifndef BAREGRND_CONST
#define BAREGRND_CONST
  const int BAREGRND = 1;
#endif

// IGSMVEG index of biofuel crops
#ifndef BIOFUELS_CONST
#define BIOFUELS_CONST
  const int BIOFUELS = 16;
#endif   

// TEMVEG index of crops
#ifndef CROPVEG_CONST
#define CROPVEG_CONST
  const int CROPVEG = 15;
#endif

// Number of months in an annual cycle
#ifndef CYCLE_CONST    
#define CYCLE_CONST
  const int CYCLE = 12;
#endif

// First value in vegetation classification scheme
//   (usually "0" or "1")
#ifndef FIRSTVEG_CONST
#define FIRSTVEG_CONST
  const int FIRSTVEG = 0;
#endif

// IGSMVEG index of glaciers
#ifndef GLACIERS_CONST
#define GLACIERS_CONST
  const int GLACIERS = 1;
#endif


#ifndef LAKES_CONST
#define LAKES_CONST
  const int LAKES = 18;
#endif

#ifndef LAWN_CONST
#define LAWN_CONST
  const int LAWN = 16;
#endif

// Maximum number of cohorts in a grid cell
#ifndef MAXCHRTS_CONST    
#define MAXCHRTS_CONST
  const int MAXCHRTS = 6000;
#endif

// Maximum number of community types for TEM parameters
#ifndef MAXCMNT_CONST
#define MAXCMNT_CONST
  const int MAXCMNT = 20;
#endif

// Maximum number of ecosystem (i.e. carbon and nitrogen)
//   pool variables in TEM
#ifndef MAXESTAT_CONST
#define MAXESTAT_CONST
  const int MAXESTAT = 9;
#endif

#ifndef MAXFRI_CONST
#define MAXFRI_CONST
  const int MAXFRI = 2000;
#endif

#ifndef MAXGRID_CONST    
#define MAXGRID_CONST
  const int MAXGRID = 1;
#endif

// Maximum number of vegetation subtypes in a mosaic
#ifndef MAXNMSAC_CONST
#define MAXNMSAC_CONST
  const int MAXNMSAC = 5;
#endif

// Maximum number of snow and soil nodes for STM
#ifndef MAXNODES_CONST    
#define MAXNODES_CONST
  const int MAXNODES = 210;
#endif

// Maximum number of vegetation types
#ifndef MAXNVEG_CONST
#define MAXNVEG_CONST
  const int MAXNVEG = 61;
#endif

// Maximum number of years in a simulation
#ifndef MAXRTIME_CONST    
#define MAXRTIME_CONST
  const int MAXRTIME = 1850;
#endif

// Maximum number of nodes in snowpack for STM
#ifndef MAXSNODES_CONST
#define MAXSNODES_CONST
  const int MAXSNODES = 9;
#endif

// Maximum standage
#ifndef MAXSTANDAGE_CONST
#define MAXSTANDAGE_CONST
  const int MAXSTANDAGE = 3000;
#endif

// Maximum number of water pool variables
#ifndef MAXWSTAT_CONST
#define MAXWSTAT_CONST
  const int MAXWSTAT = 3;
#endif

// Minimum active layer depth is 0.0001 m (used to avoid 
//   dividing by zero when calculating volumeteric soil 
//   moisture)
// Maximum number of vegetation subtypes in a mosaic
 #ifndef MINACTLAYERZ_CONST
#define MINACTLAYERZ_CONST
  const double MINACTLAYERZ = 0.0001;
#endif

// Value given for "missing" in IGSM community
//   types
#ifndef MISSCOMMUN_CONST
#define MISSCOMMUN_CONST
  const double MISSCOMMUN = 1;
#endif


// Default value for missing data
#ifndef MISSING_CONST    
#define MISSING_CONST
  const double MISSING = -999999.9;
#endif

// Value given for "missing" in IGSM vegetation
//   classification scheme
#ifndef MISSVEG_CONST
#define MISSVEG_CONST
  const double MISSVEG = 30;
#endif

// Total number of TEMCLM output variables
#ifndef NUMATMS_CONST
#define NUMATMS_CONST
const int NUMATMS = 13;
#endif

// Total number of STM output variables
#ifndef NUMSTM_CONST
#define NUMSTM_CONST
const int NUMSTM = 13;
#endif

// IGSMVEG index of pastures
#ifndef PASTURE_CONST
#define PASTURE_CONST
  const int PASTURE = 33;
#endif


#ifndef REJECT_CONST
#define REJECT_CONST
  const int REJECT = 1;
#endif

#ifndef ZERO_CONST    
#define ZERO_CONST
  const double ZERO = 0.000000;
#endif

/* *************************************************************
     Constants that are combinations of other constants
************************************************************* */

// Maximum number of pool variables in simulation
#ifndef MAXSTATE_CONST
#define MAXSTATE_CONST
  const int MAXSTATE = MAXWSTAT + MAXESTAT;
#endif

// Maximum number of state (pools plus fluxes) variables
//  used to simulate hydrology in TEM 
#ifndef NUMWEQ_CONST
#define NUMWEQ_CONST
const int NUMWEQ = MAXWSTAT + 7;
#endif

// Maximum number of state (pools plus fluxes) variables
//  used to simulate carbon and nitrogen dynamics in TEM 
#ifndef NUMEEQ_CONST
#define NUMEEQ_CONST
  const int NUMEEQ = MAXESTAT + 59;
#endif

// Total number of state (pools plus fluxes variables
//  (carbon, nitrogen and water) used in TEM 
#ifndef NUMEQ_CONST
#define NUMEQ_CONST
  const int NUMEQ = NUMWEQ + NUMEEQ;
#endif

// Total number of output variables from TEM 
#ifndef NUMTEM_CONST
#define NUMTEM_CONST
  const int NUMTEM = NUMEQ + 169;
#endif
                      
