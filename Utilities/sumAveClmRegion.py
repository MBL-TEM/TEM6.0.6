#!/usr/bin/env python

"""
################################################################
Program:  sumAveClmRegion.py - Program aggregates gridded data 
  to determine a time series of area-weighted mean annual values 
  of the Clm variable for the region 
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

*****************************************************************
*****************************************************************
"""


if __name__ == '__main__':
  ifile = open( 'Clm1500_2100.region', 'r' )
  ofile = open( 'AveClm1500_2100region.sum', 'w' )

  sumtair = {}
  sumarea = {}

  for dyr in range( 1499, 2101 ):
    sumtair[dyr] = 0.0
    sumarea[dyr] = 0

  for line in ifile.xreadlines():
    
    field = line.split( "," )
    
    area = float( field[3] )
    year = int( field[4] )
    avetair = float( field[7] )

    if avetair > -99.0:
      sumarea[year] += area
      sumtair[year] += (area * avetair)



  for dyr in range( 1499, 2101 ):
    sumtair[dyr] /= sumarea[dyr]

    ofile.write( "%d,%.3f\n" % (dyr, sumtair[dyr]) )
            
