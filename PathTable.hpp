#pragma once

#include "util.hpp"
#include <vector>
#include <unordered_map>

class PathTable
{

  

private:
  std::vector<Path> mPathDictionary;
  std::unordered_map<Path,PathID> mReversePathDictionary;
};
