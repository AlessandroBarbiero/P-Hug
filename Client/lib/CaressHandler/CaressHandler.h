#ifndef CaressHandler_h
    #define CaressHandler_h
    #include <Arduino.h>
    #include <SmallFSR.h>
    #include <Speaker.h>
    #include <Ear.h>
    #include <WiFi101.h>
    class CaressHandler {
        public:
            CaressHandler(SmallFSR smallFSR1, SmallFSR smallFSR2, SmallFSR smallFSR3, Ear ear1, Ear ear2);
            WiFiClient getClient();
            unsigned long getActivationTime();
            int getDuration();
            bool getReady();
            void setClient(WiFiClient client);
            void setActivationTime(unsigned long activationTime);
            void setReady(bool ready);
            void setSpeaker(Speaker speaker);
            void run();
        private:
            WiFiClient _client;
            int _duration;
            SmallFSR _smallFSR1;
            SmallFSR _smallFSR2;
            SmallFSR _smallFSR3;
            Speaker _speaker;
            Ear _ear1;
            Ear _ear2;
            unsigned long _activationTime = 0;
            bool _ready = false;
            
    };
    
#endif