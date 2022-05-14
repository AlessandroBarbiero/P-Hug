#include <Arduino.h>
#include <LongFSR.h>
#include <WiFi101.h>


LongFSR::LongFSR(WiFiClient client, int pin, int trigger) {
    _pin = pin;
    _client = client;
    _trigger = trigger;
}

void LongFSR::setClient(WiFiClient client){
    _client = client;
}

void LongFSR::send(){
    int value = analogRead(_pin);
    _client.write('h');
    //Serial.println(value);
    /*
    if(value > _trigger){
        Serial.println("Hugged done");
        _client.write('h');
    }
    */
   //_client.write('h');
}