#pragma once

#include "util.hpp"
#include <iostream>
#include <vector>

class Path
{
  friend class PathHash;
  friend class PathEqual;
  friend class PathAlgebra;
  friend class PathTable;
  
public:
  const std::vector<EdgeID>& getEdgeList() const { return mPath; }; // needed to access the edge list nonlocally

  std::string printEdgeID() const;

  PathID getID();

  size_t length() const { return mPath.size(); }

  VertexID getStartVertex() const { return mStartVertex; }
  VertexID getEndVertex() const { return mEndVertex; }

  Path(VertexID startVertex,
       VertexID endVertex,
       std::vector<EdgeID> pathEdgeList,
       bool checkValidity = false)
    : mIsZero(false),
      mIsVertex(false),
      mStartVertex(startVertex),
      mEndVertex(endVertex),
      mPathID(-1),  // -1 indicates that path id is currently unknown
      mPath(pathEdgeList)
  {
  }

  explicit Path(VertexID vertexID)   // make explicit to avoid accidental calls to contains/find on PathIDs.
                                     // in fact, should we just make PathID and VertexID structs?
    : mIsZero(false),
      mIsVertex(true),
      mStartVertex(vertexID),
      mEndVertex(vertexID),
      mPathID(-1),  // -1 indicates that path id is currently unknown
      mPath({})
  {
  }

  Path() // case of the zero path
    : mIsZero(true),
      mIsVertex(false),
      mStartVertex(-1),
      mEndVertex(-1),
      mPathID(0),  // zero path should be first element in dictionary
      mPath({})
  {
  }

  const std::vector<EdgeID>& getPathList() const
  {
    return this->mPath;
  }

  bool isSubword(const Path& sub, const Path& word);

private:
  bool mIsZero;
  bool mIsVertex;
  VertexID mStartVertex;
  VertexID mEndVertex;
  PathID mPathID;
  std::vector<EdgeID> mPath;
};

class PathEqual {
  public:
  bool operator()(const Path& lhs, const Path& rhs) const
  {
    if(lhs.mPathID != -1 && rhs.mPathID != -1)
    {
      return lhs.mPathID == rhs.mPathID;
    }
    // return false if they are not the same size
    if(lhs.mPath.size() != rhs.mPath.size())
    {
      return false;
    }
    // at this point they are the same length.  If zero, just check start vertices
    if (lhs.mPath.size() == 0)
       return (lhs.mStartVertex == rhs.mStartVertex);

    // now they are not vertices, so 
    // iterate over the lists to check equality
    int i = 0;
    for(EdgeID id : rhs.mPath) {
      if(id != lhs.mPath[i])
      {
        return false;
      }
      i++;
    }
    return true;
  }
};

class PathHash {
public:
  std::size_t operator()(const Path& p) const
  {
    std::size_t hash = 0;
    if (p.mIsZero) return hash;
    if (p.mIsVertex) {
      hash = p.mStartVertex;
      return hash;
    }
    hash = p.mPath[0];
    for (auto e : p.mPath) 
    {
       hash ^= e + 0x9e3779b9 + (hash << 6) + (hash >> 2);
       //hash += 12345*hash + e + 1;
    }
    return hash;
  }
};
