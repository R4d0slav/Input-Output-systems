// C++ code
//

#include <Wire.h>

#define buttons A0
#define speaker 2
#define startButton 3
#define startLed 4

int frequency[] = {261, 278, 294, 312, 330, 349, 371, 392};
int lowerLimit[] = {0, 51, 151, 301, 451, 651, 801, 901};
int upperLimit[] = {50, 150, 300, 450, 650, 800, 900, 960};
int leds[8] = {5, 6, 7, 8, 9, 10, 11, 12};

int sensorValue = 0;
bool answering = false;
int challenge[3];
int answers[3];
int start = LOW;
int answersLen = 0;

void setup()
{
  Wire.begin();
  pinMode(speaker, OUTPUT);
  pinMode(startLed, OUTPUT);
  pinMode(buttons, INPUT);
  pinMode(startButton, INPUT);
  for (int i=0; i<8; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  start = digitalRead(startButton);
  if (start == HIGH) {
  	blink(startLed, 200);
    reset();
    startChallenge();
  }
  readMelody();
  delay(10);
}

void readMelody()
{
  sensorValue = analogRead(buttons);
  for (int i=0; i<8; i++) {
    if (sensorValue >= lowerLimit[i] && sensorValue < upperLimit[i]) {
      tone(speaker, frequency[i], 300);
      blink(leds[i], 200);
      delay(200);
      if (answering) {
      	answers[answersLen] = frequency[i];
        answersLen += 1;
        if (answersLen == 3) {
          checkAnswers();
        }
      }
    }
  }
  
}

void blink(int n, int t)
{
  digitalWrite(n, HIGH);
  delay(t);
  digitalWrite(n, LOW);
  delay(t);
}

void reset()
{
  answersLen = 0;
  Wire.beginTransmission(4);
  Wire.write(2);
  Wire.endTransmission();
}

void startChallenge()
{
  createChallenge();
  answering = true;
}

void createChallenge()
{
  for (int i=0; i<3; i++) {
  	int n = random(8);
    challenge[i] = frequency[n];
    tone(speaker, challenge[i], 300);
    blink(leds[n], 200);
    delay(200);
  }
  blink(startLed, 200);
}

void checkAnswers()
{
  int correct = 1;
  for (int i=0; i<3; i++) {
    if (answers[i] != challenge[i]) {
      correct = 0;
      break;
    }
  }
  Wire.beginTransmission(4);
  Wire.write(correct);
  Wire.endTransmission();
}