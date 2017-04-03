/*
   This class represents an NDN Face (interface) and a table of content objects
   and the associated frequencies.
 
   The purpose of this class is to provide member functions to access the rank
   from a single interface, given a content item (named).  It does so through 
   maintaining a sorted list of the ContentFrequency objects, sorted by frequency.
*/

#ifndef INTERFACE_RANK_H
#define INTERFACE_RANK_H
#include "ContentFrequency.hpp" 
#include <string>
#include <vector>

class
InterfaceRank
{
   public:
      InterfaceRank(unsigned int faceId);

      unsigned int
      getFaceId();

      void
      incrementFrequency(std::string contentName);

      void
      resetFrequency(std::string contentName);

      int
      getRank(std::string contentName);

      //returns popularity (inverted rank) for THIS
      //interface
      double 
      getPopularity(std::string contentName);


   private:
      unsigned int
      faceId;

      std::vector<ContentFrequency>
      contentFrequencyList;
      
      int
      findContentObject(std::string contentName);
};
#endif
