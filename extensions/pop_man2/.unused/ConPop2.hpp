/*
    ConPop2
      revision 5/7/2017
      Purpose:  represents a content item and
                its list of frequencies with faceIDs 
                This maintains data about individual
                content items


*/

#ifndef CONPOP2_H
#define CONPOP2_H

#include <deque>
#include <string>
using namespace std;

class
ConPop2
{
   public:

      ConPop2(string name);
   
      void
      incrementFrequency(int faceID);

      void
      decrementFrequency(int faceID);

      void
      resetFrequency(int faceID);  //sets to 0
 
      void 
      setName(string name);

      string
      getName() const;

      int
      getNumFaces() const;

      int
      getFrequencyFromFace(int faceID) const;

      int
      getFrequencyFromIndex(int index) const;

      int
      getFaceFromIndex(int index) const;

   private:
      int
      getIndexOfFace(int faceID) const;    
      deque<int> faceIDs;
      deque<int> frequencies;
      string contentName;

};  //end class



#endif


