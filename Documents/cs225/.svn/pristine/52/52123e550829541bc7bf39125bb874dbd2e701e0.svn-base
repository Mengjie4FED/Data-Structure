#include <string>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {


  PNG original = PNG();
  original.readFromFile(inputFile);

  unsigned int width = original.width();
  unsigned int height = original.height();

  PNG output = PNG(width, height);

  for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {

          HSLAPixel* rotPixel = original.getPixel(width-x-1, height-y-1);

          HSLAPixel* currOutPixel = output.getPixel(x, y);

          *currOutPixel = *rotPixel;

      }
  }



  output.writeToFile(outputFile);


}
