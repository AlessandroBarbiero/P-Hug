#include <WiFi101.h>

#ifndef SmallFSR_h
    #define SmallFSR_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class SmallFSR {
        public:
            SmallFSR(WiFiClient client, int pin, int trigger, int duration);
            unsigned long getActivationTime();
            bool isActive();
            int getDuration();
            void setActive(bool isActive);
            void setActivationTime();
            void setClient(WiFiClient client);
            void send();
            void start();
        private:
            WiFiClient _client;
            int _pin;
            int _trigger;
            int _duration;
            int _step;
            bool _active = false;
            unsigned long _activationTime;
    };
    
#endif