class FieldElement
{
public:
   FieldElement(unsigned int element)
      mElement(element) {}  

private:
  unsigned int mElement;
};

// for now: this only implements finite prime fields
class Field
{
  friend class FieldElement;

  // will trust that the users inputs a prime characteristic
  Field(unsigned int characteristic)
    : mCharacteristic(characteristic) { }

public:

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
      return FieldElement {(a.mElement * invert(b.mElement)) % mCharacteristic};
   } 

   FieldElement invert(FieldElement a)
   {
      if (a.mElement == 0) { std::cout << "Attempting to divide by zero." << std::endl; }
      if (mCharacteristic == 2) then return a;
      // any short-circuits?
      return power(a,mCharacteristic - 2);
   }

   FieldElement power(FieldElement a, unsigned int pow);

private:
  unsigned int mCharacteristic;
  
};
