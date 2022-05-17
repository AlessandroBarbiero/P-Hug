#include <Arduino.h>
#include <SmallFSR.h>
#include <WiFi101.h>


SmallFSR::SmallFSR(WiFiClient client, int pin, int trigger) {
    _pin = pin;
    _client = client;
    _trigger = trigger;
}

void SmallFSR::setClient(WiFiClient client){
    _client = client;
}

void SmallFSR::send(){
    int value = analogRead(_pin);
    Serial.println(value);
    if(value > _trigger){
        Serial.println("Caress done");
        _client.write('c');
    }
}