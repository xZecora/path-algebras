#include "PathTable.hpp"

void PathTable::addToTable(Path& path) {
  this->mPathDictionary.push_back(path);                     // path is new, add it to our dictionary
  this->mReversePathDictionary.insert({path,mPathDictionary.size()-1});   // also add it to the reverse dictionary
}

void PathTable::findOrAdd(Path& path)
{
    auto lookup = this->mReversePathDictionary.find(path);

    if(lookup == this->mReversePathDictionary.end()) {
      path.mPathID = this->mPathDictionary.size();               // now give it its ID
      this->addToTable(path);                                    // add newPath to both of our path tables
    } else {
      path = lookup->first;
    }
}
