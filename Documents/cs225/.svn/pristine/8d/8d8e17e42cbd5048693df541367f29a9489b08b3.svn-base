/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"

using namespace std;

class SquareMaze {
public:
  SquareMaze();
  void makeMaze (int width, int height);
  bool canTravel (int x, int y, int dir) const;
  void setWall (int x, int y, int dir, bool exists);
  vector< int > solveMaze ();
  cs225::PNG * drawMaze () const;
  cs225::PNG * drawMazeWithSolution ();

private:
  int width_;
  int height_;
  int size_;
  vector<bool> rightWalls;
  vector<bool> downWalls;
  vector<int> parent;
  vector<int> distance;
  vector<int> solution;
};

#endif
