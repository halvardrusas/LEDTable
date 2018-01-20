#include <FastLED.h>
#include "LEDTable.h"

LEDTable::LEDTable(const int tableLength, const int tableWidth, CRGB* ledArray) {
  leds = ledArray;
  len = tableLength;
  wid = tableWidth;
  numLeds = 2 * (len + wid);
}

void LEDTable::turnLightOn() {
  isLightOn = true;
  for (int j = 0; j < val; j++) {
    for (int i = 0; i < numLeds; i++) {
      leds[i].setHSV(hue, sat, j);
    }
    FastLED.show();
    delay(1);
  }
}

void LEDTable::turnLightOff() {
  isLightOn = false;
  for (int j = 0; j < val; j++) {
    for (int i = 0; i < numLeds; i++) {
      leds[i].setHSV(hue, sat, val - j);
    }
    FastLED.show();
    delay(1);
  }
  FastLED.clear();
  FastLED.show();
}

void LEDTable::changeAllLeds(int h, int s, int v) {
  hue = h;
  sat = s;
  val = v;
  for (int i = 0; i < numLeds; i++) {
    leds[i].setHSV(hue, sat, val);
  }
  FastLED.show();
}

void LEDTable::changeColor(int newColor) {
  changeAllLeds(newColor, sat, val);
}


void LEDTable::brightnessDown() {
  if (val != 10) {
    val = val - 10;
    changeAllLeds(hue, sat, val);
  }
}

void LEDTable::brightnessUp() {
  if (val != 250) {
    val = val + 10;
    changeAllLeds(hue, sat, val);
  }
}

void LEDTable::giveLedsRandomColor() {
  for (int i = 0; i < numLeds; i++) {
    leds[i].setHSV(random(250), sat, val);
  }
  FastLED.show();
}

void LEDTable::ambulanceMode() {
  int hue1;
  int hue2;
  if (modeAmbulance == 1) {
    hue1 = 255;
    hue2 = 150;
    modeAmbulance = 2;
  }
  else if (modeAmbulance == 2) {
    hue1 = 150;
    hue2 = 255;
    modeAmbulance = 1;
  }
  for (int i = 0; i < len; i++) {
    leds[i].setHSV(hue1, sat, val);
    leds[i + wid + len].setHSV(hue1, sat, val);
  }
  for (int j = 0; j < wid; j++) {
    leds[len + j].setHSV(hue2, sat, val);
    leds[wid + 2 * len + j].setHSV(hue2, sat, val);
  }
  FastLED.show();
}

void LEDTable::keyPressed(int key) {
  if (isLightOn || key == 14) {
    switch (key) {
      case 1: //1 white
        lightMode = 1;
        sat = 0;
        changeAllLeds(hue, sat, val);
        break;
      case 2: //2 red
        lightMode = 2;
        hue = 255;
        sat = 250;
        changeAllLeds(hue, sat, val);
        break;
      case 3: //3 blue
        lightMode = 3;
        hue = 150;
        sat = 250;
        changeAllLeds(hue, sat, val);
        break;
      case 4: //4 green
        lightMode = 4;
        hue = 80;
        sat = 250;
        changeAllLeds(hue, sat, val);
        break;
      case 11: //UP
        brightnessUp();
        break;
      case 13: //DOWN
        brightnessDown();
        break;
      case 14: //OK
        if (!isLightOn) {
          turnLightOn();
        }
        else {
          if (lightMode == 15 || lightMode == 16) {
            changeAllLeds(0, 0, val);
            lightMode = 0;
          }
          turnLightOff();
        }
        break;
      case 15: //star
        sat = 255;
        lightMode = 15;
        giveLedsRandomColor();
        break;
      case 16: //hash
        if (lightMode != 16) {
          lightMode = 16;
          sat = 255;
          ambulanceMode();
          Serial.println("ambulance");
        }
        break;
      default:
        break;
    }
  }
}

void LEDTable::updateLight(long millisNow) {
  if (isLightOn) {
    switch (lightMode) {
      case 15: //starynight
        if (millisNow % 100 == 0) {
          giveLedsRandomColor();
        }
        break;
      case 16:
        if (millisNow % 750 == 0) {
          ambulanceMode();
        }
        break;
      default:
        break;
    }
  }
}

