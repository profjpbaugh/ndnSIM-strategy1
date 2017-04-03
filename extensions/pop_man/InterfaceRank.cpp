#include "InterfaceRank.hpp"
#include <algorithm>

//comparator function for sort algorithm
bool
compareContentFrequencyItems(const ContentFrequency& cf1, const ContentFrequency& cf2)
{
   return cf1.frequency >= cf2.frequency;
}//end compareContentFrequencyItems

InterfaceRank::InterfaceRank(unsigned int faceId)
{
    this->faceId = faceId;
}//end ctor

unsigned int
InterfaceRank::getFaceId()
{
   return faceId;
}//end getFaceId

void 
InterfaceRank::incrementFrequency(std::string contentName)
{

   int index = findContentObject(contentName);
   ContentFrequency temp_cf;

   if(index == -1)  //this is a new content
   {
      temp_cf.contentName = contentName;
      temp_cf.frequency = 1;

      contentFrequencyList.push_back(temp_cf);
   }
   else   //this content alread exists
   {
      contentFrequencyList.at(index).frequency++;
   }//end if-else

   std::sort(contentFrequencyList.begin(), contentFrequencyList.end(), compareContentFrequencyItems);

}//end incrementFrequency

void 
InterfaceRank::resetFrequency(std::string contentName)
{
   int index = findContentObject(contentName);
  
   if(index != -1)
   {
      contentFrequencyList.at(index).frequency = 0;  //reset
   }//end if    
}//resetFrequency

int 
InterfaceRank::getRank(std::string contentName)
{
    int index = findContentObject(contentName);
  
    if(index != -1) 
    {
       index += 1;
    }

    return index;  //index matches rank
}//end getRank

//returns popularity (inverted rank) for THIS
//interface
double
InterfaceRank::getPopularity(std::string contentName)
{
   int rank = getRank(contentName);
   if(rank == -1)  //not found
   {
      return -1;  //-1 means it's not ranked, i.e., infinity rank
   }
   return 1.0/(rank);  //return popularity
}//getPopularity



//returns the index of the content object
//or -1 if not found
int
InterfaceRank::findContentObject(std::string contentName)
{
   int index = -1;  //by default, not found

   for(int i = 0; i < contentFrequencyList.size(); i++)
   {
      if(contentFrequencyList.at(i).contentName == contentName)
      {
         index = i;
         break;
      }//end if
   }//end for
   return index;
}//end findContentObject
