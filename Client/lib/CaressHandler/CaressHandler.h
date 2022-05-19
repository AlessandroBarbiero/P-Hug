#ifndef CaressHandler_h
    #define CaressHandler_h
    #include <SmallFSR.h>
    #include <WiFi101.h>
    class CaressHandler {
        public:
            CaressHandler(SmallFSR smallFSR1,SmallFSR smallFSR2, SmallFSR smallFSR3);
            void setClient(WiFiClient client);
            void send();
            void start(int interval, int shift);
        private:
            WiFiClient _client;
            SmallFSR _smallfsr1;
            SmallFSR _smallfsr2;
            SmallFSR _smallfsr3;
            
    };
    
#endif