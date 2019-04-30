#!/usr/bin/env python

"""
##################################################################
Program: sumIGSMVEGregion.py 

Description: Program sums the land area for each land cover 
             during each year for a specified time period.
             Land cover based on IGSMVEG classification described 
             in Schlosser et al. (2007) - see Table 5 on page 10).


Reference: Schlosser, C. A., D. Kicklighter and A. Sokolov (2007) 
             A Global Land System Framework for Integrated Climate
             -Change Assessments. MIT Joint Program on Science and 
             Policy of Global Change Report No. 147. Massachusetts 
             Institute of Technology, Cambridge, Massachusetts. 
             (see also 
             https://globalchange.mit.edu/publication/15553).
                          
##################################################################

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
  import sys

#  tststate = sys.argv[1] 

  imxchrtfile = open( 'mxcohrts1500_2100.region', 'r' )
  ilulcfile = open( 'lulcchrt1500_2100.region', 'r' )
  osumfile = open( 'lulcchrt1500_2100region.sum', 'w' )

  tststate = ' All'
  tstwshed = ' All'

  firstyear = 1499
  lastyear = 2100

  numyears = lastyear - firstyear + 1

  oldforest = {}
  youngforest = {}
  shrub = {}
  grass = {}
  tundra = {}
  wetland = {}
  lake = {}
  bare = {}
  crop = {}
  pasture = {}
  urban = {}
  treefarm = {}
  suburbia = {}
  urbasph = {}
  urblwn = {}
  urbtree = {}
  subrbasph = {}
  subrblwn = {}
  subrbtree = {}
  totarea = {}

  for dyr in range( numyears ):
    oldforest[dyr]  = 0
    youngforest[dyr]  = 0
    shrub[dyr] = 0
    grass[dyr] = 0
    tundra[dyr] = 0
    wetland[dyr] = 0
    lake[dyr] = 0
    bare[dyr] = 0
    crop[dyr] = 0
    pasture[dyr] = 0
    urban[dyr] = 0
    treefarm[dyr] = 0
    suburbia[dyr] = 0
    urbasph[dyr] = 0
    urblwn[dyr] = 0
    urbtree[dyr] = 0
    subrbasph[dyr] = 0
    subrblwn[dyr] = 0
    subrbtree[dyr] = 0
    totarea[dyr] = 0

  for line in imxchrtfile.readlines():
    field = line.split( "," ) 

    col = float( field[0] )
    row = float( field[1] )
#    varname = field[2]
    carea = int( field[3] )
    year = int( field[4] )
    total = int( field[5] )
    natchrts = int( field[6] )
    state = field[7][:-1]

    for ichrt in range( total ): 
      line = ilulcfile.readline()
      field = line.split( "," ) 

      lulccol = float( field[0] )
      lulcrow = float( field[1] )
#      varname = field[2]
#      year = field[3]
#      icohort = field[4]
#      isrccohort = field[5]
      standage = int( field[6] )
      chrtarea = int( field[7] )
#      potveg = field[8]
      currentveg = int( field[9] )
#      subtype = field[10]
      agstate = int( field[11] )
#      agprevstate = field[12]
#      tillflag = field[13]
#      fertflag = field[14]
#      irrgflag = field[15]
#      disturbflag = field[16]
#      disturbmonth = field[17]
#      FRI = field[18]
#      slashpar = field[19]
#      vconvert = field[20]
#      prod10par = field[21]
#      prod100par = field[22]
#      vrespar = field[23]
#      sconvert = field[24]
      watershed = field[25][:-1]

      if( lulccol != col and lulcrow != row ):
        print "MXCOHRTS file and LULCCHRT file are not co-registered!"
        print "MXCOHRTS LON = ", col, "LAT = ", row
        print "LULCCHRT LON = ", lulccol, "LAT = ", lulcrow

      if( (' All' == tststate or tststate == state) 
          and (' All' == tstwshed or tstwshed == watershed) ): 

        if( lastyear == firstyear ): dyr = 0
        else: dyr = year - firstyear

        totarea[dyr] += chrtarea

        if( 0 == agstate or 6 == agstate or 7 == agstate ):
          if( 0 == currentveg ): bare[dyr] += chrtarea 

          if( 1 == currentveg 
              or 2 == currentveg
              or 3 == currentveg
              or 4 == currentveg
              or 5 == currentveg
              or 6 == currentveg
              or 7 == currentveg
              or 8 == currentveg
              or 26 == currentveg
              or 28 == currentveg ): 
            if( 120 <= standage ):
              oldforest[dyr] += chrtarea 
            else:
              youngforest[dyr] += chrtarea 

          if( 9 == currentveg 
              or 10 == currentveg): 
            shrub[dyr] += chrtarea 

          if( 11 == currentveg
              or 12 == currentveg):
            tundra[dyr] += chrtarea

          if( 13 == currentveg
              or 14 == currentveg
              or 27 == currentveg
              or 29 == currentveg ): 
            grass[dyr] += chrtarea 

          if( 17 == currentveg 
              or 18 == currentveg
              or 19 == currentveg
              or 20 == currentveg
              or 21 == currentveg
              or 22 == currentveg
              or 23 == currentveg
              or 24 == currentveg
              or 25 == currentveg ): 
            wetland[dyr] += chrtarea 

          if( 31 == currentveg ): lake[dyr] += chrtarea 


        if( 1 == agstate ):
          crop[dyr] += chrtarea

        if( 2 == agstate ):
          pasture[dyr] += chrtarea

        if( 3 == agstate ):
          urban[dyr] += chrtarea

          if( 1 == currentveg
              or 7 == currentveg ):
            urbtree[dyr] += chrtarea

          if( 34 == currentveg ): urblwn[dyr] += chrtarea

          if( 35 == currentveg ): urbasph[dyr] += chrtarea       

        if( 4 == agstate ):
          treefarm[dyr] += chrtarea

        if( 5 == agstate ):
          suburbia[dyr] += chrtarea

          if( 1 == currentveg
              or 7 == currentveg ):
            subrbtree[dyr] += chrtarea

          if( 34 == currentveg ): subrblwn[dyr] += chrtarea

          if( 35 == currentveg ): subrbasph[dyr] += chrtarea       

      
  osumfile.write( "Distribution of Land covers (Hectares) for State = %s Watershed = %s\n" % 
                  (tststate,
                  tstwshed) )
  osumfile.write( "Year OldForest YoungForest      Shrub      Grass     Tundra      Wetland      Lakes       Bare      Crops   Pastures  TreeFarms UrbanTotal UrbnAsphlt  UrbanLawn UrbanTrees SubrbTotal SubrbAspht SuburbLawn SubrbTrees      Total\n" )

  for dyr in range( numyears ):
    osumfile.write( "%4d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d\n" %
                    ((firstyear+dyr),
                    oldforest[dyr],
                    youngforest[dyr],
                    shrub[dyr], 
                    grass[dyr], 
                    tundra[dyr],
                    wetland[dyr], 
                    lake[dyr], 
                    bare[dyr], 
                    crop[dyr], 
                    pasture[dyr], 
                    treefarm[dyr],
                    urban[dyr],  
                    urbasph[dyr],
                    urblwn[dyr], 
                    urbtree[dyr], 
                    suburbia[dyr], 
                    subrbasph[dyr], 
                    subrblwn[dyr], 
                    subrbtree[dyr],
                    totarea[dyr]) ) 
  


