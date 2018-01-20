#include <FastLED.h>
#include "LEDTable.h"
#include <IRremote.h>
#include "irremoteheader.h"

#define tableLength 49
#define tableWidth 24
#define DATA_PIN 9

int const RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int NUM_LEDS = 2 * (tableLength + tableWidth);

CRGB leds[NUM_LEDS];
LEDTable* ledTableP;

long timeNow = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();

  ledTableP = new LEDTable(tableLength, tableWidth, leds);

  FastLED.show();

  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); //start receiver
  Serial.println("Enabled IRin");
}

void loop() {
  timeNow = millis();
  int key = keyesRemoteReceived(irrecv, results);
  if (key >= 0) {
    Serial.println(key);
    ledTableP->keyPressed(key);
  }

  ledTableP -> updateLight(timeNow);
}
