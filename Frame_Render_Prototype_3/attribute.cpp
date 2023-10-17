#include "attribute.h"

Attribute::Attribute(unsigned _maxValue, unsigned _attributeValue) {
  setMaxValue(_maxValue);
  setValue(_attributeValue);
}

void Attribute::setValue(unsigned _attributeValue) {
  attributeValue = _attributeValue;
}

void Attribute::addValue(unsigned addAmount) {
  attributeValue += addAmount;
}

void Attribute::removeValue(unsigned removeAmount) {
  if (removeAmount > attributeValue) {
    attributeValue = 0;
  } else {
    attributeValue -= removeAmount;
  }
}

void Attribute::setMaxValue(unsigned _maxValue) {
  maxValue = _maxValue;
}