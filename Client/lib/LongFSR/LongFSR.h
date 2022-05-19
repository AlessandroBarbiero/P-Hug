#include <WiFi101.h>

#ifndef LongFSR_h
    #define LongFSR_h
    #define MAX_PINS 5
    #include "Arduino.h"
    class LongFSR {
        public:
            LongFSR();
            LongFSR(WiFiClient client, int pin, int trigger);
            WiFiClient getClient();
            int getTrigger();
            bool isActive();
            void setClient(WiFiClient client);
            void setActive(bool active);
            void send();
            void run();
        private:
            WiFiClient _client;
            int _pin;
            int _trigger;
            bool _active = false;
    };
    
#endif