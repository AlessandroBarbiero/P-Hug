//Hug.cpp
#include <Arduino.h>
#include <Hug.h>

Hug::Hug(int inflateCooldown, int startCooldown) {
    // Variables
    _hugging = false;
    _lastHug = 0;
    _inflateCooldown = inflateCooldown;
    _startCooldown = startCooldown;

    // Pin
    _pin = 0; // LED. TODO: change to output pin for pump
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

void Hug::run() {
    if(_hugging) {
        digitalWrite(_pin, LOW);
        if(millis() - _lastHug > _inflateCooldown) {
            digitalWrite(_pin, HIGH);
            _hugging = false;
        }
    }
}

void Hug::start() {
    if(millis() - _lastHug > _startCooldown) {
        _lastHug = millis();
        _hugging = true;

        Serial.flush();
        Serial.println("Hug started at time: ");
        Serial.flush();
        Serial.println(_lastHug);
    }
}