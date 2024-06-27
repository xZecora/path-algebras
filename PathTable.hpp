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
  }

  void addToTable(Path& path);
  void findOrAdd(Path& path);

private:
  std::vector<Path> mPathDictionary;
  std::unordered_map<Path,PathID,PathHash,PathEqual> mReversePathDictionary;
  //std::unordered_map<Path,PathID,PathHash> mReversePathDictionary;
};
