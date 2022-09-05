/*
   Code file for use with an Arduino Uno and NeoPixel ring.
   Light up each NeoPixel, one by one, in a clockwise rotation.
   Once the end of the ring is reached, loop over.
*/

#include <Adafruit_NeoPixel.h> // Official NeoPixel library

// Direction of rotation
// 0 = clockwise
// 1 = anticlockwise
const int rotation = 0;

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
  // Start the ring
  ring.begin();

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
    // Store current milliseconds value
    previous_ms = current_ms;

    // Proceed to the next NeoPixel
    next_pixel();
  }
}

void next_pixel()
{
  // Clear the display
  ring.clear();
  ring.show();

  if (rotation == 0)  // If rotation is set to clockwise
  {
    // Update current pixel value and add to iterator
    current_pixel = ring_iterator++;

    // If iterator is at the end, reset it
    ring_iterator = (ring_iterator == pixel_amount) ? 0 : ring_iterator;

    // Set the current pixel to green
    ring.setPixelColor(current_pixel, ring.Color(0, pixel_brightness, 0));
  }
  else // If rotation is set to anticlockwise
  {
    // Update current pixel value and subtract from iterator
    current_pixel = ring_iterator--;

    // If iterator is at the start, reset it
    ring_iterator = (ring_iterator < 0) ? pixel_amount - 1 : ring_iterator;

    // Set the current pixel to blue
    ring.setPixelColor(current_pixel, ring.Color(0, 0, pixel_brightness));
  }

  // Update the display
  ring.show();
}
