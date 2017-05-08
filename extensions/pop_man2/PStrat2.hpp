#ifndef PSTRAT2_H
#define PSTRAT2_H


#include <memory>
#include <string>
#include "face/face.hpp"
#include "fw/strategy.hpp"
#include "PopularityManager2.hpp"

//#include "fw/multicast-strategy.hpp"

namespace nfd {
namespace fw {

std::string
retrieveContentName2(const std::string& fullString);

class PStrat2 : public Strategy {

public:
  PStrat2(Forwarder& forwarder, const ndn::Name& name = STRATEGY_NAME);
  
  virtual void
  afterReceiveInterest(const Face& inFace, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry);
  virtual ~PStrat2();
  static const ndn::Name STRATEGY_NAME;

  static void 
  setPopularityManager(std::shared_ptr<PopularityManager2> pm);


};//end class



}//end fw namespace
}//end nfd namespace


#endif
