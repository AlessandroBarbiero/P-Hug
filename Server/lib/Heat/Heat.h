#ifndef Heat_h
    #define Heat_h
    #include "Arduino.h"
    class Heat  {
        public:
            Heat(unsigned long heatingTime, unsigned long cooldown);
            void run(unsigned long time);
            void start(unsigned long startingTime);
        private:
            bool _heating;
            unsigned long _lastHeat;
            unsigned long _heatingTime;
            unsigned long _cooldown;
    };
    
#endif