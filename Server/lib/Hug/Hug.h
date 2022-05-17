#ifndef Hug_h
    #define Hug_h
    #include "Arduino.h"
    class Hug  {
        public:
            Hug(unsigned long inflateCooldown, unsigned long startCooldown);
            void run();
            void start();
        private:
            uint8_t _pin;
            bool _hugging;
            unsigned long _lastHug;
            unsigned long _inflateCooldown;
            unsigned long _startCooldown;
    };
    
#endif