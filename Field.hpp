#pragma once

#include <iostream>

class FieldElement
{
  friend class Field;

  friend std::ostream& operator<<(std::ostream& ostr, const FieldElement& f);

public:
   // it is the creator's responsibility to ensure
   // that element is in the range 0 <= a < = p-1 where
   // the characteristic of whatever field we are working in is p.
   // the issue is we don't want FieldElement to know what p is for space issues.
   FieldElement(unsigned int element)
     : mElement(element) { }

   FieldElement()
     : mElement(0) { }

   bool isZero(){
     return (mElement == 0);
   }
  
  bool operator==(const FieldElement& rhs) const { return mElement == rhs.mElement; }
private:
  unsigned int mElement;
};

// for now: this only implements finite prime fields
class Field
{
public:

  // will trust that the users inputs a prime characteristic
  Field(unsigned int characteristic)
    : mCharacteristic(characteristic) { }

   inline FieldElement add(FieldElement a, FieldElement b)
   {
      return FieldElement {(a.mElement + b.mElement) % mCharacteristic};
   }

   inline FieldElement subtract(FieldElement a, FieldElement b)
   {
      if (a.mElement >= b.mElement)
	return FieldElement {a.mElement - b.mElement};
      else
	return negate(FieldElement {b.mElement - a.mElement});
   }

   inline FieldElement multiply(FieldElement a, FieldElement b)
   {
      return FieldElement {(a.mElement * b.mElement) % mCharacteristic};
   }

   FieldElement divide(FieldElement a, FieldElement b)
   {
      return FieldElement {(a.mElement * invert(b.mElement).mElement) % mCharacteristic};
   } 

   FieldElement invert(FieldElement a)
   {
      // TODO: Fix this abomination -- implement the Euclidean Algorithm...
      if (a.mElement == 0) { std::cout << "Attempting to divide by zero." << std::endl; }
      if (mCharacteristic == 2) return a;
      // any short-circuits?
      return power(a,mCharacteristic - 2);
   }

   inline FieldElement negate(FieldElement a)
   {
     //return this->subtract(FieldElement(0), a);
     if (a.mElement == 0) return a;
     return FieldElement(mCharacteristic - a.mElement);
   }

   FieldElement power(FieldElement a, unsigned int pow);

private:
  unsigned int mCharacteristic;
  
};
