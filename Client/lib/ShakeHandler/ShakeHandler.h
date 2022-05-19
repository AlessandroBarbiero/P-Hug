#ifndef ShakeHandler_h
    #define ShakeHandler_h
    #include <Arduino.h>
    #include <Accelerometer.h>
    #include <Speaker.h>
    #include <Ear.h>
    #include <WiFi101.h>
    class ShakeHandler {
        public:
            ShakeHandler(int duration, Ear ear1, Ear ear2);
            WiFiClient getClient();
            unsigned long getActivationTime();
            int getDuration();
            Accelerometer getAccelerometer();
            void setClient(WiFiClient client);
            void setActivationTime();
            void setSpeaker(Speaker speaker);
            void setAccelerometer(Accelerometer accelerometer);
            void run();
        private:
            WiFiClient _client;
            int _duration;
            Accelerometer _accelerometer;
            Speaker _speaker;
            Ear _ear1;
            Ear _ear2;
            bool _isShaking = false;
            unsigned long _activationTime = 0;
    };
    
#endif