#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
MyColorPicker::MyColorPicker(double increment) {
  s = 0.32;
  hue = 185;
  increment_ = increment;
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, s, 0.8);
  s += increment_;
  hue += increment_;
  if (s >= 0.8) {s -= 0.8;}
  if (hue >= 250) {hue -= 250;}
  return pixel;
  //return HSLAPixel(185, 0.32, 0.8);
}
