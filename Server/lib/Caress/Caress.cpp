//MyBlink.cpp
#include <Arduino.h>
#include <Caress.h>
#define COOLDOWN 10000

Caress::Caress(uint8_t pins[], int size) {
    *_pins = *pins;
    _numOfVib = size;
    for(int i = 0; i<_numOfVib; i++)
        pinMode(_pins[i], OUTPUT);
    
<<<<<<< HEAD
    _step = 0;
    _caressing = false;
    _lastCaress = 0;
}

void Caress::start(int interval, int shift){
    if(millis()- _lastCaress > COOLDOWN){
        Serial.println("Caress started at time: ");
        _lastCaress = millis();
        Serial.println(_lastCaress);
        
        _interval=interval;
        _shift = shift;

        _caressing = true;
        }
}

void Caress::run(){
    if (_caressing){
        int relativeStep;
        for(int pinIndex=0; pinIndex<_numOfVib; pinIndex++){
            Serial.println(pinIndex);
            relativeStep = _step - pinIndex*_shift;
            if(relativeStep > 0){
                if(relativeStep < _interval){
                    analogWrite(_pins[pinIndex], relativeStep);
                    Serial.println(_pins[pinIndex]);
                }
                else if(relativeStep < 2 * _interval)
                    analogWrite(_pins[pinIndex], _interval*2-relativeStep);
            }
            else
                break;
        }
      
        _step++;
        if(_step == (_shift*(_numOfVib-1))+2*_interval){
            _caressing = false;
            _step=0;
        }
    }
}
=======
}
>>>>>>> a7a4f0f9c59dacab14cf2381daf54546aee5055a
