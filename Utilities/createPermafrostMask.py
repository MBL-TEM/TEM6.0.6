#!/usr/bin/env python

"""
################################################################
Program: createPermafrostMask.py

Description: Program determines where permafrost occurs based on 
             soil temperature being less that 0 degrees Celsius.
             Based on this information, the program then outputs 
             a list of the locations where permafrost occurs in
             the grid cells. 
################################################################

BY DOWNLOADING THIS PROGRAM YOU AGREE TO THE FOLLOWING TERMS OF USE:

Copyright 2019.  The Marine Biological Laboratory (MBL). All 
Rights Reserved.  

Permission to use, copy, modify, and distribute this software, 
including all object code and source code, and any accompanying
documentation (together the Software) for educational and 
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
  ifile = open( 'dst200_2100region.map', 'r' )
  ofile = open( 'permafrostmask2100region.lon', 'w' )


  sumvar = {}
 
  line = ifile.readline()
  field = line.split( " " )
  maxlon = int( field[1] ) 
  
  line = ifile.readline()
  field = line.split( " " )
  maxlat = int( field[1] ) 
  
  line = ifile.readline()
  field = line.split( " " )
  xll = float( field[1] ) 

  line = ifile.readline()
  field = line.split( " " )
  yll = float( field[1] ) 

  line = ifile.readline()
  field = line.split( " " )
  cellsize  = float( field[1] ) 

  line = ifile.readline()
  field = line.split( " " )
  nodata = float( field[1] ) 
    
  for dlat in range( maxlat ):
    line = ifile.readline()
    field = line.split( " " )
    for dlon in range( maxlon ):
      sumvar[(dlon, dlat)] = float( field[dlon] ) 

      if( sumvar[(dlon, dlat)] != nodata ):
      	if( sumvar[(dlon, dlat)] <= 0.000000 ):
          sumvar[(dlon, dlat)] = 1.000000   		     	
        else:
          sumvar[(dlon, dlat)] = 0.000000   		     	
        	
  for dlon in range( maxlon ):
    for dlat in range( (maxlat-1), -1, -1 ):
      if( sumvar[(dlon, dlat)] != 0.000000 and sumvar[(dlon, dlat)] != nodata ):
        ilon = xll + (dlon * cellsize)
        ilat = yll + (maxlat * cellsize) - (dlat * cellsize) - cellsize
        if( ilon >= 180.0 ): ilon = ilon - 360.0 
        ofile.write( "%.1f,%.1f\n" % (ilon, ilat) )  
  
