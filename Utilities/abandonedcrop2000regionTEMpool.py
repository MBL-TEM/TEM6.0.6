#!/usr/bin/env python

"""
#################################################################
crop2000regionTEpool.py - Program identifies cohorts that are 
  croplands during the year 2000 and then tracks these cohorts
  thru the 21st century to aggregate TEM estimated December pool 
  sizes from these cohorts regardless if they remain the same land 
  cover or not.
#################################################################

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

#  itemfname = raw_input( "Enter input filename of TEM results:\n" )
#  itemfile = open( itemfname,  'r' )

  itemfile = open( "TEMpool1500_2100.region",  'r' )

  ilulcfile = open( "lulcchrt1500_2100.region", 'r')
  
#  osumfname = raw_input( "Enter output summary filename:\n" )
#  osumfile = open( osumfname, 'w' )

  osumfile = open( "abandonedCrop2000TEMpool1500_2100region.sum", 'w' )

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

  cropPool = {}
  biofuelPool = {}
  pasturePool = {}
  youngForestPool = {}
  oldForestPool = {}
  allForestPool = {}
  grassPool = {}
  shrubPool = {}
  tundraPool = {}
  wetlandPool = {}
  desertPool = {}
  
  tstchrt = []
  abandoned = {}

# ###############################################################

  def areaWeightedMeanPool( dyr ):

      if( cropArea[dyr] > 0 ):
        cropPool[dyr] /= cropArea[dyr]
      else:
        cropPool[dyr] = 0.0
  
      if( biofuelArea[dyr] > 0 ): 	
        biofuelPool[dyr] /=  biofuelArea[dyr]
      else:
        biofuelPool[dyr] = 0.0

      if( pastureArea[dyr] > 0 ):
        pasturePool[dyr] /= pastureArea[dyr]
      else:
        pasturePool[dyr] = 0.0

      if( youngForestArea[dyr] > 0 ):
        youngForestPool[dyr] /= youngForestArea[dyr]
      else:
        youngForestPool[dyr] = 0.0

      if( oldForestArea[dyr] > 0 ):
        oldForestPool[dyr]  /= oldForestArea[dyr]
      else:
        oldForestPool[dyr] = 0.0

      if( pforsArea[dyr] > 0 ):
        allForestPool[dyr]  /= allForestArea[dyr]
      else:
        allForestPool[dyr] = 0.0

      if( grassArea[dyr] > 0 ):
        grassPool[dyr] /= grassArea[dyr]
      else:
        grassPool[dyr] = 0.0

      if( shrubArea[dyr] > 0 ):
        shrubPool[dyr] /= shrubArea[dyr]
      else:
        shrubPool[dyr] = 0.0

      if( tundraArea[dyr] > 0 ):
        tundraPool[dyr] /= tundraArea[dyr]
      else:
        tundraPool[dyr] = 0.0

      if( wetlandArea[dyr] > 0 ):
        wetlandPool[dyr] /= wetlandArea[dyr]
      else:
        wetlandPool[dyr] = 0.0

      if( desertArea[dyr] > 0 ):
        desertPool[dyr] /= desertArea[dyr] 
      else:
        desertPool[dyr] = 0.0
  	
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

  def initializePool( dyr ):
        cropPool[dyr] = 0.0
        biofuelPool[dyr] = 0.0
        pasturePool[dyr] = 0.0
        youngForestPool[dyr] = 0.0
        oldForestPool[dyr] = 0.0
        allForestPool[dyr] = 0.0
        grassPool[dyr] = 0.0
        shrubPool[dyr] = 0.0
        tundraPool[dyr] = 0.0
        wetlandPool[dyr] = 0.0
        desertPool[dyr] = 0.0


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

  def outputAggregatedPool( dyr ):
        osumfile.write( "%4d %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f %10.4f\n" % 
                        (dyr,  
                        (cropPool[dyr] * 0.000001), 
                        (biofuelPool[dyr] * 0.000001), 
                        (pasturePool[dyr] * 0.000001), 
                        (youngForestPool[dyr] * 0.000001), 
                        (oldForestPool[dyr] * 0.000001), 
                        (allForestPool[dyr] * 0.000001), 
                        (grassPool[dyr] * 0.000001), 
                        (shrubPool[dyr] * 0.000001), 
                        (tundraPool[dyr] * 0.000001), 
                        (wetlandPool[dyr] * 0.000001), 
                        (desertPool[dyr] * 0.000001)) ) 


# ##################################################################

  for year in range( initYear, (finalYear+1) ):
    initializeArea( year )
    initializePool( year )

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
#    anntotal = float( temfield[15] )
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
    dec = float( temfield[30] )
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
      if( dec <= -999999.9 ): dec = 0.0

      print col, row, year, icohrt

      if( year >= initYear and year <= finalYear ):
        if( col != lagcol or row != lagrow):
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

#         if( year == (initYear+1)
#             and lagcol == 5.0
#             and lagrow == 61.0 ):
#        print lagcol, lagrow, year, mxcohrt, tstchrt
#           exit( -1 )

        if( 1 == abandoned[(col,row,icohrt)] ):
          if( 0 == chrtVeg ):
            desertArea[year] += chrtArea
            desertPool[year] += (float( chrtArea ) * dec)

          if( 15 == chrtVeg ): 
            cropArea[year] += chrtArea
            cropPool[year] += (float( chrtArea ) * dec)

          if( 16 == chrtVeg ): 
            biofuelArea[year] += chrtArea
            biofuelPool[year] += (float( chrtArea ) * dec)

          if( 33 == chrtVeg ): 
            pastureArea[year] += chrtArea
            pasturePool[year] += (float( chrtArea ) * dec)

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
       	    allForestPool[year] += (float( chrtArea ) * dec)
        
            if( 120 > standage ):
              youngForestArea[year] += chrtArea
       	      youngForestPool[year] += (float( chrtArea ) * dec)
            else: 
              oldForestArea[year] += chrtArea
              oldForestPool[year] += (float( chrtArea ) * dec)

          if( 9 == chrtVeg or 10 == chrtVeg ):
            shrubArea[year] += chrtArea
            shrubPool[year] += (float( chrtArea ) * dec)
      
          if( 11 == chrtVeg or 12 == chrtVeg ):
            tundraArea[year] += chrtArea
            tundraPool[year] += (float( chrtArea ) * dec)
      
          if( 13 == chrtVeg 
              or 14 == chrtVeg 
              or 27 == chrtVeg 
              or 29 == chrtVeg): 
            grassArea[year] += chrtArea
            grassPool[year] += (float( chrtArea ) * dec)

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
            wetlandPool[year] += (float( chrtArea ) * dec)

#          print col, row, year, youngForestArea[year]

  itemfile.close()
  ilulcfile.close()
  
  osumfile.write( "Year       Crop    Biofuel   Pasture  YoungFor  OldForest AllForest     Grass     Shrub    Tundra   Wetland    Desert\n\n" ) 

#  for year in range( initYear, (finalYear+1) ):
#   areaWeightedMeanPool( year ):

  osumfile.write( "Area\n\n" )

  for year in range( initYear, (finalYear+1) ):
    outputAggregatedArea( year )

  osumfile.write( "\n\nPool\n\n" ) 

  for year in range( initYear, (finalYear+1) ):
    outputAggregatedPool( year )

  osumfile.close()

