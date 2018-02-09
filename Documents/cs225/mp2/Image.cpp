#include "Image.h"
#include "cs225/PNG.h"
using namespace cs225;

void Image::lighten	() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double l = pixel->l + 0.1;
      if (l >= 1) {pixel->l = 1;}
      else pixel->l = l;
    }
  }
}


void Image::lighten	(	double 	amount ) {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double l = pixel->l + amount;
      if (l >= 1) {pixel->l = 1;}
      else pixel->l = l;
    }
  }
}

void Image::darken	() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double l = pixel->l - 0.1;
      if (l <= 0) {pixel->l = 0;}
      else pixel->l = l;
    }
  }
}

void Image::darken	(	double 	amount ) {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double l = pixel->l - amount;
      if (l <= 0) {pixel->l = 0;}
      else pixel->l = l;
    }
  }
}

void Image::saturate	() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double s = pixel->s + 0.1;
      if (s >= 1) {pixel->s = 1;}
      else pixel->s = s;
    }
  }
}

void Image::saturate	(	double 	amount ) {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double s = pixel->s + amount;
      if (s >= 1) {pixel->s = 1;}
      else pixel->s = s;
    }
  }
}

void Image::desaturate	() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double s = pixel->s - 0.1;
      if (s <= 0) {pixel->s = 0;}
      else pixel->s = s;
    }
  }
}

void Image::desaturate	(	double 	amount ) {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

      double s = pixel->s - amount;
      if (s <= 0) {pixel->s = 0;}
      else pixel->s = s;
    }
  }
}

void Image::grayscale	() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);
      pixel->s = 0;
    }
  }
}


void Image::rotateColor	(	double 	degrees	) {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);
      int h = pixel->h + degrees;
      if (h > 360) {pixel->h = h - 360;}
      else if (h < 0) {pixel->h = h + 360;}
      else pixel->h = h;
    }
  }
}


void Image::illinify	() {

  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);

    if ( pixel->h > (11+216)/2 && pixel->h < (11+216)/2+179) {
      pixel->h = 216;
    }
    else {
      pixel->h = 11;
    }
  }
}
}


void Image::scale	(	double factor )	{

  int oldW = width();
  HSLAPixel * oldImage = new HSLAPixel[width() * height()];
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel *oldPixel = this->getPixel(x, y);
        HSLAPixel & copyPixel = oldImage[ (x + ( y * width() )) ];
        copyPixel = *oldPixel;
    }
  }

  double newWidth = width() * factor;
  double newHeight = height() * factor;
  resize(newWidth, newHeight);

  for (unsigned x = 0; x < newWidth; x++) {
    for (unsigned y = 0; y < newHeight; y++) {
        int ox = static_cast<int> (x/factor);
        int oy = static_cast<int> (y/factor);
        HSLAPixel & oriPixel = oldImage[ (ox + (oy * oldW)) ];
        HSLAPixel * newPixel = this->getPixel(x, y);
        *newPixel = oriPixel;
    }
  }
  delete[] oldImage;
}


void Image::scale	(	unsigned w, unsigned h )	{
  unsigned int oldW = width();
  unsigned int oldH = height();
  double ratio = double(oldW) / double(oldH);
  double f = 0;
  if ( double(w) / double(h) >= ratio) {f = double(h) / double(oldH) ;}
  else f = double(w) / double(oldW);
  Image::scale (f);

}
