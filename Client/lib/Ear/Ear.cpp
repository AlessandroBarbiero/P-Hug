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
    
    if(_isRight){
        for(_angle = 0; _angle < 60; _angle += 1 ){
            _servo.write(_angle);                 
            delay(15);
        }
        delay(1000);
        for(_angle = 60; _angle>=0; _angle-=1){
            _servo.write(_angle);              
            delay(15); 
        }
        delay(1000);
    }
    else{
        for(_angle = 180; _angle > 100; _angle-= 1 ){
            _servo.write(_angle);                 
            delay(15);
        }
        delay(1000);
        for(_angle = 100; _angle <= 180; _angle+=1){
            _servo.write(_angle);              
            delay(15); 
        }
        delay(1000);
    }
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

}

void Ear::shake(){
    
}

void Ear::read(){
    Serial.print(_servo.read());
}
  