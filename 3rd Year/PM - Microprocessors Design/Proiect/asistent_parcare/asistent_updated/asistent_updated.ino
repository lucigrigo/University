#include <QuickStats.h>
QuickStats stats; //initialize an instance of this class

#define RED_PIN 8
#define BLUE_PIN 2
#define YELLOW_PIN 7
#define GREEN_PIN 4

#define RGB_RED 11
#define RGB_GREEN 6
#define RGB_BLUE 5

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 3;

float duration;
float durationarray[20];
int distance;
int buzzerTone = 1000;
int buzzerDelay = 0;

void buzz() {
  if (buzzerDelay != 0) {
    tone(buzzerPin, buzzerTone);
    delay(50);
  }
  noTone(buzzerPin);
  delay(buzzerDelay);
}

void light_off() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
}

void light_red() {
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
}

void light_blue() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
}

void light_green() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);
}

void light_yellow() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(YELLOW_PIN, HIGH);
}

void rgb(int red_val, int green_val, int blue_val) {
  if (red_val > 255 || red_val < 0 || green_val > 255 || green_val < 0 ||
    blue_val > 255 || blue_val < 0) {
      rgb(0, 0, 0);
      return;
    }
    
  analogWrite(RGB_RED, red_val);
  analogWrite(RGB_GREEN, green_val);
  analogWrite(RGB_BLUE, blue_val);
}

void setup() {
  // sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // buzzer pins
  pinMode(buzzerPin, OUTPUT);

  // simple led pins
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // rgb led pins
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 20; i++) {
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

  // sound reset
  buzzerDelay = 0;

  if (distance > 100) {
    light_blue();
    rgb(0, 0, 0);
  } else if (distance > 75) {
    buzzerDelay = 250;
    light_green();
    rgb(0, 0, 0);
  } else if (distance > 50) {
    buzzerDelay = 100;
    light_green();
    rgb(0, 255, 0);
  } else if (distance > 25) {
    buzzerDelay = 100;
    light_yellow();
    rgb(255, 255, 0);
  } else {
    buzzerDelay = 25;
    light_red();
    rgb(255, 0, 0);
  }
  
  buzz();
}
