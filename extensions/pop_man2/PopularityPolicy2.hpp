#include "ns3/ndnSIM/NFD/daemon/table/cs-policy.hpp"
#include "ns3/ndnSIM/ndn-cxx/data.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "PopularityManager2.hpp"

using namespace std;

const string POLICY_NAME = "PopularityPolicy2";

class PopularityPolicy2 : public nfd::cs::Policy 
{
   
   public:
     PopularityPolicy2() : nfd::cs::Policy(POLICY_NAME)
     {
         outfile.open("popularityPolicyData.txt");
     }


     ~PopularityPolicy2() {
         cout<<"Closing outfile in PopularityPolicy2 dtor"<<endl;
         outfile.close();
     }

     void
     setPopularityManager(shared_ptr<PopularityManager2> pm)
     {
        popularityManager = pm;
     }


   protected:
     void
     doAfterInsert(nfd::cs::iterator it) 
     {
        auto dataIt = it->getData();
        outfile<<"Just inserted: "<<dataIt.getName()<<endl;
        m_cache.push_back(it);
        outfile<<endl<<"Insertion worked!"<<endl;
        //need secondary table of entries
        //also, call eviction to see if the item should even be here
        //this->emitSignal(beforeEvict, it);
     }  //end doAfterInsert

     void 
     doAfterRefresh(nfd::cs::iterator it)
     {

     }  //end doAfterRefresh

     void
     doBeforeErase(nfd::cs::iterator it)
     {
       /* auto dataIt = it->getData();
        outfile<<"About to erase: "<<dataIt.getName()<<endl;
       */
          nfd::cs::iterator i = m_cache.front();
          auto dataIt = i->getData();

          m_cache.pop_front();
          outfile <<"Erased item: "<<dataIt.getName()<<endl;
     }  //end doBeforeErase

     void
     doBeforeUse(nfd::cs::iterator it)
     {

     }  //end doBeforeUse

     void
     evictEntries()
     {

     }  //end evictEntries


    private:
       ofstream outfile;
       std::list<nfd::cs::iterator> m_cache; 
       shared_ptr<PopularityManager2> popularityManager;
};  //end of JPBPolicyClass
