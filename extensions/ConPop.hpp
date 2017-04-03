#ifndef CONPOP_H
#define CONPOP_H

#include <deque>
#include <string>
using namespace std;

class
ConPop
{
   public:

      ConPop(string name);
   
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


