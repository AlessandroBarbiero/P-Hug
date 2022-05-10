#include <WiFi101.h>

#ifndef LongFSR_h
    #define LongFSR_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class LongFSR {
        public:
            LongFSR(WiFiClient client, int pin, int trigger);
            void send();
            void start(int interval, int shift);
        private:
            WiFiClient _client;
            int _pin;
            int _trigger;
            int _step;
    };
    
#endif