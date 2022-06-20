#include <Arduino.h>
#include <EEPROMTyped.h>
#include <Credentials.h>

Credentials::Credentials(){
    readFromMemory();
}

void Credentials::clear(){
    EEPROMTyped.write(_arePresentAddress, false);
}

bool Credentials::readFromMemory(){
    _arePresentAddress = 0;
    // I wanted to add error handling but I think is not possible
    EEPROMTyped.read(_arePresentAddress, _arePresent);

    _ssidAddress = _arePresentAddress + EEPROMTyped.sizeOf(_arePresent);
    if(_arePresent){
        EEPROMTyped.read(_ssidAddress, _ssid);
        _passwordAddress = _ssidAddress + EEPROMTyped.sizeOf(_ssid);
        EEPROMTyped.read(_passwordAddress, _password);
    }

    return _arePresent;
}

void Credentials::search(){
    Serial.println("D: Retreiving credentials from Serial Port");
    Serial.println("R: search");

    const String SSID_prefix = "SSID: ";
    const String PSW_prefix = "Password: ";
    bool searchingSSID = true;
    bool searchingPassword = true;

    String connectionDetails;
    while(searchingSSID || searchingPassword){
        if(Serial.available()>0){
            Serial.print("D: Message arrived from serial: ");
            connectionDetails = Serial.readString();
            Serial.println(connectionDetails);
            if(connectionDetails.startsWith(SSID_prefix)){
                _ssid = connectionDetails.substring(SSID_prefix.length());
                searchingSSID = false;
            }
            else if(connectionDetails.startsWith(PSW_prefix)){
                _password = connectionDetails.substring(PSW_prefix.length());
                searchingPassword = false;
            }
        }
    }
    Serial.println("R: success");
}

void Credentials::save(){
    if(!_arePresent){
        EEPROMTyped.write(_arePresentAddress, true);
    }

    EEPROMTyped.write(_ssidAddress, _ssid);
    _passwordAddress = _ssidAddress + EEPROMTyped.sizeOf(_ssid);
    EEPROMTyped.write(_passwordAddress, _password);
}

//%%%%%%%%%% GETTERS %%%%%%%%%%%

bool Credentials::arePresent(){
    return _arePresent;
}
String Credentials::getSsid(){
    return _ssid;
}
String Credentials::getPassword(){
    return _password;
}