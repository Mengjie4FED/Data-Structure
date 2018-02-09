
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_ = &png;
  start_ = start;
  tolerance_ = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  queuePoint.push(start_);

  ImageTraversal::Iterator beginIte = ImageTraversal::Iterator();
  beginIte.currP = start_;
  unsigned int pW = png_->width();
  unsigned int pH = png_->height();
  beginIte.visited = new bool[pW * pH];
  std::fill_n(beginIte.visited, pW * pH, false);
  beginIte.visited[(start_.y)*pW + start_.x] = true;

  beginIte.ImageTraversal_ = this;

  return beginIte;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator endIte = ImageTraversal::Iterator();
  endIte.ImageTraversal_ = NULL;
  return endIte;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  queuePoint.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point front = queuePoint.front();
  queuePoint.pop();
  return front;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  Point front = queuePoint.front();
  return front;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  bool isEmp = queuePoint.empty();
  return isEmp;
}
