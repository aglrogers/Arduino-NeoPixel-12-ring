/*
 * Code file for use with an Arduino Uno and NeoPixel ring.
 * Light up each NeoPixel, one by one, in a clockwise rotation.
 * Once the end of the ring is reached, loop over.
 */

#include <Adafruit_NeoPixel.h> // Official NeoPixel library

// The board pin for the NeoPixel ring
const int neopixel_pin = 2;

// The number of pixels on the ring
const int pixel_amount = 12;

// The maximum brightness (0 - 255)
// I found that 20 is suitably comfortable
const int pixel_brightness = 20;

// Delay between changes in milliseconds
const int delay_interval = 200;

// Iterator variables
int current_pixel = 0;  // Current value
int ring_iterator = 0;  // Next value

// Variables for pause with using Delay()
unsigned long current_ms = 0;
unsigned long previous_ms = 0;

// Initialising the NeoPixel ring with the number of pixels and the board pin
Adafruit_NeoPixel ring(pixel_amount, neopixel_pin, NEO_GRB + NEO_KHZ800);

void setup()
{
  ring.begin();   // Start the ring

  // Clear the display
  ring.clear();
  ring.show();

  // Wait for a few moments before proceeding
  delay(200);
}

void loop()
{
  // Update millisecond counter
  current_ms = millis();

  // If a delay interval has elapsed
  if (current_ms - previous_ms >= delay_interval)
  {
    // Update the current pixel value and increase the iterator
    current_pixel = ring_iterator++;

    // Store current milliseconds value
    previous_ms = current_ms;

    // Clear the display
    ring.clear();
    ring.show();

    // Set the current pixel to green
    ring.setPixelColor(current_pixel, ring.Color(0, pixel_brightness, 0));

    // Update the display
    ring.show();

    // If the iterator is at the max amount of pixels, reset it
    ring_iterator = (ring_iterator == pixel_amount) ? 0 : ring_iterator;
  }
}
