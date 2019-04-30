/* *************************************************************
*  Program . . . .:  ADDMAP606C.CXX
*  Author. . . . .:  David Kicklighter
*  Programmer. . .:  David Kicklighter
*  Address . . . .:  Ecosystems Center
*                    Marine Biological Laboratory
*                    Woods Hole, MA  02543
*  Phone . . . . .:  (508) 289-7490
*  Date  . . . . .:  June 16, 2007
*  Notice  . . . .:  Copyright 2007
************************************************************** */


/* *************************************************************
*  Description: Program maps the addition of results in two other
                maps in ARC/INFO format

20071025 - DWK created by modifying diffmap44a.cxx

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
  double sum;

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
  cout << "  (e.g., ADD.MAP, will equal to MAP1 + MAP2) " << endl;


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
        sum = indata1 + indata2;
      }
      else { sum = missing; }

      fout << sum << " ";
    }
    
    fout << endl;
  }


// Close files

  fin1.close();
  fin2.close();
  fout.close();
  
  return 0;
  
};

