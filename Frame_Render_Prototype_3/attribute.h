#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

class Attribute {
 public:
  // Constructors
  Attribute(unsigned _maxValue = 0, unsigned _attributeValue = 0);

  unsigned getValue() const { return attributeValue; }
  void setValue(unsigned _attributeValue);
  void addValue(unsigned addAmount);
  void removeValue(unsigned removeAmount);

  unsigned getMaxValue() const { return maxValue; }
  void setMaxValue(unsigned _maxValue);

 private:
  unsigned attributeValue = 0;
  unsigned maxValue = 0;
};

#endif