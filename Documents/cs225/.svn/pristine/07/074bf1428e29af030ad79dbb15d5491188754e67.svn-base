#include "StickerSheet.h"
#include "Image.h"

int main() {
  Image RF;
  RF.readFromFile("RF.png");

  Image tennis;
  tennis.readFromFile("tennis.png");

  Image sign;
  sign.readFromFile("RF_sign.png");

  Image Wimbledon;
  Wimbledon.readFromFile("Wimbledon.png");

  StickerSheet sheet(RF, 5);
  sheet.addSticker(sign, 10, 40);
  sheet.addSticker(tennis, 0, 700);
  sheet.addSticker(Wimbledon, 500, 900);

  Image final;
  final = sheet.render();
  final.writeToFile("myImage.png");

  return 0;
}
