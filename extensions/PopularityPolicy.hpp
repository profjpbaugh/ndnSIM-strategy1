#include "ns3/ndnSIM/NFD/daemon/table/cs-policy.hpp"
#include "ns3/ndnSIM/ndn-cxx/data.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "pop_man/PopularityManager.hpp"

using namespace std;

const string POLICY_NAME = "PopularityPolicy";

class PopularityPolicy : public nfd::cs::Policy 
{
   
   public:
     PopularityPolicy() : nfd::cs::Policy(POLICY_NAME)
     {
         outfile.open("popularity_policy.txt");
     }


     ~PopularityPolicy() {
         outfile.close();
     }

     void
     setPopularityManager(shared_ptr<PopularityManager> pm)
     {
        cout<<"Setting popularity manager in PopularityPolicy"<<endl;
        popularityManager = pm;
     }


   protected:
     void
     doAfterInsert(nfd::cs::iterator it) 
     {
        auto dataIt = it->getData();
        outfile<<"Just inserted: "<<dataIt.getName()<<endl;
        m_cache.push_back(it);
        //need secondary table of entries
        //also, call eviction to see if the item should even be here
        this->emitSignal(beforeEvict, it);
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
       shared_ptr<PopularityManager> popularityManager;
};  //end of JPBPolicyClass
