#include "ns3/ndnSIM/NFD/daemon/table/cs-policy.hpp"
#include "ns3/ndnSIM/ndn-cxx/data.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string POLICY_NAME = "JPBPrintContent";

class JPBPrintContent : public nfd::cs::Policy 
{
   
   public:
     JPBPrintContent() : nfd::cs::Policy(POLICY_NAME)
     {
         outfile.open("jpbprint_content.txt");
     }


     ~JPBPrintContent() {
         printContents();
         outfile.close();
     }

   protected:
     void
     doAfterInsert(nfd::cs::iterator it) 
     {
        auto dataIt = it->getData();
        outfile<<"Just inserted: "<<dataIt.getName()<<endl;
        m_cache.push_back(it);
        this->evictEntries();  //eviction policy enacted!

        //need secondary table of entries
        //also, call eviction to see if the item should even be here
     }  //end doAfterInsert

     void 
     doAfterRefresh(nfd::cs::iterator it)
     {

     }  //end doAfterRefresh

     void
     doBeforeErase(nfd::cs::iterator it)
     {
       outfile<<"doBeforeErase just called!"<<endl;
       /* auto dataIt = it->getData();
        outfile<<"About to erase: "<<dataIt.getName()<<endl;
       */
          //nfd::cs::iterator i = m_cache.front();
          //auto dataIt = i->getData();

          //m_cache.pop_front();
          //outfile <<"Erased item: "<<dataIt.getName()<<endl;
     }  //end doBeforeErase

     void
     doBeforeUse(nfd::cs::iterator it)
     {

     }  //end doBeforeUse

     void
     evictEntries()
     {
         cout<<"Evict Entries is called"<<endl;
         BOOST_ASSERT(this->getCs() != nullptr);

         if(this->getCs()->size() > this->getLimit())
         {
           cout<<"Size is: "<<this->getCs()->size()<<endl;
           cout<<"Limit:   "<<this->getLimit()<<endl;
           if(!m_cache.empty())
           {
             cout<<"Cache is NOT empty, deleting item"<<endl;
             nfd::cs::iterator i = m_cache.front();
             this->emitSignal(beforeEvict, i);
             m_cache.pop_front();
           }
         }//end if
 
     }//end evictEntries

     void printContents()
     {
       outfile<<endl<<endl<<endl;
       outfile<<"Contents remaining: "<<endl;
       nfd::Cs& theCS = *(this->getCs());
       for(auto it = theCS.begin();
                it != theCS.end();
                ++it)
       {
         outfile<<it->getName()<<endl;
       }//end for
     }
    private:
       ofstream outfile;
       std::list<nfd::cs::iterator> m_cache; 
      
};  //end of JPBPolicyClass
