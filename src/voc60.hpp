/* **************************************************************
*****************************************************************
VOC60.HPP - describes components comprising inorganic nitrogen

Copyright © 2018.  The Marine Biological Laboratory. All Rights 
Reserved.  

Full license notice can be found in the LICENSE file at 
<https://github.com/MBL-TEM/TEM6.0.6/> 

*****************************************************************
************************************************************** */

#ifndef VOC60_H
#define VOC60_H

class VolatileOrganicCarbon60
{

  public:

/* **************************************************************
		 Public Variables
************************************************************** */

     double total;          // (Units are grams C / square meter)
     double isoprene;       // (Units are grams C / square meter)
     double monoterpene;    // (Units are grams C / square meter)
     double other;          // (Units are grams C / square meter)
     double otherReactive;  // (Units are grams C / square meter)

};

#endif
