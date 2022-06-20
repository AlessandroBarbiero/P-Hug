#include <Arduino.h>
#include <Credentials.h>

Credentials::Credentials(){
    
}

bool Credentials::readFromMemory(){
    Serial.println("D: Starting reading from memory");
    delay(2000);
    Serial.println("R: read");
    
    unsigned long startTime;
    
    bool searchingSSID = true;
    bool searchingPassword = true;
    bool exit = false;
    String connectionDetails;
    startTime = millis();
    while(!exit && (searchingSSID || searchingPassword)){
        if(Serial.available()>0){
            Serial.print("D: Message arrived from serial: ");
            connectionDetails = Serial.readString();
            Serial.println(connectionDetails);
            if(connectionDetails.equals("Empty")){
                _arePresent = false;
                exit = true;
            }
            else if(connectionDetails.startsWith(SSID_prefix)){
                _ssid = connectionDetails.substring(SSID_prefix.length(), connectionDetails.length()-2);
                searchingSSID = false;
            }
            else if(connectionDetails.startsWith(PSW_prefix)){
                _password = connectionDetails.substring(PSW_prefix.length(), connectionDetails.length()-2);
                searchingPassword = false;
            }
        }
        //if I'm searching the two parameters and the pyco didn't answer for 10 seconds send another read message
        if(searchingSSID && searchingPassword && millis() - startTime >= 10000){
            Serial.println("R: read");
            startTime = millis();
        }
    }
    
    Serial.println("D: /////////////////////////");
    Serial.println("D: Values read from memory: ");
    Serial.print("D: SSID: ");
    Serial.println(_ssid);
    Serial.print("D: Password: ");
    Serial.println(_password);
    Serial.println("D: /////////////////////////");

    if(!exit)
        _arePresent = true;
    
    return _arePresent;
}

// Search for credentials over bluetooth
void Credentials::search(){
    Serial.println("D: Retreiving credentials from Serial Port");
    Serial.println("R: search");

    bool searchingSSID = true;
    bool searchingPassword = true;
    unsigned long startTime;

    String connectionDetails;
    startTime = millis();
    while(searchingSSID || searchingPassword){
        if(Serial.available()>0){
            Serial.print("D: Message arrived from serial: ");
            connectionDetails = Serial.readString();
            Serial.println(connectionDetails);
            if(connectionDetails.startsWith(SSID_prefix)){
                _ssid = connectionDetails.substring(SSID_prefix.length(), connectionDetails.length()-2);
                searchingSSID = false;
            }
            else if(connectionDetails.startsWith(PSW_prefix)){
                _password = connectionDetails.substring(PSW_prefix.length(), connectionDetails.length()-2);
                searchingPassword = false;
            }
        }
        //if I'm searching the two parameters and nobody answered for 20 seconds send another search message
        if(searchingSSID && searchingPassword && millis() - startTime >= 20000){
            Serial.println("R: search");
            startTime = millis();
        }
    }
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