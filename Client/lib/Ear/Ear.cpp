#include <Arduino.h>
#include <Ear.h>
#include <WiFi101.h>

Ear::Ear(){
}

Ear::Ear(int pin, bool isRight){
    _pin = pin;
    _isRight = isRight;
    _servo.attach(pin);
    if(isRight){
        _servo.write(0);
    }
    else{
        _servo.write(180);
    }
}

void Ear::action(){
}

void Ear::connect(){
    if(_isRight){
        _servo.write(60);
    }
    else{
       _servo.write(120); 
    }
}

void Ear::disconnect(){
    if(_isRight){
        _servo.write(0);
    }
    else{
       _servo.write(180); 
    }
}

void Ear::caress(){

}

void Ear::hug(){
    if(_isRight){
        moveDownUpDown(0,60,10);
        delay(500);
    }
    else{
       moveUpDownUp(60,0,10); 
       delay(500);
    }
}

void Ear::shake(){
    
}

void Ear::read(){
    Serial.print(_servo.read());
}

void Ear::moveDownUpDown(int start, int stop, int time){
    for(_angle = start; _angle < stop; _angle += 1 ){
            _servo.write(_angle);                 
            delay(time);
        }
    for(_angle = stop; _angle>=start; _angle-=1){
        _servo.write(_angle);              
        delay(time); 
    }
}

void Ear::moveUpDownUp(int start, int stop, int time){
    for(_angle = start; _angle>=stop; _angle-=1){
        _servo.write(_angle);              
        delay(time); 
    }
    for(_angle = stop; _angle < start; _angle += 1 ){
        _servo.write(_angle);                 
        delay(time);
    }
}