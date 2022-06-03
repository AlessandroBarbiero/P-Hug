#ifndef Accelerometer_h
    #define Accelerometer_h
    #include "Arduino.h"
    #include <WiFi101.h>
    #include <Adafruit_MPU6050.h>
    #include <Adafruit_Sensor.h>
    #include <MPU6050_tockn.h>
    #include <Wire.h>
    class Accelerometer {
        public:
            Accelerometer();
            Accelerometer(MPU6050 *mpu6050);
            void setup();
            float getTemperature();
            float getAccelerationX();
            float getAccelerationY();
            float getAccelerationZ();
            float getGyroX();
            float getGyroY();
            float getGyroZ();
            void setClient(WiFiClient client);
            void run();
            void send();
            void print();
        private:
            WiFiClient _client;
            Adafruit_MPU6050 _mpu;
            MPU6050 *_mpu6050;
            float _temp;
            float _accX;
            float _accY;
            float _accZ;
            float _gyroX;
            float _gyroY;
            float _gyroZ;
    };
    
#endif