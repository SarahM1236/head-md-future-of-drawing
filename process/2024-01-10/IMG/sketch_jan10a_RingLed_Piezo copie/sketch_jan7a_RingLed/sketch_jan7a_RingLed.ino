#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>

#define PIN            3   // Définissez le numéro de broche auquel est connecté le Data-In de la Neopixel Ring
#define NUMPIXELS      24  // Définissez le nombre de pixels dans votre Neopixel Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int buzzerPin = 9;  // Broche de sortie pour le buzzer piézoélectrique

float x, y, z;
int degreesX = 0;
int degreesY = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  pixels.begin();  // Initialisez la bibliothèque Neopixel
  //pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  }

  // Réglez les seuils d'inclinaison selon vos besoins
  float tiltThreshold = 0.1;

  // Effet lumineux lorsque l'inclinaison est vers le haut
  if (x > tiltThreshold) {
    colorWipe(pixels.Color(255, 0, 0), 50);  // Rouge
  }

  // Effet lumineux lorsque l'inclinaison est vers le bas
  if (x < -tiltThreshold) {
    colorWipe(pixels.Color(0, 0, 255), 50);  // Bleu
  }

  // Effet lumineux lorsque l'inclinaison est vers la gauche
  if (y > tiltThreshold) {
    colorWipe(pixels.Color(0, 255, 0), 50);  // Vert
  }

  // Effet lumineux lorsque l'inclinaison est vers la droite
  if (y < -tiltThreshold) {
    colorWipe(pixels.Color(255, 255, 0), 50);  // Jaune
  }

  // Produire un son pendant 1 seconde à une fréquence de 500 Hz
tone(buzzerPin, 500);  // Fréquence de 500 Hz
delay(1000);

  // Arrêter le son pendant 1 seconde
  noTone(buzzerPin);
  delay(1000);
}

// Fonction pour effectuer un effet de balayage de couleur
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(wait);
  }
}
