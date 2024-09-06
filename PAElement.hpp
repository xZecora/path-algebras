#pragma once

#include "Field.hpp"
#include "Path.hpp"
#include "util.hpp"

class PAElement
{
public:

  PAElement(std::vector<PathID> &paths,
	    std::vector<FieldElement> &coeffs);

  PAElement(PathID path, FieldElement coeff) : 
    mPaths({path}),
    mCoeffs({coeff})
  {
  }

  PAElement(PathID path) :
    mPaths({path}),
    mCoeffs({FieldElement { 1 }})
  {
  }

  PAElement() = default;

  // iterator for the PAElement type so that something like the following should work:
  // for f a PAElement
  // for (auto it = f.begin(); it != f.end(); ++it) { stuff }
  // or:  for (auto it : f) { stuff }

  class PAElementIterator {
  public:
  private:
     // iterator for the paths std::vector
     // iterator for the coefficients std::vector
  };
  // ConstPAElementIterator as well

  PAElementIterator begin();

  // ConstPAElementIterator cbegin();

private:
  std::vector<PathID> mPaths;
  std::vector<FieldElement> mCoeffs;
};

// define (where necessary) pre/postfix ++ operators for Iterators

