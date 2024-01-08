#include <Adafruit_NeoPixel.h>

#define PIN            6  // Définissez le numéro de broche auquel est connecté le Data-In de la Neopixel Ring
#define NUMPIXELS      24 // Définissez le nombre de pixels dans votre Neopixel Ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialisez la bibliothèque Neopixel
}

void loop() {
  colorWipe(pixels.Color(255, 0, 0), 50); // Faites défiler une couleur rouge à travers les pixels
  delay(500);
  colorWipe(pixels.Color(0, 255, 0), 50); // Faites défiler une couleur verte à travers les pixels
  delay(500);
  colorWipe(pixels.Color(0, 0, 255), 50); // Faites défiler une couleur bleue à travers les pixels
  delay(500);
}

// Fonction pour effectuer un effet de balayage de couleur
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}

