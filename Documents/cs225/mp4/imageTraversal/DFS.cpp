#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>
#include <array>
#include <algorithm>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png_ = &png;
  start_ = start;
  tolerance_ = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  stackPoint.push(start_);
  // 返回起始的iterator
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
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  ImageTraversal::Iterator endIte = ImageTraversal::Iterator();
  endIte.ImageTraversal_ = NULL;
  return endIte;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  // add 只存点
  stackPoint.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = stackPoint.top();
  stackPoint.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  Point top = stackPoint.top();
  return top;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  bool isEmp = stackPoint.empty();
  return isEmp;
}
