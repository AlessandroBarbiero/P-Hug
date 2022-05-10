#include <WiFi101.h>

#ifndef SmallFSR_h
    #define SmallFSR_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class SmallFSR {
        public:
            SmallFSR(WiFiClient client, int pin, int mapping);
            void send();
            void start(int interval, int shift);
            bool checkAction(int position);
        private:
            WiFiClient _client;
            int _pin;
            int _mapping;
            int _step;
            bool p1 = false;
            bool p2 = false;
            bool p3 = false;
    };
    
#endif