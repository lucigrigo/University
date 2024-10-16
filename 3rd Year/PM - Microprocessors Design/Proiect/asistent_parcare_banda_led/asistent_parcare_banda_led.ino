#include <FastLED.h>
#include <QuickStats.h>
QuickStats stats; //initialize an instance of this class

// defining the pins
#define LED_PIN     7
#define NUM_LEDS    15
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;

// defining variables
CRGB leds[NUM_LEDS];
float duration;
float durationarray[15];
int distance;
int stopdistance = 10; //parking position from sensor (CENTIMETERS)
int startdistance = 100; //distance from sensor to begin scan as car pulls in(CENTIMETERS)
int increment = ((startdistance - stopdistance) / 15);
int buzzerTone = 1000;
int buzzerDelay = 0;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600); // Starts the serial communication
}

void buzz() {
  if (buzzerDelay != 0) {
    tone(buzzerPin, buzzerTone);
    delay(50);
  }
  noTone(buzzerPin);
  delay(buzzerDelay);
}

void loop() {
  //buzz();
  for (int i = 0; i <= 14; i++) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    durationarray[i] = pulseIn(echoPin, HIGH);
    distance = durationarray[i] * 0.034 / 2;
    Serial.print(distance);
    Serial.print(" ");
  }
  duration = (stats.median(durationarray, 15));
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  buzzerDelay = 0;

  if (distance < stopdistance) {
    buzzerDelay = 25;
    for (int i = 0; i <= 14; i++) {
      leds[i] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
  }
  else if (distance < stopdistance + increment) {
    buzzerDelay = 25;
    for (int i = 1; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 0; i++) {
      leds[i] = CRGB ( 255, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 2) {
    buzzerDelay = 25;
    for (int i = 2; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 1; i++) {
      leds[i] = CRGB ( 255, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 3) {
    buzzerDelay = 25;
    for (int i = 3; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 2; i++) {
      leds[i] = CRGB ( 255, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 4) {
    buzzerDelay = 25;
    for (int i = 4; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 3; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 5) {
    buzzerDelay = 200;
    for (int i = 5; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 4; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 6) {
    buzzerDelay = 200;
    for (int i = 6; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 5; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 7) {
    buzzerDelay = 200;
    for (int i = 7; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 6; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 8) {
    buzzerDelay = 200;
    for (int i = 8; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 7; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 9) {
    buzzerDelay = 200;
    for (int i = 9; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 8; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 10) {
    buzzerDelay = 500;
    for (int i = 10; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 9; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 11) {
    buzzerDelay = 500;
    for (int i = 11; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 10; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 12) {
    buzzerDelay = 500;
    for (int i = 12; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 11; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 13) {
    buzzerDelay = 500;
    for (int i = 13; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 12; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance < stopdistance + increment * 14) {
    buzzerDelay = 500;
    for (int i = 14; i <= 14; i++) {
      leds[i] = CRGB ( 0, 0, 0);
    }
    for (int i = 0; i <= 13; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
  else if (distance >= stopdistance + increment * 14) {
    for (int i = 0; i <= 14; i++) {
      leds[i] = CRGB ( 0, 255, 0);
    }
    FastLED.show();
    delay(50);
  }
}
