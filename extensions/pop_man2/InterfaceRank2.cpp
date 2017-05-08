#include "InterfaceRank2.hpp"
#include <algorithm>

//comparator function for sort algorithm
bool
compareContentFrequencyItems(const ContentFrequency2& cf1, const ContentFrequency2& cf2)
{
   return cf1.frequency >= cf2.frequency;
}//end compareContentFrequencyItems

InterfaceRank2::InterfaceRank2(unsigned int faceId)
{
    this->faceId = faceId;
}//end ctor

unsigned int
InterfaceRank2::getFaceId()
{
   return faceId;
}//end getFaceId

void 
InterfaceRank2::incrementFrequency(std::string contentName)
{

   int index = findContentObject(contentName);
   ContentFrequency2 temp_cf;

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
InterfaceRank2::resetFrequency(std::string contentName)
{
   int index = findContentObject(contentName);
  
   if(index != -1)
   {
      contentFrequencyList.at(index).frequency = 0;  //reset
   }//end if    
}//resetFrequency

int 
InterfaceRank2::getRank(std::string contentName)
{
    int index = findContentObject(contentName);
  
    if(index != -1) 
    {
       index += 1;   //to ensure index 0 = rank 1
                     //prevents later dividing by 0 also
    }

    return index;  //index matches rank
}//end getRank

//returns popularity (inverted rank) for THIS
//interface
double
InterfaceRank2::getPopularity(std::string contentName)
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
InterfaceRank2::findContentObject(std::string contentName)
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
