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
  DONE
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

void loop() {
  float x, y, z;

  // Lire les données d'accélération
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Détecter un mouvement d'abaissement
    if (z > 2.0) {  // Modifier cette valeur selon la sensibilité souhaitée
      switch (currentState) {
        case RED_LEDS:
          lightUpLeds(0, 6, pixels.Color(255, 0, 0));  // Allumer les 6 premières LEDs en rouge
          currentState = ORANGE_LEDS;
          break;
        case ORANGE_LEDS:
          lightUpLeds(6, 12, pixels.Color(255, 165, 0));  // Allumer les 6 LEDs suivantes en orange
          currentState = GREEN_LEDS;
          break;
        case GREEN_LEDS:
          lightUpLeds(12, 18, pixels.Color(0, 255, 0));  // Allumer les 6 LEDs suivantes en vert
          currentState = DONE;
          break;
        case DONE:
          // État final, rien de plus à faire
          break;
      }

      // Petite pause pour éviter de détecter le même mouvement plusieurs fois
      delay(1000);
    }
  }
}

void lightUpLeds(int start, int end, uint32_t color) {
  for (int i = start; i < end; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}


