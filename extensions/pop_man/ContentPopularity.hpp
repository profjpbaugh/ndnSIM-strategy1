#ifndef CONTENT_POPULARITY_H
#define CONTENT_POPULARITY_H

#include <string>

class
ContentPopularity
{
   public:
     ContentPopularity()
     {
       popularity = 0.0;  //initialize at 0
     }

     std::string contentName;
     double popularity;
};
#endif
