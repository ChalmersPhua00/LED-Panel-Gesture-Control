#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <RGBmatrixPanel.h>
#define CLK 8
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
int p1X, p1Y, p2X, p2Y;

RF24 radio(18, 19);
const byte address[6] = "00001";

int r1 = 255;
int g1 = 0;
int b1 = 0;
int r2 = 255;
int g2 = 0;
int b2 = 0;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  matrix.begin();
  for (int x = 0; x < 32; x++) {
    for(int y = 0; y < 16; y++) {
      matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
    }
  }
  p1X = 0, p1Y = 0, p2X = 31, p2Y = 15;
}

void loop() {
  char text[32] = "";
  if (radio.available()) {
    radio.read(&text, sizeof(text));
  }


  if (text[0] == 'R') {
    int value = atoi(text + 2);
    if (text[1] == '1') {
      r1 = value;
    } else if (text[1] == '2') {
      r2 = value;
    }
  } else if (text[0] == 'G') {
    int value = atoi(text + 2);
    if (text[1] == '1') {
      g1 = value;
    } else if (text[1] == '2') {
      g2 = value;
    }
  } else if (text[0] == 'B') {
    int value = atoi(text + 2);
    if (text[1] == '1') {
      b1 = value;
    } else if (text[1] == '2') {
      b2 = value;
    }
  }


  if (strcmp(text, "1Up") == 0 && p1Y >= 1) {
    p1Y--;
  } else if (strcmp(text, "1Down") == 0 && p1Y <= 14) {
    p1Y++;
  } else if (strcmp(text, "1Left") == 0 && p1X >= 1) {
    p1X--;
  } else if (strcmp(text, "1Right") == 0 && p1X <= 30) {
    p1X++;
  } else if (strcmp(text, "1button1") == 0) {
    setup();
  }


  if (strcmp(text, "2Up") == 0 && p2Y >= 1) {
    p2Y--;
  } else if (strcmp(text, "2Down") == 0 && p2Y <= 14) {
    p2Y++;
  } else if (strcmp(text, "2Left") == 0 && p2X >= 1) {
    p2X--;
  } else if (strcmp(text, "2Right") == 0 && p2X <= 30) {
    p2X++;
  } else if (strcmp(text, "2button1") == 0) {
    setup();
  }


  matrix.drawPixel(p1X, p1Y, matrix.Color333(r1, g1, b1));
  matrix.drawPixel(p2X, p2Y, matrix.Color333(r2, g2, b2));
}