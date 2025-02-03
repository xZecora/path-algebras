#include "Path.hpp"

// This is kinda sorta pseudo code, we cant actually go from an ID to a label because we can't access the path table
// commenting out for compilation sake
/*
std::string Path::printLabels()
{
  std::string output = "";
  int i = 0;
  for(EdgeID itr: this->mPath) {
    if(i+1 == this->mPath.size()){
      output.append(mPathTable[EdgeID].edgeLabel);
    } else {
      output.append(mPathTable[EdgeID].edgeLabel + ", ");
    }
  }
  return output;
}
*/

std::string Path::printEdgeID() const
{
  std::string output = "";
  int i = 0;
  if (mIsZero) return "";
  if (mIsVertex) return std::to_string(mStartVertex);
  for(EdgeID itr: this->mPath) {
    if(i+1 == this->mPath.size()){
      output.append(std::to_string(itr));
    } else {
      output.append(std::to_string(itr) + ", ");
    }
    i++;
  }
  return output;
}

PathID Path::getID() {
  return this->mPathID;
}

// Very naive, O(wordLen)
// Because this isn't an ordered list I don't know any faster way than parallellizing 
int isSubword(const Path& sub, const Path& word) {
  std::vector<EdgeID> subList = sub.getEdgeList();
  std::vector<EdgeID> wordList = word.getEdgeList();
  size_t wordLen = word.length();
  size_t subLen = sub.length();
  int s = 0;
  int location = -1;

  for (int i = 0; i < wordLen; i++)
  {
    if(subList[s] == wordList[i])
    {
      if(s == 0)
        location = i;
      s++;
    }
    else if (s != 0 && subList[0] == wordList[i])
    {
      location = i;
      s = 1;
    }
    else
    {
      location = -1;
      s = 0;
    }
    if (s == subLen)
      return location;
  }
  return -1;
}
