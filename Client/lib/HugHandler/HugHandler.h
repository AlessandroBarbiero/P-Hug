#ifndef Hug_h
    #define Hug_h
    #include <Arduino.h>
    #include <LongFSR.h>
    #include <Speaker.h>
    #include <Ear.h>
    #include <WiFi101.h>
    class Hug {
        public:
            Hug(LongFSR longFSR, Ear ear1, Ear ear2, Speaker speaker);
            WiFiClient getClient();
            unsigned long getActivationTime();
            int getDuration();
            bool getReady();
            void setClient(WiFiClient client);
            void setActivationTime(unsigned long activationTime);
            void setReady(bool ready);
            void run();
        private:
            WiFiClient _client;
            int _duration;
            LongFSR longFSR;
            Speaker _speaker;
            Ear _ear1;
            Ear _ear2;
            unsigned long _activationTime = 0;
            bool _ready = false;
            
    };
    
#endif