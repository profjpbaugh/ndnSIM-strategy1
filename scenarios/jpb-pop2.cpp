/*
   jpb-pop2
   orig revision 5/7/2017
   
*/

#include <iostream>

//core module and required helpers for example
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"

/*
   This scenario is for the purpose of the initial
   integration of the Per-Interface Popularity
   cache replacement technique into the ndnSIM
   environment.
   Initiated:  1/29/2017, jpbaugh 

*/


//required for use of CS (from NFD)
#include "ns3/ndnSIM/NFD/daemon/table/cs.hpp"
#include "ns3/ndnSIM/NFD/daemon/table/cs-policy-priority-fifo.hpp"
#include "ns3/ndnSIM/NFD/core/logger.hpp"
#include "ns3/ndnSIM/NFD/core/algorithm.hpp"
#include "ns3/ndnSIM/ndn-cxx/data.hpp"
#include "pop_man2/PopularityPolicy2.hpp"
#include "pop_man2/PStrat2.hpp"
#include "ns3/ndnSIM/ndn-cxx/name.hpp"

//#include <memory>   //for the unique_ptr and make_unique
#include <string>
#include <array>
using namespace std;

namespace ns3 {

 
  int
  main(int argc, char* argv[])
  {

     //setting default parameters for point to point links & channels

     Config::SetDefault("ns3::PointToPointNetDevice::DataRate",
                        StringValue("1Mbps"));
     Config::SetDefault("ns3::PointToPointChannel::Delay", 
                        StringValue("10ms"));
     Config::SetDefault("ns3::DropTailQueue::MaxPackets",
                        StringValue("20"));

     //read optional command line params
     CommandLine cmd;
     cmd.Parse(argc, argv);

     //Create the node
     //through the node container

     NodeContainer nodes;
     nodes.Create(4);  // [consumer] -- [router] -- [producer]
                       // [consumer] ----^

     //connect nodes (create channels)
     PointToPointHelper p2p;
     p2p.Install(nodes.Get(0), nodes.Get(2));  
     p2p.Install(nodes.Get(1), nodes.Get(2));
     p2p.Install(nodes.Get(2), nodes.Get(3));
 
     //install the NDN stack on the node
     ndn::StackHelper ndnHelper;
     ndnHelper.SetDefaultRoutes(true);
     ndnHelper.InstallAll();
 

     //Global Routing (Shortest Path) helper
     ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
     ndnGlobalRoutingHelper.InstallAll(); 

     //install forwarding strategy on the node
     ndn::StrategyChoiceHelper::InstallAll("/prefix",
                                   "/localhost/nfd/strategy/multicast");

     ndn::StrategyChoiceHelper::Install<nfd::fw::PStrat2>(nodes.Get(2),
                                                                    ndn::Name("/prefix")) ;
 
 
  //for a node - the router (node 1)
     Ptr<ns3::ndn::L3Protocol> l3 =
                        ns3::ndn::L3Protocol::getL3Protocol(nodes.Get(2)); 

     //get the content store for the node     
     nfd::Cs& myContentStore = l3->getForwarder()->getCs();
     myContentStore.setLimit(10);



     //-----------| get / create shared PopularityManager for system
     //-------------------------------------------------------------//
     //----> This can be shared by both PStrat2 and the Policy
     //----> Used to maintain and convey information between the two
     shared_ptr<PopularityManager2> popularityManager = 
                                   make_shared<PopularityManager2>(myContentStore.getLimit());

     cout<<"In jpb-pop2 main: "<<&popularityManager<<endl;
     cout<<"About to get forwarder"<<endl;


     //-------------------| get the reference to the strategy |---------------------//
     shared_ptr<nfd::Forwarder> forwarder = l3->getForwarder();

     cout<<"Just got forwarder.  About to get strategy choice"<<endl;

     nfd::StrategyChoice& sc =  forwarder->getStrategyChoice();

     cout<<"Just got strategy choice, about to get effectiveStrategy"<<endl;

     nfd::fw::PStrat2& effectiveStrategy = (nfd::fw::PStrat2&)(sc.findEffectiveStrategy(nfd::Name("/prefix")));     

     cout<<"Just got effective strategy, about to set popularity manager for it."<<endl;

     //set the manager for the strategy
       effectiveStrategy.setPopularityManager(popularityManager);
  
    
     cout<<"Just set effectiveStrategy.setPopularityManager"<<endl;
 
     //-----------| set policy for Cs

     unique_ptr<PopularityPolicy2> policy = 
                                  ndn::make_unique<PopularityPolicy2>(); 


     policy->setLimit(myContentStore.getLimit());  //should be same as Cs::setLimit
     policy->setPopularityManager(popularityManager);

     cout<<"Just set popularity manager for policy (jpb-pop1) main"<<endl;

     myContentStore.setPolicy(move(policy));  //previously move(policy)


     //consumer 1
     ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
     consumerHelper.SetPrefix("/prefix/c1");
     consumerHelper.SetAttribute("Frequency", 
                                 StringValue("10"));
     consumerHelper.Install(nodes.Get(0));
 
     //consumer 2
     ndn::AppHelper consumerHelper2("ns3::ndn::ConsumerCbr");
     consumerHelper2.SetPrefix("/prefix/c2");
     consumerHelper2.SetAttribute("Frequency", 
                                  StringValue("10"));
     consumerHelper2.Install(nodes.Get(1));
     
     //producer
     ndn::AppHelper producerHelper("ns3::ndn::Producer");
     producerHelper.SetPrefix("/prefix");
     producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
     producerHelper.Install(nodes.Get(3));

     cout<<"Just created consumers and producer helper."<<endl;

     //calculate and install FIBs
     ndn::GlobalRoutingHelper::CalculateRoutes();

     //run simulation
     Simulator::Stop(Seconds(20.0));
     Simulator::Run();

     //popularityManager->printByRank();

     cout<<"Simulation complete"<<endl;
     Simulator::Destroy();
     return 0;  
  }
} //end namespace

int
main(int argc, char* argv[]) 
{
  return ns3::main(argc, argv);
}

