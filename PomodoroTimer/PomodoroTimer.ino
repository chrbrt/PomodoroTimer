#include <Servo.h>
#include <Event.h>
#include <Timer.h>


/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 12;     // the number of the pushbutton pin
const int vibPin =  13;      // the number of the LED pin
const int servoPin = 11;

Servo leverServo;  // create servo object to control a servo
int pos = 0;  

Timer workTimer;
Timer relaxTimer;


// variables will change:

int iterations = 0;
int buttonState = 0;         // variable for reading the pushbutton status
boolean startSession = false;

void setup() {
  leverServo.attach(9);
  // initialize the LED pin as an output:
  pinMode(vibPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize the servo pin
  
}

void loop() {
  workTimer.update();
  relaxTimer.update();
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    startWorkTimer();
  }
}

void startWorkTimer() {
  giveSignal(500);
  int tickEvent = workTimer.after(2000, endWorkTimer);
}

void startRelaxTimer() {
  giveSignal(50);
  int tickEvent = relaxTimer.after(1000, endRelaxTimer);
}

void endWorkTimer() {
  iterations++;
  if(iterations < 3) {
    startRelaxTimer();
  } else {
    leverServo.write(45);
  }
}

void endRelaxTimer() {
  startWorkTimer();
}

void giveSignal(int t){
  digitalWrite(vibPin, HIGH);
  delay(t);
  digitalWrite(vibPin, LOW);
}



