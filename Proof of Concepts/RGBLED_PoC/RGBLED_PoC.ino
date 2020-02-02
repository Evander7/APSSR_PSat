#include <FastLED.h>
#define LED_PIN     11
#define NUM_LEDS    1


CRGB leds[NUM_LEDS];

void setup() {
//  // put your setup code here, to run once:
//  int led_pin = 11;
//  int num_leds = 1;
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();

  delay(250);

  leds[0] = CRGB(0, 255, 0);
  FastLED.show();

  delay(250);

  leds[0] = CRGB(0, 0, 255);
  FastLED.show();  

  delay(250);

}
