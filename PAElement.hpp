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
  friend class SumCollector;

private:
  // read TODO on l61
  //std::vector<PathID> mPaths;
  //std::vector<FieldElement> mCoeffs;
  // MAJOR TODO Is it better to store these as a vector of pairs
  // vs writing a zipper iterator?
  std::vector<Term> polynomial;
  std::vector<Term> combineVectors(std::vector<PathID> paths,
				   std::vector<FieldElement> coeffs);


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

  // in the meantime, just expose begin() and end() from polynomial
  auto begin() -> decltype(polynomial.begin()) { return polynomial.begin(); }
  auto end() -> decltype(polynomial.end()) { return polynomial.end(); }
  auto cbegin() const -> decltype(polynomial.cbegin()) { return polynomial.cbegin(); }
  auto cend() const -> decltype(polynomial.cend()) { return polynomial.cend(); }

  long numTerms() { return polynomial.size(); }
  PathID leadTermID() {
    if (numTerms() == 0) return 0;
    return polynomial[0].pathID;
  }
};

// define (where necessary) pre/postfix ++ operators for Iterators

