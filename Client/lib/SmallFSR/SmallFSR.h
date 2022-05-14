#include <WiFi101.h>

#ifndef SmallFSR_h
    #define SmallFSR_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class SmallFSR {
        public:
            SmallFSR(WiFiClient client, int pin, int trigger);
            void setClient(WiFiClient client);
            void send();
            void start(int interval, int shift);
        private:
            WiFiClient _client;
            int _pin;
            int _trigger;
            int _step;
    };
    
#endif