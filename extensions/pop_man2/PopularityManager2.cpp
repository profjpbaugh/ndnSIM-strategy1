#include "PopularityManager2.hpp"
#include "PStrat2.hpp" //for retrievePopularityName
#include <algorithm>
#include <iostream>
#include <iomanip>

//Non-member comparison function to be used as callback for sorting
bool
compareContentPopularity(const ContentPopularity2& cp1,
                         const ContentPopularity2& cp2)
{
   return cp1.popularity > cp2.popularity;
}//end compareContentPopularity


//-------------------------------------------------------------//
//--------------------| MEMBER FUNCTIONS |---------------------//
//-------------------------------------------------------------//
PopularityManager2::PopularityManager2()
{
   std::cout<<"PopularityManager2 no-arg ctor called!"<<std::endl;
   std::cout<<std::boolalpha;
   this->CsSize = 5;  //default
}


PopularityManager2::PopularityManager2(int CsSize)
{
   std::cout<<"PopularityManager2 ctor called!"<<std::endl;
   std::cout<<std::boolalpha;  //sticky setting to print true or false
   this->CsSize = CsSize;
}//end ctor

void
PopularityManager2::setCsSize(int CsSize) 
{
   this->CsSize = CsSize; 
}//end setCsSize

int
PopularityManager2::getCsSize()
{
   return this->CsSize;
}


void
PopularityManager2::setInterestByFace(int faceId, std::string contentName)
{

   contentName = nfd::fw::retrieveContentName2(contentName);
   
   //insert new content if it's new
   //update information if the content is known
   //must update BOTH the content popularity list AND 
   //the interface rank list

   //also we must test if the interface is new, not just the content

   //first use index to find content popularity 
   //used for inserting the content, or updating it

   int index = findContentPopularityInList(contentName);

   ContentPopularity2 cpItem;
   InterfaceRank2 irItem(faceId);


   if(index == -1)  //first time found
   {

      //add to content popularity list
      cpItem.contentName = contentName;
      cpItem.popularity  = getOverallPopularity(contentName);

      contentPopularityList.push_back(cpItem);
       
   }
   else //already exists in content popularity list
   {
      contentPopularityList.at(index).popularity = getOverallPopularity(contentName);
   
   }//end else

   //now sort
   std::sort(contentPopularityList.begin(), contentPopularityList.end(),
             compareContentPopularity);


   //now add to or update the interface rank if this is a new interface
   index = findInterfaceIndexInList(faceId);

   if(index == -1)
   {
      irItem.incrementFrequency(contentName);
      interfaceRankList.push_back(irItem); 
   }
   else
   {
      interfaceRankList.at(index).incrementFrequency(contentName);
   }//end if-else
}//end setInterestByFace

double
PopularityManager2::getPopularityByFace(int faceId, std::string contentName)
{
   //TODO:  pass-through to the InterfaceRank data objects
   //NOT IMPLEMENTED YET (or ever?)
   return 0.0;
}//end getPopularityByFace

double
PopularityManager2::getOverallPopularity(std::string contentName)
{
   double overallPopularity = 0.0;
   double individualPopularity = 0.0;
 
   for(int i = 0; i < interfaceRankList.size(); i++)
   {
      individualPopularity = interfaceRankList.at(i).getPopularity(contentName);

      if(individualPopularity != -1)  //doesn't contribute, since not ranked
      {
         overallPopularity+= individualPopularity;
      }//end if
   }//end for

   return overallPopularity;
}//end getOverallPopularity

int
PopularityManager2::getOverallRank(std::string contentName)
{
   //TODO:  should have a sorted list,
   //much in the same technique used in the InterfaceRank
   //class

   int overallRank = -1;  //not ranked by default
   
   overallRank = findContentPopularityInList(contentName);

   if(overallRank != -1)
   {
      overallRank +=1;  //make count from 1, not 0
   }   

   return overallRank;
}


/*
   Precondition:
      Content Store is full, so eviction must be determined

   Should we evict the content of the given name?
   Based on the internal CsSize (content store size),
   if this named item (contentName) is not within that limit
   of the Cs size, then this function returns true,
   otherwise false

   Should probably use getOverallRank member function
*/
bool
PopularityManager2::shouldEvictContent(std::string contentName)
{
   int index = findContentPopularityInList(contentName);

   if((index + 1) <= CsSize && index != -1)  //if ranked within limit and not -1
   {
      return false;
   }//end if

   // otherwise, it's a -1 (not found) or > the
   // CsSize/limit, so evict

   return true;
}//end shouldEvictContent

void
PopularityManager2::printByRank()
{
   for(int i = 0; i < contentPopularityList.size(); i++)
   {
      std::cout<<(i+1)<<" name: "<<contentPopularityList.at(i).contentName<<" -- replace? ";
      std::cout<<shouldEvictContent(contentPopularityList.at(i).contentName);
      std::cout<<std::endl;
   }//end for
}//end printByRank


void
PopularityManager2::signalInterest(const nfd::Face& inFace, const ndn::Interest& interest)
{
   if(this == nullptr) 
   {
      std::cout<<"I am a null ptr!"<<std::endl;
   }

   //Set the interest by the face
   std::cout<<"Setting interest : "<<interest.toUri()<<std::endl;

   setInterestByFace(inFace.getId(), interest.toUri());
   std::cout<<"\tInterest is set!"<<std::endl;
   

}//end signalInterest

//---------------------------------------------------//
//-------| Private helper member functions |---------//
//---------------------------------------------------//
int
PopularityManager2::findInterfaceIndexInList(int faceId)
{
   int index = -1;  //not found by default

   for(int i = 0; i < interfaceRankList.size(); i++)
   {
      if(interfaceRankList.at(i).getFaceId() == faceId)
      {
         index = i;
         break;
      } //end if
   }//end for

   return index;
}//end findInterfaceIndexInList


//assumes a list of content/popularity items
//sorted from most popular to least
//therefore, index + 1 serves as the rank
int
PopularityManager2::findContentPopularityInList(std::string contentName)
{
   int index = -1;  //not found by default
   
   for(int i = 0; i < contentPopularityList.size(); i++)
   {
      if(contentPopularityList.at(i).contentName == contentName)
      {
         index = i;
         break;
      }//end if
   }//end for

   return index;
}//end findContentPopularityInList
