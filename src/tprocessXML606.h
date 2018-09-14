/* *************************************************************
TPROCESSMXL606.H - Functions to process XML files for TEM

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 
                       
************************************************************** */

#ifndef PROCESSXML606_H
#define PROCESSXML606_H

#include "protocol605.hpp"

#include "temconsts606.hpp"

#include<iostream>

  using std::cerr;
  using std::cout;
  using std::endl;

#include<fstream>

  using std::ifstream;

#include<cstdlib>

  using std::exit;
  using std::atof;
  using std::atoi;
  using std::atol;
  
#include<string>
  
  using std::string;



class ProcessXML60
{
  public:

  ProcessXML60();

  void endXMLNode( ifstream& infile,
                   const string& node );

  void endXMLtvegNode( ifstream& infile );

  double getXMLcmntArrayDouble( ifstream& infile,
                                const string& rootnode,
                                const string& varnode,
                                const int& index );

  int getXMLcmntArrayInt( ifstream& infile,
                          const string& rootnode,
                          const string& varnode,
                          const int& index );

  long getXMLcmntArrayLong( ifstream& infile,
                            const string& rootnode,
                            const string& varnode,
                            const int& index );

  int getXMLCommunityNode( ifstream& infile,
                          string& description,
                          string& sitename,
                          string& sitecol,
                          string& siterow,
                          string& developer,
                          string& version,
                          string& updated );

  double getXMLdouble( ifstream& infile,
                       const string& rootnode,
                       const string& varnode );

  int getXMLint( ifstream& infile,
                 const string& rootnode,
                 const string& varnode );

  long getXMLlong( ifstream& infile,
                   const string& rootnode,
                   const string& varnode );

  int getXMLNode( ifstream& infile, const string& node );

  int getXMLtemvegNode( ifstream& infile, const string& rootnode );

  double getXMLtvegArrayDouble( ifstream& infile,
                                const string& rootnode,
                                const string& varnode,
                                const int& index );

  int getXMLtvegArrayInt( ifstream& infile,
                          const string& rootnode,
                          const string& varnode,
                          const int& index );

};

#endif
