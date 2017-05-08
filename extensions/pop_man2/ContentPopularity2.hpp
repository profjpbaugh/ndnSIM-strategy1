/*
   ContentPopularity2:
      Purpose:  Maintain the popularity of
                a particular content item given a name
*/


#ifndef CONTENT_POPULARITY_H
#define CONTENT_POPULARITY_H

#include <string>

class
ContentPopularity2
{
   public:
     ContentPopularity2()
     {
       popularity = 0.0;  //initialize at 0
     }

     std::string contentName;
     double popularity;
};
#endif
