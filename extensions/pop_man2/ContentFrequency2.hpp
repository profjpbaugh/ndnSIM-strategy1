/*
   ContentFrequency2
      Purpose: maintain the frequency of a particular
               content item, given a name

*/

#ifndef CONTENT_FREQUENCY_H
#define CONTENT_FREQUENCY_H

#include <string>

class
ContentFrequency2 
{
   public:
     ContentFrequency2()
     {
       frequency = 0;  //initialize at 0
     }

     std::string contentName;
     int frequency;     
};
#endif
