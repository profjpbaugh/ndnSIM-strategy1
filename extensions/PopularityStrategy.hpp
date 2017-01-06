#ifndef POPULARITY_STRATEGY_H
#define POPULARITY_STRATEGY_H


#include "face/face.hpp"
#include "fw/strategy.hpp"
#include "fw/multicast-strategy.hpp"

namespace nfd {
namespace fw {

const ndn::Name STRATEGY_NAME("ndn:/localhost/nfd/strategy/popularity-strategy");

class PopularityStrategy : public MulticastStrategy {

public:
  PopularityStrategy(Forwarder& forwarder, const ndn::Name& name = STRATEGY_NAME);
  
  virtual void
  afterReceiveInterest(const Face& inFace, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry);
  
  //static const ndn::Name STRATEGY_NAME("ndn:/localhost/nfd/strategy/popularity-strategy")

  


};//end class



}//end fw namespace
}//end nfd namespace


#endif
