#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>


#define PIN            3  // Définissez le numéro de broche auquel est connecté le Data-In de la Neopixel Ring
#define NUMPIXELS      24 // Définissez le nombre de pixels dans votre Neopixel Ring

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int buzzerPin = 9;  // Broche de sortie pour le buzzer piézoélectrique

void setup() {
  pixels.begin(); // Initialisez la bibliothèque Neopixel
   pinMode(buzzerPin, OUTPUT);
}

void loop() {
  colorWipe(pixels.Color(255, 0, 0), 50); // Faites défiler une couleur rouge à travers les pixels
  delay(500);
  colorWipe(pixels.Color(0, 255, 0), 50); // Faites défiler une couleur verte à travers les pixels
  delay(500);
  colorWipe(pixels.Color(0, 0, 255), 50); // Faites défiler une couleur bleue à travers les pixels
  delay(500);

// Produire un son pendant 1 seconde à une fréquence de 500 Hz
  tone(buzzerPin, 1000);  // Fréquence de 1000 Hz
  delay(1000);

  // Arrêter le son pendant 1 seconde
  //noTone(buzzerPin);
  //delay(1000);
}

// Fonction pour effectuer un effet de balayage de couleur
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}

