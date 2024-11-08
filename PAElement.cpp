#include "PAElement.hpp"

std::vector<Term> PAElement::combineVectors(std::vector<PathID> paths, std::vector<FieldElement> coeffs) {
  std::vector<Term> paired;
  
  if (paths.size() != coeffs.size())
    return paired;

  for(int i = 0; i < paths.size(); i++)
    paired.push_back({coeffs[i], paths[i]});
  
  return paired;
}
