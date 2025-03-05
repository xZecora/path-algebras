#pragma once

#include "Path.hpp"
#include "util.hpp"
#include <vector>
#include <unordered_map>

class PathTable
{
friend class PathAlgebra;
public:
  PathTable()
    : mPathDictionary({Path()}),
      mReversePathDictionary( {{ mPathDictionary[0], (PathID) 0 }} )
  {
      mPathDictionary[0].mPathID = 0; // this is the empty (zero) path
  }

  PathID findOrAdd(const Path& path);
  
  const std::vector<Path>& pathDictionary() const { return mPathDictionary; }

private:
  PathID addToTable(const Path& path);

  std::vector<Path> mPathDictionary;
  std::unordered_map<Path,PathID,PathHash,PathEqual> mReversePathDictionary;
  //std::unordered_map<Path,PathID,PathHash> mReversePathDictionary;
};
