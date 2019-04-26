/* *************************************************************
Program: DIFFMAP606C.CXX

Description: Program maps the difference between two other
                maps in ARC/INFO ASCII text format

**************************************************************

BY DOWNLOADING THIS PROGRAM YOU AGREE TO THE FOLLOWING TERMS OF USE:

Copyright © 2018.  The Marine Biological Laboratory (“MBL”). All 
Rights Reserved.  

Permission to use, copy, modify, and distribute this software, 
including all object code and source code, and any accompanying
documentation (together the “Software”) for educational and 
not-for-profit research purposes, without fee and without a signed
licensing agreement, is hereby granted, provided that the above 
copyright notice, this paragraph and the following three paragraphs
appear in all copies, modifications, and distributions. For the 
avoidance of doubt, educational and not-for-profit research purposes
excludes any service or part of selling a service that uses the 
Software. To obtain a commercial license for the Software, contact 
the Technology Commercialization team at the Polsky Center for 
Entrepreneurship and Innovation, University of Chicago, 1452 East 
53rd Street, 2nd floor, Chicago, IL 60615.

Created by David W. Kicklighter, A. David McGuire, and 
Greg Christopher at The Marine Biological Laboratory.

The Software is copyrighted by MBL. The Software is supplied 
"as is", without any accompanying services from MBL. MBL 
does not warrant that the operation of the Software will be 
uninterrupted or error-free. The end-user understands that the 
Software was developed for research purposes and is advised not 
to rely exclusively on the Software for any reason.

IN NO EVENT SHALL MBL BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, 
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
PROFITS, ARISING OUT OF THE USE OF THE SOFTWARE, EVEN IF MBL 
HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. MBL SPECIFICALLY
DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
THE SOFTWARE PROVIDED HEREUNDER IS PROVIDED "AS IS".  MBL HAS 
NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
ENHANCEMENTS, OR MODIFICATIONS.

*****************************************************************
************************************************************** */


#define ANSI_CPP

#include<cstdio>

  using std::fopen;
  using std::fclose;
  using std::printf;
  using std::sprintf;
  using std::fscanf;
  using std::FILE;

#include<iostream>

  using std::cout;
  using std::cin;
  using std::ios;
  using std::cerr;
  using std::endl;

#include<fstream>

  using std::ifstream;
  using std::ofstream;

#include<iomanip>

  using std::setiosflags;
  using std::setw;
  using std::setprecision;


#ifdef ANSI_CPP

  #include<cstdlib>

  #include<cmath>

#endif

#ifdef BORLAND_CPP

  #include<stdlib>

  #include<math>

#endif

#include<cctype>

  using std::toupper;
  using std::tolower;

#include<cstring>

#include<string>

  using std::string;

#include<sstream>

  using std::ostringstream;

#ifdef ANSI_CPP

  #include<ctime>

  using std::time_t;
  using std::ctime;

#endif

#ifdef BORLAND_CPP

  #include<time>

  using std::time_t;
  using std::ctime;

#endif

const int MAXNLON = 720;
const int MAXNLAT = 360;



int main()
{
  string dummy;
  
  ifstream fin1;
  ifstream fin2;
  ofstream fout;

  string ifname1;
  string ifname2;
  string ofname;

  int icol;
  int irow;

  double indata1;
  double indata2;
  double diff;

  float minlat;
  float minlon;

  double missing;
  
  int ncols;
  int nrows;
  

  cout << "Please enter the name of the first input map:" << endl;
  cout << "               (e.g., TAIR.MAP) " << endl;


  cin >> ifname1;
    
  fin1.open( ifname1.c_str(), ios::in );

  if( !fin1 ) 
  {
    cerr << endl << "Cannot open " << ifname1;
    cerr << " for data input from the first map." << endl;

    exit( -1 );
  }
   

  cout << "Please enter the name of the second input map:" << endl;
  cout << "               (e.g., TAIR.MAP) " << endl;


  cin >> ifname2;
    
  fin2.open( ifname2.c_str(), ios::in );

  if( !fin2 ) 
  {
    cerr << endl << "Cannot open " << ifname1;
    cerr << " for data input from the second map." << endl;

    exit( -1 );
  }


  cout << "Please enter the name of the output difference map:" << endl;
  cout << "  (e.g., DIFF.MAP, will equal to MAP1 - MAP2) " << endl;


  cin >> ofname;
    
  fout.open( ofname.c_str(), ios::out );

 
  // Read in header data from first map
  
  fin1 >> dummy >> ncols;
  fin1 >> dummy >> nrows; 
  fin1 >> dummy >> minlon;
  fin1 >> dummy >> minlat;
  fin1 >> dummy >> dummy;
  fin1 >> dummy >> missing;

  fin1.seekg( 0, ios::cur );
	  

  // Read in header data from second map

  fin2 >> dummy >> ncols;
  fin2 >> dummy >> nrows; 
  fin2 >> dummy >> minlon;
  fin2 >> dummy >> minlat;
  fin2 >> dummy >> dummy;
  fin2 >> dummy >> missing;

  fin2.seekg( 0, ios::cur );

  // Write header data to difference map

  fout << "ncols " << ncols << endl;
  fout << "nrows " << nrows << endl;
  fout << "xllcorner " << minlon << endl;
  fout << "yllcorner " << minlat << endl;
  fout << "cellsize 0.5" << endl;
  fout << "nodata_value " << missing << endl;
    
  for( irow = 0; irow < nrows; ++irow )
  {
    for( icol = 0; icol < ncols; ++icol )
    {
      fin1 >> indata1;
      fin1.seekg( 0, ios::cur );
      
      fin2 >> indata2;
      fin2.seekg( 0, ios::cur );

      if ( indata1 != missing && indata2 != missing ) 
      { 
        diff = indata1 - indata2;
      }
      else { diff = missing; }

      fout << diff << " ";
    }
    
    fout << endl;
  }


// Close files

  fin1.close();
  fin2.close();
  fout.close();
  
  return 0;
  
};

