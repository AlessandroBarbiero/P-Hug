#ifndef WiFiConnection_h
    #define WiFiConnection_h
    #include "Arduino.h"
    #include <WiFi101.h>
    #include <SPI.h>
    #include <NFC.h>
    class WiFiConnection {
        public:
            WiFiConnection();
            int getPort();
            char* getHost();
            char* getssid();
            char* getPassword();
            WiFiClient getClient();
            void setup();
            void connect();
            void ping(WiFiClient client);
            void setNFC(NFC nfc);

        private:
            char* _ssid;
            char* _password;
            char* _host = "192.168.43.179";
            int _port = 5566;
            WiFiClient _client;
            unsigned long _pingActivationTime = 0;
            bool _isPinging = false;
            NFC _nfc;

    };
    
#endif