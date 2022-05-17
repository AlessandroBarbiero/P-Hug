#ifndef WiFiConnection_h
    #define WiFiConnection_h
    #include "Arduino.h"
    #include <WiFi101.h>
    #include <SPI.h>
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
        private:
            char* _ssid     = "Armor 8";
            char* _password = "0032074b4f8e";
            char* _host = "192.168.43.179";
            int _port = 5566;
            WiFiClient _client;
    };
    
#endif