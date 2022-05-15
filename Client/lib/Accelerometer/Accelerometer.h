#ifndef Accelerometer_h
    #define Accelerometer_h
    #include "Arduino.h"
    #include <WiFi101.h>
    class Accelerometer {
        public:
            Accelerometer();
            void setClient(WiFiClient client);
            void send();
            void start(int interval, int shift);
        private:
            WiFiClient _client;
            int _pin;
    };
    
#endif