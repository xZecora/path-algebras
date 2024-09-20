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

std::string Path::printEdgeLabels() const { return this->printEdgeID(); }

std::string Path::printEdgeID() const
{
  std::string output = "";
  int i = 0;
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
