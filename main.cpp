#include <iostream>
#include "Field.hpp"

int main(int argc, char** argv)
{
   FieldElement a { 10 };
   FieldElement b { 4 };
   Field myField { 101 };

   FieldElement c = myField.power(a,15);

   //std::cout << "Field element a: " << a << std::endl;
   //std::cout << "a to the power 15 in field: " << myField.power(a,15)
   //          << std::endl;

   return 0;
}
