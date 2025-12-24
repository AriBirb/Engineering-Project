#include "CytronMotorFunctions.h"

CytronMD linearActuatorTilt(PWM_DIR, 11, 2);
CytronMD linearActuatorLift(PWM_DIR, 12, 3);
CytronMD motor1(PWM_DIR, 9, 4);
CytronMD motor2(PWM_DIR, 10, 5);

CytronMD* devices[4] = {&linearActuatorTilt, &linearActuatorLift, &motor1, &motor2};


// RC Receiver channel pins
int ch1Pin = A9;
int ch2Pin = A11;
int ch3Pin = A10;
int ch4Pin = A12;


int channels[4] = {ch1Pin, ch2Pin, ch3Pin, ch4Pin}; 


// You can now access the original objects through the pointers in the 'devices' array:
// devices[0]->someMethod();

// Variables to store pulse durations
int pulseDuration;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Set RC receiver channel pins as inputs
  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);
  pinMode(ch4Pin, INPUT);

  Serial.begin(9600); // Initialize serial communication
  
  // Wait for serial connection to be established
  delay(1000);
  Serial.println("FlySky Receiver Test");
  Serial.println("--------------------");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    // Read pulse from channel 4 with increased timeout value
    pulseDuration = pulseIn(channels[i], HIGH, 25000); // Increase timeout to 25ms
  
    // Map RC values to motor speed range if needed
    if (pulseDuration > 0) {
      // RC signal typically ranges from ~1000-2000μs
      // Map to motor speed range (-255 to 255)
      int motorSpeed = map(pulseDuration, 1000, 2000, -255, 255);
    
    // Add deadband in the middle to ensure actuator stops at neutral
    if (motorSpeed > -30 && motorSpeed < 30) {
      motorSpeed = 0;
    }
    
    // Apply speed to actuator
    devices[i]->setSpeed(motorSpeed);
    
    Serial.print("Motor Speed: ");
    Serial.println(motorSpeed);
    } else {
    // No signal detected, stop motor
      devices[i]->setSpeed(0);
    //Serial.println("No signal detected - motor stopped");
    }
  
  digitalWrite(LED_BUILTIN, pulseDuration > 0 ? HIGH : LOW); // Visual indicator of signal
  
  delay(10); // Wait between readings
  }
}