#include <Arduino.h>
#include <Ear.h>
#include <WiFi101.h>

Ear::Ear(int pin){
    _pin = pin;
    _servo.attach(pin);
}

void Ear::action(){
    for(_angle = 0; _angle < 180; _angle += 1 ){
        _servo.write(_angle);                 
        delay(15);
    }

    delay(1000);

    for(_angle = 180; _angle>=1; _angle-=5){
        _servo.write(_angle);              
        delay(5); 
    }

    delay(1000);
    
}

void Ear::connect(){
    _servo.write(180);
}

void Ear::disconnect(){
    _servo.write(0);
}
  