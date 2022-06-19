#ifndef HugHandler_h
    #define HugHandler_h
    #include <Arduino.h>
    #include <LongFSR.h>
    #include <Speaker.h>
    #include <Ear.h>
    #include <WiFi101.h>
    class HugHandler {
        public:
            HugHandler(LongFSR, Ear ear1, Ear ear2);
            WiFiClient getClient();
            void setClient(WiFiClient client);
            void setSpeaker(Speaker speaker);
            void run();
        private:
            WiFiClient _client;
            LongFSR _longFSR;
            Speaker _speaker;
            Ear _ear1;
            Ear _ear2; 
            unsigned long _messageTime;           
    };
    
#endif