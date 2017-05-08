/*
   This class represents an NDN Face (interface) and a table of content objects
   and the associated frequencies.
 
   The purpose of this class is to provide member functions to access the rank
   from a single interface, given a content item (named).  It does so through 
   maintaining a sorted list of the ContentFrequency objects, sorted by frequency.
*/

#ifndef INTERFACE_RANK_H
#define INTERFACE_RANK_H
#include "ContentFrequency2.hpp" 
#include <string>
#include <vector>

class
InterfaceRank2
{
   public:
      InterfaceRank2(unsigned int faceId);

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

      std::vector<ContentFrequency2>
      contentFrequencyList;
      
      int
      findContentObject(std::string contentName);
};
#endif
