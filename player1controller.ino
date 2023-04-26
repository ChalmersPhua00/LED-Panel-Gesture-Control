#include <Wire.h>
#include "paj7620.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

int xPin = A0;
int yPin = A1;
int r = 255;
int g = 0;
int b = 0;
int phase = 0;

int buttonCurrState = 0, buttonPrevState = 0;

void setup() {
  pinMode(2, INPUT);

	uint8_t error = 0;
	error = paj7620Init();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char rB[5];
  const char gB[5];
  const char bB[5];
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);
  if (xVal > 1000) {
    if (r == 255 && g == 0 && b == 0) {
      phase = 0;
    } else if (r == 255 && g == 255 && b == 0) {
      phase = 1;
    } else if (r == 0 && g == 255 && b == 0) {
      phase = 2;
    } else if (r == 0 && g == 255 && b == 255) {
      phase = 3;
    } else if (r == 0 && g == 0 && b == 255) {
      phase = 4;
    } else if (r == 255 && g == 0 && b == 255) {
      phase = 5;
    }
    if (phase == 0) {
      g += 15;
    } else if (phase == 1) {
      r -= 15;
    } else if (phase == 2) {
      b += 15;
    } else if (phase == 3) {
      g -= 15;
    } else if (phase == 4) {
      r += 15;
    } else if (phase == 5) {
      b -= 15;
    }
  }
  sprintf(rB, "R1%d", r);
  String rS = rB;
  sprintf(gB, "G1%d", g);
  String gS = gB;
  sprintf(bB, "B1%d", b);
  String bS = bB;
  radio.write(rB, sizeof(rB));
  radio.write(gB, sizeof(gB));
  radio.write(bB, sizeof(bB));


  const char button[10];
  buttonCurrState = digitalRead(2);
  if (buttonCurrState != buttonPrevState) {
    if (buttonCurrState == HIGH && buttonPrevState == LOW) {
      strcpy(button, "1button1");
      radio.write(button, sizeof(button)); 
    }
  }
  buttonPrevState = buttonCurrState;


  const char gesture[10];
	uint8_t data = 0, error;
	error = paj7620ReadReg(0x43, 1, &data);
	if (!error) {
		switch (data) {
			case GES_RIGHT_FLAG: 
        strcpy(gesture, "1Right");
        Serial.println("1Right");
        radio.write(gesture, sizeof(gesture));    
				break;
			case GES_LEFT_FLAG:
        strcpy(gesture, "1Left");
        Serial.println("1Left");
        radio.write(gesture, sizeof(gesture));  
				break;
			case GES_UP_FLAG:
        strcpy(gesture, "1Up");
        Serial.println("1Up");
        radio.write(gesture, sizeof(gesture));  
				break;
			case GES_DOWN_FLAG:
        strcpy(gesture, "1Down");
        Serial.println("1Down");
        radio.write(gesture, sizeof(gesture));   
				break;
		}
	}
  delay(50);
}