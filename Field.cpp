#include "Field.hpp"

// implement logarithmic exponentiation
FieldElement Field::power(FieldElement a, unsigned int pow)
{
   unsigned int newPow = pow % (mCharacteristic - 1);
   FieldElement result {1};
   FieldElement curPow {a};
   while (newPow != 0)
   {
      if (newPow % 2) result = multiply(result,curPow);
      newPow >>= 1;
      curPow = multiply(curPow,curPow);
   }
   return result;
}

