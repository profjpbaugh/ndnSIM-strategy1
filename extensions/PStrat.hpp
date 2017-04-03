#ifndef PSTRAT_H
#define PSTRAT_H


#include <memory>
#include "face/face.hpp"
#include "fw/strategy.hpp"
#include "pop_man/PopularityManager.hpp"

//#include "fw/multicast-strategy.hpp"

namespace nfd {
namespace fw {

class PStrat : public Strategy {

public:
  PStrat(Forwarder& forwarder, const ndn::Name& name = STRATEGY_NAME);
  
  virtual void
  afterReceiveInterest(const Face& inFace, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry);
  virtual ~PStrat();
  static const ndn::Name STRATEGY_NAME;

  void setPopularityManager(std::shared_ptr<PopularityManager> pm);

private:
  std::shared_ptr<PopularityManager> popularityManager;
};//end class



}//end fw namespace
}//end nfd namespace


#endif
