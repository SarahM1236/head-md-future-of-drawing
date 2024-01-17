#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>

#define PIN            3   // Broche pour le NeoPixel Ring
#define NUMPIXELS      24  // Nombre de LEDs sur le NeoPixel Ring
#define BUZZER_PIN     9   // Broche pour le buzzer

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int colorIndex = 0;
uint32_t colors[] = {pixels.Color(216, 87, 42), pixels.Color(121, 32, 32), pixels.Color(238, 179, 56), pixels.Color(228, 138, 53)};
unsigned long lastBuzzerTime = 0;
const int buzzerInterval = 5000; // Intervalle entre les sons du buzzer (5 secondes)

void setup() {
  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  
  pixels.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  float x, y, z;

  // Son de guidage aléatoire
  if (millis() - lastBuzzerTime > buzzerInterval) {
    lastBuzzerTime = millis();
    int beepFrequency = random(500, 1500); // Fréquence aléatoire entre 500 et 1500 Hz
    tone(BUZZER_PIN, beepFrequency, 200);
  }

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Détecter un mouvement de capture rapide
    if (abs(x) > 2.0 || abs(y) > 2.0 || abs(z) > 2.0) {
      // Allumer 6 LEDs avec la couleur actuelle
      for (int i = 0; i < 6; i++) {
        pixels.setPixelColor(i + 6 * colorIndex, colors[colorIndex]);
      }
      pixels.show();
      colorIndex = (colorIndex + 1) % 4;

      // Attendre un moment avant de permettre une autre détection
      delay(1000);
    }
  }
}
