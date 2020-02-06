#include <FastLED.h>
#define LED_PIN     6
#define NUM_LEDS    1


CRGB leds[NUM_LEDS];

void RGB_setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void RGB_on(int r, int g, int b) {
  leds[0] = CRGB(r, g, b);
  FastLED.show();
}
