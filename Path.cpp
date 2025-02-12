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
    if(word[i] == subword[0] && memcmp(&(word[i]), &subword, subLen))
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

int Path::isAnySubword(const std::vector<Path>& subDict, const Path& superPath){
  std::vector<EdgeID> word = superPath.getEdgeList();
  size_t wordLen = superPath.length();

  // I want to remove elements for subDict to shorten checks later on.
  std::vector<Path> dictCopy = subDict;

  for (int i = 0; i < wordLen; i++)
    for (auto subWord : dictCopy)
      if(!(wordLen-i <= subWord.length()) && word[i] == subWord.mPath[0] && memcmp(&(word[i]), &subWord, subWord.length()*sizeof(EdgeID)))
        return i;

  return -1;
}
