#include "HSLAPixel.h"
namespace cs225 {
  HSLAPixel::HSLAPixel () {
    l = 1;
    a = 1;
  }

  HSLAPixel::HSLAPixel (double hue, double saturation, double luminance) {
    a = 1;
    h = hue;
    s = saturation;
    l = luminance;
  }

  HSLAPixel::HSLAPixel (double hue, double saturation, double luminance, double alpha) {
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
  }
}
