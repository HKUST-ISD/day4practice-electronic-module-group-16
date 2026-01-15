/*Replace ? in the code*/
#include <Arduino.h>
    1#include "NewPing.h"

// Hook up HC-SR04 with Trig and Echo to ESP32 Pins
#define TRIG_PIN 4                  
#define ECHO_PIN 5  
// ESP 32 pin connected to ESP32
#define LED 1

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// variable value to store the duty cycle value in 8 bit (0-255) of PWM
int value;

void setup() {
  
    Serial.begin(115200); // Initialize the Serial Monitor and set a baud rate
}

void loop() {
    
    // Get the distance from the Ultrasonic Sensor
    float distance = sonar.ping_cm();

    // Print the distance to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500); // Delay 0.5s to avoid reading the distance too fast 
    
    // Distance > 10cm, LED is OFF
    // Distance< 10 cm, the closer the target, the brighter the LED 
    // set the duty cycle value in 8-bit (0-255) to use analogWrite() to generate PWM signal to set the LED brightness
    if (distance > 10 || distance == 0) // No object or too far → LED off
    {
    value=0;
    } else {  // Closer than 10 cm → brighter when closer
    // Map distance from 10cm → 0cm to PWM 0 → 255
    // Closer = higher brightness
    value = map(distance, 0, 10, 255, 0);
    value = constrain(value, 0, 255);  // Make sure we stay in valid range
  }
    // print the duty cycle value 
    Serial.print("duty cycle value: ");
    Serial.println(value); 
    // generate PWM signal to set the LED brightness
    analogWrite(LED,value);

}
