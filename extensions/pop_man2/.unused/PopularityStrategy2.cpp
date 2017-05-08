#include "PopularityStrategy2.hpp"
#include <iostream>
using namespace std;

namespace nfd {
namespace fw {

const ndn::Name PopularityStrategy2::STRATEGY_NAME = "ndn:/localhost/nfd/strategy/popularity-strategy";

NFD_REGISTER_STRATEGY(PopularityStrategy2);

PopularityStrategy2::PopularityStrategy2(Forwarder& forwarder, const Name& name)
 : MulticastStrategy(forwarder, name)
{
   cout<<"Inside ctor for PopularityStrategy2"<<endl;
}//end ctor

void
PopularityStrategy2::afterReceiveInterest(const Face& inFace, 
                               const Interest& interest,
                               const shared_ptr<pit::Entry>& pitEntry) 
{
  //behave just like the multicast strategy
//  MulticastStrategy::afterReceiveInterest(inFace, interest, pitEntry); 

  //also, maintain popularity eventually
  cout<<"In afterReceiveInterest, with interest: "<<interest.getName().toUri()<<endl;
}//end afterReceiveInterest


}//end fw
}//end nfd
