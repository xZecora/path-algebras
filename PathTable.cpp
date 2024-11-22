#include "PathTable.hpp"

PathID PathTable::addToTable(const Path& path) {
  this->mPathDictionary.push_back(path);                     // path is new, add it to our dictionary
  PathID newPathID = mPathDictionary.size()-1;
  this->mReversePathDictionary.insert({path,newPathID});   // also add it to the reverse dictionary
  mPathDictionary[newPathID].mPathID = newPathID;
  return newPathID;
}

PathID PathTable::findOrAdd(const Path& path)
{
    auto lookup = this->mReversePathDictionary.find(path);
    PathID newPathID;
    if(lookup == this->mReversePathDictionary.end()) {
      newPathID = addToTable(path);
    } else {
      newPathID = lookup->second;
    }
    return newPathID;
}
