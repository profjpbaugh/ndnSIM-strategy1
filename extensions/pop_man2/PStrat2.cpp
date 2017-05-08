#include "PStrat2.hpp"
#include <iostream>
using namespace std;

namespace nfd {
namespace fw {

const ndn::Name PStrat2::STRATEGY_NAME = "ndn:/localhost/nfd/strategy/popularity-strategy2";

static shared_ptr<PopularityManager2> popularityManager = nullptr;
static bool popularityManagerIsSet = false;

NFD_REGISTER_STRATEGY(PStrat2);


//declared in the .hpp file
//string
//retrieveContentName2(const string& fullString);


PStrat2::PStrat2(Forwarder& forwarder, const Name& name)
 : Strategy(forwarder, name)
{
   cout<<"Inside ctor for PStrat2"<<endl;
   cout<<"    Inside ctor, popularityManager contains: "<<popularityManager<<endl;
   cout<<"    Inside ctor, popularityManager lives at: "<<&popularityManager<<endl;
}//end ctor

void
PStrat2::afterReceiveInterest(const Face& inFace, 
                               const Interest& interest,
                               const shared_ptr<pit::Entry>& pitEntry) 
{

  //signal interest test
  if(popularityManager != nullptr)
  {
     popularityManager->signalInterest(inFace, interest);
  }
  else
  {
     cout<<"PopularityManager object in PStrat2 was nullptr"<<endl;
  }
}//end afterReceiveInterest


//---------------------|setPopularityManager|--------------------//
void
PStrat2::setPopularityManager(std::shared_ptr<PopularityManager2> pm)
{
  if(!popularityManagerIsSet)
  {
    cout<<"About to set Popularity Manager inside PStrat2"<<endl;
    if(pm != nullptr)
    {
    
       cout<<"Before assignment line in setPopularityManager"<<endl;
       cout<<"    popularityManager lives at "<<&popularityManager<<endl;
       cout<<"    popularityManager contains: "<<popularityManager<<endl;
       cout<<"    pm lives at "<<&pm<<endl;
       cout<<"    pm contains: "<<pm<<endl;
       //popularityManager = make_shared<PopularityManager>();
       popularityManager = pm;
       cout<<"    Successfully set popularityManager!"<<endl;
       cout<<"    Now, popularityManager contains: "<<popularityManager<<endl;
       cout<<"    size of popularity manager CS limit: "<<popularityManager->getCsSize()<<endl;
    }
    else
    {
       cout<<"The popularity manager passed to PStrat2 was nullptr"<<endl;
    }
    popularityManagerIsSet = true;
  } 
}//end setPopularityManager


//helper function
string
retrieveContentName2(const string& fullString)
{
  string returnString = "";
  int indexOfLastSlash = fullString.find_last_of("/");
  returnString = fullString.substr(0, indexOfLastSlash);
  return returnString; 
}//end retrieveContentName2




PStrat2::~PStrat2()
{
   cout<<"END OF PStrat2"<<endl;
}//end dtor



}//end fw
}//end nfd
