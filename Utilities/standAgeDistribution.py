#!/usr/bin/env python

"""
#################################################################
Program: standAgeDistribution.py - Develops histogram of stand 
  ages based on area for a specified year
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

*****************************************************************
*****************************************************************
"""


if __name__ == '__main__':

#  ilulcfname = raw_input( "Enter input filename of LULC file:\n" )
#  ilulcfile = open( ilulcfname,  'r' )

  ilulcfile = open( "lulcchrtRCP4.5_1500_2100.region", 'r')
  
#  osumfname = raw_input( "Enter output summary filename:\n" )
#  osumfile = open( osumfname, 'w' )

  osumfile = open( "standAgeDistribution2000RCP4.5region,sum", 'w' )

#  ststyear = raw_input( "Enter the year to determine histogram:\n" )
#  tstYear = int( ststyear )
  
  tstYear = 2000


  age0to10yearArea = {}
  age11to20yearArea = {}
  age21to30yearArea = {}
  age31to40yearArea = {}
  age41to50yearArea = {}
  age51to60yearArea = {}
  age61to70yearArea = {}
  age71to80yearArea = {}
  age81to90yearArea = {}
  age91to100yearArea = {}
  age101to110yearArea = {}
  age111to120yearArea = {}
  age121to130yearArea = {}
  age131to140yearArea = {}
  age141to150yearArea = {}
  age151to160yearArea = {}
  age161to170yearArea = {}
  age171to180yearArea = {}
  age181to190yearArea = {}
  age191to200yearArea = {}
  age201to210yearArea = {}
  age211to220yearArea = {}
  age221to230yearArea = {}
  age231to240yearArea = {}
  age241to250yearArea = {}
  age251to260yearArea = {}
  age261to270yearArea = {}
  age271to280yearArea = {}
  age281to290yearArea = {}
  age291to300yearArea = {}
  age301to310yearArea = {}
  age311to320yearArea = {}
  age321to330yearArea = {}
  age331to340yearArea = {}
  age341to350yearArea = {}
  agemore350yearArea = {}


# ###############################################################

  def initializeArea( dveg ):
    age0to10yearArea[dveg] = 0
    age11to20yearArea[dveg] = 0
    age21to30yearArea[dveg] = 0
    age31to40yearArea[dveg] = 0
    age41to50yearArea[dveg] = 0
    age51to60yearArea[dveg] = 0
    age61to70yearArea[dveg] = 0
    age71to80yearArea[dveg] = 0
    age81to90yearArea[dveg] = 0
    age91to100yearArea[dveg] = 0
    age101to110yearArea[dveg] = 0
    age111to120yearArea[dveg] = 0
    age121to130yearArea[dveg] = 0
    age131to140yearArea[dveg] = 0
    age141to150yearArea[dveg] = 0
    age151to160yearArea[dveg] = 0
    age161to170yearArea[dveg] = 0
    age171to180yearArea[dveg] = 0
    age181to190yearArea[dveg] = 0
    age191to200yearArea[dveg] = 0
    age201to210yearArea[dveg] = 0
    age211to220yearArea[dveg] = 0
    age221to230yearArea[dveg] = 0
    age231to240yearArea[dveg] = 0
    age241to250yearArea[dveg] = 0
    age251to260yearArea[dveg] = 0
    age261to270yearArea[dveg] = 0
    age271to280yearArea[dveg] = 0
    age281to290yearArea[dveg] = 0
    age291to300yearArea[dveg] = 0
    age301to310yearArea[dveg] = 0
    age311to320yearArea[dveg] = 0
    age321to330yearArea[dveg] = 0
    age331to340yearArea[dveg] = 0
    age341to350yearArea[dveg] = 0
    agemore350yearArea[dveg] = 0



