#include "Path.hpp"
#include <cstring>

// This is kinda sorta pseudo code, we cant actually go from an ID to a label because we can't access the path table
// commenting out for compilation sake
/*
std::string Path::printLabels()
{
  std::string output = "";
  int i = 0;
  for(EdgeID itr: this->mPath) {
    if(i+1 == this->mPath.size()){
      output.append(mPathTable[EdgeID].edgeLabel);
    } else {
      output.append(mPathTable[EdgeID].edgeLabel + ", ");
    }
  }
  return output;
}
*/

std::string Path::printEdgeID() const
{
  std::string output = "";
  int i = 0;
  if (mIsZero) return "";
  if (mIsVertex) return std::to_string(mStartVertex);
  for(EdgeID itr: this->mPath) {
    if(i+1 == this->mPath.size()){
      output.append(std::to_string(itr));
    } else {
      output.append(std::to_string(itr) + ", ");
    }
    i++;
  }
  return output;
}

PathID Path::getID() {
  return this->mPathID;
}

// Very naive, O(wordLen)
// Because this isn't an ordered list I don't know any faster way than parallellizing
int Path::isSubword(const Path& subPath, const Path& superPath) {
  std::vector<EdgeID> subword = subPath.getEdgeList();
  std::vector<EdgeID> word = superPath.getEdgeList();
  size_t wordLen = superPath.length();
  size_t subLen = subPath.length();
  

  for (int i = 0; i < wordLen; i++)
  {
    if(wordLen-i <= subLen)
      break;
    if(word[i] == subword[0] && memcmp(&(word[i]), &subword[0], subLen))
      return i;
  }

  return -1;

  // Replaced with memcmp method, keeping incase that isn't working properly
  /*
  std::vector<EdgeID> subList = sub.getEdgeList();
  std::vector<EdgeID> wordList = word.getEdgeList();
  size_t wordLen = word.length();
  size_t subLen = sub.length();
  int s = 0;
  int location = -1;
  int nextStartLetter = -1;

  for (int i = 0; i < wordLen; i++)
  {
    if(subList[s] == wordList[i]) // If our current letters match, continue on
    {
      if(s == 0)
        location = i;
      else if(wordList[i] == subList[0])
        nextStartLetter = i;
      s++;
    }
    else if (nextStartLetter != -1) // If our current letters don't match and we had a previous instance of the first letter, continue on.
    {
      location = nextStartLetter;
      s = 0;
      nextStartLetter = -1;
    }
    else if (s != 0 && subList[0] == wordList[i]) // If current letters don't match, but wordList[i] is the start letter, restart.
    {
      location = i;
      s = 1;
    }
    else
    {
      location = -1;
      s = 0;
    }
    if (s == subLen)
      return location;
  }
  return -1;
  */
}

// return (i,j) where subword j in subDict is found in position i of word.
std::pair<int,int> Path::isAnySubword(const std::vector<Path>& subDict, const Path& superPath){
  std::vector<EdgeID> word = superPath.getEdgeList();
  size_t wordLen = superPath.length();
  int j = 0;
  for (int i = 0; i < wordLen; i++)
  {
    for (int j = 0; j < subDict.size(); ++j)
    {
      if(!(wordLen-i <= subDict[j].length()) &&
         word[i] == subDict[j].mPath[0] &&
         memcmp(&(word[i]), &subDict[j].mPath[0], subDict[j].length()*sizeof(EdgeID)))
        return {i,j};
      ++j;
    }
  }
  return {-1,-1};
}

int Path::findOverlap(const Path& prefix){
  for (int i = 0; i < this->length(); i++){
    if((this->length()-i) <= prefix.length() &&
       memcmp(&(this->mPath[i]), &(prefix.mPath[0]), (this->length()-i)*sizeof(EdgeID)))
      return i;
  }
  return -1;
}
