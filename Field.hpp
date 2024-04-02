#pragma once

#include <iostream>

class FieldElement
{
  friend class Field;

  friend std::ostream& operator<<(std::ostream& ostr, const FieldElement& f);

public:
   FieldElement(unsigned int element)
     : mElement(element) { }

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
      return FieldElement {(a.mElement - b.mElement) % mCharacteristic};
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
      if (a.mElement == 0) { std::cout << "Attempting to divide by zero." << std::endl; }
      if (mCharacteristic == 2) return a;
      // any short-circuits?
      return power(a,mCharacteristic - 2);
   }

   FieldElement power(FieldElement a, unsigned int pow);

private:
  unsigned int mCharacteristic;
  
};
