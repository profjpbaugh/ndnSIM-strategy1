#include "PStrat.hpp"
#include <iostream>
using namespace std;

namespace nfd {
namespace fw {

const ndn::Name PStrat::STRATEGY_NAME = "ndn:/localhost/nfd/strategy/popularity-strategy";

NFD_REGISTER_STRATEGY(PStrat);

string
retrieveContentName(const string& fullString);


PStrat::PStrat(Forwarder& forwarder, const Name& name)
 : Strategy(forwarder, name)
{
   cout<<"Inside ctor for PStrat"<<endl;
}//end ctor

void
PStrat::afterReceiveInterest(const Face& inFace, 
                               const Interest& interest,
                               const shared_ptr<pit::Entry>& pitEntry) 
{
  //behave just like the multicast strategy
//  MulticastStrategy::afterReceiveInterest(inFace, interest, pitEntry); 

  //also, maintain popularity eventually
  //cout<<"In afterReceiveInterest, with interest: "<<interest.getName().toUri()<<endl;
  //cout<<"Face: "<<inFace.getId()<<endl;
  //cout<<"Content Name: "<<retrieveContentName(interest.getName().toUri())<<endl;

  cout<<"About to signal the interest!"<<endl;
  //signal interest test
  if(popularityManager != nullptr)
  {
     popularityManager->signalInterest(inFace, interest);
  }
  else
  {
     cout<<"PopularityManager object in PStrat was nullptr"<<endl;
  }
}//end afterReceiveInterest


//---------------------|setPopularityManager|--------------------//
void
PStrat::setPopularityManager(shared_ptr<PopularityManager> pm)
{
  cout<<"About to set Popularity Manager inside PStrat"<<endl;
  if(pm != nullptr)
  {
     cout<<"Before assignment line"<<endl;
     popularityManager = make_shared<PopularityManager>();
     cout<<"Successfully set popularityManager!"<<endl;
  }
  else
  {
     cout<<"The popularity manager passed to PStrat was nullptr"<<endl;
  }
 
}//end setPopularityManager


//helper function
string
retrieveContentName(const string& fullString)
{
  string returnString = "";
  int indexOfLastSlash = fullString.find_last_of("/");
  returnString = fullString.substr(0, indexOfLastSlash);
  return returnString; 
}//end retrieveContentName




PStrat::~PStrat()
{
   cout<<"END OF PStrat"<<endl;
}//end dtor



}//end fw
}//end nfd
