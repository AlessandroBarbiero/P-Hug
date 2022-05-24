//Heat.cpp
#include <Arduino.h>
#include <Heat.h>

Heat::Heat(unsigned long heatingTime, unsigned long cooldown) {
    // Variables
    _heating = false;
    _lastHeat = 0;
    _heatingTime = heatingTime;
    _cooldown = cooldown;

    _light = 0;
    pinMode(_light, OUTPUT);
    digitalWrite(_light, HIGH);

/*     pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_pwm, OUTPUT);
    pinMode(_standby, OUTPUT); */

/*     digitalWrite(_standby, LOW); */


}

void Heat::run() {
    if(_heating && millis() - _lastHeat > _heatingTime) {
        digitalWrite(_light, HIGH);
        Serial.println("R: w 0 ");
        
/*        digitalWrite(_standby, LOW); */
        _heating = false;
    }
}

void Heat::start() {
    if(millis() - _lastHeat > _cooldown) {
        _lastHeat = millis();
        _heating = true;
        digitalWrite(_light, LOW);
        Serial.println("R: w 1 ");
/*         digitalWrite(_standby, HIGH);
        digitalWrite(_in1,HIGH);
        digitalWrite(_in2,LOW);
        analogWrite(_pwm,255); */

        Serial.print("D: Heat started at time: ");
        Serial.println(_lastHeat);
        return;
    }
    Serial.println("D: Heat waiting for cooldown");
}