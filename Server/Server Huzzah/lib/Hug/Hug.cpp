//Hug.cpp
#include <Arduino.h>
#include <Hug.h>

Hug::Hug(unsigned long inflateCooldown, unsigned long startCooldown) {
    _hugging = false;
    _lastHug = 0;
    _inflateCooldown = inflateCooldown;
    _startCooldown = startCooldown;

    _light = 0;
    pinMode(_light, OUTPUT);
    digitalWrite(_light, HIGH);

}

void Hug::run(unsigned long time) {
    if(_hugging && time - _lastHug > _inflateCooldown) {
        digitalWrite(_light, HIGH);
        Serial.println("R: h 0 ");
        
//        digitalWrite(_standby, LOW);
        _hugging = false;
    }
}

void Hug::start(unsigned long startingTime) {
    if(startingTime - _lastHug > _startCooldown) {
        _lastHug = startingTime;
        _hugging = true;
        digitalWrite(_light, LOW);
        Serial.println("R: h 1 ");

        Serial.print("D: Hug started at time: ");
        Serial.println(_lastHug);
        return;
    }
    Serial.println("D: Hug waiting for cooldown");
}