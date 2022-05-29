#ifndef Ear_h
    #define Ear_h
    #include "Arduino.h"
    #include <WiFi101.h>
    #include <Servo.h>
    class Ear {
        public:
            Ear();
            Ear(int pin, bool isRight);
            void action();
            void connect();
            void disconnect();
            void caress();
            void hug();
            void shake();
            void read();
        private:
            WiFiClient _client;
            int _pin;
            Servo _servo;
            int _angle = 0;
            bool _isRight;
    };
    
#endif