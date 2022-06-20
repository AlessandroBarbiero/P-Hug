#include <Arduino.h>
#include <LongFSR.h>
#include <WiFi101.h>

LongFSR::LongFSR(){

}

LongFSR::LongFSR(WiFiClient client, int pin, int trigger) {
    _pin = pin;
    _client = client;
    _trigger = trigger;
}

WiFiClient LongFSR::getClient(){
    return _client;
}

int LongFSR::getTrigger(){
    return _trigger;
}

bool LongFSR::isActive(){
    return _active;
}

void LongFSR::setClient(WiFiClient client){
    _client = client;
}

void LongFSR::setActive(bool active){
    _active = active;
}

void LongFSR::send(){
    int value = analogRead(_pin);

    getClient().write(value);
}

void LongFSR::run(){
    int value = analogRead(_pin);
    if(value > getTrigger()){
        setActive(true);
        Serial.println("=======================================================");
        Serial.println("Hug Done, value:");
        Serial.println(value);
        Serial.println("=======================================================");
    }
    else{
        setActive(false);
    }
}