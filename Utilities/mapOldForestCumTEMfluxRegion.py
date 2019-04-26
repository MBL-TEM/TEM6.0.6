#!/usr/bin/env python

"""
################################################################
Program: mapOldForestCumTEMfluxRegion.py 

Description: Program maps the distribution of the December value 
  of a pool variable (e.g. Veg C) estimated by TEM version 6.0.6 
  for old forest ecosystems ( >= 120-years old) during a 
  specified year (i.e. testyr). The program output is an ARC/INFO 
  ASCII text file that can then be used directly by ARCMap to 
  generate a map.  

################################################################

BY DOWNLOADING THIS PROGRAM YOU AGREE TO THE FOLLOWING TERMS OF USE:

Copyright © 2019.  The Marine Biological Laboratory (“MBL”). All 
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

Created by David W. Kicklighter at The Marine Biological Laboratory.

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

################################################################
"""

if __name__ == '__main__':
  ifile = open( 'TEMflux1500_2100.region', 'r' )
  ofile = open( 'cumTEMflux2001_2100region.map', 'w' )

  startyr = 2001
  endyr = 2100

  MISSING = -999999.9
  testvar = {}
  sumvar = {}
 
  for dlat in range( 360 ):
    for dlon in range( 720 ):
      sumvar[(dlon, dlat)] = MISSING

  maxlon = -1
  maxlat = -1
  minlon = 900
  minlat = 900
  for line in ifile.xreadlines():
    
    field = line.split( "," )
    
    lon = float( field[0] )
    lat = float( field[1] )
    totlon = 0

    if( lon < 0.0 ):
      lon += 360.0
  
    ilon = int( (lon * 2) + (totlon * 0.5 ) )
    ilat = int( 180 - (lat * 2) - 1 )

    if( ilon > maxlon ): maxlon = ilon
    if( ilat > maxlat ): maxlat = ilat
    if( ilon < minlon ): minlon = ilon
    if( ilat < minlat ): minlat = ilat

    standage = int( field[4] )
    curveg = int( field[6] )
    grdarea = float( field[12] )
    cohrtarea = float( field[13] )
    year = int( field[14] )
    testvar = float( field[15] )

    if( year >= startyr            
         and year <= endyr         
         and testvar > MISSING     
         and(1 == curveg          
             or 2 == curveg       
             or 3 == curveg        
             or 4 == curveg        
             or 5 == curveg        
             or 6 == curveg        
             or 7 == curveg        
             or 8 == curveg        
             or 26 == curveg       
             or 28 == curveg)
         and standage >= 120 ):
      if( sumvar[(ilon, ilat)] == MISSING ):
        sumvar[(ilon, ilat)] = testvar * (cohrtarea/grdarea)
      else:
        sumvar[(ilon, ilat)] += (testvar * (cohrtarea/grdarea))


  if( minlon > 5 ): 
    minlon -= 5
  else:
    minlon = 0

  if( minlat > 5 ): 
    minlat -= 5
  else: 
    minlat = 0

  if( maxlon < 714 ):
    maxlon += 5
  else:
    maxlon = 719

  if( maxlat < 354 ):
    maxlat += 5
  else:
    maxlat = 359

  

  dlon = maxlon - minlon
  dlat = maxlat - minlat
  xll = 0.5 * minlon
  yll = 90.0 - (0.5 * maxlat)
  ofile.write( "ncols %d\n" % dlon ) 
  ofile.write( "nrows %d\n" % dlat ) 
  ofile.write( "xllcorner %f\n" % xll )  
  ofile.write( "yllcorner %f\n" % yll )
  ofile.write( "cellsize 0.5\n" )
  ofile.write( "nodata_value %.1f\n" % MISSING )
    
  for ilat in range( minlat, maxlat ):
    for ilon in range( minlon, maxlon ):
      ofile.write( "%.5f " % sumvar[(ilon, ilat)] )
   
    ofile.write( "\n" )
