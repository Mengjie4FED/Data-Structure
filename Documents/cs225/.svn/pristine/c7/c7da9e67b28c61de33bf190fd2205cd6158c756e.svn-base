/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
     int rows = theSource.getRows();
     int cols = theSource.getColumns();
     MosaicCanvas::MosaicCanvas *mosaic = new MosaicCanvas(rows, cols);

    vector<Point<3>> aveCol;
    map<Point<3>, TileImage> mapToTile;

    for (unsigned i = 0; i < theTiles.size(); i++) {
      HSLAPixel avePix = theTiles[i].getAverageColor();
      Point<3> avePixPoint((avePix.h)/360, avePix.s, avePix.l);

      aveCol.push_back(avePixPoint);
      mapToTile[avePixPoint] = theTiles[i];
    }

    KDTree<3>::KDTree kdTree(aveCol);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {

        HSLAPixel aveSouPix = theSource.getRegionColor(i, j);
        Point<3> aveSouPoint((aveSouPix.h)/360, aveSouPix.s, aveSouPix.l);
        Point<3> nnPoint = kdTree.findNearestNeighbor(aveSouPoint);

        TileImage setTile = mapToTile[nnPoint];
        mosaic->setTile(i, j, setTile);
      }
    }


    return mosaic;
}
