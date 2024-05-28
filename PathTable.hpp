#pragma once

#include "Path.hpp"
#include "util.hpp"
#include <vector>
#include <unordered_map>

class PathTable
{
public:
  PathTable()
    : mPathDictionary({Path()}),
      mReversePathDictionary( {{ mPathDictionary[0], (PathID) 0 }} )
  {
  }

private:
  std::vector<Path> mPathDictionary;
  std::unordered_map<Path,PathID,PathHash> mReversePathDictionary;
};
