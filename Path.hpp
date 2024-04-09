#pragma once

#include "util.hpp"
#include "Graph.hpp"

#include <vector>

class Path
{
public:
  const std::vector<EdgeID>& getEdgeList(); // needed to access the edge list nonlocally

  size_t length() { return mPath.size(); }

private:
  bool mIsZero;
  bool mIsVertex;
  VertexID mStartVertex;
  VertexID mEndVertex;
  PathID mPathID;
  std::vector<EdgeID> mPath;
};