# ##################################################################

  def outputAggregatedArea( ):
        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" % 
                        (5,  
                         age0to10yearArea[1],
                         age0to10yearArea[2],
                         age0to10yearArea[3],
                         age0to10yearArea[4],
                         age0to10yearArea[5],
                         age0to10yearArea[6],
                         age0to10yearArea[7],
                         age0to10yearArea[8]) ) 

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (15,
                         age11to20yearArea[1],
                         age11to20yearArea[2],
                         age11to20yearArea[3],
                         age11to20yearArea[4],
                         age11to20yearArea[5],
                         age11to20yearArea[6],
                         age11to20yearArea[7],
                         age11to20yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (25,
                         age21to30yearArea[1],
                         age21to30yearArea[2],
                         age21to30yearArea[3],
                         age21to30yearArea[4],
                         age21to30yearArea[5],
                         age21to30yearArea[6],
                         age21to30yearArea[7],
                         age21to30yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (35,
                         age31to40yearArea[1],
                         age31to40yearArea[2],
                         age31to40yearArea[3],
                         age31to40yearArea[4],
                         age31to40yearArea[5],
                         age31to40yearArea[6],
                         age31to40yearArea[7],
                         age31to40yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (45,
                         age41to50yearArea[1],
                         age41to50yearArea[2],
                         age41to50yearArea[3],
                         age41to50yearArea[4],
                         age41to50yearArea[5],
                         age41to50yearArea[6],
                         age41to50yearArea[7],
                         age41to50yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (55,
                         age51to60yearArea[1],
                         age51to60yearArea[2],
                         age51to60yearArea[3],
                         age51to60yearArea[4],
                         age51to60yearArea[5],
                         age51to60yearArea[6],
                         age51to60yearArea[7],
                         age51to60yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (65,
                         age61to70yearArea[1],
                         age61to70yearArea[2],
                         age61to70yearArea[3],
                         age61to70yearArea[4],
                         age61to70yearArea[5],
                         age61to70yearArea[6],
                         age61to70yearArea[7],
                         age61to70yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (75,
                         age71to80yearArea[1],
                         age71to80yearArea[2],
                         age71to80yearArea[3],
                         age71to80yearArea[4],
                         age71to80yearArea[5],
                         age71to80yearArea[6],
                         age71to80yearArea[7],
                         age71to80yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (85,
                         age81to90yearArea[1],
                         age81to90yearArea[2],
                         age81to90yearArea[3],
                         age81to90yearArea[4],
                         age81to90yearArea[5],
                         age81to90yearArea[6],
                         age81to90yearArea[7],
                         age81to90yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (95,
                         age91to100yearArea[1],
                         age91to100yearArea[2],
                         age91to100yearArea[3],
                         age91to100yearArea[4],
                         age91to100yearArea[5],
                         age91to100yearArea[6],
                         age91to100yearArea[7],
                         age91to100yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (105,
                         age101to110yearArea[1],
                         age101to110yearArea[2],
                         age101to110yearArea[3],
                         age101to110yearArea[4],
                         age101to110yearArea[5],
                         age101to110yearArea[6],
                         age101to110yearArea[7],
                         age101to110yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (115,
                         age111to120yearArea[1],
                         age111to120yearArea[2],
                         age111to120yearArea[3],
                         age111to120yearArea[4],
                         age111to120yearArea[5],
                         age111to120yearArea[6],
                         age111to120yearArea[7],
                         age111to120yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (125,
                         age121to130yearArea[1],
                         age121to130yearArea[2],
                         age121to130yearArea[3],
                         age121to130yearArea[4],
                         age121to130yearArea[5],
                         age121to130yearArea[6],
                         age121to130yearArea[7],
                         age121to130yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (135,
                         age131to140yearArea[1],
                         age131to140yearArea[2],
                         age131to140yearArea[3],
                         age131to140yearArea[4],
                         age131to140yearArea[5],
                         age131to140yearArea[6],
                         age131to140yearArea[7],
                         age131to140yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (145,
                         age141to150yearArea[1],
                         age141to150yearArea[2],
                         age141to150yearArea[3],
                         age141to150yearArea[4],
                         age141to150yearArea[5],
                         age141to150yearArea[6],
                         age141to150yearArea[7],
                         age141to150yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (155,
                         age151to160yearArea[1],
                         age151to160yearArea[2],
                         age151to160yearArea[3],
                         age151to160yearArea[4],
                         age151to160yearArea[5],
                         age151to160yearArea[6],
                         age151to160yearArea[7],
                         age151to160yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (165,
                         age161to170yearArea[1],
                         age161to170yearArea[2],
                         age161to170yearArea[3],
                         age161to170yearArea[4],
                         age161to170yearArea[5],
                         age161to170yearArea[6],
                         age161to170yearArea[7],
                         age161to170yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (175,
                         age171to180yearArea[1],
                         age171to180yearArea[2],
                         age171to180yearArea[3],
                         age171to180yearArea[4],
                         age171to180yearArea[5],
                         age171to180yearArea[6],
                         age171to180yearArea[7],
                         age171to180yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (185,
                         age181to190yearArea[1],
                         age181to190yearArea[2],
                         age181to190yearArea[3],
                         age181to190yearArea[4],
                         age181to190yearArea[5],
                         age181to190yearArea[6],
                         age181to190yearArea[7],
                         age181to190yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (195,
                         age191to200yearArea[1],
                         age191to200yearArea[2],
                         age191to200yearArea[3],
                         age191to200yearArea[4],
                         age191to200yearArea[5],
                         age191to200yearArea[6],
                         age191to200yearArea[7],
                         age191to200yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (205,
                         age201to210yearArea[1],
                         age201to210yearArea[2],
                         age201to210yearArea[3],
                         age201to210yearArea[4],
                         age201to210yearArea[5],
                         age201to210yearArea[6],
                         age201to210yearArea[7],
                         age201to210yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (215,
                         age211to220yearArea[1],
                         age211to220yearArea[2],
                         age211to220yearArea[3],
                         age211to220yearArea[4],
                         age211to220yearArea[5],
                         age211to220yearArea[6],
                         age211to220yearArea[7],
                         age211to220yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (225,
                         age221to230yearArea[1],
                         age221to230yearArea[2],
                         age221to230yearArea[3],
                         age221to230yearArea[4],
                         age221to230yearArea[5],
                         age221to230yearArea[6],
                         age221to230yearArea[7],
                         age221to230yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (235,
                         age231to240yearArea[1],
                         age231to240yearArea[2],
                         age231to240yearArea[3],
                         age231to240yearArea[4],
                         age231to240yearArea[5],
                         age231to240yearArea[6],
                         age231to240yearArea[7],
                         age231to240yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (245,
                         age241to250yearArea[1],
                         age241to250yearArea[2],
                         age241to250yearArea[3],
                         age241to250yearArea[4],
                         age241to250yearArea[5],
                         age241to250yearArea[6],
                         age241to250yearArea[7],
                         age241to250yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (255,
                         age251to260yearArea[1],
                         age251to260yearArea[2],
                         age251to260yearArea[3],
                         age251to260yearArea[4],
                         age251to260yearArea[5],
                         age251to260yearArea[6],
                         age251to260yearArea[7],
                         age251to260yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (265,
                         age261to270yearArea[1],
                         age261to270yearArea[2],
                         age261to270yearArea[3],
                         age261to270yearArea[4],
                         age261to270yearArea[5],
                         age261to270yearArea[6],
                         age261to270yearArea[7],
                         age261to270yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (275,
                         age271to280yearArea[1],
                         age271to280yearArea[2],
                         age271to280yearArea[3],
                         age271to280yearArea[4],
                         age271to280yearArea[5],
                         age271to280yearArea[6],
                         age271to280yearArea[7],
                         age271to280yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (285,
                         age281to290yearArea[1],
                         age281to290yearArea[2],
                         age281to290yearArea[3],
                         age281to290yearArea[4],
                         age281to290yearArea[5],
                         age281to290yearArea[6],
                         age281to290yearArea[7],
                         age281to290yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (295,
                         age291to300yearArea[1],
                         age291to300yearArea[2],
                         age291to300yearArea[3],
                         age291to300yearArea[4],
                         age291to300yearArea[5],
                         age291to300yearArea[6],
                         age291to300yearArea[7],
                         age291to300yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (305,
                         age301to310yearArea[1],
                         age301to310yearArea[2],
                         age301to310yearArea[3],
                         age301to310yearArea[4],
                         age301to310yearArea[5],
                         age301to310yearArea[6],
                         age301to310yearArea[7],
                         age301to310yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (315,
                         age311to320yearArea[1],
                         age311to320yearArea[2],
                         age311to320yearArea[3],
                         age311to320yearArea[4],
                         age311to320yearArea[5],
                         age311to320yearArea[6],
                         age311to320yearArea[7],
                         age311to320yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (325,
                         age321to330yearArea[1],
                         age321to330yearArea[2],
                         age321to330yearArea[3],
                         age321to330yearArea[4],
                         age321to330yearArea[5],
                         age321to330yearArea[6],
                         age321to330yearArea[7],
                         age321to330yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (335,
                         age331to340yearArea[1],
                         age331to340yearArea[2],
                         age331to340yearArea[3],
                         age331to340yearArea[4],
                         age331to340yearArea[5],
                         age331to340yearArea[6],
                         age331to340yearArea[7],
                         age331to340yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (345,
                         age341to350yearArea[1],
                         age341to350yearArea[2],
                         age341to350yearArea[3],
                         age341to350yearArea[4],
                         age341to350yearArea[5],
                         age341to350yearArea[6],
                         age341to350yearArea[7],
                         age341to350yearArea[8]) )

        osumfile.write( "%4d,%10d,%10d,%10d,%10d,%10d,%10d,%10d,%10d\n" %
                        (350,
                         agemore350yearArea[1],
                         agemore350yearArea[2],
                         agemore350yearArea[3],
                         agemore350yearArea[4],
                         agemore350yearArea[5],
                         agemore350yearArea[6],
                         agemore350yearArea[7],
                         agemore350yearArea[8]) )


# ##################################################################

  for dveg in range( 1, 9 ):
    initializeArea( dveg )
 
  
  for lulcline in ilulcfile.xreadlines():
    lulcfield = lulcline.split( "," )

#   Get LULC data

#    col = float( lulcfield[0] )
#    row = float( lulcfield[1] )
#    varname = lulcfield[2]
    year = int( lulcfield[3] )
#    chrt = int( lulcfield[4] )
#    srcchrt = int( lulcfield[5] )
    standage = int( lulcfield[6] )
    carea = int( lulcfield[7] )
#    potveg = int(lulcfield[8] )
    curveg = int( lulcfield[9] )
#    subtype = int( lulcfield[10] )
#    agstate = int( lulcfield[11] )
#    agprevstate = int( lulcfield[12] )
#    tillflag = int( lulcfield[13] )
#    fertflag = int( lulcfield[14] )
#    irrgflag = int( lulcfield[15] )
#    disturbflag = int( lulcfield[16] )
#    disturbmonth = int( lulcfield[17] )
#    FRI = int( lulcfield[18] )
#    slashpar = float( lulcfield[19] )
#    vconvert = float( lulcfield[20] )
#    prod10par = float( lulcfield[21] )
#    prod100par = float( lulcfield[22] )
#    vrespar = float( lulcfield[23] )
#    sconvert = float( lulcfield[24] )
#    region = lulcfield[25]



    if( (year == tstYear) 
        and (1 == curveg
        or 2 == curveg
        or 3 == curveg
        or 4 == curveg
        or 5 == curveg
        or 6 == curveg
        or 7 == curveg
       or 8 == curveg) ):

#      print year, curveg, standage, carea
       
      if( standage <= 10 ): 
        age0to10yearArea[curveg] += carea
      elif( standage > 10 and standage <= 20 ):
        age11to20yearArea[curveg] += carea
      elif( standage > 20 and standage <= 30 ):
        age21to30yearArea[curveg] += carea
      elif( standage > 30 and standage <= 40 ):
        age31to40yearArea[curveg] += carea
      elif( standage > 40 and standage <= 50 ):
        age41to50yearArea[curveg] += carea
      elif( standage > 50 and standage <= 60 ):
        age51to60yearArea[curveg] += carea
      elif( standage > 60 and standage <= 70 ):
        age61to70yearArea[curveg] += carea
      elif( standage > 70 and standage <= 80 ):
        age71to80yearArea[curveg] += carea
      elif( standage > 80 and standage <= 90 ):
        age81to90yearArea[curveg] += carea
      elif( standage > 90 and standage <= 100 ):
        age91to100yearArea[curveg] += carea
      elif( standage > 100 and standage <= 110 ):
        age101to110yearArea[curveg] += carea
      elif( standage > 110 and standage <= 120 ):
        age111to120yearArea[curveg] += carea
      elif( standage > 120 and standage <= 130 ):
        age121to130yearArea[curveg] += carea
      elif( standage > 130 and standage <= 140 ):
        age131to140yearArea[curveg] += carea
      elif( standage > 140 and standage <= 150 ):
        age141to150yearArea[curveg] += carea
      elif( standage > 150 and standage <= 160 ):
        age151to160yearArea[curveg] += carea
      elif( standage > 160 and standage <= 170 ):
        age161to170yearArea[curveg] += carea
      elif( standage > 170 and standage <= 180 ):
        age171to180yearArea[curveg] += carea
      elif( standage > 180 and standage <= 190 ):
        age181to190yearArea[curveg] += carea
      elif( standage > 190 and standage <= 200 ):
        age191to200yearArea[curveg] += carea
      elif( standage > 200 and standage <= 210 ):
        age201to210yearArea[curveg] += carea
      elif( standage > 210 and standage <= 220 ):
        age211to220yearArea[curveg] += carea
      elif( standage > 220 and standage <= 230 ):
        age221to230yearArea[curveg] += carea
      elif( standage > 230 and standage <= 240 ):
        age231to240yearArea[curveg] += carea
      elif( standage > 240 and standage <= 250 ):
        age241to250yearArea[curveg] += carea
      elif( standage > 250 and standage <= 260 ):
        age251to260yearArea[curveg] += carea
      elif( standage > 260 and standage <= 270 ):
        age261to270yearArea[curveg] += carea
      elif( standage > 270 and standage <= 280 ):
        age271to280yearArea[curveg] += carea
      elif( standage > 280 and standage <= 290 ):
        age281to290yearArea[curveg] += carea
      elif( standage > 290 and standage <= 300 ):
        age291to300yearArea[curveg] += carea
      elif( standage > 300 and standage <= 310 ):
        age301to310yearArea[curveg] += carea
      elif( standage > 310 and standage <= 320 ):
        age311to320yearArea[curveg] += carea
      elif( standage > 320 and standage <= 330 ):
        age321to330yearArea[curveg] += carea
      elif( standage > 330 and standage <= 340 ):
        age331to340yearArea[curveg] += carea
      elif( standage > 340 and standage <= 350 ):
        age341to350yearArea[curveg] += carea
      else:
        agemore350yearArea[curveg] += carea
    
  ilulcfile.close()
  
  osumfile.write( "Year  IGSMVEG01  IGSMVEG02  IGSMVEG03  IGSMVEG04  IGSMVEG05  IGSMVEG06  IGSMVEG07  IGSMVEG08\n\n" ) 

  outputAggregatedArea()

  osumfile.close()

