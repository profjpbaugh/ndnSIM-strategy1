#ifndef POPULARITY_MANAGER_H
#define POPULARITY_MANAGER_H

#include <string>
#include <vector>
#include "InterfaceRank2.hpp"
#include "ContentPopularity2.hpp"
#include "face/face.hpp"
#include "fw/strategy.hpp"

class
PopularityManager2
{
   public:
      PopularityManager2();

      PopularityManager2(int sizeOfContentStore);

      void
      setCsSize(int sizeOfContentStore);

      int 
      getCsSize();

      void
      setInterestByFace(int faceId, std::string contentName);

      double
      getPopularityByFace(int faceId, std::string contentName);

      double
      getOverallPopularity(std::string contentName);

      int
      getOverallRank(std::string contentName);

      bool
      shouldEvictContent(std::string contentName);

      void
      printByRank();

      //TEMP:  TODO: remove?
      //signal interest - basic testing
      void
      signalInterest(const nfd::Face& inFace, const ndn::Interest& interest);
      
   private:
      //maintain a list of the interfaces and their ranks of
      //each item.  This will be used to calculate popularity
      //as needed

      std::vector<InterfaceRank2>
      interfaceRankList;

      //maintain a list of each known Content and the associated
      //popularity
      //this list should be sorted, so as to be able to calculate
      //which content should be removed from the cache
      std::vector<ContentPopularity2>
      contentPopularityList;

      int
      CsSize;

      int
      findInterfaceIndexInList(int faceId);

      int
      findContentPopularityInList(std::string contentName);
};
#endif
