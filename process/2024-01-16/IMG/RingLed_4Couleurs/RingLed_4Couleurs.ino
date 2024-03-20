#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>

#define PIN            3   // Broche pour le NeoPixel Ring
#define NUMPIXELS      24  // Nombre de LEDs sur le NeoPixel Ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// État pour savoir quelle séquence de LEDs doit être allumée
enum LedState {
  RED_LEDS,
  ORANGE_LEDS,
  GREEN_LEDS,
  VIOLET_LEDS,
  DONE,
  RESET
};

LedState currentState = RED_LEDS;

void setup() {
  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  pixels.begin();  // Initialiser le NeoPixel Ring
}

// ... Existing code ...

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    if (z > 0.8) {
      switch (currentState) {
        case RED_LEDS:
          // ... Red LEDs logic ...
          break;
        case ORANGE_LEDS:
          // ... Orange LEDs logic ...
          break;
        case GREEN_LEDS:
          // ... Green LEDs logic ...
          break;
        case VIOLET_LEDS:
          // ... Violet LEDs logic ...
          break;
        case DONE:
          // ... Turn off all LEDs ...
          currentState = RESET;
          break;
        case RESET:
          delay(5000); // Wait for 5 seconds before restarting the sequence
          currentState = RED_LEDS;
          break;
      }
    }
  }
}

// ... Remaining code ...


void lightUpLeds(int start, int end, uint32_t color) {
  for (int i = start; i < end; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
