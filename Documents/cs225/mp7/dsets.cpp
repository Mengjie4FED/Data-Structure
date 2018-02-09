/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    disSets.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (disSets[elem] < 0) {
    return elem;
  } else {
    disSets[elem] = find(disSets[elem]);
    return find(disSets[elem]);
  }
}

void DisjointSets::setunion(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) {return;}

  int newSize = disSets[a] + disSets[b];

  if (disSets[a] <= disSets[b]) {
    disSets[b] = a;
    disSets[a] = newSize;
  } else {
    disSets[a] = b;
    disSets[b] = newSize;
  }
}

int DisjointSets::size(int elem) {
  return -disSets[find(elem)];
}
