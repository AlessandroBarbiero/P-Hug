#include <Arduino.h>
#include <Caress.h>
#define COOLDOWN 5000
#define SHAKE_DURATION 5000

Caress::Caress(uint8_t pins[], int size) {
    _numOfVib = size;
    for(int i = 0; i<_numOfVib; i++) {
        _pins[i] = pins[i];
        pinMode(_pins[i], OUTPUT);
    }
    _step = 0;
    _caressing = false;
    _lastCaress = 0;
    _numOfSteps = (_shift*(_numOfVib-1))+2*_interval;
}

void Caress::notify(uint8_t repeat){
    for(int i=0; i<repeat; i++){
        for(int pinIndex=0; pinIndex<_numOfVib; pinIndex++){
                analogWrite(_pins[pinIndex], 255);
        }
        delay(10);
        for(int pinIndex=0; pinIndex<_numOfVib; pinIndex++){
                analogWrite(_pins[pinIndex], 0);
        }
        delay(10);
    }
}

void Caress::start(unsigned long startingTime, int interval, int shift){
    if(startingTime - _lastCaress > COOLDOWN){
        Serial.print("D: Caress started at time: ");
        _lastCaress = startingTime;
        Serial.println(_lastCaress);
        
        _interval=interval;
        _shift = shift;
        _caressing = true;
        _step = 0;

        return;
    }
    Serial.println("D: Caress waiting for cooldown");
}

void Caress::shake(unsigned long startingTime){
    if(startingTime - _lastShake > COOLDOWN){
        Serial.print("D: Shake started at time: ");
        _lastCaress = startingTime;
        for(int pinIndex=0; pinIndex<_numOfVib; pinIndex++){
            analogWrite(_pins[pinIndex], 255);
            _shaking = true;
            _lastShake = startingTime;
        }
    }
}

void Caress::run(unsigned long time){
    if(_shaking && time - _lastShake > SHAKE_DURATION) {
        for(int pinIndex=0; pinIndex<_numOfVib; pinIndex++){
            analogWrite(_pins[pinIndex], 0);
            _shaking = false;
        }

    }
    if (_caressing){
        int relativeStep;
        for(int pinIndex=0; pinIndex<_numOfVib; pinIndex++){
            relativeStep = _step - pinIndex*_shift;
            if(relativeStep > 0){
                if(relativeStep < _interval){
                    analogWrite(_pins[pinIndex], relativeStep);
                }
                else if(relativeStep < 2 * _interval)
                    analogWrite(_pins[pinIndex], _interval*2-relativeStep);
            }
            else
                break;
        }
      
        _step++;
        if(_step == _numOfSteps){
            _caressing = false;
            _step=0;
        }
    }
}
