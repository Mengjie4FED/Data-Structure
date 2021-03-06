#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "Image.h"
#include <iostream>
#include <vector>
using namespace std;

class StickerSheet {
public:
  StickerSheet (const Image &picture, unsigned max);
  ~StickerSheet ();
  StickerSheet (const StickerSheet &other);
  const StickerSheet & 	operator= (const StickerSheet &other);

  void 	changeMaxStickers (unsigned max);
  int 	addSticker (Image &sticker, unsigned x, unsigned y);
  bool 	translate (unsigned index, unsigned x, unsigned y);
  void  removeSticker (unsigned index);
  Image *  getSticker (unsigned index) const;
  Image  render () const;

private:
  Image basePic_;
  unsigned max_;
  Image ** stickers_;
  unsigned * x_;
  unsigned * y_;

  void _clear();
  void _copy(const StickerSheet &other);

};

#endif
