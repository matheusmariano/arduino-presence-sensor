#include <Arduino.h>

const unsigned long interval = 15000;
const uint8_t lightPin = 8;
const uint8_t sensorPin = 2;
const uint8_t interruptPin = 0;

volatile unsigned long lastMovement = 0;

void registerMovement() {
    lastMovement = millis();
}

void turnLightOn() {
    digitalWrite(lightPin, HIGH);
}

void turnLightOff() {
    digitalWrite(lightPin, LOW);
}

bool hasMovementDuringInterval() {
    unsigned long lastCheck = millis() < interval ? 0 : millis() - interval;
    
    return lastMovement > lastCheck;
}

void setup() {
    pinMode(sensorPin, INPUT);
    pinMode(lightPin, OUTPUT);
    
    attachInterrupt(interruptPin, registerMovement, RISING);
}

void loop() {
    if (hasMovementDuringInterval()) {
        turnLightOn();
    } else {
        turnLightOff();
    }
}
