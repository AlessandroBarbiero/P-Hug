#include <Arduino.h>
#include <Ear.h>
#include <WiFi101.h>

#define MAX_ANGLE_RIGHT 50
#define MIN_ANGLE_RIGHT 0
#define MAX_ANGLE_LEFT 140
#define MIN_ANGLE_LEFT 90

Ear::Ear(){
}

Ear::Ear(int pin, bool isRight){
    _pin = pin;
    _isRight = isRight;
    _servo.attach(pin);
    if(isRight){
        _servo.write(MIN_ANGLE_RIGHT);
    }
    else{
        _servo.write(MAX_ANGLE_LEFT);
    }
}


void Ear::connect(){
    if(_isRight){
        _servo.write(MAX_ANGLE_RIGHT);
    }
    else{
       _servo.write(MIN_ANGLE_LEFT); 
    }
}

void Ear::disconnect(){
    if(_isRight){
        _servo.write(MIN_ANGLE_RIGHT);
    }
    else{
       _servo.write(MAX_ANGLE_LEFT); 
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
    _angle = _servo.read();
    if(_isRight){
        if(_isHugging){
            if(millis() < _hugActivationTime + _hugDuration){
                if(_angle > 0 && !_isGoingUp){
                    moveDown(5);
                }
                else if ( _angle <= 0 && !_isGoingUp){
                    _isGoingUp = true;
                }
                else if ( _angle < MAX_ANGLE_RIGHT && _isGoingUp){
                    moveUp(5);
                }
                else if (_angle >= MAX_ANGLE_RIGHT){
                    _isHugging = false;
                }
            }
            else {
                _isHugging = false;
            }
        }
        else if (_isCaressing){
            if (_angle > MIN_ANGLE_RIGHT){
                moveDown(1);
            }
            else{
                if(millis() > _caressActivationTime + _caressDuration){
                    _angle = MAX_ANGLE_RIGHT;
                    _servo.write(_angle);
                    _isCaressing = false;
                }
            } 
        }
    }
    else{
        if(_isHugging){
        if(millis() < _hugActivationTime + _hugDuration){
            if(_angle > MIN_ANGLE_LEFT && !_isGoingUp){
                moveDown(5);
            }
            else if ( _angle <= MIN_ANGLE_LEFT && !_isGoingUp){
                _isGoingUp = true;
            }
            else if ( _angle < MAX_ANGLE_LEFT && _isGoingUp){
                moveUp(5);
            }
            else if (_angle >= MAX_ANGLE_LEFT){
                _isHugging = false;
            }
        }
        else {
            _isHugging = false;
        }
    }
    else if (_isCaressing){
        if (_angle < MAX_ANGLE_LEFT) moveUp(1);
        else{
            if(millis() > _caressActivationTime + _caressDuration){
                _angle = MIN_ANGLE_LEFT;
                _servo.write(_angle);
                _isCaressing = false;
            }
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