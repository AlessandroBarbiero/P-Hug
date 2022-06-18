#include <NFC.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

NFC::NFC(Adafruit_PN532 *nfc){
    _nfc = nfc;
}

NFC::NFC(){

}


void NFC::setup(){
    (*_nfc).begin();
    uint32_t versiondata = (*_nfc).getFirmwareVersion();
    if (! versiondata) {
        Serial.print("Didn't find PN53x board");
        while (1); // halt
    }
    // Got ok data, print it out!
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
    Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
    Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
    
    // configure board to read RFID tags
    (*_nfc).SAMConfig();
    
    Serial.println("Waiting for an ISO14443A tag ...");
}

char* NFC::getSSID(){
  return _ssid;
}

char* NFC::getPassword(){
  return _password;
}

void NFC::run(){
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
    uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    uint8_t payload[1024];
        
    // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
    // 'uid' will be populated with the UID, and uidLength will indicate
    // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
    success = (*_nfc).readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
    if (success) {
        // Display some basic information about the card
        Serial.println("Found an ISO14443A tag");
        (*_nfc).PrintHex(uid, uidLength);
        
        if (uidLength == 4)
        {
        // We probably have a Mifare Classic card ... 
        uint32_t cardid = uid[0];
        cardid <<= 8;
        cardid |= uid[1];
        cardid <<= 8;
        cardid |= uid[2];  
        cardid <<= 8;
        cardid |= uid[3]; 
        Serial.print("Seems to be a Mifare Classic tag");
        //Serial.println(cardid);
        }
        getPayloadFromMifareClassicTag(uid,uidLength,payload);
        getWiFiData(payload);
        printWiFiData();
        Serial.println("");
        
    }
}

// Read and dump a Mifare Classic card (UID is 4 bytes)
void NFC::readMifareClassicTag(uint8_t uid[], uint8_t uidLength) {
  uint8_t success;
  uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  uint8_t data[16];
  char dataline[12];
  
  // Skipping manufacturer block
  for (uint8_t blockn = 1; blockn < 64; blockn++)
  {
    success = (*_nfc).mifareclassic_AuthenticateBlock(uid, uidLength, blockn, 1, keya);
    
    if (success)
    {
      success = (*_nfc).mifareclassic_ReadDataBlock(blockn, data);
    
      if (success)
      {
        // Data seems to have been read ... spit it out
        sprintf(dataline, "Block %02d : ", blockn);
        Serial.print(dataline);

        if (((blockn + 1) % 4) == 0) {
            Serial.print(F("[ Sector ] "));
        } else {
            Serial.print(F("[  Data  ] "));
        }
        
        (*_nfc).PrintHexChar(data, 16);

      } else {
        Serial.println(F("[unable to read .. quitting]"));
        return;
      } 
    } else {
      Serial.println(F("[unable to authenticate .. quitting]"));
      return;
    } 
  }
}

// Get the payload from MifareClassicTag
void NFC::getPayloadFromMifareClassicTag(uint8_t uid[], uint8_t uidLength, uint8_t payload[]) {
  uint8_t success;
  uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  uint8_t data[16];
  
  // Skipping manufacturer block
  for (uint8_t blockn = 1; blockn < 64; blockn++)
  {
    success = (*_nfc).mifareclassic_AuthenticateBlock(uid, uidLength, blockn, 1, keya);
    
    if (success)
    {
      success = (*_nfc).mifareclassic_ReadDataBlock(blockn, data);    
      if (success){
        for(int i = 0; i < 16; i++){
          payload[i + (blockn - 1)*16 ] = data[i];
        }
      } else {
        Serial.println(F("[unable to read .. quitting]"));
        return;
      } 
    } else {
      Serial.println(F("[unable to authenticate .. quitting]"));
      return;
    } 
  }
}

// Save the ssid in the pointer and return the lenght of the ssid
void NFC::getWiFiData(uint8_t payload[]){
  int ssidLen = 0;
  int i = 0;
  int j = 0;
  for(i = 57; payload[i]!=42; i++){
    _ssid[i-57]=payload[i];
    ssidLen = ssidLen +1;
  }
  i++;
  while(payload[i]!=254){
    _password[j] = payload[i];
    j++;
    i++;
  }
}


void NFC::printWiFiData(){
  Serial.println("---------------------------------------------------");
  Serial.println("SSID:");
  Serial.println(_ssid);
  Serial.println("");
  Serial.println("Password:");
  Serial.println(_password);
  Serial.println("");
  Serial.println("---------------------------------------------------");
  Serial.println("");
}





