#!/usr/bin/env python

"""
#################################################################
abandonedcrop2000regionTEMflux.py - Program identifies cohorts 
  that are croplands during the year 2000 and then tracks these 
  cohorts thru the 21st century to aggregate TEM estimated annual 
  fluxes from these cohorts regardless if they remain the same 
  land cover or not.
#################################################################

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

#  itemfname = raw_input( "Enter input filename of TEM results:\n" )
#  itemfile = open( itemfname,  'r' )

  itemfile = open( "TEMflux1500_2100.region",  'r' )

  ilulcfile = open( "lulcchrt1500_2100.region", 'r')
  
#  osumfname = raw_input( "Enter output summary filename:\n" )
#  osumfile = open( osumfname, 'w' )

  osumfile = open( "abandonedCrop2000TEMflux2000_2100region.sum", 'w' )

#  sfrstyear = raw_input( "Enter the initial year of the 5-year period to determine statistics:\n" )
#  initYear = int( sfrstyear )
  
  initYear = 2000

#  slstyear = raw_input( "Enter the final year of the 5-year period to determine statistics:\n" )
#  finalYear = int( slstyear )

  finalYear = 2100

  startSpinupYear = 299
  startlulcYear = 1500

  cropArea = {}
  biofuelArea = {}
  pastureArea = {}
  youngForestArea = {}
  oldForestArea = {}
  allForestArea = {}
  grassArea = {}
  shrubArea = {}
  tundraArea = {}
  wetlandArea = {}
  desertArea = {}

  cropFlux = {}
  biofuelFlux = {}
  pastureFlux = {}
  youngForestFlux = {}
  oldForestFlux = {}
  allForestFlux = {}
  grassFlux = {}
  shrubFlux = {}
  tundraFlux = {}
  wetlandFlux = {}
  desertFlux = {}
  
  tstchrt = []
  abandoned = {}

# ###############################################################

  def areaWeightedMeanFlux( dyr ):

      if( cropArea[dyr] > 0 ):
        cropFlux[dyr] /= cropArea[dyr]
      else:
        cropFlux[dyr] = 0.0
  
      if( biofuelArea[dyr] > 0 ): 	
        biofuelFlux[dyr] /=  biofuelArea[dyr]
      else:
        biofuelFlux[dyr] = 0.0

      if( pastureArea[dyr] > 0 ):
        pastureFlux[dyr] /= pastureArea[dyr]
      else:
        pastureFlux[dyr] = 0.0

      if( youngForestArea[dyr] > 0 ):
        youngForestFlux[dyr] /= youngForestArea[dyr]
      else:
        youngForestFlux[dyr] = 0.0

      if( oldForestArea[dyr] > 0 ):
        oldForestFlux[dyr]  /= oldForestArea[dyr]
      else:
        oldForestFlux[dyr] = 0.0

      if( pforsArea[dyr] > 0 ):
        allForestFlux[dyr]  /= allForestArea[dyr]
      else:
        allForestFlux[dyr] = 0.0

      if( grassArea[dyr] > 0 ):
        grassFlux[dyr] /= grassArea[dyr]
      else:
        grassFlux[dyr] = 0.0

      if( shrubArea[dyr] > 0 ):
        shrubFlux[dyr] /= shrubArea[dyr]
      else:
        shrubFlux[dyr] = 0.0

      if( tundraArea[dyr] > 0 ):
        tundraFlux[dyr] /= tundraArea[dyr]
      else:
        tundraFlux[dyr] = 0.0

      if( wetlandArea[dyr] > 0 ):
        wetlandFlux[dyr] /= wetlandArea[dyr]
      else:
        wetlandFlux[dyr] = 0.0

      if( desertArea[dyr] > 0 ):
        desertFlux[dyr] /= desertArea[dyr] 
      else:
        desertFlux[dyr] = 0.0
  	
# ##################################################################

  def initializeArea( dyr ):
        cropArea[dyr] = 0
        biofuelArea[dyr] = 0
        pastureArea[dyr] = 0
        youngForestArea[dyr] = 0
        oldForestArea[dyr] = 0
        allForestArea[dyr] = 0
        grassArea[dyr] = 0
        shrubArea[dyr] = 0
        tundraArea[dyr] = 0
        wetlandArea[dyr] = 0
        desertArea[dyr] = 0


# ##################################################################

  def initializeFlux( dyr ):
        cropFlux[dyr] = 0.0
        biofuelFlux[dyr] = 0.0
        pastureFlux[dyr] = 0.0
        youngForestFlux[dyr] = 0.0
        oldForestFlux[dyr] = 0.0
        allForestFlux[dyr] = 0.0
        grassFlux[dyr] = 0.0
        shrubFlux[dyr] = 0.0
        tundraFlux[dyr] = 0.0
        wetlandFlux[dyr] = 0.0
        desertFlux[dyr] = 0.0


# ##################################################################

  def outputAggregatedArea( dyr ):
        osumfile.write( "%4d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d %10d\n" % 
                        (dyr,  
                        cropArea[dyr], 
                        biofuelArea[dyr], 
                        pastureArea[dyr], 
                        youngForestArea[dyr], 
                        oldForestArea[dyr], 
                        allForestArea[dyr], 
                        grassArea[dyr], 
                        shrubArea[dyr], 
                        tundraArea[dyr], 
                        wetlandArea[dyr], 
                        desertArea[dyr]) ) 


# ##################################################################

  def outputAggregatedFlux( dyr ):
        osumfile.write( "%4d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n" % 
                        (dyr,  
                        (cropFlux[dyr] * 0.000001), 
                        (biofuelFlux[dyr] * 0.000001), 
                        (pastureFlux[dyr] * 0.000001), 
                        (youngForestFlux[dyr] * 0.000001), 
                        (oldForestFlux[dyr] * 0.000001), 
                        (allForestFlux[dyr] * 0.000001), 
                        (grassFlux[dyr] * 0.000001), 
                        (shrubFlux[dyr] * 0.000001), 
                        (tundraFlux[dyr] * 0.000001), 
                        (wetlandFlux[dyr] * 0.000001), 
                        (desertFlux[dyr] * 0.000001)) ) 


# ##################################################################

  for year in range( initYear, (finalYear+1) ):
    initializeArea( year )
    initializeFlux( year )

  lagcol = -999.9
  lagrow = -999.9
  
  for temline in itemfile.xreadlines():
 
#   Get TEM data
    temfield = temline.split( "," )

    col = float( temfield[0] )
    row = float( temfield[1] )
#    varname = temfield[2]
    icohrt = int( temfield[3] )
    standage = int( temfield[4] )
    potveg = int(temfield[5] )
    chrtVeg = int( temfield[6] )
#    subtype = int( temfield[7] )
#    cmnt = int( temfield[8] )
#    lcstate = int( temfield[9] )
#    psiplusc = float( temfield[10] )
#    qlcon = int( temfield[11] )
#    landarea = int( temfield[12] )
    chrtArea = int( temfield[13] )
    year = int( temfield[14] )
    anntotal = float( temfield[15] )
#    annmax = float( temfield[16] )
#    annave = float( temfield[17] )
#    annmin = float( temfield[18] )
#    jan = float( temfield[19] )
#    feb = float( temfield[20] )
#    may = float( temfield[21] )
#    apr = float( temfield[22] )
#    may = float( temfield[23] )
#    jun = float( temfield[24] )
#    jul = float( temfield[25] )
#    aug = float( temfield[26] )
#    sep = float( temfield[27] )
#    octbr = float( temfield[28] )
#    nov = float( temfield[29] )
#    dec = float( temfield[30] )
#    region = temfield[31][1:-1]

    if( year == startSpinupYear ):
      ilulcfile.readline()

    if( year >= startlulcYear):
      lulcline =  ilulcfile.readline()
      lulcfield = lulcline.split( "," )

#     Get LULC data

      lulccol = float( lulcfield[0] )
      lulcrow = float( lulcfield[1] )
#      varname = lulcfield[2]
      lulcyear = int( lulcfield[3] )
      lulcchrt = int( lulcfield[4] )
      lulcsrcchrt = int( lulcfield[5] )
      lulcstandage = int( lulcfield[6] )
#      lulccarea = int( lulcfield[7] )
      lulcpveg = int(lulcfield[8] )
      lulcVeg = int( lulcfield[9] )
#      lulcsubtype = int( lulcfield[10] )
#      lulcagstate = int( lulcfield[11] )
#      lulcagprevstate = int( lulcfield[12] )
#      lulctillflag = int( lulcfield[13] )
#      lulcfertflag = int( lulcfield[14] )
#      lulcirrgflag = int( lulcfield[15] )
#      lulcdisturbflag = int( lulcfield[16] )
#      lulcdisturbmonth = int( lulcfield[17] )
#      lulcFRI = int( lulcfield[18] )
#      lulcslashpar = float( lulcfield[19] )
#      lulcvconvert = float( lulcfield[20] )
#      lulcprod10par = float( lulcfield[21] )
#      lulcprod100par = float( lulcfield[22] )
#      lulcvrespar = float( lulcfield[23] )
#      lulcsconvert = float( lulcfield[24] )
#      lulcregion = lulcfield[25]


      if( col != lulccol
        or row != lulcrow
        or year != lulcyear
        or icohrt != lulcchrt
        or standage != lulcstandage
        or potveg != lulcpveg
        or chrtVeg != lulcVeg ):
        print "LULC data not co-registered with TEM data"
        print ("TEM col = %f  row = %f year = %d icohrt = %d standage = %d potveg = %d chrtveg = %d" % 
               (col, 
                row, 
                year,
                icohrt,
                standage,
                potveg,
                chrtVeg) )

        print ("LULC col = %f  row = %f year = %d icohrt = %d standage = %d potveg = %d chrtveg = %d" % 
               (lulccol, 
                lulcrow, 
                lulcyear,
                lulcchrt,
                lulcstandage,
                lulcpveg,
                lulcVeg) )
        exit( -1 )  

#   Replace missing value with zero
      if( anntotal <= -999999.9 ): anntotal = 0.0

#      print col, row, year
      
      
      if( year >= initYear and year <= finalYear ):
        if( col != lagcol or row != lagrow ):
          tstchrt = []
          mxcohrt = 0
          lagcol = col
          lagrow = row

        if( initYear == year ):
          mxcohrt += 1
          if( 15 == chrtVeg ):
            tstchrt.append( icohrt )
            abandoned[(col,row,icohrt)] = 1
          else:
            abandoned[(col,row,icohrt)] = 0
        else:
          if( icohrt > mxcohrt
              and  (icohrt in tstchrt) == 0 ):
            if( (lulcsrcchrt in tstchrt) == 1 ):
              tstchrt.append( icohrt )
              abandoned[(col,row,icohrt)] = 1
            else:
              abandoned[(col,row,icohrt)] = 0

        if( 1 == abandoned[(col,row,icohrt)] ):
          if( 0 == chrtVeg ):
            desertArea[year] += chrtArea
            desertFlux[year] += (float( chrtArea ) * anntotal)

          if( 15 == chrtVeg ): 
            cropArea[year] += chrtArea
            cropFlux[year] += (float( chrtArea ) * anntotal)

          if( 16 == chrtVeg ): 
            biofuelArea[year] += chrtArea
            biofuelFlux[year] += (float( chrtArea ) * anntotal)

          if( 33 == chrtVeg ): 
            pastureArea[year] += chrtArea
            pastureFlux[year] += (float( chrtArea ) * anntotal)

          if( 1 == chrtVeg 
              or 2 == chrtVeg 
              or 3 == chrtVeg 
              or 4 == chrtVeg 
              or 5 == chrtVeg  
              or 6 == chrtVeg 
              or 7 == chrtVeg  
              or 8 == chrtVeg 
              or 26 == chrtVeg 
              or 28 == chrtVeg):

            allForestArea[year] += chrtArea
       	    allForestFlux[year] += (float( chrtArea ) * anntotal)
        
            if( 120 > standage ):
              youngForestArea[year] += chrtArea
       	      youngForestFlux[year] += (float( chrtArea ) * anntotal)
            else: 
              oldForestArea[year] += chrtArea
              oldForestFlux[year] += (float( chrtArea ) * anntotal)

          if( 9 == chrtVeg or 10 == chrtVeg ):
            shrubArea[year] += chrtArea
            shrubFlux[year] += (float( chrtArea ) * anntotal)
      
          if( 11 == chrtVeg or 12 == chrtVeg ):
            tundraArea[year] += chrtArea
            tundraFlux[year] += (float( chrtArea ) * anntotal)
      
          if( 13 == chrtVeg 
              or 14 == chrtVeg 
              or 27 == chrtVeg 
              or 29 == chrtVeg): 
            grassArea[year] += chrtArea
            grassFlux[year] += (float( chrtArea ) * anntotal)

          if( 17 == chrtVeg 
              or 18 == chrtVeg 
              or 19 == chrtVeg 
              or 20 == chrtVeg 
              or 21 == chrtVeg 
              or 22 == chrtVeg 
              or 23 == chrtVeg 
              or 24 == chrtVeg 
              or 25 == chrtVeg ): 

            wetlandArea[year] += chrtArea
            wetlandFlux[year] += (float( chrtArea ) * anntotal)

          print col, row, year, mxcohrt, youngForestArea[year]

  itemfile.close()
  ilulcfile.close()
  
  osumfile.write( "Year       Crop    Biofuel   Pasture  YoungFor  OldForest    AllForest     Grass     Shrub    Tundra   Wetland    Desert\n\n" ) 

  osumfile.write( "Area\n\n" )

  for year in range( initYear, (finalYear+1) ):
    outputAggregatedArea( year )

  osumfile.write( "\n\nFlux\n\n" ) 

  for year in range( initYear, (finalYear+1) ):
    outputAggregatedFlux( year )

  osumfile.close()

