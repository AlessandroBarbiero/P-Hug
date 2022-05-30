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
    _caressActivationTime = millis();
    _isCaressing = true;
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
    if(_isHugging){
        if(millis() < _hugActivationTime + _hugDuration){
            if(_angle > 0 && !_isGoingUp){
                moveDown(5);
            }
            else if ( _angle <= 0 && !_isGoingUp){
                _isGoingUp = true;
            }
            else if ( _angle < _maxAngle && _isGoingUp){
                moveUp(5);
            }
            else if (_angle >= _maxAngle){
                _isHugging = false;
            }
        }
        else {
            _isHugging = false;
        }
    }
    else if (_isCaressing){
        if (_angle > 0) moveDown(1);
        else{
            if(millis() > _caressActivationTime + _caressDuration){
                _angle = _maxAngle;
                _servo.write(_maxAngle);
                _isCaressing = false;
            }
        } 
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