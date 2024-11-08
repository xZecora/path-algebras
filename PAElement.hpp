#pragma once

#include "Field.hpp"
#include "Path.hpp"
#include "util.hpp"

struct Term
{
  FieldElement coeff;
  PathID pathID;
};

class PAElement
{
  friend class PathAlgebra;
public:

  // read TODO on l61
  PAElement(std::vector<PathID> &paths,
	    std::vector<FieldElement> &coeffs) {
    this->polynomial = combineVectors(paths, coeffs);
  }

  // read TODO on l61
  PAElement(PathID path, FieldElement coeff) //: 
    //mPaths({path}),
    //mCoeffs({coeff})
  {
    this->polynomial = {{coeff, path}};
    //combineVectors({path}, {coeff});
  }

  // read TODO on l61
  PAElement(PathID path) //:
    //mPaths({path}),
    //mCoeffs({FieldElement { 1 }})
  {
    this->polynomial = combineVectors({path}, {FieldElement { 1 }});
  }

  PAElement() = default;

  // read TODO on l61
  /*
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
  //

  //PAElementIterator begin();

  // ConstPAElementIterator cbegin();
  */

  long numTerms() { return polynomial.size(); }

private:
  // read TODO on l61
  //std::vector<PathID> mPaths;
  //std::vector<FieldElement> mCoeffs;
  // MAJOR TODO Is it better to store these as a vector of pairs vs writing a zipper iterator?
  std::vector<Term> polynomial;
  std::vector<Term> combineVectors(std::vector<PathID> paths, std::vector<FieldElement> coeffs);

};

// define (where necessary) pre/postfix ++ operators for Iterators

