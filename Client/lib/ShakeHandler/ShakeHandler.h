#ifndef ShakeHandler_h
    #define ShakeHandler_h
    #include <Arduino.h>
    #include <Accelerometer.h>
    #include <Speaker.h>
    #include <Ear.h>
    #include <WiFi101.h>
    class ShakeHandler {
        public:
            ShakeHandler(Ear ear1, Ear ear2);
            WiFiClient getClient();
            unsigned long getActivationTime();
            int getDuration();
            bool getReady();
            void setClient(WiFiClient client);
            void setActivationTime(unsigned long activationTime);
            void setReady(bool ready);
            void setSpeaker(Speaker speaker);
            void setAccelerometer(Accelerometer accelerometer);
            void run();
        private:
            WiFiClient _client;
            int _duration;
            Accelerometer accelerometer;
            Speaker _speaker;
            Ear _ear1;
            Ear _ear2;
            unsigned long _activationTime = 0;
            bool _ready = false;
            
    };
    
#endif