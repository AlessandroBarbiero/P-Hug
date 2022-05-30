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
        _angle = _maxAngle;
        _servo.write(_angle);
    }
    else{
        _angle = _maxAngle;
       _servo.write(_angle); 
    }
}

void Ear::disconnect(){
    if(_isRight){
        _servo.write(0);
    }
    else{
       _servo.write(0); 
    }
}

void Ear::caress(){
    _servo.write(50);

}

void Ear::hug(){
    if(!_isHugging){
        _isHugging = true;
        _isGoingUp = false;
        _hugActivationTime = millis();
    }
    idle();
}

void Ear::shake(){
    
}

void Ear::read(){
    Serial.print(_servo.read());
}

void Ear::idle(){
    if(_isHugging && millis() < _hugActivationTime + _hugDuration){
        if(_angle > 0 && !_isGoingUp){
            Serial.print("HERE");
            moveDown(5);
        }
        else if ( _angle <= 0 && !_isGoingUp){
            _isGoingUp = true;
            Serial.print("ssssssssssssssRE");
        }
        else if ( _angle < _maxAngle && _isGoingUp){
            moveUp(5);
            Serial.print("HsssasdqdfwdERE");
        }
        else if (_angle >= _maxAngle){
            _isHugging = false;
            Serial.print("adsdfasdddasdsdasdasdasdadas");
        }
    }
    else {
        _isHugging = false;
    }
}

void Ear::moveUp(int delta){
    _angle = _angle + delta;
    _servo.write(_angle);
}

void Ear::moveDown(int delta){
    _angle = _angle - delta;
    _servo.write(_angle);
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