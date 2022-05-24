#ifndef Hug_h
    #define Hug_h
    #include "Arduino.h"
    class Hug  {
        public:
            Hug(unsigned long inflateCooldown, unsigned long startCooldown);
            void run();
            void start();
        private:
            uint8_t _light;
            // uint8_t _in1 = 12, _in2 = 13, _pwm = 15, _standby = 14;
            bool _hugging;
            unsigned long _lastHug;
            unsigned long _inflateCooldown;
            unsigned long _startCooldown;
    };
    
#endif