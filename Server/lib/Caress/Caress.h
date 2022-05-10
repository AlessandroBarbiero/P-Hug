#ifndef Caress_h
    #define Caress_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class Caress {
        public:
            Caress(uint8_t pins[]);
            void run();
            void start(int interval, int shift);
        private:
            uint8_t _pins[MAX_PINS];
            int _step;
            bool _caressing;
            unsigned long _lastCaress;
    };
    
#endif