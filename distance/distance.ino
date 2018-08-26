#include <SR04.h>

// Ultrasonic Sensor's pins
#define TRIG 11
#define ECHO 12

#define DELAYTIME 500// fading time between colors

// input of sensor
SR04 sr04 = SR04(ECHO, TRIG);

int latchPin = 6;
int clockPin = 5;
int dataPin = 7;

byte leds = 0;

int lastLed = 0;

// variables to calcultate the thresholds
int distMax = 150;
int nbrLed = 8;
int pas = distMax/nbrLed;

void setup() {
  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void shutAll() {
  leds = 0;
  updateShiftRegister();
}

void ledOn(int _led) {
  if(lastLed != _led){
    lastLed = _led;
    shutAll();  
  } else {
    bitSet(leds, _led);
    updateShiftRegister();
  }
}

// main loop
void loop() {
  long distance = sr04.Distance();
  for(int i = 0 ; i< 8; i++) { 
    if(distance <= pas * i && distance > (pas * i) -pas) {
      ledOn(i);
    } 
  }
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
  }

