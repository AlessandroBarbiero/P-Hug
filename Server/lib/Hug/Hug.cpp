//Hug.cpp
#include <Arduino.h>
#include <Hug.h>
#define HCOOLDOWN 5000

Hug::Hug() {
    // Variables
    _hugging = false;
    _lastHug = 0;

    // Pin
    _pin = 0; // LED. TODO: change to output pin for pump
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

void Hug::run() {
    if(_hugging) {
        digitalWrite(_pin, LOW);
        if(millis() - _lastHug > HCOOLDOWN) {
            digitalWrite(_pin, HIGH);
            _hugging = false;
        }
    }
}

void Hug::start() {
    if(millis() - _lastHug > HCOOLDOWN) {
        _lastHug = millis();
        _hugging = true;

        Serial.println("Hug started at time: ");
        Serial.println(_lastHug);
    }
}