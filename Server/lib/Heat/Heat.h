#ifndef Heat_h
    #define Heat_h
    #include "Arduino.h"
    class Heat  {
        public:
            Heat(unsigned long heatingTime, unsigned long cooldown);
            void run();
            void start();
        private:
            uint8_t _light;
            bool _heating;
            unsigned long _lastHeat;
            unsigned long _heatingTime;
            unsigned long _cooldown;
    };
    
#endif