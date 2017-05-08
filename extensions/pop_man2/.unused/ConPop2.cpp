#include "ConPop2.hpp"

ConPop2::ConPop2(string name)
{
   contentName = name;
}

void
ConPop2::incrementFrequency(int faceID)
{
    int index = getIndexOfFace(faceID);
    int currentFrequency = 0;

    //if new faceID, create it in ID
    //set its corresponding frequency to 1
    if(index == -1)  //it's new!
    {
       faceIDs.push_back(faceID);
       frequencies.push_back(1); 
    }
    else //it already exists!
    {
       currentFrequency = frequencies.at(index);
       currentFrequency++;
       frequencies.at(index) = currentFrequency;
    }//end if-else      
}

void
ConPop2::decrementFrequency(int faceID)
{

     int index = getIndexOfFace(faceID);
     int currentFrequency = 0;

     if(index != -1)
     {
        currentFrequency = getFrequencyFromFace(faceID);                 
        if(currentFrequency > 0)
        {
           currentFrequency--;
           frequencies.at(index) = currentFrequency;  
        }
     }
 
}

void
ConPop2::resetFrequency(int faceID)
{
    int index = getIndexOfFace(faceID);
    if(index != -1)
    {
       frequencies.at(index) = 0;  //reset to 0 
    }
}

void
ConPop2::setName(string name)
{
    contentName = name;
}

string
ConPop2::getName() const
{
    return contentName;
}

int
ConPop2::getNumFaces() const
{
    return faceIDs.size();
}

int
ConPop2::getFrequencyFromFace(int faceID) const
{
    int value = 0;

    //find the faceID if it exists
    int index = getIndexOfFace(faceID);

    if(index != -1) //it already exists
    {
       value = frequencies.at(index);   
    }
    
    return value;
}

int
ConPop2::getFrequencyFromIndex(int index) const
{
    int frequency = 0;

    if(index >= 0 && index < frequencies.size())
    {
       frequency = frequencies.at(index);
    }//end if

     return frequency;
}

int
ConPop2::getFaceFromIndex(int index) const
{
   int faceID = -1;

   if(index >=0 && index < faceIDs.size())
   {
      faceID = faceIDs.at(index);
   }//end if

   return faceID;
}
//---------------------------//
//private helper functions
//---------------------------//
int
ConPop2::getIndexOfFace(int faceID) const
{
   int index = -1;  //-1 means it doesn't exist - it's new!

   for(unsigned int i = 0; i < faceIDs.size(); ++i)
   {
     if(faceIDs.at(i) == faceID) //found it!
     {
       index = i;
       break;
     }
   }//end for

   return index;
}
