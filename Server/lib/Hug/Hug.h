#ifndef Hug_h
    #define Hug_h
    #include "Arduino.h"
    class Hug  {
        public:
            Hug(int inflateCooldown, int startCooldown);
            void run();
            void start();
        private:
            uint8_t _pin;
            bool _hugging;
            unsigned long _lastHug;
            int _inflateCooldown;
            int _startCooldown;
    };
    
#endif