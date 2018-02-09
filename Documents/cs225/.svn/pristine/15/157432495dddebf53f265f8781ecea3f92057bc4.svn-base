#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  visited = new bool[0];
}


bool ImageTraversal::Iterator::isAddPoint(unsigned x, unsigned y) {
  bool isPixNotNull = (x < ImageTraversal_->png_->width()) && (y < ImageTraversal_->png_->height());
  if (isPixNotNull == false) {
    return false;
  }
  unsigned stPX = ImageTraversal_->start_.x;
  unsigned stPY = ImageTraversal_->start_.y;
  bool isTole = ImageTraversal_->calculateDelta(*(ImageTraversal_->png_->getPixel(stPX, stPY)), *(ImageTraversal_->png_->getPixel(x, y))) < ImageTraversal_->tolerance_;
  return isPixNotNull && isTole;
}

unsigned ImageTraversal::Iterator::locPix(const Point & t) {
  unsigned pngW = ImageTraversal_->png_->width();
  //unsigned pngH = ImageTraversal_->png_->height();
  return ((t.y)*pngW + (t.x));
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {

  /** @todo [Part 1] */
  unsigned currX = currP.x;
  unsigned currY = currP.y;
  // 加所有的nei， 不为空 不超tole，不判断vis
  Point neiP;
  if (isAddPoint(currX+1, currY)) {
    neiP = Point(currX+1, currY);
    ImageTraversal_->add(neiP);
  }
  if (isAddPoint(currX, currY+1)) {
    neiP = Point(currX, currY+1);
    ImageTraversal_->add(neiP);
  }
  if (isAddPoint(currX-1, currY)) {
    neiP = Point(currX-1, currY);
    ImageTraversal_->add(neiP);
  }
  if (isAddPoint(currX, currY-1)) {
    neiP = Point(currX, currY-1);
    ImageTraversal_->add(neiP);
  }


  //pop判断是否visi， 没有就是下一个ite 改visi，不然接着pop，直到emp就结束

  while (ImageTraversal_->empty() != true) {
    Point popPoi = ImageTraversal_->pop();

    if (visited[locPix(popPoi)] == false) { //没走过
      currP = popPoi;
      visited[locPix(popPoi)] = true;
      return *this;
    }
  }

  if (ImageTraversal_->empty() == true) {
    ImageTraversal_ = NULL;

  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currP;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return ImageTraversal_ != other.ImageTraversal_;
}


ImageTraversal::Iterator::~Iterator() {
    delete[] visited;
    // visited = NULL;
}
