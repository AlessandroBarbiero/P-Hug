#ifndef NFC_h
    #define NFC_h
    #include "Arduino.h"
    #include <Wire.h>
    #include <SPI.h>
    #include <Adafruit_PN532.h>
    class NFC{
        public:
            NFC();
            NFC(Adafruit_PN532 *nfc);
            void setup();
            char *getSSID();
            char *getPassword();
            uint8_t *getPayloadFromMifareClassicTag(uint8_t uid[], uint8_t uidLength);
            void run();
            void readMifareClassicTag(uint8_t uid[], uint8_t uidLength);
            void getPayloadFromMifareClassicTag(uint8_t uid[], uint8_t uidLength, uint8_t payload[]);
            void getWiFiData(uint8_t payload[]);
            void getData();
            void printWiFiData();
        private:
            Adafruit_PN532 *_nfc;
            char _ssid[30];
            char _password[30];
    };

#endif