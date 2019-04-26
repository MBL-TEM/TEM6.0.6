#!/usr/bin/env python

"""
################################################################
Program: mapPasture2Forest.py 

Description: Program maps the areas in a region where decreases 
  in the relative coverage in pastures over time are related to 
  the concurrent increases in the relative coverage of forests 
  over the same	time period.

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
  firstfile = open( 'dforest2050_2100region.map', 'r' )
  secndfile = open( 'dpasture2050_2100region.map', 'r' )
  ofile = open( 'pasture2forest2050_2100region.map', 'w' )


  var1 = {}
  var2 = {}
  diffvar = {}
 
  firstline = firstfile.readline()
  firstfield = firstline.split( " " )
  maxlon = int( firstfield[1] ) 
  
  firstline = firstfile.readline()
  firstfield = firstline.split( " " )
  maxlat = int( firstfield[1] ) 
  
  firstline = firstfile.readline()
  firstfield = firstline.split( " " )
  xll = float( firstfield[1] ) 

  firstline = firstfile.readline()
  firstfield = firstline.split( " " )
  yll = float( firstfield[1] ) 

  firstline = firstfile.readline()
  firstfield = firstline.split( " " )
  cellsize  = float( firstfield[1] ) 

  firstline = firstfile.readline()
  firstfield = firstline.split( " " )
  nodata = float( firstfield[1] ) 
  
  secndline = secndfile.readline()
  secndline = secndfile.readline()
  secndline = secndfile.readline()
  secndline = secndfile.readline()
  secndline = secndfile.readline()
  secndline = secndfile.readline()
  
  for dlat in range( maxlat ):
    firstline = firstfile.readline()
    firstfield = firstline.split( " " )
    secndline = secndfile.readline()
    secndfield = secndline.split( " " )
    for dlon in range( maxlon ):
      var1[(dlon, dlat)] = float( firstfield[dlon] ) 
      var2[(dlon, dlat)] = float( secndfield[dlon] )
      if( var1[(dlon, dlat)] != nodata and var2[(dlon, dlat)] != nodata ):
        if( var1[(dlon, dlat)] > 0.000000 ):
          if( var2[(dlon, dlat)] < -0.000000 ):
            if( var1[(dlon, dlat)] + var2[(dlon, dlat)] > 0.00000 ):
              diffvar[(dlon, dlat)] = -1.0 *  var2[(dlon, dlat)]
            else:
     	      diffvar[(dlon, dlat)] = var1[(dlon, dlat)]
          else:
            diffvar[(dlon, dlat)] = 0.000000;
        else:
            diffvar[(dlon, dlat)] = 0.000000;
      else:
    	  diffvar[(dlon, dlat)] = nodata
      	

  ofile.write( "ncols %d\n" % maxlon ) 
  ofile.write( "nrows %d\n" % maxlat ) 
  ofile.write( "xllcorner %f\n" % xll )  
  ofile.write( "yllcorner %f\n" % yll )
  ofile.write( "cellsize %.1f\n" % cellsize )
  ofile.write( "nodata_value %f\n" % nodata )
    
  for dlat in range( 0, maxlat ):
    for dlon in range( maxlon ):
      ofile.write( "%f " % diffvar[(dlon, dlat)] )
   
    ofile.write( "\n" )
