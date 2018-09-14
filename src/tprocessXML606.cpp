/* *************************************************************
TPROCESSMXL606.CPP - Functions to process XML files for TEM

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/>   

************************************************************* */

#include "tprocessXML606.h"


ProcessXML60::ProcessXML60()
{

};

/* *************************************************************
************************************************************* */

void ProcessXML60::endXMLNode( ifstream& infile,
                               const string& node )

{
  string line;
  string endNode = "</" + node + ">";

  while ( line.find( endNode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << endNode << " !!!" << endl;
    exit( -1 );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

void ProcessXML60::endXMLtvegNode( ifstream& infile )

{
  string line;

  while ( line.find( "</temveg>" ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double ProcessXML60::getXMLcmntArrayDouble( ifstream& infile,
                                            const string& rootnode,
                                            const string& varnode,
                                            const int& index )

{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode << " for community type ";
    cerr << index << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return MISSING; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atof( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int ProcessXML60::getXMLcmntArrayInt( ifstream& infile,
                                      const string& rootnode,
                                      const string& varnode,
                                      const int& index )
{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode << " for community type ";
    cerr << index << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return -99; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atoi( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

long ProcessXML60::getXMLcmntArrayLong( ifstream& infile,
                                        const string& rootnode,
                                        const string& varnode,
                                        const int& index )
{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode << " for community type ";
    cerr << index << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return -99; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atol( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double ProcessXML60::getXMLdouble( ifstream& infile,
                                   const string& rootnode,
                                   const string& varnode )
{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode;
    cerr << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return MISSING; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atof( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int ProcessXML60::getXMLint( ifstream& infile,
                             const string& rootnode,
                             const string& varnode )
{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode;
    cerr << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return -99; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atoi( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

long ProcessXML60::getXMLlong( ifstream& infile,
                               const string& rootnode,
                               const string& varnode )
{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode;
    cerr << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return -99; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atol( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int ProcessXML60::getXMLNode( ifstream& infile,
                              const string& node )

{
  string line;

  while ( line.find( node ) == string::npos && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << node << " !!!" << endl;
    exit( -1 );
  }

  return 0;

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int ProcessXML60::getXMLCommunityNode( ifstream& infile,
                                       string& description,
                                       string& sitename,
                                       string& sitecol,
                                       string& siterow,
                                       string& developer,
                                       string& version,
                                       string& updated )
{

  string line;
  string temp;
  string temp2;

  int startString;
  int endString;

  string value;

  while ( line.find( "community" ) == string::npos && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find <community> node!!!" << endl;
    exit( -1 );
  }
  else
  {
    startString = line.find( "type" );
    temp = line.substr( startString, 30 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 30 );
    endString = temp2.find( '"' );
    value = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "description" );
    temp = line.substr( startString, 50 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 50 );
    endString = temp2.find( '"' );
    description = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "site" );
    temp = line.substr( startString, 80 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 80 );
    endString = temp2.find( '"' );
    sitename = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "longitude" );
    temp = line.substr( startString, 50 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 50 );
    endString = temp2.find( '"' );
    sitecol = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "latitude" );
    temp = line.substr( startString, 50 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 50 );
    endString = temp2.find( '"' );
    siterow = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "developedBy" );
    temp = line.substr( startString, 80 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 80 );
    endString = temp2.find( '"' );
    developer = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "version" );
    temp = line.substr( startString, 50 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 50 );
    endString = temp2.find( '"' );
    version = temp2.substr( 0, endString );

    getline( infile, line );

    startString = line.find( "updated" );
    temp = line.substr( startString, 50 );
    startString = temp.find( '"' );
    temp2 = temp.substr( (startString+1), 50 );
    endString = temp2.find( '"' );
    updated = temp2.substr( 0, endString );
  }

  return atoi( value.c_str() );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int ProcessXML60::getXMLtemvegNode( ifstream& infile,
                                    const string& rootnode )
{
  string line;
  string value;

  string temp;
  int startString;


  while ( line.find( ">" ) == string::npos
          && !infile.eof() )
  {
    getline( infile, temp );
    if ( temp.size() > 0 )
    {
      line += temp;
      temp.erase();
    }
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find TEMVEG type in " << rootnode;
    cerr << " !!!" << endl;
    exit( -1 );
  }

  startString = line.find( "<temveg type = " );
  temp = line.substr( startString, 30 );
  startString = temp.find( '"' );
  value = temp.substr( (startString+1), 5 );

  return atoi( value.c_str() );

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

double ProcessXML60::getXMLtvegArrayDouble( ifstream& infile,
                                            const string& rootnode,
                                            const string& varnode,
                                            const int& index )

{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode << " for TEMVEG = ";
    cerr << index << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return MISSING; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atof( value.c_str() );
  }

};

/* *************************************************************
************************************************************* */


/* *************************************************************
************************************************************* */

int ProcessXML60::getXMLtvegArrayInt( ifstream& infile,
                                      const string& rootnode,
                                      const string& varnode,
                                      const int& index )
{
  string line;
  string value;

  string endVarnode = "</" + varnode + ">";
  unsigned int startString;

  while ( line.find( endVarnode ) == string::npos
          && !infile.eof() )
  {
    getline( infile, line );
  }

  if ( 0 == line.size() )
  {
    cerr << endl << "Cannot find " << varnode << " for TEMVEG = ";
    cerr << index << " in " << rootnode << endl;
    exit( -1 );
  }

  startString = line.find( ">" );
  if ( startString == string::npos ) { return (int) MISSING; }
  else
  {
    value = line.substr( (startString+1), 20 );
    return atoi( value.c_str() );
  }

};


