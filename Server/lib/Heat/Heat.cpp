//Heat.cpp
#include <Arduino.h>
#include <Heat.h>

Heat::Heat(unsigned long heatingTime, unsigned long cooldown) {
    _heating = false;
    _lastHeat = 0;
    _heatingTime = heatingTime;
    _cooldown = cooldown;

}

void Heat::run() {
    if(_heating && millis() - _lastHeat > _heatingTime) {
        Serial.println("R: w 0 ");
        _heating = false;
    }
}

void Heat::start() {
    if(millis() - _lastHeat > _cooldown) {
        _lastHeat = millis();
        _heating = true;
        Serial.println("R: w 1 ");

        Serial.print("D: Heat started at time: ");
        Serial.println(_lastHeat);
        return;
    }
    Serial.println("D: Heat waiting for cooldown");
}