/* *************************************************************
****************************************************************
TBIOME606.CPP - object describing general characteristics of
               vegetation mosaic used in the Terrestrial
	       Ecosystem Model (TEM)

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
           
****************************************************************
************************************************************* */

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
  using std::atoi;
  
#include<string>
  
  using std::string;

#include<sstream>

  using std::ostringstream;


#include "tbiome606.h"


/* *************************************************************
************************************************************* */

Biome60::Biome60( void ) : ProcessXML60()
{
  int dmsac;
  int dv;

  cmnt = -99;
  cmnt_name = "MISSING";
  subarea = MISSING;
  temveg = -99;
  
  for( dv = 0; dv < MAXNVEG; ++dv )
  {
    numtype[dv] = 1;  
    wfpsoff[dv] = MISSING;

    for( dmsac = 0; dmsac < MAXNMSAC; ++dmsac )
    {
      subtype[dv][dmsac] = -99;
      pcttype[dv][dmsac] = MISSING;
    }
  }
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Biome60::getCommunityType( const int& tveg )
{
  int mez;
  int communtype;
  
//  mez = tveg - 1;
  mez = tveg;

  if( mez < 0 || mez >= MAXNVEG )
  {
    communtype = 0;
  }
  else { communtype = subtype[mez][0]; }

  return communtype;	
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Biome60::getVegMosaic( const int& tveg )
{
  int mez;
  int maxtype;

//  mez = tveg - 1;
  
  mez = tveg;

  if( mez < 0 || mez >= MAXNVEG )
  {
    maxtype = 1;
  }
  else { maxtype = numtype[mez]; }

  return maxtype;
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Biome60::getVegSubarea( const int& tveg,
                               const int& dmsac,
                               const int& carea )
{
  int mez;
  double sarea;
 
  mez = tveg;

  if( mez < 0 || mez >= MAXNVEG )
  {
    sarea = (double) carea;
  }
  else { sarea = (double) carea * pcttype[mez][dmsac] * 0.01; }

  return sarea;
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int Biome60::getVegSubtype( const int& tveg, const int& dmsac )
{
  int mez;
  int vegtype;
 
  mez = tveg;

  if( mez < 0 || mez >= MAXNVEG )
  {
    vegtype = 0;
  }
  else { vegtype = subtype[mez][dmsac]; }

  return vegtype;
};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Biome60::getvtype( ofstream& rflog1 )
{

  string ecd;

  cout << endl;
  cout << "Enter name of the file prescribing vegetation mosaics (.ECD):";
  cout << endl;
  
  cin >> ecd;

  rflog1 << endl;
  rflog1 << "Enter name of the file prescribing vegetation mosaics (.ECD):";
  rflog1 << endl << ecd << endl << endl;

  getvtype( ecd );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void Biome60::getvtype( const string& ecd )
{
  int dmsac;

  int dv;

  int endString;

  int ez;

  ifstream infile;

  string line;

  int numveg;

  int startString;

  string temp;

  string temp2;

  ostringstream tempString;

  string value;

  int vegtype;



  infile.open( ecd.c_str(), ios::in );

  if ( !infile )
  {
    cerr << endl << "Cannot open " << ecd;
    cerr << " for community ECD input" << endl;

    exit( -1 );
  }

  getXMLNode( infile, "communityECD" );

  getline( infile, line );

  startString = line.find( "numveg" );
  temp = line.substr( startString, 30 );
  startString = temp.find( '"' );
  temp2 = temp.substr( (startString+1), 30 );
  endString = temp2.find( '"' );
  value = temp2.substr( 0, endString  );

  numveg = atoi( value.c_str() );

  for ( dv = 0; dv < numveg; ++dv )
  {

    vegtype = getXMLtemvegNode( infile, "communityECD" );

    if ( vegtype >= MAXNVEG )
    {
      cerr << endl << "TEMVEG type " << vegtype << endl;
      cerr << " cannot be greater than " << (MAXNVEG-1);
      cerr << " in communityECD" << endl;
      
      exit( -1 );
    }

    ez = vegtype;


    numtype[ez] = getXMLtvegArrayInt( infile,
                                      "communityECD",
                                      "numtype",
                                      vegtype );

    for ( dmsac = 0; dmsac < MAXNMSAC; ++dmsac )
    {
      tempString.str( "" );
      tempString << "subtype" << (dmsac+1);
      subtype[ez][dmsac] = getXMLtvegArrayInt( infile,
                                               "communityECD",
                                               tempString.str(),
                                               vegtype );

      tempString.str( "" );
      tempString << "pcttype" << (dmsac+1);
      pcttype[ez][dmsac] = getXMLtvegArrayDouble( infile,
                                                  "communityECD",
                                                  tempString.str(),
                                                  vegtype );
    }

    wfpsoff[ez] = getXMLtvegArrayInt( infile,
                                      "communityECD",
                                      "wfpsoff",
                                      vegtype );

    endXMLtvegNode( infile );
  }


  if ( dv < numveg )
  {
    cerr << endl << " Parameters found for only " << dv;
    cerr << " community types out of a maximum of ";
    cerr << numveg << " types in communityECD" << endl;

    exit( -1 );
  }

  infile.close();

};


/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double Biome60::getWFPSOFF( const int& tveg )
{
  int mez;
  
//  mez = tveg - 1;

  mez = tveg;
  
  if( mez < 0 || mez >= MAXNVEG ) { return ZERO; }
  else { return wfpsoff[mez]; }

};
