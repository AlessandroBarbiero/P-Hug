// The heat is made heating at constant rate
#include <Arduino.h>
#include <Heat.h>
// The time of a cycle is constant at 22 seconds -> the heat is regulated changing the duty cycle
#define CYCLE 22000

// The heating rate is made passing the percentage of activity as the duty-cycle
Heat::Heat(float dutyCycle) {
    _heating = false;
    _lastHeat = 0;
    _heatingTime = CYCLE * dutyCycle;
    _cooldown = CYCLE;

}

void Heat::run(unsigned long time) {
    if(_heating && time - _lastHeat > _heatingTime) {
        Serial.println("R: w 0 ");
        _heating = false;
    }
    else if(!_heating && time - _lastHeat > _cooldown)
        start(time);
}

void Heat::start(unsigned long startingTime) {
    if(startingTime - _lastHeat > _cooldown) {
        _lastHeat = startingTime;
        _heating = true;
        Serial.println("R: w 1 ");

        Serial.print("D: Heat started at time: ");
        Serial.println(_lastHeat);
        return;
    }
    Serial.println("D: Heat waiting for cooldown");
}