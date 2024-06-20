#include "PathTable.hpp"

void PathTable::addToTable(Path& path) {
  this->mPathDictionary.push_back(path);                     // path is new, add it to our dictionary
  this->mReversePathDictionary.insert({path,mPathDictionary.size()-1});   // also add it to the reverse dictionary
}
