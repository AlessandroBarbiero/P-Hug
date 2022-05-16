#ifndef Accelerometer_h
    #define Accelerometer_h
    #include "Arduino.h"
    #include <WiFi101.h>
    #include <Adafruit_MPU6050.h>
    #include <Adafruit_Sensor.h>
    #include <Wire.h>
    class Accelerometer {
        public:
            Accelerometer();
            void setup();
            void setClient(WiFiClient client);
            void send();
            void print();
        private:
            WiFiClient _client;
            Adafruit_MPU6050 _mpu;
    };
    
#endif