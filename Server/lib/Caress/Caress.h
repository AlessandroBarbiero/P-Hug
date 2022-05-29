#ifndef Caress_h
    #define Caress_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class Caress {
        public:
            Caress(uint8_t pins[], int size);
            void run(unsigned long time);
            void start(unsigned long startingTime, int interval, int shift);
        private:
            uint8_t _pins[MAX_PINS];
            int _step, _interval, _shift, _numOfVib, _numOfSteps;
            bool _caressing;
            unsigned long _lastCaress;
    };
    
#endif