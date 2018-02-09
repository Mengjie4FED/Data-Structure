/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
 #include <algorithm>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] < second[curDim]) {
       return true;
     } else if (first[curDim] > second[curDim]) {
       return false;
     } else {
       if (first < second) {
         return true;
       } else {
         return false;
       }
     }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double disP = 0;
     double disC = 0;
     for (int i = 0; i < Dim; i++ ) {
       disP += (potential[i] - target[i]) * (potential[i] - target[i]);
       disC += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
     }
     if (disP < disC) {
       return true;
     } else if (disP > disC) {
       return false;
     } else {
       if (potential < currentBest) {
         return true;
       } else {
         return false;
       }
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     if (newPoints.empty()) {return;}
     KDTreeHelper(points, 0, points.size() - 1, 0);

}

template <int Dim>
void KDTree<Dim>::KDTreeHelper(vector<Point<Dim>>& points, int left, int right, int curDim) {
  if (left >= right) {
    return;
  }

  quickSelectKth(points, left, right, (left+right)/2, curDim%Dim);
  KDTreeHelper(points, left, ((left+right)/2)-1, (curDim+1)%Dim);
  KDTreeHelper(points, ((left+right)/2)+1, right, (curDim+1)%Dim);
}


template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIndex, int curDim) {
  Point<Dim> pivotValue = newPoints[pivotIndex];
  std::swap(newPoints[pivotIndex], newPoints[right]);
  int storeIndex = left;
  for (int i = left; i < right; i++) {
    if (smallerDimVal(newPoints[i], pivotValue, curDim)) {
      std::swap(newPoints[storeIndex], newPoints[i]);
      storeIndex += 1;
    }
  }
  std::swap(newPoints[right], newPoints[storeIndex]);
  return storeIndex;
}

/*template <int Dim>
void KDTree<Dim>::swap(const vector<Point<Dim>>& newPoints, int left, int right) {
  Point<Dim> temp = newPoints[left];
  newPoints[left] = newPoints[right];
  newPoints[right] = temp;
}*/

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelectKth(vector<Point<Dim>>& newPoints, int left, int right, int k, int curDim) {
  if (left == right) {
    return newPoints[left];
  }
  //int k = (left + right) / 2;
  int pivotIndex = (left + right)/2;
  pivotIndex = partition(newPoints, left, right, pivotIndex, curDim);
  if (k == pivotIndex) {
    return newPoints[k];
  } else if (k < pivotIndex) {
    return quickSelectKth(newPoints, left, pivotIndex-1, k, curDim);
  } else {
    return quickSelectKth(newPoints, pivotIndex+1, right, k, curDim);
  }
}



template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> currentBest = points[0];
    findNNHelp(points, query, 0, points.size()-1, 0, currentBest);
    return currentBest;
}


template <int Dim>
void KDTree<Dim>::findNNHelp(const vector<Point<Dim>>& points, const Point<Dim>& query, int left, int right, int curDim, Point<Dim>& currentBest) const {
  if (left > right) {
    return;
  }
  if (left == right) {
    if (shouldReplace(query, currentBest, points[left])) {
      currentBest = points[left];
    }
    return;
  }

  if (smallerDimVal(query, points[(left+right)/2], curDim)) {
    findNNHelp(points, query, left, (left+right)/2 -1, (curDim+1)%Dim, currentBest);
    if (shouldReplace(query, currentBest, points[(left+right)/2])) {
      currentBest = points[(left+right)/2];
    }
    if ( (points[(left+right)/2][curDim] - query[curDim])*(points[(left+right)/2][curDim] - query[curDim]) <= distance(query, currentBest)) {
      findNNHelp(points, query, (left+right)/2 +1, right, (curDim+1)%Dim, currentBest);
    }

  } else {
    findNNHelp(points, query, (left+right)/2 +1, right, (curDim+1)%Dim, currentBest);
    if (shouldReplace(query, currentBest, points[(left+right)/2])) {
      currentBest = points[(left+right)/2];
    }
    if ( (points[(left+right)/2][curDim] - query[curDim])*(points[(left+right)/2][curDim] - query[curDim]) <= distance(query, currentBest)) {
      findNNHelp(points, query, left, (left+right)/2 -1, (curDim+1)%Dim, currentBest);
    }
  }



}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& first, const Point<Dim>& second) const {
  double dis = 0;
  for (int i = 0; i < Dim; i++ ) {
    dis += (first[i] - second[i]) * (first[i] - second[i]);
  }
  return dis;
}
