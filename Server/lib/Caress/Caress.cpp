#include <Arduino.h>
#include <Caress.h>
#define COOLDOWN 10000

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

void Caress::start(unsigned long startingTime, int interval, int shift){
    if(startingTime - _lastCaress > COOLDOWN){
        Serial.print("D: Caress started at time: ");
        _lastCaress = startingTime;
        Serial.println(_lastCaress);
        
        _interval=interval;
        _shift = shift;
        _caressing = true;

        return;
    }
    Serial.println("D: Caress waiting for cooldown");
}

void Caress::run(unsigned long time){
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
