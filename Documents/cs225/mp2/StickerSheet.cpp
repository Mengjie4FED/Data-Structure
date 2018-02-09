#include "StickerSheet.h"
using namespace std;

StickerSheet::StickerSheet	(	const Image & picture, unsigned max){
  basePic_ = picture;
  max_ = max;
  stickers_ = new Image*[max];
  x_ = new unsigned[max];
  y_ = new unsigned[max];

  for (unsigned i = 0; i < max; i++) {
    stickers_[i] = NULL;
    x_[i] = 0;
    y_[i] = 0;
  }
}


StickerSheet::~StickerSheet () {
  _clear();
}

void StickerSheet::_clear() {
  for(unsigned i = 0; i < max_; i++){
    delete stickers_[i];
    stickers_[i] = NULL;
  }

 delete[] stickers_;
 delete[] x_;
 delete[] y_;
 stickers_ = NULL;
 x_ = NULL;
 y_ = NULL;
}

StickerSheet::StickerSheet (const StickerSheet &other) {
  _copy(other);
}

void StickerSheet::_copy(const StickerSheet &other) {
  basePic_ = other.basePic_;
  max_ = other.max_;
  stickers_ = new Image*[max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];

  for (unsigned i = 0; i < max_; i++) {
    if (other.stickers_[i] != NULL) {
      x_[i] = other.x_[i];
      y_[i] = other.y_[i];
      stickers_[i] = new Image(*(other.stickers_[i]));
    }
    else {
      x_[i] = 0;
      y_[i] = 0;
      stickers_[i] = NULL;
    }
  }
}

const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other) {
  if (this != &other)  {
    _clear();
    _copy(other);
  }
  return *this;
}


void 	StickerSheet::changeMaxStickers (unsigned max) {
  if (max == max_) {
    return;
  }

  Image ** newstickers = new Image*[max];
  unsigned * newx = new unsigned[max];
  unsigned * newy = new unsigned[max];

  if (max > max_) {

    for (unsigned i = 0; i < max_; i++) {
      newx[i] = x_[i];
      newy[i] = y_[i];

      if (stickers_[i] != NULL) {
        newstickers[i] = new Image(*stickers_[i]);
      }
      else {
        newstickers[i] = NULL;
      }
    }

    for (unsigned i = max_; i < max; i++) {
      newstickers[i] = NULL;
      newx[i] = 0;
      newy[i] = 0;
    }

  }

  if (max < max_) {

    for(unsigned i = 0; i < max; i++){
	    newx[i] = x_[i];
	    newy[i] = y_[i];

      if (stickers_[i] != NULL) {
        newstickers[i] = new Image(*stickers_[i]);
      }
	    else {
        newstickers[i] = NULL;
      }

    }

  }

  _clear();
  max_ = max;
  x_ = newx;
  y_ = newy;
  stickers_ = newstickers;
}


int 	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
  unsigned i = 0;

  while (i < max_) {
    if (stickers_[i] == NULL) {
      stickers_[i] = new Image(sticker);
      x_[i] = x;
      y_[i] = y;
      return i;
    } else {
      i += 1;
    }
  }
  return -1;
}


bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
  if (index > max_-1 || stickers_[index] == NULL) {
     return false;
   } else {
     x_[index] = x;
     y_[index] = y;
     return true;
   }
}


void  StickerSheet::removeSticker (unsigned index) {
  delete stickers_[index];
  stickers_[index] = NULL;
}

Image *  StickerSheet::getSticker (unsigned index) const {
  if (index > max_-1 || stickers_[index] == NULL) {
     return NULL;
  }
  return stickers_[index];
}


Image  StickerSheet::render () const{
  unsigned width = basePic_.width();
  unsigned height = basePic_.height();

  for (unsigned i = 0; i < max_; i++) {
    if (stickers_[i] != NULL) {
      if ((x_[i] + stickers_[i]->width()) > width) {
        width = x_[i] + stickers_[i]->width();
      }
      if ((y_[i] + stickers_[i]->height()) > height) {
        height = y_[i] + stickers_[i]->height();
      }
    }
  }

  Image render = basePic_;
  render.resize(width, height);

  for (unsigned i = 0; i < max_; i++) {
    if (stickers_[i] != NULL) {
      for (unsigned j = x_[i]; j < x_[i] + stickers_[i]->width(); j++) {
        for (unsigned k = y_[i]; k < y_[i] + stickers_[i]->height(); k++) {
          if (stickers_[i]->getPixel(j - x_[i], k - y_[i])->a != 0) {
            cs225::HSLAPixel * basePixel = render.getPixel(j, k);
            *basePixel = *(stickers_[i]->getPixel(j - x_[i], k - y_[i]));
          }
        }
      }
    }
  }
  return render;
}
