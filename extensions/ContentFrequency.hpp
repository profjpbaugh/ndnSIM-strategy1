#ifndef CONTENT_FREQUENCY_H
#define CONTENT_FREQUENCY_H

#include <string>

class
ContentFrequency 
{
   public:
     ContentFrequency()
     {
       frequency = 0;  //initialize at 0
     }

     std::string contentName;
     int frequency;     
};
#endif
