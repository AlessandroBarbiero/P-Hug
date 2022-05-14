#ifndef Ear_h
    #define Ear_h
    #include "Arduino.h"
    #include <WiFi101.h>
    #include <Servo.h>
    class Ear {
        public:
            Ear(int pin);
        private:
            WiFiClient _client;
            int _pin;
            int angle = 0;
    };
    
#endif