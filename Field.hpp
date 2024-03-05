class FieldElement{
  unsigned int element;
};

class Field {
  FieldElement add(FieldElement a, FieldElement b);
  FieldElement subtract(FieldElement a, FieldElement b);
  FieldElement multiply(FieldElement a, FieldElement b);
  FieldElement divide(FieldElement a, FieldElement b);
};
