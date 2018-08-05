#include <SR04.h>

//www.elegoo.com
//2016.12.8

// Led Pins
// RED
#define RED0 2
#define RED1 3
#define RED2 4
#define RED3 5
#define RED4 6

// GREEN
#define GREEN0 7
#define GREEN1 8
#define GREEN2 9
#define GREEN3 10
#define GREEN4 13

// Ultrasonic Sensor's pins
#define TRIG 11
#define ECHO 12

#define DELAYTIME 500// fading time between colors

// Arrays of pins
int redPins[5] = {RED0, RED1, RED2, RED3, RED4};
int greenPins[5] = {GREEN0, GREEN1, GREEN2, GREEN3, GREEN4};
int allLedPins[10] = {RED0, RED1, RED2, RED3, RED4, GREEN0, GREEN1, GREEN2, GREEN3, GREEN4};

// input of sensor
SR04 sr04 = SR04(ECHO, TRIG);

// variables to calcultate the thresholds
int distMax = 150;
int nbrLed = 10;
int pas = distMax/nbrLed;

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 10; i++) {
    pinMode(allLedPins[i], OUTPUT); 
  }
}

void shutAll() {
  for(int i = 0 ; i < 10; i++) {
     digitalWrite(allLedPins[i], LOW);  
  }  
}

void ledOn(int _led) {
  digitalWrite(allLedPins[_led], HIGH);  
}

void ledOff(int _led) {
  digitalWrite(allLedPins[_led], LOW);  
}

// main loop
void loop() {
   long distance = sr04.Distance();
   
   for(int i = 0; i < 10; i++) {
      if(distance <= pas * i && distance > (pas * i) - pas) {
        ledOn(i);
        delay(DELAYTIME);
        ledOff(i);
        delay(DELAYTIME);
      }   
   }
   
}

