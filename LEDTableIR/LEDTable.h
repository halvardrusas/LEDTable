#ifndef LEDTABLE_H
#define LEDTABLE_H

#include <FastLED.h>

class LEDTable {
  private:
    CRGB* leds;
    int len;
    int wid;
    int numLeds;
    int hue = 0;
    int sat = 0;
    int val = 200;
    bool isLightOn = false;
    int lightMode = 0;
    int modeAmbulance = 1;
  public:
    LEDTable(const int tableLength, const int tableWidth, CRGB* ledArray);
    void turnLightOn();
    void turnLightOff();
    void changeAllLeds(int h, int s, int v);
    void changeColor(int newColor);
    void brightnessUp();
    void brightnessDown();
    void keyPressed(int key);
    void updateLight(long millisNow);
    void giveLedsRandomColor();
    void ambulanceMode();
};

#endif
