/* Your code here! */
#include "maze.h"
#include <cstdlib>
#include <queue>
using namespace cs225;

SquareMaze::SquareMaze() {
}

void SquareMaze::makeMaze (int width, int height) {
  width_ = width;
  height_ = height;
  size_ = width * height;

  // create DisjointSets
  DisjointSets cells = DisjointSets();
  cells.addelements(size_);
  // create walls
  rightWalls = vector<bool> (size_, true);
  downWalls = vector<bool> (size_, true);

  int i = 0;
  // break walls
  while (i < size_ - 1) {
    // pick a cell and dir randomly
    int cellIdx = rand() % size_;
    int rowIdx = cellIdx / width_;
    int colIdx = cellIdx % width_;
    // 0 -- right; 1 -- down;
    int breakDir = rand() % 2;

    // break right walls
    if (breakDir == 0 && colIdx != width_ -1 && rightWalls[cellIdx] == true
      && cells.find(cellIdx) != cells.find(cellIdx+1)) {
      rightWalls[cellIdx] = false;
      cells.setunion(cellIdx, cellIdx+1);
      i++;
    }
    // break down walls
    if (rowIdx != height_ -1 && breakDir == 1 && downWalls[cellIdx] == true
      && cells.find(cellIdx) != cells.find(cellIdx+width_)) {
        downWalls[cellIdx] = false;
        cells.setunion(cellIdx, cellIdx+width_);
        i++;
      }
  }
}


bool SquareMaze::canTravel (int x, int y, int dir) const {
  // right
  if (dir == 0) {
    if (x == width_ -1) return false;
    return (rightWalls[y * width_ + x] == false);
  }
  // down
  if (dir == 1) {
    if (y == height_ -1) return false;
    return (downWalls[y * width_ + x] == false);
  }
  // left
  if (dir == 2) {
    if (x == 0) return false;
    return (rightWalls[y * width_ + x-1] == false);
  }
  // up
  if (dir == 3) {
    if (y == 0) return false;
    return (downWalls[y * width_ + x - width_] == false);
  }
  return false;
}


void SquareMaze::setWall (int x, int y, int dir, bool exists) {
  // right
  if (dir == 0 && x != width_ -1) {
    rightWalls[y * width_ + x] = exists;
  }
  // down
  if (dir == 1 && y != height_ -1) {
    downWalls[y * width_ + x] = exists;
  }
}


vector< int > SquareMaze::solveMaze () {
  queue<int> q;
  q.push(0);
  parent = vector<int> (size_, -1);
  distance = vector<int> (size_, -1);
  distance[0] = 0;

  while (!q.empty()) {
    int a = q.front();
    int aX = a % width_;
    int aY = a / width_;
    q.pop();

    // right 0
    if (canTravel(aX, aY, 0)) {
      if (distance[a +1] == -1) {
        q.push(a + 1);
        parent[a + 1] = a;
        distance[a + 1] = distance[a] +1;
      }
    }
    // down 1
    if (canTravel(aX, aY, 1)) {
      if (distance[a + width_] == -1) {
        q.push(a + width_);
        parent[a + width_] = a;
        distance[a + width_] = distance[a] +1;
      }
    }
    // left 2
    if (canTravel(aX, aY, 2)) {
      if (distance[a -1] == -1) {
        q.push(a - 1);
        parent[a - 1] = a;
        distance[a - 1] = distance[a] +1;
      }
    }
    // up 3
    if (canTravel(aX, aY, 3)) {
      if (distance[a - width_] == -1) {
        q.push(a - width_);
        parent[a - width_] = a;
        distance[a - width_] = distance[a] +1;
      }
    }
  }

  int maxIdx = 0;
  int maxDis = 0;
  for (int i = (height_ - 1)*width_; i < size_; i++) {
    if (distance[i] > maxDis) {
      maxDis = distance[i];
      maxIdx = i;
    }
  }

  solution = vector<int> (maxDis, -1);
  for (int i = 0; i < maxDis; i++) {
    // right 0
    if (parent[maxIdx] == maxIdx -1) {
      solution[maxDis-1-i] = 0;
      maxIdx = maxIdx -1;
    }
    // down 1
    else if (parent[maxIdx] == maxIdx -width_) {
      solution[maxDis-1-i] = 1;
      maxIdx = maxIdx -width_;
    }
    // left 2
    else if (parent[maxIdx] == maxIdx +1) {
      solution[maxDis-1-i] = 2;
      maxIdx = maxIdx +1;
    }
    // up 3
    else if (parent[maxIdx] == maxIdx +width_) {
      solution[maxDis-1-i] = 3;
      maxIdx = maxIdx +width_;
    }
  }
  return solution;
}

cs225::PNG * SquareMaze::drawMaze () const {
  PNG * maze = new PNG(10 * width_ + 1, 10 * height_ + 1);
  HSLAPixel black = HSLAPixel(0, 0, 0, 1);
  // top most row
  for (int i = 10; i < 10 * width_ + 1; i++) {
    *(maze->getPixel(i, 0)) = black;
  }
  // lefmost column
  for (int i = 0; i < 10 * height_ + 1; i++) {
    *(maze->getPixel(0, i)) = black;
  }

  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {

      if (downWalls[i + j * width_]) {
        for (int k = 0; k < 11; k++) {
          int drawX = i * 10 + k;
          int drawY = (j + 1) * 10;
          *(maze->getPixel(drawX, drawY)) = black;
        }
      }

      if (rightWalls[i + j * width_]) {
        for (int k = 0; k < 11; k++) {
          int drawX = (i + 1) * 10;
          int drawY = j * 10 + k;
          *(maze->getPixel(drawX, drawY)) = black;
        }
      }
    }
  }
  return maze;
}

cs225::PNG * SquareMaze::drawMazeWithSolution () {
  PNG * mazeSol = drawMaze();
  HSLAPixel red = HSLAPixel(0, 1, 0.5, 1);

  int staX = 5;
  int staY = 5;
  for (size_t i = 0; i < solution.size(); i++) {
    // right
    if (solution[i] == 0) {
      for (int j = 0; j < 11; j++) {
        //int curIdx = staX + j + staY * (10 * height_ + 1);
         *(mazeSol->getPixel(staX + j, staY)) = red;
      }
      staX += 10;
    }
    // down 1
    else if (solution[i] == 1) {
      for (int j = 0; j < 11; j++) {
        //int curIdx = staX + (staY + j) * (10 * height_ + 1);
        *(mazeSol->getPixel(staX, staY + j)) = red;
      }
      staY += 10;
    }
    // left 2
    else if (solution[i] == 2) {
      for (int j = 0; j < 11; j++) {
        // int curIdx = staX - j + staY * (10 * height_ + 1);
        *(mazeSol->getPixel(staX - j, staY)) = red;
      }
      staX -= 10;
    }
    // up 3
    else if (solution[i] == 3) {
      for (int j = 0; j < 11; j++) {
        //int curIdx = staX + (staY - j) * (10 * height_ + 1);
        *(mazeSol->getPixel(staX, staY -j)) = red;
      }
      staY -= 10;
    }
  }

  int endX = staX -5;
  int endY = staY +5;
  HSLAPixel white = HSLAPixel(0, 0, 1, 1);
  for (int i = 1; i < 10; i++) {
    //int curIdx = endX + i + endY * (10 * height_ + 1);
    *(mazeSol->getPixel(endX + i, endY)) = white;
  }

  return mazeSol;
}
