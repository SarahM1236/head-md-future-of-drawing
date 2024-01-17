#include <Arduino_LSM9DS1.h>
#include <Adafruit_NeoPixel.h>

#define PIN            3   // Broche pour le NeoPixel Ring
#define NUMPIXELS      24  // Nombre de LEDs sur le NeoPixel Ring
#define BUZZER_PIN     9   // Broche pour le buzzer

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int colorIndex = 0;
uint32_t colors[] = {pixels.Color(255, 0, 0), pixels.Color(121, 32, 32), pixels.Color(238, 179, 56), pixels.Color(228, 138, 53)}; // Première couleur en rouge
unsigned long lastBuzzerTime = 0;
unsigned long startTime; // Déclaration de startTime
const int totalDuration = 30000; // Durée totale de l'augmentation de la fréquence du bip (30 secondes)
int ledIndex = 0; // Index pour les LEDs allumées
bool captureDone = false; // Ajoutez cette variable au début du programme

void setup() {
  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  
  pixels.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  randomSeed(analogRead(0));
  startTime = millis();
}

void loop() {
  float x, y, z;

  float timeElapsed = (millis() - startTime) / (float)totalDuration;
  timeElapsed = min(timeElapsed, 1.0);

  if (!captureDone && millis() - lastBuzzerTime > (2000 * (1 - timeElapsed))) {
    lastBuzzerTime = millis();
    tone(BUZZER_PIN, 1000, 200);
  }

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    if (abs(x) > 2.0 || abs(y) > 2.0 || abs(z) > 2.0 && !captureDone) {
      noTone(BUZZER_PIN);
      captureDone = true;
      
      // Allumer uniquement 6 LEDs la première fois
      if (ledIndex < 6) {
        for (int i = 0; i < 6 && ledIndex < NUMPIXELS; i++) {
          pixels.setPixelColor(ledIndex++, colors[colorIndex]);
        }
        pixels.show();
      }

      // Réinitialiser startTime pour la prochaine séquence de bip
      if (ledIndex == 6) { // Après avoir allumé les premières 6 LEDs
        startTime = millis();
        captureDone = false; // Prêt pour la prochaine séquence de capture
        colorIndex = (colorIndex + 1) % 4; // Passer à la couleur suivante
      }
    }
  }
}

