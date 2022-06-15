#ifndef NFC_h
    #define NFC_h
    #include "Arduino.h"
    #include <Wire.h>
    #include <SPI.h>
    #include <Adafruit_PN532.h>
    class NFC{
        public:
            NFC(Adafruit_PN532 *nfc);
            void setup();
            uint8_t *getPayloadFromMifareClassicTag(uint8_t uid[], uint8_t uidLength);
            void run();
            void readMifareClassicTag(uint8_t uid[], uint8_t uidLength);
            void getPayloadFromMifareClassicTag(uint8_t uid[], uint8_t uidLength, uint8_t payload[]);
        private:
            Adafruit_PN532 *_nfc;
    };

#endif