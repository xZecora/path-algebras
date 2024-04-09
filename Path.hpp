#pragma once

#include "util.hpp"
#include "Graph.hpp"

#include <vector>

class Path
{
public:
  std::vector<EdgeID> getEdgeList(); // needed to access the edge list nonlocally

private:
  bool mIsZero;
  bool mIsVertex;
  VertexID mStartVertex;
  VertexID mEndVertex;
  PathID mPathID;
  std::vector<EdgeID> mPath;
};
